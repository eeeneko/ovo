
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */


#ifndef _OVO_H
#define _OVO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <exception>
#include <map>
#include <iomanip>

#ifdef _pthread

#include <thread>
#include <chrono>

#endif

#define BLOCK_SIZE 16 //AES Block Size

/* Define of btye.*/
typedef unsigned char byte;
/* Define of byte. */
typedef unsigned int bit32;


using namespace std;


namespace ovo{

    /**
    * Show info about ovo
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class info{

        public:
            static string version;
            inline void hi() const {cout << "Hello OvO~" << endl;};
            void detail() const;
    };

    /**
    * Operate with files
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class file{

        public:
            /*** Files ***/
            class FileInfo {
                public:
                    string name; //File name
                    string path;
                    unsigned int size; //File size
                    time_t time_create; //File created time
                    time_t time_access; //File last accessed time
                    time_t time_write; //File last write time
                    unsigned int attrib; //File attribute*/
            } FileInfo;
            vector<class FileInfo> file;
            /* Get files numbers */
            inline int num(){return file.size();} 
            /* Get info of Files */
            void get_files_info(const string path, const string format = "*", const int isSearchSubfolders = 0);

        private:
            /*** Files ***/
            void get_all_files_info(string path, const string format = "*");
            void get_all_folders_name(string path, vector<string>& folders);
    };

    /**
    * Math operation
    *
    * @author yimian, Jiewei Wei(md5), Rene Nyffenegger(base64), Louis Nam(sha256)
    * @category ovo
    * @package ovo
    */
    class math {

            /*** md5 ***/
        public:
            inline string md5 (const string message) const {
                MD5 m(message);
                return m.toStr();
            }

            class MD5 {

                public:
                    /* Construct a md5 object with a string. */
                    MD5(const string& message);
                    /* Generate md5 digest. */
                    const byte* getDigest();
                    /* Convert digest to string value */
                    string toStr(const int length = 32);

                private:
                    /* Initialization the md5 object, processing another message block,
                     * and updating the context.*/
                    void init(const byte* input, size_t len);
                    /* md5 basic transformation. Transforms state based on block. */
                    void transform(const byte block[64]);
                    /* Encodes input (usigned long) into output (byte). */
                    void encode(const bit32* input, byte* output, size_t length);
                    /* Decodes input (byte) into output (usigned long). */
                    void decode(const byte* input, bit32* output, size_t length);
                    /* Flag for mark whether calculate finished. */
                    bool finished;
                    /* state (ABCD). */
                    bit32 state[4];
                    /* number of bits, low-order word first. */
                    bit32 count[2];
                    /* input buffer. */
                    byte buffer[64];
                    /* message digest. */
                    byte digest[16];
                    /* padding for calculate. */
                    static const byte PADDING[64];
                    /* Hex numbers. */
                    static const char HEX_NUMBERS[16];
            };


            /*** base64 ***/
        public:
            string base64_encode(const string fromStr);
            string base64_decode(string const& s);

        private:
            static const string base64_chars;
            static inline bool is_base64(unsigned char c) {
                return (isalnum(c) || (c == '+') || (c == '/'));
            }


            /*** SHA256 ***/
        public:
            string sha256(string input);

        private:
            class SHA256 {
                protected:
                    typedef unsigned char uint8;
                    typedef unsigned int uint32;
                    typedef unsigned long long uint64;

                    const static uint32 sha256_k[];
                    static const unsigned int SHA224_256_BLOCK_SIZE = (512/8);
                public:
                    void init();
                    void update(const unsigned char *message, unsigned int len);
                    void final(unsigned char *digest);
                    static const unsigned int DIGEST_SIZE = ( 256 / 8);

                protected:
                    void transform(const unsigned char *message, unsigned int block_nb);
                    unsigned int m_tot_len;
                    unsigned int m_len;
                    unsigned char m_block[2*SHA224_256_BLOCK_SIZE];
                    uint32 m_h[8];
            };


            /*** AES ***/
        public:
            aes_ini(std::string key, std::string iv = ""){
                key = (this->md5(key)).substr(0, 16);
                _aes_key = key;
                if(iv == "") this->_aes_iv = this->_aes_key;
                else _aes_iv = (this->sha256(iv)).substr(0, 16);
            }

            std::string aes_decode(const string& strSrc);
            std::string aes_encode(string strSrc);

        private:
            std::string _aes_key;
            std::string _aes_iv;
            class AES {
                public:
                    enum{
                        ECB = 0, CBC = 1, CFB = 2
                    };

                private:
                    enum{
                        DEFAULT_BLOCK_SIZE = 16
                    };
                    enum{
                    MAX_BLOCK_SIZE = 32, MAX_ROUNDS = 14, MAX_KC = 8, MAX_BC = 8
                    };
                public:
                    AES();
                    virtual ~AES();
                private:
                    //Key Initialization Flag
                    bool m_bKeyInit;
                    //Encryption (m_Ke) round key
                    int m_Ke[MAX_ROUNDS + 1][MAX_BC];
                    //Decryption (m_Kd) round key
                    int m_Kd[MAX_ROUNDS + 1][MAX_BC];
                    //Key Length
                    int m_keylength;
                    //Block Size
                    int m_blockSize;
                    //Number of Rounds
                    int m_iROUNDS;
                    //Chain Block
                    char m_chain0[MAX_BLOCK_SIZE];
                    char m_chain[MAX_BLOCK_SIZE];
                    //Auxiliary private use buffers
                    int tk[MAX_KC];
                    int a[MAX_BC];
                    int t[MAX_BC];
                    private:
                    void Xor(char* buff, char const* chain);
                    void DefEncryptBlock(char const* in, char* result);
                    void DefDecryptBlock(char const* in, char* result);
                    void EncryptBlock(char const* in, char* result);
                    void DecryptBlock(char const* in, char* result);
                    public:
                    void MakeKey(char const* key, char const* chain, int keylength = DEFAULT_BLOCK_SIZE, int blockSize = DEFAULT_BLOCK_SIZE);
                    void Encrypt(char const* in, char* result, size_t n, int iMode = ECB);
                    void Decrypt(char const* in, char* result, size_t n, int iMode = ECB);
            };

    };

