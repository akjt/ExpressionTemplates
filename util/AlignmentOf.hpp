#ifndef UTIL_TYPETRAITS_ALIGNMENTOF_HPP
#define UTIL_TYPETRAITS_ALIGNMENTOF_HPP


//******************************************************************************
// Includes
//******************************************************************************

#include <type_traits>

#include "Vectorization.hpp"
#include "IsVectorizable.hpp"


namespace FCFD
{
namespace type_traits
{

//******************************************************************************
//
// Auxiliary helper struct for the AlignmentOf type trait.
// type_traits
template< typename T >
struct AlignmentOfHelper
{
private:
//***************************************************************************
    static constexpr size_t defaultAlignment = std::alignment_of<T>::value;
//***************************************************************************

public:
//***************************************************************************
    static constexpr size_t value =
#if FCFD_AVX512F_MODE
    ( IsVectorizable_v<T> )?( sizeof(T) >= 4UL ? 64UL : 32UL )
    :( defaultAlignment );
#elif FCFD_AVX2_MODE
    ( IsVectorizable_v<T> )?( 32UL ):( defaultAlignment );
#else
    defaultAlignment;
#endif
//******************************************************************************
};
//******************************************************************************


//******************************************************************************
//  AlignmentOfHelper for 'float'.
//
template<>
struct AlignmentOfHelper<float>
{
public:
//******************************************************************************
    static constexpr size_t value =
#if FCFD_AVX512F_MODE
    64UL;
#elif FCFD_AVX_MODE
    32UL;
#elif FCFD_SSE_MODE
    16UL;
#else
    std::alignment_of<float>::value;
#endif
//******************************************************************************
};
//******************************************************************************


//******************************************************************************
//  Specialization of AlignmentOfHelper for 'double'.
template<>
struct AlignmentOfHelper<double>
{
public:
//***************************************************************************
    static constexpr size_t value =
#if FCFD_AVX512F_MODE
    64UL;
#elif FCFD_AVX_MODE
    32UL;
#elif FCFD_SSE_MODE
    16UL;
#else
    std::alignment_of<double>::value;
#endif
//***************************************************************************
};
//******************************************************************************

//******************************************************************************
// Evaluation of the required alignment of the given data type.
//
// The AlignmentOf type trait template evaluates the required alignment for the given data type.

//   AlignmentOf<double>::value        // Return 32 for AVX and to 16 for SSE

template< typename T >
struct AlignmentOf
   : public std::integral_constant<size_t,AlignmentOfHelper<T>::value>
{};
//******************************************************************************


//******************************************************************************
//
//  Partial specialization of AlignmentOf for 'const' data types.
template< typename T >
struct AlignmentOf< const T >
    : public std::integral_constant<size_t,AlignmentOfHelper<T>::value>
{};
//******************************************************************************


//******************************************************************************
//  Partial specialization of  AlignmentOf for 'volatile' data types.
template< typename T >
struct AlignmentOf< volatile T >
   : public std::integral_constant<size_t,AlignmentOfHelper<T>::value>
{};
//******************************************************************************


//******************************************************************************
//  Partial specialization of AlignmentOf for 'const volatile' data types.
template< typename T >
struct AlignmentOf< const volatile T >
    : public std::integral_constant<size_t,AlignmentOfHelper<T>::value>
{};
//******************************************************************************


//******************************************************************************
template< typename T >
constexpr size_t AlignmentOf_v = AlignmentOf<T>::value;
//******************************************************************************

} // namespace type_traits
} // namespace FCFD
#endif
