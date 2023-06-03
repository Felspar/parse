#pragma once


#include <span>


namespace felspar::parse::binary::detail {


    template<typename T>
    inline T native_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        T into;
        std::copy(s.begin(), s.end(), reinterpret_cast<std::byte *>(&into));
        return into;
    }
    template<typename T>
    inline T non_native_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        T into;
        std::copy(s.rbegin(), s.rend(), reinterpret_cast<std::byte *>(&into));
        return into;
    }


}
