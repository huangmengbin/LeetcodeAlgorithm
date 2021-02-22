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


    /**
     * 求 01、0011、111000、00001111 之类型的子串数量
     * @param s
     * @return
     */
    int countBinarySubstrings(const string& s) {
        char historyChar = '\0';
        int currentLen = 0; //  buggy 这个不但必须初始化，而且必须初始为0. 主要是为了把0传递给 historyLen， 让它第一次为0
        int historyLen = 0;//   因此这个不需要初始化，第一次for必定是进入else的
        int result = 0;
        for(const char ch : s){
            if(ch==historyChar){
                currentLen ++;
            } else {
                result += min(historyLen, currentLen);
                historyChar = ch;
                historyLen = currentLen;
                currentLen = 1;
            }
        }
        result += min(historyLen, currentLen);  //  这个必须要有
        return result;
    }

    /**
     * 同构字符串，注意双向
     * @param s
     * @param t
     * @return
     */
    bool isIsomorphic(const string& s, const string& t) {
        // buggy 这个是双向的映射，比方说:"badc" 和 "baba"，会出错.   所以需要两个表
        char myMap1[256] = {0}, myMap2[256] = {0};
        const unsigned SIZE = s.length();
        for(unsigned i = 0; i<SIZE; i++){
            const char c1 = s.at(i), c2 = t.at(i);
            if(myMap1[c1] and myMap1[c1] != c2 or myMap2[c2] and myMap2[c2] != c1){
                return false;
            }
            myMap1[c1] = c2;
            myMap2[c2] = c1;
        }
        return true;
    }


    /**
     * 求: 所有的回文子串数目. 由于可重叠性，和求最大回文串长度差不多.
     * @param s
     * @return
     */
    int countSubstrings(const string& s) {
        if(s.empty())return 0;
        const int SIZE = (int)s.size()*2+1;
        //  buggy  在最左边、最右边， 应该也分别整一个辅助位，防止边界情况的混乱
        char *const ARRAY = new char [SIZE];
        int *const dp = new int[SIZE];

        for(int i = 0; i<SIZE; i++){
            if(i%2==1){
                ARRAY[i] = s.at(i/2);
            }
            else{
                ARRAY[i] = '*';
            }
            dp[i] = 1;
        }

        for(int center = 0; center < SIZE; center++){
            int offset;
            for(offset = dp[center] ; center-offset>=0 and center+offset<SIZE and ARRAY[center-offset]==ARRAY[center+offset]; offset++){
                ++ dp[center];
            }
            /// 以下为优化
            --offset;   // 抵消最后一次
            for(; offset>0 ; offset--){
                dp[center+offset] = max( dp[center+offset],    min(dp[center-offset],  dp[center] - offset )  );
            }
            ///
        }

        int result = 0;
        for(int i = 0; i<SIZE; i++){
            result += dp[i] / 2;
        }
        return result;
    }
public:
    void test_KMP(){
        cout<<KMP("hello","ll");
    }

    void test_countSubstrings(){
        countSubstrings("121");
    }
};
#endif //LEETCODE_DS_STRING_H
