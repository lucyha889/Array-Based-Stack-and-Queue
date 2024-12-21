#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class ABS {
private:
    T* data; //pointer to the array storing the stock elements
    int size; //current elements in the stock
    int capacity; //max capacity of the stack
    float staticScale; //factor in which the array will increase or decrease, in this case it will grow by 2.0f

    //purpose of private method is to resize the array
    void resize(float capFactor) {
        //solve for new capacity based on the scaling factor 
        int currentCap = static_cast<int>(capacity * capFactor);
        T* currentData = new T[currentCap];

        //purpose is to copy old elements to the new array
        for (int i = 0; i < size; ++i) {
            currentData[i] = data[i];
        }

        delete[] data;  //purpose is to get rid of old memory
        data = currentData;  //pointer to a new memory
        capacity = currentCap;  //update the capacity amount
    }

public:
    //default constructor that sets the size to 0, capacity to 1, and scale factor to 2.0f
    ABS() : size(0), capacity(1), staticScale(2.0f) {
        data = new T[capacity];
    }

    //parameterized constructor for ABS
    ABS(int firstCapacity) : size(0), capacity(firstCapacity), staticScale(2.0f) {
        data = new T[capacity];
    }

    //copy constructor for ABS
    ABS(const ABS& d) : size(d.size), capacity(d.capacity), staticScale(d.staticScale) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = d.data[i];
        }
    }

    //assignment operator for ABS
    ABS& operator=(const ABS& d) {
        if (this != &d) {
            delete[] data;
            //copy both size and capacity
            size = d.size;
            capacity = d.capacity;
            staticScale = d.staticScale;
            data = new T[capacity]; //allocate new memory for this stack
            //copy each element from the stack
            for (int i = 0; i < size; ++i) {
                data[i] = d.data[i];
            }
        }
        return *this;
    }

    // destructor which deallocates the dynamically allocated memory
    ~ABS() {
        delete[] data;
    }

    //purpose is to add an element to the stack through the push method
    void push(T value) {
        if (size == capacity) {
            resize(staticScale);  //doubles the size when full
        }
        data[size++] = value;  //adds element and increment size
    }

    //purpose was to remove the top element from the stack through the pop method
    T pop() {
        if (size == 0) {
            throw runtime_error("An error has occurred.");
        }
        T value = data[--size];  //decrements the size and get value

        //purpose is to resize the if it's less than 1/staticScale of the capacity
        if (size < capacity / staticScale && capacity > 1) {
            resize(1.0f / staticScale);
        }

        return value;
    }

    //purpose was to return the top element without removing it (peek)
    T peek() const {
        if (size == 0) {
            throw runtime_error("An error has occured.");
        }
        //return the top element 
        return data[size - 1];
    }

    //purpose was to get the current size of the stack
    unsigned int getSize() const {
        return size;
    }

    //purpose was to get the maximum capacity of the stack
    unsigned int getMaxCapacity() const {
        return capacity;
    }

    //purpose was to return the underlying array of the stack
    T* getData() const {
        return data;
    }
};