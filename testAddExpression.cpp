/*******************************************************************************
Application:
    testAddExpression

Description:
    This application test the add expression template

License:
    <LICENSE_DESCRIPTION>

*******************************************************************************/



// FCFD include files

#include "expressions/CAddExprCD2DContainerCD2DContainer.hpp"
#include "containers/CDynamic2DContainer.hpp"

// typedefs
using namespace FCFD;
using namespace container;
using namespace allocator;
using namespace type_traits;
using Float_2D = CDynamic2DContainer< float
                                    , StorageOrder::SoA
                                    , AlignedAllocator<float>
                                    , AlignmentFlag::aligned>;



//==============================================================================
// Main program
//==============================================================================

int main(int argc, char const *argv[])
{
    std::cout << "This program will test the add expression template using "
         << "CDynamic2DContainer.\n";

    CDynamic2DContainer< float, StorageOrder::SoA , AlignedAllocator<float>, AlignmentFlag::aligned> A( 10UL, 10UL,0.5);
    CDynamic2DContainer< float, StorageOrder::SoA , AlignedAllocator<float>, AlignmentFlag::aligned> B( 10UL, 10UL,0.5);
    CDynamic2DContainer< float, StorageOrder::SoA , AlignedAllocator<float>, AlignmentFlag::aligned> D ( 10UL, 10UL,0.);
    D= A+B;


    return 0;
}