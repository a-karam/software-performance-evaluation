// sw_perf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<vector>
#include <string>
#include <fstream>
#include "windows.h"
using namespace std;
ofstream output;
string func;
string SplitString(string s) {
    vector<string> v;
    string temp = "";
    for (int i = 0; i < s.length(); ++i) {

        if (s[i] == '(') {
            v.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(s[i]);
        }

    }
    v.push_back(temp);
    return v[0];
}

bool find_func (string str1)
{
    int c = 0, j = 0, i;
    string str2;
    str2 = "func";
    if (str2.length() < str1.length())
        for (i = 0; i < str1.length() - str2.length() + 1; i++)
        {
            if (str1[i] == str2[j])
            {
                c = 1;
                for (j = 1; j < str2.length(); j++)
                    if (str1[j + i] == str2[j])
                        c++;
                j = 0;
            }
            if (c == str2.length())
            {
                
                func = SplitString(str1);
                return true;
    
            }
        }
    else return 0;
    if (i == (str1.length() - str2.length() + 1))
        return false;
}
int main()
{   int count_func=0;
    //find_func("func");
    bool bracket = false;
    bool main_bracket = false;
    ifstream text("assignment.cpp");
    output.open("output.cpp", ios::out | ios::trunc);
    output << "#include <fstream>" << endl<< "#include <string>"<<endl<< "#include <vector>" << endl ;
    while (!text.eof())
    {
        
        string x;
        text >> x;
        if (x == "std;")
        {
            output << x<<endl;
            output << "vector<string> logCalls;" << endl;
            text >> x;
        }
        
        if ((x == "{") && (main_bracket))
        {
            output << x << " ofstream logF(\"log.txt\");";
        
            text >> x;
            //main_bracket = false;

        }
        if ((x == "return") && (main_bracket))
        {
            output << "for (string call: logCalls){logF << call << endl;} logF.close(); ";
            output << x <<" ";

            text >> x;
            //main_bracket = false;

        }
        if ((x == "using"))
        {
            output << endl;
            output << x << " ";
            text >> x;
        }
       if (bracket && (x == "{"))
        {
            output << x << " ";
             output << "logCalls.push_back( \""+func +" called \");";
            text >> x;
        }
       if (bracket && (x == "return"))
       {

           output << "logCalls.push_back( \"" + func + " returned \");";
           output << x << " ";
           text >> x;
           bracket = false;
       }
        if ((x == "int") || (x=="void"))
        {   
            output << x << " ";
            text >> x;
            if (find_func(x))
            {
                output << x << " ";
                count_func++;
                bracket = true;
               
            }
         
            else if ((x == "main"))
            {
                output << x << "() ";
                text >> x;
                main_bracket = true;
            }
            else output << x << " ";
        }else output << x << " ";
        
       
    }

    text.close();
    output.close();
    WinExec("g++ output.cpp -o output.exe", 1);
    cout << "output.exe generated" << endl;
        Sleep(5000);
 
        WinExec("output.exe", 1);
    cout << "running output.exe..." << endl;
    Sleep(5000);
        string functions[10];
        int f_count[10] = { 0 };
        int function_n = 0;
        bool found = false;

        std::ifstream log;

        log.open("log.txt");
        while (!log.eof())
        {
            found = false;

            string x;
            string y;

            log >> x;

            log >> y;

            if ((y == "called"))
            {

                for (int i = 0; i < 10; i++)
                {
                    if (functions[i] == x)
                    {
                        f_count[i]++;
                        found = true;

                    }

                }

                if (found == false)
                {
                    functions[function_n] = x;
                    f_count[function_n]++;
                    function_n++;

                }
            }

        }

        for (int i = 0; i < function_n; i++)
        {
            cout << functions[i] << " was called: " << f_count[i] << " times" << endl;

        }

        //////// max index
        int Max, temp;
        int i = 0;
        temp = i;
        Max = f_count[i];
        while (i < function_n)
        {
            if (Max < f_count[i])
            {
                Max = f_count[i];
                temp = i;
            }
            i++;
        }
        cout <<endl <<"most called function is " << functions[temp] << endl;

        return 0;
 

}

