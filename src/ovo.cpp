
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 2.0
 * @version 0.0.1
 */


#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <io.h>
#include <string>
#include <algorithm>

#include "ovo.h"



/****** Class info ******/

/**
 * Display version
 *
 * @access public
 */
string ovo::info::version = "Version 0.0.1";

/**
 * Display a welcome string
 *
 * @access public
 * @param void
 * @return void
 */
void ovo::info::detail() const
{
    cout << endl << "Lib Name: ovo" <<endl;
    cout << "Org: EEENeko (https://github.com/eeeNeko)" << endl;
    cout << "Author: Jianzhi Fan, Yimian Liu" << endl;
    cout << "license GNU General Public License 2.0" << endl;
    cout << "copyright Copyright (c) 2019 EEENeko" << endl << endl;
}



/****** Class file ******/

/**
 * Get All Files info with certain format
 *
 * @Author yimian
 * @access private
 * @param string path filePath
 * @param string format  #such as "*.jpg"
 * @param int isShowPath  #If this is 1, the path would display before every filename
 * @return void
 */
void ovo::file::get_all_files_info(string path, const string format, const int isShowPath)
{
    long hFile = 0;
    //File info struct
    struct _finddata_t fileInfo;
    FileInfo t_file;
    string p;
#ifdef linux    
    const string sign = "/";
#else
    const string sign = "\\";
#endif
    //If the path end with '/'
    if(path[path.size()-1] == '/' || path[path.size()-1] == '\\') path.erase(path.end() - 1);
    //Deal with files
    if((hFile = _findfirst(p.assign(path).append(sign+format).c_str(),&fileInfo)) != -1){
        do
        {
            if(!(fileInfo.attrib & _A_SUBDIR)){
                if(isShowPath)
                    t_file.name = p.assign(path).append(sign).append(fileInfo.name);
                else
                    t_file.name = p.assign(fileInfo.name);

                t_file.size = fileInfo.size;
                t_file.time_create = fileInfo.time_create;
                t_file.time_access = fileInfo.time_access;
                t_file.time_write = fileInfo.time_write;
                t_file.attrib = fileInfo.attrib;
                file.push_back(t_file);
            }

        }while(_findnext(hFile, &fileInfo) == 0);

        _findclose(hFile);
    }
}

/**
 * Get All Folders and subFolders
 *
 * @Author yimian
 * @access private
 * @param string path filePath
 * @param vector<string>& folders
 * @return void
 */
void ovo::file::get_all_folders_name(string path, vector<string>& folders)
{
    long hFile = 0;
    //File info struct
    struct _finddata_t fileInfo;
    string p;
#ifdef linux    
    const string sign = "/";
#else
    const string sign = "\\";
#endif
    //If the path end with '/'
    if(path[path.size()-1] == '/' || path[path.size()-1] == '\\') path.erase(path.end() - 1);
    //Deal with folders
    if((hFile = _findfirst(p.assign(path).append(sign+"*").c_str(),&fileInfo)) != -1){
        do
        {
            if((fileInfo.attrib & _A_SUBDIR)){
                if(strcmp(fileInfo.name,".") != 0 && strcmp(fileInfo.name,"..") != 0){
                    folders.push_back(p.assign(path).append(sign).append(fileInfo.name));
                    get_all_folders_name(p.assign(path).append(sign).append(fileInfo.name), folders);
                }
            }

        }while(_findnext(hFile, &fileInfo) == 0);

        _findclose(hFile);
    }
}

/**
 * Get files with certain format and settings
 *
 * @Author yimian
 * @access public
 * @param string path filePath
 * @param string format  #such as "*.jpg"
 * @param int isSearchSubfolders  ##If this is 1, will search all the sub folders
 * @param int isShowPath  #If this is 1, the path would display before every filename
 * @return void
 */
void ovo::file::get_files_info(const string path, const string format, const int isSearchSubfolders, const int isShowPath)
{

#ifdef linux    
    const string sign = "/";
#else
    const string sign = "\\";
#endif

    get_all_files_info(path, format, isShowPath);

    //Search Sub Folders
    if(isSearchSubfolders){
        vector<string> foldersPath;
        get_all_folders_name(path, foldersPath);

        for(int i = 0; i < foldersPath.size(); i++){

            get_all_files_info(foldersPath[i], format, isShowPath);
        }
    }

}





/****** Class math ******/

/*** md5 ***/

/**
 * @From file md5.h
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Oct 19 2014
 */
/* Define the static member of md5. */
const byte ovo::math::MD5::PADDING[64] = { 0x80 };
const char ovo::math::MD5::HEX_NUMBERS[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};

/**
 * @Construct a md5 object with a string.
 *
 * @param {message} the message will be transformed.
 *
 */
