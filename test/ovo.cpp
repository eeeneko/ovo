
/**
 * ovo Main File
 *
 * @category ovo
 * @package ovo.cpp
 * @copyright Copyright (c) 2019 EEENeko (https://github.com/eeeneko)
 * @license GNU General Public License 2.0
 * @version 0.0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
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

