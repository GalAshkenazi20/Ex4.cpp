// galashkena1@gmail.com
#ifndef _ASCENDING_ORDER_HPP_
#define _ASCENDING_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>
#include <numeric>

namespace container
{
    /**
     * @brief Iterator that traverses container elements in ascending (sorted) order
     * 
     * This iterator sorts the elements by value and provides access to them
     * from smallest to largest. The original container order is not modified;
     * only the traversal order changes.
     * 
     * Example: Container [5, 2, 8, 1] -> Ascending iteration: [1, 2, 5, 8]
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::AscendingOrder : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates an ascending order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the sorted traversal order.
         */
        AscendingOrder(MyContainer<T> &c) : Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for ascending order traversal
         * 
         * This method:
         * 1. Creates indices [0, 1, 2, ..., size-1]
         * 2. Sorts these indices based on the actual element values
         * 3. Results in indices that point to elements in ascending value order
         * 
         * The sorting uses element values but rearranges indices, so the
         * original container remains unchanged.
         */
        void prepareIndices() override
        {
            this->indices.resize(this->original_container.size());
            std::iota(this->indices.begin(), this->indices.end(), 0);
            std::sort(this->indices.begin(), this->indices.end(), 
                [&](size_t i, size_t j) {
                    return this->original_container[i] < this->original_container[j];
                });
        }
    };
}

#endif