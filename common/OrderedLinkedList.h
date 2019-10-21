//
// Created by lyp on 2019/9/24.
//

#ifndef DS_ORDEREDLINKEDLIST_H
#define DS_ORDEREDLINKEDLIST_H


#include <ostream>

template<class T>
class Node {
public:
    T value;
    Node *prev = nullptr;
    Node *next = nullptr;
};


template<class T>
class LinkedList {
    template<class S>
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<S> &s);

private:
    Node<T> *base = nullptr;

    void unlink(Node<T> *n);//取消某个已知结点的链接

public:
    LinkedList();

    ~LinkedList();

    void add(T item);

    bool find(const T &value) const;

    void delByElement(const T &value);

    void delSame();

};

template<class T>
void LinkedList<T>::add(T item) {
    if (base == nullptr) {
        base = new Node<T>();
        base->value = item;
        return;
    }
    auto *node = new Node<T>();
    node->value = item;
    //尝试找到要插入的位置的前一个节点
    Node<T> *nodeForInsert = nullptr;
    Node<T> *start = base;
    //从头开始遍历 直到最后一个节点跳出
    while (start == base || (start != nullptr)) {
        if (start->value <= item) {
            nodeForInsert = start;
        }
        start = start->next;
    }
    //处理需要插在链表头的情况
    if (nodeForInsert == nullptr) {
        Node<T> *tmp = base;
        base = node;
        node->next = tmp;
        tmp->prev = node;
        return;
    }
    //处理需要插在链表结尾的情况
    if (nodeForInsert->next == nullptr) {
        nodeForInsert->next = node;
        node->prev = nodeForInsert;
        return;
    }
    //插在链表中间的情况
    Node<T> *tmp = nodeForInsert->next;
    nodeForInsert->next = node;
    node->prev = nodeForInsert;
    node->next = tmp;
}

template<class T>
void LinkedList<T>::delByElement(const T &value) {
    for (Node<T> *x = base; x != nullptr; x = x->next) {
        if (value == x->value) {
            Node<T> *next = x->next;
            unlink(x);
            //处理没有到结尾的情况
            delete x;
            //先清理内存，再把下一个节点接到for循环上
            if (next != nullptr) {
                x = next;
            }
        }
    }
}


template<class T>
std::ostream &operator<<(std::ostream &out, const LinkedList<T> &s) {
    //输出链表
    Node<T> *start = s.base;
    while (start->next != nullptr) {
        out << start->value << "\n";
        start = start->next;
    }
    out << start->value << "\n";

    return out;
}

template<class T>
void LinkedList<T>::delSame() {
    Node<T> *node = base;
    while (node != nullptr) {
        //遍历完成
        if (node->next == nullptr) {
            return;
        }
        //下一个节点与本节点不等
        if (node->value != node->next->value) {
            node = node->next;
        }
        //下一个节点与本节点相等，从本节点往后遍历删除所有相同的节点
        while (node->next != nullptr && node->value == node->next->value) {
            unlink(node->next);
        }
    }

}

template<class T>
void LinkedList<T>::unlink(Node<T> *n) {
    Node<T> *next = n->next;
    Node<T> *prev = n->prev;
    if (prev == nullptr) {
        //该结点为表头的情况
        base = next;
    } else {
        //将该结点的前驱结点的后继指向该结点的后继
        prev->next = next;
    }
    if (next != nullptr) {
        //该节点不为表尾时，将该结点的下一个节点的前驱结点指向该结点的前一个结点
        next->prev = prev;
    }
    delete (n);
}

template<class T>
LinkedList<T>::LinkedList() {}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> *tmp = base;
    while (tmp != nullptr) {
        Node<T> *del = tmp;
        tmp = tmp->next;
        delete (del);
    }
    std::cout << "链表删除完成" << std::endl;
}

//在链表中查找值为value的元素是否存在
template<class T>
bool LinkedList<T>::find(const T &value) const {
    for (Node<T> *x = base; x != nullptr; x = x->next) {
        if (value == x->value) {
            std::cout << "链表中存在值为" + value + "的元素" << std::endl;
            return true;
        }
    }
    std::cout << "链表中不存在值为" + value + "的元素" << std::endl;
    return false;
}

#endif //DS_ORDEREDLINKEDLIST_H
