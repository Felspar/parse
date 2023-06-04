#pragma once


#include <felspar/exceptions.hpp>


namespace felspar::parse::binary {


    class buffer_too_small : public stdexcept::logic_error {
    public:
        buffer_too_small(felspar::source_location const &loc =
                           felspar::source_location::current())
        : stdexcept::logic_error{"Buffer is too small", loc} {}
    };


}
