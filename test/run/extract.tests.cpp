#include <felspar/parse/extract.hpp>
#include <felspar/test.hpp>


namespace {


    auto const suite = felspar::testsuite("extract");


    auto const i = suite.test([](auto check) {
        std::array<std::uint8_t, 1> ar{123};
        std::span<std::uint8_t> sp{ar};
        check(felspar::parse::binary::unchecked_extract<std::uint8_t>(sp))
                == 123;
        check(sp.empty()) == true;
    });


}
