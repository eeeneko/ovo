## Class ovo::string

### void ovo::String::split(const std::string& s, std::vector<std::string>& v, const std::string& c)

Split the string.

### replaceStr
````C++
void replaceStr(string& str, const string fromStr = " ", const string toStr = "", int pos = 0, const int end = 99999)
````

This function can search for a specific string fromStr in a string str between an interval (default the entire string), and replace fromStr with another string toStr.

### params
1. **string str** The string need to be changed
2. **string fromStr** The string will be replaced by toStr (default space)
3. **string toStr** The string that will replace fromStr (default empty)
4. **int pos** The function will start searching for fromStr from position pos of str (default 0)
5. **int end** The function will finish searching for fromStr at position end of str (default 99999)

### example 1: Using default value
````C++
#include<iostream>
#include<string>

using namespace std;

void replaceStr(string& str, const string fromStr = " ", const string toStr = "", int pos = 0, const int end = 99999)
{
    while(pos > -1 && pos < end){

        pos = str.find(fromStr, pos);
        if(pos > -1 && pos < end){
            str.replace(pos++, fromStr.length(), toStr);
        }
    }
}


int main()
{
    string str1 = "aallaaa bbbbbbb cccccccc ddddddddd";

    replaceStr(str1);

    cout << str1 << endl;
}
````
The string print on the screen is
````C++
aallaaabbbbbbbccccccccddddddddd
````

### example 2: using setup value
````c++
#include<iostream>
#include<string>

using namespace std;

void replaceStr(string& str, const string fromStr = " ", const string toStr = "", int pos = 0, const int end = 99999)
{
    while(pos > -1 && pos < end){

        pos = str.find(fromStr, pos);
        if(pos > -1 && pos < end){
            str.replace(pos++, fromStr.length(), toStr);
        }
    }
}


int main()
{
    string str1 = "aallaaa bbbbbbb cccccccc ddddddddd";

    replaceStr(str1, "bbb", "22", 8, 9);

    cout << str1 << endl;
}
````
The string print on the screen is
````C++
aallaaa 22bbbb cccccccc ddddddddd
````
