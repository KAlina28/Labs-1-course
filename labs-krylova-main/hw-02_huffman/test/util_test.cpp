#include "doctest.h"
#include "util.h"

TEST_CASE("converter tests")
{
    SUBCASE("String's length is less than 8") {
        CHECK_EQ(converter("0101"), 'P');
        CHECK_EQ(converter("011011"), 'l');
        CHECK_EQ(converter("010"), '@');
    }
    SUBCASE("String's length is equal to 8") {
        CHECK_EQ(converter("00101010"), '*');
        CHECK_EQ(converter("01101101"), 'm');
        CHECK_EQ(converter("01111011"), '{');
    }
}