ovo::math::MD5::MD5(const string& message)
{
    finished = false;
    /* Reset number of bits. */
    count[0] = count[1] = 0;
    /* Initialization constants. */
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;

    /* Initialization the object according to message. */
    init((const byte*)message.c_str(), message.length());
}

/**
 * @Generate md5 digest.
 *
 * @return the message-digest.
 *
 */
const byte* ovo::math::MD5::getDigest()
{
    if (!finished) {
        finished = true;

        byte bits[8];
        bit32 oldState[4];
        bit32 oldCount[2];
        bit32 index, padLen;

        /* Save current state and count. */
        memcpy(oldState, state, 16);
        memcpy(oldCount, count, 8);

        /* Save number of bits */
        encode(count, bits, 8);

        /* Pad out to 56 mod 64. */
        index = (bit32)((count[0] >> 3) & 0x3f);
        padLen = (index < 56) ? (56 - index) : (120 - index);
        init(PADDING, padLen);

        /* Append length (before padding) */
        init(bits, 8);

        /* Store state in digest */
        encode(state, digest, 16);

        /* Restore current state and count. */
        memcpy(state, oldState, 16);
        memcpy(count, oldCount, 8);
    }
    return digest;
}

/**
 * @Initialization the md5 object, processing another message block,
 * and updating the context.
 *
 * @param {input} the input message.
 *
 * @param {len} the number btye of message.
 *
 */
void ovo::math::MD5::init(const byte* input, size_t len)
{
    bit32 i, index, partLen;

    finished = false;

    /* Compute number of bytes mod 64 */
    index = (bit32)((count[0] >> 3) & 0x3f);

    /* update number of bits */
    if ((count[0] += ((bit32)len << 3)) < ((bit32)len << 3)) {
        ++count[1];
    }
    count[1] += ((bit32)len >> 29);

    partLen = 64 - index;

      /* transform as many times as possible. */
      if (len >= partLen) {
        memcpy(&buffer[index], input, partLen);
        transform(buffer);

        for (i = partLen; i + 63 < len; i += 64) {

            transform(&input[i]);
        }
        index = 0;
    } else {
        i = 0;
    }

    /* Buffer remaining input */
    memcpy(&buffer[index], &input[i], len - i);
}

/**
 * @md5 basic transformation. Transforms state based on block.
 *
 * @param {block} the message block.
 */
