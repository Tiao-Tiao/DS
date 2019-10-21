#define CRTDBG_MAP_ALLOC
#include "common/SeqList.h"
#include "common/OrderedSeqList.h"
#include "common/OrderedLinkedList.h"
#include <iostream>
#include <vector>

int main() {


//    LinkedList<int> list = *new LinkedList<int>();
//    list.add(-9);
//    list.add(-8);
//    list.add(1);
//    list.add(2);
//
//
//    LinkedList<int> b = *new LinkedList<int>();
//    b.add(3);
//    b.add(4);
//    b.add(6);
//    b.add(7);
//
//
//    std::cout << list << std::endl;
//    list.mix(b);
//    std::cout << list << std::endl;

//    SeqList<int> array = *new SeqList<int>;
//    array.add(1);
//    array.insert(1, 2);
//    std::cout << array << std::endl;
//    array.delByElement(1);
//    std::cout << array << std::endl;

    OrderedSeqList<int> s = *new OrderedSeqList<int>();
    s.add(-5);
    s.add(1);
    s.add(2);
    s.add(5);
    s.add(6);
    s.add(7);
    s.add(3);
    s.add(6);
    s.add(7);
    s.add(7);

    std::cout<< s <<std::endl;
    s.delSame();
    std::cout<< s <<std::endl;
//    LinkedList<int> list = *new LinkedList<int>();
//    T item;
//    std::cout<<"请依次输入数据，若要结束输入请输入N"<<std::endl;
//    do{
//        std::cin>>item;
//        list.add(item);
//    }while (item!='N');

//    LinkedList<int> *list = new LinkedList<int>();
//    list->add(6);
//    list->add(5);
//    list->add(3);
//    list->add(7);
//    list->add(2);
//    list->add(6);
//    list->add(2);
//
//    std::cout<<*list<<std::endl;
//    list->delSame();
//    std::cout<<*list<<std::endl;
//    delete list;
//	_CrtDumpMemoryLeaks();
//	system("pause");
    return 0;
}