#ifdef _pthread

    class Timer {

        private:
            bool clear = false;

        public:
            void setTimeout(auto function, int delay);
            void setInterval(auto function, int interval);
            void stop();
    };

#endif


    /**
    * Data Storage
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class data{

        public:
            data(){};
            data(const data& d){
                this->_data = d._data;
            };
            ~data(){
                this->_data.erase(this->_data.begin(),this->_data.end());
            };
            /* insert data */
            template <typename T, typename Y>
            inline void insert(const T& key, const Y& val){
                if(this->isExist(key)) this->_data[this->toStr(key)] = this->toStr(val);
                else this->_data.insert(make_pair(this->toStr(key), this->toStr(val)));
            };

            /* overload [] */
            template <typename T>
            string& operator[](const T& i){
                return this->_data[this->toStr(i)];
            }
            /* overload [] */
            template <typename T>
            const string& operator[](const T& i) const{
                return this->_data[this->toStr(i)];
            };
            /* find begin */
            inline map<string, string>::iterator begin(){
                return _data.begin();
            }
            /* find end */
            inline map<string, string>::iterator end(){
                return _data.end();
            }
            /* find elements's address */
            template <typename T>
            inline map<string, string>::iterator find(const T& i){
                return _data.find(this->toStr(i));
            }
            /* clear all elements */
            inline void clear(){
                this->_data.erase(this->_data.begin(),this->_data.end());
            }
            /* clear elements */
            template <typename T>
            inline void clear(const T& key){
                if(isExist(key)){
                    map<string, string>::iterator t_iter = this->find(key);
                    this->_data.erase(t_iter);
                }
            }
            /* clear elements */
            template <typename T>
            inline void erase(const T& key){
                if(isExist(key)){
                    map<string, string>::iterator t_iter = this->find(key);
                    this->_data.erase(t_iter);
                }
            }
            /* iterator */
            map<string, string>::iterator iter;
            /* if key is exist */
            template <typename T>
            inline int isExist(T& key) const{
                return this->_data.count(this->toStr(key));
            }
            /* get size of data */
            inline int size() const{
                return _data.size();
            }

        private:
            map<string, string> _data;
            /* string to string */
            inline string toStr(const string& from) const{
                return from;
            }
            /* from T to string */
            template <typename T>
            string toStr(const T& from) const{

                stringstream ss;
                ss << setprecision(15) << from;
                string s;
                ss >> s;
                return s;
            }

    };

    /**
    * Database operation
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class db{

        public:
            db(){
                this->_path = "data\\";
                this->_AES = false;
            }
            /* construct with path and method */
            db(const string& s, const string method = ""){
                this->_path = s + "\\";
                if(method == "AES") this->_AES = true;
                else this->_AES = false;
            }
            /* push data to database */
            void pushData(data& data, const string& key);
            /* get data from database */
            data getData(const string& key);
            /* del data */
            void del(const string& key);

        private:
            ovo::math m;
            string _path;
            bool _AES;
            /* generate file name */
            inline string getFName(string key){
                return this->_path + m.md5(key + "_ovo_db") + ".ovo_db";
            }
            /* check folder */
            inline void checkFolder(){
                string cmd = "if not exist " + _path + " md " + _path;
                system(cmd.c_str());
            }
    };

}



/* Parameters of md5. */
#define s11 7
#define s12 12
#define s13 17
#define s14 22
#define s21 5
#define s22 9
#define s23 14
#define s24 20
#define s31 4
#define s32 11
#define s33 16
#define s34 23
#define s41 6
#define s42 10
#define s43 15
#define s44 21

/**
 * @Basic ovo::math::md5 functions.
 *
 * @param there bit32.
 *
 * @return one bit32.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/**
 * @Rotate Left.
 *
 * @param {num} the raw number.
 *
 * @param {n} rotate left n.
 *
 * @return the number after rotated left.
 */
#define ROTATELEFT(num, n) (((num) << (n)) | ((num) >> (32-(n))))

/**
 * @Transformations for rounds 1, 2, 3, and 4.
 */
#define FF(a, b, c, d, x, s, ac) { \
  (a) += F ((b), (c), (d)) + (x) + ac; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
  (a) += G ((b), (c), (d)) + (x) + ac; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
  (a) += H ((b), (c), (d)) + (x) + ac; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
  (a) += I ((b), (c), (d)) + (x) + ac; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}






/*** sha256 define ***/
#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
*((str) + 3) = (uint8) ((x)      );       \
*((str) + 2) = (uint8) ((x) >>  8);       \
*((str) + 1) = (uint8) ((x) >> 16);       \
*((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
*(x) =   ((uint32) *((str) + 3)      )    \
| ((uint32) *((str) + 2) <<  8)    \
| ((uint32) *((str) + 1) << 16)    \
| ((uint32) *((str) + 0) << 24);   \
}




#endif