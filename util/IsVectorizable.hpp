/*******************************************************************************
Namespace:
    FCFD::type_trait

Description:


Source files:


License:
    <LICENSE_DESCRIPTION>

*******************************************************************************/

#ifndef UTIL_TYPETRAITS_ISVECTORIZABLE_HPP
#define UTIL_TYPETRAITS_ISVECTORIZABLE_HPP

//******************************************************************************
// Includes
//******************************************************************************

#include "Vectorization.hpp"
#include "IsFloat.hpp"


namespace FCFD
{
namespace type_traits
{


//******************************************************************************
// TODO: add more vector machine types
template< typename T >
struct IsVectorizableHelper
{
public:
//******************************************************************************
    static constexpr bool value = ( sizeof(T) <= 8UL ) &&
                                ( ( bool( FCFD_SSE_MODE ) && IsFloat_v<T>   ) ||
                                  ( bool( FCFD_AVX2_MODE ) && IsFloat_v<T>  ) ||
                                  ( bool( FCFD_AVX_MODE ) && IsFloat_v<T>  )  ||
                                  ( bool( FCFD_AVX512F_MODE )
                                    &&
                                    std::is_arithmetic_v<T>
                                    && sizeof(T) >= 4UL
                                  )
                                );
//******************************************************************************
};
//******************************************************************************


//******************************************************************************
template<>
struct IsVectorizableHelper<void>
{
public:
//******************************************************************************
    static constexpr bool value = false;
//******************************************************************************
};
//******************************************************************************


//******************************************************************************
template< typename T >
struct IsVectorizable
   : public std::bool_constant<IsVectorizableHelper< std::remove_cv<T> >::value>
{};
//******************************************************************************


//******************************************************************************
// shortcut variable template for the IsVectorizable type trait.
template< typename T >
constexpr bool IsVectorizable_v = IsVectorizable<T>::value;
//******************************************************************************

} // namespace type_trait
} // FCFD

#endif
