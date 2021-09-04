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

class DoublyListNode {
public:
    int key = 0;
    int val = 0;
    DoublyListNode *prev = nullptr;
    DoublyListNode *next = nullptr;
    explicit DoublyListNode() = default;
    explicit DoublyListNode(int x) : DoublyListNode() { this->val = x; }
    explicit DoublyListNode(int key, int val) : DoublyListNode(val) { this->key = key; }
    explicit DoublyListNode(int key, int val, DoublyListNode *prev, DoublyListNode *next) : DoublyListNode(key, val){ this->prev = prev; this->next = next;}
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


class UnionSet{
    int * nodes;
    int N;

    int find(int index) const {
        if(nodes[index] == index){
            return index;
        }
        return nodes[index] = find(nodes[index]);  // 路径压缩, 注意传参
    }

public:
    inline explicit UnionSet(const int N){
        nodes = new int [N];
        for(int i = 0; i<N; i++){
            nodes[i] = i;
        }
        this->N = N;
    }

    inline int size() const {
        return N;
    }

    inline bool isConnected(int a, int b){
        assert(0<a && a<N && 0<b && b<N);
        return find(a) == find(b);
    }

    inline void merge(int a, int b){
        assert(0<a && a<N && 0<b && b<N);
        nodes[find(a)] = find(b);
    }

    inline bool tryToMerge(int a, int b){
        assert(0<a && a<N && 0<b && b<N);
        int find_a = find(a), find_b = find(b);
        if(find_a == find_b){
            return false;
        } else{
            nodes[find_a] = find_b;
            return true;
        }
    }
};

#define LEETCODE_HELPER_H

#endif //LEETCODE_HELPER_H
