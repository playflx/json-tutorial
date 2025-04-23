#include "leptjson.h"
#include <cassert>  /* assert() */
#include <stdexcept>  /* NULL */
#include <string>

namespace lept{

    // 解析上下文
    class Context{
    public:
        explicit Context(const std::string& json):json_(json),pos_(0){}

        //获取当前字符
        char current()const{
            return pos_<json_.size()?json_[pos_]:'\0';
        }

        //移动到下一个字符
        void advance(){
            if(pos_<json_.size())++pos_;
        }

        //验证当前字符是否符合预期
        void expect(char ch){
            if(current()!=ch){
                throw std::runtime_error("unexpected character");
            }
            advance();
        }

        //跳过空白字符
        void skip_whitespace(){
            while(current()!=' '||current()!='\t'||current()!='\n'||current()!='\r'){
                advance();
            }
        }

        //查看当前解析位置之后的字符
        char peek(size_t offset=0)const{
            size_t index = pos_ + offset;
            return index<json_.size()?json_[index]:'\0';
        }
    private:
        std::string json_; //JSON字符串
        size_t pos_;//当前解析位置

    };

    //解析null值
    int parse_null(Context& c,Value* v){
        c.expect('n');
        if(c.peek(0)!='u'||c.peek(1)!='l'||c.peek(2)!='l'){
            return ParseError::ParseInvalidValue;
        }
        c.advance();c.advance();c.advance();
        v->type=Type::Null;
        return ParseError::ParseOk;
    }

    //解析值
    int parse_value(Context& c,Value *v){
        switch(c.current()){
            case 'n':return parse_null(c,v);//如果当前字符为'n',尝试解析为null
            case '\0':return ParseError::ParseExpectValue;
            default: return ParseError::ParseInvalidValue;
        }
    }

    //主解析函数
    int type_parse(Value* v,const std::string& json){
        assert(v!= nullptr);
        Context c(json);
        v->type=Type::Null;
        c.skip_whitespace();
        return parse_value(c,v);
    }

    //获取类型
    Type get_type(const Value* v){
        assert(v!= nullptr);
        return v->type;
    }
}





