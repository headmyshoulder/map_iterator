/*
 * main.cpp
 * Date: 2014-09-22
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 */


#include "counted_map_range.hpp"
#include "map_range.hpp"

#include <boost/range/algorithm/copy.hpp>

#include <iostream>
#include <algorithm>

using namespace std;


int main( int argc , char *argv[] )
{
        
//     for( double r = 1.0 ; r<4.0 ; r+=0.01 )
//     {
//         auto range = make_counted_map_range( 0.5 , [r]( auto x ) { return r * x * ( 1.0 - x ); } , 1000 );
//         for( auto x : range )
//         {
//             cout << r << " " << x << endl;
//         }
//     }
    
    
//     for( double r = 1.0 ; r<4.0 ; r+=0.01 )
//     {
//         const auto range = make_map_range( 0.5 , [r]( auto x ) { return r * x * ( 1.0 - x ); } , []( auto x ) { return x < 0.4; } );
//         for( auto x : range )
//         {
//             cout << r << " " << x << endl;
//         }
//     }
    
    size_t n = 10;
    auto iota_range = make_counted_map_range( 2 , []( auto x ) { return x + 2 ; } , 10 );
    std::vector< int > values;
    boost::copy( iota_range , back_inserter( values ) );
    
    for( auto i : values ) { cout << i << endl; }
    
    return 0;
}
