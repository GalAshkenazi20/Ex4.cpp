// galashkena1@gmail.com
#ifndef _SIDE_CROSS_ORDER_HPP_
#define _SIDE_CROSS_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>
#include <numeric>

namespace container
{
    /**
     * @brief Iterator that alternates between smallest and largest remaining elements
     * 
     * This iterator first sorts elements, then alternates between taking from
     * the left (smallest) and right (largest) sides of the sorted array.
     * This creates a "zigzag" pattern through the sorted values.
     * 
     * Example: Container [5, 2, 8, 1, 9] 
     *          Sorted: [1, 2, 5, 8, 9]
     *          SideCross: [1, 9, 2, 8, 5] (left, right, left, right, left)
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::SideCrossOrder : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates a side-cross order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the alternating traversal order.
         */
        SideCrossOrder(MyContainer<T> &c) : Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for side-cross traversal
         * 
         * This method:
         * 1. Creates and sorts indices based on element values
         * 2. Uses two pointers (left and right) on the sorted indices
         * 3. Alternates between taking from left (smallest) and right (largest)
         * 4. Continues until all elements are included
         * 
         * The algorithm creates a pattern that alternates between extremes,
         * which can be useful for balanced processing or display purposes.
         */
        void prepareIndices() override
        {

            std::vector<size_t> sortedIndices(this->original_container.size());
            std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
            
            // Sort indices to get them in ascending order by value
            std::sort(sortedIndices.begin(), sortedIndices.end(), 
                [&](size_t i, size_t j) {
                    return this->original_container[i] < this->original_container[j];
                });
            
            this->indices.clear();
            size_t left = 0;                           
            size_t right = sortedIndices.size() - 1;   
            bool take_left = true;                     

            while (left <= right)
            {
                if (take_left)
                {
                    this->indices.push_back(sortedIndices[left]);
                    ++left;
                }
                else
                {
                    this->indices.push_back(sortedIndices[right]);
                    --right;
                }
                take_left = !take_left;  

                if (left > right) break;
            }
        }
    };
}

#endif