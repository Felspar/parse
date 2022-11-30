#include <felspar/parse/extract.hpp>
#include <felspar/test.hpp>


namespace {


    auto const suite = felspar::testsuite("extract");


    auto const i8 = suite.test([](auto check) {
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
    auto const i16 = suite.test([](auto check) {
        std::array<std::uint8_t, 2> ar{0x12, 0x34};
        check(felspar::parse::binary::unchecked_extract<std::uint16_t>(ar))
                == 0x1234;
    });


    auto const mi8 = suite.test([](auto check) {
        std::vector<std::uint8_t> ar{95, 96};
        std::span sp{ar};
        check(felspar::parse::binary::extract<std::uint8_t>(sp)) == 95;
        check(felspar::parse::binary::extract<std::uint8_t>(sp)) == 96;
        check(sp.empty()) == true;
    });


}
