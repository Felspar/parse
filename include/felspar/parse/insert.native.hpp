#pragma once


#include <felspar/parse/concepts.hpp>
#include <felspar/parse/exceptions.hpp>
#include <felspar/parse/insert.detail.hpp>


namespace felspar::parse::binary::native {


    /// ## Insert binary representation of the type using native byte order


    /// ### Insert into the buffer without checking the length
    template<concepts::numeric T>
    inline void unchecked_insert(
            std::span<std::byte, sizeof(T)> const s, T const t) {
        if constexpr (sizeof(T) == 1) {
            s[0] = std::byte{t};
        } else {
            detail::native_insert(s, t);
        }
    }

    template<concepts::numeric T>
    inline void unchecked_insert(
            std::span<std::uint8_t, sizeof(T)> const s, T const t) {
        unchecked_insert(std::as_writable_bytes(s), t);
    }
    template<concepts::numeric T>
    inline void unchecked_insert(std::span<char, sizeof(T)> const s, T const t) {
        unchecked_insert(std::as_writable_bytes(s), t);
    }


    /// ### Insert into buffer after checking the buffer length
    template<concepts::numeric T>
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
