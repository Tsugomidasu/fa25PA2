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

        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) return -1;

        int root = data[0]; // Store the root (smallest element)

        // Replace root with last element, then call downheap()
        data[0] = data[size - 1];
        size--;

        if (size > 0) {
            downheap(0, weightArr);
        }
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;

            // If current node is smaller than parent, swap
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                // Swap
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;

                // Move up
                pos = parent;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos < size) {
            int leftChild = 2 * pos + 1;
            int rightChild = 2 * pos + 2;
            int smallest = pos;

            // Find smallest among parent and children
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }
            // If smallest is not the parent, swap and continue
            if (smallest != pos) {
                // Swap
                int temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;

                // Move down
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif