cmake_minimum_required(VERSION 3.14)
project(untitled1)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")

add_executable(untitled1 AVL.cpp AVL.h BST.cpp BST.h input.txt main.cpp node.cpp
        node.h Sorted.cpp Sorted.h Unsorted.cpp Unsorted.h AVL.cpp AVL.h BST.cpp BST.h node.cpp
        node.h Sorted.cpp Sorted.h Unsorted.cpp Unsorted.h hashtable.cpp hashtable.h myPair.h)