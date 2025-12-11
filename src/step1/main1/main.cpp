#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"

using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &result);

int main(int argc, const char *argv[]) {
    // 简化命令行处理：只需要输入文件
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    const char* input_file = argv[1];

    // 打开输入文件
    yyin = fopen(input_file, "r");
    if (!yyin) {
        cerr << "Error: Cannot open file '" << input_file << "'" << endl;
        return 1;
    }

    // 调用 parser 函数
    unique_ptr<BaseAST> ast;
    int ret = yyparse(ast);
    
    assert(!ret);
    ast->Dump();
    cout<<endl;

    // 清理
    fclose(yyin);
    return 0;
}