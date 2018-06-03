#include <iostream>
#include <queue>
#include <vector>

int main() {
    char c1, r1, c2, r2;
    scanf(" %c%c %c%c", &c1, &r1, &c2, &r2);
    c1 -= 'A'; r1 -= '1';
    c2 -= 'A'; r2 -= '1';
    
    std::vector<std::vector<int>> dist(9, std::vector<int>(9, -1));
    dist[r1][c1] = 0;
    std::queue<int> queue;
    queue.push(r1*16+c1);
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        const int r = curr / 16;
        const int c = curr % 16;
        if ((r + c) % 2) { // white
            for (int dr = -2; dr <= 2; ++dr) {
                for (int dc = -2; dc <= 2; ++dc) {
                    if (dr*dr + dc*dc != 5) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr < 0 || nr > 8 || nc < 0 || nc > 8) {
                        continue;
                    }
                    if (dist[nr][nc] == -1) {
                        dist[nr][nc] = dist[r][c]+1;
                        queue.push(nr*16+nc);
                    }
                }
            }
        } else {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr*dr + dc* dc != 2) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    while (0 <= nr && nr < 9 && 0 <= nc && nc < 9) {
                        if (dist[nr][nc] == -1) {
                            dist[nr][nc] = dist[r][c]+1;
                            queue.push(nr*16+nc);
                        }
                        nr += dr;
                        nc += dc;
                    }
                }
            }
        }
    }
    std::cout << dist[r2][c2];
    return 0;
}