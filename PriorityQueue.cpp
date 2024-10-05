#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp;
    temp.customer = a->customer;
    temp.restaurantName = a->restaurantName;
    temp.review = a->review;
    temp.time = a->time;

    a->customer = b->customer;
    a->restaurantName = b->restaurantName;
    a->review = b->review;
    a->time = b->time;

    b->customer = temp.customer;
    b->restaurantName = temp.restaurantName;
    b->review = temp.review;
    b->time = temp.time;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    // create heapArr[cap]
    heapArr = new ReviewInfo[cap];
    capacity = cap;
    currentSize = 0;
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return (index/2);
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return (index*2)+2;
}

/*
Returns the right child of a node.
*/
    int PriorityQ::rightChild(int index)
{
    return (index*2) + 1;
}

void PriorityQ::peek()
{
    if(currentSize == 0)
    {
        cout << "no record found" << endl;
    }
    else 
    {
        cout << "Restaurant: "<< heapArr[0].restaurantName << endl;
        cout << "Customer:" << heapArr[0].customer << endl;
        cout << "Review:" << heapArr[0].review << endl;
        cout << "Time:" << heapArr[0].time << endl;
    }
}

void PriorityQ::heapify(int i)
{
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    // Checks to see if the left child (l) key (time) is larger than the current largest key so far
    // If so then the largest is set to the left node
    if(l < currentSize && heapArr[l].time > heapArr[largest].time )
    {
        largest = l;
    }
    // Functions basiclly the same as the function above just with the right node
    if(r < currentSize && heapArr[r].time > heapArr[largest].time)
    {
        largest = r;
    }

    // Checks if the largest node was changed from what was orgnally passed throught the function
    // If it was then the vaules are swapped and function is run again with the new largest vaule
    if(largest != i)
    {
        swap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if(currentSize == capacity)
    {
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
    }
    else
    {
        heapArr[currentSize] = restaurant;
        int child = currentSize;
        currentSize++;
        while(heapArr[child].time > heapArr[parent(child)].time)
        {
            swap(&heapArr[child], &heapArr[parent(child)]);
            child = parent(child);
        }
    }
    
}

/*
Prints the elements in the heap 
*/
void PriorityQ::print()
{
    for(int i = 0; i < currentSize; i++)
    {
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if(currentSize <= 0)
    {
        cout << "There are no reviews for this resturant." << endl;
        return;
    }
    else
    {
        heapArr[0] = heapArr[currentSize-1];
        currentSize--;
        heapify(0);
        cout << "The review was popped." << endl;
    }
    
}
