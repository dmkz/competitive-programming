/*
    Задача: 1177. Пирамида
    Решение: двумерное дерево отрезков, запрос на минимум, O(n*m*log(n)*log(m))
*/
#include <stdio.h>
#include <algorithm>
#include <cassert>

int arr[1024][1024];
int tree[2048][2048];

struct Node {
    int vertex, left, right;
    
    Node(int vertex_, int left_, int right_)
        : vertex(vertex_)
        , left(left_)
        , right(right_)
    { }
    
    inline int length() const {
        return right - left + 1;
    }
    
    inline int mid() const {
        return (left + right) / 2;
    }
    
    inline bool empty() const {
        return right < left;
    }
    
    inline Node left_child() const {
        return Node(2 * vertex + 1, left, (left + right) / 2);
    }
    
    inline Node right_child() const {
        return Node(2 * vertex + 2, (left + right) / 2 + 1, right);
    }
};

struct Query {

    Node node;
    
    int left, right;
    
    Query(const Node& node_, int left_, int right_)
        : node(node_)
        , left(left_)
        , right(right_)
    { }
    
    inline bool empty() const {
        return right < left;
    }
    
    inline bool full() const {
        return node.left == left && node.right == right;
    }
    
    inline Query left_child() const {
        return Query(node.left_child(), left, std::min(right, node.mid()));
    }
    
    inline Query right_child() const {
        return Query(node.right_child(), std::max(node.mid()+1, left), right);
    }
};

inline void build2(const Node& r, const Node& c) {
    if (c.length() == 1) {
        tree[r.vertex][c.vertex] = (r.length() > 1) ? 
            std::min(
                tree[ r.left_child().vertex][c.vertex], 
                tree[r.right_child().vertex][c.vertex]
            ) : arr[r.left][c.left];    
    } else {
        const auto left  = c.left_child();
        const auto right = c.right_child();
        build2(r,  left);
        build2(r, right);
        tree[r.vertex][c.vertex] = std::min(
            tree[r.vertex][ left.vertex], 
            tree[r.vertex][right.vertex]
        );
    }
}

inline void build1(const Node& r, const Node& c) {
    if (r.length() > 1) {
        build1( r.left_child(), c);
        build1(r.right_child(), c);
    }
    build2(r, c);
}

inline void build(int nRows, int nCols) {
    build1(Node(0, 0, nRows-1), Node(0, 0, nCols-1));
}

const int INF = (int)1e9;

inline int query2(const Query& r, const Query& c) {
    if (c.empty()) {
        return INF;
    } else if (c.full()) {
        return tree[r.node.vertex][c.node.vertex];
    } else {
        return std::min(query2(r, c.left_child()), query2(r, c.right_child()));
    }
   
}

inline int query1(const Query& r, const Query& c) {
    if (r.empty()) {
        return INF;
    } else if (r.full()) {
        return query2(r, c);
    } else {
        return std::min(query1(r.left_child(), c), query1(r.right_child(), c));
    }
    
}

inline int query(int nRows, int nCols, int row1, int col1, int row2, int col2) {
    return query1(
        Query(Node(0, 0, nRows-1), row1, row2), 
        Query(Node(0, 0, nCols-1), col1, col2)
    );
}

int main() {
    int nCols, nRows, w1, h1, w2, h2;
    scanf("%d %d %d %d %d %d", &nCols, &nRows, &w1, &h1, &w2, &h2);
    
    static int sum[1024][1024];
    for (int i = 1; i <= nRows; ++i) {
        for (int j = 1; j <= nCols; ++j) {
            scanf("%d", &sum[i][j]);
        }
    }
    
    for (int i = nRows; i >= 1; --i) {
        for (int j = nCols; j >= 1; --j) {
            sum[i][j] += sum[i+1][j] + sum[i][j+1] - sum[i+1][j+1];
        }
    }
    
    for (int r = 2; r + h2 - 1 < nRows; ++r) {
        for (int c = 2; c + w2 - 1 < nCols; ++c) {
            arr[r][c] = sum[r][c] - sum[r+h2][c] - sum[r][c+w2] + sum[r+h2][c+w2];
        }
    }
    
    build(nRows+1, nCols+1);
    
    int answ = 0;
    for (int r = 1; r + h1 - 1 <= nRows; ++r) {
        for (int c = 1; c + w1 - 1 <= nCols; ++c) {
            int s = sum[r][c] - sum[r+h1][c] - sum[r][c+w1] + sum[r+h1][c+w1];
            int q = query(nRows+1, nCols+1, r+1, c+1, r + h1 - 1 - h2, c + w1 - 1 - w2);
            s -= q;
            answ = std::max(answ,  s);
        }
    }
    
    printf("%d", answ);
    
    return 0;
}