
#ifndef COMMON_EXPR_HPP
#define COMMON_EXPR_HPP
// Base type for all expression templates. All expression templates must inherit from this.
// This is important to be able to type trait whether a given type is of an expression
namespace FCFD
{
namespace expression
{
template< typename T>
struct SExpression
    : public T
{};
}
}
#endif