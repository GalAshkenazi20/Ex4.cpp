// galashkena1@gmail.com
#ifndef _DESCENDING_ORDER_HPP_
#define _DESCENDING_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>

namespace container
{
    template <typename T>
    class MyContainer<T>::DescendingOrder : public Iterator<T>
    {
    public:
        DescendingOrder(const MyContainer<T> &c) : Iterator<T>()
        {
            prepareData(c.getT());
            this->it = this->container.begin();
        }

    protected:
        void prepareData(const std::vector<T>& original_data) override
        {
            this->container = original_data;
            std::sort(this->container.begin(), this->container.end(), std::greater<T>());
        }
    };
}

#endif