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

string findSaveReplace(const string& _input) {
    regex str_expr(".*text=\"(.*)\".*");
    regex replc_expr("text=\"(.*)\"");
    try {
        if (regex_match(_input, str_expr)) {
            smatch m;
            if (regex_search(_input, m, str_expr) == false) {
                return "";
            }
            string en(m[1].str());
            regex str1_expr(en);
            cout << "En=" << en << endl;

            string tag;
            cout << "Enter tag=";
            getline(cin, tag);

            string ru;
            if (dict.find(tag) != dict.end()) {
                ru = dict[tag]["ru"];
                cout << "Exits: " << ru;
            } else {
                cout << "Enter ru=";
                getline(cin, ru);
            }

            string res = regex_replace(_input, replc_expr, "text={i18n."s + tag + ".ru}"s);
            cout << "res=" << res << endl;
            // fix it
            dict[tag];
            dict[tag]["ru"s] = ru;
            dict[tag]["en"s] = en;

            return res;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n'
                  << _input << endl;
    }

    return "";
}

int main(int args, char* argv[]) {
    cout << "Start!" << endl;
    if (args < 2) {
        cout << "Enter argument pls" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    ofstream output(argv[1] + "_new.jsx"s, ios::trunc);
    if (input) {
        string line;
        while (getline(input, line)) {
            if (line.find("text") != std::string::npos) {
                string res = findSaveReplace(line);
                output << res << endl;
                cout << "-------------" << endl;
            } else
                output << line << endl;
        }
    } else {
        cout << "error!" << endl;
    }
    input.close();

    if (args > 2 && argv[2] == "json"s) {
        for (auto elem : dict) {
            cout << "\"" << elem.first << "\":{"
                 << "\"ru\":\"" << elem.second["ru"] << "\",";
            cout << "\"en\":\"" << elem.second["en"] << "\"},";
            cout << endl;
        }
    } else {
        for (auto elem : dict) {
            cout << elem.first << endl;
            cout << "\tru: " << elem.second["ru"] << endl;
            cout << "\ten: " << elem.second["en"] << endl;
            cout << endl;
        }
    }

    cout << endl
         << "End!" << endl;
    return 0;
}
