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
     bool isBipartite_dfs(const vector<vector<int>>& graph, const int currentIndex, const int currentState, vector<short>& state){
         const vector<int>& next = graph.at(currentIndex);
         state[currentIndex] = currentState;                    //  buggy 不要忘记修改 当前正在遍历的节点的状态
         for(int nextIndex:next){
             if( 0 == state.at(nextIndex)){
                 if( ! isBipartite_dfs(graph, nextIndex, -currentState, state)){
                     return false;
                 }
             } else if(currentState == state.at(nextIndex)){    //  同色当然不行，所以是 ==
                 return false;
             }
         }
         return true;
     }

    bool isBipartite_using_dfs(const vector<vector<int>>& graph) {
        vector<short> state(graph.size());
        for(int i = 0; i<graph.size(); i++){
            if( 0 == state.at(i) ){
                if( ! isBipartite_dfs(graph, i, 1, state) ){
                    return false;
                }
            }
        }
        return true;
    }


    /**
     * 使用并查集的方法
     * @param graph
     * @return
     */
    bool isBipartite(const vector<vector<int>>& graph) {
        UnionSet unionSet(graph.size());
        for(unsigned index = 0; index < graph.size(); index++){
            const vector<int>& next = graph.at(index);
            for(const int nextIndex: next){
                if(unionSet.isConnected((int)index, nextIndex)){
                    return false;
                }
            }
            for(const int nextIndex: next){
                unionSet.merge(next.front(), nextIndex);
            }
        }
        return true;
    }


    vector<int> findRedundantConnection(const vector<vector<int>>& edges) {
        UnionSet unionSet((int)edges.size()+1);    //   buggy  范围是 1~N ， 因此需要多给他一个冗余空间
        for(auto & edge : edges){
            if( ! unionSet.tryToMerge(edge.at(0), edge.at(1)) ){
                return edge;
            }
        }
    }




};
#endif //LEETCODE_GRAPH_H
