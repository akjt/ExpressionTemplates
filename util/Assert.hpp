
#ifndef UTIL_ASSERT_H
#define UTIL_ASSERT_H


//******************************************************************************
// Includes
//******************************************************************************
#include <cassert>
namespace FCFD {

//==============================================================================
//  RUN TIME ASSERTION
//==============================================================================
//******************************************************************************
// Helper function to avoid warnings by certain compilers
inline bool ASSERT_MESSAGE( const char* /*msg*/ )
{
   return false;
}
//******************************************************************************

//******************************************************************************
#define FCFD_ASSERT(expr,msg) assert( ( expr ) || FCFD::ASSERT_MESSAGE( msg ) )

//******************************************************************************


//******************************************************************************
// Compile time assertion macro.
// In case of an invalid compile time expression, a compilation error is created.
#define FCFD_STATIC_ASSERT(expr) \
    static_assert( expr, "Compile time condition violated" )
//******************************************************************************


//******************************************************************************
//  Compile time assertion macro with specific message
// In case of an invalid compile time expression, a compilation error is created.

#define FCFD_STATIC_ASSERT_MSG(expr,msg) \
    static_assert( expr, msg )
//******************************************************************************
} // namespace FCFD

#endif
