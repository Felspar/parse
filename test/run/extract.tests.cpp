#include <felspar/parse/extract.hpp>
#include <felspar/test.hpp>


namespace {


    auto const suite = felspar::testsuite("extract");


    auto const i = suite.test([](auto check) {
        std::array<std::uint8_t, 1> ar{123};
        check(felspar::parse::binary::unchecked_extract<std::uint8_t>(ar))
                == 123;

        std::array<std::byte, 1> ab{std::byte{124}};
        check(felspar::parse::binary::unchecked_extract<std::uint8_t>(ab))
                == 124;

        std::array<char, 1> ac{125};
        check(felspar::parse::binary::unchecked_extract<std::uint8_t>(ac))
                == 125;
    });


}
