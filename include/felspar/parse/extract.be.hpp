#pragma once


#include <felspar/exceptions.hpp>

#include <span>


namespace felspar::parse::binary::be {


    /// Extract an instance of a requested type from the memory pointed to by
    /// the span
    template<typename T>
    T unchecked_extract(std::span<std::uint8_t const, sizeof(T)>) noexcept;

    template<typename T>
    inline T unchecked_extract(
            std::span<std::byte const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::span<std::uint8_t const, sizeof(T)>{
                reinterpret_cast<std::uint8_t const *>(s.data()), s.size()});
    }

    template<typename T>
    inline T unchecked_extract(
            std::span<char const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::span<std::uint8_t const, sizeof(T)>{
                reinterpret_cast<std::uint8_t const *>(s.data()), s.size()});
    }


    /// Bytes
    template<>
    inline std::uint8_t unchecked_extract<std::uint8_t>(
            std::span<std::uint8_t const, 1> const s) noexcept {
        return s[0];
    }

    /// 16 bit/WORD
    template<>
    inline std::uint16_t unchecked_extract<std::uint16_t>(
            std::span<std::uint8_t const, 2> const s) noexcept {
        return (s[0] << 8) + s[1];
    }

    /// 32 bit/DWORD
    template<>
    inline std::uint32_t unchecked_extract<std::uint32_t>(
            std::span<std::uint8_t const, 4> const s) noexcept {
        return (s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3];
    }


    /// Extract from a variable length data span
    template<typename T>
    inline T
            extract(std::span<std::uint8_t const> &s,
                    felspar::source_location const &loc =
                            felspar::source_location::current()) {
        if (s.size() >= sizeof(T)) {
            auto const v = unchecked_extract<T>(
                    std::span<std::uint8_t const, sizeof(T)>{
                            s.data(), sizeof(T)});
            s = s.subspan(sizeof(T));
            return v;
        } else {
            throw felspar::stdexcept::logic_error{
                    "Buffer doesn't have enough data", loc};
        }
    }


}
