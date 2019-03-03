
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
#include <string>
#include <vector>

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
            inline void hi(){cout << "Hello OvO~" << endl;};
            void detail();
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
            vector<string> name;
            vector<unsigned int> size;
            vector<time_t> time_create;
            vector<time_t> time_access;
            vector<time_t> time_write;
            vector<unsigned int> attrib;
            inline int num(){return name.size();}
            void get_files_info(const string path, const string format = "*", const int isSearchSubfolders = 0, const int isShowPath = 0);

        private:
            void get_all_files_info(string path, const string format = "*", const int isShowPath = 0);
            void get_all_folders_name(string path, vector<string>& folders);
    };
}


#endif