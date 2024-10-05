// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    
    node *new_node = new node;
    new_node->pq = new PriorityQ(50);
    new_node->next = next;
    new_node->restaurantName = restaurantName;

    return new_node;
}

HashTable::HashTable(int bsize)
{
    numCollision = 0;
    tableSize = bsize;
    table = new node*[tableSize];
    for (int i = 0; i < bsize; i++)
        table[i] = nullptr;
}

HashTable::~HashTable()
{
    node *temp = nullptr;
    node *next = nullptr;
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        while(temp != nullptr)
        {
            next = temp->next;
            delete temp->pq;
            delete temp;
            temp = next;
        }
    }
    delete[] table;
}

void HashTable::displayTable()
{
    node *temp = nullptr;
    for(int i = 0; i < tableSize; i++)
    {
        cout << i << "|";
        temp = table[i];
        while(temp)
        {
            cout << temp->restaurantName << "-->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    // will return 0,1,2,3...
    // add up the letters and then take result and mode the table size
    int char_total = 0;
    for(int i = 0; i < restaurantName.length(); i++)
    {
        char_total = char_total + restaurantName[i];
    }
    return (char_total % tableSize);
}

node* HashTable::searchItem(string restaurantName)
{
    // look for the resturan in the hash table
    // if doesnt exist return null
    // if exists return a pointer to that memory location
    int hash_val = hashFunction(restaurantName);
    node *temp = table[hash_val];
    while(temp != nullptr)
    {
        if(temp->restaurantName == restaurantName)
        {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    // searchItem() see if it is in the hash table/linked list
    // if !found 
    // create a node
    //node new node[name]
    //also creat a pq of size 50
    node *item = searchItem(restaurant.restaurantName);
    if(item == nullptr)
    {
        int hash_val = hashFunction(restaurant.restaurantName);
        node *new_resturant = createNode(restaurant.restaurantName, table[hash_val]);
        table[hash_val] = new_resturant;
        if(table[hash_val]->next != nullptr)
        {
            numCollision++;
        }
        item = new_resturant;
    }
    item->pq->insertElement(restaurant);
}


void HashTable::setup(string fname)
{
    // read from the file
    // sstream
    // searchItem and pass the resturan name
    // reviewInfo istances for each item. 
    // reviewInfo r; 
    ifstream file(fname);
    string line, resturant_name, review, reviwer_name, time; 
    int time_int, index = 0;                   
    while(getline(file, line))
    {
        stringstream ss(line);
        getline(ss, resturant_name, ';');
        getline(ss, review, ';');
        getline(ss, reviwer_name, ';');
        getline(ss, time, ';');

        ReviewInfo review_info{resturant_name, review, reviwer_name, stoi(time)};
        insertItem(review_info);
        index++;
    }
}
