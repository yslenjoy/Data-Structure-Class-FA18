/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    if (s.size() == 0) {
        return 0;
    }
    T tmp = s.top();
    s.pop();
    T total = sum(s) + tmp;
    s.push(tmp);

    return total; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets. 
 * A string will consist of 
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    // @TODO: Make less optimistic
    
    // strcmp(input.front(), "") == 0
    stack<char> s;
    if (input.size() == 0) {
        return true;
    }
    int leftCount = 0;
    int rightCount = 0;
    while (input.size() != 0) {
        // char front = input.front();
        // cout << input.front() << " here-------" << endl;
        // std::cout<<"front is of type: "<<typeid(input.front()).name()<<std::endl;
        if (input.front() == '[') {
            leftCount++;
        }
        if (input.front() == ']') {
            rightCount++;
        }
        input.pop();
        if (rightCount > leftCount) {
            return false;
        }
    }
    if (leftCount == rightCount) {
        return true;
    } else {
        return false;
    }
    
    // return true;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    // stack<T> s;
    // optional: queue<T> q2;
    queue<T> q2;
    // Your code here
    int total = q.size();
    int grouped = 0; // used as iterator
    int groupSize = 1;
    bool finished = false;
    bool reverse = false;

    while (grouped < total) {
        if ((total-grouped) < (groupSize + 1)) {
            finished = true;
            groupSize = total - grouped;
        }
        if (reverse) {
            // do the reverse
            
            // T tmpArray[groupSize]; error: variable length arrays are a C99 (cannot create dynamic array directly without key word new)
            T tmpArray[20];
            for (int i = 0; i < groupSize; i++) {
                T added = q.front();
                q.pop();
                tmpArray[i] = added;
            }
            for (int i = 0; i < groupSize; i++) {
                q2.push(tmpArray[groupSize-1-i]);
            }

            
        } else {
            // don't do the reverse
            for (int j = 0; j < groupSize; j++) {
                T added = q.front();
                q.pop();
                q2.push(added);
            }
        }
        grouped += groupSize;
        groupSize++;
        reverse = !reverse;
        if (finished) {
            break;
        }
    }
    q = q2;
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool r = true; // optional
    // T temp1; // rename me
    // T temp2; // rename :)

    // Your code here

    // base case
    if (s.empty()) { // go to the end of stack first, compare the buttom of stack with the front of queue
        return true;
    }
    T stackValue = s.top();
    s.pop();


    r = verifySame(s, q);
    // check last element stackVale is the same as the front of queue
    r = (r && (stackValue == q.front()));


    T queueValue = q.front();
    q.pop();
    q.push(queueValue); // put the first value to the end of the queue

    // put stackValue back to the stack (original location)
    s.push(stackValue);

    return r;
}

}
