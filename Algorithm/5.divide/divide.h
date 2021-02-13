//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_DIVIDE_H
#define LEETCODE_DIVIDE_H
#include "../../Helper.h"

class Divide{
private:

    unordered_map<int,int> diffWaysToCompute(const string& input, const int LEFT_PTR, const int RIGHT_PTR, const unordered_map<char,function<int(int, int)>>& my_map, unordered_map<long long, unordered_map<int,int>>& cache){
        long long cache_key = 2147483647*(long long)LEFT_PTR + RIGHT_PTR;
        //  利用一个字典，存储已经运算过的内容，避免重复计算。但是，dp会更快
        if(cache.count(cache_key)){
            return cache.at(cache_key);
        }
        unordered_map<int,int> result;
        bool isNumber = true;
        for(int i = LEFT_PTR; i <= RIGHT_PTR; i++){
            const char c = input.at(i);
            if(my_map.count(c)){
                isNumber = false;
                unordered_map<int,int> left = diffWaysToCompute(input, LEFT_PTR, i-1, my_map, cache);
                unordered_map<int,int> right= diffWaysToCompute(input, i+1, RIGHT_PTR, my_map, cache);
                for(pair<int,int> pii1: left){
                    for(pair<int,int> pii2: right){
                        int key = my_map.at(c)(pii1.first, pii2.first);
                        int value = pii1.second * pii2.second;
                        result[key] += value;
                    }
                }
            }
        }
        if(isNumber){
            string sub_string = input.substr(LEFT_PTR, RIGHT_PTR - LEFT_PTR + 1);
            result[stoi(sub_string)] = 1;
        }
        cache[cache_key] = result;
        return result;
    }
    vector<int> diffWaysToCompute(const string& input) {
        unordered_map<char,function<int(int,int)>> my_map = {
                {'+', [](int a, int b){return a+b;}},
                {'-', [](int a, int b){return a-b;}},
                {'*', [](int a, int b){return a*b;}},
        };
        unordered_map<long long, unordered_map<int,int>> cache;
        unordered_map<int,int> result_map = diffWaysToCompute(input, 0, (int)input.length()-1, my_map, cache);
        vector<int> result_vector;
        for(auto pii: result_map){
            for(int i = 0; i<pii.second; i++){
                result_vector.push_back(pii.first);
            }
        }
        return result_vector;
    }



    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    vector<TreeNode*> generateTreesRecursively(const int LOW, const int HIGH){
        vector<TreeNode*> result;
        for(int i=LOW;i<=HIGH;++i){
            auto  leftTrees = (i == LOW) ? vector<TreeNode*>{nullptr} : generateTreesRecursively(LOW, i - 1);
            auto rightTrees = (i == HIGH) ? vector<TreeNode*>{nullptr} : generateTreesRecursively(i + 1, HIGH);
            for(auto leftTree: leftTrees){
                for(auto rightTree: rightTrees){
                    result.push_back(new TreeNode(i, leftTree, rightTree));
                }
            }
        }
        return result;
    }
    vector<TreeNode*> generateTreesRecursively(int n) {
        if(n==0)  return {};
        return generateTreesRecursively(1, n);
    }

    class TreeNodes{    // 可有可无的一个类
        vector<TreeNode*>* treesInitialPtr;
        int N;
        vector<TreeNode*> empty = vector<TreeNode*>{nullptr};
    public:
        inline explicit TreeNodes(int N){
            this->N = N;
            treesInitialPtr = new vector<TreeNode*>[N * N];
        }
        inline vector<TreeNode*>* getVector(int row, int column){
            if(row>column){
                return &empty;
            }
            return (treesInitialPtr + row * N + column);
        }
    };
    vector<TreeNode*> generateTreesDP(const int N) {      //DP，使用动态规划改造，自底向上，提高效率(时间、空间)
        TreeNodes treeNodes(N);
        for(int i = 0; i < N; i++){//差值
            for(int row = 0, endRow = N - i; row < endRow; row++){//行号
                //row; row+i;//斜线遍历
                const int column = row + i;
                vector<TreeNode*>* const treePtr = treeNodes.getVector(row, column);
                for(int middle = row; middle <= column; middle++){
                    //row,middle-1 ; middle+1,row+i; 记得一个是k-1，一个是k+1
                    const auto * const leftVector = treeNodes.getVector(row, middle - 1);
                    const auto * const rightVector = treeNodes.getVector(middle + 1, column);
                    for(TreeNode* const left : *leftVector){
                        for(TreeNode* const right : *rightVector){
                            treePtr->push_back(new TreeNode(middle+1, left, right));
                        }
                    }
                }
            }
        }
        return *treeNodes.getVector(0, N-1);
    }

public:
    void test_diffWaysToCompute(){
        printVector(this->diffWaysToCompute("2*3-4*5"));
    }
    void test_generateTrees(){
        printVector(this->generateTreesDP(3));
    }
};

#endif //LEETCODE_DIVIDE_H
