#ifndef AST_HPP
#define AST_HPP

#include<iostream>
#include<memory>
//智能指针管理
#include<string>

#define ARCH 1

class BaseAST{
    public:
    virtual ~BaseAST()=default;
    virtual std::string Dump() const=0;
    virtual std::string GAsm()const=0;
    virtual void print() const{std::cout<<GAsm();}
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
    std::string GAsm()const override{
        return func_def->GAsm();
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
    std::string GAsm()const override{
        std::string code="";
        #if ARCH ==0
        code+="# x86 code:\n";
        #else
        code+="# risc_v 裸机 code:\n";
        #endif
        code+=".globl "+ident+"\n";
        code+=ident+":\n";
        code+=block->GAsm();
        return code;
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
    std::string GAsm()const override{
        return stmt->GAsm();
    }
};
class StmtAST:public BaseAST{
    public:
    int number;
    std::string Dump() const override{
        return "ret i32 "+std::to_string(number);
    }
    std::string GAsm()const override{
        std::string code="";
        #if ARCH ==0
        code+="    movl $"+std::to_string(number)+", %eax\n";
        code+="    ret\n";
        #else
        code+="    li a0, "+std::to_string(number)+"\n";
        code+="    ret\n";
        #endif
        return code;
    }
};
class FuncTypeAST:public BaseAST{
    public:
    std::string functype;
    std::string Dump() const override{
        return "i32";
    }
    std::string GAsm()const override{
        return "";
    }
};

#endif