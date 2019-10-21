//
// Created by lyp on 2019/9/24.
//

#ifndef DS_ORDEREDLINKEDLIST_H
#define DS_ORDEREDLINKEDLIST_H


#include <iostream>


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
    Node<T> *end = nullptr;

    void unlink(Node<T> *n);

public:

    void add(T item);

    void delByElement(const T &value);

    void delSame();

    T getMax();

    void reverse();

    void mix(LinkedList<T> B);

    int difference(LinkedList<T> B);


};


template<class T>
void LinkedList<T>::add(T item) {
    if (base == nullptr) {
        base = new Node<T>();
        end = base;
        base->value = item;
        return;
    }
    auto *node = new Node<T>();
    node->value = item;
    end->next = node;
    node->prev = end;

    end = node;
}


template<class T>
void LinkedList<T>::delByElement(const T &value) {
    for (Node<T> *x = base; x != nullptr; x = x->next) {
        if (value == x->value) {
            Node<T> *next = x->next;
            unlink(x);
            //先清理内存，再把下一个节点接到for循环上
            if (next != nullptr) {
                x = next;
            }
        }
    }
}


template<class T>
std::ostream &operator<<(std::ostream &out, const LinkedList<T> &s) {
    Node<T> *start = s.base;
    while (start != nullptr) {
        out << start->value << "\n";
        start = start->next;
    }
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

//取消某个已知结点的链接的方法
template<class T>
void LinkedList<T>::unlink(Node<T> *n) {
    Node<T> *next = n->next;
    Node<T> *prev = n->prev;
    if (prev == nullptr) {
        //该结点为表头的情况
        base = next;
    } else {
        prev->next = next;
    }
    if (next != nullptr) {
        //该节点不为表尾时，将该结点的下一个节点的前驱结点指向该结点的前一个结点
        next->prev = prev;
    }
    delete n;
}

//6.确定值最大节点
template<class T>
T LinkedList<T>::getMax() {
    //先判断该表是否为空表
    if (base == nullptr || base->next == nullptr) {
        throw std::string("This list is empty");
    }
    //max值存储，此时max以base的value初始化
    T max = base->value;
    Node<T> *start = base;
    while (start != nullptr) {
        //从表头遍历单链表
        if (start->value > max) {
            //当找到比此时的结点值大的值时，把该值赋给max
            max = start->value;
        }
        start = start->next;
    }
    return max;
}

//7.翻转链表方向，沿用原表存储空间
template<class T>
void LinkedList<T>::reverse() {
    //表为空表时，直接结束算法
    if (base == nullptr || base->next == nullptr) {
        return;
    }
    Node<T> *cnt = base;
    Node<T> *next = base->next;     //存储头结点的下一个结点
    cnt->next = nullptr;            //将头结点的后继结点置空
    end = base;                     //将头结点赋给尾结点
    //从头结点的下一个结点开始翻转方向
    while (next != nullptr) {
        Node<T> *tmp = next->next;
        next->next = cnt;
        cnt->prev = next;
        cnt = next;
        next = tmp;
    }
    base = cnt;                     //将尾结点赋给置空的头结点
    cnt->prev = nullptr;

}

//3.A和B两递增链表，求A和B交集，存储在A链表中
template<class T>
void LinkedList<T>::mix(LinkedList<T> B) {
    //取A和B的头结点
    Node<T> *startA = base, *startB = B.base;
    //遍历并比较，通过比较删除A表中与B中不同的元素
    // 直至超出其中某一链表的边界
    while (startA != nullptr && startB != nullptr) {
        if (startA->value < startB->value) {
            //A<B，则B不前进，A前进至下一个结点
            Node<T> *temp = startA->next;
            //取消此时结点的链接
            unlink(startA);
            startA = temp;
        } else if (startA->value == startB->value) {
            //A=B，各前进一个结点
            startA = startA->next;
            startB = startB->next;
        } else {
            //A>B，A不动，B前进一个结点
            startB = startB->next;
        }
    }
}

//4.A和B两递增链表，求A和B差集，返回元素个数
template<class T>
int LinkedList<T>::difference(LinkedList<T> B) {
    Node<T> *startA = base, *startB = B.base;
    //遍历并比较，通过比较删除A表中不与B中相同的元素
    // 直至超出其中某一链表的边界
    while (startA != nullptr && startB != nullptr) {
        if (startA->value < startB->value) {
            //A<B，则B不前进，A前进至下一个结点
            startA = startA->next;
        } else if (startA->value == startB->value) {
            //A=B，删除A中该结点
            Node<T> *temp = startA->next;
            //取消此时结点的链接
            unlink(startA);
            startA = temp;
        } else {
            //A>B，A不动，B前进一个结点
            startB = startB->next;
        }
    }
    //遍历比较删除后的新链表
    Node<T> *start = base;
    size_t sz = 0;
    while (start != nullptr) {
        sz++;
        start = start->next;
    }
    return sz;
}


#endif //DS_ORDEREDLINKEDLIST_H
