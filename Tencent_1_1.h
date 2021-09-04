//
// Created by 13524 on 2021/3/11.
//

#ifndef LEETCODE_TENCENT_1_1_H
#define LEETCODE_TENCENT_1_1_H



#include <bits/stdc++.h>
using namespace std;


class Tencent_1_1_Solution{
private:


    int func(char c, int numa, int numb){
        switch(c){
            case '+':
                return numa + numb;
            case '-':
                return numa - numb;
            case '*':
                return numa * numb;
            case '/':
                return numa / numb;
        }
        return 0;
    }

    int t1(){
        string s = "123 +1-6*5/4";
        s.push_back('#');        // # 是终止符
        stack<char> myStack;    //
        stack<int> intStack;    //
        map<char,int> myMap = {{'+',1},{'-',1},{'*',2},{'/',2},  {'#',INT_MIN} };
        for(auto it = s.begin(); it != s.end() ; ){
            const char c = (*it);
            if(c == ' '){
                ++it;
            }
            else if( myMap.count(c) ){// 符号
                if(myStack.empty() || myMap[myStack.top()] < myMap[c]){
                    //  为空入栈；  当前比栈顶 优先级高、压入当前符号
                    myStack.push(c);
                    ++it;
                }
                else{    // 当前比栈顶 优先级更低，取之前的运算
                    const char calculate = myStack.top();
                    myStack.pop();
                    int numb = intStack.top();
                    intStack.pop();
                    int numa = intStack.top();
                    intStack.pop();
                    int numberC = func(calculate, numa, numb);
                    intStack.push(numberC);
                }
            }
            else {    // c 是数字型
                int number = 0;
                for( ; ! myMap.count(*it) and (*it) != ' ' ; ++it ){    // 移动it直到为运算符或为空格，反正不是数字就行了
                    number = number*10 + (*it) - '0' ;
                }
                intStack.push(number);
            }
        }
        cout<<intStack.top()<<endl;
    }


    const int WHITE = 0;
    const int BLACK = 1;


    int t2(){
        vector<int> cats {0,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,1,0};
        const int SIZE = cats.size();
        for(int i = 0, j = 0; i < SIZE and j < SIZE; ++i){
            if(cats[i] == BLACK){
                if(j == 0) j = i + 1;
                for ( ; j < SIZE and cats[j] == BLACK ; ++j) ;
                if(j < SIZE)swap( cats[i], cats[j] );
            }
        }
        printVector(cats);
    }



public:
    inline void test(){
        //t1();
        t2();
    }
};


#endif //LEETCODE_TENCENT_1_1_H
