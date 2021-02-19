//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_SEARCH_H
#define LEETCODE_SEARCH_H
#include "../../Helper.h"
class Search{
    /**
     * DFS
     * */
    template<class T>
    void DFS(const vector<vector<T>>& grids, const int index, const int N,
             const function<bool(int,int)>& to_visit_function,
             const function<void(T)>& visiting_function,
             const function<void(int,int)>& dfs_function
             ){
        for(int i = 0; i < N; i++){
            if(to_visit_function(index,i)){
                visiting_function(grids[index][i]);
                dfs_function(index,i);
            }
        }
    }

    void findCircleNum_dfs(const vector<vector<int>>& isConnected, const int current, bool *const hasVisited, const int N){
        hasVisited[current] = true;
        for(int i = 0; i < N; i++){
            if(!hasVisited[i] && isConnected.at(current).at(i)){
                findCircleNum_dfs(isConnected,i,hasVisited,N);
            }
        }
    }

    int findCircleNum(const vector<vector<int>>& isConnected) {
        const int N = isConnected.size();
        bool* hasVisited = new bool [N];
        memset(hasVisited,0,sizeof(bool)*N);    // buggy 默认不一定会初始化的，所以要初始化
        int result = 0;
        for(int i = 0; i < N; i++){
            if(!hasVisited[i]){
                findCircleNum_dfs(isConnected, i, hasVisited, N);
                ++result;
            }
        }
        return result;
    }

    template<typename T>
    int island_dfs(const vector<vector<T>>& grid, const T ocean, const int row, const int column,
                   const int ROW, const int COLUMN,
                   const vector<pair<int,int>>& direction, vector<vector<bool>>& hasVisited){
        //  使用了hasVisited[row][column]避免重复，比较直观
        if(row<0 || column<0 || row == ROW || column == COLUMN || hasVisited[row][column]
            || ocean == grid[row][column]){ // buggy 别忘了最重要的grid数组，代表陆地与海洋.
            return 0;
        }
        hasVisited[row][column] = true;
        int result = 1;
        for(auto pii:direction){
            result+= island_dfs(grid, ocean, row + pii.first, column + pii.second, ROW, COLUMN, direction, hasVisited);
        }
        return result;
    }


    int maxAreaOfIsland(const vector<vector<int>>& grid) {
        const int ROW = grid.size(), COLUMN = grid.at(0).size();
        vector<vector<bool>> hasVisited( ROW,vector<bool>(COLUMN, false));
        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        int result = 0;
        for(int i = 0;i<ROW;i++){
            for(int j = 0;j<COLUMN;j++){
                result = max(result, island_dfs(grid,0, i, j, ROW, COLUMN, direction, hasVisited));
            }
        }
        return result;
    }

    int numIslands(const vector<vector<char>>& grid) {
        const int ROW = grid.size(), COLUMN = grid.at(0).size();
        vector<vector<bool>> hasVisited( ROW,vector<bool>(COLUMN, false));
        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        int result = 0;
        for(int i = 0;i<ROW;i++){
            for(int j = 0;j<COLUMN;j++){
                //  buggy 这里的是字符的 0 和 1， 即 ‘0’ 。 不能把它当成bool，使用简单的 ! 操作
                if(island_dfs(grid,'0', i, j, ROW, COLUMN, direction, hasVisited)){
                    ++result;
                }
            }
        }
        return result;
    }

    bool solve_dfs01(const vector<vector<char>>& board, const int row, const int column,
                     const int ROW, const int COLUMN,
                     const vector<pair<int,int>>& direction, vector<vector<bool>>& hasVisited){
        if(row<0 || column<0 || row == ROW || column == COLUMN){
            return false;
        }
        if(hasVisited[row][column] || board[row][column]=='X'){
            return true;
        }
        hasVisited[row][column] = true;
        bool result = true;
        for(auto pii:direction){
            result &= solve_dfs01(board, row + pii.first, column + pii.second, ROW, COLUMN, direction, hasVisited);
        }
        return result;
    }

    void solve_dfs01(vector<vector<char>>& board, const int row, const int column,
                     const int ROW, const int COLUMN,
                     const vector<pair<int,int>>& direction){
        //  board[row][column] == 'X' 与下面照应，避免重复遍历。
        if(row<0 || column<0 || row == ROW || column == COLUMN || board[row][column] == 'X'){
            return ;
        }
        board[row][column] = 'X';
        for(auto pii:direction){
            solve_dfs01(board, row + pii.first, column + pii.second, ROW, COLUMN, direction);
        }
    }

