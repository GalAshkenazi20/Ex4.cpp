// galashkena1@gmail.com
#ifndef _REVERSE_ORDER_HPP_
#define _REVERSE_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <numeric>
#include <algorithm>

namespace container
{
    /**
     * @brief Iterator that traverses container elements in reverse insertion order
     * 
     * This iterator provides access to elements in the opposite order from how
     * they were inserted into the container. It reverses the physical positions,
     * not the sorted values.
     * 
     * Example: Container [5, 2, 8, 1] -> Reverse iteration: [1, 8, 2, 5]
     *          (last inserted first, first inserted last)
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::ReverseOrder : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates a reverse order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the reversed traversal order.
         */
        ReverseOrder(MyContainer<T> &c) : Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for reverse order traversal
         * 
         * This method:
         * 1. Creates indices in normal order [0, 1, 2, ..., size-1]
         * 2. Reverses the entire indices array
         * 3. Results in traversal order [size-1, size-2, ..., 1, 0]
         * 
         * This gives access to elements in reverse insertion order.
         */
        void prepareIndices() override
        {
            this->indices.resize(this->original_container.size());
            std::iota(this->indices.begin(), this->indices.end(), 0);
            std::reverse(this->indices.begin(), this->indices.end());
        }
    };
}

#endif