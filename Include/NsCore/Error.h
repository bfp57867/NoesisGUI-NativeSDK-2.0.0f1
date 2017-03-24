////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ERROR_H__
#define __CORE_ERROR_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

/// Installs custom assert handler and returns previous one
typedef NsBool (*AssertHandler)(const NsChar* expr, const NsChar* file, NsSize line);
NS_CORE_KERNEL_API AssertHandler SetAssertHandler(AssertHandler handler);

NS_CORE_KERNEL_API NsBool InvokeAssertHandler(const NsChar* expr, const NsChar* file, NsSize line)
    CLANG_ANALYZER_NORETURN;

#define NS_INTERNAL_ASSERT(expr) \
    NS_MACRO_BLOCK_BEGIN \
        if (!(expr)) \
        { \
            if (Noesis::Core::InvokeAssertHandler(#expr, __FILE__, __LINE__) == true) \
            { \
                NS_DEBUG_BREAK; \
            } \
        } \
    NS_MACRO_BLOCK_END

#ifndef NS_ASSERT
    #ifdef _PREFAST_
        #define NS_ASSERT(expr) __analysis_assume(!!(expr)) 

    #elif NS_ASSERTS_ENABLED
        #define NS_ASSERT(expr) NS_INTERNAL_ASSERT((expr))

    #else
        #define NS_ASSERT(expr) NS_UNUSED(expr)

    #endif
#endif

#define NS_ASSERT_UNREACHABLE \
    NS_MACRO_BLOCK_BEGIN \
        NS_ASSERT(false); \
        NS_UNREACHABLE; \
    NS_MACRO_BLOCK_END

/// Installs custom error handler and returns previous one
typedef void (*ErrorHandler)(const NsChar* file, NsSize line, const NsChar* desc, NsBool fatal);
NS_CORE_KERNEL_API ErrorHandler SetErrorHandler(ErrorHandler handler);

/// NS_FATAL signals a non-recoverable error
NS_NORETURN NS_CORE_KERNEL_API void InvokeErrorHandlerFatal(const NsChar* file, NsSize line,
    _Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(3,4);

#ifndef NS_FATAL
    #define NS_FATAL(...) Noesis::Core::InvokeErrorHandlerFatal(__FILE__, __LINE__, __VA_ARGS__)
#endif

/// NS_ERROR signals a recoverable error
NS_CORE_KERNEL_API void InvokeErrorHandler(const NsChar* file, NsSize line,
    _Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(3,4);

#ifndef NS_ERROR
    #define NS_ERROR(...) Noesis::Core::InvokeErrorHandler(__FILE__, __LINE__, __VA_ARGS__)
#endif

}
}


#endif
