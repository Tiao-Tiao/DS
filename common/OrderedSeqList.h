//
// Created by lyp on 2019/10/9.
//

#ifndef DS_ORDEREDSEQLIST_H
#define DS_ORDEREDSEQLIST_H

#include <iostream>

template<class T>
class OrderedSeqList {
    template<class S>
    friend std::ostream &operator<<(std::ostream &os, const OrderedSeqList<S> &s);

private:

    //逻辑容器长度
    int length;
    //最大容器长度
    int size;
    int DEFAULT_CAPACITY = 10;
    T *base;

    void ensureCapacity(int minCapacity);

public:
    OrderedSeqList();

    ~OrderedSeqList();

    void add(T item);

    void insert(int index, T item);

    void del(int index);

    T get(int index) const;

    void delByElement(const T &item);

    void delSame();
};

//构造函数，对顺序表进行初始化
template<class T>
OrderedSeqList<T>::OrderedSeqList() {
    base = (T *) malloc(sizeof(T) * DEFAULT_CAPACITY);
    size = DEFAULT_CAPACITY;
    length = 0;
}

template<class T>
OrderedSeqList<T>::~OrderedSeqList() {
    if(base){
        delete[] base;
    }
}

/**
 * 扩容
 * @param minCapacity 该线性表应有的最小容量
 */
template<class T>
void OrderedSeqList<T>::ensureCapacity(int minCapacity) {
    if (size == DEFAULT_CAPACITY) {
        minCapacity = std::max(DEFAULT_CAPACITY, minCapacity);
    }
    if (minCapacity - size > 0) {
        int oldCapacity = size;
        int newCapacity = (int) (oldCapacity + 0.5 * oldCapacity);
        if (newCapacity - minCapacity < 0)
            newCapacity = minCapacity;
        T *newBase = (T *) realloc(base, newCapacity);
        base = newBase;
        size = newCapacity;
    }
}

//在顺序表中添加一个数据元素
template<class T>
void OrderedSeqList<T>::add(T item) {
    bool confirmInsert = false;
    for (int i = 0; i < length; ++i) {
        //遍历顺序表，找到第一个比item值大的元素的位置
        if (base[i] >= item) {
            confirmInsert = true;
            insert(i , item);
            break;
        }
    }
    //若item值比此时表中所有元素的值都大，则插入表尾
    if (!confirmInsert) {
        insert(length, item);
    }
}

//删除有序顺序表中所有值相同的元素
template<class T>
void OrderedSeqList<T>::delSame() {
    int i = 0;
    while (i < length) {
        while (base[i] == base[i + 1] && i + 1 != length) {
            del(i);
        }
        i++;
    }

}

//插入功能，同时排序
template<class T>
void OrderedSeqList<T>::insert(int index, T item) {
    if (index > length || index < 0) {
        throw std::out_of_range("Index out of bound");
    }
    ensureCapacity(length + 1);
    //使用引用存储位置index的地址
    T &q = base[index];
    //把指定位置index及其后面的元素全部后移一位
    for (int i = length - 1; i >= index; i--) {
        base[i + 1] = base[i];
    }
    //将item的值存入位置index
    q = item;
    length++;
}

//删除顺序表中一给定位置的数据元素
template<class T>
void OrderedSeqList<T>::del(int index) {
    if (index > length || index < 0) {
        throw std::out_of_range("Index out of bound");
    }
    int numMoved = size - index - 1;
    if (numMoved > 0) {
        for (int i = index; i < length - 1; i++) {
            base[i] = base[i + 1];
        }
    }
    length--;
}

//按给定值item，删除顺序表中所有值为item的元素
template<class T>
void OrderedSeqList<T>::delByElement(const T &item) {
    for (int i = 0; i < length; i++) {
        if (get(i) == item) {
            del(i);
        }
    }
}

//取出顺序表中给定位置的元素
template<class T>
T OrderedSeqList<T>::get(int index) const {
    if (index > length || index < 0) {
        throw std::out_of_range("Index out of bound");
    }
    return base[index];
}

//重载输出操作符，输出顺序表
template<class T>
std::ostream &operator<<(std::ostream &out, const OrderedSeqList<T> &s) {
    for (int i = 0; i < s.length; ++i) {
        out << s.get(i) << "\n";
    }
    return out;
}

#endif //DS_ORDEREDSEQLIST_H