    void solve01(vector<vector<char>>& board) {
        const int ROW = board.size();
        if(ROW==0) return;      // buggy 防止下面那一行溢出
        const int COLUMN = board.at(0).size();
        vector<vector<bool>> hasVisited( ROW,vector<bool>(COLUMN, false));
        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        for(int i = 0;i<ROW;i++){
            for(int j = 0;j<COLUMN;j++){
                //  buggy 这个 !hasVisited[i][j] && 拥有至高无上的优先级，不能遗漏
                if(!hasVisited[i][j] && solve_dfs01(board, i, j, ROW, COLUMN, direction, hasVisited)){
                    solve_dfs01(board, i, j, ROW, COLUMN, direction);
                }
            }
        }
    }

    void solve_dfs02(vector<vector<char>>& board, const int row, const int column,
                     const int ROW, const int COLUMN, const vector<pair<int,int>>& direction) {
        //  board[row][column] != 'O' 与下面照应，避免重复遍历。  主要是这里为了偷懒，未使用 hasVisited 数组。
        if(row<0 || column<0 || row == ROW || column == COLUMN || board[row][column] != 'O'){
            return ;
        }
        board[row][column] = ' ';
        for(auto pii:direction){
            solve_dfs02(board, row + pii.first, column + pii.second, ROW, COLUMN, direction);
        }
    }
    //巧妙的方法，从外到内的逆向思维
    void solve02(vector<vector<char>>& board){
        const int ROW = board.size();
        if(ROW==0) return;
        const int COLUMN = board.at(0).size();
        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        for(int i = 0; i < ROW; i++){
            solve_dfs02(board, i, 0, ROW, COLUMN, direction);
            solve_dfs02(board, i, COLUMN - 1, ROW, COLUMN, direction);
        }
        for(int j = 0; j < COLUMN; j++){
            solve_dfs02(board, 0, j, ROW, COLUMN, direction);
            solve_dfs02(board, ROW - 1, j, ROW, COLUMN, direction);
        }
        for(int i = 0;i<ROW;i++){
            for(int j = 0;j<COLUMN;j++){
                if(board[i][j]=='O'){
                    board[i][j]='X';
                }
                else if(board[i][j]==' '){
                    board[i][j]='O';
                }
            }
        }
    }

    void pacificAtlantic_dfs(const vector<vector<int>>& matrix,const int row, const int column,
                             const int ROW, const int COLUMN, const vector<pair<int,int>>& direction,
                             vector<vector<bool>>& reached, int historyHeight) {
        //  matrix.at(row).at(column) < historyHeight 是 题意的逻辑
        if(row<0 || column<0 || row == ROW || column == COLUMN || reached[row][column] || matrix.at(row).at(column) < historyHeight){
            return ;
        }
        const int HEIGHT = matrix.at(row).at(column);
        reached[row][column] = true;
        for(auto pii:direction){
            pacificAtlantic_dfs(matrix, row + pii.first, column + pii.second, ROW, COLUMN, direction,reached,HEIGHT);
        }
    }

    vector<vector<int>> pacificAtlantic(const vector<vector<int>>& matrix) {
        vector<vector<int>> result;
        const int ROW = matrix.size();
        if(ROW==0) return result;
        const int COLUMN = matrix.at(0).size();
        if(COLUMN==0) return result;

        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        vector<vector<bool>> up_left(ROW,vector<bool>(COLUMN,false));
        vector<vector<bool>> down_right(ROW,vector<bool>(COLUMN,false));

        for(int i = 0; i < ROW; i++){
            pacificAtlantic_dfs(matrix, i, 0, ROW, COLUMN, direction, up_left,matrix[i][0]);
            pacificAtlantic_dfs(matrix, i, COLUMN - 1, ROW, COLUMN, direction, down_right,matrix[i][COLUMN - 1]);
        }
        for(int j = 0; j < COLUMN; j++){
            pacificAtlantic_dfs(matrix, 0, j, ROW, COLUMN, direction, up_left,matrix[0][j]);
            pacificAtlantic_dfs(matrix, ROW - 1, j, ROW, COLUMN, direction, down_right,matrix[ROW-1][j]);
        }

        for(int i = 0;i<ROW;i++){
            for(int j = 0;j<COLUMN;j++){
                if(up_left.at(i).at(j) && down_right.at(i).at(j)){
                    result.push_back({i,j});
                }
            }
        }
        return result;
    }





