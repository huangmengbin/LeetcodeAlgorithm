//
// Created by 13524 on 2021/2/21.
//

#ifndef LEETCODE_BIT_CALCULATE_H
#define LEETCODE_BIT_CALCULATE_H
#include "../../Helper.h"
class Bit{


    /**
     * i-(i&(-i)  相当于  i & (i-1)  。  也就是把 int 的最后一个 1 清除掉
     * @param num
     * @return
     */
    vector<int> countBits(const int num) {
        vector<int> ret = {0};
        for(int i = 1; i <= num; i++){
            ret.push_back( ret[i-(i&(-i))] + 1);
        }
        return ret;
    }

    /**
     * 思想：xor产生的值 diff, 里面必定有1。 每一个1都代表这 a 和 b 不同位上有差异
     * 任意取一个1，都能把整个数组划分为两部分.
     * @param nums
     * @return
     */
    vector<int> singleNumber(const vector<int>& nums) {
        int diff = 0;
        for (int num : nums) diff ^= num;
        assert(diff!=0);
        //  buggy 小心溢出 ! 虽然有的环境不会察觉出来
        const int new_diff = diff == INT_MIN ? diff : diff & -diff ; // 得到最右一位,即最低位
        vector<int> ret(2,0);
        for (const int num : nums) {
            if ((num & new_diff) == 0)
                ret[0] ^= num;
            else
                ret[1] ^= num;
        }
        return ret;
    }
};
#endif //LEETCODE_BIT_CALCULATE_H
