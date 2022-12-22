#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
/*
    ? 1 51 2
    ! 150 1 0
    ? 167 50 0
    ! 150 67 3
    ? 150 84 1
    ! 174 50 2
    ? 135  1 2
    ! 16  51 0
    ? 25 51 2
    ! 126 1 0
    ? 101 50 3
    ! 100 51 0
    ? 98 51 2
    ! 101 48 1
    ? 106 100 0
    ! 45 150 2
    ? 50 127 1
    ! 
*/
using pii = std::pair<int,int>;
using tiii = std::tuple<int,int,int>;
using vpii = std::vector<pii>;
using vtiii = std::vector<tiii>;
using vs = std::vector<std::string>;
const int right = 0, down = 1, left = 2, up = 3; 
const vpii steps{{0,+1},{+1,0},{0,-1},{-1,0}};

bool empty(std::string s) {
    return s.find('.') == s.npos && s.find('#') == s.npos;
}

tiii ask(int row, int col, int dir) {
    int nextRow, nextCol, nextDir;
    if (dir == left) {
        if (col == 51) {
            if (1 <= row && row <= 50) {
                nextRow = 51 - row + 100;
                nextCol = 1;
                nextDir = right;
            } else {
                assert(51 <= row && row <= 100);
                nextRow = 101;
                nextCol = row - 50;
                nextDir = down;
            }
        } else if (col == 1) {
            if (101 <= row && row <= 150) {
                nextRow = 151 - row;
                nextCol = 51;
                nextDir = right;
            } else {
                assert(151 <= row && row <= 200);
                nextRow = 1;
                nextCol = row - 150 + 50;
                nextDir = down;
            }
        }
    } else if (dir == up) {
        if (row == 1) {
            if (51 <= col && col <= 100) {
                nextRow = 150 + col - 50;
                nextCol = 1;
                nextDir = right;
            } else {
                assert(101 <= col && col <= 150);
                nextRow = 200;
                nextCol = col - 100;
                nextDir = up;
            }
        } else {
            assert(row == 101);
            nextRow = col + 50;
            nextCol = 51;
            nextDir = right;
        }
    } else if (dir == down) {
        if (row == 50) {
            assert(101 <= col && col <= 150);
            nextRow = col - 100 + 50;
            nextCol = 100;
            nextDir = left;
        } else if (row == 150) {
            assert(51 <= col && col <= 100);
            nextRow = col - 50 + 150;
            nextCol = 50;
            nextDir = left;
        } else {
            assert(row == 200);
            assert(1 <= col && col <= 50);
            nextRow = 1;
            nextCol = col - 0 + 100;
            nextDir = down;
        }
    } else {
        assert(dir == right);
        if (col == 150) {
            assert(1 <= row && row <= 50);
            nextRow = 51 - row + 100;
            nextCol = 100;
            nextDir = left;
        } else if (col == 100) {
            if (51 <= row && row <= 100) {            
                nextRow = 50;
                nextCol = row - 50 + 100;
                nextDir = up;
            } else {
                assert(101 <= row && row <= 150);
                nextCol = 150;
                nextRow = 151 - row;
                nextDir = left;
            }
        } else {
            assert(col == 50);
            assert(151 <= row && row <= 200);
            nextRow = 150;
            nextCol = row - 150 + 50;
            nextDir = up;
        }
    }
    return std::make_tuple(nextRow, nextCol, nextDir);
}

