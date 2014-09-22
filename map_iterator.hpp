/*
 * map_iterator.hpp
 * Date: 2014-09-22
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#ifndef MAP_ITERATOR_HPP_INCLUDED
#define MAP_ITERATOR_HPP_INCLUDED

#include <iterator>


template< typename T , typename F >
class map_iterator : public std::iterator< std::input_iterator_tag , T >
{
public:
    
    map_iterator( T initial_value , F func )
    : m_value( std::move( initial_value ) ) , m_func( std::move( func ) )
    {}
    
    map_iterator& operator++( void )
    {
        m_value = m_func( m_value );
        return *this;
    }
    
    reference operator*() const
    {
        return m_value;
    }
    
    
private:
    
    T m_value;
    F m_func;
};

template< typename T , typename F >
map_iterator< T , F > make_map_iterator( T t , F f )
{
    return map_iterator< T , F >( t , f );
}





#endif // MAP_ITERATOR_HPP_INCLUDED