    /**
     * BFS
     * */

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        const int ROW = grid.size();
        if(ROW==0) return 0;
        const int COLUMN = grid.at(0).size();
        if(COLUMN==0) return 0;
        const vector<pair<int,int>>& directions = {
                {0,1},{1,0},{0,-1},{-1,0},
                {1,1},{1,-1},{-1,1},{-1,-1}
        };
        queue<pair<int,int>> q1;
        queue<pair<int,int>> q2;
        queue<pair<int,int>>* q1_ptr = &q1;
        queue<pair<int,int>>* q2_ptr = &q2;
        q1.push({0,0});
        int result = 0;
        while (!q1_ptr->empty()){
            while (!q1_ptr->empty()){
                const auto pii = q1_ptr->front();
                q1_ptr->pop();
                if(pii.first<0 || pii.first==ROW || pii.second < 0 || pii.second == COLUMN || grid[pii.first][pii.second]){
                    continue;
                }
                grid[pii.first][pii.second] = 2;
                if(pii.first == ROW-1 && pii.second == COLUMN-1){
                    return result;
                }
                for(const auto direction:directions){
                    q2_ptr->push({pii.first+direction.first,pii.second+direction.second});
                }
            }
            swap(q1_ptr,q2_ptr);
            ++result;
        }
        return -1;
    }

    int numSquares(const int N) {
        const int sq = ceil(sqrt(N));
        int *const square = new int [sq + 1]{0};
        for(int i=1; i <= sq; i++) square[i] = i * i;
        bool *const hasVisited = new bool [N+1];
        memset(hasVisited,0,(N+1) * sizeof (bool));
        queue<int> queue_int;
        queue_int.push(N);
        int result = 1;
        while (true){
            for(int SIZE = queue_int.size();SIZE>0;--SIZE){
                const int item = queue_int.front();queue_int.pop();
                hasVisited[item] = true;
                for(int i=1; i <= sq; i++) {
                    const int new_item = item - square[i];
                    if(new_item<0){
                        break;
                    } else if(new_item==0){
                        return result;
                    } else if(hasVisited[new_item]){
                        continue;
                    } else{
                        queue_int.push(new_item);
                    }
                }
            }
            ++result;
        }
    }



    int ladderLength(const string& beginWord, const string& endWord, vector<string>& wordList) {
        wordList.push_back(beginWord);
        const int N = (int)wordList.size();
        unordered_map<string,int> wordMap;
        for(unsigned i=0; i<N ;i++) {
            wordMap[wordList.at(i)] = i;
        }
        if(!wordMap.count(endWord)){
            return -0;
        }

        // 巧妙的建图方法，利用了“小写字母数量有限”和“字符串长度较短”，但还有更巧妙的，虚拟节点避免字符类型过多 ******* ...
        vector<vector<int>> grids(N,vector<int>{});
        for(const string& old_str : wordList){
            for(unsigned i = 0; i < old_str.size(); i++){
                for(char ch = 'a'; ch <= 'z'; ch++){
                    if(ch != old_str.at(i)){
                        string new_str = old_str;
                        new_str.at(i) = ch;
                        if(wordMap.count(new_str)){
                            grids.at(wordMap.at(old_str)).push_back(wordMap.at(new_str));
                        }
                    }
                }
            }
        }
        vector<char> hasVisited(N,0);
        queue<int> q_begin, q_end;
        q_begin.push(wordMap.at(beginWord));
        q_end.push(wordMap.at(endWord));    // buggy  endWord 不一定有, 必须提前判断，return 0
        int result = 0;
        queue<int>* queue_ptr = &q_begin;
        while (!q_begin.empty() && !q_end.empty()){
            for(int CURRENT_SIZE = queue_ptr->size(); CURRENT_SIZE >0; CURRENT_SIZE--){
                const int ptr = queue_ptr->front();
                queue_ptr->pop();
                if(hasVisited.at(ptr) == 1){
                    continue;
                } else if(hasVisited.at(ptr) == 2){
                    return result;
                } else{
                    hasVisited.at(ptr) = 1;
                    for(const int next: grids.at(ptr)){
                        queue_ptr->push(next);
                    }
                }
            }
            result ++;
            for(int CURRENT_SIZE = q_end.size(); CURRENT_SIZE >0; CURRENT_SIZE--){
                const int ptr = q_end.front();
                q_end.pop();
                if(hasVisited.at(ptr) == 2){
                    continue;
                } else if(hasVisited.at(ptr) == 1){
                    return result;
                } else{
                    hasVisited.at(ptr) = 2;
                    for(const int next: grids.at(ptr)){
                        q_end.push(next);
                    }
                }
            }
            result ++;
        }
        return -0;
    }

    /**
     *    Backtracking
     *
     * */

    // 用其他方法存储字符串(中间结果)，以减少不必要的变量拷贝，提升时空效率

     void letterCombinationsBacktracking(const string& digits, const unsigned ptr, const string stringList[], string& currentString, vector<string>& result){
         if(ptr == digits.size()){
             if(!currentString.empty()){
                 result.push_back(currentString);
             }
             return;
         }
         const string next_str = stringList[digits.at(ptr)-'2'];
         for(const char next_char:next_str){
             currentString.push_back(next_char);    //对称
             letterCombinationsBacktracking(digits,ptr+1,stringList,currentString,result);
             currentString.pop_back();              //对称
         }
     }

    vector<string> letterCombinations(const string& digits) {
        const string stringList[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        string s;
        letterCombinationsBacktracking(digits,0,stringList,s,result);
        return result;
    }


    void binaryTreePathsBacktracking(const TreeNode* father, vector<string>& result, string & currentString) {
        if(father->left){
            string next = "->"+to_string(father->left->val);
            currentString.append(next);
            binaryTreePathsBacktracking(father->left,result,currentString);
            currentString.erase(currentString.size()-next.size());
        }
        if(father->right){
            string next = "->"+to_string(father->right->val);
            currentString.append(next);
            binaryTreePathsBacktracking(father->right,result,currentString);
            currentString.erase(currentString.size()-next.size());
        } else if(!father->left){
            result.push_back(currentString);
        }
    }

    vector<string> binaryTreePaths(const TreeNode* root) {
        vector<string> result;
        if(root) {
            string s = to_string(root->val);
            binaryTreePathsBacktracking(root, result, s);
        }
        return result;
    }



    void restoreIpAddressesBacktracking(const string& NUMBER_STR, vector<string> & result, unsigned index, vector<unsigned>& current) {
         if(index == NUMBER_STR.size()){
             if(current.size() == 4){
                 string s;
                 s.append(to_string(current.at(0))).append(".");
                 s.append(to_string(current.at(1))).append(".");
                 s.append(to_string(current.at(2))).append(".");
                 s.append(to_string(current.at(3)));
                 result.push_back(s);
             }
             return;
         }
        if(current.size()==4)  return;   // 避免傻逼用例

         for( unsigned i = index; i<NUMBER_STR.size();++i){
             unsigned number = stoul(NUMBER_STR.substr(index,i+1-index));
             if(number<256){
                 current.push_back(number);
                 restoreIpAddressesBacktracking(NUMBER_STR, result, i+1, current);
                 current.pop_back();
             } else{
                 break;
             }

             if(number == 0){  //  buggy 不应该是 NUMBER_STR.at(i) == '0' , 避免出现 10，20 这类被打断
                break;
             }
        }
    }

    vector<string> restoreIpAddresses(const string& NUMBER_STR) {
        vector<string> result;
        vector<unsigned> current;
        restoreIpAddressesBacktracking(NUMBER_STR, result, 0, current);
        return result;
    }





    bool existBacktracking(vector<vector<char>>& board, const string& word, int row, int column, int ROW, int COLUMN, const unsigned index, const vector<pair<int,int>>& directions) {
         if(index == word.size()){
             return true;
         }
         if(row<0 || column <0 || row ==ROW || column==COLUMN){
             return false;
         }
         const char ch = board.at(row).at(column);
         if(word.at(index) == ch){
             board.at(row).at(column) = '\0';   // 对称，避免重复遍历
             for(auto direction : directions){
                 if(existBacktracking(board,word, row+direction.first, column+direction.second, ROW, COLUMN, index+1, directions)){
                     return true;
                 }
             }
             board.at(row).at(column) = ch;     // 对称，避免重复遍历
         }
        return false;
    }

    bool exist(vector<vector<char>>& board, const string& word) {
        const int ROW = board.size(), COLUMN = board.at(0).size();
        const vector<pair<int,int>>& direction = {{0,1},{1,0},{0,-1},{-1,0}};
        for(int row = 0; row < ROW; row++){
            for(int column = 0; column < COLUMN; column ++){
                if(existBacktracking(board,word,row,column,ROW,COLUMN,0, direction)){
                    return true;
                }
            }
        }
        return false;
    }

    inline bool isPalindrome(const string& s, unsigned begin, unsigned end){
        while ( begin < end ) {
            if(s.at(begin) != s.at(end)){
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
    void partitionBacktracking(const string& s, vector<vector<string>> & res, vector<string>& current, const unsigned index){
         if(index == s.size()){
            res.push_back(current);
         }
         for(unsigned i=index;i<s.size();i++){
            if(isPalindrome(s,index,i)){
                current.push_back(s.substr(index,1+i-index));
                partitionBacktracking(s,res,current,i+1);
                current.pop_back();
            }
//            else{
//                break;        // buggy  不应该break，这里没有那种传递的关系。比如 12321 ， 前面部分非回文无法判断整体性质
//            }
         }
     }

    vector<vector<string>> partition(const string& s) {
        vector<vector<string>> res;
        vector<string> current;
        partitionBacktracking(s,res,current,0);
        return res;
    }

    /**
     * 排列、组合、子集
     */

    /**
     * 排列
     */
    void permuteBacktracking(const vector<int>& nums, vector<vector<int>>& result, vector<bool>& hasVisited, vector<int>& current) {
        if(current.size() == nums.size()){
            result.push_back(current);
            return;
        }
        for(unsigned i = 0; i< nums.size(); i++){
            if(!hasVisited.at(i)){
                hasVisited.at(i) = true;
                current.push_back(nums.at(i));
                permuteBacktracking(nums, result, hasVisited, current);
                current.pop_back();
                hasVisited.at(i) = false;
            }
        }
    }


    vector<vector<int>> permute(const vector<int>& nums) {
        vector<vector<int>> result;
        vector<bool> hasVisited(nums.size(), false);
        vector<int> cur;
        permuteBacktracking(nums, result, hasVisited, cur);
        return result;
    }




    void permuteUniqueBacktracking(const vector<int>& nums, vector<vector<int>>& result, vector<bool>& hasVisited, vector<int>& current) {
        if(current.size() == nums.size()){
            result.push_back(current);
            return;
        }
        int history = -6766666;
        for(unsigned i = 0; i< nums.size(); i++){
            if(!hasVisited.at(i)){
                if(history == nums.at(i)){
                    continue;       //  只需避免和上一次的重复，即可
                }
                history = nums.at(i);
                hasVisited.at(i) = true;
                current.push_back(nums.at(i));
                permuteUniqueBacktracking(nums, result, hasVisited, current);
                current.pop_back();
                hasVisited.at(i) = false;
            }
        }
    }


    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<bool> hasVisited(nums.size(), false);
        vector<int> cur;
        permuteUniqueBacktracking(nums, result, hasVisited, cur);
        return result;
    }


    void combineBacktracking(const int N, const int K, int n, int k, vector<vector<int>> &result, vector<int>& current) {
        if(k == K){
            result.push_back(current);
            return;
        }
        for(int i = n; i <= N; i++){
            current.push_back(i);
            combineBacktracking(N, K, i + 1, k + 1, result, current);
            current.pop_back();
        }
    }
    vector<vector<int>> combine(const int N, const int K) {
        vector<vector<int>> result;
        vector<int> current;
        combineBacktracking(N, K, 1, 0, result, current);
        return result;
    }


    void combinationSumBacktracking1(unsigned index, const vector<int>& candidates, const int target, const int currentSum, vector<vector<int>> &result, vector<int>& current) {
        if(currentSum >= target){
            if(currentSum == target){
                result.push_back(current);
            }
            return;
        }
        //  buggy .允许无限制重复选取某一个元素，但不允许重复的组合
        for(unsigned i = index, SIZE = candidates.size(); i<SIZE; i++){
            const int candidate = candidates.at(i);
            current.push_back(candidate);
            //  buggy  递归不是用 index, 更不是 index+1, 而是 当前的 i；这样才能避免重复组合，同时重复选取
            combinationSumBacktracking1(i, candidates, target, currentSum + candidate, result, current);
            current.pop_back();
        }
    }
    vector<vector<int>> combinationSum1(const vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        combinationSumBacktracking1(0, candidates, target, 0, result, current);
        return result;
    }


    void combinationSumBacktracking2(unsigned index, const vector<int>& candidates, const int target, const int currentSum, vector<vector<int>> &result, vector<int>& current) {
        if(currentSum >= target){
            if(currentSum == target){
                result.push_back(current);
            }
            return;
        }
        int history = -6766666;
        for(unsigned i = index, SIZE = candidates.size(); i<SIZE; i++){
            const int candidate = candidates.at(i);
            if(history == candidate){
                continue;
            }
            history = candidate;
            current.push_back(candidate);
            combinationSumBacktracking2(1+i, candidates, target, currentSum + candidate, result, current);
            current.pop_back();
        }
    }
    //  buggy  题目说的是对组合(最终结果)去重，而不是对求结果时对里面的元素去重。因此方法仍然是先排序、引入history记录
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        sort(candidates.begin(), candidates.end());
        combinationSumBacktracking2(0, candidates, target, 0, result, current);
        return result;
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        auto tmp = combine(9,k);
        // v in tmp ， 因为 tmp 才有点东西， res 是空的
        for(auto& v : tmp){
            int sum = 0;
            for(auto i : v){
                sum += i;
            }
            if(sum == n){
                res.push_back(v);
            }
        }
        return res;
    }


    /**
     * 子集(幂集)
     */

    void subsetsBacktracking(const vector<int>& nums, vector<vector<int>> &result, vector<int>& current, unsigned index){
        if(index == nums.size()){
            result.push_back(current);
            return;
        }
        // 幂集 与 排列 不一样， 不需要 for 循环。 而是每次进行2种分支，选它 or 不选
        current.push_back(nums.at(index));
        subsetsBacktracking(nums,result,current,index+1);
        current.pop_back();
        subsetsBacktracking(nums,result,current,index+1);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        /// sort(nums.begin(), nums.end());
        subsetsBacktracking(nums,result,current,0);
        return result;
    }


    void subsetsWithDupBacktracking(const vector<int>& nums, vector<vector<int>> &result, vector<int>& current, unsigned index,const bool selected){
        if(index == nums.size()){
            result.push_back(current);
            return;
        }

        current.push_back(nums.at(index));
        subsetsWithDupBacktracking(nums, result, current, index + 1, true);
        current.pop_back();

        // 奇妙的剪枝，如果上次选了，且重复，那这次就必须要选了，不能不选。
        // 这个相等是可以传递很远的
        if( selected && nums.at(index) == nums.at(index - 1)){
            return;
        }
        subsetsWithDupBacktracking(nums, result, current, index + 1, false);

    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        sort(nums.begin(), nums.end());        ///
        subsetsWithDupBacktracking(nums, result, current, 0, false);
        return result;
    }


public:
    void test_findCircleNum(){
        cout<<findCircleNum({{1,1,0,0},{1,1,0,0},{0,0,1,0},{0,0,0,1}})<<endl;
    }
    void test_maxAreaOfIsland(){
        cout<<maxAreaOfIsland({
                                      {0,0,1,0,0,0,0,1,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,1,1,1,0,0,0},
                                      {0,1,1,0,1,0,0,0,0,0,0,0,0},
                                      {0,1,0,0,1,1,0,0,1,0,1,0,0},
                                      {0,1,0,0,1,1,0,0,1,1,1,0,0},
                                      {0,0,0,0,0,0,0,0,0,0,1,0,0},
                                      {0,0,0,0,0,0,0,1,1,1,0,0,0},
                                      {0,0,0,0,0,0,0,1,1,0,0,0,0}
        });
    }
    void test_numIslands(){
        cout<<numIslands({
                                 {'1','1','0','0','0'},
                                 {'1','1','0','0','0'},
                                 {'0','0','1','0','0'},
                                 {'0','0','0','1','1'}
        }
        );
    }
    void test_solve(){
        vector<vector<char>> v = {
                {'X','X','X','X'},
                {'X','O','O','X'},
                {'X','X','O','X'},
                {'X','O','X','X'},
        };
        solve02(v);
        printVectorVector(v);
    }
    void test_pacificAtlantic(){
        printVectorVector(pacificAtlantic({{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4},}));
    }

    void test_ladderLength(){
        vector<string> v = {"hot","dot","dog","lot","log","cog"};
        cout<<ladderLength("hit","hot",v);
    }

    void test_permute(){
        printVectorVector(permute({1,2,3}));
    }

    void test_combinationSum3(){
        printVectorVector(combinationSum3(3,7));
    }

};

#endif //LEETCODE_SEARCH_H
