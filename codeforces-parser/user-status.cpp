// g++ -O3 -Wall -Wextra -pedantic user-status.cpp -o user-status.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"

#define watch(x) debug && std::cerr << #x << " = '" << x << "'" << std::endl;

const bool debug = false;

#include "submission.hpp"

int main(int argc_, char **argv_) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc_ <= 4);
    auto argv = getArguments(argc_, argv_);
    std::string fs = fileToString(argv[1]);
    int maxPage = getMaxPage(fs);
    std::cerr << "maxPage = " << maxPage << std::endl;
    stringToFile("user-status.txt", fs);
    std::string link = argv[2];
    const bool isSave = (argv[3] == "save");
    std::cerr << "need to save!" << std::endl;
    Cache cacheObject(link, isSave);
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
    int added = 0;
    int ignored = 0;
    //std::cerr << "cache size = " << isz(cache) << std::endl;
    for (const auto &s : currPage) {
        if (!std::binary_search(cache.begin(),
                                cache.begin()+last,
                                s, std::greater<>()))
        {
            cache.push_back(s);
            added++;
        } else {
            ignored++;
        }
    }
    int nextUnreadPage = -1;
    if (added == 0) {
        nextUnreadPage = (added+isz(cache))/50;
    }
    std::cerr << "added = " << added << std::endl;
    std::cerr << "ignored = " << ignored << std::endl;
    int nAdded = isz(cache) - last;
    std::inplace_merge(cache.begin(), cache.begin()+last,cache.end(),std::greater<>());
    //std::sort(all(cache),std::greater<>());
    /*if (nAdded < isz(currPage)) {
        std::cout << "done " << maxPage << " " << added << " " << ignored << std::endl;
        return 0;
    }*/
    bool paginationOK = removeBefore(fs,"<div class=\"pagination\">");
    if (!paginationOK) {
        std::cerr << "There is no additional pages...";
        std::cout << "done " << maxPage << " " << added << " " << ignored << std::endl;
        return 0;
    }
    assert(paginationOK);
    bool activePage = removeBefore(fs,"<span class=\"page-index active\"");
    assert(activePage);
    bool nextPage = removeBefore(fs,"<span class=\"page-index\"");
    std::string page;
    nextPage = nextPage && extractBetween(fs, "pageIndex=\"", "\"", page);
    if(!nextPage) {
        std::cout << "done " << maxPage << " " << added << " " << ignored << std::endl;
        return 0;
    }
    //assert(nextPage);
    if (nextUnreadPage != -1 && nextUnreadPage <= maxPage) {
        page = std::to_string(
            std::max<int>(std::stoi(page), nextUnreadPage)
        );
    }
    std::cout << page << " " << maxPage << " " << added << " " << ignored << std::endl;
    return 0;
}