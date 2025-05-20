#include "leptjson.hpp"
#include <cassert>  /* assert() */
#include <cctype>  /* NULL */
#include <limits>

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define EXPECT(c,ch) do {assert(*c.json==(ch));c.json++;}while(0)
namespace lept{
    struct Context{
        const char* json;
    };



    static void parse_whitespace(Context& c){
        const char* p = c.json;
        while(*p ==' '||*p=='\t'||*p=='\n'||*p=='\r')
            ++p;
        c.json=p;
    }

    static ParseResult parse_literal(Context& c, Value& v, const char* literal, Type type){
        EXPECT(c, literal[0]);
        size_t i;
        for(i=0;literal[i+1];++i){
            if(c.json[i]!=literal[i+1]){
                return ParseResult::PARSE_INVALID_VALUE;
            }
        }
        c.json+=i;
        v.type=type;
        return ParseResult::PARSE_OK;
    }
//    static ParseResult parse_true(Context& c, Value& v){
//        EXPECT(c,'t');
//        if(c.json[0]!='r'||c.json[1]!='u'||c.json[2]!='e'){
//            return ParseResult::PARSE_INVALID_VALUE;
//        }
//        c.json+=3;
//        v.type=Type::TRUE;
//        return ParseResult::PARSE_OK;
//    }
//
//    static ParseResult parse_false(Context& c, Value& v){
//        EXPECT(c, 'f');
//        if(c.json[0]!='a'||c.json[1]!='l'||c.json[2]!='s'||c.json[3]!='e'){
//            return ParseResult::PARSE_INVALID_VALUE;
//        }
//        c.json+=4;
//        v.type=Type::FALSE;
//        return ParseResult::PARSE_OK;
//    }
//
//    static ParseResult parse_null(Context& c, Value& v){
//        EXPECT(c,'n');
//        if(c.json[0]!='u'||c.json[1]!='l'||c.json[2]!='l'){
//            return ParseResult::PARSE_INVALID_VALUE;
//        }
//        c.json+=3;
//        v.type=Type::NULL_;
//        return ParseResult::PARSE_OK;
//    }

    static ParseResult parse_value(Context& c, Value& v){
        switch (*c.json) {
            case 't': return parse_literal(c,v,"true",Type::TRUE);
            case 'f': return parse_literal(c,v,"false",Type::FALSE);
            case 'n': return parse_literal(c,v,"null",Type::NULL_);
//            case 't': return parse_true(c,v);
//            case 'f': return parse_false(c,v);
//            case 'n': return parse_null(c,v);
            case '\0': return ParseResult::PARSE_EXPECT_VALUE;
            default: return ParseResult::PARSE_INVALID_VALUE;
        }
    }

    static ParseResult parse_number(Context& c, Value& v){
        const char* p = c.json; // 获取当前解析位置
        if(*p=='-')p++; //负号检测
        if(*p=='0')p++;// 0检测
        else{
            if(!ISDIGIT1TO9(*p))//判断是否是1-9 数字
                return ParseResult::PARSE_INVALID_VALUE;
            for(p++; ISDIGIT(*p);++p);//跳过后续数字
        }
        if(*p=='.'){//检查小数点
            p++;
            if(!ISDIGIT(*p))//小数点后必须有数字
                return ParseResult::PARSE_INVALID_VALUE;
            for(p++; ISDIGIT(*p);++p);
        }
        if(*p=='e'||*p=='E'){//检查指数部分
            p++;
            if(*p=='+'||*p=='-')p++;
            if(!ISDIGIT(*p))
                return ParseResult::PARSE_INVALID_VALUE;//指数后必须有数字
            for(p++; ISDIGIT(*p);p++);

        }
        //清除errno
        errno = 0;
        v.n = std::strtod(c.json, nullptr);//转换为double
        if(errno == ERANGE &&(v.n == std::numeric_limits<double>::infinity()||v.n==-std::numeric_limits<double>::infinity()))
            return ParseResult::PARSE_NUMBER_TOO_BIG;
        v.type = Type::Number;
        c.json = p;
        return ParseResult::PARSE_OK;

    }

    ParseResult type_parse(Value& v, const std::string& json){
        Context c;
        c.json=json.c_str();
        v.type = Type::NULL_;
        parse_whitespace(c);
        auto result = parse_value(c,v);
        if(result==ParseResult::PARSE_OK){
            parse_whitespace(c);
            if(*c.json!='\0'){
                result = ParseResult::PARSE_ROOT_NOT_SINGULAR;
            }
        }
        return result;
    }

    Type get_type(const Value& v){
        return v.type;
    }
    double get_number(const Value& v){
        return v.n;
    }
}


