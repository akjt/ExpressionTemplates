/*******************************************************************************
License:
    <LICENSE_DESCRIPTION>

*******************************************************************************/

//==============================================================================
//  CONSTRUCTORS
//==============================================================================

//******************************************************************************
// The (default) constructor
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( const Alloc& alloc )noexcept
    : nVar_{ 0UL }
    , nDim_{ 0UL }
    , size_{ 0UL }
    , rawdata_{ nullptr }
    , alloc_{ alloc }
    , nRows_{ 0UL }
    , nColumns_{ 0UL }
{}
//******************************************************************************

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( size_t nVar, size_t nDim, const Alloc& alloc )
    : nVar_{ nVar }
    , nDim_{nDim}
    , size_{nVar*nDim}
    , rawdata_ { nullptr }
    , alloc_{ alloc }
{
    rawdata_ = alloc_.allocate( size_ );

    if constexpr ( SO == StorageOrder::AoS )
    {
        nRows_    = nDim_ ;
        nColumns_ =  nVar_;
    }
    else
    {
        nRows_     = nVar_ ;
        nColumns_ =  nDim_;
    }
}

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( size_t nVar, size_t nDim, const T& init, const Alloc& alloc )
    : CDynamic2DContainer( nVar, nDim, alloc )
{
    for( size_t i=0UL; i<size_; ++i )
        rawdata_[i] = init;

}
//******************************************************************************

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
template< typename Other >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer(size_t nVar, size_t nDim, const Other* array, const Alloc& alloc)
    : CDynamic2DContainer( nVar, nDim, alloc )
{
    for( size_t i=0UL; i<size_; ++i )
        rawdata_[i] = array[i];

}
//******************************************************************************

//==============================================================================
//  DESTRUCTOR
//==============================================================================

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
~CDynamic2DContainer( )
{
    alloc_.deallocate( rawdata_ );
}

//******************************************************************************

//==============================================================================
//  COPY CONSTRUCTORS
//==============================================================================
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( const CDynamic2DContainer& other )
    : CDynamic2DContainer( other.nVar_, other.nDim_ )
{
    ::FCFD::operation::GlobalAssign( *this, *other );
}
//******************************************************************************


//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( CDynamic2DContainer&& other ) noexcept
    : nVar_     { other.nVar_}
    , nDim_     { other.nDim_}
    , nColumns_ { other.nColumns_}
    , nRows_    { other.nRows_}
    , size_     { other.size_}
    , rawdata_  { other.rawdata_}
{
    other.rawdata_  = nullptr;
    other.nVar_     = 0UL;
    other.nDim_     = 0UL;
    other.nRows_    = 0UL;
    other.nColumns_ = 0UL;
    other.size_     = 0UL;
}
//******************************************************************************

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
template< typename CT2, StorageOrder SO2>
inline CDynamic2DContainer<T,SO,Alloc,Align>::
CDynamic2DContainer( const C2DContainer<CT2,SO2>& other )
    : CDynamic2DContainer( (*other).GetNvar(), (*other).GetNdim() )
{
    ::FCFD::operation::GlobalAssign( *this, *other );
}

//==============================================================================
//  ASSIGNMENT CONSTRUCTORS
//==============================================================================

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align> &
CDynamic2DContainer<T,SO,Alloc,Align>::
operator=( const CDynamic2DContainer& rhs ) &
{
    if( &rhs == this ) return *this;
    // resize( rhs.nVar_, rhs.nDim_, true );
    ::FCFD::operation::GlobalAssign( *this, *rhs );
    return *this;
}
//******************************************************************************


//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
inline CDynamic2DContainer<T,SO,Alloc,Align>&
CDynamic2DContainer<T,SO,Alloc,Align>::
operator=( CDynamic2DContainer&& rhs ) & noexcept
{
    alloc_.deallocate( rawdata_  );
    nVar_    = rhs.nVar_;
    nDim_    = rhs.nDim_;
    nColumns_ = rhs.nColumns_;
    nRows_   = rhs.nRows_;
    size_    = rhs.size_;
    rawdata_ = rhs.rawdata_;
    return *this;
}
//******************************************************************************

//******************************************************************************
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
template< typename CT2, StorageOrder SO2 >
inline CDynamic2DContainer<T,SO,Alloc,Align>&
    CDynamic2DContainer<T,SO,Alloc,Align>::
        operator=( const C2DContainer<CT2,SO2>& rhs ) &
{
    // resize((*rhs).GetNvar(), (*rhs).GetNdim(), true);
    ::FCFD::operation::GlobalAssign( *this, *rhs );
    return *this;
}
//******************************************************************************

//==============================================================================
//  EXPRESSION TEMPLATE FUNCTIONS
//==============================================================================


//***NO SIMD expressions type***************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
template< typename CT >
inline auto CDynamic2DContainer< T,  SO, Alloc, Align >::
Assign( const CD2DContainer<CT,SO>& rhs )
// -> std::enable_if_t<!VectorizedAssign_v> removed for demo
{
    FCFD_ASSERT( nRows_ == (*rhs).rows()  , "Number of rows inconsistent"    );
    FCFD_ASSERT( nColumns_ == (*rhs).columns(), "Number of columns inconsistent" );

    for (size_t i = 0UL; i < nRows_ ; i++) {
        for (size_t j = 0UL; j < nColumns_; j++) {
            rawdata_[i*nColumns_ + j] = ConsistentAccess(rhs, i, j);
        }
    }

}
//******************************************************************************


