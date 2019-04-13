## Class ovo::db

### 快速开始
 - 请查看如下示例代码
 ````C++
 #include <iostream>
 #include "ovo.h"
 
 int main()
 {
    ovo::db db;
    ovo::data data;
    
    data.insert("test", 666); //创建数据
    
    db.pushData(data, "indexName"); //右边的字符串是寻找这个数据块的唯一索引值，不同数据块索引值唯一，否则会导致数据丢失
    
    ovo::data newData = db.getData("indexName"); //用索引值提取数据块
    
    std::cout << newData["test"] << endl; //显示数据
    
    db.del("indexName"); //删除数据块
 
    return 0;
 }
 ````

