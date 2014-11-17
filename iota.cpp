/*
 * main.cpp
 * Date: 2014-09-22
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 */


#include "counted_map_range.hpp"
#include "map_range.hpp"
#include "projected_map_range.hpp"
#include "projected_counted_map_range.hpp"

#include <boost/range/algorithm/copy.hpp>

#include <iostream>
#include <algorithm>

void iota1( void )
{
    auto iota_range = make_counted_map_range( 2 , []( auto x ) { return x + 2 ; } , 10 );
    std::vector< int > values;
    boost::copy( iota_range , back_inserter( values ) );
    
    for( auto i : values ) { std::cout << i << std::endl; }
}

void iota2( void )
{
    auto iota_range = make_projected_map_range(
        2
        , []( auto x ) { return x + 1 ; }
        , []( auto x ) { return x > 10; } 
        , []( auto x ) { return x*x; }
        );
    std::vector< int > values;
    for( auto x : iota_range )
        values.push_back( x );
    
    for( auto i : values ) { std::cout << i << std::endl; }
}

void iota3( void )
{
    auto iota_range = make_projected_counted_map_range(
        1
        , []( auto x ) { return x + 1 ; }
        , 11
        , []( auto x ) { return x*x; }
        );
    for( auto i : iota_range ) { std::cout << i << std::endl; }
}

void iota4( void )
{
    auto iota_range = make_projected_counted_map_range(
        1
        , []( auto x ) { return x + 1 ; }
        , 11
        , []( auto x ) { return x*x; }
        );
    std::vector< int > values;
    for( auto x : iota_range )
        values.push_back( x );
    
    for( auto i : values ) { std::cout << i << std::endl; }
}


int main( int argc , char *argv[] )
{
    // iota1();
    // iota2();
    iota3();

    return 0;
}
