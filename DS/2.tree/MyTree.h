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




    /**
     * 翻转二叉树，它让我想起了Google...
     * @param root
     * @return
     */
    TreeNode* invertTree(TreeNode* root) {
        swap(root->left, root->right);
        if(root->left)invertTree(root->left);
        if(root->right)invertTree(root->right);
        return root;
    }


    /**
     * 合并两个二叉树。相同部位，值加起来就行
     * @param root1
     * @param root2
     * @return
     */
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(!root1 and !root2) return nullptr;
        if(!root1) return root2;
        if(!root2) return root1;
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }


    /**
     * 从根节点到叶子节点，给定路径长度
     * @param root
     * @param targetSum
     * @return
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root){
            return false;
        }
        targetSum -= root->val;
        return !root->left and !root->right and targetSum == 0 or hasPathSum(root->left, targetSum) or hasPathSum(root->right, targetSum);
    }


    /**
     *
     * 求满足路径长度的 路径 的 总条数
     * 路径不一定以 root 开头，也不一定以 leaf 结尾，但是必须连续。
     *
     * @param root
     * @param sum
     * @return
     */
    int pathSum(TreeNode* root, unordered_map<int,int>& myMap, int currentSum, const int targetSum){
        if(! root){
            return 0;
        }
        int result = 0;
        currentSum += root->val;
        result += myMap[currentSum - targetSum];
        //  buggy  currentSum是从根节点加到这里，是最"大"的东西。因此是用它减去targetSum，代表此处作为路径终点，从map里面寻找起点的个数
        myMap[currentSum]++;
        result += pathSum(root->left, myMap, currentSum, targetSum);
        result += pathSum(root->right, myMap, currentSum, targetSum);
        myMap[currentSum]--;
        return result;
    }

    int pathSum(TreeNode* root, int sum) {
        unordered_map<int,int> myMap;
        myMap[0]=1;
        return pathSum(root, myMap, 0, sum);
    }




    /**
     * 给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。
     * 更正式地说，root.val = min(root.left.val, root.right.val) 总成立。
     * 给出这样的一个二叉树，你需要输出所有节点中的第二小的值。如果第二小的值不存在的话，输出 -1 。（unique后的第二小）
     *
     * 实际上，它是一个 “堆”
     * 只需要求出，【除当前顶部之外】的最小值
     *
     * @param root
     * @return
     */
    int findSecondMinimumValue_01(TreeNode* root) {
        if(!root or root->left == nullptr or root->right == nullptr) {
            return -1;
        }
        int leftVal = root->left->val == root->val ? findSecondMinimumValue_01(root->left) : root->left->val;
        int rightVal = root->right->val == root->val ? findSecondMinimumValue_01(root->right) : root->right->val;
        if(leftVal == root->val and rightVal == root->val){    // buggy   小心根节点是 1 , 左边右边都是3, 所以不能写 leftVal == rightVal
            return -1;
        }
        if(leftVal == -1){
            return rightVal;
        }
        if(rightVal == -1){
            return leftVal;
        }
        return min(leftVal, rightVal);
    }



    /**
     * 在内层，不妨把 -1 暂时转化掉。因为 -1 太小了，还要特判
     * @param root
     * @param ERROR
     * @return
     */
    long long findSecondMinimumValue_02(TreeNode* root, const long long  ERROR = -1) {
        if(!root or root->left == nullptr or root->right == nullptr) {
            return ERROR;
        }
        long long leftVal = root->left->val == root->val ? findSecondMinimumValue_02(root->left, LONG_LONG_MAX) : root->left->val;
        long long rightVal = root->right->val == root->val ? findSecondMinimumValue_02(root->right, LONG_LONG_MAX) : root->right->val;
        if(leftVal == root->val and rightVal == root->val){
            return ERROR;
        }
        long long res = min(leftVal, rightVal);
        return res == LONG_LONG_MAX ? ERROR : res;          //  这个东西最外层才有用，目的是为了把它强行转成-1
    }


    /**
     *
     * @param big
     * @param small
     * @return
     */
    bool isSubtree(TreeNode* big, TreeNode* small) {
        if(big == nullptr and small == nullptr){
            return true;
        }
        if(big == nullptr or small == nullptr){
            return false;
        }
        // buggy 小心这里 isSameTree 和 isSubtree 的细节
        return (big->val == small->val and isSameTree(big->left, small->left) and isSameTree(big->right, small->right))
            or (isSubtree(big->left, small) or isSubtree(big->right, small));
    }

    bool isSameTree(TreeNode* big, TreeNode* small) {
        if(big == nullptr and small == nullptr){
            return true;
        }
        if(big == nullptr or small == nullptr){
            return false;
        }
        if(big->val != small->val){
            return false;
        }
        return (isSameTree(big->left, small->left) and isSameTree(big->right, small->right));
    }


    /**
     * 最长同值路径
     * @param root
     * @return
     */
    int longestUnivaluePath(TreeNode* root) {
        int longestPath = 0;
        longestUnivaluePathRecursive(root, longestPath);
        return longestPath;
    }

    int longestUnivaluePathRecursive(TreeNode *root, int & longestPath){
        if(root == nullptr)  return 0;
        int leftResult = longestUnivaluePathRecursive(root->left, longestPath);             // 与本节点断开的最大高度
        int rightResult = longestUnivaluePathRecursive(root->right, longestPath);
        //  buggy 即使是该处(暂时)不符合，函数也是要算的。  实际上，只需不为nullptr就得算子节点，如果本节点值等于子节点的值就得拼接起来
        int leftHeight = root->left and root->val == root->left->val ? 1+leftResult : 0;        // 与本节点连接的最大高度
        int rightHeight = root->right and root->val == root->right->val ? 1+rightResult : 0;
        longestPath = max(longestPath, leftHeight+rightHeight);
        return max(leftHeight, rightHeight);
    }


    /**
     * 不能抢劫相邻的两间房子
     * @param root
     * @return
     */
    int rob(TreeNode* root) {
        return rob_pii(root).first;
    }

    /**
     * 用于辅助, 把递归法 搞成 和dp一样的复杂度
     * @param root
     * @return {允许使用当前 , 不允许使用当前}
     */
    pair<int,int> rob_pii(TreeNode* root) {
        if(!root){
            return {0, 0};
        }
        int canUseCurrent = root->val;
        int notUseCurrent = 0;
        pair<int,int> leftResult = rob_pii(root->left);
        pair<int,int> rightResult = rob_pii(root->right);
        notUseCurrent += leftResult.first + rightResult.first;
        canUseCurrent += leftResult.second + rightResult.second;
        canUseCurrent = max(canUseCurrent, notUseCurrent);
        return {canUseCurrent, notUseCurrent};
    }

    /**
     * 每层的均值，小心溢出，记得提前用double
     * @param root
     * @return
     */
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> myQueue;
        myQueue.push(root);
        vector<double> result;
        while ( ! myQueue.empty() ){
            const int SIZE = myQueue.size();
            double total = 0;
            for(int i = 0; i < SIZE; i++){
                TreeNode * current = myQueue.front();
                total += current->val;
                myQueue.pop();
                if(current->left)myQueue.push(current->left);
                if(current->right)myQueue.push(current->right);
            }
            result.push_back(total / SIZE);
        }
        return result;
    }

    /**
     * 左下角的val
     * @param root
     * @return
     */
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> myQueue;
        myQueue.push(root);
        int result;
        while ( ! myQueue.empty() ){
            const int SIZE = myQueue.size();
            result = myQueue.front()->val;
            for(int i = 0; i < SIZE; i++){
                TreeNode * current = myQueue.front();
                myQueue.pop();
                if(current->left)myQueue.push(current->left);
                if(current->right)myQueue.push(current->right);
            }
        }
        return result;
    }



    /**
     * BST, binary search tree, 二叉搜索树。
     * 即中序遍历有序, 单调非递减
     */



};
#endif //LEETCODE_MYTREE_H
