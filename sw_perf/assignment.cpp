#include <iostream>
using namespace std;
int func1(int a);int func2(int a);int func3(int a);
int func1(int a) { int x = func2(1) + func3(2); return x; }
int func2(int a) { int x = func3(2) + a + 2; return x; }
int func3(int a) { return a + 3; }
int main ()
{       
    func1(1);
    func2(1);
     
    return 0;
 

}

