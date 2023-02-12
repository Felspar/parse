#pragma once


#include <felspar/exceptions.hpp>
#include <felspar/parse/concepts.hpp>

#include <span>


namespace felspar::parse::binary::be {


    /// Extract an instance of a requested type from the memory pointed to by
    /// the span
    template<detail::unsigned_integral T>
    T unchecked_extract(std::span<std::byte const, sizeof(T)>) noexcept;

    template<detail::signed_integral T>
    T unchecked_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        return unchecked_extract<std::make_unsigned_t<T>>(s);
    }

    template<typename T>
    inline T unchecked_extract(
            std::span<std::uint8_t const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::span<std::byte const, sizeof(T)>{
                reinterpret_cast<std::byte const *>(s.data()), s.size()});
    }

    template<typename T>
    inline T unchecked_extract(
            std::span<char const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::span<std::byte const, sizeof(T)>{
                reinterpret_cast<std::byte const *>(s.data()), s.size()});
    }


    /// boolean
    template<>
    inline bool unchecked_extract<bool>(
            std::span<std::byte const, 1> const s) noexcept {
        return s[0] != std::byte{};
    }


    /// Bytes
    template<>
    inline std::uint8_t unchecked_extract<std::uint8_t>(
            std::span<std::byte const, 1> const s) noexcept {
        return std::uint8_t(s[0]);
    }

    /// 16 bit/WORD
    template<>
    inline std::uint16_t unchecked_extract<std::uint16_t>(
            std::span<std::byte const, 2> const s) noexcept {
        return (std::uint16_t(s[0]) << 8) + std::uint16_t(s[1]);
    }

    /// 32 bit/DWORD
    template<>
    inline std::uint32_t unchecked_extract<std::uint32_t>(
            std::span<std::byte const, 4> const s) noexcept {
        return (std::uint32_t(s[0]) << 24) + (std::uint32_t(s[1]) << 16)
                + (std::uint32_t(s[2]) << 8) + std::uint32_t(s[3]);
    }

    /// 64 bit/QWORD
    template<>
    inline std::uint64_t unchecked_extract<std::uint64_t>(
            std::span<std::byte const, 8> const s) noexcept {
        return (std::int64_t(s[0]) << 56) + (std::int64_t(s[1]) << 48)
                + (std::int64_t(s[2]) << 40) + (std::int64_t(s[3]) << 32)
                + (std::int64_t(s[4]) << 24) + (std::int64_t(s[5]) << 16)
                + (std::int64_t(s[6]) << 8) + std::int64_t(s[7]);
    }


    /// Extract from a variable length data span
    template<typename T>
    inline T
            extract(std::span<std::byte const> &s,
                    felspar::source_location const &loc =
                            felspar::source_location::current()) {
        if (s.size() >= sizeof(T)) {
            auto const v = unchecked_extract<T>(
                    std::span<std::byte const, sizeof(T)>{s.data(), sizeof(T)});
            s = s.subspan(sizeof(T));
            return v;
        } else {
            throw felspar::stdexcept::logic_error{
                    "Buffer doesn't have enough data", loc};
        }
    }


}
