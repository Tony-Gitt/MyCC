%code requires{
    #include<memory>
    #include<string>
    #include"ast.hpp"
}
%{
#include "ast.hpp"    
#include<iostream>
#include<memory>
#include<string>


int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast,const char *s);
using namespace std;
%}

%parse-param {std::unique_ptr<std::string> &ast} /* 生成字符串*/
%union{
    std::string *str_val;
    int int_val;
    BaseAST *ast_val;
}
/* yylval的定义，lex中的处理就是与此有关*/
/* 同时也要声明 token 种类*/
%token INT RETURN 
%token <str_val> IDENT 
%token <int_val> INT_CONST
%type <ast_val> FuncDef FuncType Block Stmt 
%type <int_val> Number 
/* 变量的类型定义*/
%%

// 生成规则，回调函数内容
CompUnit : FuncDef{
    auto comp_unit=make_unique<CompUnitAST>();
    comp_unit->func_def=unique_ptr<BaseAST>($1);
    ast=move(comp_unit);
};
FuncDef : FuncType IDENT '(' ')' Block{
    auto ast=new FuncDefAST();
    ast->func_type=unique_ptr<BaseAST>($1);
    ast->ident=*unique_ptr<string>($2);
    ast->block=unique_ptr<BaseAST>($5);
    $$=ast;
};
FuncType : INT{
    $$=new string("int");
};
Block : '{' Stmt '}'{
    auto stmt=unique_ptr<string>($2);
    $$=new string("{"+*stmt+"}");
};
Stmt : RETURN Number ';'{
    auto number=unique_ptr<string>($2);
    $$=new string("return "+*number+";");
};
Number : INT_CONST{
    $$=new string(to_string($1));
};
/* 基本定义了语法的处理逻辑。利用c语言处理*/
%%

void yyerror(unique_ptr<string> &ast,const char *s){
    cerr<<"error: "<<s<<endl;
}

