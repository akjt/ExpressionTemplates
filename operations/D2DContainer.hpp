/*******************************************************************************
Class:

Description:
These Global operations are enabled through the SFINAE principle when the target
(lhs) is a Dense2Dcontainer. The rhs can be of any type Container type.
This is Global execution with respect to a running process. IOW, a parallel
MPI application can still call these functions since each MPI rank would be
considered as a Global entity.
SIMD Vectorisation might also happen (when enabled) using these API.
OpenMP threads or other multithreads applications where the running process
consists of multiple threads shoudl never be calling these APIs.

Source files:
License:
    <LICENSE_DECRIPTION>
*******************************************************************************/
#ifndef COMMON_OP_D2DCONTAINER_HPP
#define COMMON_OP_D2DCONTAINER_HPP

#include "../expressions/C2DContainer.hpp"
#include "../util/IsCD2DContainer.hpp"
#include "../util/StorageOrder.hpp"
#include "../util/Error.hpp"

using namespace ::FCFD::type_traits;

namespace FCFD
{
namespace operation
{

//==============================================================================
//  FUNCTION INTERFACES
//==============================================================================

// Assign to the target lhs which is a dense container.
// We use the SFINAE to disregard this function in case we assign to a different type
// We SFINAE away these functions in case we are not applying the following functions
// for CDense2DContainer. Note it would work whether it is a static or dynamic container.
// For sparse 2D or vectors the functions in the
// respective files in the same folder as this file would be enabled.


template< typename CT1, StorageOrder SO1, typename CT2, StorageOrder SO2>
auto GlobalAssign( C2DContainer<CT1,SO1>& lhs, const C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >;

template< typename CT1, StorageOrder SO1, typename CT2, StorageOrder SO2>
auto GlobalAddAssign( C2DContainer<CT1,SO1>& lhs, const C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >;

template< typename CT1, StorageOrder SO1, typename CT2, StorageOrder SO2 >
auto GlobalSubtractAssign( C2DContainer<CT1,SO1>& lhs, const C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >;

template< typename CT1, StorageOrder SO1, typename CT2, StorageOrder SO2 >
auto GlobalHadamardAssign( C2DContainer<CT1,SO1>& lhs, const C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >;

//******************************************************************************

//******************************************************************************
// Assign rhs to lhs =>  lhs = rhs;
template< typename CT1, StorageOrder SO1
        , typename CT2, StorageOrder SO2>
inline auto GlobalAssign( C2DContainer<CT1,SO1>& lhs, const C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >
{
    FCFD_ASSERT( (*lhs).rows() == (*rhs).rows(),"Number of rows inconsistent");
    FCFD_ASSERT( (*lhs).columns() == (*rhs).columns(),"Number of columns inconsistent");

    Assign(*lhs, *rhs);
    return;
}
//******************************************************************************

//******************************************************************************
// Add Assign rhs to lhs =>  lhs = rhs + lhs or lhs += rhs;
template< typename CT1, StorageOrder SO1
        , typename CT2, StorageOrder SO2>
inline auto GlobalAddAssign( C2DContainer<CT1,SO1>& lhs, C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >
{
    FCFD_ASSERT( (*lhs).rows() == (*rhs).rows(),"Number of rows inconsistent");
    FCFD_ASSERT( (*lhs).columns() == (*rhs).columns(),"Number of columns inconsistent");
    AddAssign(*lhs, *rhs);
    return;
}

//******************************************************************************
// Subtract Assign rhs to lhs =>  lhs = rhs- lhs or lhs -= rhs ;
template< typename CT1, StorageOrder SO1
        , typename CT2, StorageOrder SO2>
inline auto GlobalSubtractAssign( C2DContainer<CT1,SO1>& lhs, C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >
{
    FCFD_ASSERT( (*lhs).rows() == (*rhs).rows(),"Number of rows inconsistent");
    FCFD_ASSERT( (*lhs).columns() == (*rhs).columns(),"Number of columns inconsistent");
    SubtractAssign(*lhs, *rhs);
    return;
}
//******************************************************************************

//******************************************************************************
// Element wise multiplication and Assign rhs to lhs =>  lhs = rhs * lhs or lhs *= rhs ;
template< typename CT1, StorageOrder SO1
        , typename CT2, StorageOrder SO2>
inline auto GlobalHadamardAssign( C2DContainer<CT1,SO1>& lhs, C2DContainer<CT2,SO2>& rhs )
    -> std::enable_if_t< IsCD2DContainer_v<CT1> >
{
    FCFD_ASSERT( (*lhs).rows() == (*rhs).rows(),"Number of rows inconsistent");
    FCFD_ASSERT( (*lhs).columns() == (*rhs).columns(),"Number of columns inconsistent");
    HadamardAssign(*lhs, *rhs);
    return;
}


}
}
#endif