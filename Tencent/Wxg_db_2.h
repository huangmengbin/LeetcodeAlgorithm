//
// Created by 13524 on 2021/8/27.
//

#ifndef LEETCODE_WXG_DB_2_H
#define LEETCODE_WXG_DB_2_H

#include <bits/stdc++.h>
class Wxg_db_2{

private:

    //  [ ]

    int index = 0;
    string decodeString(const string& s) {
        string result = "";
        int number = 1;
        const int SIZE = s.size();
        while (index < SIZE) {
            const char c = s[index];
            if ('0' <= c && c <= '9') {
                number = 0;
                for (; s[index] != '['; ++index) {
                    number = number * 10 + s[index] - '0';
                }
            } else if (c == '[') {
                index++;
                const string sub = decodeString(s);
                for (int i = 0; i < number; ++i) {
                    result += sub;
                }
            } else if (c == ']') {
                index++;
                break;
            } else {
                index++;
                result.push_back(c);
            }
        }
        return result;
    }



    class AST{
    public:
        int number = 0;
        string str;
        AST* brother;
        AST* son;

        string to_string() {
            string result = "";
            if (number > 0) {
                string tmp = son->to_string();
                for (int i = 0; i < number; ++i) {
                    result.append(tmp);
                }
            }

            result.append(this->str);

            if (brother != nullptr) {
                result.append(brother->to_string());
            }
            return result;
        }
    };

    AST* decodeAST(const string & s) {
        AST* ast = new AST();
        AST* const result = ast;

        const int SIZE = s.size();
        while (index < SIZE) {
            const char c = s[index];
            if ('0' <= c && c <= '9') {
                int number = 0;
                for (; s[index] != '['; ++index) {
                    number = number * 10 + s[index] - '0';
                }
                ast->brother = new AST();
                ast = ast->brother;
                ast->number = number;
            } else if (c == '[') {
                index++;
                ast->son = decodeAST(s);
            } else if (c == ']') {
                index++;
                break;
            } else {
                ast->str.push_back(c);
                index++;
            }
        }
        return result;
    }

    string decodeString2(const string& s) {
        AST* ast = decodeAST(s);
        return ast->to_string();
    }

        public:

    void testDecodeString() {
        cout << decodeString2("a3[m]b");
    }

};
#endif //LEETCODE_WXG_DB_2_H
