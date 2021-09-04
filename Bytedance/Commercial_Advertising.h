//
// Created by 13524 on 2021/3/13.
//

#ifndef LEETCODE_COMMERCIAL_ADVERTISING_H
#define LEETCODE_COMMERCIAL_ADVERTISING_H
#include "bits/stdc++.h"
using namespace std;
//#include "../Helper.h"
class Commercial_Advertising{





    /**
     *
     * @param myList
     * @param total 当前 用户权重和的大小
     * @return 被抽中的那个人的 <用户id, 权重>
     */
    pair<int,int> getOne(list<pair<int,int>>& myList, const int total){
        int targetPtr = (rand()) % total;
        int currentPtr = 0;
        for(auto it = myList.begin(); it != myList.end(); ++it){
            currentPtr += (*it).second;
            if(currentPtr >= targetPtr){
                myList.erase(it);
                return (*it);
            }
        }
    }

    /**
     *
     * @param myList 以链表形式传入所有用户的 <用户id, 权重> 键值对
     * @param NUMBER 需要抽的人数
     * @return 被抽中的用户的用户id，保证唯一性
     */
    vector<int> get(list<pair<int,int>>& myList, const int NUMBER = 3){
        assert(NUMBER <= myList.size());
        srand(time(nullptr));
        int total = 0;
        for(const auto& pii : myList){
            total += pii.second;
        }
        // total 是奖池的大小，就是所有用户的权重和吧
        vector<int> result;
        for(int i = 0; i < NUMBER; i++){
            auto pii = getOne(myList, total);
            total -= pii.second;
            result.push_back(pii.first);
        }
        return result;
    }







public:
    void test(){
        list<pair<int,int>> myList{{1,1},{2,5},{3,10},{4,6},{5,9},{6,4},{7,7}};
        printVector(get(myList));
    }
};
#endif //LEETCODE_COMMERCIAL_ADVERTISING_H
