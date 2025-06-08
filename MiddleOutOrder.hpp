// galashkena1@gmail.com
#ifndef _MIDDLE_OUT_ORDER_HPP_
#define _MIDDLE_OUT_ORDER_HPP_

#include "MyContainer.hpp"
#include "Iterator.hpp"

namespace container
{
    template <typename T>
    class MyContainer<T>::MiddleOutOrder : public Iterator<T>
    {
    public:
        MiddleOutOrder(const MyContainer<T> &c) : Iterator<T>()
        {
            prepareData(c.getT());
            this->it = this->container.begin();
        }

    protected:
        void prepareData(const std::vector<T>& original_data) override
        {
            this->container.clear();
            if (original_data.empty()) return;
            
            size_t middle = original_data.size() / 2;
            this->container.push_back(original_data[middle]);
            
            int left = middle - 1;
            int right = middle + 1;
            bool take_left = true;
            
            while (left >= 0 || right < static_cast<int>(original_data.size()))
            {
                if (take_left && left >= 0)
                {
                    this->container.push_back(original_data[left]);
                    --left;
                }
                else if (!take_left && right < static_cast<int>(original_data.size()))
                {
                    this->container.push_back(original_data[right]);
                    ++right;
                }
                else if (left >= 0)
                {
                    this->container.push_back(original_data[left]);
                    --left;
                }
                else if (right < static_cast<int>(original_data.size()))
                {
                    this->container.push_back(original_data[right]);
                    ++right;
                }
                take_left = !take_left;
            }
        }
    };
}

#endif