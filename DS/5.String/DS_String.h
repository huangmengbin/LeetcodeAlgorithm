//
// Created by 13524 on 2021/2/4.
//

#ifndef LEETCODE_DS_STRING_H
#define LEETCODE_DS_STRING_H
#include "../../Helper.h"
class DS_string{
private:
    int KMP(const string& longStr, const string& shortStr){
        const int LONG_SIZE = (int)longStr.size(), SHORT_SIZE = (int)shortStr.size();
        if(SHORT_SIZE == 0){
            return 0;
        }
        if(LONG_SIZE < SHORT_SIZE){
            return -1;
        }

        int *next = (int*)malloc((1 + SHORT_SIZE) * sizeof(int));
        // buggy  需要给末尾留个垃圾，防越界，因为弄了一个偏移量
        // buggy  括号，记得把 1+SIZE 括起来，否则那个1就傻了

        //    建立 next 数组
        next[0] = -1;
        for(int right = 0, left = -1; right < SHORT_SIZE;){
            if(left == -1 || shortStr.at(right) == shortStr.at(left)){
                next[++right] = ++left;
            } else{
                left = next[left];
            }
        }

        //    利用next数组, 开始KMP匹配
        int right = 0, left = 0;
        while (left < LONG_SIZE && right < SHORT_SIZE) {
            if(right == -1 || longStr.at(left) == shortStr.at(right) ){
                ++left;
                ++right;
            } else{
                right = next[right];
            }
        }

        free(next);
        if(right == SHORT_SIZE){
            return left - SHORT_SIZE;
        } else{
            return -1;
        }
    }


public:
    void test_KMP(){
        cout<<KMP("hello","ll");
    }
};
#endif //LEETCODE_DS_STRING_H
