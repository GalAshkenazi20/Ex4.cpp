#include "MyContainer.hpp"
#include "AscendingOrder.hpp"
#include "DescendingOrder.hpp"
#include "SideCrossOrder.hpp"
#include "ReverseOrder.hpp"
#include "Order.hpp"
#include "MiddleOutOrder.hpp"
#include <iostream>
#include <iomanip>

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSubSection(const std::string& title) {
    std::cout << "\n--- " << title << " ---" << std::endl;
}

int main() {
    using namespace container;
    
    printSeparator("MyContainer Demo - All Features!");
    
    // Creating first container
    MyContainer<int> container1;
    container1.add(7);
    container1.add(15);
    container1.add(6);
    container1.add(1);
    container1.add(2);
    
    std::cout << " Original container: " << container1 << std::endl;
    std::cout << " Size: " << container1.size() << " elements" << std::endl;
    
    printSubSection(" All Iterator Types");
    
    std::cout << " Order (original):   ";
    for (auto it : container1.order()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " Ascending:          ";
    for (auto it : container1.ascending()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " Descending:         ";
    for (auto it : container1.descending()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " Reverse:            ";
    for (auto it : container1.reverse()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " SideCross:          ";
    for (auto it : container1.sidecross()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " MiddleOut:          ";
    for (auto it : container1.middleout()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    printSeparator(" Modifying Values Through Iterator");
    
    std::cout << " Before modification: " << container1 << std::endl;
    
    printSubSection(" Adding 100 to each value in ascending order");
    std::cout << " Iterating in ascending order and adding 100:" << std::endl;
    
    int counter = 1;
    for (auto& value : container1.ascending()) {
        std::cout << "   Step " << counter++ << ": " << value << " → " << (value + 100) << std::endl;
        value += 100;
    }
    
    std::cout << " After modification: " << container1 << std::endl;
    
    printSubSection(" Verification - Original order preserved");
    std::cout << " Original order:  ";
    for (auto it : container1.order()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " Ascending order: ";
    for (auto it : container1.ascending()) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    printSeparator(" Element Deletion Demo");
    
    std::cout << " Before deletion: " << container1 << std::endl;
    std::cout << " Deleting element 106..." << std::endl;
    
    try {
        container1.remove(106);
        std::cout << " Deletion successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << " Error: " << e.what() << std::endl;
    }
    
    std::cout << " After deletion: " << container1 << std::endl;
    
    printSeparator(" Additional Example - Container with Different Numbers");
    
    MyContainer<int> container2;
    container2.add(100);
    container2.add(50);
    container2.add(200);
    container2.add(25);
    container2.add(150);
    container2.add(75);
    
    std::cout << " Container 2: " << container2 << std::endl;
    
    printSubSection(" Comparing Different Orders");
    
    std::cout << std::left << std::setw(15) << "Iterator Type" << "Result" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    std::cout << std::setw(15) << "Original:" << " ";
    for (auto it : container2.order()) std::cout << it << " ";
    std::cout << std::endl;
    
    std::cout << std::setw(15) << "Ascending:" << " ";
    for (auto it : container2.ascending()) std::cout << it << " ";
    std::cout << std::endl;
    
    std::cout << std::setw(15) << "Descending:" << " ";
    for (auto it : container2.descending()) std::cout << it << " ";
    std::cout << std::endl;
    
    std::cout << std::setw(15) << "SideCross:" << " ";
    for (auto it : container2.sidecross()) std::cout << it << " ";
    std::cout << std::endl;
    
    printSeparator(" Advanced Modification Test");
    
    std::cout << " Before: " << container2 << std::endl;
    
    printSubSection(" Multiply by 2 in descending order");
    std::cout << " Iterating in descending order and multiplying each value by 2:" << std::endl;
    
    counter = 1;
    for (auto& value : container2.descending()) {
        int old_value = value;
        value *= 2;
        std::cout << "   Step " << counter++ << ": " << old_value << " × 2 = " << value << std::endl;
    }
    
    std::cout << " After multiplication: " << container2 << std::endl;
    
    printSubSection(" Verifying order preservation");
    std::cout << " Original: ";
    for (auto it : container2.order()) std::cout << it << " ";
    std::cout << std::endl;
    
    std::cout << " Ascending: ";
    for (auto it : container2.ascending()) std::cout << it << " ";
    std::cout << std::endl;
    
    printSeparator(" Error Handling Test");
    
    std::cout << " Attempting to delete non-existent element (999)..." << std::endl;
    try {
        container2.remove(999);
        std::cout << " Deletion successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    
    printSeparator(" Demo Summar");
    
    std::cout << "    Successfully demonstrated:" << std::endl;
    std::cout << "    6 different iterator types" << std::endl;
    std::cout << "    Value modification through iterators" << std::endl;
    std::cout << "    Original order preservation" << std::endl;
    std::cout << "    Element deletion" << std::endl;
    std::cout << "    Error handling" << std::endl;
    std::cout << "    Multiple container operations" << std::endl;

    std::cout << "\n Project works perfectly!" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    MyContainer<int> container4;
    container4.add(7);
    container4.add(15);
    container4.add(6);
    container4.add(1);
    container4.add(2);

    std::cout<<container4;
    std::cout<<"\n";
     for (auto& it : container4.ascending()) {
        if(it == 7){
            it = 12;
        }
        std::cout << it << " ";
     }
    std::cout<<"\n";
    std::cout<<container4;
    std::cout<<"\n";


    return 0;
}