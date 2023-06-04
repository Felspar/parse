#pragma once


#include <felspar/parse/concepts.hpp>
#include <felspar/parse/endian.hpp>
#include <felspar/parse/exceptions.hpp>
#include <felspar/parse/extract.detail.hpp>


namespace felspar::parse::binary::le {


    template<concepts::numeric T>
    T unchecked_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        if constexpr (sizeof(T) == 1u) {
            return static_cast<T>(s[0]);
        } else if constexpr (endian::native == endian::little) {
            return detail::native_extract<T>(s);
        } else {
            return detail::non_native_extract<T>(s);
        }
    }
    template<concepts::numeric T>
    T unchecked_extract(
            std::span<std::uint8_t const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::as_bytes(s));
    }
    template<concepts::numeric T>
    T unchecked_extract(std::span<char const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::as_bytes(s));
    }


    /// Extract from a variable length data span
    template<typename T>
    T extract(
            std::span<std::byte const> &s,
            felspar::source_location const &loc =
                    felspar::source_location::current()) {
        buffer_too_small::check(sizeof(T), s.size(), loc);
        auto const v = unchecked_extract<T>(
                std::span<std::byte const, sizeof(T)>{s.data(), sizeof(T)});
        s = s.subspan(sizeof(T));
        return v;
    }


}
