#ifndef COMMON_EXPR_ADDEXPRCD2DCD2D
#define COMMON_EXPR_ADDEXPRCD2DCD2D

#include "../util/StorageOrder.hpp"
#include "../util/AddTrait.hpp"
#include "../util/Error.hpp"
#include "../util/IsTemporary.hpp"
#include "../util/IsCD2DContainer.hpp"

#include "CD2DContainer.hpp"
#include "SExpression.hpp"

using namespace ::FCFD::type_traits;

namespace FCFD
{
namespace expression
{

// TODO: Apply concept/requirement for the template argument for better understanding
// of compiler errors.

template< typename CDT1     // Dense container type 2D lhs
        , typename CDT2     // Dense container type 2D rhs
        , StorageOrder SO > // Storage order AoS or SoA
class CAddExprCD2DContainerCD2DContainer
    :   public SExpression< CD2DContainer <
              CAddExprCD2DContainerCD2DContainer< CDT1, CDT2, SO >, SO > >
{
private:
//**Type definitions************************************************************
    using return_type_1   = typename CDT1::return_type;
    using return_type_2   = typename CDT2::return_type;
    using result_type_1   = typename CDT1::result_type;
    using result_type_2   = typename CDT2::result_type;


//** Return type evaluation*****************************************************
// If both types are not temporary , this means we are returning an expression.
    static constexpr bool returnExpr =  ( !IsTemporary_v<return_type_1>
                                     &&   !IsTemporary_v<return_type_2> );

   using returnExprType = decltype( std::declval<return_type_1>()
                                  + std::declval<return_type_2>() );



public:
//**Type definitions************************************************************
    using This =  CAddExprCD2DContainerCD2DContainer<CDT1, CDT2, SO >;
    // remove evaluation to a different place?
    using result_type     = AddTrait_t< result_type_1, result_type_2 >;
    using value_type      = typename result_type::value_type;
    using left_hand_expr  = std::conditional_t< IsExpression_v<CDT1>
                                              , const CDT1
                                              , const CDT1& >;

    using right_hand_expr = std::conditional_t< IsExpression_v<CDT2>
                                              , const CDT2
                                              , const CDT2& >;

    using return_type     = const std::conditional_t< returnExpr
                                                    , returnExprType
                                                    , value_type >;
//**Constructors****************************************************************

    inline CAddExprCD2DContainerCD2DContainer( const CDT1& lhs
                                             , const CDT2& rhs )noexcept;

//**Access functions************************************************************
    inline return_type operator()( const size_t i, const size_t j )const noexcept;


//**Utility functions***********************************************************
    inline size_t rows() const noexcept { return lhs_.rows(); };
    inline size_t columns() const noexcept { return lhs_.columns(); };;

private:
//**Member variables************************************************************
   left_hand_expr  lhs_;  // Left-hand side dense matrix of the addition expression.
   right_hand_expr rhs_;  // Right-hand side dense matrix of the addition expression.
};

#include "CAddExprCD2DContainerCD2DContainer_impl.hpp"
} // expression
} // FCFD
#endif