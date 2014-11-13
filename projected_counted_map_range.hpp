/*
 * projected_counted_map_range.hpp
 * Date: 2014-11-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#ifndef PROJECTED_COUNTED_MAP_RANGE_HPP_INCLUDED
#define PROJECTED_COUNTED_MAP_RANGE_HPP_INCLUDED




template< typename T , typename F , typename P >
class projected_counted_map_range
{
    using range = projected_counted_map_range< T , F , P >;


    struct map_iterator 
    {
        using iterator_category = std::input_iterator_tag;

        
        map_iterator( range const* r )
        : m_range { r } {}
        
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
        
        auto operator*() const
        {
            return m_range->m_projection( m_range->m_value );
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
        
    
    projected_counted_map_range( T value , F func , size_t max_iterations , P projection )
    : m_value { std::move( value ) }
    , m_func { std::move( func ) }
    , m_current_iteration { 0 }
    , m_max_iterations { max_iterations }
    , m_projection { std::move( projection ) }
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
    mutable size_t m_current_iteration;
    size_t m_max_iterations;
    P m_projection;
};


template< typename T , typename F , typename P >
auto make_projected_counted_map_range( T t , F f , size_t max_iterations , P projection )
{
    return projected_counted_map_range< T , F , P >(
        std::move( t ) ,
        std::move( f ) ,
        max_iterations ,
        std::move( projection ) );
}






#endif // PROJECTED_COUNTED_MAP_RANGE_HPP_INCLUDED
