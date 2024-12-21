#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class ABQ {
private:
    T*data;
    int size;
    int capacity;
    float staticScale; 

    void resize(int currentCap) {
        T * newData = new T[currentCap];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = currentCap;
    }
public:
    //default constructor with an empty queue with a capacity of 1 and scale factor set to 2.0f
    ABQ() : size(0), capacity(1), staticScale(2.0f) {
        data = new T[capacity];
    }
    //constructor with custom capacity
    ABQ(int capacity) : size(0), capacity(capacity), staticScale(2.0f) {
        data = new T[capacity];
    }
   //copy constructor to create a deep copy of another ABQ object
    ABQ(const ABQ& d) : size(d.size), capacity(d.capacity), staticScale(2.0f) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data = d.data;
        }
    }
    //assignment operator set up same way as ABS 
    ABQ& operator = (const ABQ &d) {
        if (this != &d) {
            delete[] data;
            size = d.size; //copy the size
            capacity = d.capacity; //copy the capacity amount
            staticScale = d.staticScale;
            data = new T[capacity]; //allocate new memory for this stack
            //copy each element from the stack
            for (int i = 0; i < size; ++i) {
                data[i] = d.data[i];
            }
        }
        return *this;
    }
    ~ABQ() {
        delete[] data;
    }
    //function to add a new element to the queue
    void enqueue(T value) {
        if (size == capacity) { //if the array is full, resize it
            resize(capacity * staticScale);
        }
        data[size] = value; //add new element to end of the queue
        ++size; //increment size of the queue
    }
    //function to remove first element from the queue
    T dequeue() {
        if (size == 0) {
            throw runtime_error("An error has occured.");
        }
        T value = data[0];
        //used to shift remaining elements to the left
        for (int i = 1; i < size; ++i) {
            data[i - 1] = data[i];
        }
        --size;//decrement size of the queue
        //if queue is less than half full, resize it down
        if (size < capacity / staticScale) {
            resize(capacity / staticScale);
        }
        return value;
    }
    //return first element without removing it
    T peek() const {
        if (size == 0) {
            throw runtime_error("An error has occured.");
        }
        return data[0];
    }

    //retrieve the current size
    unsigned int getSize() const {
        return size;
    }

    //retrieve the current max capacity
    unsigned int getMaxCapacity() const {
        return capacity;
    }

    //retrieve the data array
    T* getData() const {
        return data;
    }
};