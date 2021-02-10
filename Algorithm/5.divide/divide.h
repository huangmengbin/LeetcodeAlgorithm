//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_DIVIDE_H
#define LEETCODE_DIVIDE_H
#include "../../Helper.h"


class Divide{
private:

    unordered_map<char,function<int(int,int)>> my_map = {
            {'+', [](int a, int b){return a+b;}},
            {'-', [](int a, int b){return a-b;}},
            {'*', [](int a, int b){return a*b;}},
    };

    vector<int> diffWaysToCompute(const string& input) {
        return {};
    }



    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    vector<TreeNode*> generateTrees(int n) {
        return {};
    }

public:
    test_diffWaysToCompute(){
        printVector(this->diffWaysToCompute(""));
    }
    test_generateTrees(){
        printVector(this->generateTrees(0));
    }
};
#endif //LEETCODE_DIVIDE_H
