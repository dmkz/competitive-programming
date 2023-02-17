// g++ -O3 -Wall -Wextra -pedantic user-status.cpp -o user-status.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"

#define watch(x) debug && std::cerr << #x << " = '" << x << "'" << std::endl;

const bool debug = false;

#include "submission.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc == 3);
    std::string fs = fileToString(argv[1]);
    std::string link = argv[2];
    Cache cacheObject(link);
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
    //int added = 0;
    //int ignored = 0;
    //std::cerr << "cache size = " << isz(cache) << std::endl;
    for (const auto &s : currPage) {
        if(!std::binary_search(cache.begin(),
                               cache.begin()+last,
                               s, std::greater<>()))
        {
            cache.push_back(s);
            //added++;
        } else {
            //ignored++;
        }
    }
    //std::cerr << "added = " << added << std::endl;
    //std::cerr << "ignored = " << ignored << std::endl;
    int nAdded = isz(cache) - last;
    std::inplace_merge(cache.begin(), cache.begin()+last,cache.end(),std::greater<>());
    //std::sort(all(cache),std::greater<>());
    if (nAdded < isz(currPage)) {
        std::cout << "done";
        return 0;
    }
    bool paginationOK = removeBefore(fs,"<div class=\"pagination\">");
    if (!paginationOK) {
        std::cerr << "There is no additional pages...";
        std::cout << "done";
        return 0;
    }
    assert(paginationOK);
    bool activePage = removeBefore(fs,"<span class=\"page-index active\"");
    assert(activePage);
    bool nextPage = removeBefore(fs,"<span class=\"page-index\"");
    std::string page;
    nextPage = nextPage && extractBetween(fs, "pageIndex=\"", "\"", page);
    if(!nextPage) {
        std::cout << "done";
        return 0;
    }
    //assert(nextPage);
    std::cout << page << std::endl;
    return 0;
}