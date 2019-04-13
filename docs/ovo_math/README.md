## Class ovo::math

### math.md5()
This function can generate a Hash md5 value from a string.
#### Params:
 - **string value** The content need to encode.
#### Return:
 - **string Hex md5 code** The generated Hex md5 code.
#### Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    std::string s = "a";
    ovo::math m;

    std::cout << m.md5(s) << std::endl;
    return 0;
}
````
This will get the following result.
>0cc175b9c0f1b6a831c399e269772661
#### Advanced
 - **math.toStr(int length)** You can use this to define the length of the generated code.
 - **math.getDigest()** Use this generate a binary md5 code.
#### Advanced Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    std::string s = "a";
    ovo::math::MD5 m(s);

    std::cout << m.toStr() << std::endl;
    std::cout << m.getDigest() << std::endl;
    return 0;
}
````
This will get the following result.
>0cc175b9c0f1b6a8<br/>
>♀羥估穸?脵鈏w&a
--------------
### math.sha256()
This function can generate a Hash sha256 value from a string.
#### Params:
 - **string value** The content need to encode.
#### Return:
 - **string Hex md5 code** The generated sha256 code.
#### Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    std::string s = "a";
    ovo::math m;

    std::cout << m.sha256(s) << std::endl;
    return 0;
}
````
This will get the following result.
>ed968e840d10d2d313a870bc131a4e2c311d7ad09bdf32b3418147221f51a6e2
----------------------
### math.base64_encode()
This function can encode a string to base64 format.
#### Params:
 - **string value** The content need to encode.
#### Return:
 - **string base64Code** The generated base64 code.
#### Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    std::string s = "aaaaa";

    ovo::math m;

    std::cout << m.base64_encode(s) << std::endl;
    return 0;
}
````
This will get the following result.
>YWFhYWE=
--------------
### math.base64_decode()
This function can decode a string from base64 format.
#### Params:
 - **string base64Code** The base64 content need to decode.
#### Return:
 - **string value** The original string.
#### Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    std::string s = "YWFhYWE=";

    ovo::math m;

    std::cout << m.base64_decode(s) << std::endl;
    return 0;
}
````
This will get the following result.
>aaaaa

--------------
### math.aes_ini()
在AES加密前使用本函数来设置密钥。
#### Params:
 - **string key** 加密解密密钥
 - **string iv** chain参数，可以留空
 
------------
### math.aes_encode()
AES加密，使用前请先调用math.aes_ini()设置密钥
#### Params:
 - **string strSrc** 待加密字符串
#### Return:
 - **string str** 加密后的字符串
--------------
### math.aes_decode()
AES解密，使用前请先调用math.aes_ini()设置密钥
#### Params:
 - **string strSrc** 待解密字符串
#### Return:
 - **string str** 解密后的字符串
#### Example
````C++
#include <iostream>
#include <string>
#include "ovo.h"
  
int main()
{
    ovo::math m;
    
    //初始化aes模块
    m.aes_ini("dq3tea09fyd98hds"); //这里填入的是密钥，可以是任意长度
    
    string str1 = "Such a cute world~";
    cout << "before: " << str1 << endl;
    //加密
    string str2 = m.aes_encode(str1);
    cout << "Encode: " << str2 << endl;
    //解密
    string str3 = m.aes_decode(str2);
    cout << "Decode: " << str3 << endl;
    
    return 0;
}
````
This will get the following result.
> before: Such a cute world~<br/>
> Encode: nyAu2sPOR91zny+2w4brwivyHYzDIJV0MDLxonSuztE=<br/>
> Decode: Such a cute world~<br/>

