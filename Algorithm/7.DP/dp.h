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

    /**
     * 字符串编辑
     */

    /**
     * 两个字符串的删除操作
     * @param text1
     * @param text2
     * @return
     */
    int minDistance(const string& text1, const string& text2) {
        const int N1 = text1.size(), N2 = text2.size();
        //  buggy 不要忘了 *2 ， 因为两个串都有剩余值
        return N1+N2-longestCommonSubsequence(text1,text2)*2;
    }

    /**
     * 字符串编辑距离（除了删除，还能增、改, 【实际上不再需要考虑删除了】）
     * @param text1
     * @param text2
     * @return
     */
    int minDistance(string text1, string text2) {
        const int N1 = text1.size(), N2 = text2.size();
        int **const dp = new int * [1+N1];
        for(int i = 0; i<= N1; i++){
            dp[i] = new int [1+N2];
            dp[i][0] = i;
        }
        for(int j = 0; j<=N2; j++){
            dp[0][j] = j;
        }

        for(int i = 1;i<=N1;i++){
            const char c1 = text1.at(i-1);
            for(int j = 1; j<=N2; j++){
                const char c2 = text2.at((j-1));
                ///
                if(c1==c2){
                    dp[i][j] = dp[i-1][j-1];
                } else{
                    dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
                }
                ///
//                dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
//                if(c1==c2){
//                    dp[i][j] = min(dp[i][j],dp[i-1][j-1]);
//                }
            }
        }
        return dp[N1][N2];
    }

    /**
     * 只有两个键的键盘 ： 复制全部 粘贴复制框内容
     * @param n 目的字符串的长度
     * @return 步骤数
     */
    int minSteps(int n) {
        int *const dp = new int [1+n];
        dp[1] = 0;
        //  将dp[0] 浪费掉了
        for(int i = 2; i<=n; i++){
            dp[i] = INT_MAX;
            for(int j = 1; j < i; j++){
                if(i%j == 0){
                    dp[i] = min(dp[i], dp[j]+(i/j));
                }
            }
        }
        return dp[n];
    }


    /**
     * dalao 写的优化，首先是 sqrt 开方，然后，dp[i+j]十分巧妙，因此才可以用break
     * @param n
     * @return
     */
    int minSteps_666 (int n) {
        int *const dp = new int [1+n];
        dp[1] = 0;
        for (int i = 2; i <= n; i++) {
            dp[i] = i;
            int h = (int) sqrt(i);
            for (int j = 2; j <= h; j++) {
                if (i % j == 0) {
                    dp[i] = dp[j] + dp[i / j];
                    break;
                }
            }
        }
        return dp[n];
    }


    /**
     *     0-1 背包， 数量有限、维度简单(一维)
     *
     * @param  VOLUME 为背包总容积、重量限制......
     * @param weights 数组存储 NUMBER 个物品的重量(体积)
     * @param values 数组存储 NUMBER 个物品的"价值"
     * @return  最大的价值
     */
    int knapsack1(const int VOLUME, const vector<int>& weights, const vector<int>& values) {
        assert(weights.size() == values.size());
        const int NUMBER = weights.size();
        /// @var NUMBER 为物品数量
        int *const dp = new int[VOLUME + 1];  // dp 数组，搞一个0号位，方便计算
        memset(dp,0,sizeof(int)*(1+VOLUME));
        for (int i = 1; i <= NUMBER; i++) {
            const int weight = weights[i - 1], value = values[i - 1];
            for (int j = VOLUME; j >= 1; j--) {  // 这里本应该使用上一行的数据，因此倒序以防止覆盖
                if (j >= weight) {
                    dp[j] = max(dp[j], dp[j - weight] + value);
                }
            }
        }
        return dp[VOLUME];
    }



    /**
     * 复杂度与 sum_of (nums)/2有关, 这也是背包问题不可避免的通病
     * @param nums 只包含正整数的非空数组, 相当于背包里面的 weight
     * @return 是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
     */

    bool canPartition(const vector<int>& nums) {
        int sum = 0;
        for(int num:nums){
            sum+=num;
        }
        if(sum % 2){
            return false;
        }
        const int VOLUME = sum/2;
        vector<bool> dp (VOLUME+1,false);
        dp[0]=true;
        for (const int weight : nums) {                 // 0-1 背包一个物品只能用一次
            for (int i = VOLUME; i >= weight; i--) {   // 从后往前，先计算 dp[i] 再计算 dp[i-weight]
                dp[i] = dp[i] || dp[i - weight];      //dp[]是指，允许取到 该数字(外层循环) 时，能否达到规定的大小（i就是大小）
            }
            printVector(dp);
        }
        return dp.back();
    }

    /**
     *
     *
     * @param nums 相当于weight
     * @param S 目标和，对总体积有一定影响
     * @return 使最终数组和为目标数 S 的所有添加符号的方法数。
     *
     * 方法总数，把第0个初始化为1，  不断 += 就行......
     */
    int findTargetSumWays(const vector<int>& nums, int S) {
        int sum = 0;
        for(int num:nums){
            sum+=num;
        }
        if(sum<S){
            return false;
        }
        sum += S;
        if(sum % 2){
            return false;
        }
        const int VOLUME = sum/2;
        vector<int> dp (VOLUME+1);
        dp[0]=1;
        for (const int weight : nums) {
            for (int i = VOLUME; i >= weight; i--) {
                //  变成求方法总数了，比较难
                dp[i] += dp[i-weight];  // 存在 +0 的可能性, 这...太迷惑了
            }
            printVector(dp);
        }
        return dp.back();
    }

    /**
     * 给你一个二进制字符串数组 strings 和两个整数 m 和 n
     * 请你找出并返回 strings 的最大子集的大小，该子集中 最多 有 m 个 0 和 n 个 1
     * @param strings 二维的weight
     * @param m 限制0
     * @param n 限制1
     * @return 最大的size，相当于每一个字符串的 value 均为 1
     */
    int findMaxForm0(const vector<string>& strings, int m, int n) {
        int **const dp = new int *[m+1];
        for(int i = 0; i<=m; ++i){  // buggy 这个初始化是 i<=m 而不是 i<m
            dp[i] = new int [n+1];
            memset(dp[i],0,(n+1)*sizeof(int));
        }
        for(const string& s : strings){
            int zero = 0, one = 0;
            for(const char c: s){
                if(c=='0'){
                    zero++;
                }
                else{
                    one++;
                }
            }
            for(int i = m; i>=zero; i--){
                for(int j = n; j>=one; j--){
                    /// dp[j] = max(dp[j], dp[j - weight] + value);
                    dp[i][j] = max(dp[i][j], dp[i-zero][j-one]+1);
                }
            }
        }
        return dp[m][n];
    }

    /**
     * 通用的 二维背包问题 解决方案
     *
     * @param weightLimit1 相当于容积1
     * @param weights1 每一个的体积，被容积1所限制
     * @param weightLimit2 相当于容积2
     * @param weights2 每一个的体积，被容积2所限制
     * @param values 每一件物品的最终"价值"
     * @param initial 用它来初始化，默认为0
     * @return 最大的“价值”
     */

    inline int knapsack2(const int weightLimit1, const vector<int>& weights1, const int weightLimit2, const vector<int>& weights2, const vector<int>& values, const int initial = 0) {
        assert(weights1.size() == values.size() && weights2.size() == values.size());
        vector<vector<int>> dp (1+weightLimit1, vector<int>(1+weightLimit2, initial));
        for(unsigned ptr = 0, SIZE = values.size(); ptr<SIZE; ptr++){
            const int value = values.at(ptr);
            const int weight1 = weights1.at(ptr);
            const int weight2 = weights2.at(ptr);
            for(int i = weightLimit1; i >= weight1; i--){
                for(int j = weightLimit2; j >= weight2; j--){
                    dp[i][j] = max(dp[i][j], value+dp[i-weight1][j-weight2]);
                }
            }
        }
        return dp[weightLimit1][weightLimit2];
    }

    int findMaxForm(const vector<string>& strings, int m, int n) {
        vector<int> zeros, ones;
        const vector<int> values(strings.size(), 1);
        for(const string& s : strings){
            int zero = 0, one = 0;
            for(const char c: s){
                if(c=='0'){
                    zero++;
                }
                else{
                    one++;
                }
            }
            zeros.push_back(zero);
            ones.push_back(one);
        }
        return knapsack2(m,zeros,  n,ones,   values);
    }


    /**
     * 经典的硬币组合问题，转化为恰好装满的完全背包
     *
     * @param coins 各个的体积
     * @param amount 容积限制，且是必须相等，即：恰好装满
     *   value 均为1
     * @return  最小的“价值”，不是最大的，其实思路也也差不多
     */
    int coinChange(const vector<int>& coins, const int amount) {
        if(amount == 0){
            return 0;
        }
        vector<int> dp (amount + 1, INT_MAX);
        for (const int weight : coins) {
            for (int j = weight; j<=amount; ++j) {  /// 内层循环改成：正向， 为什么正向就可以了？
                if(j==weight){
                    //dp[weight] = 1, 不解释，
                    dp[j] = 1;
                } else if(dp[j-weight]!=INT_MAX){
                    // 必须要保证【前面那个有解】才行啊，否则自己也没法利用以前的数据，因为题目要求‘恰好’.
                    // 这里保证 j>weight，因此dp[0]没有用, 或者预先强行把dp[0]设置为0，就可以利用ta了
                    // 利用以前的数据，优化、优化
                    dp[j] = min(dp[j], 1+dp[j-weight]);
                }
            }
        }
        return dp[amount];
    }


    int change(int amount, vector<int>& coins) {
        vector<int> dp (amount+1);
        dp[0]=1;
        for (const int weight : coins) {
            //  内层 for 换方向，即可变成完全背包
            for (int i = weight; i <= amount; i++) {
                //  变成求方法总数了，比较难
                dp[i] += dp[i-weight];  // 存在 +0 的可能性, 这...太迷惑了
            }
            printVector(dp);
        }
        return dp.back();
    }



    /**
     * 给定一个非空字符串 @param s 和一个包含非空单词的列表 @param wordDict，  判定：该字符串是否可以被拆分为一个或多个在字典中出现的单词。
     * @param s 非空字符串
     * @param wordDict  可以重复利用
     * @return
     *
     * 如果不调换 for 的话，把wordDict的遍历放到最外层，那么apple就无法跟在pen后面再次使用了
     * "applepenapple"
     * ["apple","pen"]
     * 就是说，它能组成appleappleapplepenpenpen，但pen后面不可能再有apple
     */
    bool wordBreak(const string& s, vector<string>& wordDict) {
        const int N = s.length();
        vector<bool> dp (N + 1);
        dp[0] = true;
        for (int i = 1; i <= N; i++) {
            for (const string& word : wordDict) {  // 涉及了顺序，因此两个for...
                const int smallLen = word.length();
                if( i>=smallLen ){
                    if(word == s.substr(i-smallLen,smallLen)){
                        dp[i] = dp[i] || dp[i-smallLen];
                        if(dp[i]){
                            break;
                        }
                    }
                }
            }
        }
        return dp[N];
    }


    /**
     * 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
     * @param nums 数组，保证unique
     * @param target 目标和
     * @return 方法数。【顺序不同的序列被视作不同的组合】
     */
    int combinationSum4(const vector<int>& nums, const int target) {
        vector<int> dp(target+1);
        dp.at(0) = 1;
        for (int i = 1; i <= target; i++) {
            for (int num : nums) {
                if( i >= num ){
                    if(INT_MAX - dp[i] < dp[i-num]){    // buggy 居然溢出了， 只能面向用例...无语。。。
                        break;
                    }
                    dp[i] += dp[i - num];       // num > 0 保证了顺序无关性？？？？？？  若允许num==0，就很恶心
                }
            }
        }
        return dp[target];
    }




    /**
     * 股票交易问题，注意区分多个状态，持仓、清仓、冷冻、当前次数(如果有次数限制的话)
     */

    /**
     * 冷冻期为1天
     * @param prices
     * @return
     */
    int maxProfit(const vector<int>& prices) {
        const int N = prices.size();
        if(!N)return 0;
        int *const buy = new int [N],   // 持仓时最大利润
            *const frozen = new int [N],// 清仓后最大利润(在冷冻期)
            *const sell = new int [N];  // 清仓后最大利润(非冷冻期)
        buy[0] = -prices.at(0);
        sell[0] = frozen[0] = 0;
        for (int i = 1; i < N; i++) {
            buy[i] = max(buy[i-1], sell[i-1]-prices.at(i));
            frozen[i] = buy[i-1]+prices.at(i);
            sell[i] = max(sell[i-1], frozen[i-1]);
        }
        return max(frozen[N-1], sell[N-1]);
    }

    /**
     * 需要手续费
     * @param prices
     * @param fee 每次【卖】需要支付的手续费. 若为0则退化成无约束
     * @return
     */
    int maxProfit(const vector<int>& prices, const int fee) {
        const int N = prices.size();
        int *const buy = new int [N],   // 持仓时最大利润
            *const sell = new int [N];  // 清仓后最大利润
        buy[0] = -prices.at(0);
        sell[0] = 0;
        for (int i = 1; i < N; i++) {
            sell[i] = max(sell[i-1], buy[i-1]+prices.at(i) - fee);
            buy[i] = max(buy[i-1], sell[i-1]-prices.at(i));
        }
        return sell[N-1];
    }


    /**
     * 限制次数
     * @param k 最多买k次
     * @param prices
     * @return
     */
    int maxProfit(int k, const vector<int>& prices) {
        const int N = prices.size();
        if( k >= N/2){  // 太简单了，不解释. 不写也是可以的
            int result = 0;
            for (int i = 1; i < N; i++) {
                if (prices[i] > prices[i - 1]) {
                    result += prices[i] - prices[i - 1];
                }
            }
            return result;
        }
        vector<int> dp(N);
        for (int i = 1; i <= k; i++) {                  // 限制最多 买卖 i 次
            int localMax =  - prices.at(0);          // 有股票在手时，最多的钱。反正就是必定有股票。可能有钱、可能没钱、可能是负数的钱
            for (int j = 1; j < N; j++) {               // 这一整个for循环，只会买卖一次股票。。。。。。？
                localMax = max(localMax, dp[j] - prices.at(j));
                dp[j] = max(dp[j - 1], localMax + prices.at(j));    // dp[]是交易正常结束后的，已经赚到钱了，即: 清仓了
            }
            printVector(dp);
        }
        return dp[N - 1];
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

    void test_canPartition(){
        canPartition({1,5,11,5});
    }

    void test_findTargetSumWays(){
        findTargetSumWays({1,1,1,1,1},3);
    }

    void test_findMaxForm(){
        cout<<findMaxForm({"10", "0001", "111001", "1", "0"},5,3);
    }

    void test_maxProfit(){
        maxProfit(2,{3,2,6,5,0,3});
    }

};
#endif //LEETCODE_DP_H
