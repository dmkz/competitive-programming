// g++ -O3 -Wall -Wextra -pedantic group-contests.cpp -o group-contests.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"
int main(int argc_, char **argv_) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc_ == 3);
    auto argv = getArguments(argc_, argv_);
    auto fs = fileToString(argv[1]);
    std::string params = argv[2];
    //std::cerr << "group-contest has been called" << std::endl;
    //assert(false);
    stringToFile("contests.txt", fs);
    std::cerr << "saved in file 'contests.txt'" << std::endl;
    while(true)
    {
        std::cerr << "search for a contest" << std::endl;
        std::string id, title, href;
        if (!extractBetween(fs,"data-contestId=\"","\"",id)) {
            std::cerr << "can't find id" << std::endl;
            break;
        }
        if (!extractBetween(fs,"<td>","<br/>",title)) {
            std::cerr << "can't find title" << std::endl;
            break;
        }
        if (!extractBetween(fs,"href=\"", "\"",href)) {
            std::cerr << "can't find href" << std::endl;
            break;
        }
        trimRef(id);
        trimRef(title);
        title = "\"" + title + "\"";
        //std::cerr << "contest '" << title << "'" << std::endl;
        trimRef(href);
        std::cerr << "id = '" << id << "'" << std::endl;
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
        //std::cerr << "res = '" << res << "'" << std::endl;
        printf("%s\n", res.c_str()); //std::cout << res << std::endl;
    }
}