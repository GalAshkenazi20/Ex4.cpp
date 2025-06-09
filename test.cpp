#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MyContainer.hpp"
#include "AscendingOrder.hpp"
#include "DescendingOrder.hpp"
#include "SideCrossOrder.hpp"
#include "ReverseOrder.hpp"
#include "Order.hpp"
#include "MiddleOutOrder.hpp"

#include <vector>
#include <algorithm>
#include <limits>

using namespace container;

// Helper function to extract values from iterator
template<typename IteratorType>
std::vector<int> extractValues(IteratorType iterator) {  // Removed & to avoid potential issues
    std::vector<int> result;
    for (const auto& val : iterator) {
        result.push_back(val);
    }
    return result;
}

// 🧪 BASIC FUNCTIONALITY TESTS
TEST_SUITE("Basic Functionality") {
    
    TEST_CASE("Container basic operations") {
        MyContainer<int> container;
        
        SUBCASE("Empty container") {
            CHECK(container.empty());
            CHECK(container.size() == 0);
        }
        
        SUBCASE("Add elements") {
            container.add(5);
            container.add(2);
            container.add(8);
            
            CHECK_FALSE(container.empty());
            CHECK(container.size() == 3);
        }
        
        SUBCASE("Remove element") {
            container.add(10);
            container.add(20);
            container.remove(10);
            
            CHECK(container.size() == 1);
        }
    }
    
    TEST_CASE("All iterator types work") {
        MyContainer<int> container;
        std::vector<int> data = {5, 2, 8, 1, 9};
        for (int val : data) {
            container.add(val);
        }
        
        SUBCASE("Ascending order") {
            auto values = extractValues(container.ascending());
            std::vector<int> expected = {1, 2, 5, 8, 9};
            CHECK(values == expected);
        }
        
        SUBCASE("Descending order") {
            auto values = extractValues(container.descending());
            std::vector<int> expected = {9, 8, 5, 2, 1};
            CHECK(values == expected);
        }
        
        SUBCASE("Reverse order") {
            auto values = extractValues(container.reverse());
            std::vector<int> expected = {9, 1, 8, 2, 5}; // Original reversed
            CHECK(values == expected);
        }
        
        SUBCASE("All iterators return same size") {
            auto asc = extractValues(container.ascending());
            auto desc = extractValues(container.descending());
            auto rev = extractValues(container.reverse());
            auto side = extractValues(container.sidecross());
            auto middle = extractValues(container.middleout());
            
            CHECK(asc.size() == 5);
            CHECK(desc.size() == 5);
            CHECK(rev.size() == 5);
            CHECK(side.size() == 5);
            CHECK(middle.size() == 5);
        }
    }
    
    TEST_CASE("Modify values through iterator") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        // Modify through ascending iterator
        for (auto& val : container.ascending()) {
            val += 10;
        }
        
        auto values = extractValues(container.ascending());
        std::vector<int> expected = {11, 12, 13};
        CHECK(values == expected);
    }
}

