#ifndef LEPTJSON_HPP__
#define LEPTJSON_HPP__

#include <string>
namespace lept{
    //使用enum class定义强类型枚举
    enum class Type{
        NULL_,
        FALSE,
        TRUE,
        Number,
        String,
        Array,
        Object
    };

    //JSON值的结构体
    struct Value{
        Type type;
        double n;
    };

    //解析错误码
    enum ParseResult{
        PARSE_OK=0,
        PARSE_INVALID_VALUE,
        PARSE_EXPECT_VALUE,
        PARSE_ROOT_NOT_SINGULAR,
        PARSE_NUMBER_TOO_BIG
    };

    //解析JSON字符串
    int type_parse(Value* v,const std::string& json);

    //获取JSON值的类型
    Type get_type(const Value* v);

    //number
    double get_number(const Value& v);
}
#endif