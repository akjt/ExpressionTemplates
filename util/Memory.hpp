
#ifndef ALLOCATION_TOOLS_HPP
#define ALLOCATION_TOOLS_HPP


#include <stdlib.h>
#include <cstddef>
#include <type_traits>

using size_t = std::size_t;
using byte_t = std::byte;

namespace FCFD
{
namespace memory
{
//==============================================================================
//  ALLOCATION FUNCTIONS BASED ON RAW BYTES
//==============================================================================

//******************************************************************************
inline byte_t* AlignedAllocate( size_t size, size_t alignment )
{
    void *raw(nullptr);
    raw = std::aligned_alloc( alignment, size );
    return reinterpret_cast<byte_t *>(raw);
}

//******************************************************************************
// Aligned array allocation for built-in data types .e.g.
// allocate an array with 20 elements which is guaranteed to be aligned,
// double* cPtrArray = allocate( 20UL )
template <typename T, std::enable_if_t<std::is_fundamental_v<T>>* = nullptr>
inline T *allocate(size_t size)
{
    constexpr size_t alignment(type_traits::AlignmentOf_v<T>);

    return reinterpret_cast<T *>(AlignedAllocate(size * sizeof(T), alignment));
}
//******************************************************************************

//******************************************************************************
// Deallocation of aligned memory.
inline void AlignedDeallocate(const void *address) noexcept
{
    std::free(const_cast<void *>(address));
}
//******************************************************************************

//******************************************************************************
// deallocate
template <typename T, std::enable_if_t<std::is_fundamental_v<T>> * = nullptr>
inline void deallocate( T* address )noexcept
{
    if( address == nullptr )
        return;
    AlignedDeallocate( address );
    return;
}
//******************************************************************************

}; // memory_allocation
}; // FCFD
#endif