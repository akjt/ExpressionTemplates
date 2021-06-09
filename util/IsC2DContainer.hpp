#ifndef UTIL_TYPETRAITS_IS2DCONTAINER
#define UTIL_TYPETRAITS_IS2DCONTAINER

//******************************************************************************
// Includes
//******************************************************************************
#include <type_traits>
#include "../expressions/C2DContainer.hpp"
#include "StorageOrder.hpp"

using namespace ::FCFD::expression;

namespace FCFD
{
namespace type_traits
{

//******************************************************************************

// helper function
template< typename T, StorageOrder SO >
std::true_type IsC2DContainer_aux( const volatile C2DContainer<T,SO> * );

// everything else becomes a false type
std::false_type IsC2DContainer_aux( ... );
//******************************************************************************


//******************************************************************************

template< typename T >
struct IsC2DContainer
   : public decltype( IsC2DContainer_aux( std::declval<T*>() ) )
{};

// Specialisation for references
template< typename T >
struct IsC2DContainer<T&>
    : public std::false_type
{};


//******************************************************************************
// value type
template< typename T >
constexpr bool IsC2DContainer_v = IsC2DContainer<T>::value;

}
}

#endif
