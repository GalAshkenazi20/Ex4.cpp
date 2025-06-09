// galashkena1@gmail.com
#ifndef _MIDDLE_OUT_ORDER_HPP_
#define _MIDDLE_OUT_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <numeric>

namespace container
{
    /**
     * @brief Iterator that starts from the middle element and expands outward
     * 
     * This iterator begins with the middle element (by position, not value)
     * and then alternates between elements to the left and right of the middle,
     * gradually expanding outward until all elements are covered.
     * 
     * Example: Container [A, B, C, D, E] (5 elements, middle index = 2)
     *          MiddleOut: [C, B, D, A, E] (middle, left, right, left, right)
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::MiddleOutOrder : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates a middle-out order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the middle-out traversal order.
         */
        MiddleOutOrder(MyContainer<T> &c) : Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for middle-out traversal
         * 
         * This method:
         * 1. Starts with the middle element (size/2)
         * 2. Uses two pointers expanding left and right from the middle
         * 3. Alternates between adding left and right elements
         * 4. Continues until all positions are covered
         * 5. Handles edge cases for both even and odd-sized containers
         * 
         * The algorithm creates a traversal pattern that radiates outward
         * from the center, which can be useful for certain processing patterns.
         */
        void prepareIndices() override
        {
            this->indices.clear();
            if (this->original_container.empty()) return;
            
            size_t middle = this->original_container.size() / 2;
            this->indices.push_back(middle);  

            int left = middle - 1;    
            int right = middle + 1;   
            bool take_left = true;   

            while (left >= 0 || right < static_cast<int>(this->original_container.size()))
            {
                if (take_left && left >= 0)
                {
                    this->indices.push_back(left);
                    --left;
                }
                else if (!take_left && right < static_cast<int>(this->original_container.size()))
                {
                    this->indices.push_back(right);
                    ++right;
                }
                else if (left >= 0)
                {
                    this->indices.push_back(left);
                    --left;
                }
                else if (right < static_cast<int>(this->original_container.size()))
                {
                    this->indices.push_back(right);
                    ++right;
                }
                take_left = !take_left;
            }
        }
    };
}

#endif