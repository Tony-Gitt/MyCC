#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
extern FILE *yyin;
extern int yyparse(unique_ptr<string> &result);

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
    unique_ptr<string> result;
    int ret = yyparse(result);
    
    if (ret != 0) {
        cerr << "Parse failed!" << endl;
        fclose(yyin);
        return ret;
    }

    // 输出解析得到的字符串结果
    if (result) {
        cout << *result << endl;
    } else {
        cout << "No output" << endl;
    }

    // 清理
    fclose(yyin);
    return 0;
}