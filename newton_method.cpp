/*
 * newton_method.cpp
 * Date: 2014-11-17
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */


#include "map_range.hpp"
#include "advance.hpp"

#include <iostream>
#include <cmath>

using namespace std;


template< typename X , typename F , typename DF , typename B >
auto newton_range( X x , F f , DF df , B break_condition )
{
    return make_map_range(
        x ,
        [f,df]( auto x ) { return x - f( x ) / df( x ); } ,
        break_condition );
}

void newton1( void )
{
    auto f = []( auto x ) { return exp(-x*x) - 0.5; };
    auto df = []( auto x ) { return -2.0*x * exp(-x*x); };
    auto cond  = [f]( auto x ) { return std::abs( f( x ) ) < 1.0e-12; };
    auto range = newton_range( 1.5 , f , df , cond );

    for( auto r : range )
        std::cout << r << " : " << f( r ) << std::endl;
}


int main( int argc , char *argv[] )
{
    newton1();
    return 0;
}
