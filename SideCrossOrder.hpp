// galashkena1@gmail.com
#ifndef _SIDE_CROSS_ORDER_HPP_
#define _SIDE_CROSS_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"
#include <algorithm>

namespace container
{
    template <typename T>
    class MyContainer<T>::SideCrossOrder : public Iterator<T>
    {
    public:
        SideCrossOrder(const MyContainer<T> &c) : Iterator<T>()
        {
            prepareData(c.getT());
            this->it = this->container.begin();
        }

    protected:
        void prepareData(const std::vector<T>& original_data) override
        {
            std::vector<T> sortedData = original_data;
            std::sort(sortedData.begin(), sortedData.end());
            
            this->container.clear();
            size_t left = 0;
            size_t right = sortedData.size() - 1;
            bool take_left = true;

            while (left <= right)
            {
                if (take_left)
                {
                    this->container.push_back(sortedData[left]);
                    ++left;
                }
                else
                {
                    this->container.push_back(sortedData[right]);
                    --right;
                }
                take_left = !take_left;
                
                if (left > right) break;
            }
        }
    };
}

#endif