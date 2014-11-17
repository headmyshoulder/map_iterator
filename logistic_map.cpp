/*
 * logistic_map.cpp
 * Date: 2014-11-17
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#include "map_range.hpp"
#include "counted_map_range.hpp"
#include "projected_map_range.hpp"
#include "projected_counted_map_range.hpp"

#include <boost/range/algorithm/copy.hpp>

#include <iostream>
#include <algorithm>


void logistic_map1( void )
{
    for( double r = 1.0 ; r<4.0 ; r+=0.01 )
    {
        auto range = make_counted_map_range(
            0.5 ,
            [r]( auto x ) { return r * x * ( 1.0 - x ); } ,
            1000 );
        for( auto x : range )
        {
            std::cout << r << " " << x << std::endl;
        }
    }
}

void logistic_map2( void )
{
    for( double r = 1.0 ; r<4.0 ; r+=0.01 )
    {
        const auto range = make_map_range(
            0.5 ,
            [r]( auto x ) { return r * x * ( 1.0 - x ); } ,
            []( auto x ) { return x < 0.4; } );
        for( auto x : range )
        {
            std::cout << r << " " << x << std::endl;
        }
    }
}


int main( int argc , char *argv[] )
{
    using namespace std;

    logistic_map1();
    logistic_map2();


    return 0;
}
