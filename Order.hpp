// galashkena1@gmail.com
#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"

namespace container
{
    template <typename T>
    class MyContainer<T>::Order : public Iterator<T>
    {
    public:
        Order(const MyContainer<T> &c) : Iterator<T>()
        {
            prepareData(c.getT());
            this->it = this->container.begin();
        }

    protected:
        void prepareData(const std::vector<T>& original_data) override
        {
            this->container = original_data;
        }
    };
}

#endif