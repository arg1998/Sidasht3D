#pragma once

#include "S3D/Definitions.hpp"

#include <tracy/Tracy.hpp>

#if defined(S3D_RELEASE_PROFILING_BUILD)

    constexpr u16 TRACY_STACK_CAPTURE_SIZE = 32;

    inline void* __S3D_PRIVATE__MALLOC_PROFILED(size_t size) {
        ZoneScopedN("Heap Alloc");
        void* ptr = std::malloc(size);
        TracyAllocS(ptr, size, TRACY_STACK_CAPTURE_SIZE);
        return ptr;
    }

    inline void __S3D_PRIVATE__FREE_PROFILED(void* ptr) {
        ZoneScopedN("Heap Free");
        std::free(ptr);
        TracyFreeS(ptr, TRACY_STACK_CAPTURE_SIZE);
    }

    inline void* operator new(std::size_t size) {
        return __S3D_PRIVATE__MALLOC_PROFILED(size);
    }

    inline void* operator new[](std::size_t size) {
        return __S3D_PRIVATE__MALLOC_PROFILED(size);
    }

    inline void operator delete(void* ptr) noexcept {
        __S3D_PRIVATE__FREE_PROFILED(ptr);
    }

    inline void operator delete[](void* ptr) noexcept {
        __S3D_PRIVATE__FREE_PROFILED(ptr);
    }

    extern "C" {
        inline void* malloc(size_t size) { return __S3D_PRIVATE__MALLOC_PROFILED(size); }
        inline void free(void* ptr) { __S3D_PRIVATE__FREE_PROFILED(ptr); }
    }

#endif