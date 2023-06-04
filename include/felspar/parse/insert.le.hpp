#pragma once


#include <felspar/parse/concepts.hpp>
#include <felspar/parse/endian.hpp>
#include <felspar/parse/exceptions.hpp>
#include <felspar/parse/insert.detail.hpp>


namespace felspar::parse::binary::le {


    template<concepts::numeric T>
    inline void unchecked_insert(std::span<std::byte, sizeof(T)> s, T const t) {
        if constexpr (sizeof(T) == 1u) {
            s[0] = static_cast<std::byte>(t);
        } else if constexpr (endian::native == endian::little) {
            detail::native_insert(s, t);
        } else {
            detail::non_native_insert(s, t);
        }
    }


    template<typename T>
    inline void unchecked_insert(
            std::span<std::uint8_t, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(std::as_writable_bytes(b), t);
    }
    template<typename T>
    inline void unchecked_insert(
            std::span<char, sizeof(T)> const b, T const t) noexcept {
        unchecked_insert(std::as_writable_bytes(b), t);
    }


    /// Insert binary representation from a variable into a buffer
    template<typename T>
    inline void
            insert(std::span<std::byte> &s,
                   T const t,
                   felspar::source_location const &loc =
                           felspar::source_location::current()) {
        buffer_too_small::check(sizeof(T), s.size(), loc);
        unchecked_insert(
                std::span<std::byte, sizeof(T)>{s.data(), sizeof(T)}, t);
        s = s.subspan(sizeof(T));
    }


}
