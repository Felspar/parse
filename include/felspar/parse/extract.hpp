#pragma once


#include <span>

#include <felspar/test/source.hpp>


namespace felspar::parse::binary {


    /// Extract an instance of a requested type from the memory pointed to by
    /// the span
    template<typename T>
    T extract(
            std::span<std::uint8_t> &,
            felspar::source_location const & =
                    felspar::source_location::current());

    template<typename T, std::size_t N>
    inline T
            extract(std::span<std::byte, N> &s,
                    felspar::source_location const &loc =
                            felspar::source_location::current()) {
        return extract(
                std::span<std::uint8_t, N>{
                        reinterpret_cast<std::uint8_t>(s.data()), s.size()},
                loc);
    }

    template<typename T, std::size_t N>
    inline T
            extract(std::span<char, N> &s,
                    felspar::source_location const &loc =
                            felspar::source_location::current()) {
        return extract(
                std::span<std::uint8_t, N>{
                        reinterpret_cast<std::uint8_t>(s.data()), s.size()},
                loc);
    }


}
