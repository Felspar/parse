#pragma once


#include <felspar/exceptions.hpp>


namespace felspar::parse::binary {


    class buffer_too_small : public stdexcept::logic_error {
    public:
        buffer_too_small(felspar::source_location const &loc =
                           felspar::source_location::current())
        : stdexcept::logic_error{"Buffer is too small", loc} {}
        buffer_too_small(std::size_t const wants, std::size_t const has,
                         felspar::source_location const &loc =
                           felspar::source_location::current())
        : stdexcept::logic_error{"Buffer is too small\n"
            "Wants " + std::to_string(wants) + " bytes, but only has " + std::to_string(has) + " bytes", loc} {}
    };


}