const bool debug = 1;
void part1() {
    std::string s;
    vs a;
    int nCols=0;
    while(std::getline(std::cin,s)) {
        if (empty(s)) break;
        a.push_back(s);
        nCols = std::max(nCols, isz(s));
    }
    for (auto &it : a) {
        while (isz(it) < nCols) it += ' ';
    }
    std::cin >> s;
    int row = 0, col = (int)a[0].find('.'), dir = 0;
    auto print = [&](){
        if(!debug)return;
        std::cout << "map:\n";
        for (int r = 0; r < isz(a); r++) {
            for (int c = 0; c < isz(a[r]); c++) {
                if (r == row && c == col) {
                    std::cout << 'o';
                } else {
                    std::cout << a[r][c];
                }
            }
            std::cout << std::endl;
        }
    };
    while(s.size()) {
        if(debug) {
            std::cout << std::string(40,'-') << std::endl;
            std::cout << "s = '" << s << "'" << std::endl;
        }
        int x;
        int code = sscanf(s.c_str(),"%d", &x);
        if (code == 1) {
            debug && std::cout << "x = " << x << std::endl;
            s = s.substr(std::to_string(x).size());
            while (x--) {
                debug && std::cout << "row = " << row << ", col = " << col << std::endl;
                print();
                int nextRow = row + steps[dir].first;
                int nextCol = col + steps[dir].second;
                while (true) {
                    if (nextRow < 0) nextRow += isz(a);
                    if (nextRow >= isz(a)) nextRow -= isz(a);
                    assert(0 <= nextRow && nextRow < isz(a));
                    if (nextCol < 0) nextCol += isz(a[nextRow]);
                    if (nextCol >= isz(a[nextRow])) nextCol -= isz(a[nextRow]);
                    assert(0 <= nextCol && nextCol < isz(a[nextRow]));
                    if (a[nextRow][nextCol] == ' ') {
                        nextRow += steps[dir].first;
                        nextCol += steps[dir].second;
                    } else {
                        break;
                    }
                }
                debug && std::cout << "nextRow = " << nextRow << ", nextCol = " << nextCol << std::endl;
                assert(0 <= nextRow && nextRow < isz(a));
                assert(0 <= nextCol && nextCol < isz(a[nextRow]));
                if (a[nextRow][nextCol] == '#') {
                    x = 0;
                } else {
                    row = nextRow;
                    col = nextCol;
                }
            }
        } else {
            switch(s[0]) {
                case 'R': (dir+=1)%=4; break;
                case 'L': (dir+=3)%=4; break;
                default: assert(false);
            };
            s = s.substr(1);
        }
    }
    row++,col++;
    std::cout << "row = " << row << ", col = " << col << ", facing = " << dir << std::endl;
    std::cout << "answer1 = " << row * 1000 + col * 4 + dir << std::endl;
}
void part3(std::string filename) {
    std::ifstream fin(filename);
    assert(!!fin);
    std::string s;
    vs a;
    int nCols=0;
    while(std::getline(fin,s)) {
        if (empty(s)) break;
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        s = " " + s + " ";
        a.push_back(s);
        nCols = std::max(nCols, isz(s));
    }
    a.insert(a.begin(), std::string(nCols, ' '));
    a.push_back(std::string(nCols, ' '));
    for (auto &it : a) {
        while (isz(it) < nCols) it += ' ';
    }
    fin >> s;
    int row = 1, col = (int)a[1].find('.'), dir = 0;
    auto print = [&](){
        std::cout << "pos = {" << row << ", " << col << ", " << dir << std::endl;
        std::cout << "map:\n";
        for (int r = 0; r < isz(a); r++) {
            for (int c = 0; c < isz(a[r]); c++) {
                if (r == row && c == col) {
                    std::cout << 'o';
                } else {
                    std::cout << a[r][c];
                }
            }
            std::cout << std::endl;
        }
    };
    while(s.size()) {
        int x;
        int code = sscanf(s.c_str(),"%d", &x);
        if (code == 1) {
            s = s.substr(std::to_string(x).size());
            while (x--) {
                int nextRow = row + steps[dir].first;
                int nextCol = col + steps[dir].second;
                int nextDir = dir;
                assert(0 <= nextRow && nextRow < isz(a));
                assert(0 <= nextCol && nextCol < isz(a[nextRow]));
                if (a[nextRow][nextCol] == ' ') {
                    //print();
                    std::cout << "? " << row << ' ' << col << ' ' << dir << std::endl;
                    std::tie(nextRow, nextCol, nextDir) = ask(row, col, dir);
                    std::cout << "! " << nextRow << " " << nextCol << " " << nextDir << std::endl;
                    auto tmp = ask(nextRow, nextCol, (nextDir + 2) % 4);
                    if (tmp != std::make_tuple(row,col,(dir+2)%4)) {
                        std::cout << "WA for " << nextRow << ' ' << nextCol << ' ' << (nextDir + 2) % 4 << std::endl;
                        std::cout << "got = " << std::get<0>(tmp) << ' ' << std::get<1>(tmp) << ' ' << std::get<2>(tmp) << std::endl;
                        std::cout << "exp = " << row << ' ' << col << ' ' << (dir+2)%4 << std::endl;
                    }
                    assert(tmp == std::make_tuple(row,col,(dir+2)%4));
                    //std::cout << "type nextRow, nextCol and nextDir:\n";
                    //std::cin >> nextRow >> nextCol >> nextDir;
                }
                if (a[nextRow][nextCol] == '#') {
                    x = 0;
                } else {
                    row = nextRow;
                    col = nextCol;
                    dir = nextDir;
                }
            }
        } else {
            switch(s[0]) {
                case 'R': (dir+=1)%=4; break;
                case 'L': (dir+=3)%=4; break;
                default: assert(false);
            };
            s = s.substr(1);
        }
    }
    std::cout << "row = " << row << ", col = " << col << ", facing = " << dir << std::endl;
    std::cout << "answer1 = " << row * 1000 + col * 4 + dir << std::endl;
}


