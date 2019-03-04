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
