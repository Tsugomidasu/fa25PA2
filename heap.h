//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) return -1;

        int root = data[0]; // Store the root (smallest element)

        // Replace root with last element
        data[0] = data[size - 1];
        size--;

        // Replace root with last element, then call downheap()
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif