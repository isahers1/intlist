/**
 * intlist-test.cpp
 * CS 70 Starter Code
 * The program unit tests the IntList class.
 *
 * Part of CS70 Homework 5. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Include the testing-logger library from
// the CS70 system directory in Docker.

#include <cs70/testinglogger.hpp>

#include "intlist.hpp"
using namespace std;

///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////

// ISSUE 2 TESTS

/** \brief Test default constructor for IntLists
 */
bool defaultConstructorTest() {
    // Set up the TestingLogger object
    TestingLogger log("default constructor");

    IntList myList;

    // Add checks for things that should be true.
    affirm(myList.size() == 0);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 3 TESTS -------------------------------------------------

/** \brief Test empty
 *  \detail Tests that empty is true for a default intlist, and that
 *          it is false for a non-empty intlist.
 */
bool emptyTest() {
    // Set up the TestingLogger object
    TestingLogger log("empty");

    IntList myList;

    // check that the default initializer sets size to 0
    affirm(myList.empty());

    // check that empty() returns false after adding an element
    myList.push_front(42);
    affirm(!myList.empty());

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test push_front
 *  \detail Tests that push_front increases the list size
 *          and actually adds elements.
 */
bool pushFrontTest() {
    TestingLogger log("push front");

    // Initialize list to test
    IntList myList;
    myList.push_front(7);

    // test that push_front increments the size correctly
    affirm(myList.size() == 1);

    // create an iterator so we can access element values
    IntList::iterator iterOne = myList.begin();

    // check that the value in the first (only) element is 7
    affirm(*iterOne == 7);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test pop_front
 *  \detail Tests that pop_front decreases the list size
 *          and returns the value_ of the removed element.
 */
bool popFrontTest() {
    TestingLogger log("push front");

    // Initialize list to test and add two elements
    IntList myList;
    myList.push_front(3);
    myList.push_front(4);

    // remove the first element
    int v = myList.pop_front();

    // test that pop_front returns the removed element's value_
    affirm(v == 4);

    // test that pop_front decrements the list's size
    affirm(myList.size() == 1);

    // remove another element to test with an empty list
    int y = myList.pop_front();

    // test that pop_front again returns the reemoved element's value_
    affirm(y == 3);

    // and that the size is now 0 (empty list)
    affirm(myList.size() == 0);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 5 TESTS -------------------------------------------------

/** \brief Test begin
 *  \detail Tests that begin creates an iterator 
 *          starting at the front of the intlist
 */
bool beginTest() {
    TestingLogger log("begin");

    // initialize list with two elements
    IntList myList;
    myList.push_front(42);
    myList.push_back(43);

    // declare new iterator using begin
    IntList::iterator iter = myList.begin();

    // check that the iterator points to the first element
    affirm(iter == myList.begin());

    // check that the value in the element iterator points to is 42
    affirm(*iter == 42);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test end
 *  \detail Tests that end creates an iterator 
 *          that pointss to the last element of the list
 */
bool endTest() {
    TestingLogger log("end");

    // intialize a list with two elements
    IntList myList;
    myList.push_front(42);
    myList.push_front(41);

    // declare new iterator using end
    IntList::iterator iter = myList.end();

    // check that the iterator points to th elast element
    affirm(iter == myList.end());

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test iterator * operator
 *  \detail Tests that the * of an iterator returns 
 *          the value_ of the element that the iterator points to
 */
bool starTest() {
    TestingLogger log("star");

    // initialize new list with two values
    IntList myList;
    myList.push_front(42);
    myList.push_back(41);

    // declare an iterator pointing to the first element
    IntList::iterator iter = myList.begin();

    // check that the star operater returns the first value_
    affirm(*iter == 42);

    ++(iter);

    // chek that the star oprator returns the next value_ after
    // the iterator is inremented
    affirm(*iter == 41);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test operator==() for iterators 
 * \detail Test that the equals operator works for comparing two iterators
 */
bool iteratorEqualsTest() {
    // Set up the TestingLogger object
    TestingLogger log("iterator equals");

    IntList myList;

    myList.push_front(42);
    myList.push_front(41);

    IntList::iterator iterOne = myList.begin();
    IntList::iterator iterTwo = myList.begin();

    affirm(iterTwo == iterOne);

    ++iterOne;

    affirm(!(iterTwo == iterOne));

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test operator++() for iterators
 * \detail Test that the ++ operator works for incrementing an iterator
 */
bool iteratorPlusTest() {
    // Set up the TestingLogger object
    TestingLogger log("iterator plus");

    IntList myList;
    myList.push_front(42);
    myList.push_front(41);
    myList.push_front(43);

    IntList::iterator iter = myList.begin();

    ++iter;
    affirm(*iter == 41);

    ++iter;
    affirm(*iter == 42);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 6 TESTS -------------------------------------------------

/** \brief Test operator==() for intList's
 * \detail Test that the equals operator works for comparing two intLists
 */
bool listEqualsTest() {
    // Set up the TestingLogger object
    TestingLogger log("list equals");

    IntList myListOne;
    IntList myListTwo;

    affirm(myListOne == myListTwo);

    myListOne.push_front(42);
    myListOne.push_front(43);

    myListTwo.push_front(42);
    myListTwo.push_front(43);

    affirm(myListOne == myListTwo);

    myListOne.push_front(2021);

    affirm(!(myListOne == myListTwo));

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 7 TESTS -------------------------------------------------

/** \brief Test push_back() for intList's
 * \detail Test that push_back() adds element, and becomes the new back of list
 */
bool pushBackTest() {
    // Set up the TestingLogger object
    TestingLogger log("push_back");

    IntList myListOne;
    IntList myListTwo;

    myListOne.push_front(41);
    myListOne.push_back(43);

    myListTwo.push_front(41);
    myListTwo.push_back(43);

    affirm(myListOne.size() == 2);
    affirm(myListOne == myListTwo);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test insert_after() for intList's
 * \detail Test that inser_after() adds element, and next changes for 
 *  itself and previous element
 */
bool insertAfterTest() {
    // Set up the TestingLogger object
    TestingLogger log("insert after");

    IntList myList;

    myList.push_front(42);
    myList.push_front(43);
    myList.push_front(2021);

    IntList::iterator iter = myList.begin();
    ++iter;

    myList.insert_after(iter, 7);

    ++iter;
    affirm(*iter == 7);

    ++iter;
    affirm(*iter == 42);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 8 TESTS -------------------------------------------------
// Add tests here for the IntList copy constructor

/** \brief Test copy constructor for intList's
 * \detail Test that copying a list indeed copies it and also preserves equality 
 */
bool copyConstruct() {
    // Set up the TestingLogger object
    TestingLogger log("copy constructor");

    IntList myList;
    IntList empty = myList;

    affirm(empty == myList);

    myList. push_front(42);
    myList.push_front(43);
    myList.push_front(44);

    IntList copiedList = myList;

    affirm(copiedList == myList);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/*
 * Test the IntList!
 */
int main(int, char**) {
    TestingLogger alltests("All tests");

    affirm(defaultConstructorTest());

    affirm(emptyTest());

    affirm(pushFrontTest());

    affirm(popFrontTest());

    affirm(beginTest());

    affirm(endTest());

    affirm(starTest());

    affirm(iteratorEqualsTest());

    affirm(iteratorPlusTest());

    affirm(listEqualsTest());

    affirm(pushBackTest());

    affirm(insertAfterTest());

    affirm(copyConstruct());

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
