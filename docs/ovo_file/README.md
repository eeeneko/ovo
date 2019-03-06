## Class ovo::file
### file.get_files_info() [windows only]
This function deals with the info of files. It has 4 params.
 - **string path** The path to search (Necessary)
 - **string format** The file format to search e.g. `*.png` (Default: '*')
 - **int isSearchSubfolders** Is the subfolders be searched. (Default: 0)

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
    f.get_files_info(".\\","*.md",1);//In Windows
    for(int i = 0; i < f.num(); i++){

        std::cout << "FileName: " << f.file[i].name << endl;
        std::cout << "FileName: " << f.file[i].path << endl;
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
>FileName: README.md<br/>
>Path: .\README.md<br/>
>Size: 28<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 16:35:26 2019<br/>
>Last Access Time: Sat Mar 02 16:35:26 2019<br/>
>Last Write Time: Sat Mar 02 16:35:26 2019<br/>
><br/>
>FileName: README.md<br/>
>Path: .\docs\ovo_file\README.md<br/>
>Size: 2578<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 23:50:44 2019<br/>
>Last Access Time: Tue Mar 05 11:40:18 2019<br/>
>Last Write Time: Tue Mar 05 11:40:18 2019<br/>
><br/>
>FileName: README.md<br/>
>Path: .\docs\ovo_info\README.md<br/>
>Size: 1211<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 17:55:06 2019<br/>
>Last Access Time: Tue Mar 05 11:40:18 2019<br/>
>Last Write Time: Tue Mar 05 11:40:18 2019<br/>
>
>FileName: README.md<br/>
>Path: .\docs\ovo_math\README.md<br/>
>Size: 2603<br/>
>Attribute: 32<br/>
>Create Time: Sun Mar 03 20:09:49 2019<br/>
>Last Access Time: Mon Mar 04 21:38:31 2019<br/>
>Last Write Time: Mon Mar 04 21:38:31 2019<br/>
>
>FileName: README.md<br/>
>Path: .\docs\ovo_string\README.md<br/>
>Size: 2067<br/>
>Attribute: 32<br/>
>Create Time: Sat Mar 02 18:14:52 2019<br/>
>Last Access Time: Mon Mar 04 19:12:56 2019<br/>
>Last Write Time: Mon Mar 04 19:12:56 2019<br/>
>
>FileName: README.md<br/>
>Path: .\docs\ovo_Timer\README.md<br/>
>Size: 2268<br/>
>Attribute: 32<br/>
>Create Time: Mon Mar 04 21:37:45 2019<br/>
>Last Access Time: Mon Mar 04 22:11:50 2019<br/>
>Last Write Time: Mon Mar 04 22:11:50 2019<br/>
--------------------


