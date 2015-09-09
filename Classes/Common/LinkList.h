//
//  LinkList.h
//  StarCowboy
//
//  Created by match5 on 15/8/14.
//
//

#ifndef __LinkList_h__
#define __LinkList_h__

#include "Allocator.h"

template <class T>
class LinkList {
    
public:
    
    template <class __T>
    class __Node {
        friend class LinkList;
    public:
        Node (T& d)
        :data(d){}
        T     data;
    protected:
        Node* next = nullptr;
    };
    
    operator bool() {
        return _list != nullptr;
    }
    
    void push(T& data) {
        Node* newHead = New(Node, data);
        newHead->next = _list;
        _list = newHead;
    }
    
    T pop() {
        T rt = _list->data;
        __Node* newHead = _list->next;
        Delete(_list);
        _list = newHead;
    }
    
    void clear() {
        __Node* n = _list;
        while (n != nullptr) {
            _list = n->next;
            Delete(n);
            n = _list;
        }
    }
    
    void remove(T& data, bool all = false) {
        if (_list) {
            if (_list->data == data) {
                pop();
            }
            __Node *n1 = _list;
            __Node *n2 = _list->next;
            for (; n2 != nullptr; n1 = n1->next, n2 = n2->next) {
                if (n2->data == data) {
                    n1->next = n2->next;
                    Delete(n2);
                    n2 = n1->next;
                    if (!all) {
                        break;
                    }
                }
            }
        }
    }
    
    __Node* find(T& data) {
        if (_list && _list->data == data) {
            return _list;
        }
        return findNext(_list, data);
    }
    
    __Node* findNext(Node* n, T& data) {
        Node *n2 = n->next;
        for (; n2 != nullptr; n2 = n2->next) {
            if (n2->data == data) {
                return n2;
            }
        }
        return nullptr;
    }
    
private:
    
    __Node<T>* _list;
};

#endif
