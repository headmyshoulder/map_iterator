/*
 * main.cpp
 * Date: 2014-09-22
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 */


#include "map_range.hpp"

#include <iostream>

using namespace std;


int main( int argc , char *argv[] )
{
    for( double r = 1.0 ; r<4.0 ; r+=0.01 )
    {
        auto logistic_map = [r]( auto x ) {
            return r * x * ( 1.0 - x ); };
        auto range = make_map_range( 0.5 , logistic_map , 1000 );
        for( auto x : range )
        {
            cout << r << " " << x << endl;
        }
    }
    
    return 0;
}
