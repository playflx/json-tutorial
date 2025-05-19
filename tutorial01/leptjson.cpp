#include "leptjson.h"
#include <cassert>  /* assert() */
#include <cctype>  /* NULL */
#include <bitset>

namespace lept{
    struct Context{
        const char* json;
    };

#define EXPECT(c,ch) do {assert(*c.json==(ch));c.json++;}while(0)

    static void parse_whitespace(Context& c){
        const char* p = c.json;
        while(*p ==' '||*p=='\t'||*p=='\n'||*p=='\r')
            ++p;
        c.json=p;
    }

    static ParseResult parse_true(Context& c, Value& v){
        EXPECT(c,'t');
        if(c.json[0]!='r'||c.json[1]!='u'||c.json[2]!='e'){
            return ParseResult::PARSE_INVALID_VALUE;
        }
        c.json+=3;
        v.type=Type::TRUE;
        return ParseResult::PARSE_OK;
    }

    static ParseResult parse_false(Context& c, Value& v){
        EXPECT(c, 'f');
        if(c.json[0]!='a'||c.json[1]!='l'||c.json[2]!='s'||c.json[3]!='e'){
            return ParseResult::PARSE_INVALID_VALUE;
        }
        c.json+=4;
        v.type=Type::FALSE;
        return ParseResult::PARSE_OK;
    }

    static ParseResult parse_null(Context& c, Value& v){
        EXPECT(c,'n');
        if(c.json[0]!='u'||c.json[1]!='l'||c.json[2]!='l'){
            return ParseResult::PARSE_INVALID_VALUE;
        }
        c.json+=3;
        v.type=Type::NULL_;
        return ParseResult::PARSE_OK;
    }

    static ParseResult parse_value(Context& c, Value& v){
        switch (*c.json) {
            case 't': return parse_true(c,v);
            case 'f': return parse_false(c,v);
            case 'n': return parse_null(c,v);
            case '\0': return ParseResult::PARSE_EXPECT_VALUE;
            default: return ParseResult::PARSE_INVALID_VALUE;
        }
    }


    static int lept_parse_number(lept_context* c, lept_value* v) {
        char* end;
        /* \TODO validate number */
        v->n = strtod(c->json, &end);
        if (c->json == end)
            return LEPT_PARSE_INVALID_VALUE;
        c->json = end;
        v->type = LEPT_NUMBER;
        return LEPT_PARSE_OK;
    }
    static ParseResult parse_number(Context& c,Value& v){
        std::bitset<8> binary()
    }

    ParseResult parse(Value& v, const std::string& json){
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


