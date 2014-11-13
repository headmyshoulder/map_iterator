/*
 * map_range.hpp
 * Date: 2014-09-29
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 */

#ifndef MAP_RANGE_HPP_INCLUDED
#define MAP_RANGE_HPP_INCLUDED

#include <utility>
#include <iterator>


template< typename T , typename F , typename C >
class map_range
{
    using range = map_range< T , F , C >;
    
    struct map_iterator : public std::iterator< std::input_iterator_tag , T >
    {
        using reference = T&;
        
        map_iterator( range const* r )
        : m_range( r ) {}
        
        map_iterator& operator++( void )
        {
            m_range->m_value = m_range->m_func( m_range->m_value );
            if( m_range->m_condition( m_range->m_value ) )
            {
                    m_range = nullptr;
            }
            return *this;
        }
        
        map_iterator operator++( int )
        {
            map_iterator orig = *this;
            ++(*this);
            return orig;
        }
        
        reference operator*() const
        {
            return m_range->m_value;
        }
        
        bool operator==( map_iterator const& other ) const
        {
            return ( m_range == other.m_range );
        }
        
        bool operator!=( map_iterator const& other ) const
        {
            return ! ( *this == other );
        }
        
        range const* m_range;
    };
    
public:
    
    using iterator = map_iterator;
    using const_iterator = map_iterator;
        
    
    map_range( T value , F func , C condition )
    : m_value { std::move( value ) }
    , m_func { std::move( func ) }
    , m_condition( condition )
    {}
    
    iterator begin( void )
    {
        return iterator( this );
    }
    
    iterator end( void )
    {
        return iterator( nullptr );
    }
    
    
    const_iterator begin( void ) const
    {
        return const_iterator( this );
    }
    
    const_iterator end( void ) const
    {
        return const_iterator( nullptr );
    }
    
private:
    
    mutable T m_value;
    mutable F m_func;
    mutable C m_condition;
};


template< typename T , typename F , typename C >
auto make_map_range( T t , F f , C condition )
{
    return map_range< T , F , C >( std::move( t ) , std::move( f ) , std::move( condition ) );
}





#endif // MAP_RANGE_HPP_INCLUDED
