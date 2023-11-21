#pragma once
#include "iostream"
using namespace std;

template <typename type> class Vector {
    type* data;
    int maxSize, curSize;

public:
    Vector() {
        data = new type[3];
        maxSize = 3;
        curSize = 0;
    }

    void push_back(const type& value) {
        if (curSize == maxSize) {
            type* temp = new type[maxSize];
            for (int i = 0; i < maxSize; ++i)
                temp[i] = data[i];
            delete[] data;
            data = new type[maxSize + 10];
            for (int i = 0; i < maxSize; ++i)
                data[i] = temp[i];
            delete[] temp;
            maxSize += 10;
        }
        data[curSize] = value;
        ++curSize;
    }

    void erase(int index) {
        if (index < 0 || index > curSize) {
            cout << "Invalid index.";
            exit(0);
        }
        if (index == curSize - 1)
            --curSize;
        else {
            for (int i = index; i < curSize - 1; ++i)
                data[i] = data[i + 1];
            --curSize;
        }
    }

    int size() {
        return curSize;
    }

    type& operator[](int index) {
        if (index < 0 || index > curSize) {
            cout << "Invalid index.";
            exit(0);
        }
        return data[index];
    }

    ~Vector() {
        delete[] data;
    }
};

template <typename type>
class Vector<type*> {
    public:
    type** data;
    int maxSize, curSize;

public:
    Vector() {
        data = new type * [1];
        maxSize = 1;
        curSize = 0;
    }

    void push_back(type* value) {
        if (data == nullptr) {
            data = new type * [1];
            maxSize = 1;
            curSize = 0;
        }
        if (curSize == maxSize) {
            type** temp = new type * [maxSize];

            for (int i = 0; i < maxSize; ++i)
                temp[i] = data[i];

            delete[] data;
            data = new type * [maxSize + 3];
            for (int i = 0; i < maxSize; ++i)
                data[i] = temp[i];
            delete[] temp;
            maxSize += 3;
        }
        data[curSize] = value;
        ++curSize;
    }

    void erase(int index) {
        if (index < 0 || index > curSize) {
            cout << "Invalid index.";
            exit(0);
        }
        if (index == curSize - 1) {
            --curSize;
        }
        else {
            for (int i = index; i < curSize - 1; ++i)
                data[i] = data[i + 1];
            --curSize;
        }
    }

    int size() {
        return curSize;
    }

    type*& operator[](int index) {
        if (index < 0 || index > curSize) {
            cout << "Invalid index.";
            exit(0);
        }
        return data[index];
    }

    ~Vector() {
        for (int i = 0; i < curSize; ++i) {
            if (data[i] != nullptr)
                delete[] data[i];
        }
        delete[] data;
    }
};