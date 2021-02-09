//
// Created by 13524 on 2021/2/4.
//

#ifndef LEETCODE_GREEDY_H
#define LEETCODE_GREEDY_H
#include "../../Helper.h"
class Greedy{
private:
    int eraseOverlapIntervals(vector<vector<int>>& vec) {
        if(vec.empty())  return 0;
        sort(vec.begin(), vec.end(), [](const vector<int>& a, const vector<int>& b){return a.at(1) < b.at(1);});
        int count = 1, lastRight = vec[0][1];
        for(unsigned i = 1; i < vec.size(); i++){
            if(lastRight <= vec[i][0]){    // 这是由于右边是开区间，相等时无冲突
                lastRight  =  vec[i][1];
                count ++;
            }
        }
        return (int)vec.size() - count;
    }

    int findMinArrowShots(vector<vector<int>>& vec) {
        if(vec.empty())  return 0;
        sort(vec.begin(), vec.end(), [](const vector<int>& a, const vector<int>& b){return a.at(1) < b.at(1);});
        int count = 1, lastRight = vec[0][1];
        for(unsigned i = 1; i < vec.size(); i++){
            if( lastRight < vec[i][0]){    // 这是由于右边是闭区间，相等时会冲突
                lastRight =  vec[i][1];
                count ++;
            }
        }
        return count;
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](const vector<int>&a,const vector<int>&b){
            if(a.at(0)==b.at(0)){
                return a.at(1)<b.at(1);
            }
            return a.at(0)>b.at(0);
        });
        vector<vector<int>> result;
        for(const vector<int>&i : people){
            result.insert(result.begin()+i.at(1), i);
        }
        return result;
    }

    bool isSubsequence(const string& shortStr, const string& longStr) {
        string::size_type index = -1;
        for(char c:shortStr){
            if((index = longStr.find(c, 1+index)) == string::npos) {  // buggy 记得加一, 否则就傻了, 反复利用...
                return false;
            }
        }
        return true;
    }
public:
    void test_eraseOverlapIntervals_and_findMinArrowShots(){
        vector<vector<int>> intervals = {{1,2},{0,1},{3,4},{3,7},{5,6},{4,6}};
        cout<<eraseOverlapIntervals(intervals)<<endl;
        cout<<findMinArrowShots(intervals)<<endl;
    }

    void test_reconstructQueue(){
        vector<vector<int>> vec = {{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}};
        printVectorVector(reconstructQueue(vec));
    }
    void test_isSubsequence(){
        cout<<isSubsequence("ace","ache");
    }
};
#endif //LEETCODE_GREEDY_H
