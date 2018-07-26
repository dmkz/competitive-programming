/*
    Задача: 991. ePig
    
    Решение: моделирование, реализация, O(n^2*k^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>

struct Query {
    int client, piece;
};

struct Transfer {
    int from, to, what;
};

int main() {
    int nClients, nPieces;
    scanf("%d %d", &nClients, &nPieces);

    std::vector<std::vector<bool>> has(1+nClients, std::vector<bool>(1+nPieces));
    
    std::vector<std::vector<int>> nSent(1+nClients, std::vector<int>(1+nClients));
    
    std::vector<int> countPerPiece(1+nPieces, 0);
    
    std::vector<int> countPerClient(1+nClients, 0);
    
    for (int k = 1; k <= nPieces; ++k) {
        has[1][k] = true;
        countPerClient[1]++;
        countPerPiece[k]++;
    }
    
    std::vector<std::vector<Query>> queries(1+nClients);
    
    int time = 0;
    
    std::vector<int> answer(1+nClients, 0);
    
    std::vector<Transfer> queue;
    
    while (true) {
        bool finished = true;
        for (int id = 1; id <= nClients; ++id) {
            if (countPerClient[id] != nPieces) {
                finished = false;
                break;
            }
        }
        if (finished) {
            break;
        }
        ++time;
        
        for (int id = 2; id <= nClients; ++id) {
            if (answer[id]) continue;
            int need = 0;
            for (int i = 1; i <= nPieces; ++i) {
                if (!has[id][i] && (need == 0 || countPerPiece[i] < countPerPiece[need])) {
                    need = i;
                }
            }
            assert(need != 0);
            int from = 0;
            for (int i = 1; i <= nClients; ++i) {
                if (has[i][need] && (from == 0 || countPerClient[i] < countPerClient[from])) {
                    from = i;
                }
            }
            assert(from != 0);
            queries[from].push_back(Query{id, need});
        }
        
        for (int from = 1; from <= nClients; ++from) {
            if (queries[from].empty()) {
                continue;
            }
            int to = 0, what = 0;
            for (auto& q : queries[from]) {
                if (to == 0) {
                    to = q.client;
                    what = q.piece;
                    continue;
                }
                if (nSent[q.client][from] < nSent[to][from]) {
                    continue;
                }
                if (nSent[q.client][from] > nSent[to][from]) {
                    to = q.client;
                    what = q.piece;
                    continue;
                }
                if (countPerClient[q.client] > countPerClient[to]) {
                    continue;
                }
                if (countPerClient[q.client] < countPerClient[to]) {
                    to = q.client;
                    what = q.piece;
                    continue;
                }
                assert(to < q.client);
            }
            queue.push_back(Transfer{from, to, what});
            queries[from].clear();
            assert(to != 0 && what != 0 && !has[to][what] && has[from][what]);
        }
        
        for (auto& it : queue) {
            nSent[it.from][it.to]++;
            countPerPiece[it.what]++;
            countPerClient[it.to]++;
            has[it.to][it.what] = true;
            if (countPerClient[it.to] == nPieces) {
                answer[it.to] = time;
            }
        }
        
        queue.clear();
    }
    for (int id = 2; id <= nClients; ++id) {
        printf("%d ", answer[id]);
    }
    return 0;
}