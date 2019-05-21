## Class ovo::data

### 快速开始
 - 使用以下代码快速开始
 ````C++
 #include <iostream>
 #include "ovo.h"
 
 int main()
 {
    ovo::data d;
    
    d["name"] = "Tomato"; //插入数据
    std::cout << d["name"] << endl; //输出数据
    
    return 0;
 }
 ````
以上代码将输出：
 > Tomato<br/>
 
 ### 进阶使用
 - 使用以下代码进阶
 ````C++
 #include <iostream>
 #include "ovo.h"
 
 int main()
 {
    ovo::data d;
    
    d["name"] = "Potato"; //插入数据，前面是键名，后面是键值
    d["kk"] = 97; //这种写法无法插入数字，这里实际上插入的是ASCII码'a'
                  //插入数字请使用insert()
                  
    d.insert("num", 97); //这样将插入数字
    d.insert("float", 3.1415926); //插入浮点数，最高支持15位有效数字
    std::cout << d["name"] << endl; //输出数据，无论你的输入格式如何，数据的输出格式将是string
                                    //如果你想使用其它类型请由string类型转换
    d.size(); //返回data的大小，即包含几个键值对，包括undefined内容
    d.isExist("name"); //查看某键名是否存在，存在返回true，否则为false
    d.classify(); //整理data，清除包含undefined内容
    //d.clear(); //清空所有data
    d.clear("name"); //删除"name"键值对
    
    //如果你想遍历元素，请使用内置迭代器，方法如下
    d.iter = d.begin();
    for(;d.iter != d.end(); d.iter++){
        std::cout << "Key: " << d.iter->first << "  val: " << d.iter->second << endl;
    }
    
    
    return 0;
 }
 ````
 以上代码将输出
 > Potato<br/>
 > Key: float  val: 3.1415926<br/>
 > Key: kk  val: a<br/>
 > Key: num  val: 97<br/>
