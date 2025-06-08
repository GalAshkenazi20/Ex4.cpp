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
        virtual ~Iterator() = default;
        
        // Iterator operations for the iterator itself
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
        
        // For range-based for loops - return iterators to the container
        typename std::vector<T>::const_iterator begin() const {
            return container.begin();
        }
        
        typename std::vector<T>::const_iterator end() const {
            return container.end();
        }

    protected:
        // Pure virtual method for data preparation
        virtual void prepareData(const std::vector<T>& original_data) = 0;
    };
}

#endif