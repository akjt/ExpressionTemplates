template< typename CDT1, typename CDT2, StorageOrder SO >
inline CAddExprCD2DContainerCD2DContainer<CDT1, CDT2, SO>::
CAddExprCD2DContainerCD2DContainer( const CDT1& lhs, const CDT2& rhs )noexcept
    : lhs_{lhs}
    , rhs_{rhs}
{
    FCFD_ASSERT(lhs.rows() == rhs.rows() , "Number of rows not matching");
    FCFD_ASSERT(lhs.columns() == rhs.columns()
              , "Number of columns not matching");
}

template< typename CDT1, typename CDT2, StorageOrder SO >
inline
typename CAddExprCD2DContainerCD2DContainer<CDT1, CDT2, SO>::return_type
CAddExprCD2DContainerCD2DContainer<CDT1, CDT2, SO>::
operator() ( const size_t i, const size_t j )const noexcept
{
    FCFD_ASSERT(i < lhs_.rows(), "Row access index out of bound" );
    FCFD_ASSERT(j < rhs_.columns(), "Column access index out of bound" );
    return lhs_(i,j) + rhs_(i,j);
}


template< typename CDT1, typename CDT2, StorageOrder SO >
decltype(auto)
operator+( const CD2DContainer<CDT1,SO>& lhs, const CD2DContainer<CDT2,SO>& rhs )
{
    if( (*lhs).rows() != (*rhs).rows() || (*lhs).columns() != (*rhs).columns() )
        FCFDError( "The size of lhs/rhs containers do not match" );

    using returntype = const CAddExprCD2DContainerCD2DContainer<CDT1,CDT2,SO>;
    return returntype(*lhs, *rhs);
}