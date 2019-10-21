cmake_minimum_required(VERSION 3.14)
project(DS)

set(CMAKE_CXX_STANDARD 14)

add_executable(DS main.cpp common/SeqList.h common/OrderedLinkedList.h common/LinkedList.h common/OrderedSeqList.h)