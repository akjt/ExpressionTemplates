
#ifndef UTIL_TYPETRAITS_ISEXPR
#define UTIL_TYPETRAITS_ISEXPR

#include <type_traits>
#include "../expressions/SExpression.hpp"

using namespace ::FCFD::expression;

namespace FCFD
{
namespace type_traits
{

//******************************************************************************

// helper function
template< typename T >
std::true_type IsExpression_aux( const volatile SExpression<T> * );

// everything else becomes a false type
std::false_type IsExpression_aux( ... );
//******************************************************************************


//******************************************************************************

template< typename T >
struct IsExpression
   : public decltype( IsExpression_aux( std::declval<T*>() ) )
{};

// Specialisation for references
template< typename T >
struct IsExpression<T&>
    : public std::false_type
{};


//******************************************************************************
// value type
template< typename T >
constexpr bool IsExpression_v = IsExpression<T>::value;

}
}

#endif