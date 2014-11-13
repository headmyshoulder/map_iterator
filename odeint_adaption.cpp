/*
 * odeint_adaption.cpp
 * Date: 2014-11-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#include "map_range.hpp"

#include <boost/numeric/odeint.hpp>

#include <iostream>
#include <array>
#include <typeindex>

auto lorenz = []( auto const& x , auto& dxdt , auto t )
{
    const double sigma = 10.0;
    const double R = 28.0;
    const double b = 8.0 / 3.0;
    dxdt[0] = sigma * ( x[1] - x[0] );
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];
};

template< typename System , typename Stepper , typename State , typename Time >
auto make_odeint_range( System system , Stepper stepper , State x , Time t_start , Time dt , Time t_end )
{
    auto updater = [system,stepper,dt]( auto x ) mutable { 
            stepper.do_step( system , x.first , x.second , dt );
            x.second += dt;
            return x; };
    auto condition = [t_end]( auto const& x ) { return x.second > t_end; };
    auto range = make_map_range( std::make_pair( x , t_start ) , updater , condition );
    return range;
}


void odeint1( void )
{
    using state_type = std::array< double , 3 >;
    using stepper_type = boost::numeric::odeint::runge_kutta4< state_type >;

    state_type x {{ 10.0 , 10.0 , 10.0 }};
    stepper_type stepper;
    auto r = make_odeint_range( lorenz , stepper , x , 0.0 , 0.1 , 100.0 );

    for( auto iter = r.begin() ; iter != r.end() ; ++iter )
    {
        auto x = *iter;
        std::cout << x.second << " " << x.first[0] << " " << x.first[1] << " " << x.first[2] << std::endl;
    }
}

using namespace std;

int main( int argc , char *argv[] )
{
    odeint1();
    return 0;
}
