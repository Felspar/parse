#pragma once


#include <felspar/parse/concepts.hpp>
#include <felspar/parse/exceptions.hpp>
#include <felspar/parse/extract.detail.hpp>


namespace felspar::parse::binary::native {


    /// ## Extract a value without checking that the span is large enough
    template<concepts::numeric T>
    inline T unchecked_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        if constexpr (sizeof(T) == 1u) {
            return static_cast<T>(s[0]);
        } else {
            return detail::native_extract<T>(s);
        }
    }


    template<concepts::numeric T>
    inline T unchecked_extract(std::span<std::uint8_t const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::as_bytes(s));
    }
    template<concepts::numeric T>
    inline T unchecked_extract(std::span<char const, sizeof(T)> const s) noexcept {
        return unchecked_extract<T>(std::as_bytes(s));
    }


    /// ## Extract a numeric from a buffer
    template<concepts::numeric T>
    inline T extract(std::span<std::byte const> &s,
                    felspar::source_location const &loc =
                            felspar::source_location::current()) {
        buffer_too_small::check(sizeof(T), s.size(), loc);
        auto const v = unchecked_extract<T>(
                std::span<std::byte const, sizeof(T)>{s.data(), sizeof(T)});
        s = s.subspan(sizeof(T));
        return v;
    }


}
