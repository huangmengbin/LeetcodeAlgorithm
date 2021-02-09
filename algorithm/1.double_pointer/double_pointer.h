//
// Created by 13524 on 2021/1/27.
//

#ifndef LEETCODE_TWOSUM_167_H
#define LEETCODE_TWOSUM_167_H

#include "../../Helper.h"

class Double_pointer {
    vector<int> twoSum(vector<int> numbers, int target) {
        for(int i=0,j=(int)numbers.size()-1;;){          // buggy 注意要减一，别越界了
            int s = numbers[i] + numbers[j];
            if(s<target){
                i++;
            } elif(s>target){
                j--;
            } else{
                return vector<int> {i+1,j+1};
            }
        }
    }

    bool judgeSquareSum(int c) {
        const LL sqrt_c = (int)sqrt(c);
        for(LL i = 0, j = sqrt_c;i<=j;) {
            const LL  tmp = i*i + j*j;           // buggy 注意 long long 范围
            if(tmp < c){
                i++;
            }
            else if(tmp > c){
                j--;
            }
            else{
                return true;
            }
        }
        return false;
    }

    string reverseVowels(string s) {
        if(s.size()<=1){
            return s;                           // buggy 小心空串 减一后负数越界
        }
        unordered_set <char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        for(unsigned i = 0, j = s.size()-1; i<j; ){
            if(!vowels.count(s[i])){
                i ++;
            }
            elif(!vowels.count(s[j])){
                j --;
            }
            else{
                swap(s[i], s[j]);
                i ++; j--;                      // buggy 小心无限循环
            }
        }
        return s;
    }

    bool validPalindrome(string s) {
        if(s.size()<=2){
            return true;
        }

        unsigned ii, jj;

        for(unsigned i = 0, j = s.size()-1; ; i++, j-- ){
            if(i>=j){
                return true;
            }
            if(s.at(i) != s.at(j)){
                ii = i;
                jj = j;
                break;
            }
        }

        for(unsigned i = ii+1, j = jj; ; i++, j--){
            if(i>=j){
                return true;
            }
            if(s.at(i) != s.at(j)){
                break;
            }
        }

        for(unsigned i = ii, j = jj-1; ; i++, j--){
            if(i>=j){
                return true;
            }
            if(s.at(i) != s.at(j)){
                break;
            }
        }

        return false;
    }

    string findLongestWord(const string& longString, const vector<string>& vec) {
        string result;
        for(const string& shortString : vec){
            if(shortString.size() > result.size() || (shortString.size()==result.size() && shortString.compare(result)<0)){
                {
                    unsigned s_ptr = 0;
                    for(unsigned l_ptr = 0; l_ptr < longString.size() && s_ptr < shortString.size() ; l_ptr++){
                        // buggy  不应该在for里面特判s抵达了字符串的末端
                        if(shortString.at(s_ptr) == longString.at(l_ptr)){
                            s_ptr++;
                        }
                    }
                    if(s_ptr == shortString.size()){    // fix 应该推迟至这里判断
                        result = shortString;
                    }
                }
            }
        }
        return result;
    }

public:

    void test_twoSum(){
        printVector(this->twoSum(vector<int>{1,2,3,5,6,7},10));
    }

    void test_judgeSquareSum(){
        cout<<judgeSquareSum(3);
    }

    void test_reverseVowels(){
        cout<<reverseVowels("leetcode");
    }
    void test_validPalindrome(){
        cout<<validPalindrome("acmmcca");
    }
    void test_findLongestWord(){
        cout<<findLongestWord("abpcplea", {"ale","apple","monkey","plea","abpcplea"});
    }
};


#endif //LEETCODE_TWOSUM_167_H
