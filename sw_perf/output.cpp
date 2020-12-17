#include <fstream>
#include <string>
#include <vector>
#include <iostream> 
using namespace std;
vector<string> logCalls;
int func1(int a);int func2(int a);int func3(int a); int func1(int a) { logCalls.push_back( "func1 called ");int x = func2(1) + func3(2); logCalls.push_back( "func1 returned ");return x; } int func2(int a) { logCalls.push_back( "func2 called ");int x = func3(2) + a + 2; logCalls.push_back( "func2 returned ");return x; } int func3(int a) { logCalls.push_back( "func3 called ");logCalls.push_back( "func3 returned ");return a + 3; } int main() { ofstream logF("log.txt");func1(1); func2(1); for (string call: logCalls){logF << call << endl;} logF.close(); return 0; }  