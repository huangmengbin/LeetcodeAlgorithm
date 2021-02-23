//
// Created by 13524 on 2021/2/22.
//

#ifndef LEETCODE_ARRAYS_H
#define LEETCODE_ARRAYS_H
#include "../../Helper.h"
class My_Array{

    /**
     * 原数组操作，把 0 移动到末尾
     * @param nums
     */
    void moveZeroes(vector<int>& nums) {
        const int SIZE = nums.size();
        for(int ptr = 0, zero_ptr = 0; ptr<SIZE; ptr++){
            if(ptr>zero_ptr and nums.at(ptr)!=0){
                swap(nums[zero_ptr], nums[ptr]);
            }
            for(;zero_ptr<SIZE and nums.at(zero_ptr)!=0 ; zero_ptr++);
        }
    }

    /**
     * 数组改造，改造成 r行 c列
     * @param nums
     * @param r 新数组的行数
     * @param c 新数组的列数
     * @return
     */
    vector<vector<int>> matrixReshape(const vector<vector<int>>& nums, const int r, const int c) {
        int ROW = nums.size(), COLUMN = nums.at(0).size();
        if((ROW*COLUMN)%(r*c))return nums;
        vector<vector<int>> result;
        int index = 0;
        for(const auto& vec : nums){
            for(const int num : vec){
                if(index%c == 0){
                    result.emplace_back();
                }
                result.back().push_back(num);
                index++;
            }
        }
        return result;
    }


    /**
     * 理论上应该是1-n的数字，但一个缺失、一个重复. 找出来它
     * 本方法是基于O(N)的原地排序，非比较算法。缺点是修改了nums的内容
     * 使用位运算是更6的方法
     * @param nums
     * @return
     */
    vector<int> findErrorNums(vector<int>& nums) {
        const int N = nums.size();
        int dump = 67666, missing = -67666;
        for(int i = 0;i<N; ){
            const int current = nums.at(i);
            if(current == i+1){
                i++;
            } else{
                const int destination = current - 1;
                if(current == nums[destination]){
                    dump = current;
                    i++;
                } else{
                    swap(nums[i], nums[destination]);
                }
            }
        }
        for(int i = 0;i<N; i++){
            if(nums.at(i) != i+1){
                missing = i+1;
                break;
            }
        }
        return vector<int>{dump, missing};
    }


    vector<int> findErrorNums_faster(vector<int>& nums) {
        const int N = nums.size();
        for(int i = 0;i<N; i++){
            // current === nums.at(i)
            // destination === current - 1
            while (nums.at(i) != i+1 and nums.at(i) != nums[nums.at(i)-1]){
                swap(nums[i], nums[nums.at(i)-1]);
            }
        }
        for(int i = 0; /* i<N */ ; i++){
            if(nums.at(i) != i+1){
                return vector<int>{nums.at(i), i+1};
            }
        }
    }


    /**
     * 给定一个包含n + 1 个整数的数组 nums ，其数字都在 1 到 n之间（包括 1 和 n），可知至少存在一个重复的整数。
     * 假设 nums 只有 一个重复的整数 ，找出 这个重复的数
     *
     * 不可以使用位运算，因为可能重复很多次，也不保证 1 ~ n 都存在。  如 {2,2,2,2,2} , n = 4.
     *
     * @param nums
     * @return
     *
     * 因此就是二分了，主要是对 1 和 N . 对数字本身, 而不是对数组。 复杂度比线性高一个log. 因为每次分割是O(N)的，不是O(1)的
     */
    int findDuplicate(const vector<int>& nums) {
        const int SIZE = nums.size();
        const int N = SIZE -1;
        int low = 1, high = N;

        while (low <= high){

            const int  middle = low + (high-low)/2;
            int count = 0;
            for(const int num : nums){
                if(num <= middle){
                    count++;
                }
            }

            if(count <= middle){
                low = middle + 1;
            } else{
                high = middle - 1;
            }
        }
        return low;

    }


