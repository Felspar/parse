#pragma once


#include <felspar/exceptions.hpp>
#include <felspar/parse/concepts.hpp>

#include <span>


namespace felspar::parse::binary::native {


    /// ## Insert binary representation of the type using native byte order


    /// ### Insert into the buffer without checking the length
    template<concepts::numeric T>
    inline void unchecked_insert(std::span<std::byte, sizeof(T)> const s, T const t) {
        std::span<std::byte const, sizeof(T)> b{reinterpret_cast<std::byte const *>(&t), sizeof(T)};
        std::copy(b.begin(), b.end(), s.begin());
    }
    inline void unchecked_insert(std::span<std::byte, 1> s, std::byte const i) {
        s[0] = i;
    }
    inline void unchecked_insert(std::span<std::byte, 1> s, std::uint8_t const i) {
        s[0] = std::byte{i};
    }

    template<concepts::numeric T>
    inline void unchecked_insert(std::span<std::uint8_t, sizeof(T)> const s, T const t) {
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
        if (s.size() >= sizeof(T)) {
            unchecked_insert(std::span<std::byte, sizeof(T)>{s.data(), sizeof(T)}, t);
            s = s.subspan(sizeof(T));
        } else {
            throw felspar::stdexcept::logic_error{
                    "Buffer isn't large enough", loc};
        }
    }


}
