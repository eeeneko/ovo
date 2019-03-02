
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
}


#endif