void ovo::math::MD5::transform(const byte block[64])
{
    bit32 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    decode(block, x, 64);

    /* Round 1 */
    FF (a, b, c, d, x[ 0], s11, 0xd76aa478);
    FF (d, a, b, c, x[ 1], s12, 0xe8c7b756);
    FF (c, d, a, b, x[ 2], s13, 0x242070db);
    FF (b, c, d, a, x[ 3], s14, 0xc1bdceee);
    FF (a, b, c, d, x[ 4], s11, 0xf57c0faf);
    FF (d, a, b, c, x[ 5], s12, 0x4787c62a);
    FF (c, d, a, b, x[ 6], s13, 0xa8304613);
    FF (b, c, d, a, x[ 7], s14, 0xfd469501);
    FF (a, b, c, d, x[ 8], s11, 0x698098d8);
    FF (d, a, b, c, x[ 9], s12, 0x8b44f7af);
    FF (c, d, a, b, x[10], s13, 0xffff5bb1);
    FF (b, c, d, a, x[11], s14, 0x895cd7be);
    FF (a, b, c, d, x[12], s11, 0x6b901122);
    FF (d, a, b, c, x[13], s12, 0xfd987193);
    FF (c, d, a, b, x[14], s13, 0xa679438e);
    FF (b, c, d, a, x[15], s14, 0x49b40821);

    /* Round 2 */
    GG (a, b, c, d, x[ 1], s21, 0xf61e2562);
    GG (d, a, b, c, x[ 6], s22, 0xc040b340);
    GG (c, d, a, b, x[11], s23, 0x265e5a51);
    GG (b, c, d, a, x[ 0], s24, 0xe9b6c7aa);
    GG (a, b, c, d, x[ 5], s21, 0xd62f105d);
    GG (d, a, b, c, x[10], s22,  0x2441453);
    GG (c, d, a, b, x[15], s23, 0xd8a1e681);
    GG (b, c, d, a, x[ 4], s24, 0xe7d3fbc8);
    GG (a, b, c, d, x[ 9], s21, 0x21e1cde6);
    GG (d, a, b, c, x[14], s22, 0xc33707d6);
    GG (c, d, a, b, x[ 3], s23, 0xf4d50d87);
    GG (b, c, d, a, x[ 8], s24, 0x455a14ed);
    GG (a, b, c, d, x[13], s21, 0xa9e3e905);
    GG (d, a, b, c, x[ 2], s22, 0xfcefa3f8);
    GG (c, d, a, b, x[ 7], s23, 0x676f02d9);
    GG (b, c, d, a, x[12], s24, 0x8d2a4c8a);

    /* Round 3 */
    HH (a, b, c, d, x[ 5], s31, 0xfffa3942);
    HH (d, a, b, c, x[ 8], s32, 0x8771f681);
    HH (c, d, a, b, x[11], s33, 0x6d9d6122);
    HH (b, c, d, a, x[14], s34, 0xfde5380c);
    HH (a, b, c, d, x[ 1], s31, 0xa4beea44);
    HH (d, a, b, c, x[ 4], s32, 0x4bdecfa9);
    HH (c, d, a, b, x[ 7], s33, 0xf6bb4b60);
    HH (b, c, d, a, x[10], s34, 0xbebfbc70);
    HH (a, b, c, d, x[13], s31, 0x289b7ec6);
    HH (d, a, b, c, x[ 0], s32, 0xeaa127fa);
    HH (c, d, a, b, x[ 3], s33, 0xd4ef3085);
    HH (b, c, d, a, x[ 6], s34,  0x4881d05);
    HH (a, b, c, d, x[ 9], s31, 0xd9d4d039);
    HH (d, a, b, c, x[12], s32, 0xe6db99e5);
    HH (c, d, a, b, x[15], s33, 0x1fa27cf8);
    HH (b, c, d, a, x[ 2], s34, 0xc4ac5665);

    /* Round 4 */
    II (a, b, c, d, x[ 0], s41, 0xf4292244);
    II (d, a, b, c, x[ 7], s42, 0x432aff97);
    II (c, d, a, b, x[14], s43, 0xab9423a7);
    II (b, c, d, a, x[ 5], s44, 0xfc93a039);
    II (a, b, c, d, x[12], s41, 0x655b59c3);
    II (d, a, b, c, x[ 3], s42, 0x8f0ccc92);
    II (c, d, a, b, x[10], s43, 0xffeff47d);
    II (b, c, d, a, x[ 1], s44, 0x85845dd1);
    II (a, b, c, d, x[ 8], s41, 0x6fa87e4f);
    II (d, a, b, c, x[15], s42, 0xfe2ce6e0);
    II (c, d, a, b, x[ 6], s43, 0xa3014314);
    II (b, c, d, a, x[13], s44, 0x4e0811a1);
    II (a, b, c, d, x[ 4], s41, 0xf7537e82);
    II (d, a, b, c, x[11], s42, 0xbd3af235);
    II (c, d, a, b, x[ 2], s43, 0x2ad7d2bb);
    II (b, c, d, a, x[ 9], s44, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

/**
* @Encodes input (unsigned long) into output (byte).
*
* @param {input} usigned long.
*
* @param {output} byte.
*
* @param {length} the length of input.
*
*/
void ovo::math::MD5::encode(const bit32* input, byte* output, size_t length)
{
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {

        output[j]= (byte)(input[i] & 0xff);
        output[j + 1] = (byte)((input[i] >> 8) & 0xff);
        output[j + 2] = (byte)((input[i] >> 16) & 0xff);
        output[j + 3] = (byte)((input[i] >> 24) & 0xff);
    }
}

/**
 * @Decodes input (byte) into output (usigned long).
 *
 * @param {input} bytes.
 *
 * @param {output} unsigned long.
 *
 * @param {length} the length of input.
 *
 */
void ovo::math::MD5::decode(const byte* input, bit32* output, size_t length)
{
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {

        output[i] = ((bit32)input[j]) | (((bit32)input[j + 1]) << 8) |
        (((bit32)input[j + 2]) << 16) | (((bit32)input[j + 3]) << 24);
    }
}


/**
 * @Convert digest to string value.
 *
 * @return the hex string of digest.
 *
 */
string ovo::math::MD5::toStr(const int length)
{
    const byte* digest_ = getDigest();
    string str;
    str.reserve(16 << 1);
    for (size_t i = 0; i < 16; ++i) {

        int t = digest_[i];
        int a = t / 16;
        int b = t % 16;
        str.append(1, HEX_NUMBERS[a]);
        str.append(1, HEX_NUMBERS[b]);
    }
    return str.substr(0, (length > 0 && length < 33) ? length : 32);
}


/*** base64 ***/

/**
 * 
 * @From file base64.h
 * @author ReneNyffenegger
 * @mail rene.nyffenegger@adp-gmbh.ch
 * @github https://github.com/ReneNyffenegger
 * 
 */
const string ovo::math::base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

string ovo::math::base64_encode(const string fromStr)
{
    char const* bytes_to_encode = fromStr.c_str();
    unsigned int in_len = fromStr.length();
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while(in_len--) {

        char_array_3[i++] = *(bytes_to_encode++);
        if(i == 3) {
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for(i = 0; (i <4) ; i++)

            ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if(i) {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';
    }

    return ret;
}

string ovo::math::base64_decode(string const& encoded_string)
{
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;

    while(in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {

        char_array_4[i++] = encoded_string[in_]; in_++;
        if(i ==4) {
        for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

        char_array_3[0] = ( char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

        for(i = 0; (i < 3); i++)
            ret += char_array_3[i];
        i = 0;
        }
    }

    if(i) {
        for(j = 0; j < i; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}


/*** sha256 ***/
const unsigned int ovo::math::SHA256::sha256_k[64] = //UL = uint32
{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void ovo::math::SHA256::transform(const unsigned char *message, unsigned int block_nb)
{
    uint32 w[64];
    uint32 wv[8];
    uint32 t1, t2;
    const unsigned char *sub_block;
    int i;
    int j;
    for (i = 0; i < (int) block_nb; i++) {
        sub_block = message + (i << 6);
        for (j = 0; j < 16; j++) {
            SHA2_PACK32(&sub_block[j << 2], &w[j]);
        }
        for (j = 16; j < 64; j++) {
            w[j] =  SHA256_F4(w[j -  2]) + w[j -  7] + SHA256_F3(w[j - 15]) + w[j - 16];
        }
        for (j = 0; j < 8; j++) {
            wv[j] = m_h[j];
        }
        for (j = 0; j < 64; j++) {
            t1 = wv[7] + SHA256_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
            + sha256_k[j] + w[j];
            t2 = SHA256_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }
        for (j = 0; j < 8; j++) {
            m_h[j] += wv[j];
        }
    }
}

void ovo::math::SHA256::init()
{
    m_h[0] = 0x6a09e667;
    m_h[1] = 0xbb67ae85;
    m_h[2] = 0x3c6ef372;
    m_h[3] = 0xa54ff53a;
    m_h[4] = 0x510e527f;
    m_h[5] = 0x9b05688c;
    m_h[6] = 0x1f83d9ab;
    m_h[7] = 0x5be0cd19;
    m_len = 0;
    m_tot_len = 0;
}

void ovo::math::SHA256::update(const unsigned char *message, unsigned int len)
{
    unsigned int block_nb;
    unsigned int new_len, rem_len, tmp_len;
    const unsigned char *shifted_message;
    tmp_len = SHA224_256_BLOCK_SIZE - m_len;
    rem_len = len < tmp_len ? len : tmp_len;
    memcpy(&m_block[m_len], message, rem_len);
    if (m_len + len < SHA224_256_BLOCK_SIZE) {
        m_len += len;
        return;
    }
    new_len = len - rem_len;
    block_nb = new_len / SHA224_256_BLOCK_SIZE;
    shifted_message = message + rem_len;
    transform(m_block, 1);
    transform(shifted_message, block_nb);
    rem_len = new_len % SHA224_256_BLOCK_SIZE;
    memcpy(m_block, &shifted_message[block_nb << 6], rem_len);
    m_len = rem_len;
    m_tot_len += (block_nb + 1) << 6;
}

void ovo::math::SHA256::final(unsigned char *digest)
{
    unsigned int block_nb;
    unsigned int pm_len;
    unsigned int len_b;
    int i;
    block_nb = (1 + ((SHA224_256_BLOCK_SIZE - 9)
                     < (m_len % SHA224_256_BLOCK_SIZE)));
    len_b = (m_tot_len + m_len) << 3;
    pm_len = block_nb << 6;
    memset(m_block + m_len, 0, pm_len - m_len);
    m_block[m_len] = 0x80;
    SHA2_UNPACK32(len_b, m_block + pm_len - 4);
    transform(m_block, block_nb);
    for (i = 0 ; i < 8; i++) {
        SHA2_UNPACK32(m_h[i], &digest[i << 2]);
    }
}

string ovo::math::sha256(string input)
{
    unsigned char digest[ovo::math::SHA256::DIGEST_SIZE];
    memset(digest,0,ovo::math::SHA256::DIGEST_SIZE);
    
    SHA256 ctx = SHA256();
    ctx.init();
    ctx.update( (unsigned char*)input.c_str(), input.length());
    ctx.final(digest);
    
    char buf[2*ovo::math::SHA256::DIGEST_SIZE+1];
    buf[2*ovo::math::SHA256::DIGEST_SIZE] = 0;
    for (int i = 0; i < ovo::math::SHA256::DIGEST_SIZE; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    return string(buf);
}











