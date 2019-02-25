/*
    Задача: 1648. Автоматизация склада
    
    Решение: дерево отрезков, ленивое проталкивание, связный список, O((n+m)*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

namespace SegmentTreeLazy {
    
    /*******************************************************************************
     *  SegmentTree<Value, Extra, Traits> - segment tree class with lazy propagation, 0-indexed
     *  Default operations: minimal value on segment and addition on segment for int64_t type
     *  Use Traits<Value,Extra> for definition of:
     *      1)  neutral element for `Value`;
     *      2)  neutral element for `Extra`;
     *      3)  how should combine `Extra` with `Value`;
     *      4)  how should combine `Value` with `Value` (children to root);
     *      5)  how should combine `Extra` with `Extra`;
     *  See examples below: TraitsMinAdd<Value, Extra>
     ******************************************************************************/
    
    /*******************************************************************************
     *  Traits for minimal value on segment. 
     *  Get-query:    get minimal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsMinAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::max(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::min(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };
    
    /*******************************************************************************
     *  Additional traits, implemented below 
     ******************************************************************************/
    template<typename Value, typename Extra>  struct TraitsMaxAdd;
    
    /*******************************************************************************
     *  SegmentTree, see description above
     ******************************************************************************/
    template<typename Value = int64_t, typename Extra = int64_t, typename Traits = TraitsMinAdd<Value, Extra> >
    struct SegmentTree {
        
        /*******************************************************************************
         *  Node class
         ******************************************************************************/
        struct Node {
            Value value;
            
            Extra extra;
            
            Node(Value value_ = Traits::valueNeutral(), Extra extra_ = Traits::extraNeutral())
                : value(value_), extra(extra_) { }
            
            Value getValue(int l, int r) const { return Traits::getValue(NodeWrapper<Node>(l, r, *this)); }
        };
        
        /*******************************************************************************
         *  NodeWrapper class
         ******************************************************************************/
        template<typename NodeType>
        struct NodeWrapper {
            int l, r;
            NodeType node;
            NodeWrapper(int l_, int r_, NodeType node_)
                : l(l_), r(r_), node(node_) { }
            int  left() const { return l; }
            int right() const { return r; }
            int   mid() const { return (l+r)/2; }
            int   len() const { return r - l + 1; }
            Value& value() { return node.value; }
            Extra& extra() { return node.extra; }
            const Value& value() const { return node.value; }
            const Extra& extra() const { return node.extra; }
        };
        
        /*******************************************************************************
         *  SegmentTree public data: n - number of items, data - vector for nodes
         ******************************************************************************/
        int n; std::vector<Node> data;
        
        
        /*******************************************************************************
         *  Resize segment tree data to needed size
         ******************************************************************************/
        void resize(int n_) {
            n = n_;
            data.assign(2 * n - 1, Node());
        }
        
        /*******************************************************************************
         *  Lazy propagation from node to its children
         ******************************************************************************/
        void push(int v, int l, int r, int m) {
            if (data[v].extra != Traits::extraNeutral()) {
                Traits::push(
                    NodeWrapper<Node&>(l, m, data[v+1]), 
                    NodeWrapper<const Node&>(l, r, data[v])
                );
                Traits::push(
                    NodeWrapper<Node&>(m+1, r, data[v+2*(m-l+1)]), 
                    NodeWrapper<const Node&>(  l, r, data[v])
                );
                data[v].extra = Traits::extraNeutral();
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(int v, int l, int r, int m) {
            assert(data[v].extra == Traits::extraNeutral());
            Traits::pull(
                NodeWrapper<Node&>(  l, r, data[v]), 
                NodeWrapper<const Node&>(  l, m, data[v+1]), 
                NodeWrapper<const Node&>(m+1, r, data[v+2*(m-l+1)])
            );
        }
        
        /*******************************************************************************
         *  Build segtree from array with given values
         ******************************************************************************/
        template<typename T>
        void build(const std::vector<T>& arr, const int v, const int tl, const int tr) {
            if (tl == tr) {
                data[v] = Node(arr[tl]);
            } else {
                const int tm = (tl + tr) / 2;
                build(arr, v+1,   tl, tm);
                build(arr, v+2*(tm-tl+1), tm+1, tr);
                pull(v, tl, tr, tm);
            }
        }
        
        template<typename T>
        void build(const std::vector<T>& arr) { 
            resize((int)arr.size());
            build(arr, 0, 0, n-1);
        }

        /*******************************************************************************
         *  Get-query on range [ql, qr]
         ******************************************************************************/
        Node get(int ql, int qr, const int v, const int tl, const int tr) {
            if (ql == tl && qr == tr) {
                return data[v];
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                Node ret;
                if (qr <= tm) {
                    ret = get(ql, qr, v+1,   tl, tm);
                } else if (ql > tm) {
                    ret = get(ql, qr, v+2*(tm-tl+1), tm+1, tr);
                } else {
                    const auto lt = get(  ql, tm, v+1,   tl, tm);
                    const auto rt = get(tm+1, qr, v+2*(tm-tl+1), tm+1, tr);
                    Traits::pull(
                        NodeWrapper<Node&>(  ql, qr, ret), 
                        NodeWrapper<const Node&>(  ql, tm, lt), 
                        NodeWrapper<const Node&>(tm+1, qr, rt)
                    );
                }
                pull(v, tl, tr, tm);
                return ret;
            }
        }
        
        Value get(const int ql, const int qr) { return get(ql, qr, 0, 0, n-1).getValue(ql, qr); }
        
        /*******************************************************************************
         *  Update query on range [ql, qr] by extra
         ******************************************************************************/
        void update(const int ql, const int qr, const Extra& extra, const int v, const int tl, const int tr) {
            if (ql == tl && tr == qr) {
                Traits::push(
                    NodeWrapper<Node&>(tl, tr, data[v]),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra))
                );
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                if (qr <= tm) {
                    update(ql, qr, extra, v+1, tl, tm);
                } else if (ql > tm) {
                    update(ql, qr, extra, v+2*(tm-tl+1),tm+1,tr);
                } else {
                    update(ql, tm, extra, v+1,   tl, tm);
                    update(tm+1, qr, extra, v+2*(tm-tl+1), tm+1, tr);
                }
                pull(v, tl, tr, tm);
            }
        }

        void update(const int ql, const int qr, const Extra& extra) {
            update(ql, qr, extra, 0, 0, n-1); 
        }

    };
    
    /*******************************************************************************
     *  Traits for maximal value on segment. 
     *  Get-query:    get maximal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsMaxAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::min(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::max(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };   
}

const int INF = (int)2e8;

struct MaxPos {
    int max, pos;
    MaxPos(int max_ = -INF, int pos_ = 0) : max(max_), pos(pos_) { }
};

bool operator<(const MaxPos& a, const MaxPos& b) {
    return a.max < b.max || (a.max == b.max && a.pos > b.pos);
}

MaxPos operator+(const MaxPos& a, int extra) {
    return MaxPos(a.max+extra,a.pos);
}

/*******************************************************************************
 *  Traits for maximal value and its leftmost position on segment.
 *  Get-query:    get maximal value in segment [l, r] and its leftmost position
 *  Update-query: add const to each value in segment [l, r]
 ******************************************************************************/
