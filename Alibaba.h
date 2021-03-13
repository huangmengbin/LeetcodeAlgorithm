//
// Created by hmb on 2021/3/12.
//

#ifndef LEETCODE_ALIBABA_H
#define LEETCODE_ALIBABA_H


#include <bits/stdc++.h>
using namespace std;

int matrix[1007][1007] = {0};


class Alibaba_Solution{


private:



    void t1_Floyd(){
        int n , m;
        cin>>n>>m;
        for(int i = 0; i<m; ++i){
            int x,y;
            cin >> x >> y;
            matrix[x][y] = 1;
        }
        //  buggy 这里要看题，是 0到n-1 还是 1到n。总之得前后对应就是了
        for(int k = 1; k<=n; k++){
            for(int i = 1; i<=n; i++){
                for(int j = 1; j<=n;++j){
                    if(matrix[i][k] and matrix[k][j]){
                        if(matrix[i][j] == 0){
                            matrix[i][j] = matrix[i][k]+matrix[k][j];
                        } else {
                            matrix[i][j] = min(matrix[i][k] + matrix[k][j], matrix[i][j]);
                        }
                    }
                }
            }
        }
    }

    void t1_bfs(){
        int n , m;
        cin>>n>>m;
        vector<set<int>> my_vector(n+7);
        for(int i = 0; i<m; ++i){
            int x,y;
            cin >> x >> y;
            my_vector.at(x).insert(y);
        }

        int q;
        cin>>q;
        for(int times = 0; times < q; times++){
            int x,y;
            cin >> x >> y;
            queue<int> my_queue;
            map<int,int> visited;
            my_queue.push(x);

            int path = 0;
            int result = -1;
            while (!my_queue.empty()){

                const int SIZE = my_queue.size();
                for(int i = 0; i< SIZE; i++){
                    const int front = my_queue.front();
                    my_queue.pop();
                    if(visited.count(front) > 0){
                        continue;
                    }
                    visited[front] = path;
                    if(front == y){
                        result = path;
                        my_queue = {};  // 退出外层循环
                        break;          // buggy 得先退出内层循环，否则，就等着出错吧
                    } else{
                        for(int num : my_vector.at(front)){
                            my_queue.push(num);
                        }
                    }
                }
                ++path;
            }
            cout<<result<<endl;

        }
    }

    void t2_Bidirectional(){
        int n,m;
        cin>>n>>m;
        unordered_map<int,int> x_to_y;
        unordered_map<int,int> y_to_x;
        for(int i = 0; i<m; ++i){
            int x,y;
            cin >> x >> y;
            if(x != y){
                x_to_y[x] = y;
                y_to_x[y] = x;
            }
        }

        int result = 0;
        for(int x = 1; x <= n; x++){
            if(x_to_y.count(x)){
                const int y = x_to_y.at(x);
                x_to_y.erase(x);
                y_to_x.erase(y);
                unordered_set<int> my_set = {x, y};
                int count = 1;
                for(int newX = y; ; ++count){
                    if(!x_to_y.count(newX)){
                        break;
                    }
                    int newY = x_to_y.at(newX);
                    my_set.insert(newY);
                    x_to_y.erase(newX);
                    y_to_x.erase(newY);
                    newX = newY;
                }
                for(int newY = x; ; ++count){
                    if(!y_to_x.count(newY)){
                        break;
                    }
                    int newX = y_to_x.at(newY);
                    my_set.insert(newX);
                    x_to_y.erase(newX);
                    y_to_x.erase(newY);
                    newY = newX;
                }


                if(my_set.size() == count){
                    result += count+1;
                } else if(my_set.size() > count) {
                    result += count;
                }
            }
        }
        cout<<result;
    }


    void t2_Unidirectional(){
        int n,m;
        cin>>n>>m;
        unordered_map<int,int> x_to_y;
        unordered_map<int,int> y_to_x;
        for(int i = 0; i<m; ++i){
            int x,y;
            cin >> x >> y;
            if(x != y){
                x_to_y[x] = y;
                y_to_x[y] = x;
            }
        }

        int result = 0;

        for(int x = 1; x <= n; x++){
            if(x_to_y.count(x) and ! y_to_x.count(x)) {
                // 表示这里是头部，因此无环
                const int y = x_to_y.at(x);
                x_to_y.erase(x);
                y_to_x.erase(y);
                int count = 1;
                for(int newX = y; ; ++count){
                    if(!x_to_y.count(newX)){
                        break;
                    }
                    int newY = x_to_y.at(newX);
                    x_to_y.erase(newX);
                    y_to_x.erase(newY);
                    newX = newY;
                }
                result += count;
            }
        }

        for(int x = 1; x <= n; x++){
            if(x_to_y.count(x)) {
                // 这里剩下来的，就只能是有环的了
                const int y = x_to_y.at(x);
                x_to_y.erase(x);
                y_to_x.erase(y);
                int count = 1;
                for(int newX = y; ; ++count){
                    if(!x_to_y.count(newX)){
                        break;
                    }
                    int newY = x_to_y.at(newX);
                    x_to_y.erase(newX);
                    y_to_x.erase(newY);
                    newX = newY;
                }
                result += count+1;
            }
        }

        cout<<result<<endl;
    }



    

public:
    void test(){
        t1_bfs();
        int T;
        cin>>T;
        for(int i = 0; i<T; ++i){
            t2_Unidirectional();
        }
    }
};


#endif //LEETCODE_ALIBABA_H
