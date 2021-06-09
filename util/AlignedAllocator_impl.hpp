//==============================================================================
//  CONSTRUCTOR
//==============================================================================
//******************************************************************************
//  Conversion constructor from different AlignedAllocator instances.
//
// allocator The foreign aligned allocator to be copied.

template <typename T>
template <typename U>
inline AlignedAllocator<T>::AlignedAllocator
(
    [[maybe_unused]] const AlignedAllocator<U> &allocator
)
{
}
//******************************************************************************

//==============================================================================
//  ALLOCATION FUNCTIONS
//==============================================================================

//******************************************************************************
// Allocates aligned memory for the specified number of objects.
//
template <typename T>
inline T* AlignedAllocator<T>::allocate(size_t nSize)
{
    const size_t alignment(AlignmentOf_v<T>);

    if (alignment >= 8UL)
    {
        return reinterpret_cast<T *>
        (
            memory::AlignedAllocate(nSize * sizeof(T), alignment)
        );
    }
    else
    {
        return static_cast<T *>(operator new[](nSize * sizeof(T)));
    }
}
//******************************************************************************

//******************************************************************************
// Deallocation of memory.
//
template <typename T>
inline void AlignedAllocator<T>::deallocate( T *ptr )noexcept
{

    if (ptr == nullptr)
        return;

    const size_t alignment(AlignmentOf_v<T>);

    if (alignment >= 8UL)
    {
        memory::AlignedDeallocate(ptr);
    }
    else
    {
        operator delete[](ptr);
    }
}
//******************************************************************************
