//
// Created by 13524 on 2021/2/21.
//

#ifndef LEETCODE_HASHTABLE_H
#define LEETCODE_HASHTABLE_H
#include "../../Helper.h"
class My_HashTable{

    int longestConsecutive_slow(const vector<int>& nums) {
        unordered_set<int> my_set;
        unordered_set<int> hasVisited;
        for(int num: nums){
            my_set.insert(num);
        }
        int result = 0;
        for(const int num:my_set){

            if(hasVisited.count(num)){    //  buggy 这个是continue啊，不要break哎 ！！！
                continue;
            }
            hasVisited.insert(num);

            int tmp_result = 1;
            for(int i = num - 1; my_set.count(i) && !hasVisited.count(i) ; i--){    //  buggy 千万不要遗漏了重要的 my_set.count(i)
                hasVisited.insert(i);
                tmp_result++;
            }
            for(int i = num + 1; my_set.count(i) && !hasVisited.count(i) ; i++){
                hasVisited.insert(i);
                tmp_result++;
            }
            result = max(result, tmp_result);
        }
        return result;
    }

    int longestConsecutive(const vector<int>& nums) {
        unordered_set<int> my_set;
        for(int num: nums){
            my_set.insert(num);
        }
        int result = 0;
        for(const int num:my_set){
            if( my_set.count(num-1) ){    //  这里稍微改一改
                continue;
            }
            int tmp_result = 1;
            for(int i = num + 1; my_set.count(i) ; i++){
                tmp_result++;
            }
            result = max(result, tmp_result);
        }
        return result;
    }
};
#endif //LEETCODE_HASHTABLE_H
