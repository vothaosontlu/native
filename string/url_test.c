#include "../unit_test.h"
#include "../string.h"

TEST(String, Url_Encode) {
    char *target = "Quán ăn";
    char *result = url_encode(target);
    char *expect = "Qu%c3%a1n+%c4%83n";
    ASSERT_STR(expect, result);
}

TEST(String, Url_Decode) {
    char *target = "Qu%c3%a1n+%c4%83n";
    char *result = url_decode(target);
    char *expect = "Quán ăn";
    ASSERT_STR(expect, result);
}