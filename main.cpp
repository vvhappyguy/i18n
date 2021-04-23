#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

map<string, map<string, string>> dict;

/*
"i18n": {
    "tagsWasNotFound": {
      "ru": "Теги не были обнаружены...",
      "en": "Tags was not found..."
    }
  }
*/

pair<string, string> findSaveReplace(const string& _input) {
    regex str_expr(".*text=\"(.*)\".*");

    if (regex_match(_input, str_expr)) {
        smatch m;
        regex_search(_input, m, str_expr);
        regex str1_expr(m[1].str());
        cout << "Matched: " << m[1].str() << endl;

        string tmp;
        cout << "Enter tmp=";
        getline(cin, tmp);

        string res = regex_replace(_input, str1_expr, tmp);
        //cout << res;
        return {res, m[1].str()};
    }
    return {""s, ""s};
}

int main(int args, char* argv[]) {
    cout << "Start!" << endl;
    if (args < 2) {
        cout << "Enter argument pls" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[1] + "_new.txt"s, ios::trunc);
    if (input) {
        string line;
        while (getline(input, line)) {
            pair<string, string> res = findSaveReplace(line);
            if (res.first != "") {
                cout << res.second << endl;
                output << res.first << endl;
                cout << "-------------" << endl;
            } else {
                output << line << endl;
            }
        }
    } else {
        cout << "error!" << endl;
    }
    input.close();
    cout << endl
         << "End!" << endl;
    return 0;
}
