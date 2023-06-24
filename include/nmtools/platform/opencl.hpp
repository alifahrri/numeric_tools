#ifndef NMTOOLS_PLATFORM_OPENCL_HPP
#define NMTOOLS_PLATFORM_OPENCL_HPP

// compiling opencl kernel
#define NMTOOLS_DISABLE_STL
#define NMTOOLS_UTL_NO_MALLOC
#define NMTOOLS_DISABLE_DYNAMIC_ARRAY
#define NMTOOLS_DISABLE_VECTOR
#define NMTOOLS_META_MAKE_SEQUENCE
#define nmtools_list ::nmtools::utl::static_vector
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM 8

// NOTE: on spirv, we can't have access / cast to base class
#define NMTOOLS_NO_BASE_ACCESS

#endif // NMTOOLS_PLATFORM_OPENCL_HPP