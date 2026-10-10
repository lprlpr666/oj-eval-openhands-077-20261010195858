#pragma once
#include <cstddef>
#include <algorithm>
#include <stdexcept>

namespace sjtu {
class CrossArray {
private:
    int maxLines;          // maximum number of lines (arrays)
    int **data;            // pointers to each int array
    int *len;              // length of each line (0 if nullptr)

    // helper to count total elements
    std::size_t totalElements() const {
        std::size_t total = 0;
        for (int i = 0; i < maxLines; ++i) {
            if (data[i]) total += static_cast<std::size_t>(len[i]);
        }
        return total;
    }
public:
    explicit CrossArray(int lines) : maxLines(lines) {
        if (lines < 0) throw std::invalid_argument("lines must be non‑negative");
        data = new int*[maxLines];
        len  = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            data[i] = nullptr;
            len[i] = 0;
        }
    }

    // copy constructor – deep copy
    CrossArray(const CrossArray &o) : maxLines(o.maxLines) {
        data = new int*[maxLines];
        len  = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            if (o.data[i]) {
                len[i] = o.len[i];
                data[i] = new int[len[i]];
                std::copy(o.data[i], o.data[i] + len[i], data[i]);
            } else {
                data[i] = nullptr;
                len[i] = 0;
            }
        }
    }

    // assignment operator (optional, but good practice)
    CrossArray& operator=(const CrossArray &o) {
        if (this == &o) return *this;
        // clean current
        for (int i = 0; i < maxLines; ++i) {
            delete[] data[i];
        }
        delete[] data;
        delete[] len;
        // copy
        maxLines = o.maxLines;
        data = new int*[maxLines];
        len  = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            if (o.data[i]) {
                len[i] = o.len[i];
                data[i] = new int[len[i]];
                std::copy(o.data[i], o.data[i] + len[i], data[i]);
            } else {
                data[i] = nullptr;
                len[i] = 0;
            }
        }
        return *this;
    }

    // WhichGreater – compare total element count
    CrossArray &WhichGreater(CrossArray &o) {
        if (totalElements() >= o.totalElements())
            return *this;
        else
            return o;
    }

    // IsSame – check whether two objects share the same underlying storage
    bool IsSame(const CrossArray &o) {
        return (data == o.data) && (len == o.len);
    }

    // InsertArrays – insert a new line at the first free slot
    bool InsertArrays(const int *Input, int size) {
        if (size < 0) return false;
        // find first nullptr slot
        int idx = -1;
        for (int i = 0; i < maxLines; ++i) {
            if (data[i] == nullptr) { idx = i; break; }
        }
        if (idx == -1) return false; // no space
        // allocate and copy
        data[idx] = new int[size];
        std::copy(Input, Input + size, data[idx]);
        len[idx] = size;
        return true;
    }

    // AppendArrays – append to an existing line
    void AppendArrays(const int *Input, int Line, int size) {
        if (Line < 0 || Line >= maxLines) throw std::out_of_range("Line index out of range");
        if (!data[Line]) throw std::runtime_error("Append to nullptr line");
        if (size < 0) return;
        int oldSize = len[Line];
        int newSize = oldSize + size;
        int *newArr = new int[newSize];
        // copy old elements
        std::copy(data[Line], data[Line] + oldSize, newArr);
        // copy new elements
        std::copy(Input, Input + size, newArr + oldSize);
        delete[] data[Line];
        data[Line] = newArr;
        len[Line] = newSize;
    }

    // DoubleCrossLength – double the capacity
    void DoubleCrossLength() {
        int newMax = maxLines * 2;
        int **newData = new int*[newMax];
        int *newLen = new int[newMax];
        // copy existing
        for (int i = 0; i < maxLines; ++i) {
            newData[i] = data[i];
            newLen[i] = len[i];
        }
        // initialise new slots
        for (int i = maxLines; i < newMax; ++i) {
            newData[i] = nullptr;
            newLen[i] = 0;
        }
        delete[] data;
        delete[] len;
        data = newData;
        len = newLen;
        maxLines = newMax;
    }

    // AtArray – return pointer to the beginning of a line
    const int *AtArray(int i) {
        if (i < 0 || i >= maxLines) throw std::out_of_range("Index out of range");
        return data[i];
    }

    // At – return reference to element (i, j)
    int &At(int i, int j) {
        if (i < 0 || i >= maxLines) throw std::out_of_range("Line index out of range");
        if (!data[i]) throw std::runtime_error("Accessing nullptr line");
        if (j < 0 || j >= len[i]) throw std::out_of_range("Column index out of range");
        return data[i][j];
    }

    // destructor
    ~CrossArray() {
        for (int i = 0; i < maxLines; ++i) {
            delete[] data[i];
        }
        delete[] data;
        delete[] len;
    }
};
} // namespace sjtu
