/*******************************************************************************
Class:
Description:
Source files:
License:
    <LICENSE_DECRIPTION>
*******************************************************************************/


//******************************************************************************
// Includes
//******************************************************************************
#ifndef UTIL_TYPETRAITS_ISDENSE2D
#define UTIL_TYPETRAITS_ISDENSE2D

#include <type_traits>

#include "StorageOrder.hpp"
#include "../expressions/CD2DContainer.hpp"

using namespace ::FCFD::expression;

namespace FCFD
{
namespace type_traits
{

//******************************************************************************

// helper function
template< typename T, StorageOrder SO >
std::true_type IsCD2DContainer_aux( const volatile CD2DContainer<T,SO>* );

// everything else becomes a false type
std::false_type IsCD2DContainer_aux( ... );
//******************************************************************************


//******************************************************************************

template< typename T >
struct IsCD2DContainer
   : public decltype( IsCD2DContainer_aux( std::declval<T*>() ) )
{};

// Specialisation for references
template< typename T >
struct IsCD2DContainer<T&>
    : public std::false_type
{};


//******************************************************************************
// value type
template< typename T >
constexpr bool IsCD2DContainer_v = IsCD2DContainer<T>::value;

}
}

#endif