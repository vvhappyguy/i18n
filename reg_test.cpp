#include <iostream>
#include <regex>
#include <string>
using namespace std;

pair<string, string> findSaveReplace(const string& _input) {
    regex str_expr("text=\"(.*)\"");

    if (regex_match(_input, str_expr)) {
        cout << "string:object => matched\n";
        smatch m;
        regex_search(_input, m, str_expr);
        regex str1_expr(m[1].str());

        string tmp;
        cout << "Enter tmp=";
        cin >> tmp;

        string res = regex_replace(_input, str1_expr, tmp);
        cout << res;
        return {res, tmp};
    }
    return {""s, ""s};
}

int main() {
    string str;
    cin >> str;
    findSaveReplace(str);
    return 0;
}
