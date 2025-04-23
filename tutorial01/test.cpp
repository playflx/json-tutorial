#include <iostream>
#include <string>
#include "leptjson.h"

namespace lept_test{
    //测试统计信息
    static int main_ret = 0;
    static int test_count = 0;
    static int test_pass = 0;

    //基础断言函数
    template <typename T>
    void expect_eq_base(bool equality, const T& expect, const T& actual, const std::string& message){
        test_count++;
        if(equality){
            test_pass++;
        }else{
            std::cerr<<__FILE__<<":"<<__LINE__<<":"
                     <<"except: "<<expect<<" actual"<<actual
                     <<" ("<<message<<")"<<std::endl;
            main_ret=1;
        }
    }

    //针对整数断言
    inline void expect_eq_int(int expect, int actual){
        expect_eq_base(expect==actual,expect,actual,"integer comparison");
    }

    //解析测试null
    void test_parse_null(){
        lept::Value v;
        v.type=lept::Type::False;
        expect_eq_int(static_cast<int>(lept::ParseError::ParseOk), lept::type_parse(&v,"null"));
        expect_eq_int(static_cast<int>(lept::Type::Null), static_cast<int>(lept::get_type(&v)));
    }

    //解析测试True
    void test_parse_true(){
        lept::Value v(lept::Type::True);
        expect_eq_int(static_cast<int>(lept::ParseError::ParseOk), lept::type_parse(&v,"true"));
        expect_eq_int(static_cast<int>(lept::Type::True), static_cast<int>(lept::get_type(&v)));
    }

    //解析测试False
    void test_parse_false(){
        lept::Value v(lept::Type::False);
        expect_eq_int(static_cast<int>(lept::ParseError::ParseOk), lept::type_parse(&v,"false"));
        expect_eq_int(static_cast<int>(lept::Type::False), static_cast<int>(lept::get_type(&v)));
    }

    //解析测试空值
    void test_parse_except_value(){
        lept::Value v(lept::Type::False);
        expect_eq_int(static_cast<int>(lept::ParseError::ParseExpectValue), lept::type_parse(&v,""));
        expect_eq_int(static_cast<int>(lept::Type::Null),static_cast<int>(lept::get_type(&v)));
    }

    //解析测试是否为无效值
    void test_parse_invalid_value(){
        lept::Value v(lept::Type::False);
        expect_eq_int(static_cast<int>(lept::ParseError::ParseInvalidValue), lept::type_parse(&v,"nul"));
        expect_eq_int(static_cast<int>(lept::Type::Null),static_cast<int>(lept::get_type(&v)));
    }

    //测试解析是否为单一值
    void test_parse_root_not_singular(){
        lept::Value v(lept::Type::False);
        expect_eq_int(static_cast<int>(lept::ParseError::ParseRootNotSingular), lept::type_parse(&v,"null x"));
        expect_eq_int(static_cast<int>(lept::Type::Null),static_cast<int>(lept::get_type(&v)));
    }

    //运行所有测试
    void test_run(){
        test_parse_null();
        test_parse_true();
        test_parse_false();
        test_parse_except_value();
        test_parse_invalid_value();
        test_parse_root_not_singular();
    }
}

int main() {
    lept_test::test_run();
    std::cout<<lept_test::test_pass<<"/"<<lept_test::test_count
             <<" ("<<(lept_test::test_pass * 100.0 / lept_test::test_count)
             <<"%) passed" << std::endl;
    return lept_test::main_ret;
}
