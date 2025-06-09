// galashkena1@gmail.com
#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <numeric>

namespace container
{
    /**
     * @brief Iterator that traverses container elements in their original insertion order
     * 
     * This iterator provides access to elements in the exact same order they were
     * added to the container. This is the "natural" order of the container.
     * 
     * Example: Container [5, 2, 8, 1] -> Order iteration: [5, 2, 8, 1]
     *          (same as insertion order)
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class MyContainer<T>::Order : public Iterator<T>
    {
    public:
        /**
         * @brief Constructor that creates an original order iterator
         * @param c Reference to the MyContainer to iterate over
         * 
         * Automatically calls prepareIndices() to set up the natural traversal order.
         */
        Order(MyContainer<T> &c) : Iterator<T>(c.getT())
        {
            prepareIndices();
        }

    protected:
        /**
         * @brief Prepares the indices for original order traversal
         * 
         * This method simply creates indices in sequential order [0, 1, 2, ..., size-1].
         * This results in traversing elements in their natural insertion order,
         * which is the same as iterating through the underlying vector normally.
         * 
         * This is the simplest iterator - no reordering is performed.
         */
        void prepareIndices() override
        {
            this->indices.resize(this->original_container.size());
            std::iota(this->indices.begin(), this->indices.end(), 0);
        }
    };
}

#endif