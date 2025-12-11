#ifndef AST_HPP
#define AST_HPP

#include<iostream>
#include<memory>
//智能指针管理
#include<string>

class BaseAST{
    public:
    virtual ~BaseAST()=default;
    virtual std::string Dump() const=0;
    virtual void print() const{std::cout<<Dump();}
    // 输出内容
}; 

class CompUnitAST: public BaseAST{
    public:
    std::unique_ptr<BaseAST> func_def;
    std::string Dump() const override{
        std::string ir="llvm ir:\n";
        ir+=func_def->Dump();
        return ir;
    }
};

class FuncDefAST: public BaseAST{
    public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;
    std::string Dump() const override{
        std::string ir="";
        ir+="define "+func_type->Dump()+" @"+ident+"(){\n";
        ir+="entry:\n";
        ir+=block->Dump()+"\n";
        ir+="}\n";
        return ir;
    }
};
//其他终结类型相同
class BlockAST:public BaseAST{
    public:
    std::unique_ptr<BaseAST> stmt;
    std::string Dump() const override{
        std::string ir=" ";
        ir+=stmt->Dump();
        return ir;
    }
};
class StmtAST:public BaseAST{
    public:
    int number;
    std::string Dump() const override{
        return "ret i32 "+std::to_string(number);
    }
};
class FuncTypeAST:public BaseAST{
    public:
    std::string functype;
    std::string Dump() const override{
        return "i32";
    }
};

#endif