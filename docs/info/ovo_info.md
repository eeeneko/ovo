## Class info
### info.version
This is a `static` `string` variable with the version info. A simple demo like this:
````C++
ovo::info obj;
std::cout << obj.version << endl;
````
The screen should show like this: 
>Version 0.0.1

### info.hi()
This function can print a welcome info with a `void` return value. Demo like this:
````C++
ovo::info obj;
obj.hi();
````
Expected screen: 
>Hellow OvO~

### info.detail()
This function return with void, print detail info about this library. Use like this:
````C++
ovo::info obj;
obj.detail();
````
Expected screen: 
>Lib Name: ovo
>Org: EEENeko (https://github.com/eeeNeko)
>Author: Jianzhi Fan, Yimian Liu
>license GNU General Public License 2.0
>copyright Copyright (c) 2019 EEENeko


