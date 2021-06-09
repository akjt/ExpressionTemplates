#ifndef COMMON_EXPR_CD2DCONTAINER_HPP
#define COMMON_EXPR_CD2DCONTAINER_HPP
#include "../util/StorageOrder.hpp"
#include "C2DContainer.hpp"

namespace FCFD
{
namespace expression
{

// This should be inherited by all containers not being a sparse data structure
template< typename CDT, StorageOrder SO>
class CD2DContainer : public C2DContainer<CDT,SO>
{
    protected:
//**CONSTRUCTORS*************************************************************
    CD2DContainer() = default;
//**COPY CONSTRUCTORS********************************************************
    CD2DContainer( const CD2DContainer& ) = default;
    CD2DContainer( CD2DContainer&& ) = default;
//**DESTRUCTOR CONSTRUCTORS**************************************************
    ~CD2DContainer() = default;
    CD2DContainer& operator=( const CD2DContainer& ) = default;
    CD2DContainer& operator=( CD2DContainer&& ) = default;
};

}
}

#endif