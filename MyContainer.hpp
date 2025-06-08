// galashkena1@gmail.com
#ifndef _MY_CONTAINER_HPP_
#define _MY_CONTAINER_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

namespace container
{
    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> t;

    public:
        MyContainer() {}
        MyContainer(size_t size) : t(size) {}

        void add(const T &element) { t.push_back(element); }

        void remove(const T &element)
        {
            auto it = std::find(t.begin(), t.end(), element);
            if (it == t.end())
            {
                throw std::invalid_argument("Element not found in container");
            }
            for (auto it = t.begin(); it != t.end();)
            {
                if (*it == element)
                {
                    it = t.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        size_t size() const { return t.size(); }

        const std::vector<T> &getT() const
        {
            return t;
        }

        friend std::ostream &operator<<(std::ostream &os, const MyContainer<T> &c)
        {
            os << "[";
            for (size_t i = 0; i < c.t.size(); ++i)
            {
                os << c.t[i];
                if (i < c.t.size() - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }

        class AscendingOrder;
        class DescendingOrder;
        class SideCrossOrder;
        class ReverseOrder;
        class Order;
        class MiddleOutOrder;

        AscendingOrder ascending() const { return AscendingOrder(*this); }
        DescendingOrder descending() const { return DescendingOrder(*this); }
        SideCrossOrder sidecross() const { return SideCrossOrder(*this); }
        ReverseOrder reverse() const { return ReverseOrder(*this); }
        Order order() const { return Order(*this); }
        MiddleOutOrder middleout() const { return MiddleOutOrder(*this); }
    };
}

#endif