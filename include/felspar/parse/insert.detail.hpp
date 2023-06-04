#pragma once


#include <span>


namespace felspar::parse::binary::detail {


    template<typename T>
    inline void native_insert(
            std::span<std::byte, sizeof(T)> const s, T const t) noexcept {
        auto const input = std::as_bytes(std::span{&t, 1});
        std::copy(input.begin(), input.end(), s.begin());
    }
    template<typename T>
    inline void non_native_insert(
            std::span<std::byte, sizeof(T)> const s, T const t) noexcept {
        auto const input = std::as_bytes(std::span{&t, 1});
        std::copy(input.rbegin(), input.rend(), s.begin());
    }


}
