#pragma once


#include <felspar/exceptions.hpp>

#include <span>


namespace felspar::parse::binary::le {


    /// Insert data of the requested type into the memory described by the span
    template<typename T>
    void unchecked_insert(std::span<std::byte, sizeof(T)>, T) noexcept;

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


    /// Bytes
    template<>
    inline void unchecked_insert(
            std::span<std::byte, 1> const b, std::uint8_t const v) noexcept {
        b[0] = std::byte(v);
    }

    /// 16 bit/WORD
    template<>
    inline void unchecked_insert(
            std::span<std::byte, 2> const b, std::uint16_t const v) noexcept {
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
    }

    /// 32 bit/DWORD
    template<>
    inline void unchecked_insert(
            std::span<std::byte, 4> const b, std::uint32_t const v) noexcept {
        b[3] = std::byte(v >> 24);
        b[2] = std::byte(v >> 16);
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
    }

    /// 64 bit/QWORD
    template<>
    inline void unchecked_insert(
            std::span<std::byte, 8> const b, std::uint64_t const v) noexcept {
        b[7] = std::byte(v >> 56);
        b[6] = std::byte(v >> 48);
        b[5] = std::byte(v >> 40);
        b[4] = std::byte(v >> 32);
        b[3] = std::byte(v >> 24);
        b[2] = std::byte(v >> 16);
        b[1] = std::byte(v >> 8);
        b[0] = std::byte(v);
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
