#pragma once


#include <span>


namespace felspar::parse::binary::detail {


    template<typename T>
    inline void native_insert(
            std::span<std::byte, sizeof(T)> const s, T const t) noexcept {
        auto const addr = reinterpret_cast<std::byte const *>(&t);
        std::copy(addr, addr + sizeof(T), s.begin());
    }
    template<typename T>
    inline void non_native_insert(
            std::span<std::byte, sizeof(T)> const s, T const t) noexcept {
        auto const input =
                std::span{reinterpret_cast<std::byte const *>(&t), sizeof(T)};
        std::copy(input.rbegin(), input.rend(), s.begin());
    }


}
