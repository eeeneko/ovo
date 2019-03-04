## Class Timer

>To use this class, you need to put `#define _pthread` before your `#include "ovo.h"` <br/>
>And also, use `g++ yourCode.cpp -std=c++14 -pthread` to compile <br/>
---------
### Timer.setTimeout()
This can let your function be executed after certain time.
#### Params:
 - **auto function** Your function. `Lambda Expression is allowed!`
 - **int delay** Time to delay in milliseconds.

#### Example
````C++
#include <iostream>

#define _pthread

#include "ovo.h"

using namespace std;

void display(){
    cout << "Hey.. After 1s." << endl;
}

int main()
{
    ovo::Timer t = ovo::Timer();
    t.setsetTimeout(dis, 1000); 

    while (1); //Keep the main thread never stop
    return 0;
}
````
This will get the following result. (Use Ctrl+C to interrupt)
>Hey.. After 1s.
--------------
### Timer.setInterval()
This can let your function be executed repetitively with certain time.
#### Params:
 - **auto function** Your function. `Lambda Expression is allowed!`
 - **int delay** Time for every interval in milliseconds.

#### Example
````C++
#include <iostream>

#define _pthread

#include "ovo.h"

using namespace std;

void display(){
    cout << "Hey.. " << endl;
}

int main()
{
    ovo::Timer t = ovo::Timer();
    t.setsetInterval(dis, 1000); 

    while (1); //Keep the main thread never stop
    return 0;
}
````
This will get the following result. (Use Ctrl+C to interrupt)
>Hey..<br/>
>Hey.. <br/>
>Hey.. <br/>
> .<br/>
> .<br/>
> .<br/>
-------------------
### Timer.stop()
This can be used to stop a Timer.

#### Example
````C++
#include <iostream>

#define _pthread

#include "ovo.h"

using namespace std;

void display(){
    cout << "Hey.. " << endl;
}

int main()
{
    ovo::Timer t = ovo::Timer();
    t.setsetInterval(dis, 1000);

    t.setTimeout([&]() {
        cout << "Hey.. After 5.6s. I will stop the timer!" << endl;
        t.stop();
    }, 5600); 

    while (1); //Keep the main thread never stop
    return 0;
}
````
This will get the following result. (Use Ctrl+C to interrupt)
>Hey..<br/>
>Hey.. <br/>
>Hey.. <br/>
>Hey.. <br/>
>Hey.. <br/>
>Hey.. After 5.6s. I will stop the timer
-------------------

