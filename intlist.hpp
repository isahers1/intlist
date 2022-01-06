/**
 * intlist.hpp
 * A list of ints.
 *
 * Part of CS70 Homework 5. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 *
 */

#ifndef INTLIST_HPP_INCLUDED
#define INTLIST_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include <utility>

/**
 * IntList
 *
 * A linked list of many Element objects which hold \c ints.
 *
 * Class allocates memory dynamically; thus can't use C++'s
 *          defaults for copy constructor, assignment operator and
 *          destructor.
 */
class IntList {
 private:
    // Forward declaration of private class.
    class Iterator;

 public:
    IntList();
    IntList(const IntList& orig);
    IntList& operator=(const IntList& rhs);
    ~IntList();
    void swap(IntList& rhs);


   /**
    * \brief Push to front of intList
    * \param integer to push
    * \returns void
    **/
    void push_front(int pushee);  // Push onto head of list

    /**
    * \brief Push to back of intList
    * \param integer to push
    * \returns void
    **/
    void push_back(int pushee);   // Push onto tail of list

    /**
    * \brief Drop first element of intList
    * \param None
    * \returns integer value of first element
    **/
    int pop_front();              // Drop & return the head element

   /**
    * \brief Get size of intlist
    * \param None
    * \returns size_t of size of the intlist
    **/
    size_t size() const;  // Size of the list

    /**
    * \brief Check if list is empty
    * \param None
    * \returns bool whether list is empty
    **/
    bool empty() const;   // true if the list is empty

    bool operator==(const IntList& rhs) const;
    bool operator!=(const IntList& rhs) const;

    // Allow clients to iterate over the contents of the list.
    using iterator = Iterator;
    iterator begin() const;  // An iterator that refers to the first element
    iterator end() const;    // A "past-the-end" iterator

    /**
    * \brief Insert element in given position in list
    * \param iterator for where to push, integer to push
    * \returns void
    **/
    void insert_after(iterator where, int value);

 private:
    /*
     * Element
     *
     * The list is stored as a linked list of Elements.
     *        The class is private so only IntList knows about it.
     *        A constructor is provided for convenience.
     *
     * The Copy Constructor and Assignment operator are disabled.
     */
    struct Element {
        // Data members
        int value_;
        Element* next_;

        // Convenience constructor
        Element(int value, Element* next);

        // Disabled functions
        Element() = delete;
        Element(const Element&) = delete;
        Element& operator=(const Element&) = delete;
        ~Element() = default;  // If you don't like this, you can change it.
    };

    Element* back_;   // Current tail of list
    Element* front_;  // Current head of list
    size_t size_;     // Current size of list

    bool consistent() const;

    /*
     * Iterator
     * STL-style iterator for IntList.
     */
    class Iterator {
     public:
        // Definitions that are required for this class to be a well-behaved
        // STL-style iterator that moves forward through a collection of ints.
        using value_type = int;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        // Provide all the usual operations for a forward iterator

        Iterator() = default;
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;
        ~Iterator() = default;

        Iterator& operator++();
        reference operator*() const;

        /**
       * \brief Check whether iterators are equal
       * \param iterator to check
       * \returns boolean whether the values of the iterators are equal
       **/
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;

     private:
        friend class IntList;
        explicit Iterator(Element* current);
        // Friends create non-default iterators
        Element* current_;  // The current list node
    };
};

// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(IntList& lhs, IntList& rhs);

#endif  // INTLIST_HPP_INCLUDED
