#pragma once

// https://stackoverflow.com/questions/8498300/allow-for-range-based-for-with-enum-classes

template< typename T, T First, T Last >
class EnumImpl
{
public:
    class Iterator
    {
    public:
        Iterator(std::underlying_type_t<T> value) :
            m_value(value)
        { }

        T operator*(void) const
        {
            // Тут должен быть reinterpret_cast
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
        std::underlying_type_t<T>  m_value;
    };

};

template< typename T, T First, T Last>
typename EnumImpl<T, First, Last>::Iterator begin(EnumImpl<T, First, Last>)
{
    return typename EnumImpl<T, First, Last>::Iterator(std::underlying_type_t<T>(First));
}

template< typename T, T First, T Last >
typename EnumImpl<T, First, Last>::Iterator end(EnumImpl<T, First, Last>)
{
    return typename EnumImpl<T, First, Last>::Iterator(std::underlying_type_t<T>(Last) + 1);
}