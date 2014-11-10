/*
 * counted_map_range.hpp
 * Date: 2014-11-10
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#ifndef COUNTED_MAP_RANGE_HPP_INCLUDED
#define COUNTED_MAP_RANGE_HPP_INCLUDED


#include <utility>
#include <iterator>

template< typename T , typename F >
class counted_map_range
{
    using range = counted_map_range< T , F >;
    
    struct map_iterator : public std::iterator< std::input_iterator_tag , T >
    {
        using reference = T&;
        
        map_iterator( range const* r )
        : m_range( r ) {}
        
        map_iterator& operator++( void )
        {
            m_range->m_value = m_range->m_func( m_range->m_value );
            ++( m_range->m_current_iteration );
            if( m_range->m_current_iteration >= m_range->m_max_iterations )
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
    
    
    counted_map_range( T value , F func , size_t max_iterations )
    : m_current_iteration { 0 }
    , m_max_iterations { max_iterations }
    , m_value { std::move( value ) }
    , m_func { std::move( func ) }
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
    
    mutable size_t m_current_iteration = 0;
    const size_t m_max_iterations;
    mutable T m_value;
    mutable F m_func;
};


template< typename T , typename F >
auto make_counted_map_range( T t , F f , size_t max_iterations )
{
    return counted_map_range< T , F >( std::move( t ) , std::move( f ) , max_iterations );
}






#endif // COUNTED_MAP_RANGE_HPP_INCLUDED