//******************************************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
template< typename CT >
inline auto CDynamic2DContainer< T,  SO, Alloc, Align >::
AddAssign( const CD2DContainer<CT,SO>& rhs )
// -> std::enable_if_t<!VectorizedAssign_v> removed for demo
{
    FCFD_ASSERT( nRows_    == (*rhs).rows()   , "Number of rows inconsistent"    );
    FCFD_ASSERT( nColumns_ == (*rhs).columns(), "Number of columns inconsistent" );

    for (size_t i = 0UL; i < nRows_ ; i++) {
        for (size_t j = 0UL; j < nColumns_; j++) {
            rawdata_[i*nColumns_ + j] += ConsistentAccess(rhs, i, j);
        }
    }

}
//******************************************************************************


//******************************************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
template< typename CT >
inline auto CDynamic2DContainer< T,  SO, Alloc, Align >::
SubtractAssign( const CD2DContainer<CT,SO>& rhs )
// -> std::enable_if_t<!VectorizedAssign_v> removed for demo
{
    FCFD_ASSERT( nRows_    == (*rhs).rows()   , "Number of rows inconsistent"    );
    FCFD_ASSERT( nColumns_ == (*rhs).columns(), "Number of columns inconsistent" );

    for (size_t i = 0UL; i < nRows_ ; i++) {
        for (size_t j = 0UL; j < nColumns_; j++) {
            rawdata_[i*nColumns_ + j] -= ConsistentAccess(rhs, i, j);
        }
    }

}
//******************************************************************************


//******************************************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
template< typename CT >
inline auto CDynamic2DContainer< T,  SO, Alloc, Align >::
HadamardAssign( const CD2DContainer<CT,SO>& rhs )
// -> std::enable_if_t<!VectorizedAssign_v> removed for demo
{
    FCFD_ASSERT( nRows_    == (*rhs).rows()   , "Number of rows inconsistent"    );
    FCFD_ASSERT( nColumns_ == (*rhs).columns(), "Number of columns inconsistent" );

    for (size_t i = 0UL; i < nRows_ ; i++) {
        for (size_t j = 0UL; j < nColumns_; j++) {
            rawdata_[i*nColumns_ + j] *= ConsistentAccess(rhs, i, j);
        }
    }

}
//******************************************************************************


//*** SIMD expressions type*****************************************************

//******************************************************************************


//==============================================================================
//  ACCESS FUNCTIONS
//==============================================================================

//******************************************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
inline typename CDynamic2DContainer< T,  SO, Alloc, Align >::const_reference
CDynamic2DContainer< T,  SO, Alloc, Align >::
operator()( const size_t iVar, const size_t iDim)const noexcept
{
    FCFD_ASSERT(iVar >= 0 && iVar < nVar_ && iDim >= 0 && iDim < nDim_
        , "Access index out of bounds");

    return rawdata_[(SO == StorageOrder::SoA) ? iVar * nDim_ + iDim
                                              : iVar + iDim * nDim_];
}

//******************************************************************************
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
inline typename CDynamic2DContainer< T,  SO, Alloc, Align >::reference
CDynamic2DContainer< T,  SO, Alloc, Align >::
operator()( const size_t iVar, const size_t iDim) noexcept

{
    const CDynamic2DContainer &const_this = *this;
    return const_cast<T &>(const_this(iVar, iDim));
}
//******************************************************************************


//******************************************************************************
// Return the first row of the variable
// if AoS it would be the cell of all variables
// if SoA it would be the one variable of all cells
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
inline typename CDynamic2DContainer< T,  SO, Alloc, Align >::pointer
CDynamic2DContainer< T,  SO, Alloc, Align>::
operator[](const size_t k) noexcept
{
    const CDynamic2DContainer &const_this = *this;
    return const_cast<T &>(const_this[k]);
}
//******************************************************************************


//******************************************************************************
// Return the first row of the variable - const version
template <typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align>
inline typename CDynamic2DContainer< T,  SO, Alloc, Align >::const_pointer
CDynamic2DContainer< T,  SO, Alloc, Align >::
operator[](const size_t k) const noexcept
{
    if constexpr (SO == StorageOrder::SoA)
    {
        assert(k >= 0 && k < nVar_);
        return &rawdata_[k * nDim_];
    }
    else
    {
        assert(k >= 0 && k < nDim_);
        return &rawdata_[k * nVar_];
    }
}

//******************************************************************************

//==============================================================================
// UTILITY
//==============================================================================
template< typename T, StorageOrder SO, typename Alloc, AlignmentFlag Align >
template< typename CT >
inline const typename CDynamic2DContainer< T,  SO, Alloc, Align >::value_type
CDynamic2DContainer< T,  SO, Alloc, Align >::
ConsistentAccess(  const C2DContainer<CT,SO>& other
                 , size_t iRow , size_t iCol )const noexcept
{
    if constexpr ( SoA )
        return static_cast<T>( (*other)(iRow,iCol) );
    else
        return static_cast<T>( (*other)(iCol,iRow) ) ;
}
