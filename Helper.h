//
// Created by 13524 on 2021/2/1.
//
#pragma once
#ifndef LEETCODE_HELPER_H

#define LL long long
#define uLL unsigned long long
#define elif else if

#include <bits/stdc++.h>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

inline void printListNode(ListNode* listNode){
    while(listNode){
        cout << listNode->val << " -> ";
        listNode = listNode->next;
    }
    cout<<"NULL\n";
}

template <typename T>
void printVector(vector<T> v, const string& m = ", ", const string& l = "{ ", const string& r = " }\n"){
    cout<<l;
    for(auto i = v.begin();i!=v.end();++i){
        if(i != v.begin()){
            cout<<m;
        }
        cout<<(*i);
    }
    cout<<r;
}

template <typename T>
void printVectorVector(vector<vector<T>> v, const string& m = ", ", const string& l = "{ ", const string& r = " }\n"){
    for(typename vector<vector<T>>::iterator i = v.begin();i!=v.end();++i){
        printVector((*i), m, l, r);
    }
    cout<<endl;
}

#define LEETCODE_HELPER_H

#endif //LEETCODE_HELPER_H
