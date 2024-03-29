#include <felspar/parse/extract.be.hpp>
#include <felspar/parse/extract.le.hpp>
#include <felspar/parse/extract.native.hpp>
#include <felspar/test.hpp>

#include <array>
#include <vector>


namespace {


    auto const suite = felspar::testsuite("extract");


    auto const i8 = suite.test([](auto check) {
        std::array<std::uint8_t, 1> ar{123};
        check(felspar::parse::binary::native::unchecked_extract<std::uint8_t>(
                ar))
                == 123;
        check(felspar::parse::binary::be::unchecked_extract<std::uint8_t>(ar))
                == 123;
        check(felspar::parse::binary::le::unchecked_extract<std::uint8_t>(ar))
                == 123;

        std::array<std::byte, 1> ab{std::byte{124}};
        check(felspar::parse::binary::native::unchecked_extract<std::uint8_t>(
                ab))
                == 124;
        check(felspar::parse::binary::be::unchecked_extract<std::uint8_t>(ab))
                == 124;
        check(felspar::parse::binary::le::unchecked_extract<std::uint8_t>(ab))
                == 124;

        std::array<char, 1> ac{125};
        check(felspar::parse::binary::native::unchecked_extract<std::uint8_t>(
                ac))
                == 125;
        check(felspar::parse::binary::be::unchecked_extract<std::uint8_t>(ac))
                == 125;
        check(felspar::parse::binary::le::unchecked_extract<std::uint8_t>(ac))
                == 125;
    });
    auto const i16 = suite.test([](auto check) {
        std::array<std::uint8_t, 2> ar{0x12, 0x34};
        check(felspar::parse::binary::native::unchecked_extract<std::uint16_t>(
                ar))
                == 0x3412;
        check(felspar::parse::binary::be::unchecked_extract<std::uint16_t>(ar))
                == 0x1234;
        check(felspar::parse::binary::le::unchecked_extract<std::uint16_t>(ar))
                == 0x3412;
    });
    auto const i32 = suite.test([](auto check) {
        std::array<std::uint8_t, 4> ar{0x12, 0x34, 0x56, 0x78};
        check(felspar::parse::binary::native::unchecked_extract<std::uint32_t>(
                ar))
                == 0x7856'3412UL;
        check(felspar::parse::binary::be::unchecked_extract<std::uint32_t>(ar))
                == 0x1234'5678UL;
        check(felspar::parse::binary::le::unchecked_extract<std::uint32_t>(ar))
                == 0x7856'3412UL;
    });
    auto const i64 = suite.test([](auto check) {
        std::array<std::uint8_t, 8> ar{0x12, 0x34, 0x56, 0x78,
                                       0x98, 0x76, 0x54, 0x32};
        check(felspar::parse::binary::native::unchecked_extract<std::uint64_t>(
                ar))
                == 0x3254'7698'7856'3412UL;
        check(felspar::parse::binary::be::unchecked_extract<std::uint64_t>(ar))
                == 0x1234'5678'9876'5432UL;
        check(felspar::parse::binary::le::unchecked_extract<std::uint64_t>(ar))
                == 0x3254'7698'7856'3412UL;
    });


    auto const mi8 = suite.test([](auto check) {
        std::vector<std::byte> ar{std::byte{95}, std::byte{96}};
        {
            std::span<std::byte const> sp{ar.data(), ar.size()};
            check(felspar::parse::binary::native::extract<std::uint8_t>(sp))
                    == 95;
            check(felspar::parse::binary::native::extract<std::uint8_t>(sp))
                    == 96;
            check(sp.empty()) == true;
        }
        {
            std::span<std::byte const> sp{ar.data(), ar.size()};
            check(felspar::parse::binary::be::extract<std::uint8_t>(sp)) == 95;
            check(felspar::parse::binary::be::extract<std::uint8_t>(sp)) == 96;
            check(sp.empty()) == true;
        }
        {
            std::span<std::byte const> sp{ar.data(), ar.size()};
            check(felspar::parse::binary::le::extract<std::uint8_t>(sp)) == 95;
            check(felspar::parse::binary::le::extract<std::uint8_t>(sp)) == 96;
            check(sp.empty()) == true;
        }
    });


}
