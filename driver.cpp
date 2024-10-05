#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool data_built = false;
    node *search = nullptr;
	
    while(ch!=8)
    {
        // Input Validation
        // Checks to make sure that the first charcter the user inputs is valid by checking the
        // ASCII vaule, (Should be between 49 and 58 for the number 1 - 8)
        while(true)
        {
            displayMenu();
            cout << "Enter your choice >>";
            getline(cin, chs);
            if(chs[0] >= 49 && chs[0] <= 56)
            {
                chs = chs[0];
                ch = stoi(chs);
                break;
            }
            else
            {
                cout << "That is not a valid input." << endl;
            }
            
        }
        // Used in case for 2 for implementing 
        string resturant_name, customer, review, time;

        switch (ch)
        {
            case 1:
			{
				//Add flag to check if this was already done so it is only called once
                if(!data_built)
                {
                    ht.setup(fname);
                    data_built = true;
                    cout << "Data structure build sucessful." << endl;
                }
                else
                {
                    cout << "The data structure has already been built." << endl;
                }
				break;
            }
            case 2:
			{
                //
                cout << "Resturant Name: ";
                getline(cin, resturant_name);
                if(ht.searchItem(resturant_name) == nullptr)
                {
                    cout << "Could not find that resturant." << endl; 
                }
                else
                {
                    cout << "Customer: ";
                    getline(cin, customer);
                    cout << "Review: ";
                    getline(cin, review);
                    cout << "Time: ";
                    getline(cin, time);

                    ReviewInfo ri;
                    ri.restaurantName = resturant_name;
                    ri.customer = customer;
                    ri.review = review;
                    ri.time = stoi(time);

                    search = ht.searchItem(resturant_name);
                    search->pq->insertElement(ri);
                }
				break;
            }
            case 3:
			{
                //
                cout << "Resturant Name: ";
                getline(cin, resturant_name);
                search = ht.searchItem(resturant_name);
                if(!search)
                {
                    cout << "Could not find that resturant." << endl; 
                    break;
                }
                cout << "Retrived Result." << endl;
                search->pq->peek();
				break;
            }
            case 4:
			{
                //
                cout << "Resturant Name: ";
                getline(cin, resturant_name);
                search = ht.searchItem(resturant_name);
                if(!search)
                {
                    cout << "Could not find that resturant." << endl; 
                    break;
                }
                search->pq->pop();
				break;
            }
            case 5:
			{
				//
                cout << "Resturant Name: ";
                getline(cin, resturant_name);
                search = ht.searchItem(resturant_name);
                if(!search)
                {
                    cout << "Could not find that resturant." << endl; 
                    break;
                }
                search->pq->print();
				break;
			}
            case 6:
                //
                cout << "Number of Collison: " << ht.getNumCollision();
                break;
            case 7:
                //
                ht.displayTable();
                break;
            case 8:
                return 0;
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
