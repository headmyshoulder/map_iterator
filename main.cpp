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

using namespace std;

void logistic_map1( void )
{
    for( double r = 1.0 ; r<4.0 ; r+=0.01 )
    {
        auto range = make_counted_map_range( 0.5 , [r]( auto x ) { return r * x * ( 1.0 - x ); } , 1000 );
        for( auto x : range )
        {
            cout << r << " " << x << endl;
        }
    }
}

void logistic_map2( void )
{
    for( double r = 1.0 ; r<4.0 ; r+=0.01 )
    {
        const auto range = make_map_range( 0.5 , [r]( auto x ) { return r * x * ( 1.0 - x ); } , []( auto x ) { return x < 0.4; } );
        for( auto x : range )
        {
            cout << r << " " << x << endl;
        }
    }
}

void iota1( void )
{
    size_t n = 10;
    auto iota_range = make_counted_map_range( 2 , []( auto x ) { return x + 2 ; } , 10 );
    std::vector< int > values;
    boost::copy( iota_range , back_inserter( values ) );
    
    for( auto i : values ) { cout << i << endl; }
}

void iota2( void )
{
    size_t n = 10;
    auto iota_range = make_projected_map_range(
        2
        , []( auto x ) { return x + 1 ; }
        , []( auto x ) { return x > 10; } 
        , []( auto x ) { return x*x; }
        );
    std::vector< int > values;
    for( auto x : iota_range )
        values.push_back( x );
    
    for( auto i : values ) { cout << i << endl; }
}

void iota3( void )
{
    size_t n = 10;
    auto iota_range = make_projected_counted_map_range(
        1
        , []( auto x ) { return x + 1 ; }
        , 11
        , []( auto x ) { return x*x; }
        );
    std::vector< int > values;
    for( auto x : iota_range )
        values.push_back( x );
    
    for( auto i : values ) { cout << i << endl; }
}


int main( int argc , char *argv[] )
{
    // logistic_map1();
    // logistic_map2();
    // iota1();
    // iota2();
    iota3();

    return 0;
}
