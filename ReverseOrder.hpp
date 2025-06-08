// galashkena1@gmail.com
#ifndef _REVERSE_ORDER_HPP_
#define _REVERSE_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>

namespace container
{
    template <typename T>
    class MyContainer<T>::ReverseOrder : public Iterator<T>
    {
    public:
        ReverseOrder(const MyContainer<T> &c) : Iterator<T>()
        {
            prepareData(c.getT());
            this->it = this->container.begin();
        }

    protected:
        void prepareData(const std::vector<T>& original_data) override
        {
            this->container = original_data;
            std::reverse(this->container.begin(), this->container.end());
        }
    };
}

#endif