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
    ListNode* reverseList(ListNode*const head) {
        if(!head)return head;
        ListNode *fast = head->next, *slow = head;
        while (fast){
            ListNode *tmp = fast->next;
            fast->next = slow;
            slow = fast;
            fast = tmp;
        }
        head->next = nullptr;
        return slow;    // buggy 返回slow而不是fast，因为fast必定是nullptr
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


};

#endif //LEETCODE_MY_LINKEDLIST_H
