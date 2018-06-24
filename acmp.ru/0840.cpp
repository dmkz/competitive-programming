#include <stdio.h>
#include <vector>

struct Ball {
    double x, y, z, r;
    
    static Ball read() {
        double x, y, z, r;
        scanf("%lf %lf %lf %lf", &x, &y, &z, &r);
        return Ball{x,y,z,r};
    }
    
    inline bool intersect(const Ball& other) const {
        double dx = x - other.x, dy = y - other.y, dz = z - other.z;
        return dx*dx+dy*dy+dz*dz < (r + other.r)*(r + other.r);
    }
};

int main() {
    std::vector<bool> alone{true};
    std::vector<Ball> balls{Ball::read()};
    int nAlone = 1;
    
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        // Добавление нового шара:
        alone.push_back(true);
        balls.push_back(Ball::read());
        ++nAlone;
        
        // Пересечение со всеми предыдущими шарами:
        for (int j = i-1; j >= 0; --j) {
            if (balls[j].intersect(balls[i])) {
                if (alone[j]) {
                    alone[j] = false;
                    --nAlone;
                }
                if (alone[i]) {
                    alone[i] = false;
                    --nAlone;
                }
            }
        }
        
        // Проверка на существование обособленного шара:
        if (nAlone == 0) {
            printf("%d", i);
            return 0;
        }
    }
    printf("0");
    return 0;
}