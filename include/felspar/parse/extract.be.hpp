#pragma once


#include <span>

#include <felspar/test/source.hpp>


namespace felspar::parse::binary::be {


    /// Extract an instance of a requested type from the memory pointed to by
    /// the span
    template<typename T>
    T unchecked_extract(
            std::span<std::uint8_t> &,
            felspar::source_location const & =
                    felspar::source_location::current());

    template<typename T>
    inline T unchecked_extract(
            std::span<std::byte> &s,
            felspar::source_location const &loc =
                    felspar::source_location::current()) {
        auto i = std::span<std::uint8_t>{
                reinterpret_cast<std::uint8_t *>(s.data()), s.size()};
        auto const v = unchecked_extract<T>(i, loc);
        s = std::span<std::byte>{
                reinterpret_cast<std::byte *>(i.data()), i.size()};
        return v;
    }

    // template<typename T>
    // inline T
    //         extract(std::span<char> &s,
    //                 felspar::source_location const &loc =
    //                         felspar::source_location::current()) {
    //     return extract<T>(
    //             std::span<std::uint8_t>{
    //                     reinterpret_cast<std::uint8_t*>(s.data()), s.size()},
    //             loc);
    // }


    /// Bytes
    template<>
    inline std::uint8_t unchecked_extract<std::uint8_t>(
            std::span<std::uint8_t> &s, felspar::source_location const &) {
        auto const v = s[0];
        s = s.subspan(1);
        return v;
    }


}
