#pragma once


#include <span>


namespace felspar::parse::binary::detail {


    template<typename T>
    T native_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        T into;
        std::copy(
                s.begin(), s.end(),
                std::as_writable_bytes(std::span{&into, 1}).begin());
        return into;
    }
    template<typename T>
    T non_native_extract(std::span<std::byte const, sizeof(T)> const s) noexcept {
        T into;
        std::copy(
                s.rbegin(), s.rend(),
                std::as_writable_bytes(std::span{&into, 1}).begin());
        return into;
    }


}
