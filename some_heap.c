
#include <stdio.h>
#include <stdlib.h>

#include "some_heap.h"

#define KEY_NOT_PRESENT -1

heap_t* heap_create(int capacity) 
{
    heap_t* newHeap=(struct heap_t*)malloc(1 * sizeof(heap_t));
    heap_node_t *arr = (struct heap_node_t*)malloc(capacity * sizeof(heap_node_t));
    newHeap->data = arr;
    newHeap->capacity = capacity;
    newHeap->size = 0;

    return newHeap;
}

void heap_free(heap_t* heap) 
{
    free(heap->data);
    free(heap);
}

unsigned int heap_size(heap_t* heap)
{ return heap->size; }

unsigned int heap_parent(unsigned int index) //get parent iteration
{
    if(index==0)
    {
        return 0;
    }
    else
    {
        return  (index - 1) / 2;
    }
}

unsigned int heap_left_child(unsigned int index)//get leftchild  iteration
{
    return (2 * index) + 1;
}

unsigned int heap_right_child(unsigned int index)//get rightchild  iteration
{
    return (2 * index) + 2;
}

unsigned int heap_level(unsigned int index) //get level
{
    int count = 1;
    while (index!=0)
    {
        index = (index - 1) / 2;
        count++;
    }
    return count;
}

void heap_print(heap_t* heap) 
{
    FILE* myFile = fopen("output.txt", "a");
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix, heap->data[ix].key);
        fprintf(myFile, "%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix, heap->data[ix].key);
    }
    printf("\n");
    fprintf(myFile,"\n");
    fclose(myFile);
}

void heap_swap(heap_t* heap, int index1, int index2) 
{
    heap_node_t placeHolder = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = placeHolder;

}

void heap_bubble_up(heap_t* heap, int index)
{//point is to take newly added node and bubble it up properly
        int parentIteration =  heap_parent(index);
        if ((heap->data[parentIteration].key > heap->data[index].key) && (index != 0))
        {
            heap_swap(heap, parentIteration, index);
            heap_bubble_up(heap, parentIteration);
        }
}

void heap_bubble_down(heap_t* heap, int index)
{
    //get lowest in level pair
    int iteratorLeftChild = heap_left_child(index);
    int iteratorRightChild = heap_right_child(index);
    int chosenIterator;
    if ((heap->data[iteratorLeftChild].key >= 1) && (heap->data[iteratorLeftChild].key <= 1000))//if left child exists
    {
        if ((heap->data[iteratorLeftChild].key < heap->data[iteratorRightChild].key) ||//if left is less than or right is non existent
            ((heap->data[iteratorRightChild].key < 1) || (heap->data[iteratorRightChild].key > 1000)))
        {
            chosenIterator = iteratorLeftChild;
            if (heap->data[index].key > heap->data[chosenIterator].key)
            {
                heap_swap(heap, index, chosenIterator);
                heap_bubble_down(heap, chosenIterator);//recursion
            }
        }
        else if (heap->data[iteratorLeftChild].key > heap->data[iteratorRightChild].key)
        {
            chosenIterator = iteratorRightChild;
            if (heap->data[index].key > heap->data[chosenIterator].key)
            {
                heap_swap(heap, index, chosenIterator);
                heap_bubble_down(heap, chosenIterator);//recursion
            }
        }
        //compare lowest to parent, swap if necessary
        
    }
    

}

void heap_insert(heap_t* heap, heap_key_t key, heap_value_t data) {
    int heapSize = heap_size(heap);
    if ( heapSize == heap->capacity) {
        return;
    }

    heap->data[heapSize].key = key;
    heap->data[heapSize].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}


heap_value_t heap_remove_min(heap_t* heap) {
    if (heap_size(heap) == 0)
    {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