    /**
     *
     * 给定两个整数 n 和 k，你需要实现一个数组，这个数组包含从 1 到 n 的 n个不同整数，同时满足以下条件：
     * 如果这个数组是 {a1, a2, a3, ... , an} ，那么数组{|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|}中应该有且仅有 k 个不同整数；
     *
     * @param n
     * @param k
     * @return
     */
    vector<int> constructArray(int n, int k) {
        int start = 1, end = n;
        vector<int> result;
        int i = 0;
        for( ; i<k-1; i++){
            if(i%2 == 0){
                result.push_back(start++);
            } else{
                result.push_back(end--);
            }
        }
        if(i%2 == 0){
            for(int j = 0; j<n-k+1; j++){
                result.push_back(start++);
            }
        } else{
            for(int j = 0; j<n-k+1; j++){
                result.push_back(end--);
            }
        }
        return result;
    }





     /**
      *     给定一个非空且只包含非负数的整数数组 nums ，数组的度的定义是指数组里任一元素出现频数的最大值。
      *     你的任务是在 nums 中找到与 nums 拥有相同大小的度的 最短连续子数组，返回其长度。 即最小值
      *
      * @param nums
      * @return
      */
    int findShortestSubArray(const vector<int>& nums) {
        map<int,int> times, left, right;
        const int SIZE = nums.size();
        int max_time = 0;
        for(int i = 0; i<SIZE; ++i){
            const int num = nums.at(i);
            times[num]++;
            max_time = max(max_time, times.at(num) );
            if(0 == left.count(num) ){
                left[num] = i;
            }
            right[num] = i;
        }
        int min_length = INT_MAX;
        for(const int num : nums){
            if(max_time == times.at(num)){
                min_length = min(min_length, 1 + right.at(num) - left.at(num) );
            }
        }
         return min_length;
    }



    /**
     * 分隔数组成为“排序块”
     *
     * 数组arr是[0, 1, ..., arr.length - 1]的一种排列，我们将这个数组分割成几个“块”，
     * 并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。
     *
     * @param arr
     * @return 最多的 “块” 个数
     */
    int maxChunksToSorted(const vector<int>& arr) {
        const int SIZE = arr.size();
        int result = 0;
        for(int lastIndex = 0; lastIndex < SIZE; lastIndex++, result++){
            for(int index = lastIndex; index <= lastIndex; index++){
                lastIndex = max(lastIndex, arr.at(index));      // 贪婪的不断索取右边的块
            }
        }
        return result;
    }


    /**
     *
     * 索引从0开始长度为N的数组A，包含 0 到 N - 1 的所有整数。找到最大的集合S并返回其大小，
     * 其中 S[i] = {A[i], A[A[i]], A[A[A[i]]], ... }且遵守以下的规则。
     *
     * 假设选择索引为i的元素A[i]为S的第一个元素，S的下一个元素应该是A[A[i]]，之后是A[A[A[i]]]... 以此类推，不断添加直到S出现重复的元素。
     *
     *     实际上，把数组看出链表，就是求最大 简单圈 的长度
     *     由于它包含 0 到 N - 1 的所有整数，即所有值唯一，所以不会有【多个顶点指向同一节点】的复杂情况
     *     因此不必区分 当前遍历 和 历史遍历
     *
     * @param nums
     * @return
     */
    int arrayNesting(vector<int>& nums) {
        const int SIZE = nums.size();
        int result = 0;
        for(int i = 0; i < SIZE; i++){
            int cnt = 0;
            for(int index = i; nums.at(index) != -1; cnt++){
                int& currentIndex = nums.at(index); //  临时存储当前,以引用形式, 与for循环里面的判断条件是完全相同的
                index = nums.at(index); //  指向下一个
                //  buggy 最好是使当前遍历的那个变为 -1， 而不是使下一个变为 -1
                currentIndex = -1;
            }
            result = max(result, cnt);
        }
        return result;
    }



};
#endif //LEETCODE_ARRAYS_H
