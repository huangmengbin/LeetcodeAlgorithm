//
// Created by 13524 on 2021/2/20.
//

#ifndef LEETCODE_MY_LINKEDLIST_H
#define LEETCODE_MY_LINKEDLIST_H

#include "../../Helper.h"
class My_LinkedList{

    /**
     * 求交点, 十分巧妙，化解了差值
     * @param headA
     * @param headB
     * @return 交点
     */
    ListNode *getIntersectionNode(ListNode *const headA, ListNode *const headB) {
        ListNode *p1 = headA, *p2 = headB;
        while (p1!=p2){
            p1 = p1? p1->next : headB;
            p2 = p2? p2->next : headA;
        }
        return p1;
    }


    /**
     * 反转
     * @param head
     * @return
     */
    inline ListNode* reverseList(ListNode*const head) {
        if(!head)return head;
        ListNode *ptr2 = head->next, *ptr1 = head;
        while (ptr2){
            ListNode *ptr3 = ptr2->next;
            ptr2->next = ptr1;
            ptr1 = ptr2;
            ptr2 = ptr3;
        }
        head->next = nullptr;
        return ptr1;    // buggy 返回ptr1而不是ptr2,即:返回靠后面那个。因为 ptr2(靠前) 必定是nullptr
    }


    inline ListNode* reverseList(ListNode *const start, ListNode *const end){
        if(start== nullptr || start==end)return start;
        if(end == nullptr) return reverseList(start);
        ListNode *ptr1 = start, *ptr2 = start->next, *ptr3 = start->next->next;
        while (ptr2!=end){
            ptr2->next = ptr1;
            ptr1 = ptr2;
            ptr2 = ptr3;
            ptr3 = ptr3->next;
        }
        ptr2->next = ptr1;  //  buggy  !!!  这个不能忽视 !!!!!!  因为实际上指针修改还没完成。  当ptr2==end时，还剩最后一步。 同时小心空指针异常
        start->next = ptr3;//  这个是为外界提供方便
        return end;
    }

    /**
     * 合并有序链表
     * @param l1
     * @param l2
     * @return
     */
    ListNode* mergeTwoLists(ListNode * l1, ListNode * l2) {
        if(!l1)return l2;
        if(!l2)return l1;
        ListNode node(67666);
        ListNode * ptr = &node;
        while (l1 && l2){
            if(l1->val < l2->val){
                ptr->next = l1;
                l1 = l1->next;
            } else{
                ptr->next = l2;
                l2 = l2->next;
            }
            ptr = ptr->next;    // buggy 不要漏了步进!!!
        }
        if(!l1) ptr->next=l2;
        if(!l2) ptr->next=l1;
        return node.next;
    }


    /**
     * 有序链表, 删除重复
     * @param head
     * @return
     */
    ListNode* deleteDuplicates(ListNode *const head) {
        if(!head)return head;
        for(ListNode *ptr = head;ptr->next; ){
            if(ptr->val == ptr->next->val){
                ptr->next = ptr->next->next;
            } else{
                ptr = ptr->next;
            }
        }
        return head;
    }

    /**
     *
     * @param head
     * @param n
     * @return
     */
    ListNode* removeNthFromEnd(ListNode *const head, int n) {
        ListNode *fast = head, *slow = head;
        while (n--){
            fast = fast->next;
        }
        if(!fast){
            return slow->next;
        }
        while (fast->next){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }



    /**
     *
     * @param head
     * @return 当然是原来时候的第 k 个节点了  (从1开始数)
     */

    ListNode* reverseKGroup(ListNode *const head, const int k = 2) {
        if(k<2)return head;
        ListNode node(67666);
        node.next = head;
        ListNode *fast = &node;
        while (true) {
            ListNode *slow = fast;
            for (int i = 0; i < k; i++) {
                if(fast->next){
                    fast = fast->next;
                } else{
                    return node.next;
                }
            }
            ListNode *slow_next = slow->next;

            reverseList(slow_next, fast);

            slow->next = fast;
            fast = slow_next;
        }
    }


    /**
     * 判断链表回文，O(1)
     * @param head
     * @return
     */
    bool isPalindrome(ListNode *const head) {
        //if(!head || !head->next)return true;
        ListNode *fast = head, *slow = head;
        while (fast && fast->next){
            slow = slow->next;fast=fast->next->next;
        }
        fast = fast ? reverseList(slow,fast) : reverseList(slow);   // 利用了两种reverse
        for(slow = head; fast; slow = slow->next, fast = fast->next){
            if(fast->val!=slow->val)return false;
        }
        return true;
    }


    /**
     * 分隔链表
     * @param root
     * @param k 把链表分成k份,尽量平均一些
     * @return
     */
    vector<ListNode*> splitListToParts(ListNode *const root, const int k) {
        int N = 0;
        ListNode *ptr = root;
        while (ptr != nullptr) {
            N++;
            ptr = ptr->next;
        }
        const int mod = N % k;    //前mod个需要加一
        const int each_size = N / k;
        ptr = root;                 //  不要忘记恢复
        vector<ListNode*> result_vector;
        for(int cnt=0; cnt < k; cnt++){
            const int current_size = cnt<mod? each_size+1 : each_size;
            if(current_size == 0){
                result_vector.push_back(nullptr);
            } else{
                result_vector.push_back(ptr);
                for(int i = 1; i<current_size; i++){
                    ptr = ptr->next;
                }
                ListNode *tmp = ptr->next;
                ptr->next= nullptr;
                ptr=tmp;
            }
        }
        return result_vector;
    }


    /**
     * 链表划分 奇编号节点、偶编号节点 （从1开始计数）
     * @param head
     * @return
     */
    ListNode* oddEvenList(ListNode *const head) {
        if(!head || !head->next ||!head->next->next)return head;
        ListNode *left = head, *right = head->next, *const tmp = head->next;
        for ( ; right->next && right->next->next; left=left->next,right=right->next){
            left->next=right->next;
            right->next=right->next->next;
        }
        if(right->next == nullptr){
            left->next=tmp;
        } else{
            left->next=right->next;
            left->next->next=tmp;
            right->next= nullptr;
        }
        return head;
    }

public:
    void test_reverseKGroup(){
        ListNode *listNodes[10];
        for(int i = 1;i<=10;i++){
            listNodes[i-1] = new ListNode(i);
        }
        for(int i = 1;i<10;++i){
            listNodes[i-1]->next=listNodes[i];
        }
        reverseKGroup(listNodes[0],3);
        printListNode(listNodes[2]);
    }

};

#endif //LEETCODE_MY_LINKEDLIST_H
