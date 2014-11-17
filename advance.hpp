/*
 * advance.hpp
 * Date: 2014-11-17
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#ifndef ADVANCE_HPP_INCLUDED
#define ADVANCE_HPP_INCLUDED


template< typename Iter >
void advance( Iter first , Iter last )
{
    if( first == last ) return;
    for( ; ++first != last ; ) ;
}

template< typename Range >
void advance( Range const& range )
{
    advance( range.begin() , range.end() );
}




#endif // ADVANCE_HPP_INCLUDED
