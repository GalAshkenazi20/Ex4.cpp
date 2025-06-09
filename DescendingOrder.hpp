// galashkena1@gmail.com
#ifndef _DESCENDING_ORDER_HPP_
#define _DESCENDING_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>
#include <numeric>

namespace container
{
    /**
     * @brief Iterator that traverses container elements in descending order
     * 
     * This iterator sorts the elements by value and provides access to them
     * from largest to smallest. The original container order is not modified;
     * only the traversal order changes.
     * 
     * Example: Container [5, 2, 8, 1] -> Descending iteration: [8, 5, 2, 1]
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::DescendingOrder : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates a descending order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the reverse-sorted traversal order.
         */
        DescendingOrder(MyContainer<T> &c) :  Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for descending order traversal
         * 
         * This method:
         * 1. Creates indices [0, 1, 2, ..., size-1]
         * 2. Sorts these indices based on element values in descending order
         * 3. Results in indices that point to elements from largest to smallest
         * 
         * Uses the greater-than operator (>) to sort in descending order.
         */
        void prepareIndices() override
        {
            this->indices.resize(this->original_container.size());
            std::iota(this->indices.begin(), this->indices.end(), 0);
            std::sort(this->indices.begin(), this->indices.end(), 
                [&](size_t i, size_t j) {
                    return this->original_container[i] > this->original_container[j];
                });
        }
    };
}

#endif