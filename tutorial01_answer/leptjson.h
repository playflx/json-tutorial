#ifndef LEPTJSON_HPP__
#define LEPTJSON_HPP__

#include<string>

namespace lept{
    enum class Type{
        NULL_,
        FALSE,
        TRUE,
        NUMBER,
        STRING,
        ARRAY,
        OBJECT
    };

    struct Value{
        double n;
        Type type;
    };

    //解析返回码
    enum ParseResult{
        PARSE_OK = 0,
        PARSE_EXPECT_VALUE,
        PARSE_INVALID_VALUE,
        PARSE_ROOT_NOT_SINGULAR
    };

    //主解析函数
    ParseResult parse(Value& value, const std::string& json);

    //获取值类型
    Type get_type(const Value& value);

    //整数类型
    double get_number(const Value& value);
}


#endif //LEPTJSON_HPP
