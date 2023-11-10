// g++ -O3 -Wall -Wextra -pedantic contest-status.cpp -o contest-status.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"

const bool debug = false;

#include "submission.hpp"

int main(int argc_, char **argv_) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc_ == 3);
    auto argv = getArguments(argc_, argv_);
    std::string fs = fileToString(argv[1]);
    std::string link = argv[2];
    Cache cacheObject(link, true);
    auto &cache = cacheObject.cache;
    int count = 0;
    std::vector<Submission> currPage;
    for(bool lastRowDetected{}; !lastRowDetected; )
    {
        Submission sub;
        bool ok = sub.readFromPage(fs, lastRowDetected);
        count += ok;
        if (!ok) break;
        currPage.push_back(sub);
    }
    std::sort(all(currPage),std::greater<>());
    std::cerr << "OK, " << count
              << " submissions have been readed. "
              << "Link = '" << link << "'" << std::endl;
    
    assert(std::is_sorted(all(cache),std::greater<>()));
    assert(std::is_sorted(all(currPage),std::greater<>()));
    int last = isz(cache);
    for (const auto &s : currPage) {
        if(!std::binary_search(cache.begin(),
                               cache.begin()+last,
                               s, std::greater<>()))
        {
            cache.push_back(s);
        }
    }
    int nAdded = isz(cache) - last;
    std::inplace_merge(cache.begin(), cache.begin()+last,cache.end(),std::greater<>());
    //std::sort(all(cache),std::greater<>());
    if (nAdded < isz(currPage)) {
        std::cout << "0" << std::endl;
        return 0;
    }
    bool paginationOK = removeBefore(fs,"<div class=\"pagination\">");
    if (!paginationOK) {
        std::cerr << "There is no additional pages...";
        std::cout << "0" << std::endl;
        return 0;
    }
    assert(paginationOK);
    bool activePage = removeBefore(fs,"<span class=\"page-index active\"");
    assert(activePage);
    bool nextPage = removeBefore(fs,"<span class=\"page-index\"");
    std::string page;
    nextPage = nextPage && extractBetween(fs, "pageIndex=\"", "\"", page);
    if(!nextPage) {
        std::cout << "0" << std::endl;
        return 0;
    }
    //assert(nextPage);
    std::cout << page << std::endl;
    return 0;
}