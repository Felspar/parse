#pragma once


#include <felspar/exceptions.hpp>

#include <span>


namespace felspar::parse::binary::be {


    /// Insert data of the requested type into the memory described by the span
    template<typename T>
    void unchecked_insert(std::span<std::uint8_t, sizeof(T)>, T) noexcept;

    template<typename T>
    inline void unchecked_insert(
            std::span<std::byte, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(
                std::span<std::uint8_t, sizeof(T)>{
                        reinterpret_cast<std::uint8_t *>(b.data()), b.size()},
                t);
    }

    template<typename T>
    inline void unchecked_insert(
            std::span<char, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(
                std::span<std::uint8_t, sizeof(T)>{
                        reinterpret_cast<std::uint8_t *>(b.data()), b.size()},
                t);
    }


    /// Bytes
    template<>
    inline void unchecked_insert(
            std::span<std::uint8_t, 1> const b, std::uint8_t const v) noexcept {
        b[0] = v;
    }

    /// 16 bit/WORD
    template<>
    inline void unchecked_insert(
            std::span<std::uint8_t, 2> const b,
            std::uint16_t const v) noexcept {
        b[0] = v >> 8;
        b[1] = v;
    }

    /// 32 bit/DWORD
    template<>
    inline void unchecked_insert(
            std::span<std::uint8_t, 4> const b,
            std::uint32_t const v) noexcept {
        b[0] = v >> 24;
        b[1] = v >> 16;
        b[2] = v >> 8;
        b[3] = v;
    }


    /// Insert binary representation from a variable into a buffer
    template<typename T>
    inline void
            insert(std::span<std::uint8_t> &s,
                   T const t,
                   felspar::source_location const &loc =
                           felspar::source_location::current()) {
        if (s.size() >= sizeof(T)) {
            unchecked_insert(
                    std::span<std::uint8_t, sizeof(T)>{s.data(), sizeof(T)}, t);
            s = s.subspan(sizeof(T));
        } else {
            throw felspar::stdexcept::logic_error{
                    "Buffer isn't large enough", loc};
        }
    }


}
