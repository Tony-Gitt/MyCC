#ifndef AST_HPP
#define AST_HPP

#include<iostream>
#include<memory>
//智能指针管理
#include<string>
#include<vector>

class BaseAST{
    public:
    virtual ~BaseAST()=default;
    virtual void Dump() const=0;
    // 输出内容
}; 

class CompUnitAST: public BaseAST{
    public:
    std::unique_ptr<BaseAST> func_def;
    void Dump() const override{
        std::cout<<"ComUnitAST{ ";
        func_def->Dump();
        std::cout<<"}";
        // 递归输出
    }
};

class FuncDefAST: public BaseAST{
    public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;
    void Dump() const override{
        std::cout<<"FuncDefAST{ ";
        // 标志从属关系
        func_type->Dump();
        std::cout<<" + "<<ident<<" + ";
        block->Dump();
        std::cout<<"}";
    }
};
//其他终结类型相同
class BlockAST:public BaseAST{
    public:
    std::unique_ptr<BaseAST> stmt;
    void Dump() const override{
        std::cout<<"BlockAST{ ";
        stmt->Dump();
        std::cout<<"}";
    }
};
class StmtAST:public BaseAST{
    public:
    int number;
    void Dump() const override{
        std::cout<<"StmtAST{ ";
        std::cout<<number<<" ";
        std::cout<<"}";
    }
};
class FuncTypeAST:public BaseAST{
    public:
    std::string functype;
    void Dump() const override{
        std::cout<<functype;
    }
};

#endif