using tiii = std::tuple<int,int,int>;
void part2() {
   
    std::string s;
    vs a;
    int nCols = 0;
    while(std::getline(std::cin,s)) {
        if (empty(s)) break;
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        a.push_back(s);
        nCols = std::max(nCols, isz(s));
    }
    for (auto &it : a) {
        while (isz(it) < nCols) it += ' ';
    }
    if(debug) {
        for (auto &it : a)
            std::cout << "it = '" << it << "'" << std::endl;
    }
    const tiii UNDEF{-1,-1,-1};
    int nRows = isz(a);
    std::vector next(nRows, std::vector(nCols,vtiii(4,UNDEF)));
    // next[r][c][d] -> nextCell
/*
    my pattern:
    .12
    .3.
    54.
    6..
*/ 
    const int side = nCols/3;
    std::cout << "side = " << side << std::endl;
    // 2D <--> 3R (+)
    for (int c = 0; c < side; c++) {
        next[side-1][2*side+c][down] = {side+c, 2*side-1, left};
        next[side+c][2*side-1][right] = {side-1,2*side+c,up};
    }
    // 4D <--> 6R (+)
    for (int c = 0; c < side; c++) {
        next[3*side-1][side+c][down] = {3*side+c, side-1, left};
        next[3*side+c][side-1][right] = {3*side-1,side+c, up};
    }
    // 2R <--> 4R (+)
    for (int r = 0; r < side; r++) {
        next[r][3*side-1][right] = {3*side-1-r, 2*side-1, left};
        next[3*side-1-r][2*side-1][right] = {3*side-1-r, 2*side-1, left};
    }
    // 2U <--> 6D (+)
    for (int c = 0; c < side; c++) {
        next[0][c+2*side][up] = {4*side-1,c,up};
        next[4*side-1][c][down] = {0,c+2*side,down};
    }
    // 3L <--> 5U (+)
    for (int r = side; r < 2*side; r++) {
        next[r][side][left] = {2*side,r-side,down};
        next[2*side][r-side][up] = {r,side,right};
    }
    // 1U <--> 6L (+)
    for (int c = 0; c < side; c++) {
        next[0][side+c][up] = {3*side+c, 0, right};
        next[3*side+c][0][left] = {0, side+c, down};
    }
    // 1L <--> 5L (+)
    for (int r = 0; r < side; r++) {
        next[r][side][left] = {3*side-1-r,0,right};
        next[3*side-1-r][0][left] = {r,side,right};
    }
    std::cin >> s;
    int row = 0, col = (int)a[0].find('.'), dir = 0;
    auto print = [&](){
        std::cout << "map:\n";
        for (int r = 0; r < isz(a); r++) {
            for (int c = 0; c < isz(a[r]); c++) {
                if (r == row && c == col) {
                    std::cout << 'o';
                } else {
                    std::cout << a[r][c];
                }
            }
            std::cout << std::endl;
        }
    };
    while(s.size()) {
        if(debug) {
            std::cout << std::string(40,'-') << std::endl;
            std::cout << "s = '" << s << "'" << std::endl;
        }
        int x;
        int code = sscanf(s.c_str(),"%d", &x);
        if (code == 1) {
            debug && std::cout << "move = " << x << std::endl;
            s = s.substr(std::to_string(x).size());
            debug && std::cout << "before:\n";
            print();
            while (x--) {
                debug && std::cout << "row = " << row << ", col = " << col << ", dir = " << dir << std::endl;
                int nextRow, nextCol, nextDir;
                if (next[row][col][dir] != UNDEF) {
                    std::tie(nextRow,nextCol,nextDir) = next[row][col][dir];
                    std::cout << "staying at the row = " << row << ", col = " << col << ", dir = " << dir << std::endl;
                    
                } else {
                    nextRow = row+steps[dir].first;
                    nextCol = col+steps[dir].second;
                    nextDir = dir;
                }
                if (a[nextRow][nextCol] == '#') {
                    x = 0;
                } else {
                    row = nextRow;
                    col = nextCol;
                    dir = nextDir;
                }
            }
            debug && std::cout << "after:\n";
            print();
        } else {
            std::cout << "command = " << s[0] << std::endl;
            switch(s[0]) {
                case 'R': (dir+=1)%=4; break;
                case 'L': (dir+=3)%=4; break;
                default: assert(false);
            };
            s = s.substr(1);
        }
    }
    print();
    row++,col++;
    std::cout << "row = " << row << ", col = " << col << ", facing = " << dir << std::endl;
    std::cout << "answer1 = " << row * 1000 + col * 4 + dir << std::endl;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    part3(argv[1]);
}