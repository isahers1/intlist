/*
 * intlist.cpp
 * Authors: Isaac & Tejus
 * Implemenation of IntList and its private classes.
 * Part of CS70 Homework 5. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 */

#include <utility>

// Include the testing-logger library from
// the CS70 system directory in Docker.
#include <cs70/testinglogger.hpp>

#include "intlist.hpp"
#include <iostream>
using namespace std;

IntList::IntList() : back_(nullptr), front_(nullptr), size_(0) {
    affirm(consistent() && empty());
}

IntList::~IntList() {
    // delete the front element until the list is empty
    while (!empty()) {
        pop_front();
    }
}

IntList::IntList(const IntList& orig) : back_{nullptr},
    front_{nullptr}, size_{0} {
    // make sure list is not empty before going
    if (!orig.empty()) {
        Iterator iterOrig{orig.begin()};
        Iterator iterOrigEnd{orig.end()};
        // add front and back to our newlist
        push_back(*iterOrigEnd);
        push_front(*iterOrig);

        Iterator iterNew{begin()};
        // while we are in middle of the old list,
        // we just insert_after current element
        while ((iterOrig.current_) -> next_ != orig.back_) {
            ++iterOrig;
            insert_after(iterNew, *iterOrig);
            ++iterNew;
        }
    }

    affirm(consistent());
}

void IntList::swap(IntList& rhs) {
    // This is the canonical way to swap arbitrary types; this incantation
    // will call std::swap unless we're swapping a class that provides its
    // own swap function (like we do), in which case that swap is called.
    // Here we end up calling std::swap since the swapped parts are primitives.

    using std::swap;

    swap(back_, rhs.back_);
    swap(front_, rhs.front_);
    swap(size_, rhs.size_);
    affirm(consistent());
}

void swap(IntList& lhs, IntList& rhs) { lhs.swap(rhs); }

IntList& IntList::operator=(const IntList& rhs) {
    // Assignment is implemented idiomatically for C++, using "the swap trick"
    IntList copy = rhs;
    swap(copy);

    affirm(consistent());
    return *this;
}


size_t IntList::size() const { return size_; }

bool IntList::empty() const {
    return size_ == 0;
}

bool IntList::operator==(const IntList& rhs) const {
    // Return false if the lists aren't the same size
    if (rhs.size() != size()) {
        return false;
    }
    // Return true if they are both empty
    if (rhs.size() == 0 && size() == 0) {
        return true;
    }

    Iterator iterRhs{rhs.begin()};
    Iterator iterThis{begin()};
    // Iterate over the lists from start to end - 1 element
    while (iterRhs != rhs.end()) {
        // Return false if the values in each list at the
        // iterator position aren't equal
        if (*iterRhs != *iterThis) {
            return false;
        }
        ++(iterRhs);
        ++(iterThis);
    }
    // Return true if the last value in the last list elements are equal
    return *iterRhs == *iterThis;
}


bool IntList::operator!=(const IntList& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !operator==(rhs);
}



void IntList::push_front(int pushee) {
    ++size_;
    front_ = new Element(pushee, front_);
    // if the list is empty, set back_ to front_ as well since there will
    // now only be one element in the list
    if (back_ == nullptr) {
        back_ = front_;
    }
    affirm(consistent() && !empty());
}



int IntList::pop_front() {
    // separate case when value is nonexistant
    if (size_ == 0) {
        return 0;
    } else {
        // save the value of the front element to return later
        int value = front_->value_;
        --size_;
        Element* oldFront = front_;

        // if size_ is 0 after decrementing, set nullptr's
        // else set front to be the old fron't next.
        if (size_ == 0) {
            front_ = nullptr;
            back_ = nullptr;
        } else {
            front_ = front_->next_;
        }
        delete oldFront;
        affirm(consistent());
        return value;
    }
}


void IntList::push_back(int pushee) {
    // in case where list is empty, simply call push_front since in this case
    // it will have the same affect on the list
    if (size_ == 0) {
        push_front(pushee);
    } else {
        ++size_;
        Element* oldBack = back_;

        back_ = new Element(pushee, nullptr);
        oldBack -> next_ = back_;

        affirm(consistent() && !empty());
    }
}


void IntList::insert_after(iterator where, int value) {
    // In case where we are inserting after the back, simply call push_back
    if (where.current_ == back_) {
        push_back(value);
    } else {
        ++size_;
        (where.current_) -> next_ =
            new Element(value, (where.current_) -> next_);
    }
    affirm(consistent() && !empty());
}



IntList::iterator IntList::begin() const {
    return IntList::Iterator(front_);
}



IntList::iterator IntList::end() const {
    return IntList::Iterator(back_);
}


bool IntList::consistent() const {
    return ((front_ == nullptr) && (back_ == nullptr) && (size_ == 0)) ||
           ((front_ == back_) && (size_ == 1)) ||
           ((front_ != back_) && (size_ > 1));
}

// --------------------------------------
// Implementation of IntList::Element
// --------------------------------------

IntList::Element::Element(int value, Element* next)
    : value_(value), next_(next) {
    // Nothing else to do.
}

// --------------------------------------
// Implementation of IntList::Iterator
// --------------------------------------

IntList::Iterator::Iterator(Element* current) : current_(current) {
    // Nothing else to do.
}


IntList::Iterator& IntList::Iterator::operator++() {
    current_ = current_ -> next_;
    return *this;
}



IntList::Iterator::reference IntList::Iterator::operator*() const {
    return current_ -> value_;
}



bool IntList::Iterator::operator==(const Iterator& rhs) const {
    return current_ == rhs.current_;
}

bool IntList::Iterator::operator!=(const Iterator& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}
