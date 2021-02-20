//
// Created by 13524 on 2021/2/20.
//

#ifndef LEETCODE_ARRAYLIST_H
#define LEETCODE_ARRAYLIST_H
#include "../../Helper.h"

class ArrayList{




    /**
     *  单调栈, O(N), 十分easy
     */

    /**
     * 数组中元素与下一个比它大的元素之间的距离
     *
     * @param nums  代表普通数组
     * @return 比他大的下一个，元素的【下标】
     */
    vector<int> dailyTemperatures(const vector<int>& nums) {
        vector<int> result(nums.size() , 676666);
        stack<int> indexes;
        for(int index = 0; index < nums.size(); ++index){
            const int num = nums.at(index);
            while(!indexes.empty() && nums[indexes.top()] < num){  //单调递减栈，注意，存的是【下标】而不是具体数字！
                result[indexes.top()] = index - indexes.top();
                indexes.pop();
            }
            //  保证  (indexes.empty() || nums[indexes.top()] >= num) 成立
            indexes.push(index);                                //存的是【下标】而不是具体数字！
        }
        while (!indexes.empty()){
            result[indexes.top()] = 0;
            indexes.pop();
        }
        return result;
    }

    /**
     * 循环数组中比当前元素大的下一个元素
     *
     * @param nums  代表循环数组
     * @return 比他大的下一个，元素的值，注意是循环数组
     */
    vector<int> nextGreaterElements(const vector<int>& nums) {
        vector<int> result(nums.size() , -1);   //  省略了最后的【清空栈】操作
        stack<int> indexes;
        for(unsigned i = 0; i < nums.size(); ++i){
            const int num = nums.at(i);
            while(!indexes.empty() && nums[indexes.top()] < num){
                result[indexes.top()] =num;
                indexes.pop();
            }
            //  保证  (indexes.empty() || nums[indexes.top()] >= num) 成立
            indexes.push(i);
        }
        for(int num : nums){      //  第二个for和第一个差不多，相当于复制粘贴吧
            while(!indexes.empty() && nums[indexes.top()] < num){
                result[indexes.top()] = num;
                indexes.pop();
            }
            if(indexes.empty()){  // 提前break，提高效率
                break;
            }
        }
        //  最后没有清空栈
        return result;
    }
};
#endif //LEETCODE_ARRAYLIST_H
