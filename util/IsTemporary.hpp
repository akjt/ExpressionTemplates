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
#ifndef UTIL_TYPETRAITS_ISTEMPORARY
#define UTIL_TYPETRAITS_ISTEMPORARY

#include <type_traits>
#include "IsExpression.hpp"
#include "IsC2DContainer.hpp"

namespace FCFD
{
namespace type_traits
{


//******************************************************************************

template< typename T >
struct IsTemporary
//   : public std::bool_constant< ( Is2DContainer_v<T> || Is1DContainer_v<T> ) && !IsExpression_v<T> ) >
   : public std::bool_constant< ( IsC2DContainer_v<T> ) && !IsExpression_v<T>  >
{};

//******************************************************************************
// value type
template< typename T >
constexpr bool IsTemporary_v = IsTemporary<T>::value;

}
}

#endif
