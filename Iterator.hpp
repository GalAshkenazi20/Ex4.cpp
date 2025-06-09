// galashkena1@gmail.com
#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <vector>
#include <iostream>
#include <stdexcept>

namespace container
{
    /**
     * @brief Base exception class for iterator-related errors
     */
    class IteratorException : public std::runtime_error {
    public:
        IteratorException(const std::string& msg) : std::runtime_error("Iterator error: " + msg) {}
    };

    /**
     * @brief Exception thrown when an iterator is in an invalid state
     */
    class InvalidIteratorException : public IteratorException {
    public:
        InvalidIteratorException() : IteratorException("Iterator is in invalid state") {}
    };

    /**
     * @brief Abstract base class for all iterator types
     * 
     * This class provides the foundation for different iteration patterns.
     * It manages indices that determine the order of traversal and provides
     * a custom iterator interface for range-based for loops.
     * 
     * @tparam T The type of elements in the container
     */
    template <typename T>
    class Iterator
    {
    protected:
        std::vector<T>& original_container;  
        std::vector<size_t> indices;        

    public:
        /**
         * @brief Constructor that creates an iterator for the given container
         * @param container Reference to the container to iterate over
         * @throws InvalidIteratorException if the container is empty
         */
        Iterator(std::vector<T>& container) : original_container(container) {
            if (container.empty()) {
                throw InvalidIteratorException();
            }
        }
        
        /**
         * @brief Virtual destructor for proper inheritance
         */
        virtual ~Iterator() = default;
        
        /**
         * @brief Custom iterator class that implements the actual iteration logic
         * 
         * This nested class provides the standard iterator interface (*, ++, ==, !=)
         * and includes safety checks to prevent invalid operations.
         */
        class custom_iterator {
        private:
            std::vector<T>& container;           ///< Reference to the data container
            typename std::vector<size_t>::iterator idx_it;      ///< Current position in indices
            typename std::vector<size_t>::iterator indices_begin; ///< Begin iterator for bounds checking
            typename std::vector<size_t>::iterator indices_end;   ///< End iterator for bounds checking
            
        public:
            /**
             * @brief Constructor for the custom iterator
             * @param cont Reference to the data container
             * @param it Current position iterator
             * @param begin_it Begin iterator for bounds checking
             * @param end_it End iterator for bounds checking
             */
            custom_iterator(std::vector<T>& cont, 
                          typename std::vector<size_t>::iterator it,
                          typename std::vector<size_t>::iterator begin_it,
                          typename std::vector<size_t>::iterator end_it) 
                : container(cont), idx_it(it), indices_begin(begin_it), indices_end(end_it) {}
                
            /**
             * @brief Dereference operator - returns reference to current element
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is at end or index is invalid
             */
            T& operator*() { 
                if (idx_it == indices_end) {
                    throw std::out_of_range("Iterator is at end position - cannot dereference");
                }
                if (*idx_it >= container.size()) {
                    throw std::out_of_range("Invalid index in iterator: " + std::to_string(*idx_it));
                }
                return container[*idx_it]; 
            }
            
            /**
             * @brief Const dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or index is invalid
             */
            const T& operator*() const { 
                if (idx_it == indices_end) {
                    throw std::out_of_range("Iterator is at end position - cannot dereference");
                }
                if (*idx_it >= container.size()) {
                    throw std::out_of_range("Invalid index in iterator: " + std::to_string(*idx_it));
                }
                return container[*idx_it]; 
            }
            
            /**
             * @brief Pre-increment operator - moves iterator to next position
             * @return Reference to this iterator
             * @throws std::out_of_range if trying to increment beyond end
             */
            custom_iterator& operator++() { 
                if (idx_it == indices_end) {
                    throw std::out_of_range("Cannot increment iterator beyond end");
                }
                ++idx_it; 
                return *this; 
            }
            
            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return True if iterators point to different positions
             */
            bool operator!=(const custom_iterator& other) const { 
                return idx_it != other.idx_it; 
            }
            
            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return True if iterators point to the same position
             */
            bool operator==(const custom_iterator& other) const { 
                return idx_it == other.idx_it; 
            }
        };
        
        /**
         * @brief Returns iterator pointing to the beginning of the traversal
         * @return custom_iterator pointing to the first element
         * @throws InvalidIteratorException if indices are empty
         */
        custom_iterator begin() { 
            if (indices.empty()) {
                throw InvalidIteratorException();
            }
            return custom_iterator(original_container, indices.begin(), indices.begin(), indices.end()); 
        }
        
        /**
         * @brief Returns iterator pointing to the end of the traversal
         * @return custom_iterator pointing past the last element
         * @throws InvalidIteratorException if indices are empty
         */
        custom_iterator end() { 
            if (indices.empty()) {
                throw InvalidIteratorException();
            }
            return custom_iterator(original_container, indices.end(), indices.begin(), indices.end()); 
        }

        /**
         * @brief Stream output operator for printing iterator contents
         * @param os Output stream
         * @param iter Iterator to print
         * @return Reference to the output stream
         * 
         * Prints all elements in the iterator's traversal order in format: [elem1, elem2, ...]
         * If an error occurs during iteration, prints an error message instead.
         */
        friend std::ostream& operator<<(std::ostream& os, Iterator& iter) {
            try {
                os << "[";
                bool first = true;
                for (auto value : iter) {
                    if (!first) os << ", ";
                    os << value;
                    first = false;
                }
                os << "]";
            } catch (const std::exception& e) {
                os << "[ERROR: " << e.what() << "]";
            }
            return os;
        }

    protected:
        /**
         * @brief Pure virtual method that derived classes must implement
         * 
         * This method should populate the indices vector to define the
         * specific traversal order for each iterator type.
         */
        virtual void prepareIndices() = 0;
    };
}

#endif