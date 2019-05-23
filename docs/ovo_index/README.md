## Class ovo::index

### 快速开始
 - 使用以下代码快速开始
 ````C++
 #include <iostream>
 #include <vector>
 #include "ovo.h"
 
 int main()
 {
    ovo::index i;
    
    i.push_back("22", "qwertyujk"); //插入一组数据，第一个为值，第二个为索引
    i.push_back("22", "23456789");
    i.push_back("33", "32wfr2wef23");
    
    vector<string> v = i.getIndex("22"); //根据值提前索引
    string s = i.getVal("32wfr2wef23"); //根据索引提值
    
    i.delByVal("33"); //根据值删除数据
    i.delByIndex("32wfr2wef23"); //根据索引删除数据
    
    i.size(); //获取大小
    

    return 0;
 }
 ````
