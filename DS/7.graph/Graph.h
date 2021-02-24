//
// Created by 13524 on 2021/2/23.
//

#ifndef LEETCODE_GRAPH_H
#define LEETCODE_GRAPH_H
#include "../../Helper.h"
class Graph{

    /**
     * 判断是否为二分图， 图已经建好，邻接表形式
     * @param graph 图，邻接表形式
     * @return
     *
     * 使用搜索即可，即判断其 是否有奇数圈。bfs和dfs都差不多。
     * 而且它是无向图，所以不会有强连通、弱连通之区别。
     * 所以非常简单，只需标记三个状态就行了
     *
     */
     void isBipartite_dfs(){

     }

    bool isBipartite(const vector<vector<int>>& graph) {

    }
};
#endif //LEETCODE_GRAPH_H
