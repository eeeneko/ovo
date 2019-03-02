
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 2.0
 * @version 0.0.1
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cstring>

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
void ovo::info::detail()
{
    cout << endl << "Lib Name: ovo" <<endl;
    cout << "Org: EEENeko (https://github.com/eeeNeko)" << endl;
    cout << "Author: Jianzhi Fan, Yimian Liu" << endl;
    cout << "license GNU General Public License 2.0" << endl;
    cout << "copyright Copyright (c) 2019 EEENeko" << endl << endl;
}




/****** Class file ******/

/**
 * Get All Files with certain format
 *
 * @Author yimian
 * @access private
 * @param string path filePath
 * @param vector<string>& files
 * @param string format  #such as "*.jpg"
 * @param int isShowPath  #If this is 1, the path would display before every filename
 * @return void
 */
void ovo::file::get_all_files_name(string path, vector<string>& files, const string format, const int isShowPath)
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
    //Deal with files
    if((hFile = _findfirst(p.assign(path).append(sign+format).c_str(),&fileInfo)) != -1){
        do
        {
            if(!(fileInfo.attrib & _A_SUBDIR)){
                if(isShowPath)
                    files.push_back(p.assign(path).append(sign).append(fileInfo.name));
                else
                    files.push_back(p.assign(fileInfo.name));
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
 * @param vector<string> files
 * @param string format  #such as "*.jpg"
 * @param int isSearchSubfolders  ##If this is 1, will search all the sub folders
 * @param int isShowPath  #If this is 1, the path would display before every filename
 * @return void
 */
void ovo::file::get_files_name(const string path, vector<string>& files, const string format, const int isSearchSubfolders, const int isShowPath)
{

#ifdef linux    
    const string sign = "/";
#else
    const string sign = "\\";
#endif

    get_all_files_name(path, files, format, isShowPath);

    //Search Sub Folders
    if(isSearchSubfolders){
        vector<string> foldersPath;
        get_all_folders_name(path, foldersPath);

        for(int i = 0; i < foldersPath.size(); i++){

            get_all_files_name(foldersPath[i], files, format, isShowPath);
        }
    }

}