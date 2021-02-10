//
// Created by 13524 on 2021/2/2.
//

#ifndef LEETCODE_MY_SORT_H
#define LEETCODE_MY_SORT_H
#include "../../Helper.h"
class Sort{
private:
    int findKthLargest(vector<int>& nums, const int k, const int LOW = 0, int high = -1 /* 实际上是size */) {//左闭右开
        //使用某种nb的算法, [bfprt]
        const int HIGH = high == -1 ? (int)nums.size() : high;
        assert(HIGH - LOW >= k);
        if(HIGH - LOW == 1){
            return nums[LOW];
        }
        vector<int> middles;

        for(int i = LOW, j = LOW + 5; ; i = j, j += 5){
            if(j >= HIGH){
                sort(&nums[i], &nums[HIGH]);
                middles.push_back(nums[(i + HIGH - 1) / 2]);
                break;
            }
            else{
                sort(&nums[i], &nums[j]);
                middles.push_back(nums[i+2]);
            }
        }

        const int middle = findKthLargest(middles, ((int)middles.size()+1)/2);  // 原因: k 是从 1 开始计数的...
        int empty_ptr = -1;
        for(int i = LOW;i<HIGH;i++){
            if(nums.at(i) == middle){
                empty_ptr = HIGH - 1;
                swap(nums[i], nums[empty_ptr]);//为了简化流程，引入冗余的move
                break;
            }
        }
        assert(empty_ptr > 0);
        //直到这里，才求出了中间数及其对应的位置

        cout<<endl;
        cout<<empty_ptr<<endl;
        printVector(nums);
        for(int i = LOW, j = HIGH-1; ;){
            while(i<=j && nums.at(i) >= middle){        // buggy  是以中位数为分隔基准
                i++;
            }
            if(i<j){
                nums[empty_ptr] = nums[i];
                empty_ptr = i;
            } else{
                break;
            }
            printVector(nums);
            while(i<=j && nums.at(j) <= middle) {
                j--;
            }
            if(i<j){
                nums[empty_ptr] = nums[j];
                empty_ptr = j;
            } else{
                break;
            }
            printVector(nums);
        }
        nums[empty_ptr] = middle;

        cout<<"low="<<LOW<<" high="<<HIGH<<" k="<<k<<" ptr="<<empty_ptr<< " middle="<<middle << endl;
        printVector(nums);

        if(empty_ptr+1 - LOW < k){                                           // buggy  要 +1 -LOW, 因为它才是真正的序数
            return findKthLargest(nums, k-(empty_ptr+1 - LOW), empty_ptr+1, HIGH);
        } else if(empty_ptr+1 - LOW > k){
            return findKthLargest(nums, k, LOW, empty_ptr);
        } else{
            return middle;
        }

    }

    vector<int> topKFrequent(const vector<int>& nums, int k) {
        unordered_map<int,int> unorderedMap;
        for(int num : nums){
            unorderedMap[num] = unorderedMap[num] + 1;
        }
        vector<pair<int,int>> bullet;
        for(auto pii : unorderedMap){
            bullet.emplace_back(pii);
        }
        // lambda 表达式
        sort(bullet.begin(),bullet.end(),[](pair<int,int>&a, pair<int,int>&b)->bool{return a.second > b.second;});
        vector<int> res;
        for(int i = 0; i< k; i++){
            res.push_back(bullet[i].first);
        }
        return res;
    }

    void sortColors(vector<int>& nums) {
        int l = -1, m = 0, r = (int)nums.size();
        while(m<r){
            switch (nums.at(m)) {
                case 0:
                    swap(nums[++l],nums[m]);    //无break, 即 m 仍要 加一
                case 1:
                    m++;
                    break;
                default:
                    swap(nums[--r],nums[m]);
                    break;
            }
        }
    }
public:
    void test_findKthLargest(){
        vector<int> nums = {3,2,3,1,2,4,5,5,6};
        cout<<findKthLargest(nums,4);
    }
    void test_topKFrequent(){
        printVector(topKFrequent({1,1,2,2,3,1,0},2));
    }
};
#endif //LEETCODE_MY_SORT_H
