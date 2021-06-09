
#ifndef UTIL_TYPETRAITS_ADDTRAIT_HPP
#define UTIL_TYPETRAITS_ADDTRAIT_HPP


//******************************************************************************
// Includes
//******************************************************************************

#include <type_traits>


namespace FCFD {
namespace type_traits {

template< typename, typename, typename = void > struct AddTrait;
template< typename, typename, typename = void > struct AddTraitEval1;
template< typename, typename, typename = void > struct AddTraitEval2;
template< typename, typename, typename = void > struct AddTraitEval3;


//******************************************************************************
template< typename T1, typename T2 >
auto EvalAddTrait( const volatile T1&, const volatile T2& )
    -> AddTraitEval1<T1, T2>;
//******************************************************************************

template< typename T1  // left-hand side operand
        , typename T2  // right-hand side operand
        , typename >
struct AddTrait
   : public decltype( EvalAddTrait( std::declval<T1&>(), std::declval<T2&>() ) )
{
};
//******************************************************************************


//******************************************************************************
// Specialization for two data types.
template< typename T1, typename T2 >
struct AddTrait< T1, T2, std::enable_if_t< std::is_arithmetic_v<T1>
                                        && std::is_arithmetic_v<T2>
                                        && !std::is_same_v<T1,bool>
                                        && !std::is_same_v<T2,bool> > >
{
 public:
   using type = std::common_type_t<T1,T2>;
};
//******************************************************************************
template< typename T1, typename T2 >
using AddTrait_t = typename AddTrait<T1,T2>::type;
//******************************************************************************

template< typename T1  // Type of the left-hand side operand
        , typename T2  // Type of the right-hand side operand
        , typename >   // Restricting condition
struct AddTraitEval1
   : public AddTraitEval2<T1,T2>
{};

//******************************************************************************
// This can be specialized by a specific implementation.
// template< typename T1, typename T2, typename >
template< typename T1  // Type of the left-hand side operand
        , typename T2  // Type of the right-hand side operand
        , typename >   // Restricting condition
struct AddTraitEval2
   : public AddTraitEval3<T1,T2>
{};

template< typename T1  // Type of the left-hand side operand
        , typename T2  // Type of the right-hand side operand
        , typename >   // Restricting condition
struct AddTraitEval3
{};
//******************************************************************************
// Specialization of the AddTraitEval3 class template for two types supporting addition.
template< typename T1, typename T2 >
struct AddTraitEval3< T1, T2, std::void_t< decltype( std::declval<T1>()
                                                   + std::declval<T2>() ) > >
{
 public:
//******************************************************************************
    using type = std::remove_cv_t< std::remove_reference_t<
                    decltype( std::declval<T1>() + std::declval<T2>() ) > >;
//******************************************************************************
};
} //
}
#endif
