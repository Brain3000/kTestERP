#pragma once

// https://stackoverflow.com/questions/8498300/allow-for-range-based-for-with-enum-classes

template< typename T>
class EnumImpl
{
public:
    using InternalType = std::underlying_type_t<T>;
    class Iterator
    {
    public:
        Iterator(InternalType value) :
            m_value(value)
        { }

        T operator*(void) const
        {
            // ��� ������ ���� reinterpret_cast
            return (T)(m_value);
        }

        void operator++(void)
        {
            ++m_value;
        }

        bool operator!=(const Iterator rhs) const
        {
            return m_value != rhs.m_value;
        }

    private:
        InternalType  m_value;
    };

};

template<typename T>
typename EnumImpl<T>::Iterator begin(EnumImpl<T>)
{
    return typename EnumImpl<T>::Iterator(EnumImpl<T>::InternalType(T::eFirst));
}

template<typename T>
typename EnumImpl<T>::Iterator end(EnumImpl<T>)
{
    return typename EnumImpl<T>::Iterator(EnumImpl<T>::InternalType(T::eLast) + 1);
}