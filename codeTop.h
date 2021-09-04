//
// Created by 13524 on 2021/3/13.
//

#ifndef LEETCODE_CODETOP_H
#define LEETCODE_CODETOP_H
#include "Helper.h"

class CodeTop{

    /**
     * LRUCache(int capacity) 以正整数作为容量capacity 初始化 LRU 缓存
     * int getOne(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
     * void put(int key, int value)如果关键字已经存在，则变更其数据值；
     *      如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间
     */
    class LRUCache {
        DoublyListNode* head = nullptr;
        DoublyListNode* tail = nullptr;
        int size = 0;
        int capacity;
        map<int,DoublyListNode*> my_map;

        void removeNode(DoublyListNode*const node){
            DoublyListNode *prev = node->prev;
            DoublyListNode *next = node->next;
            node->prev = node->next = nullptr;
            prev->next = next;
            next->prev = prev;
        }
        void addToHead(DoublyListNode*const node){
            DoublyListNode *second = head->next;
            head->next = node;
            second->prev = node;
            node->prev = head;
            node->next = second;
        }
        int removeBack(){   // 返回key，以便于map的remove
            DoublyListNode *node = tail->prev;
            assert(node != head);
            removeNode(node);
            const int key = node->key;
            delete node;
            return key;
        }
        void moveToHead(DoublyListNode*const node){
            if(head->next != node) {
                removeNode(node);
                addToHead(node);
            }
        }
    public:
        explicit LRUCache(int capacity) {
            this->capacity = capacity;
            head = new DoublyListNode();
            tail = new DoublyListNode();
            head->next = tail;
            tail->prev = head;
        }

        int get(int key) {
            if( ! my_map.count(key)){
                return -1;
            }
            DoublyListNode* result = my_map.at(key);
            moveToHead(result);
            return result->val;
        }

        void put(int key, int value) {
            if( ! my_map.count(key)){
                auto *node = new DoublyListNode(key, value);
                my_map.insert({key,node});
                addToHead(node);
                if(my_map.size() > capacity){
                    my_map.erase(removeBack() );
                }
            } else{
                auto  *node = my_map.at(key);
                node->val = value;
                moveToHead(node);
            }
        }
    };



public:
    void test_LRUCache(){
        LRUCache lRUCache(2);
        lRUCache.put(1, 1);         // 缓存是 {1=1}
        lRUCache.put(2, 2);         // 缓存是 {1=1, 2=2}
        cout<<lRUCache.get(1)<<endl;      // 返回 1
        lRUCache.put(3, 3);         // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
        cout<<lRUCache.get(2)<<endl;      // 返回 -1 (未找到)
        lRUCache.put(4, 4);         // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
        cout<<lRUCache.get(1)<<endl;      // 返回 -1 (未找到)
        cout<<lRUCache.get(3)<<endl;      // 返回 3
        cout<<lRUCache.get(4)<<endl;      // 返回 4
    }
};
#endif //LEETCODE_CODETOP_H
