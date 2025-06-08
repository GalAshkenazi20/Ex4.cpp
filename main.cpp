#include "MyContainer.hpp"
#include "AscendingOrder.hpp"
#include "DescendingOrder.hpp"
#include "SideCrossOrder.hpp"
#include "ReverseOrder.hpp"
#include "Order.hpp"
#include "MiddleOutOrder.hpp"
#include <iostream>

int main() {
    using namespace container;
    
    std::cout << "=== MyContainer examples ===" << std::endl;
    
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    

    
  
    std::cout << "\n=== Iterators ===" << std::endl;
    
    std::cout << "Order: ";
    for (auto it : container.order()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Ascending: ";
    for (auto it : container.ascending()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Descending: ";
    for (auto it : container.descending()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "SideCross: ";
    for (auto it : container.sidecross()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Reverse: ";
    for (auto it : container.reverse()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "MiddleOut: ";
    for (auto it : container.middleout()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    // הדגמת מחיקה
    std::cout << "\n=== Deleting element===" << std::endl;
    std::cout << "deleting element n.6" << std::endl;
    container.remove(6);
    std::cout << "container after delete: " << container << std::endl;
    
    return 0;
}