template <typename T, size_t N>
Array<T, N>::Array() 
{
    std::memset(m_data, 0, sizeof(T) * N);
}

template <typename T, size_t N>
Array<T, N>::~Array()
{
}

template <typename T, size_t N>
size_t Array<T, N>::size() const
{
    return N;
}

template <typename T, size_t N>
bool Array<T, N>::empty() const
{
    return N == 0;
}

template <typename T, size_t N>
T* Array<T, N>::data()
{
    return m_data;
}

template <typename T, size_t N>
const T* Array<T, N>::data() const
{
    return m_data;
}

template <typename T, size_t N>
void Array<T, N>::swap(Array<T, N> &other)
{
    if (this == &other)
        return;
    // other.T == T, other.N == N
    for (int i = 0; i < N; i ++)
    {
        auto temp = other.m_data[i];
        other.m_data[i] = m_data[i];
        m_data[i] = temp;
    }
}

template <typename T, size_t N>
void Array<T, N>::fill(const T &value)
{
    for (int i = 0; i < N; i ++)
        m_data[i] = value;
}

template <typename T, size_t N>
T& Array<T, N>::front()
{
    return m_data[0];
}

template <typename T, size_t N>
const T& Array<T, N>::front() const
{
    return m_data[0];
}

template <typename T, size_t N>
T& Array<T, N>::back() 
{
    return m_data[N - 1];
}

template <typename T, size_t N>
const T& Array<T, N>::back() const
{
    return m_data[N - 1];
}

template <typename T, size_t N>
T& Array<T, N>::at(size_t index)
{
    if (index >= N)
        throw std::out_of_range("out of range");
    return m_data[index];
}

template <typename T, size_t N>
const T& Array<T, N>::at(size_t index) const
{
    if (index >= N)
        throw std::out_of_range("out of range");
    return m_data[index];
}

template <typename T, size_t N>
T& Array<T, N>::operator[](size_t index)
{
    return m_data[index];
}

template <typename T, size_t N>
const T& Array<T, N>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin()
{
    return iterator(m_data); 
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end()
{
    return iterator(m_data + N);
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin() const
{
    return const_iterator(m_data);
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cend() const
{
    return const_iterator(m_data + N);
}

template <typename T, size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rbegin()
{
    return reverse_iterator(m_data + N - 1);
}

template <typename T, size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rend()
{
    return reverse_iterator(m_data - 1);
}

