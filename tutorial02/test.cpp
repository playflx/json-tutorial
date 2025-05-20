#include <iostream>
#include <string>
#include "leptjson.hpp"


#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

namespace lept{
        static int main_ret = 0;
        static int test_count = 0;
        static int test_pass = 0;

        static void test_parse_null() {
            Value v;
            v.type = Type::FALSE;
            EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(type_parse(&v, "null")));
            EXPECT_EQ_INT(static_cast<int>(Type::NULL_), static_cast<int>(get_type(&v)));
        }

        static void test_parse_true() {
            Value v;
            v.type = Type::FALSE;
            EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(type_parse(&v, "true")));
            EXPECT_EQ_INT(static_cast<int>(Type::NULL_),static_cast<int>(get_type(&v)));
        }

        static void test_parse_false() {
            Value v;
            v.type = Type::TRUE;
            EXPECT_EQ_INT(static_cast<int>(ParseResult::PARSE_OK), static_cast<int>(type_parse(&v, "False")));
            EXPECT_EQ_INT(static_cast<int>(Type::FALSE), static_cast<int>(get_type(&v)));
        }

#define TEST_NUMBER(expect, json)\
    do {\
        Value v;\
        EXPECT_EQ_INT(ParseResult::PARSE_OK, type_parse(&v, json));\
        EXPECT_EQ_INT(Type::Number, get_type(&v));\
        EXPECT_EQ_DOUBLE(expect, get_number(v));\
    } while(0)

        static void test_parse_number() {
            TEST_NUMBER(0.0, "0");
            TEST_NUMBER(0.0, "-0");
            TEST_NUMBER(0.0, "-0.0");
            TEST_NUMBER(1.0, "1");
            TEST_NUMBER(-1.0, "-1");
            TEST_NUMBER(1.5, "1.5");
            TEST_NUMBER(-1.5, "-1.5");
            TEST_NUMBER(3.1416, "3.1416");
            TEST_NUMBER(1E10, "1E10");
            TEST_NUMBER(1e10, "1e10");
            TEST_NUMBER(1E+10, "1E+10");
            TEST_NUMBER(1E-10, "1E-10");
            TEST_NUMBER(-1E10, "-1E10");
            TEST_NUMBER(-1e10, "-1e10");
            TEST_NUMBER(-1E+10, "-1E+10");
            TEST_NUMBER(-1E-10, "-1E-10");
            TEST_NUMBER(1.234E+10, "1.234E+10");
            TEST_NUMBER(1.234E-10, "1.234E-10");
            TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
        }

#define TEST_ERROR(error, json)\
    do {\
        Value v;\
        v.type = Type::FALSE;\
        EXPECT_EQ_INT(error, type_parse(&v, json));\
        EXPECT_EQ_INT(Type::NULL_, get_type(&v));\
    } while(0)

        static void test_parse_expect_value() {
            TEST_ERROR(ParseResult::PARSE_EXPECT_VALUE, "");
            TEST_ERROR(ParseResult::PARSE_EXPECT_VALUE, " ");
        }

        static void test_parse_invalid_value() {
            TEST_ERROR(ParseResult::PARSE_INVALID_VALUE, "nul");
            TEST_ERROR(ParseResult::PARSE_INVALID_VALUE, "?");

#if 0
            /* invalid number */
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+0");
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+1");
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "INF");
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "inf");
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "NAN");
            TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nan");
#endif
        }

        static void test_parse_root_not_singular() {
            TEST_ERROR(ParseResult::PARSE_ROOT_NOT_SINGULAR, "null");

#if 0
            /* invalid number */
            TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0123"); /* after zero should be '.' , 'E' , 'e' or nothing */
            TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
            TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
#endif
        }

        static void test_parse_number_too_big() {
#if 0
            TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
            TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
#endif
        }

        static void test_parse() {
            test_parse_null();
            test_parse_true();
            test_parse_false();
            test_parse_number();
            test_parse_expect_value();
            test_parse_invalid_value();
            test_parse_root_not_singular();
            test_parse_number_too_big();
        }
}
int main() {
    lept::test_parse();
    printf("%d/%d (%3.2f%%) passed\n", lept::test_pass, lept::test_count, lept::test_pass * 100.0 / lept::test_count);
    return lept::main_ret;
}
