//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_DP_H
#define LEETCODE_DP_H
#include "../../Helper.h"
class DP{


    /**
     * 斐波那契
     */


    /**
     * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
     * 影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
     * 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
     *
     *     dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
     *
     *     为什么这个是对的，确实不那么直观... 还是得仔细思索
     */


    int rob1(const vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        int *dp = new int[nums.size()];
        for(int i = 0; i<nums.size(); i++){
            if(i==0){
                dp[0]=nums[0];
            } else if(i==1){
                dp[1] = max(dp[0], nums[1]);
            } else{
                dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
            }
        }
        return dp[nums.size() - 1];
    }


    int rob2(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        if(nums.size() == 1){
            return nums.at(0);
        }
        int end_num = nums.back();
        nums.pop_back();
        int res1 = rob1(nums);
        nums.push_back(end_num);
        nums.erase(nums.begin());
        return max(res1, rob1(nums));
    }

    /**
     * 矩阵
     */

    int minPathSum_2(const vector<vector<int>>& grid) {
        int row = grid.size(), column = grid[0].size();
        assert(row * column);
        int **const dp = new int *[row];
        for(int i = 0;i<row; i++){
            dp[i] = new int [column];
        }
        dp[0][0] = grid[0][0];

        for (int j = 1; j < column; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        for (int i = 1; i < row; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        for (int i = 1; i < row; i++) {
            for (int j = 1; j < column; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[row - 1][column - 1];
    }

    // 循环利用 一维数组， 节省空间
    int minPathSum_1(const vector<vector<int>>& grid){
        int row = grid.size(), column = grid[0].size();
        assert(row * column);
        int *dp = new int [column];

        dp[0] = grid[0][0];
        for (int j = 1; j < column; j++) {
            //  处理 第 0 行， 累加
            dp[j] = dp[j - 1] + grid[0][j];
        }

        for (int i = 1; i < row; i++) {
            dp[0] = dp[0] + grid[i][0];  // j == 0 的时候，先预处理第一列
            for (int j = 1; j < column; j++) {
                dp[j] = min(dp[j],  dp[j-1]) + grid[i][j];
            }
        }
        return dp[column - 1];
    }


    /**
     * 数组区间
     */

    /**
     *
     *   dp 数组代表: 以此处作为结尾的所有子数组中，等差数组的数量
     */
    int numberOfArithmeticSlices(const vector<int>& ARRAY) {
        const int N = ARRAY.size();
        if(N < 3){
            return 0;
        }
        int *dp = new int [N];
        dp[0] = dp[1] = 0;
        for (int i = 2; i < N; i++) {
            if (ARRAY[i] - ARRAY[i - 1] == ARRAY[i - 1] - ARRAY[i - 2]) {
                dp[i] = dp[i - 1] + 1;
            } else {
                dp[i] = 0;          //  buggy 小心未初始化
            }
        }
        int total = 0;
        for (int i = 0; i<N; i++) {
            total += dp[i];
        }
        return total;
    }



    int numberOfArithmeticSlices_1(const vector<int>& ARRAY) {
        const int N = ARRAY.size();
        if(N < 3){
            return 0;
        }
        int tmp = 0,   total = 0;;
        for (int i = 2; i < N; i++) {
            if (ARRAY[i] - ARRAY[i - 1] == ARRAY[i - 1] - ARRAY[i - 2]) {
                total += (++tmp);
            } else {
                tmp = 0;          //  buggy 小心未初始化
            }
        }
        return total;
    }



    /**
     *   整数拆分
     */

    int numSquares(const int N) {
        int *const dp = new int [N+1]{0};
        for(int i = 1; i <= N; i++){
            dp[i] = INT_MAX;
            const int sq = floor(sqrt(i));
            for(int j = 1; j<=sq; j++){
                dp[i] = min(dp[i],  1+dp[i-j*j]);
            }
        }
        return dp[N];
    }

public:
    void test_minPathSum(){
        cout<<minPathSum_1({{1,3,1},{1,5,1},{4,2,1}});
    }

};
#endif //LEETCODE_DP_H
