#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <string>

namespace lept{
    //使用enum class定义强类型枚举
    enum class Type{
        Null,
        False,
        True,
        Number,
        String,
        Array,
        Object
    };

    //JSON值的结构体
    struct Value{
        Type type;

        //构造函数
        Value():type(Type::Null){}
        explicit Value(Type t):type(t){}
    };

    //解析错误码
    enum ParseError{
        ParseOk=0,
        ParseExpectValue,
        ParseInvalidValue,
        ParseRootNotSingular
    };

    //解析JSON字符串
    int type_parse(Value* v,const std::string& json);

    //获取JSON值的类型
    Type get_type(const Value* v);
}
#endif