//
// Created by 13524 on 2021/2/2.
//

#ifndef LEETCODE_MY_SORT_H
#define LEETCODE_MY_SORT_H
#include "../../Helper.h"
class Sort{

    inline int findKthLargest(vector<int>& nums, const int k, const int LOW = 0, int high = -1 /* 实际上是size */) {//左闭右开
        //使用某种nb的算法, [bfprt]
        const int HIGH = high == -1 ? (int)nums.size() : high;
        assert(LOW <= k - 1 and k - 1 < HIGH);
        if(HIGH - LOW == 1){
            return nums[LOW];
        }
        vector<int> middles;
//        cout<<"low="<<LOW<<'\t'<<"high="<<HIGH<<'\t'<<"k="<<k<<endl;
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
        for(int i = LOW;i<HIGH;i++){
            if(nums.at(i) == middle){
                swap(nums[i], nums[LOW]);//为了简化流程，引入冗余的move
                break;
            }
        }

        //直到这里，才求出了中间数及其对应的位置. 而且已经完成一次交换
        //下面可以通过修改 >  ,   <  来更换功能
        int left = LOW, right = HIGH-1;
        for(int i = LOW ; i<=right; ){
            const int current = nums.at(i);
            if(current > middle){
                swap(nums[i++], nums[left++]);
            } else if(current < middle){
                swap(nums[i],nums[right--]);
            } else{
                ++i;
            }
        }

        if(k - 1 < left){
            return findKthLargest(nums, k, LOW, left);
        } else if(k - 1 > right){
            return findKthLargest(nums, k, right + 1, HIGH);
        } else{
            return middle;
        }
    }


    /**
     * 使用堆
     * @param nums
     * @param K
     * @return
     */
    int findKthLargest_heap( const vector<int>& nums, const int K ) {
        priority_queue<int,vector<int>,greater<> > my_heap; // buggy 这个才是最小堆，默认 less 是大顶堆
        for(const int num:nums){
            if(my_heap.size() == K){
                const int top = my_heap.top();
                if(num > top){ // 维护一个数字较大 的 最小堆, 所以不断寻找更大的数字
                    my_heap.pop();
                    my_heap.push(num);
                }
            } else{
                my_heap.push(num);
            }
        }
        return my_heap.top();
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
        vector<int> nums = {3,2,1,5,6,4};
        cout<<findKthLargest(nums,2) <<endl;
    }
    void test_findKthLargest_heap(){
        vector<int> nums = {3,2,1,5,6,4};
        cout<<findKthLargest_heap(nums,2) <<endl;
    }
    void test_topKFrequent(){
        printVector(topKFrequent({1,1,2,2,3,1,0},2));
    }
};
#endif //LEETCODE_MY_SORT_H
