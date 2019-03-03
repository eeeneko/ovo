#include <iostream>
#include <time.h>
#include "ovo.h"

int main()
{
    ovo::file f;
    f.get_files_info(".\\","*.md",1,1);//In Windows
    for(int i = 0; i < f.num(); i++){

        std::cout << "FileName: " << f.name[i] << endl;
        std::cout << "Size: " << f.size[i] << endl;
        std::cout << "Attribute: " << f.attrib[i] << endl;
        std::cout << "Create Time: " << ctime(&f.time_create[i]);
        std::cout << "Last Access Time: " << ctime(&f.time_access[i]);
        std::cout << "Last Write Time: " << ctime(&f.time_write[i]) << endl;
    }
    return 0;
}