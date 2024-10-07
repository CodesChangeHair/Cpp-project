#pragma once

namespace whao {
namespace stl {

template <typename T>
class ArrayReverseIterator
{
    typedef ArrayReverseIterator<T> iterator;
public:
    ArrayReverseIterator() : m_pointer(nullptr) {}
    ArrayReverseIterator(T *pointer) : m_pointer(pointer) {}
    ~ArrayReverseIterator() {}

    bool operator==(const iterator &other) const
    {
        return m_pointer == other.m_pointer;
    }
    
    bool operator!=(const iterator &other) const
    {
        return m_pointer != other.m_pointer;
    }

    iterator& operator=(const iterator &other)
    {
        if (this != &other)
            m_pointer = other.m_pointer;
        return *this;
    }
    
    // prefix ++, ++ it 
    iterator& operator++() 
    {
        m_pointer -= 1;
        return *this;
    }

    // sufix ++, it ++
    iterator operator++(int) 
    {
        iterator it = *this;
        ++(*this);
        return it;
    }

    // prefix --, -- it
    iterator& operator--()
    {
        m_pointer += 1;
        return *this;
    }

    // sufix --, it --
    iterator operator--(int)
    {
        iterator it = *this;
        --(*this);
        return it;
    }

    iterator operator-(int n)
    {
        iterator it = *this;
        it.m_pointer += n;
        return it;
    }

    iterator& operator-=(int n)
    {
        m_pointer += n;
        return *this;
    }

    iterator operator+(int n)
    {
        iterator it = *this;
        it.m_pointer -= n;
        return it;
    }

    iterator& operator+=(int n)
    {
        m_pointer -= n;
        return *this;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    T* operator->()
    {
        return m_pointer;
        // or return &(operator*());
    }

    int operator-(const iterator &other) const
    {
        return m_pointer - other.m_pointer;
    }

private:
    T *m_pointer;
};

}
}