// 🔥 EDGE CASES TESTS
TEST_SUITE("Edge Cases") {
    
    TEST_CASE("Empty container edge cases") {
        MyContainer<int> empty;
        
        SUBCASE("Remove from empty throws") {
            CHECK_THROWS_AS(empty.remove(5), std::runtime_error);
        }
        
        SUBCASE("Iterators on empty container") {
            CHECK_THROWS_AS(empty.ascending(), std::runtime_error);
            CHECK_THROWS_AS(empty.descending(), std::runtime_error);
            CHECK_THROWS_AS(empty.reverse(), std::runtime_error);
        }
    }
    
    TEST_CASE("Single element container") {
        MyContainer<int> single;
        single.add(42);
        
        auto asc = extractValues(single.ascending());
        auto desc = extractValues(single.descending());
        auto rev = extractValues(single.reverse());
        
        CHECK(asc == std::vector<int>{42});
        CHECK(desc == std::vector<int>{42});
        CHECK(rev == std::vector<int>{42});
    }
    
    TEST_CASE("Duplicate elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(3);
        container.add(5);
        container.add(3);
        container.add(5);
        
        SUBCASE("Ascending with duplicates") {
            auto values = extractValues(container.ascending());
            std::vector<int> expected = {3, 3, 5, 5, 5};
            CHECK(values == expected);
        }
        
        SUBCASE("Remove all occurrences") {
            container.remove(5); // Should remove all 5s
            auto values = extractValues(container.ascending());
            CHECK(values == std::vector<int>{3, 3});
        }
    }
    
    TEST_CASE("Extreme values") {
        MyContainer<int> container;
        container.add(std::numeric_limits<int>::max());
        container.add(std::numeric_limits<int>::min());
        container.add(0);
        container.add(-1);
        container.add(1);
        
        auto values = extractValues(container.ascending());
        
        // Check that min is first and max is last
        CHECK(values[0] == std::numeric_limits<int>::min());
        CHECK(values[values.size()-1] == std::numeric_limits<int>::max());
        
        // Check that it's properly sorted
        for (size_t i = 1; i < values.size(); ++i) {
            CHECK(values[i-1] <= values[i]);
        }
    }
    
    TEST_CASE("Index out of bounds") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        CHECK_THROWS_AS(container.at(5), std::out_of_range);
        CHECK_THROWS_AS(container[10], std::out_of_range);
    }
    
    TEST_CASE("Iterator boundaries") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto asc = container.ascending();
        auto it = asc.begin();
        
        // Move to end
        ++it;
        ++it;
        CHECK(it == asc.end());
        
        // Try to increment past end
        CHECK_THROWS_AS(++it, std::out_of_range);
        
        // Try to dereference end iterator
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
}

//  STRESS TESTS (Simple)
TEST_SUITE("Stress Tests") {
    
    TEST_CASE("Large container") {
        MyContainer<int> container;
        const int SIZE = 1000;
        
        // Add elements in reverse order
        for (int i = SIZE; i > 0; --i) {
            container.add(i);
        }
        
        CHECK(container.size() == SIZE);
        
        // Check ascending order is correct
        auto values = extractValues(container.ascending());
        for (int i = 0; i < SIZE-1; ++i) {
            CHECK(values[i] <= values[i+1]);
        }
        CHECK(values[0] == 1);
        CHECK(values[SIZE-1] == SIZE);
    }
    
    TEST_CASE("Multiple iterators on same container") {
        MyContainer<int> container;
        container.add(3);
        container.add(1);
        container.add(2);
        
        auto asc1 = container.ascending();
        auto asc2 = container.ascending();
        auto desc = container.descending();
        
        auto asc1_vals = extractValues(asc1);
        auto asc2_vals = extractValues(asc2);
        auto desc_vals = extractValues(desc);
        
        // Both ascending should be identical
        CHECK(asc1_vals == asc2_vals);
        
        // Descending should be reverse of ascending
        std::reverse(asc1_vals.begin(), asc1_vals.end());
        CHECK(asc1_vals == desc_vals);
    }
}

//  ERROR HANDLING
TEST_SUITE("Error Handling") {
    
    TEST_CASE("Remove non-existent element") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        CHECK_THROWS_AS(container.remove(999), std::runtime_error);
        
        // Container should be unchanged
        CHECK(container.size() == 2);
        auto values = extractValues(container.ascending());
        CHECK(values == std::vector<int>{1, 2});
    }
    
    TEST_CASE("Exception safety") {
        MyContainer<int> container;
        container.add(5);
        container.add(10);
        
        size_t original_size = container.size();
        
        try {
            container.remove(999); // Should throw
        } catch (const std::runtime_error&) {
            // Container should be unchanged
            CHECK(container.size() == original_size);
        }
    }
}

// 🎮 PRACTICAL USAGE
TEST_CASE("Real world example") {
    MyContainer<int> grades;
    
    // Add student grades
    std::vector<int> student_grades = {85, 92, 78, 96, 88};
    for (int grade : student_grades) {
        grades.add(grade);
    }
    
    // Get sorted grades
    auto sorted = extractValues(grades.ascending());
    CHECK(sorted == std::vector<int>{78, 85, 88, 92, 96});
    
    // Add curve (5 points to everyone)
    for (auto& grade : grades.ascending()) {
        grade += 5;
    }
    
    // Check curved grades
    auto curved = extractValues(grades.ascending());
    CHECK(curved == std::vector<int>{83, 90, 93, 97, 101});
    
    // Remove failing grade (if any under 60)
    // grades.remove(59); // Would throw since no such grade exists
}