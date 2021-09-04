//
// Created by 13524 on 2021/2/9.
//

#ifndef LEETCODE_BINARY_SEARCH_H
#define LEETCODE_BINARY_SEARCH_H
#include "../../Helper.h"

class BinarySearch{

    /*
     * 使用了 std::function 与 lambda表达式， 十分nb
     * */
    inline int binarySearchLeft(int LEFT, int RIGHT,  const function<bool(const int&)>& func) {   //  最左, 返回值可能在[LEFT,RIGHT],但 m==RIGHT 永远不会发生
        int l = LEFT, h = RIGHT;    //  [ l , h ]
        while (l < h) {
            int m = l + (h - l) / 2;
            if (func(m)) {
                h = m;
            } else {    //  不满足，那就十分确定了.
                l = m + 1;
            }
        }
        return l;
    }
    inline int binarySearchRight(const int LEFT, const int RIGHT,  const function<bool(const int&)>& func) {   //  最右, 返回值可能在[LEFT,RIGHT],但 m==LEFT 永远不会发生
        int l = LEFT, h = RIGHT;    //  [ l , h ]
        while (l < h) {
            int m = l + (h - l + 1) / 2;    // 向上取整
            if (func(m)) {
                l = m;
            } else {    //  不满足，那就十分确定了.
                h = m - 1;
            }
        }
        return h;
    }

    int mySqrt01(int x) {
        int l = 0, h = 46341;   //  不可能达到46341
        while(h - l > 1){
            const int mid = l + (h - l) / 2;
            if(mid*mid < x){
                l = mid;
            }
            else if(mid*mid > x){
                h = mid;
            }
            else{
                return mid;
            }
        }
        return l;
    }

    int mySqrt02(int x) {
        int l = 0, h = 46340;   //  可能达到46340
        while(h > l){
            const int mid = (h + l + 1) / 2;  // buggy 这里记得加一，加一的位置要小心，相当于向上取整
            if(mid*mid <= x){
                l = mid;
            }
            else{
                h = mid - 1;
            }
        }
        return h;
    }

    int mySqrt03(int x){
        return binarySearchRight(0, 46340, [x](const int mid){return mid*mid > x;});
    }

    char nextGreatestLetter01(const vector<char>& letters, char target) {
        //  buggy 这里不能 -1
        int l = binarySearchLeft(0, (int)letters.size(), [&letters, &target](const int& mid){return letters.at(mid) > target;});
        return l == letters.size() ? letters.at(0) : letters.at(l);
    }

    char nextGreatestLetter02(vector<char>& letters, char target) {
        const int SIZE = (int)letters.size();
        int l = 0, h = SIZE;
        while(h > l){
            int mid = l + (h-l) / 2;
            if(letters.at(mid) > target){
                h = mid;
            } else{
                l = mid + 1;
            }
        }
        return l == SIZE ? letters.at(0) : letters.at(l);
    }

    int findMin(const vector<int>& nums) {
        if(nums.at(0) < nums.at(nums.size()-1)){
            return nums.at(0);
        }
        // buggy 还能不旋转吗？？？ 这是什么奇怪的题目？
        const int minNum = min(nums.at(0), nums.at(nums.size()-1));
        // 所以说这里最好 -1
        return nums.at(binarySearchLeft(0, (int)(nums.size())-1, [minNum, &nums](int mid){return nums.at(mid) <= minNum;}));
    }

    int singleNonDuplicate(const vector<int>& nums) {
        return nums.at(binarySearchLeft(0, (int)nums.size()-1,[&nums](int m){
            return  m%2==0  &&  nums.at(m)!=nums.at(m+1)
                ||  m%2==1  &&  nums.at(m)==nums.at(m+1);
        }));
    }

    vector<int> searchRange(const vector<int>& nums, int target) {
        const int SIZE = nums.size();
        if(!SIZE){
            return {-1,-1};
        }
        const int left = binarySearchLeft(0, SIZE-1, [target, &nums](int m){return nums.at(m) >= target;});
        if(nums.at(left) != target){
            return {-1,-1};
        }
        return {left, binarySearchRight(0, SIZE-1, [target, &nums](int m){return nums.at(m) <= target;})};
    }


    int lengthOfLIS_right(const vector<int>& nums) {
        vector<int>vec;
        for(const int num : nums){
            const int lastIndex = (int)vec.size()-1;    // lastIndex第一次肯定是负数的
            // buggy 这里左边应该传 -1，右边传size()-1. 要避免该类错误，请熟读并背诵文档。
            int index = binarySearchRight(-1, lastIndex,[&vec,num](const int p){ return vec.at(p)<num; });
            if(index == lastIndex){
                vec.push_back(num);
            } else{
                vec.at(index+1)=num;
            }
            printVector(vec);
        }
        return vec.size();
    }

    int lengthOfLIS(const vector<int>& nums) {
        vector<int>vec;
        for(const int num : nums){
            const int SIZE = (int)vec.size();
            int index = binarySearchLeft(0, SIZE,[&vec,num](const int p){ return vec.at(p) >= num; });
            if(index == SIZE){
                vec.push_back(num);
            } else{
                vec.at(index)=num;
            }
            printVector(vec);
        }
        return vec.size();
    }

public:


    void test_mySqrt(){
        cout<<mySqrt02(2147438647);
    }

    void test_nextGreatestLetter(){
        cout<<nextGreatestLetter01({'c','f','j'},'i');
    }

    void test_findMin(){
        cout<<findMin({1,3,5});
    }

    void test_singleNonDuplicate(){
        cout<<singleNonDuplicate({1,1,3,3,4,4,5,8,8});
    }

    void test_searchRange() {
        printVector(searchRange({5,7,7,8,8,10},8));
    }

    void test_lengthOfLIS(){
        cout<<lengthOfLIS({10,9,2,5,3,7,101,18});
    }

};
#endif //LEETCODE_BINARY_SEARCH_H
