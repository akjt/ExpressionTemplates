/*******************************************************************************
Namespace:
    FCFD::error

Description:
    Run time errors with information about location, file.
    These type of errors cannot be recovered, and program should terminate
Source files:
    Error_impl.hpp

License:
    <LICENSE_DESCRIPTION>

*******************************************************************************/
#ifndef UTIL_ERROR_HPP
#define UTIL_ERROR_HPP
#include <iostream>

// Macro definitions
#define FCFDError( msg )FCFD::error::ErrorMsg(__FILE__,__LINE__,msg);
#define FCFDAllocFail FCFD::error::ErrorMsg(__FILE__,__LINE__);

namespace FCFD {
namespace error{


    void ErrorMsg( const std::string &file, int line, const std::string &report);
    void ErrorMsg( const std::string &file, int line );

/* C++ 20 this avoid having to put __FILE__ all the time
   void ErrorMsg( const std::string &report
                     , const std::source_location& location
                      = std::source_location::current()       )

*/

#include "Error_impl.hpp"

}
}

#endif
