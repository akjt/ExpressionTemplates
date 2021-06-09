#ifndef UTIL_VECTORIZATION_HPP
#define UTIL_VECTORIZATION_HPP


//******************************************************************************
// Includes
//******************************************************************************

// SSE mode
#if FCFD_USE_VECTORIZATION && defined(__SSE__)
#  define FCFD_SSE_MODE 1
#else
#  define FCFD_SSE_MODE 0
#endif


//******************************************************************************
// AVX mode
#if FCFD_USE_VECTORIZATION && defined(__AVX__)
#  define FCFD_AVX_MODE 1
#else
#  define FCFD_AVX_MODE 0
#endif
//******************************************************************************


//******************************************************************************
#if FCFD_USE_VECTORIZATION && defined(__AVX2__)
#  define FCFD_AVX2_MODE 1
#else
#  define FCFD_AVX2_MODE 0
#endif
//******************************************************************************

//******************************************************************************

#if FCFD_USE_VECTORIZATION && defined(__AVX512F__)
#  define FCFD_AVX512F_MODE 1
#else
#  define FCFD_AVX512F_MODE 0
#endif
//******************************************************************************

//==============================================================================
//  SSE/AVXINCLU DE FILE CONFIGURATION
//==============================================================================
#if FCFD_AVX512F_MODE || FCFD_AVX2_MODE || FCFD_AVX_MODE
#  include <immintrin.h>
#elif FCFD_SSE_MODE
#  include <xmmintrin.h>
#endif

#endif
