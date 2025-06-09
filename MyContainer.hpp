// galashkena1@gmail.com
#ifndef _MY_CONTAINER_HPP_
#define _MY_CONTAINER_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>

namespace container
{
    /**
     * @brief Exception thrown when trying to operate on an empty container
     * 
     * This exception is thrown when operations like remove() or creating iterators
     * are attempted on containers that have no elements.
     */
    class ContainerEmptyException : public std::runtime_error {
    public:
        ContainerEmptyException() : std::runtime_error("Container is empty - cannot perform operation") {}
    };

    /**
     * @brief Exception thrown when trying to find an element that doesn't exist
     * 
     * This exception is thrown when the remove() method cannot find the
     * specified element in the container.
     */
    class ElementNotFoundException : public std::runtime_error {
    public:
        ElementNotFoundException(const std::string& msg) : std::runtime_error("Element not found: " + msg) {}
    };

    /**
     * @brief Exception thrown when accessing invalid array indices
     * 
     * This exception is thrown when trying to access elements using at() or []
     * operators with an index that is out of bounds.
     */
    class IndexOutOfBoundsException : public std::out_of_range {
    public:
        IndexOutOfBoundsException(size_t index, size_t size) 
            : std::out_of_range("Index " + std::to_string(index) + " is out of bounds. Container size: " + std::to_string(size)) {}
    };

    /**
     * @brief A container class that stores elements and provides different iteration orders
     * 
     * MyContainer is a wrapper around std::vector that allows you to iterate through
     * elements in various orders: ascending, descending, reverse, side-cross, and middle-out.
     * You can also modify elements through iterators while maintaining the original order.
     * 
     * @tparam T The type of elements stored in the container (default: int)
     */
    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> t;  ///< Internal storage for elements

    public:
        /**
         * @brief Default constructor - creates an empty container
         */
        MyContainer() {}

        /**
         * @brief Constructor that creates a container with a specific size
         * @param size The initial size of the container
         */
        MyContainer(size_t size) : t(size) {}

        /**
         * @brief Adds an element to the end of the container
         * @param element The element to add
         */
        void add(const T &element) { 
            t.push_back(element); 
        }

        /**
         * @brief Removes all occurrences of the specified element from the container
         * @param element The element to remove
         * @throws ContainerEmptyException if the container is empty
         * @throws ElementNotFoundException if the element is not found
         */
        void remove(const T &element)
        {
            if (t.empty()) {
                throw ContainerEmptyException();
            }

            auto it = std::find(t.begin(), t.end(), element);
            if (it == t.end()) {
                throw ElementNotFoundException("Value: " + std::to_string(element));
            }

            // Remove all occurrences
            for (auto it = t.begin(); it != t.end();) {
                if (*it == element) {
                    it = t.erase(it);
                } else {
                    ++it;
                }
            }
        }

        /**
         * @brief Access element at specific index with bounds checking
         * @param index The index of the element to access
         * @return Reference to the element at the specified index
         * @throws IndexOutOfBoundsException if index is invalid
         */
        T& at(size_t index) {
            if (index >= t.size()) {
                throw IndexOutOfBoundsException(index, t.size());
            }
            return t[index];
        }

        /**
         * @brief Access element at specific index with bounds checking (const version)
         * @param index The index of the element to access
         * @return Const reference to the element at the specified index
         * @throws IndexOutOfBoundsException if index is invalid
         */
        const T& at(size_t index) const {
            if (index >= t.size()) {
                throw IndexOutOfBoundsException(index, t.size());
            }
            return t[index];
        }

        /**
         * @brief Array subscript operator with bounds checking
         * @param index The index of the element to access
         * @return Reference to the element at the specified index
         * @throws IndexOutOfBoundsException if index is invalid
         */
        T& operator[](size_t index) {
            if (index >= t.size()) {
                throw IndexOutOfBoundsException(index, t.size());
            }
            return t[index];
        }

        /**
         * @brief Array subscript operator with bounds checking (const version)
         * @param index The index of the element to access
         * @return Const reference to the element at the specified index
         * @throws IndexOutOfBoundsException if index is invalid
         */
        const T& operator[](size_t index) const {
            if (index >= t.size()) {
                throw IndexOutOfBoundsException(index, t.size());
            }
            return t[index];
        }

        /**
         * @brief Returns the number of elements in the container
         * @return The size of the container
         */
        size_t size() const { return t.size(); }

        /**
         * @brief Checks if the container is empty
         * @return True if the container has no elements, false otherwise
         */
        bool empty() const { return t.empty(); }

        /**
         * @brief Removes all elements from the container
         */
        void clear() { t.clear(); }

        /**
         * @brief Get const reference to the internal vector
         * @return Const reference to the internal storage
         */
        const std::vector<T> &getT() const { return t; }

        /**
         * @brief Get reference to the internal vector
         * @return Reference to the internal storage
         */
        std::vector<T> &getT() { return t; }

        /**
         * @brief Stream output operator for printing the container
         * @param os Output stream
         * @param c Container to print
         * @return Reference to the output stream
         * 
         * Prints the container in format: [element1, element2, element3]
         */
        friend std::ostream &operator<<(std::ostream &os, const MyContainer<T> &c)
        {
            if (c.t.empty()) {
                os << "[]";
                return os;
            }

            os << "[";
            for (size_t i = 0; i < c.t.size(); ++i) {
                os << c.t[i];
                if (i < c.t.size() - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }

        // Forward declarations for iterator classes
        class AscendingOrder;
        class DescendingOrder;
        class SideCrossOrder;
        class ReverseOrder;
        class Order;
        class MiddleOutOrder;

        /**
         * @brief Creates an iterator that traverses elements in ascending (sorted) order
         * @return AscendingOrder iterator
         * @throws ContainerEmptyException if the container is empty
         */
        AscendingOrder ascending() { 
            if (t.empty()) throw ContainerEmptyException();
            return AscendingOrder(*this); 
        }
        
        /**
         * @brief Creates an iterator that traverses elements in descending order
         * @return DescendingOrder iterator
         * @throws ContainerEmptyException if the container is empty
         */
        DescendingOrder descending() { 
            if (t.empty()) throw ContainerEmptyException();
            return DescendingOrder(*this); 
        }
        
        /**
         * @brief Creates an iterator that alternates between smallest and largest remaining elements
         * @return SideCrossOrder iterator
         * @throws ContainerEmptyException if the container is empty
         */
        SideCrossOrder sidecross() { 
            if (t.empty()) throw ContainerEmptyException();
            return SideCrossOrder(*this); 
        }
        
        /**
         * @brief Creates an iterator that traverses elements in reverse order of insertion
         * @return ReverseOrder iterator
         * @throws ContainerEmptyException if the container is empty
         */
        ReverseOrder reverse() { 
            if (t.empty()) throw ContainerEmptyException();
            return ReverseOrder(*this); 
        }
        
        /**
         * @brief Creates an iterator that traverses elements in their original insertion order
         * @return Order iterator
         * @throws ContainerEmptyException if the container is empty
         */
        Order order() { 
            if (t.empty()) throw ContainerEmptyException();
            return Order(*this); 
        }
        
        /**
         * @brief Creates an iterator that starts from the middle and expands outward
         * @return MiddleOutOrder iterator
         * @throws ContainerEmptyException if the container is empty
         */
        MiddleOutOrder middleout() { 
            if (t.empty()) throw ContainerEmptyException();
            return MiddleOutOrder(*this); 
        }
    };
}

#endif