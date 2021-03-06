// bsls_atomicoperations_powerpc_aix_gcc.h                            -*-C++-*-
#ifndef INCLUDED_BSLS_ATOMICOPERATIONS_POWERPC_AIX_GCC
#define INCLUDED_BSLS_ATOMICOPERATIONS_POWERPC_AIX_GCC

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide implementations of atomic operations for PowerPC/AIX/GCC.
//
//@CLASSES:
//  bsls::AtomicOperations_POWERPC_AIX_GCC: atomics for PPC/AIX/GCC.
//
//@DESCRIPTION: This component provides classes necessary to implement atomics
// on the AIX PowerPC platform in 32bit/64bit mode with the GCC compiler.  The
// classes are for private use only.  See 'bsls_atomicoperations' and
// 'bsls_atomic' for the public interface to atomics.
//
// NOTE: this implementation is incorrect and only minimally complete.  It is
// provided for the sole purpose of passing cscheckin validation tests
// performed on AIX with the GCC compiler.

#ifndef INCLUDED_BSLS_ATOMICOPERATIONS_DEFAULT
#include <bsls_atomicoperations_default.h>
#endif

#ifndef INCLUDED_BSLS_PLATFORM
#include <bsls_platform.h>
#endif

#ifndef INCLUDED_BSLS_TYPES
#include <bsls_types.h>
#endif

#if defined(BSLS_PLATFORM_CPU_POWERPC) && defined(BSLS_PLATFORM_CMP_GNU)

namespace BloombergLP {

namespace bsls {

struct AtomicOperations_POWERPC_AIX_GCC;
typedef AtomicOperations_POWERPC_AIX_GCC  AtomicOperations_Imp;

         // ==========================================================
         // struct Atomic_TypeTraits<AtomicOperations_POWERPC_AIX_GCC>
         // ==========================================================

template <>
struct Atomic_TypeTraits<AtomicOperations_POWERPC_AIX_GCC>
{
    struct Int
    {
        volatile int d_value __attribute__((__aligned__(sizeof(int))));
    };

    struct Int64
    {
        volatile Types::Int64 d_value
                       __attribute__((__aligned__(sizeof(Types::Int64))));
    };

    struct Pointer
    {
        void * volatile d_value __attribute__((__aligned__(sizeof(void *))));
    };
};

                   // =======================================
                   // struct AtomicOperations_POWERPC_AIX_GCC
                   // =======================================

struct AtomicOperations_POWERPC_AIX_GCC
    : AtomicOperations_Default64<AtomicOperations_POWERPC_AIX_GCC>
{
    typedef Atomic_TypeTraits<AtomicOperations_POWERPC_AIX_GCC> AtomicTypes;

        // *** atomic functions for int ***

    static int getInt(const AtomicTypes::Int *atomicInt)
    {
        return atomicInt->d_value;
    }

    static void setInt(AtomicTypes::Int *atomicInt, int value)
    {
        atomicInt->d_value = value;
    }

    static int swapInt(AtomicTypes::Int *atomicInt, int swapValue)
    {
        int prev = atomicInt->d_value;
        atomicInt->d_value = swapValue;
        return prev;
    }

    static int testAndSwapInt(AtomicTypes::Int *atomicInt,
                              int compareValue,
                              int swapValue)
    {
        int prev = atomicInt->d_value;
        if (atomicInt->d_value == compareValue) {
            atomicInt->d_value = swapValue;
        }

        return prev;
    }

    static int addIntNv(AtomicTypes::Int *atomicInt, int value)
    {
        return atomicInt->d_value += value;
    }

        // *** atomic functions for Int64 ***

    static Types::Int64 getInt64(const AtomicTypes::Int64 *atomicInt)
    {
        return atomicInt->d_value;
    }

    static void setInt64(AtomicTypes::Int64 *atomicInt, Types::Int64 value)
    {
        atomicInt->d_value = value;
    }

    static Types::Int64 swapInt64(AtomicTypes::Int64  *atomicInt,
                                  Types::Int64 swapValue)
    {
        Types::Int64 prev = atomicInt->d_value;
        atomicInt->d_value = swapValue;
        return prev;
    }

    static Types::Int64 testAndSwapInt64(AtomicTypes::Int64 *atomicInt,
                                         Types::Int64 compareValue,
                                         Types::Int64 swapValue)
    {
        Types::Int64 prev = atomicInt->d_value;
        if (atomicInt->d_value == compareValue) {
            atomicInt->d_value = swapValue;
        }

        return prev;
    }

    static Types::Int64 addInt64Nv(AtomicTypes::Int64 *atomicInt,
                                   Types::Int64 value)
    {
        return atomicInt->d_value += value;
    }
};

}  // close package namespace

}  // close enterprise namespace

#endif  // BSLS_PLATFORM_CPU_POWERPC && BSLS_PLATFORM_CMP_GNU

#endif

// ----------------------------------------------------------------------------
// Copyright 2013 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
