// g++ -O3 -Wall -Wextra -pedantic group-contests.cpp -o group-contests.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"
int main(int argc, char **argv) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc == 3);
    auto fs = fileToString(argv[1]);
    std::string params = argv[2];
    while(true)
    {
        std::string id, title, href;
        if (!extractBetween(fs,"data-contestId=\"","\"",id))
            break;
        if (!extractBetween(fs,"<td>","<br/>",title))
            break;
        if (!extractBetween(fs,"href=\"", "\"",href))
            break;
        trimRef(id);
        trimRef(title);
        title = "\"" + title + "\"";
        trimRef(href);
        std::string res;
        for (char c : params) {
            res += ' ';
            if (c == 'i') res += id;
            else if (c == 'h') res += href;
            else if (c == 't') res += title;
            else {
                std::cout << "Unknown param " << c << std::endl;
                return 1;
            }
        }
        trimRef(res);
        std::cout << res << std::endl;
    }
}