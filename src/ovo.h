
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 2.0
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
            typedef struct FileInfo {
                string name; //File name
                unsigned int size; //File size
                time_t time_create; //File created time
                time_t time_access; //File last accessed time
                time_t time_write; //File last write time
                unsigned int attrib; //File attribute*/
            } FileInfo;
            vector<FileInfo> file;
            /* Get files numbers */
            inline int num(){return file.size();} 
            /* Get info of Files */
            void get_files_info(const string path, const string format = "*", const int isSearchSubfolders = 0, const int isShowPath = 0);

        private:
            /*** Files ***/
            void get_all_files_info(string path, const string format = "*", const int isShowPath = 0);
            void get_all_folders_name(string path, vector<string>& folders);
    };

    /**
    * Math operation
    *
    * @author yimian, Jiewei Wei(md5), Rene Nyffenegger(base64)
    * @category ovo
    * @package ovo
    */
    class math {

        public:
            /*** md5 ***/
            inline string md5 (const string message) const {
                MD5 m(message);
                return m.toStr();
            }

            /*** base64 ***/
            string base64_encode(const string fromStr);
            string base64_decode(string const& s);

            /*** sha256 ***/
            string sha256(string input);

            class MD5 {

                public:
                    /*** md5 ***/
                    /* Construct a md5 object with a string. */
                    MD5(const string& message);
                    /* Generate md5 digest. */
                    const byte* getDigest();
                    /* Convert digest to string value */
                    string toStr(const int length = 32);

                private:
                    /*** md5 ***/
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

        private:
            /*** base64 ***/
            static const string base64_chars;
            static inline bool is_base64(unsigned char c) {
                return (isalnum(c) || (c == '+') || (c == '/'));
            }

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