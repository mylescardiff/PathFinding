#pragma once
#include <stdint.h>
/** \file Hasher.h */
// Created by Myles Cardiff

// taken from: https://gist.github.com/underscorediscovery/81308642d0325fd386237cfa3b44785c
// FNV1a c++11 constexpr compile time hash functions, 32 and 64 bit
// str should be a null terminated string literal, value should be left out 
// e.g hash_32_fnv1a_const("example")
// code license: public domain or equivalent
// post: https://notes.underscorediscovery.com/constexpr-fnv1a/

namespace slth
{
    constexpr uint32_t val_32_const = 0x811c9dc5;
    constexpr uint32_t prime_32_const = 0x1000193;
    constexpr uint64_t val_64_const = 0xcbf29ce484222325;
    constexpr uint64_t prime_64_const = 0x100000001b3;

    /// <summary>
    /// Compile Time Hashing Functions
    /// </summary>
    class Hasher
    {
    public:

        inline static constexpr uint32_t Hash32(const char* const str, const uint32_t value = val_32_const) noexcept {
            return (str[0] == '\0') ? value : Hash32(&str[1], (value ^ uint32_t(str[0])) * prime_32_const);
        }

        inline static constexpr uint64_t Hash64(const char* const str, const uint64_t value = val_64_const) noexcept {
            return (str[0] == '\0') ? value : Hash64(&str[1], (value ^ uint64_t(str[0])) * prime_64_const);
        }


    };
};