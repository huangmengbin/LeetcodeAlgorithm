//
// Created by 13524 on 2021/2/24.
//

#ifndef LEETCODE_MYTREE_H
#define LEETCODE_MYTREE_H

#include "../../Helper.h"

class MyTree{

public:

    /**
     *
     * 通过 lastVisit 来记忆位置。  小心continue、nullptr、3种特殊的树节点(左空、右空、左右均空)
     *
     * @param root
     * @return
     */
    vector<int> Traversal(TreeNode*const root) {
        if(!root)return{};
        stack<TreeNode*> node_stack;
        node_stack.push(root);
        TreeNode* lastVisit = root;   /// 从逻辑上来说，应该设置为它的父节点。但设置成自己，在行为上上也是一样的. 易错点是，这个永远不能是nullptr，因为有的节点左or右会为空
        vector<int> result;

        while ( ! node_stack.empty() ) {
            /*  每次push、pop都要continue. 即模拟函数的跳转 */

            TreeNode* const current = node_stack.top();

            if(lastVisit != current->left and lastVisit != current->right){ // <---不是从左右节点回来 <等价于> 从父节点过来
                ///result.push_back(current->val); /// @先序
                if(current->left != nullptr) {                              //  <--欲图遍历左树
                    node_stack.push(current->left);                         //  <--左树非空，允许遍历左树，则将其压栈
                    continue;                                               //  <--重新循环，下次循环将会从左树出发，本次遍历成功
                }
            }


            /*  如果左边是nullptr，右边非空，它确实是能够进入这里的，而且方式很...奇妙  */
            if(lastVisit != current->right){                                // <---不是从右节点回来 <等价于> 从左节点过来，或 从父节点过来但左节点为空 <等价于> 已经遍历完左子树或者遍历左子树失败 <等价于> 不再需要遍历其左子树
                ///result.push_back(current->val); /// @中序
                if(current->right != nullptr){                              //  <--欲图遍历右树
                    node_stack.push(current->right);                        //  <--右树非空，允许遍历右树，则将其压栈
                    continue;                                               //  <--重新循环，下次循环将会从右树出发，本次遍历成功
                }
            }


            ///result.push_back(current->val); /// @后序
            lastVisit = current;                                            //已经遍历完右树，或者遍历右树失败<等价于>不再需要遍历其右子树<等价于>不再需要遍历其左右子树
            node_stack.pop();                                               //此时，自身必定已完成遍历，则将其完全退出

        }
        return result;

    }




};
#endif //LEETCODE_MYTREE_H
