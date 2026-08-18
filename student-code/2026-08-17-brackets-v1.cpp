#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Stack{
    string v;
    void push(char a){ v.push_back(a); }
    void pop(){ if(!v.empty()){ v.pop_back(); } }
    char top(){ if(!v.empty())return v.back(); return ' '; }
};
int main(){
    Stack s;
    string input;
    cin>>input;
    unsigned int size=input.size();
    for(unsigned int i=0;i<size;++i)
    {
        if(input[i]=='('||input[i]=='['||input[i]=='{'){ s.push(input[i]); }
        if(input[i]==')'){ if(s.top()=='(')s.pop(); else { cout<<"false"; return 0; } }
        if(input[i]==']'){ if(s.top()=='[')s.pop(); else { cout<<"false"; return 0; } }
        if(input[i]=='}'){ if(s.top()=='{')s.pop(); else { cout<<"false"; return 0; } }
    }
    if(s.top()==' ')cout<<"true";
    else { cout<<"false"; }
    return 0;
}
