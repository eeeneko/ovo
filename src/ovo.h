
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 3.0
 * @version 0.0.2
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
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>

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
    * string tools
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class String{

        public:
            void split(const std::string& s, std::vector<std::string>& v, const std::string& c);
    };

    /**
    * Math operation
    *
    * @author yimian, Jiewei Wei(md5), Rene Nyffenegger(base64), Louis Nam(sha256)
    * @category ovo
    * @package ovo
    */
    class math {

        public:
            math(){
                srand(time(NULL));
            }

            /* rand */
        public:
            unsigned long randNum;
            inline int rand(const int& a, const int& b){
                return (time(NULL) + (randNum++) * std::rand()) % std::abs(b - a + 1) + a;
            }

            inline string randStr(const unsigned int length = 0){
                if(!length){
                    return md5(to_string(time(NULL)) +  to_string(this->randNum++));
                }
                return (sha256(to_string(time(NULL)) +  to_string(this->randNum++))).substr(0, length);
            }

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
            void aes_ini(std::string key, std::string iv = ""){
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
            friend class db;
            data(const data& d){
                this->_data = d._data;
            };
            ~data(){
                this->_data.erase(this->_data.begin(),this->_data.end());
            };
            /* insert data */
            template <typename T, typename Y>
            inline void insert(const T& key, const Y& val){
                this->isExist(key);
                this->_data[this->toStr(key)] = this->toStr(val);
            };

            /* attach data */
            template <typename T>
            inline void attachData(const T& key, ovo::data data){
                this->isExist(key);
                this->_data[this->toStr(key)] = this->dataToStr(data);
            };

           /* attach data */
            template <typename T>
            inline void attachData(const T& key, string s){
                this->isExist(key);
                this->_data[this->toStr(key)] = s;
            };

            /* overload [] */
            template <typename T>
            string& operator[](const T& i){
                isExist(i);
                return this->_data[this->toStr(i)];
            }
            /* overload [] */
            template <typename T>
            const string& operator[](const T& i) const{
                isExist(i);
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
                if(this->_data.count(this->toStr(key))){
                    map<string, string>::iterator t_iter = this->find(this->toStr(key));
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
            inline bool isExist(T& key){

                if(this->_data.count(this->toStr(key)) && this->_data[this->toStr(key)] != "undefined"){
                    return true;
                }
                this->_data[this->toStr(key)] = "undefined";
                return false;
            }
            /* classify elements */
            void classify(){
                map<string, string>::iterator t_iter = this->_data.begin();
                while(t_iter != this->_data.end()){
                    if(t_iter->second == "undefined"){
                        this->_data.erase(t_iter++);
                    }else{
                        t_iter++;
                    }
                }
            }

            /* data to string */
            string dataToStr(ovo::data& d){

                string s = "__OVO_DATA__";
                d.classify();
                d.forEach([&](string first, string second){
                    s += first + "$$||$$" + second + "$$||$$";
                });

                return s;
            };

            /* string to data */
            ovo::data strToData(string s){

                ovo::data d;

                if(s.length() <= 12 || s.substr(0, 12) != "__OVO_DATA__") return d;

                s = s.substr(12);

                std::vector<string> v;
                S.split(s, v, "$$||$$");

                for(int i = 0; i < v.size() - 1; i += 2){

                    d[v[i]] = v[i + 1];
                }

                return d;

            };

            /* for each */
            void forEach(const std::function<void(string, string)>& f){
                map<string, string>::iterator t_iter = this->_data.begin();
                while(t_iter != this->_data.end()){
                    f(t_iter->first, t_iter->second);
                    t_iter++;
                }
            };

           /* display all elements */
            string showAll(){
                this->classify();
                string s = "{";
                map<string, string>::iterator t_iter = this->_data.begin();
                while(t_iter != this->_data.end()){

                    s += "\n  \"" + t_iter->first + "\": \"" + t_iter->second + "\",";
                    t_iter++;
                    
                }
                s += "\n}";
                return s;
            }
            /* get size of data */
            inline int size() const{
                return _data.size();
            }

            map<string, string> _data;
        private:
            
            ovo::String S;
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
    * Index Storage
    *
    * @author yimian
    * @category ovo
    * @package ovo
    */
    class index{

        public:
            index(){};
            friend class db;
            index(const index& i){
                this->_val = i._val;
                this->_index = i._index;
            };
            ~index(){
                this->_val.erase(this->_val.begin(),this->_val.end());
                this->_index.erase(this->_index.begin(),this->_index.end());
            };

            void push_back(const string& val, const string& index){

                this->_val.push_back(val);
                this->_index.push_back(index);
            };

            std::vector<string> getIndex(const string& val){

                std::vector<string> v;
                std::vector<unsigned int> pos = this->_getPosition(this->_val, val);

                for(unsigned int i : pos){
                    v.push_back(this->_index[i]);
                }
                return v;
            };

           string getVal(const string& index){

                std::vector<unsigned int> pos = this->_getPosition(this->_index, index);

                if(pos.size()) return this->_val[pos[0]];
                return string();
            };

            void delByIndex(const string& index){

                std::vector<unsigned int> pos = this->_getPosition(this->_index, index);

                sort(pos.begin(), pos.end(), [&](const unsigned int& a, const unsigned int& b)->bool{
                    return (a > b);
                });

                for(unsigned int i : pos){
                    this->_index.erase(this->_index.begin() + i);
                    this->_val.erase(this->_val.begin() + i);
                }
            };

            void delByVal(const string& val){

                std::vector<unsigned int> pos = this->_getPosition(this->_val, val);

                sort(pos.begin(), pos.end(), [&](const unsigned int& a, const unsigned int& b)->bool{
                    return (a > b);
                });

                for(unsigned int i : pos){
                    this->_index.erase(this->_index.begin() + i);
                    this->_val.erase(this->_val.begin() + i);
                }
            };

            int size(){
                return this->_index.size();
            }

        private:
            std::vector<string> _val, _index;

            std::vector<unsigned int> _getPosition(std::vector<string>& v, const string& s){

                std::vector<unsigned int> o;
                vector <string>::iterator it = find(v.begin(), v.end(), s);
                while(it != v.end()){

                    o.push_back(distance(v.begin(), it));
                    it = find(++it, v.end(), s);
                }
                
                return o;
            };

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

            /* no-sql */

            /* push data to database */
            void pushData(const string& key, data& data);
            inline void pushData(data& data, const string& key){
                pushData(key, data);
            };
            /* add data to database */
            void addData(const string& key, data& data);
            inline void addData(data& data, const string& key){
                pushData(key, data);
            };
            /* get data from database */
            data getData(const string& key);
            /* get data from database */
            void getData(const string& key, std::vector<string>& v1, std::vector<string>& v2);
            /* classify data in db */
            inline void classify(const string& key){
                std::vector<string> v;
                this->classify(key, v);
            };
            /* classify data in db */
            void classify(const string& key, std::vector<string> v);
            /* del data */
            void del(const string& key);

            /* sql */
            void createTable(const string& tableName, std::vector<string> v){
                std::vector<string> index;
                this->createTable(tableName, v, index);
            };
            void createTable(const string& tableName, std::vector<string> v, std::vector<string> index){
                ovo::data d;
                string keysName = "";
                string indexNames = "";
                for(int i = 0; i < v.size(); i ++){
                    d[v[i]] = this->generateIndex(v[i]);
                    keysName += v[i] + "||$$||";
                }

                if(index.size()){
                    for(int i = 0; i < index.size(); i ++){
                        d[this->getIndexName(index[i])] = this->generateIndex(this->getIndexName(index[i]));
                        indexNames += this->getIndexName(index[i]) + "||$$||";
                    }
                }else{
                    for(int i = 0; i < v.size(); i ++){
                        d[this->getIndexName(v[i])] = this->generateIndex(this->getIndexName(v[i]));
                        indexNames += this->getIndexName(v[i]) + "||$$||";
                    }

                }

                d["__OVO_KEYS__"] = keysName;
                d["__OVO_INDEX__"] = indexNames;
                d["__OVO_LIST__"] = generateIndex();
                d["__OVO_DEL_LIST__"] = generateIndex();
                this->pushData(generateTableName(tableName), d);
            };

            void insertSQL(const string& tableName, ovo::data d){
                ovo::data temp;

                temp = this->_getTableKeys(tableName, true);

                temp.forEach([&](string first, string second){
                    if(d._data.count(first)){
                        temp[first] = d[first];
                    }
                });

                string id = this->generateIndex();

                this->pushData(id, temp);

                temp.clear();

                temp[id] = to_string(time(NULL));

                this->addData(this->_getTableList(tableName), temp);

                ovo::data index = this->_getTableIndex(tableName);

                for(auto i : index._data){

                    temp.clear();
                    if(d[i.first.substr(15)] != "undefined")
                    temp[d[i.first.substr(15)]] = id;
                    this->addData(i.second, temp);
                }

            };

            std::vector<ovo::data> getSQL(const string& tableName, const string& index, const string& val){

                ovo::data indexList;
                std::vector<string> v;
                std::vector<ovo::data> o;

                indexList = this->_getTableIndex(tableName);
                if(indexList["_isExist"] == "NO"){
                    return o;
                }
                if(indexList["__TABLE_INDEX__" + index] == "undefined"){
                    return o;
                }

                v = this->_getItemAddress(indexList, index, val);

                for(string i : v){
                    o.push_back(this->getData(i));
                }

                return o;

            };

            std::vector<ovo::data> getSQL(const string& tableName, ovo::data& d){

                ovo::data indexList;
                std::vector<std::vector<string>> v;
                std::vector<ovo::data> o;

                d.classify();
                if(!d.size()) return this->getSQL(tableName);

                indexList = this->_getTableIndex(tableName);
                if(indexList["_isExist"] == "NO"){
                    return o;
                }

                d.forEach([&](string index, string val){

                    v.push_back(this->_getItemAddress(indexList, index, val));
                });

                for(string i : this->_getInterSection(v)){
                    o.push_back(this->getData(i));
                }

                return o;
            };
            std::vector<ovo::data> getSQL(const string& tableName){

                ovo::data indexList;
                std::vector<ovo::data> o;

                indexList = this->getData(this->_getTableList(tableName));
                if(indexList["_isExist"] == "NO"){
                    return o;
                }


                for(auto i : indexList){
                    o.push_back(this->getData(i.first));
                }

                return o;
            };

            unsigned int getNumSQL(const string& tableName, const string& index, const string& val){

                ovo::data indexList;
                std::vector<string> v;

                indexList = this->_getTableIndex(tableName);
                if(indexList["_isExist"] == "NO"){
                    return 0;
                }
                if(indexList["__TABLE_INDEX__" + index] == "undefined"){
                    return 0;
                }

                v = this->_getItemAddress(indexList, index, val);

                return v.size();

            };

            unsigned int getNumSQL(const string& tableName, ovo::data& d){

                ovo::data indexList;
                std::vector<std::vector<string>> v;

                indexList = this->_getTableIndex(tableName);


                d.forEach([&](string index, string val){

                    v.push_back(this->_getItemAddress(indexList, index, val));
                });

                return this->_getInterSection(v).size();
            };
            unsigned int getNumSQL(const string& tableName){

                ovo::data indexList;

                indexList = this->getData(this->_getTableList(tableName));

                return indexList.size();
            };


            std::vector<string> _getInterSection(std::vector<std::vector<string>> v){

                std::vector<string> vv;


                if(v.size() == 1){
                    return v[0];
                }

                for(int i = 0; i < v[0].size(); i ++){

                    int cnt = 0;

                    for(int ii = 0; ii < v.size(); ii ++){

                        if(find(v[ii].begin(), v[ii].end(), v[0][i]) != v[ii].end()){

                            cnt ++;
                        }
                    }

                    if(cnt == v.size()){
                        vv.push_back(v[0][i]);
                    }
                }

                return vv;


            }

            std::vector<string> _getItemAddress(ovo::data& indexList, const string& index, const string& val){

                std::vector<string> v1, v2, v3;

                if(indexList["__TABLE_INDEX__" + index] == "undefined"){
                    return v3;
                }

                this->getData(indexList["__TABLE_INDEX__" + index], v1, v2);

                for(int i = 0; i < v1.size(); i ++){

                    if(v1[i] == val){
                        v3.push_back(v2[i]);
                    }
                }

                return v3;
            }

            void _getAll(ovo::data& indexList, std::vector<string>& v2){

                std::vector<string> v1;

                if(indexList["__TABLE_INDEX__"] == "undefined"){
                    return ;
                }

                this->getData(indexList["__OVO_LIST__"], v1, v2);

                return ;
            }

            ovo::data _getTableKeys(const string& tableName, const bool isNULL = false){
                ovo::data d, o;

                d = this->getData(generateTableName(tableName));
                std::vector<string> v;

                S.split(d["__OVO_KEYS__"], v, "||$$||");

                for(int i = 0; i < v.size(); i ++){
                    if(isNULL){
                        o[v[i]];
                    }else{
                         o[v[i]] = d[v[i]];                  
                    }
                }

                return o;
            };


            ovo::data _getTableIndex(const string& tableName){
                ovo::data d, o;

                d = this->getData(generateTableName(tableName));

                if(d["_isExist"] == "NO") return d;

                std::vector<string> v;

                S.split(d["__OVO_INDEX__"], v, "||$$||");

                for(int i = 0; i < v.size(); i ++){
                    o[v[i]] = d[v[i]];
                }

                return o;
            };

            string _getTableList(const string& tableName){
                ovo::data d;

                d = this->getData(generateTableName(tableName));

                return d["__OVO_LIST__"];
            };

            void _delTable(const string& tableName){
                this->del(generateTableName(tableName));
            };



        private:
            ovo::math m;
            ovo::String S;
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

            inline string generateTableName(const string& tableName){
                return "__OVO_DB_TABLE__" + tableName;
            }

            inline string getIndexName(const string& index){
                return "__TABLE_INDEX__" + index;
            }

            inline string generateIndex(const string& salt = ""){
                return m.sha256(m.randStr() + salt);
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