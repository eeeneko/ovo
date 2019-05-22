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
 运行以上代码将显示：
 > 666<br/>
 
 ### 进阶
 - 请查看以下代码
 ````C++
 #include <iostream>
 #include <vector>
 #include "ovo.h"
 
 int main()
 {
    ovo::db db("database\\my_data"); //自定义数据库文件夹
    ovo::db db_second("database\\my_second_data", "AES"); //指定数据加密方式为AES, 有一定几率解密失败，不建议
    
    ovo::data newData = db.getData("indexName"); //用索引值提取数据块
    if(newData["_isExist"] == "NO"){
        //数据块不存在！！
    }
    
    db.addData(newData, "indexName"); //追加数据
    
    std::vector<string> v;
    v[0] = "777";
    db.classify("indexName"); //整理数据块以提高效率
    db.classify("indexName", v); //整理时删除指定键名的键值对

    return 0;
 }
 ````
 
 ### 关系型数据库
 
  - 请查看以下代码
 ````C++
 #include <iostream>
 #include <vector>
 #include "ovo.h"
 
 int main()
 {
    ovo::db db("database\\my_data"); //自定义数据库文件夹
    
    ovo::data newData;
    std::vector<string> v;
    
    //配置各列名称
    v.push_back("name");
    v.push_back("id");
    
    db._createTable("TableName",  v); //用表名和列表名vector创建table
    //db._createTable("TableName",  v, vv); //你也可以传入第三个vector<string>指定索引，默认全部列为索引
    
    newData["id"] = "1515";
    newData["name"] = "iotcat";
    
    db.insertSQL("TableName", newData); //插入新数据
    
    ovo::data FilterData;
    
    FilterData["iotcat"] = "iotcat";
    
    std::cout << "Found " db.getNumSQL("TableName", FilterData) << " Items!!" << std::endl; //获取满足FilterData条件的数据条数
    
    vector<ovo::data> resData = db.getSQL("TableName", FilterData); //获取所有满足条件的数据块
    
    //显示所有接收到的数据
    for(auto i : resData){
        std::cout << i.showAll() << std::endl;
    }
    
    return 0;
 }
 ````
 

