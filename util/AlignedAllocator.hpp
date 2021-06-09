/*******************************************************************************
Namespace:
    FCFD::AllignedAllocator

Description:


Source files:


License:
    <LICENSE_DESCRIPTION>

*******************************************************************************/
#ifndef UTIL_ALIGNEDALLOCATOR_HPP
#define UTIL_ALIGNEDALLOCATOR_HPP
#include<cstddef>


#include "AlignmentOf.hpp"
#include "Memory.hpp"

namespace FCFD
{
namespace allocator
{

using namespace type_traits;

template< typename T >
class AlignedAllocator
{
public:
//**Type definitions************************************************************
    // STL allocator requirements
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
//******************************************************************************

//**rebind class definition*****************************************************
// Implementation of the AlignedAllocator rebind mechanism.
    template< typename U >
    struct rebind
    {
        using other = AlignedAllocator<U>;  //! Type of the other allocator.
    };

//**Constructors****************************************************************
    AlignedAllocator() = default;

    template< typename U >
    inline AlignedAllocator( const AlignedAllocator<U>& );
//******************************************************************************

//**Allocation functions********************************************************
    inline T*   allocate  ( std::size_t nSize );
    inline void deallocate( T* ptr ) noexcept;
//******************************************************************************
};
//******************************************************************************

#include "AlignedAllocator_impl.hpp"

} // allocator
} // FCFD

#endif
