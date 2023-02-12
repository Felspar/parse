#pragma once


#include <felspar/exceptions.hpp>

#include <span>


namespace felspar::parse::binary::le {


    /// Bytes
    template<concepts::unsigned_integral T>
    inline void unchecked_insert(
            std::span<std::byte, 1> const b, T const v) noexcept {
        b[0] = std::byte(v);
    }

    /// 16 bit/WORD
    template<concepts::unsigned_integral T>
    inline void unchecked_insert(
            std::span<std::byte, 2> const b, T const v) noexcept {
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
    }

    /// 32 bit/DWORD
    template<concepts::unsigned_integral T>
    inline void unchecked_insert(
            std::span<std::byte, 4> const b, T const v) noexcept {
        b[3] = std::byte(v >> 24);
        b[2] = std::byte(v >> 16);
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
    }

    /// 64 bit/QWORD
    template<concepts::unsigned_integral T>
    inline void unchecked_insert(
            std::span<std::byte, 8> const b, T const v) noexcept {
        b[7] = std::byte(v >> 56);
        b[6] = std::byte(v >> 48);
        b[5] = std::byte(v >> 40);
        b[4] = std::byte(v >> 32);
        b[3] = std::byte(v >> 24);
        b[2] = std::byte(v >> 16);
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
    }


    template<typename T>
    inline void unchecked_insert(
            std::span<std::uint8_t, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(
                std::span<std::byte, sizeof(T)>{
                        reinterpret_cast<std::byte *>(b.data()), b.size()},
                t);
    }

    template<typename T>
    inline void unchecked_insert(
            std::span<char, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(
                std::span<std::byte, sizeof(T)>{
                        reinterpret_cast<std::byte *>(b.data()), b.size()},
                t);
    }


    /// Insert binary representation from a variable into a buffer
    template<typename T>
    inline void
            insert(std::span<std::byte> &s,
                   T const t,
                   felspar::source_location const &loc =
                           felspar::source_location::current()) {
        if (s.size() >= sizeof(T)) {
            unchecked_insert(
                    std::span<std::byte, sizeof(T)>{s.data(), sizeof(T)}, t);
            s = s.subspan(sizeof(T));
        } else {
            throw felspar::stdexcept::logic_error{
                    "Buffer isn't large enough", loc};
        }
    }


}
