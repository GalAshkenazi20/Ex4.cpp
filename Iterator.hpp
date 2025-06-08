// galashkena1@gmail.com
#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <vector>

namespace container
{
    template <typename T>
    class Iterator
    {
    protected:
        std::vector<T> container;
        typename std::vector<T>::const_iterator it;

    public:
        Iterator() = default;
        Iterator(const std::vector<T>& data) : container(data), it(container.begin()) {}
        virtual ~Iterator() = default;
        
        // Iterator operations
        T operator*() const { return *it; }
        
        Iterator& operator++() { 
            ++it; 
            return *this; 
        }
        
        bool operator!=(const Iterator& other) const { 
            return it != other.it; 
        }
        
        bool operator==(const Iterator& other) const { 
            return it == other.it; 
        }
        
        Iterator begin() { 
            it = container.begin(); 
            return *this; 
        }
        
        Iterator end() { 
            Iterator temp = *this;
            temp.it = container.end(); 
            return temp; 
        }

    protected:
        // Pure virtual method for data preparation
        virtual void prepareData(const std::vector<T>& original_data) = 0;
    };
}

#endif