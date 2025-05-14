#include <iostream>
#include "list.hpp"

using namespace std;
using namespace lasd;

void printInt(const int& value) {
    std::cout << value << " ";
}

int main() {
    // Create a list of integers
    List<int> myList;
    
    // Test InsertAtFront and InsertAtBack
    std::cout << "Adding elements to the list..." << std::endl;
    myList.InsertAtFront(10);
    myList.InsertAtFront(5);
    myList.InsertAtBack(15);
    myList.InsertAtBack(20);
    
    // Print the size
    std::cout << "List size: " << myList.Size() << std::endl;
    
    // Print the list using Traverse
    std::cout << "List elements: ";
    myList.Traverse(printInt);
    std::cout << std::endl;
    
    // Test Front and Back
    std::cout << "Front element: " << myList.Front() << std::endl;
    std::cout << "Back element: " << myList.Back() << std::endl;
    
    // Test RemoveFromFront
    std::cout << "Removing front element..." << std::endl;
    myList.RemoveFromFront();
    std::cout << "New front element: " << myList.Front() << std::endl;
    
    // Test FrontNRemove
    std::cout << "Front and remove: " << myList.FrontNRemove() << std::endl;
    
    // Test operator[]
    if (myList.Size() > 0) {
        std::cout << "First element using operator[]: " << myList[0] << std::endl;
    }
    
    // Test Clear
    std::cout << "Clearing the list..." << std::endl;
    myList.Clear();
    std::cout << "List size after clearing: " << myList.Size() << std::endl;
    
    return 0;
}

