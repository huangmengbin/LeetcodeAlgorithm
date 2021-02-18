//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_DP_H
#define LEETCODE_DP_H
#include "../../Helper.h"
class DP{


    /************************************************
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

    /************************************************
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


    /************************************************
     * 数组区间
     */

    /*************************
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



    /************************************************
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


    /*************************
     * 求方法总数，DP较好
     * 求每个方法的具体细节，回溯较好
     */
    int numDecodings(const string& s) {
        const int N = s.size();
        assert(N);
        int *dp = new int [N];
        //  buggy 小心 s 里面包含了字符 '0'
        for(int i = 0; i<N; ++i){
            int num1 = s.at(i) - '0';
            if(i) {
                dp[i] = num1 ? dp[i-1] : 0;         //  这里的，一旦被0阻断，就会很复杂，慢慢想吧
                int num2 = stoi(s.substr(i-1,2));
                if(10<=num2 && num2<=26) {          //  避免 00 ~ 09 这类,  也是 0 阻断的原因之一
                    dp[i] +=  i==1? 1 : dp[i-2];    //  buggy 防止溢出；也可以设一个虚拟节点 dp[-1]=1;
                }
            } else{
                dp[0] = num1!=0;
            }
        }
        for(int i=0;i<N;i++){
            cout<<dp[i]<<' ';
        }
        cout<<endl;
        return dp[N-1];
    }


    /***
     *
     * 子序列问题。
     *
     */

    /**
     * 最长递增子序列
     * @param nums
     * @return
     */
    int lengthOfLIS(const vector<int>& nums) {
        int n = nums.size();
        int * dp = new int[n];
        int result = 1;         //  buggy 也初始化为1，避免永远不进入 if 而导致无法更新。或者把result=max()写在if外
        for(int i = 0; i<n; i++){
            dp[i] = 1;
            //  buggy dp[i] = INT_MIN 是错的。无论i是多少，都可以选择从此处开始(忽略之前的所有)，因此至少会有1
            for(int j = i-1; j>=0; j--){
                if(nums.at(j) < nums.at(i)){
                    dp[i] = max(dp[i], dp[j]+1);
                    result = max(result, dp[i]);///
                }
            }
        }
        return result;
    }


    /**
     * 最长摆动子序列
     * @param nums
     * @return
     */
    int wiggleMaxLength(const vector<int>& nums) {
        int N = nums.size();
        if (N < 2) {
            return N;
        }
        int *const up = new int [N], *const down = new int [N];
        up[0] = down[0] = 1;                // 末尾是up还是down
        for (int i = 1; i < N; i++) {
            if (nums[i-1] < nums[i]) {        // 上升的时候
                up[i] = max(up[i - 1], down[i - 1] + 1);    // 立刻接上并没有太大坏处, 请参见下面一行
                down[i] = down[i - 1];          //  上升对down数组更有利，因为未来下降潜力变大了
            } else if (nums[i-1] > nums[i]) {
                up[i] = up[i - 1];
                down[i] = max(up[i - 1] + 1, down[i - 1]);
            } else {                            //  仅仅传递到下一个而已，相当于 up 和 down 的指针都不动
                up[i] = up[i - 1];
                down[i] = down[i - 1];
            }
        }
        return max(up[N - 1], down[N - 1]);
    }

    /**
     * 一组整数对能够构成的最长链
     * @param pairs
     * @return
     */
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        //  因为是任意，所以最好排序
        sort(pairs.begin(),pairs.end(),[](const vector<int>&a,const vector<int>&b){
            return a.at(0) < b.at(0);
        });
        int * dp = new int[n];
        int result = 1;
        for(int i = 0; i<n; i++){
            dp[i] = 1;
            for(int j = i-1; j>=0; j--){
                if(pairs.at(j)[1] < pairs.at(i)[0]){    // 只需这一行改动一下下
                    dp[i] = max(dp[i], dp[j]+1);
                    result = max(result, dp[i]);
                }
            }
        }
        return result;
    }

    /**
     * 最长公共子序列
     * @param text1
     * @param text2
     * @return
     */
    int longestCommonSubsequence(const string& text1, const string& text2) {
        const int N1 = text1.size(), N2 = text2.size();
        int **const dp = new int * [1+N1];
        for(int i = 0; i<= N1; i++){
            dp[i] = new int [1+N2];
            dp[i][0]=0;
        }
        memset(dp[0],0,(1+N2)*sizeof(int));
        for(int i = 1;i<=N1;i++){
            const char c1 = text1.at(i-1);
            for(int j = 1; j<=N2; j++){
                const char c2 = text2.at((j-1));
                if(c1==c2){
                    //  buggy  这个必须要用左上角，也就是斜线的。为了保证不发生重复匹配， 如 "ba" 和 “bcbcbcbc”
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[N1][N2];
    }

public:

    void test_minPathSum(){
        minPathSum_1({{1,3,1},{1,5,1},{4,2,1}});
    }

    void test_numDecodings(){
        cout<<numDecodings("12002");
    }

    void test_longestCommonSubsequence(){
        cout<<longestCommonSubsequence("bsbininm",
                                       "jmjkbkjkv");
    }

};
#endif //LEETCODE_DP_H
