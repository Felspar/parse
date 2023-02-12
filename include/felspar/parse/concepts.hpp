#pragma once


#include <concepts>
#include <type_traits>


namespace felspar::parse::concepts {


    /// Shims for concepts missing on Android :-(
    template<class T>
    concept integral = std::is_integral_v<T>;

    template<class T>
    concept signed_integral = integral<T> and std::is_signed_v<T>;

    template<class T>
    concept unsigned_integral = integral<T> and not
    signed_integral<T>;


}
