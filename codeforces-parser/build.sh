#!/bin/bash
echo "building group-contests.cpp..."
g++ -O3 -Wall -Wextra -pedantic group-contests.cpp -o "group-contests"
echo "building contest-status.cpp..."
g++ -O3 -Wall -Wextra -pedantic contest-status.cpp -o "contest-status"
echo "building process-rating.cpp..."
g++ -O3 -Wall -Wextra -pedantic process-rating.cpp -o "process-rating"
echo "user-status.cpp..."
g++ -O3 -Wall -Wextra -pedantic user-status.cpp -o user-status.exe
echo "get-link.cpp..."
g++ -O3 -Wall -Wextra -pedantic get-link.cpp -o "get-link"
echo "search-in-file.cpp..."
g++ -O3 -Wall -Wextra -pedantic search-in-file.cpp -o "search-in-file"