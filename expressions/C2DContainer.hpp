/*******************************************************************************
Class:
    C2DContainer
Description:
    The very basic class to all types of 2D containers.
    We employ the CRTP design pattern for static inheritance between.
    We forward the 2D container type and the storage order. The latter
    could have been omitted, however, it might be usefull for future
    applications that we would like to convert between SoA and AoS.
Source files:
License:
    <LICENSE_DECRIPTION>
*******************************************************************************/
#ifndef COMMON_EXPR_C2DCONTAINER_HPP
#define COMMON_EXPR_C2DCONTAINER_HPP

#include "../util/StorageOrder.hpp"
#include "../util/Assert.hpp"


namespace FCFD
{
namespace expression
{

template< typename CT, StorageOrder SO >
class C2DContainer
{
protected:
//**CONSTRUCTORS*************************************************************
    C2DContainer() = default;
//**COPY CONSTRUCTORS********************************************************
    C2DContainer( const C2DContainer& ) = default;
    C2DContainer( C2DContainer&& ) = default;
//**DESTRUCTOR CONSTRUCTORS**************************************************
    ~C2DContainer() = default;
    C2DContainer& operator=( const C2DContainer& ) = default;
    C2DContainer& operator=( C2DContainer&& ) = default;
//***************************************************************************

public:
//**STATIC BINDING FUNCTIONS*************************************************
    constexpr CT& operator*() noexcept;
    constexpr const CT& operator*() const noexcept;
};
//***************************************************************************

//===========================================================================
//  STATIC BINDING FUNCTIONS
//===========================================================================

//***************************************************************************
// non const version
template< typename CT, StorageOrder SO >
inline constexpr CT& C2DContainer<CT,SO>::operator*() noexcept
{
    return static_cast<CT&>( *this );
}
//***************************************************************************

//***************************************************************************
// const version
template< typename CT, StorageOrder SO >
inline constexpr const CT& C2DContainer<CT,SO>::operator*() const noexcept
{
    return static_cast<const CT&>( *this );
}
//***************************************************************************


//===========================================================================
//  GENERIC OPERATORS
//===========================================================================
template< typename CT1, StorageOrder SO1   // lhs container
        , typename CT2, StorageOrder SO2 > // rhs container
inline void Assign(       C2DContainer<CT1,SO1>& lhs
                        , const C2DContainer<CT2,SO2>& rhs )
{
   FCFD_ASSERT( (*lhs).rows()    == (*rhs).rows()
              , "Number of rows not consistent" );
   FCFD_ASSERT( (*lhs).columns() == (*rhs).columns()
              , "Number of columns not consistent");

   Assign_( *lhs, *rhs );
}


template< typename CT1, StorageOrder SO1   // lhs container
        , typename CT2, StorageOrder SO2 > // rhs container
inline void AddAssign(       C2DContainer<CT1,SO1>& lhs
                           , const C2DContainer<CT2,SO2>& rhs )
{
   FCFD_ASSERT( (*lhs).rows()    == (*rhs).rows()
              , "Number of rows not consistent" );
   FCFD_ASSERT( (*lhs).columns() == (*rhs).columns()
              , "Number of columns not consistent");

   AddAssign_( *lhs, *rhs );
}



template< typename CT1, StorageOrder SO1   // lhs container
        , typename CT2, StorageOrder SO2 > // rhs container
inline void SubtractAssign(       C2DContainer<CT1,SO1>& lhs
                                , const C2DContainer<CT2,SO2>& rhs )
{
   FCFD_ASSERT( (*lhs).rows()    == (*rhs).rows()
                , "Number of rows not consistent" );
   FCFD_ASSERT( (*lhs).columns() == (*rhs).columns()
                , "Number of columns not consistent");
   SubtractAssign_( *lhs, *rhs );
}

template< typename CT1, StorageOrder SO1   // lhs container
        , typename CT2, StorageOrder SO2 > // rhs container
inline void HadamardAssign(       C2DContainer<CT1,SO1>& lhs
                                , const C2DContainer<CT2,SO2>& rhs )
{
   FCFD_ASSERT( (*lhs).rows()    == (*rhs).rows()
              , "Number of rows not consistent" );
   FCFD_ASSERT( (*lhs).columns() == (*rhs).columns()
              , "Number of columns not consistent");

   HadamardAssign_( *lhs, *rhs );
}

//==============================================================================
//  SPECILIASTION OPERATORS
//==============================================================================
// The idea here is to use SFINAE to choose the right function at compilation time.
// The examples here are only shown for the case with same storage order.

//***With same storage type*****************************************************
template< typename CT1, typename CT2, StorageOrder SO >
inline void Assign_(       C2DContainer<CT1,SO>& lhs
                         , const C2DContainer<CT2,SO>& rhs )
{
    (*lhs).Assign( *rhs );
}
//******************************************************************************

//******************************************************************************
template< typename CT1, typename CT2, StorageOrder SO >
inline void AddAssign_(       C2DContainer<CT1,SO>& lhs
                            , const C2DContainer<CT2,SO>& rhs )
{
    (*lhs).AddAssign( *rhs );
}
//******************************************************************************

//******************************************************************************
template< typename CT1, typename CT2, StorageOrder SO >
inline void SubtractAssign_(       C2DContainer<CT1,SO>& lhs
                                 , const C2DContainer<CT2,SO>& rhs )
{
    (*lhs).SubtractAssign( *rhs );
}

//******************************************************************************
template< typename CT1, typename CT2, StorageOrder SO >
inline void HadamardAssign_(       C2DContainer<CT1,SO>& lhs
                                 , const C2DContainer<CT2,SO>& rhs )
{
    (*lhs).HadamardAssign( *rhs );
}
//******************************************************************************

}
}

#endif
