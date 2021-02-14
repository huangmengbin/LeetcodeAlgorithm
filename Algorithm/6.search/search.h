//
// Created by 13524 on 2021/2/10.
//

#ifndef LEETCODE_SEARCH_H
#define LEETCODE_SEARCH_H
#include "../../Helper.h"
class Search{
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
};

#endif //LEETCODE_SEARCH_H