template<typename Value, typename Extra>
struct TraitsMaxPosAdd {
    // Definition of neutral element for `Value`:
    static Value valueNeutral() { return Value(); }
    // Definition of neutral element for `Extra`:
    static Extra extraNeutral() { return Extra(0); }
    // Definition of how should combine `Extra` with `Value`:
    template<typename Node>
    static Value getValue(const Node& src) {
        return src.value() + src.extra();
    }
    // Definition of how should combine `Value` with `Value` (children to root):
    template<typename NodeRoot, typename NodeLt, typename NodeRt>
    static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
        root.value() = std::max(getValue(lt), getValue(rt));
    }
    // Definition of how should combine `Extra` with `Extra`:
    template<typename NodeDst, typename NodeSrc>
    static void push(NodeDst dst, const NodeSrc& src) {
        dst.extra() += src.extra();
    }
};

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
#define all(x) (x).begin(), (x).end()

template<typename Value>
struct SqrtList {
    
    std::vector<std::vector<Value>> data;
    
    static const int gsize = 256;
    
    SqrtList() : data(1, std::vector<Value>{}) {}
    
    void split(int g) {
        if ((int)data[g].size() >= 2 * gsize) {
            data.insert(data.begin()+g+1, std::vector<Value>(data[g].begin()+gsize, data[g].end()));
            data[g].resize(gsize);
        }
    }
    
    void mergeTo(int dst, int src) {
        if ((int)(data[dst].size()+data[src].size()) >= gsize) {
            data[dst].insert(data[dst].end(), data[src].begin(), data[src].end());
            data.erase(data.begin() + src);
        }
    }
    
    void merge(int g) {
        if (g+1 < (int)data.size()) { mergeTo(g,g+1); }
        if (g-1 >= 0 ) { mergeTo(g-1,g); }
    }
    
    bool getGroupPos(int index, int& g, int& p) const {
        g = (int)data.size()-1;
        p = (int)data[g].size();
        for (int id = 0; id < (int)data.size(); ++id) {
            if (index >= (int)data[id].size()) {
                index -= (int)data[id].size();
            } else {
                g = id;
                p = index;
                return true;
            }
        }
        return false;
    }
    
    const Value& get(int index) const {
        int g, p;
        bool flag = getGroupPos(index, g, p);
        assert(flag);
        return data[g][p];
    }
    
    Value& get(int index) {
        int g, p;
        bool flag = getGroupPos(index, g, p);
        assert(flag);
        return data[g][p];
    }
    
    void erase(int index) {
        int g, p;
        bool flag = getGroupPos(index, g, p);
        assert(flag);
        data[g].erase(data[g].begin()+p);
        merge(g);
    }

    void insert(int index, Value x) {
        int g, p;
        getGroupPos(index, g, p);
        assert(0 <= g && g < (int)data.size());
        assert(0 <= p && p <= (int)data[g].size());
        data[g].insert(data[g].begin()+p, x);
        split(g);
    }
    
};

