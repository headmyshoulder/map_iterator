# CMakeLists.txt
# Date: 2014-09-22
# Author: Karsten Ahnert (karsten.ahnert@gmx.de)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or
# copy at http://www.boost.org/LICENSE_1_0.txt)
#


project ( map_iterator )
cmake_minimum_required ( VERSION 2.6 )

# Add path for custom modules
set( CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
  )

set ( ODEINT_ROOT "/home/karsten/src/odeint-v2/include" )

find_package ( Boost REQUIRED )

if ( CMAKE_COMPILER_IS_GNUCXX )
    set ( CMAKE_CXX_FLAGS "-std=c++1y" )        ## Optimize
endif ()

include_directories ( ${ODEINT_ROOT} )
include_directories ( ${Boost_INCLUDE_DIRS} )

add_executable ( main main.cpp )
add_executable ( odeint_adaption odeint_adaption.cpp )