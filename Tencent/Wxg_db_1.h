//
// Created by 13524 on 2021/8/24.
//

#ifndef LEETCODE_WXG_DB_1_H
#define LEETCODE_WXG_DB_1_H
class Wxg_db_1{
    int function(vector<int> & num ,    const int k,  int begin = 0,  int end = -1) {

        if(begin==end){
            return num[begin];
        }

        int ptr = begin;

        const int mid = num[ptr];

        swap( num[ptr], num[begin] );
        ptr = begin;

        for( int right = begin+1; right <= end; right++ ){
            if(num[right] < num[ptr]){
                swap(num[ptr], num[ptr+1]);
                if(right != ptr+1)swap(num[ptr], num[right]);
                ptr++;
            }
        }

        printVector(num);


        if(ptr==k){
            return mid;
        }
        else if(ptr > k) {
            return function(num, k, begin, ptr-1);
        }
        else {// (ptr < k)
            return function(num, k  , ptr+1, end);
        }
    }


    unordered_map<int,int> myMap{};
    void init (int n, vector<int>& blacklist) {
        int limit = n-blacklist.size();
        unordered_set<int> mySet(blacklist.begin(),blacklist.end());
        for(int end = limit, i = 0; i<blacklist.size(); i++, end++){
            int num = blacklist[i];
            if(num<limit){
                while(mySet.count(num)) {
                    num++;
                }
                myMap[end]=num;
            }
        }
    }


    int findKthLargest(vector<int>& nums, const int k) {//左闭右开
        return function(nums,nums.size()- k,0,nums.size()-1);
    }

public:


    void test() {
        vector<int> nums{3,2,1,5,6,4};
        int a = this->findKthLargest(nums, 2);
        cout<<a<<endl;
    }
};

#endif //LEETCODE_WXG_DB_1_H
