## Class ovo::file
### file.get_files_name()
This function deals with the name of files. It has 5 params.
 - **string path** The path to search (Necessary)
 - **vector<string>& files** Vector to store the file names.(Necessary)
 - **string format** The file format to search e.g. `*.png` (Default: '*')
 - **int isSearchSubfolders** Is the subfolders be searched. (Default: 0)
 - **int isShowPath** Is a path before the name. (Default: 0)

The most simple demo for this:
````C++
ovo::file f;
vector<string> fls;
f.get_files_name(".\\",fls);//In Windows
for(int i = 0; i < fls.size(); i++)
std::cout << fls[i] << endl;
```` 
This will show all the files in current position. Such as:
>README.md
>LICENSE

You can also do like this:
````C++
ovo::file f;
vector<string> fls;
f.get_files_name(".\\",fls,"*.md",1,1);//In Windows
for(int i = 0; i < fls.size(); i++)
std::cout << fls[i] << endl;
````

This will show all the .md files with a path in current and all subfolders.
>.\README.md
>.\docs\ovo_file\README.md
>.\docs\ovo_info\README.md
>.\docs\ovo_string\README.



