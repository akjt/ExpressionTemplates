/*******************************************************************************
Class:
    CContainer
Description:
    Class for our internal dynamic arrays made friendly for optimisation stuff
    For example, arrays can be aligned.
    TODO: Apply padding if requested.
    TODO: add more details in description
Source files:
    TODO - > move code to impl file.
License:
    <LICENSE_DECRIPTION>
*******************************************************************************/

#ifndef COMMON_CDYNAMIC2DCONTAINER_HPP
#define COMMON_CDYNAMIC2DCONTAINER_HPP

#include "../util/AlignedAllocator.hpp"
#include "../util/Assert.hpp"
#include "../util/StorageOrder.hpp"
#include "../util/AlignmentFlag.hpp"
#include "../util/AddTrait.hpp"
#include "../util/IsCD2DContainer.hpp"
#include "../util/IsC2DContainer.hpp"

#include "../expressions/CD2DContainer.hpp"
#include "../Operations/D2DContainer.hpp"



namespace FCFD
{

namespace container
{

// using namespace iterator;
using namespace expression;
using namespace type_traits;

template< typename T            // data type
        , StorageOrder SO       // data order (SoA  or AoS)
        , typename Alloc         // Allocator
        , AlignmentFlag AF  > // Do we align
class CDynamic2DContainer
    : public CD2DContainer< CDynamic2DContainer<T,SO,Alloc,AF>, SO >
{
private:
    T* __restrict rawdata_;
    size_t nVar_;
    size_t nDim_;
    size_t size_;
    size_t nRows_;
    size_t nColumns_;
    [[no_unique_address]] Alloc alloc_;

    static constexpr bool SoA = (SO == StorageOrder::SoA) ? true : false;
    static constexpr bool AoS = (SO == StorageOrder::AoS) ? true : false;
    FCFD_STATIC_ASSERT_MSG( SoA != AoS, "SoA and AoS have same bool");


public:
//**Type definitions************************************************************
    using result_type     = CDynamic2DContainer<T,SO,Alloc,AF>;;
    using value_type      = T;
    using return_type     = const T&;                 // Return type used for expression template evaluations.
    using reference       = T&;                       // Reference to a non-constant matrix value.
    using const_reference = const T&;                 // Reference to a constant matrix value.
    using pointer         = T*;                       // Pointer to a non-constant matrix value.
    using const_pointer   = const T*;                 // Pointer to a constant matrix value.
    // using iterator        = CContainerIterator<T,AF>;        // Iterator over non-constant elements.
    // using const_iterator  = CContainerIterator<const T,AF>;  // Iterator over constant elements.


//**Constructors****************************************************************
    inline CDynamic2DContainer( const Alloc& alloc = Alloc{} ) noexcept;
    inline CDynamic2DContainer( size_t nVar, size_t nDim
                             , const Alloc& alloc = Alloc{} );
    inline CDynamic2DContainer( size_t nVar, size_t nDim
                              , const T& init, const Alloc& alloc = Alloc{} );

    template< typename Other >
    inline CDynamic2DContainer( size_t m, size_t n, const Other* array
                              , const Alloc& alloc = Alloc{} );

//**Copy Constructors***********************************************************
    inline CDynamic2DContainer( const CDynamic2DContainer& other );
    inline CDynamic2DContainer( CDynamic2DContainer&& other ) noexcept;
    template< typename CT2, StorageOrder SO2 >
    inline CDynamic2DContainer( const C2DContainer<CT2,SO2>& other );

//**Assignment copy**************************************************************
    inline CDynamic2DContainer& operator=( const CDynamic2DContainer& rhs ) &;
    inline CDynamic2DContainer& operator=( CDynamic2DContainer&& rhs ) & noexcept;

    template< typename CT2, StorageOrder SO2 >
    inline CDynamic2DContainer& operator=( const C2DContainer<CT2,SO2>& rhs ) &;


//******************************************************************************

//**Destructor******************************************************************
    ~CDynamic2DContainer();
//******************************************************************************

//** Access functions***********************************************************
    inline pointer         data  () noexcept {return rawdata_;};
    inline const_pointer   data  () const noexcept;
    inline pointer         data  ( size_t i ) noexcept;
    inline const_pointer   data  ( size_t i ) const noexcept;
    // inline iterator        begin ( size_t i ) noexcept;  Commented for demo
    // inline const_iterator  begin ( size_t i ) const noexcept;
    // inline const_iterator  cbegin( size_t i ) const noexcept;
    // inline iterator        end   ( size_t i ) noexcept;
    // inline const_iterator  end   ( size_t i ) const noexcept;
    // inline const_iterator  cend  ( size_t i ) const noexcept;
    inline reference       at( size_t iVar, size_t iDim );
    inline const_reference at( size_t iVar, size_t iDim ) const;
    inline reference operator()(const size_t iVar, const size_t iDim) noexcept;
    inline const_reference operator()(const size_t iVar, const size_t iDim) const noexcept;
    inline pointer operator[](const size_t k) noexcept;
    inline const_pointer operator[](const size_t k) const noexcept;
//**Expression template evaluation functions************************************

//**Serial expressions
    template< typename CT >
    inline auto Assign( const CD2DContainer<CT,SO>& rhs );
//        -> std::enable_if_t<!VectorizedAssign_v>

    template< typename CT >
    inline auto AddAssign( const CD2DContainer<CT,SO>& rhs );
//        -> std::enable_if_t<!VectorizedAssign_v>

    template< typename CT >
    inline auto SubtractAssign( const CD2DContainer<CT,SO>& rhs );
//        -> std::enable_if_t<!VectorizedAssign_v>

    template< typename CT >
    inline auto HadamardAssign( const CD2DContainer<CT,SO>& rhs );
//        -> std::enable_if_t<!VectorizedAssign_v>

//**SIMD expressions

// TODO

//**Utility functions************************************************************
    template< typename CT >
    inline const value_type
    ConsistentAccess(const  C2DContainer<CT,SO>& other
                    , size_t iRow, size_t iCol )const noexcept;

    inline size_t GetSize() const noexcept { return size_; };
    inline size_t GetNvar() const noexcept { return nVar_; };
    inline size_t GetNdim() const noexcept { return nDim_; };
    inline size_t rows()    const noexcept { return nRows_; };
    inline size_t columns() const noexcept { return nColumns_; };
    void   resize ( size_t m, size_t n, bool overwrite = false );
};

#include "CDynamic2DContainer_impl.hpp"

template <typename T>
using alignContainerSoA = CDynamic2DContainer< T
                                           , StorageOrder::SoA
                                           , allocator::AlignedAllocator< T >
                                           , AlignmentFlag::aligned >;

template <typename T>
using alignContainerAoS = CDynamic2DContainer< T
                                           , StorageOrder::AoS
                                           , allocator::AlignedAllocator<T>
                                           , AlignmentFlag::aligned >;

} // Container namespace


namespace type_traits
{
using namespace container;
using namespace allocator;

template< typename T1, typename T2 >
struct AddTraitEval1< T1, T2
                    , std::enable_if_t< IsC2DContainer_v<T1> &&
                                        IsC2DContainer_v<T2> &&
                                      ( IsCD2DContainer_v<T1> ||
                                        IsCD2DContainer_v<T2> )  >   >
{
    using value_type1 = typename T1::value_type;
    using value_type2 = typename T2::value_type;
    using value_type  = AddTrait_t< value_type1, value_type2 >;
    static constexpr StorageOrder SO   = StorageOrder::SoA;
    static constexpr AlignmentFlag AF  =  AlignmentFlag::aligned;
    // FCFD_STATIC_ASSERT_MSG( SO == T2::storage_order
    //     , "Adding containers of different storage orders is not supported yet.");

    // FCFD_STATIC_ASSERT_MSG( AF == T2::aligned
    //     , "Adding containers of oppposing alignment flag is not possible.");


//  Warning: This need to be changed later to handle cases where two containers
//  might have different allocators using the rebind strategy.
    using type = container::CDynamic2DContainer< value_type, SO, AlignedAllocator<value_type>, AF >;
};

}
}

#endif
