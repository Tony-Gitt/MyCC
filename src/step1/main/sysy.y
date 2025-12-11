%code requires{
    #include<memory>
    #include<string>
}
%{
#include<iostream>
#include<memory>
#include<string>

int yylex();
void yyerror(std::unique_ptr<std::string> &ast,const char *s);
using namespace std;
%}

%parse-param {std::unique_ptr<std::string> &ast} /* 生成字符串*/
%union{
    std::string *str_val;
    int int_val;
}
/* yylval的定义，lex中的处理就是与此有关*/
/* 同时也要声明 token 种类*/
%token INT RETURN 
%token <str_val> IDENT 
%token <int_val> INT_CONST
%type <str_val> FuncDef FuncType Block Stmt Number 
/* 变量的类型定义*/
%%

// 生成规则，回调函数内容
CompUnit : FuncDef{
    ast=unique_ptr<string>($1);
    /* FuncDef 返回值给 ast*/
};
FuncDef : FuncType IDENT '(' ')' Block{
    auto type=unique_ptr<string>($1);
    auto ident=unique_ptr<string>($2);
    auto block=unique_ptr<string>($5);
    $$=new string(*type+" "+*ident+"()"+*block);
    /* 回调生成字符串，本该生成 ast 节点*/
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

