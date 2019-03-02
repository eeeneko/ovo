
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
            void get_files_name(const string path, vector<string>& files, const string format = "*", const int isSearchSubfolders = 0, const int isShowPath = 0);

        private:
            void get_all_files_name(string path, vector<string>& files, const string format = "*", const int isShowPath = 0);
            void get_all_folders_name(string path, vector<string>& folders);
    };
}


#endif