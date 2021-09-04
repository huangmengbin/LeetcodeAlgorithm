//
// Created by 13524 on 2021/5/9.
//

#ifndef LEETCODE_SHARED_H
#define LEETCODE_SHARED_H
#include "bits/stdc++.h"
using namespace std;

class MyString{
public:
    explicit MyString(){
        cout<<"myString"<<endl;
    }
    explicit MyString(int i){
        cout<<"myString "<<i<<endl;
    }
    explicit MyString(const string& s){
        cout<<"myString " << s << endl;
    }
    virtual ~MyString(){
        cout<<"del myString"<<endl;
    }
};

class Father{
public:
    MyString string1;
    explicit Father(): string1(){
        cout<<"father"<<endl;
    }
    explicit Father(int i): string1(i){
        cout<<"father"<<i<<endl;
    }
    explicit Father(const string& i):string1(i){
        cout<<"father"<<i<<endl;
    }
    virtual ~Father(){
        cout<<"del father"<<endl;
    }
};

class Son: public Father{
public:
    MyString string2;
    explicit Son(): Father(), string2(){
        cout<<"son"<<endl;
    }
    explicit Son(int i): Father(i), string2(i){
        cout<<"son"<<i<<endl;
    }

    explicit Son(const string& i): Father(i), string2(i){
        cout<<"son"<<i<<endl;
    }
    ~Son() override{
        cout<<"del son"<<endl;
    }
};

#endif //LEETCODE_SHARED_H
