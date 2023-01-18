#include <felspar/parse/insert.hpp>
#include <felspar/test.hpp>


namespace {


    auto const suite = felspar::testsuite("insert");


    auto const i8 = suite.test([](auto check) {
        std::array<std::uint8_t, 1> ar;
        felspar::parse::binary::unchecked_insert(ar, std::uint8_t(123));
        check(ar[0]) == 123;

        std::array<std::byte, 1> ab;
        felspar::parse::binary::unchecked_insert(ab, std::uint8_t(123));
        check(ab[0]) == std::byte(123);

        std::array<char, 1> ac;
        felspar::parse::binary::unchecked_insert(ac, std::uint8_t(123));
        check(ac[0]) == 123;
    });
    auto const i16 = suite.test([](auto check) {
        std::array<std::uint8_t, 2> ar;
        felspar::parse::binary::unchecked_insert(ar, std::uint16_t(0x1234));
        check(ar[0]) == 0x12;
        check(ar[1]) == 0x34;
    });
    auto const i32 = suite.test([](auto check) {
        std::array<std::uint8_t, 4> ar;
        felspar::parse::binary::unchecked_insert(
                ar, std::uint32_t(0x1234'5678));
        check(ar[0]) == 0x12;
        check(ar[1]) == 0x34;
        check(ar[2]) == 0x56;
        check(ar[3]) == 0x78;
    });


    auto const mi8 = suite.test([](auto check) {
        std::vector<std::uint8_t> ar(6);
        std::span<std::uint8_t> sp{ar.data(), ar.size()};
        felspar::parse::binary::insert(sp, std::uint16_t(0x1234));
        check(sp.size()) == 4u;
        check(ar[0]) == 0x12;
        check(ar[1]) == 0x34;
        felspar::parse::binary::insert(sp, std::uint32_t(0x5678'9876));
        check(sp.size()) == 0u;
        check(ar[2]) == 0x56;
        check(ar[3]) == 0x78;
        check(ar[4]) == 0x98;
        check(ar[5]) == 0x76;
    });


}
