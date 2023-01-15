#pragma once


#include <felspar/exceptions.hpp>

#include <span>


namespace felspar::parse::binary::be {


    /// Insert data of the requested type into the memory described by the span
    template<typename T>
    void unchecked_insert(std::span<std::uint8_t, sizeof(T)>, T) noexcept;

    template<typename T>
    inline void unchecked_insert(
            std::span<std::byte, sizeof(T)> b, T const t) noexcept {
        unchecked_insert(
                std::span<std::uint8_t, sizeof(T)>{
                        reinterpret_cast<std::uint8_t *>(b.data()), b.size()},
                t);
    }

    template<typename T>
    inline void
            unchecked_insert(std::span<char, sizeof(T)> b, T const t) noexcept {
        unchecked_insert(
                std::span<std::uint8_t, sizeof(T)>{
                        reinterpret_cast<std::uint8_t *>(b.data()), b.size()},
                t);
    }


    /// Bytes
    template<>
    inline void unchecked_insert(
            std::span<std::uint8_t, 1> b, std::uint8_t const v) noexcept {
        b[0] = v;
    }

    /// 16 bit/WORD


}
