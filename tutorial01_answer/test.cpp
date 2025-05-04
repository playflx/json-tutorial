#include <iostream>
#include <string>
#include "leptjson.h"

namespace lept{
//    namespace test{
    static int main_ret = 0;
    static int test_count = 0;
    static int test_pass = 0;

//    }
    #define EXPECT_EQ_BASE(equality, expect, actual, format) \
        do {\
            test_count++;\
            if (equality)\
                test_pass++;\
            else {\
                std::cerr << __FILE__ << ":" << __LINE__ << ": " \
                      << "expect: " << expect << " actual: " << actual << std::endl; \
                main_ret = 1; \
            }\
        } while(0)

    #define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect)==(actual),expect, actual, "%d")

    void test_parse_null(){
        Value v;
        v.type = Type::FALSE;
        auto result = parse(v, "null");
//        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(result));
//        EXPECT_EQ_INT(static_cast<int>(Type::NULL_),static_cast<int>(get_type(v)));

    }

    void test_parse_true() {
        Value v;
        v.type = Type::FALSE;
        auto result = parse(v, "true");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::TRUE), static_cast<int>(get_type(v)));
    }

    void test_parse_false() {
        Value v;
        v.type = Type::TRUE;
        auto result = parse(v, "false");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::FALSE), static_cast<int>(get_type(v)));
    }

    void test_parse_expect_value() {
        Value v;

        v.type = Type::FALSE;
        auto result = parse(v, "");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_EXPECT_VALUE), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(v)));

        v.type = Type::FALSE;
        result = parse(v, " ");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_EXPECT_VALUE), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(v)));
    }

    void test_parse_invalid_value() {
        Value v;
        v.type = Type::FALSE;
        auto result = parse(v, "nul");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_INVALID_VALUE), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(v)));

        v.type = Type::FALSE;
        result = parse(v, "?");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_INVALID_VALUE), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(v)));
    }

    void test_parse_root_not_singular() {
        Value v;
        v.type = Type::FALSE;
        auto result = parse(v, "null x");
        EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_ROOT_NOT_SINGULAR), static_cast<int>(result));
        EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(v)));
    }

    void test_parse() {
        test_parse_null();
        test_parse_true();
        test_parse_false();
        test_parse_expect_value();
        test_parse_invalid_value();
        test_parse_root_not_singular();
    }
};






int main() {
    lept::test_parse();
    std::printf("%d/%d (%3.2f%%) passed\n", lept::test_pass, lept::test_count,
                lept::test_pass * 100.0 / lept::test_count);
    return lept::main_ret;
}