struct Permutation {
    int front, back;
    std::vector<int> next;
    void build(const std::vector<int>& arr) {
        next.resize(arr.size());
        front = arr.front();
        back  = arr.back();
        next[back] = -1;
        for (int i = 0; i + 1 < (int)arr.size(); ++i) {
            next[arr[i]] = arr[i+1];
        }
    }
    void moveFront(int after) {
        if (after == front) {
            return;
        }
        if (after == back) {
            int newFront = next[front];
            next[back] = front;
            next[front] = -1;
            back = front;
            front = newFront;
            return;
        }
        int newFront = next[front];
        next[front] = next[after];
        next[after] = front;
        front = newFront;
    }
};

vi fast(vi queries, vi queueInit) {
    const int nQueries = (int)queries.size();
    const int nItems = (int)queueInit.size();
    
    Permutation queue;
    queue.build(queueInit);
        
    vi posQueryInQueue(nQueries), posItemInQueue(nItems), answer;
    for (int i = 0; i < nItems; ++i) {
        const int item = queueInit[i];
        posItemInQueue[item] = i;
    }
    vvi posItemInQueries(nItems);
    {
        vi was(nItems);
        for (int i = 0; i < nQueries; ++i) {
            const int item = queries[i];
            posItemInQueries[item].push_back(i);
            if (was[item]) {
                posQueryInQueue[i] = -INF;
            } else {
                posQueryInQueue[i] = posItemInQueue[item];
                was[item] = 1;
            }
        }
    }
    // Building SegmentTree
    SegmentTreeLazy::SegmentTree<MaxPos,int,TraitsMaxPosAdd<MaxPos,int>> segtree;
    {
        std::vector<MaxPos> temp(queries.size());
        for (int i = 0; i < (int)queries.size(); ++i) {
            temp[i] = MaxPos(posQueryInQueue[i], i);
        }
        segtree.build(temp);
    }
    auto getMaxPos = [&](int l, int r) {
        return segtree.get(l,r);
    };
    auto inc = [&](int l, int r, int x) {
        assert(0 <= l && l <= r && r < (int)posQueryInQueue.size());
        segtree.update(l,r,x);
    };
    auto set = [&](int p, int x) {
        assert(0 <= p && p < (int)posQueryInQueue.size());
        segtree.update(p, p, x-segtree.get(p,p).max);
    };
    
    auto moveFront = [&](int from) {
        int front = queue.front;
        auto up = std::upper_bound(all(posItemInQueries[front]), from);
        int after, right, pos;
        if (up == posItemInQueries[front].end()) {
            after = queue.back;
            pos = nItems-1;
            right = nQueries-1;
        } else {
            right = *up-1;
            assert(from <= right);
            auto maxPos = getMaxPos(from, right);
            pos = maxPos.max;
            after = queries[maxPos.pos];
        }
        answer.push_back(pos);
        queue.moveFront(after);
        
        inc(from, right,-1);
        if (right+1 < nQueries) { set(right+1, pos); }
    };
    for (int p = 0; p < nQueries; ++p) {
        int query = queries[p];
        while (queue.front != query) { moveFront(p); }
        moveFront(p);
    }
    return answer;
}

namespace FastIO {
    
    void putChar(char c) {
        static const int SIZE = 1 << 16;
        static char buffer[SIZE];
        static int size = 0;
        if (size == SIZE || c == EOF) {
            fwrite(buffer, 1, size, stdout);
            size = 0;
        }
        if (c != EOF) { buffer[size++] = c; }
    }
    
    template<typename T>
    void putInt(T x) {
        static char stack[25];
        int size = 0;
        bool positive = true;
        if (x < 0) { positive = false; x = -x; }
        do { stack[size++] = char('0' + x % 10); x /= 10; } while (x > 0);
        if (!positive) {stack[size++] = '-'; }
        while (size--) { putChar(stack[size]); }
    }
    
    char getChar() {
        static const int SIZE = 1 << 16;
        static char buffer[SIZE];
        static int pos = 0;
        static int size = 0;
        if (pos == size) {
            size = (int)fread(buffer, 1, SIZE, stdin);
            pos = 0;
        }
        return (pos == size) ? EOF : buffer[pos++];
    }
    
    template<typename T>
    T getInt() {
        char c = '?';
        while (!(c == '-' || ('0' <= c && c <= '9'))) { c = getChar(); }
        T v(0);
        bool positive = true;
        if (c == '-') { positive = false; c = getChar(); }
        while ('0' <= c && c <= '9') { (v *= 10) += (c - '0'); c = getChar(); }
        return positive ? v : -v;
    }
}

int main() {
    using namespace FastIO;
    int n, q;
    n = getInt<int>();
    q = getInt<int>();
    vi queries(q), queue(n);
    for (auto &it : queries) { it = getInt<int>()-1; }
    for (auto &it : queue) { it = getInt<int>()-1; }
    vi answ = fast(queries, queue);
    putInt((int)answ.size());
    putChar('\n');
    for (auto it : answ) { putInt(it+1); putChar(' '); }
    putChar('\n');
    putChar(EOF);
    return 0;
}