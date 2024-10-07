#pragma once

#include <cstring>      // memset()
#include <stdexcept>    // out_of_range()
#include <stl/array_iterator.h>
#include <stl/array_const_iterator.h>
#include <stl/array_reverse_iterator.h>

namespace whao {
namespace stl {

template<typename T, size_t N>
class Array
{
public:
    typedef ArrayIterator<T> iterator;
    typedef ArrayConstIterator<T> const_iterator; 
    typedef ArrayReverseIterator<T> reverse_iterator;
public:
    Array();
    ~Array();

    size_t size() const;
    bool empty() const;
    T* data();
    const T* data() const;
    void swap(Array<T, N> &other);
    void fill(const T &value);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T& at(size_t index);
    const T& at(size_t index) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // iterator
    iterator begin();
    iterator end();
    
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    reverse_iterator rbegin();
    reverse_iterator rend();
private:
    T m_data[N];
};

#include <stl/array.inl>

}
}
