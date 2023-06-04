#include <felspar/parse/insert.be.hpp>
#include <felspar/parse/insert.le.hpp>
#include <felspar/parse/insert.native.hpp>
#include <felspar/test.hpp>

#include <vector>


namespace {


    auto const suite = felspar::testsuite("insert");


    auto const i8 = suite.test([](auto check) {
        std::array<std::uint8_t, 1> ar1, ar2, ar3;
        felspar::parse::binary::native::unchecked_insert(
                ar1, std::uint8_t(123));
        check(ar1[0]) == 123;
        felspar::parse::binary::be::unchecked_insert(ar2, std::uint8_t(123));
        check(ar2[0]) == 123;
        felspar::parse::binary::le::unchecked_insert(ar3, std::uint8_t(123));
        check(ar3[0]) == 123;

        std::array<std::byte, 1> ab1, ab2, ab3;
        felspar::parse::binary::native::unchecked_insert(
                ab1, std::uint8_t(123));
        check(ab1[0]) == std::byte(123);
        felspar::parse::binary::be::unchecked_insert(ab2, std::uint8_t(123));
        check(ab2[0]) == std::byte(123);
        felspar::parse::binary::le::unchecked_insert(ab3, std::uint8_t(123));
        check(ab3[0]) == std::byte(123);

        std::array<char, 1> ac1, ac2, ac3;
        felspar::parse::binary::native::unchecked_insert(
                ac1, std::uint8_t(123));
        check(ac1[0]) == 123;
        felspar::parse::binary::be::unchecked_insert(ac2, std::uint8_t(123));
        check(ac2[0]) == 123;
        felspar::parse::binary::le::unchecked_insert(ac3, std::uint8_t(123));
        check(ac3[0]) == 123;
    });
    auto const i16 = suite.test([](auto check) {
        std::array<std::uint8_t, 2> ar1, ar2, ar3;
        felspar::parse::binary::native::unchecked_insert(
                ar1, std::uint16_t(0x1234));
        check(ar1[1]) == 0x12;
        check(ar1[0]) == 0x34;
        felspar::parse::binary::be::unchecked_insert(
                ar2, std::uint16_t(0x1234));
        check(ar2[0]) == 0x12;
        check(ar2[1]) == 0x34;
        felspar::parse::binary::le::unchecked_insert(
                ar3, std::uint16_t(0x1234));
        check(ar3[1]) == 0x12;
        check(ar3[0]) == 0x34;
    });
    auto const i32 = suite.test([](auto check) {
        std::array<std::uint8_t, 4> ar1, ar2, ar3;
        felspar::parse::binary::native::unchecked_insert(
                ar1, std::uint32_t(0x1234'5678));
        check(ar1[3]) == 0x12;
        check(ar1[2]) == 0x34;
        check(ar1[1]) == 0x56;
        check(ar1[0]) == 0x78;
        felspar::parse::binary::be::unchecked_insert(
                ar2, std::uint32_t(0x1234'5678));
        check(ar2[0]) == 0x12;
        check(ar2[1]) == 0x34;
        check(ar2[2]) == 0x56;
        check(ar2[3]) == 0x78;
        felspar::parse::binary::le::unchecked_insert(
                ar3, std::uint32_t(0x1234'5678));
        check(ar3[3]) == 0x12;
        check(ar3[2]) == 0x34;
        check(ar3[1]) == 0x56;
        check(ar3[0]) == 0x78;
    });
    auto const i64 = suite.test([](auto check) {
        std::array<std::uint8_t, 8> ar1, ar2, ar3;
        felspar::parse::binary::native::unchecked_insert(
                ar1, std::uint64_t(0x1234'5678'9876'5432));
        check(ar1[7]) == 0x12;
        check(ar1[6]) == 0x34;
        check(ar1[5]) == 0x56;
        check(ar1[4]) == 0x78;
        check(ar1[3]) == 0x98;
        check(ar1[2]) == 0x76;
        check(ar1[1]) == 0x54;
        check(ar1[0]) == 0x32;
        felspar::parse::binary::be::unchecked_insert(
                ar2, std::uint64_t(0x1234'5678'9876'5432));
        check(ar2[0]) == 0x12;
        check(ar2[1]) == 0x34;
        check(ar2[2]) == 0x56;
        check(ar2[3]) == 0x78;
        check(ar2[4]) == 0x98;
        check(ar2[5]) == 0x76;
        check(ar2[6]) == 0x54;
        check(ar2[7]) == 0x32;
        felspar::parse::binary::le::unchecked_insert(
                ar3, std::uint64_t(0x1234'5678'9876'5432));
        check(ar3[7]) == 0x12;
        check(ar3[6]) == 0x34;
        check(ar3[5]) == 0x56;
        check(ar3[4]) == 0x78;
        check(ar3[3]) == 0x98;
        check(ar3[2]) == 0x76;
        check(ar3[1]) == 0x54;
        check(ar3[0]) == 0x32;
    });


    auto const mi8 = suite.test([](auto check) {
        {
            std::vector<std::byte> ar(6);
            std::span<std::byte> sp{ar.data(), ar.size()};
            felspar::parse::binary::native::insert(sp, std::uint16_t(0x1234));
            check(sp.size()) == 4u;
            check(ar[0]) == std::byte(0x34);
            check(ar[1]) == std::byte(0x12);
            felspar::parse::binary::native::insert(
                    sp, std::uint32_t(0x5678'9876));
            check(sp.size()) == 0u;
            check(ar[2]) == std::byte(0x76);
            check(ar[3]) == std::byte(0x98);
            check(ar[4]) == std::byte(0x78);
            check(ar[5]) == std::byte(0x56);
        }
        {
            std::vector<std::byte> ar(6);
            std::span<std::byte> sp{ar.data(), ar.size()};
            felspar::parse::binary::be::insert(sp, std::uint16_t(0x1234));
            check(sp.size()) == 4u;
            check(ar[0]) == std::byte(0x12);
            check(ar[1]) == std::byte(0x34);
            felspar::parse::binary::be::insert(sp, std::uint32_t(0x5678'9876));
            check(sp.size()) == 0u;
            check(ar[2]) == std::byte(0x56);
            check(ar[3]) == std::byte(0x78);
            check(ar[4]) == std::byte(0x98);
            check(ar[5]) == std::byte(0x76);
        }
        {
            std::vector<std::byte> ar(6);
            std::span<std::byte> sp{ar.data(), ar.size()};
            felspar::parse::binary::le::insert(sp, std::uint16_t(0x1234));
            check(sp.size()) == 4u;
            check(ar[1]) == std::byte(0x12);
            check(ar[0]) == std::byte(0x34);
            felspar::parse::binary::le::insert(sp, std::uint32_t(0x5678'9876));
            check(sp.size()) == 0u;
            check(ar[5]) == std::byte(0x56);
            check(ar[4]) == std::byte(0x78);
            check(ar[3]) == std::byte(0x98);
            check(ar[2]) == std::byte(0x76);
        }
    });


}
