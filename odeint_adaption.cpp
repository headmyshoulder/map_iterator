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
auto make_ode_range( System system , Stepper stepper , State x , Time t_start , Time dt , Time t_end )
{
    auto updater = [system,stepper,dt]( auto x ) mutable { 
            stepper.do_step( system , x.first , x.second , dt );
            x.second += dt;
            return x; };
    auto condition = [t_end]( auto const& x ) { return x.second > t_end; };
    auto range = make_map_range( std::make_pair( x , t_start ) , updater , condition );
    return range;
}

template< typename System , typename Stepper , typename State , typename Time , typename Cond >
auto make_ode_range2( System system , Stepper stepper , State x , Time t_start , Time dt , Cond cond )
{
    State x2;
    stepper.do_step( system , x , t_start , x2 , dt );
    auto state = std::make_tuple( true , x2 , x , t_start );
    auto updater = [system,stepper,dt]( auto x ) mutable { 
        if( std::get< 0 >( x ) )
        {
            stepper.do_step( system , std::get< 1 >( x ) , std::get< 3 >( x ) , std::get< 2 >( x ) , dt );
            std::get< 0 >( x ) = false;
        }
        else
        {
            stepper.do_step( system , std::get< 2 >( x ) , std::get< 3 >( x ) , std::get< 1 >( x ) , dt );
            std::get< 0 >( x ) = true;
        }
        std::get< 3 >( x ) += dt;
        return x; };
    auto range = make_map_range( state , updater , cond );
    return range;
}



void odeint0( void )
{
    namespace odeint = boost::numeric::odeint;

    using state_type = std::array< double , 3 >;
    using stepper_type = odeint::runge_kutta4< state_type >;

    state_type x {{ 10.0 , 10.0 , 10.0 }};
    stepper_type stepper;
    double t = 0.0;
    double dt = 0.01;
    stepper.do_step( lorenz , x , t , dt );
    t += dt;

    auto obs = []( auto x , auto t ) { std::cout << t << " " << x[0] << "\n"; };
    odeint::integrate_const( stepper , lorenz , x , 0.0 , 10.0 , dt , obs );
}


void odeint1( void )
{
    using state_type = std::array< double , 3 >;
    using stepper_type = boost::numeric::odeint::runge_kutta4< state_type >;

    state_type x {{ 10.0 , 10.0 , 10.0 }};
    stepper_type stepper;
    auto range = make_ode_range( lorenz , stepper , x , 0.0 , 0.1 , 100.0 );

    for( auto r : range )
        std::cout << r.second << " " << r.first[0] << "\n";
}

void odeint2( void )
{
    using state_type = std::array< double , 1 >;
    using stepper_type = boost::numeric::odeint::runge_kutta4< state_type >;

    auto sys = []( auto const& x , auto& dxdt , auto t ) { dxdt[0] = -0.1 * x[0]; };
    state_type x {{ 10.0 }};
    stepper_type stepper;
    auto cond = []( auto x ) {
        double val2 = std::abs( std::get< 2 >( x )[0] - std::get< 1 >( x )[0] );
        return val2 < 1.0e-6;
    };

    auto range = make_ode_range2( sys , stepper , x , 0.0 , 0.1 , cond );

    for( auto r : range )
    {
        std::cout << std::get< 3 >( r ) << " " << std::get< 1 >( r )[0] << "\n";
    }
}


using namespace std;

int main( int argc , char *argv[] )
{
    // odeint0();
    // odeint1();
    odeint2();
    return 0;
}
