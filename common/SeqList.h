//
// Created by lyp on 2019/9/23.
//

#ifndef DS_SEQLIST_H
#define DS_SEQLIST_H

#include <iostream>

template<class T>
class SeqList {
    template<class S>
    friend std::ostream &operator<<(std::ostream &os, const SeqList<S> &s);

private:
    T *base;
    //逻辑容器长度
    int length;
    //最大容器长度
    int size;
    int DEFAULT_CAPACITY = 10;

    void ensureCapacity(int minCapacity);

public:
    SeqList();

    ~SeqList();

    void add(T item);

    void del(int index);

    T get(int index) const;

    void delByElement(const T &item);
};

//构造函数，对顺序表进行初始化
template<class T>
SeqList<T>::SeqList() {
    base = (T *) malloc(sizeof(T) * DEFAULT_CAPACITY);
    size = DEFAULT_CAPACITY;
    length = 0;
}

template<class T>
SeqList<T>::~SeqList() {
    if(base){
        delete[] base;
    }
}

/**
 * 扩容
 * @param minCapacity 该线性表应有的最小容量
 */
template<class T>
void SeqList<T>::ensureCapacity(int minCapacity) {
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
void SeqList<T>::add(T item) {
    ensureCapacity(length + 1);
    base[length++] = item;
}

//删除顺序表中一给定位置的数据元素
template<class T>
void SeqList<T>::del(int index) {
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
void SeqList<T>::delByElement(const T &item) {
    for (int i = 0; i < length; i++) {
        if (get(i) == item) {
            del(i);
        }
    }
}

//取出顺序表中给定位置的元素
template<class T>
T SeqList<T>::get(int index) const {
    if (index > length || index < 0) {
        throw std::out_of_range("Index out of bound");
    }
    return base[index];
}

//重载输出操作符，输出顺序表
template<class T>
std::ostream &operator<<(std::ostream &out, const SeqList<T> &s) {
    for (int i = 0; i < s.length; ++i) {
        out << s.get(i) << "\n";
    }
    return out;
}

#endif //DS_SEQLIST_H
