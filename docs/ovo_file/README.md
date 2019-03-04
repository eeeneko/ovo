## Class ovo::file
### file.get_files_info() [windows only]
This function deals with the info of files. It has 4 params.
 - **string path** The path to search (Necessary)
 - **string format** The file format to search e.g. `*.png` (Default: '*')
 - **int isSearchSubfolders** Is the subfolders be searched. (Default: 0)
 - **int isShowPath** Is a path before the name. (Default: 0)

The most simple demo for this:
````C++
#include <iostream>
#include "ovo.h"

int main()
{
    ovo::file f;
    f.get_files_info(".\\");
    for(int i = 0; i < f.num(); i++)
        std::cout << "FileName: " << f.file[i].name << endl;
    return 0;
}
```` 
This will show all the files in current position. Such as:
>README.md<br/>
>LICENSE<br/>

You can also do like this:
````C++
#include <iostream>
#include <time.h>
#include "ovo.h"

int main()
{
    ovo::file f;
    f.get_files_info(".\\","*.md",1,1);//In Windows
    for(int i = 0; i < f.num(); i++){

        std::cout << "FileName: " << f.file[i].name << endl;
        std::cout << "Size: " << f.file[i].size << endl;
        std::cout << "Attribute: " << f.file[i].attrib << endl;
        std::cout << "Create Time: " << ctime(&f.file[i].time_create);
        std::cout << "Last Access Time: " << ctime(&f.file[i].time_access);
        std::cout << "Last Write Time: " << ctime(&f.file[i].time_write) << endl;
    }
    return 0;
}
````

This will show all the .md files with a path in current and all subfolders.
>.\README.md<br>
>.\docs\ovo_file\README.md<br/>
>.\docs\ovo_info\README.md<br/>
>.\docs\ovo_string\README.<br/>
><br/>
>FileName: .\README.md<br/>
>Size: 28<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 16:35:26 2019<br/>
>Last Access Time: Sat Mar 02 16:35:26 2019<br/>
>Last Write Time: Sat Mar 02 16:35:26 2019<br/>
><br/>
>FileName: .\docs\ovo_file\README.md<br/>
>Size: 1595<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 23:50:44 2019<br/>
>Last Access Time: Sun Mar 03 16:31:51 2019<br/>
>Last Write Time: Sun Mar 03 18:01:55 2019<br/>
><br/>
>FileName: .\docs\ovo_info\README.md<br/>
>Size: 763<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 17:55:06 2019<br/>
>Last Access Time: Sun Mar 03 16:31:51 2019<br/>
>Last Write Time: Sun Mar 03 16:31:51 2019<br/>
><br/>
>FileName: .\docs\ovo_string\README.md<br/>
>Size: 31<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 18:14:52 2019<br/>
>Last Access Time: Sat Mar 02 18:14:52 2019<br/>
>Last Write Time: Sat Mar 02 18:14:52 2019<br/>




