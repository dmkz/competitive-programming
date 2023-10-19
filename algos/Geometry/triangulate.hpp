#ifndef __TRIANGULATE_HPP__
#define __TRIANGULATE_HPP__
namespace algos {
namespace triangulate {

using namespace geoma;

inline bool liesBelow(pii P1, pii P2) {
    auto [x1,y1] = P1;
    auto [x2,y2] = P2;
    return (y1 < y2 || (y1 == y2 && x1 > x2));
}

inline bool liesAbove(pii P1, pii P2) {
    auto [x1,y1] = P1;
    auto [x2,y2] = P2;
    return (y1 > y2 || (y1 == y2 && x1 < x2));
}

const int START = 0, SPLIT = 1, END = 2, MERGE = 3, REGULAR = 4;

inline auto getTypeOfVertex(const auto &P, int i) {
    pii L = getPrev(P, i), M = P[i], R = getNext(P, i);
    if (liesBelow(L,M) && liesBelow(R,M) && angleLessThanPi(L,M,R))
        return START;
    if (liesBelow(L,M) && liesBelow(R,M) && angleGreaterThanPi(L,M,R))
        return SPLIT;
    if (liesAbove(L,M) && liesAbove(R,M) && angleLessThanPi(L,M,R))
        return END;
    if (liesAbove(L,M) && liesAbove(R,M) && angleGreaterThanPi(L,M,R))
        return MERGE;
    return REGULAR;
}

inline std::string type2str(int t) {
    switch(t) {
        case START: return "start";
        case SPLIT: return "split";
        case END: return "end";
        case MERGE: return "merge";
        case REGULAR: return "regular";
        default: return "none";
    };
}

inline bool isMonotone(const vpii &P) {
    if (isz(P) <= 3)
        return true;
    // начинаем с максимальной
    int imax = -1, ymax = INT_MIN;
    for (int i = 0; i < isz(P); i++)
        if (P[i].second >= ymax) {
            imax = i;
            ymax = P[i].second;
        }
    int len = 0;
    int i = imax;
    while (len <= isz(P) && P[i].second >= getNext(P, i).second) {
        len++;
        i++;
        if (i == isz(P)) i = 0;
    }
    while (len <= isz(P) && P[i].second <= getNext(P, i).second) {
        len++;
        i++;
        if (i == isz(P)) i = 0;
    }
    return len >= isz(P);
}

inline vpii findDiagonals(const vpii &P) {
    static vtiii pq;
    pq.clear();
    for (int i = 0; i < isz(P); i++) {
        auto [x,y] = P[i];
        pq << tiii(y,-x,i);
    }
    std::sort(all(pq), std::greater<>());
    int currY, currX;
    auto setCurrY = [&](int newCurrY) { currY = newCurrY; };
    auto setCurrX = [&](int newCurrX) { currX = newCurrX; };

    static vi helper;
    helper.assign(isz(P),-1);
    
    auto getHelper = [&](int i) {
        if (i < 0) i += isz(P);
        assert(0 <= i && i < isz(P));
        assert(helper[i] != -1);
        return helper[i];
    };
    auto setHelper = [&](int i, int j) {
        if (i < 0) i += isz(P);
        assert(0 <= i && i < isz(P));
        if (helper[i] == i)
            helper[i] = j;
        else if (helper[i] != -1) {
            int k = helper[i];
            if (P[k].second == P[j].second) {
                //helper[i];
            } else if (P[k].second > P[j].second) {
                helper[i] = j;
            }
        } else
            helper[i] = j;
    };
    auto getEdge = [&](int i) {
        if (i < 0) i += isz(P);
        if (i >= isz(P)) i -= isz(P);
        auto L = P[i], R = getNext(P, i);
        auto [ymin, ymax] = std::minmax({L.second, R.second});
        return tiii(ymin, ymax, i);
    };
    auto getEdgeId = [&](int i) {
        auto [y1,y2,j] = getEdge(i);
        if (y1 == y2) return -1;
        return j;
    };
    
    int cachedId = -1;
    ld cachedX = -1;
    auto isCached = [&](int id) { return id == cachedId; };
    auto setCached = [&](int id, ld x) { cachedId = id; cachedX = x; };
    auto clearCached = [&](){cachedId = -1; cachedX = -1;};
    
    auto coordOfIntersection = [&](int i, int y) -> ld {
        if (i < 0) i += isz(P);
        if (isCached(i))
            return cachedX;
        assert(0 <= i && i < isz(P));
        auto [x1,y1] = P[i];
        auto [x2,y2] = getNext(P, i);
        //ld B = ld(x2-x1)/(y2-y1);
        //ld A = x1 - y1 * B;
        // x1 - y1 * (x2-x1)/(y2-y1)
        // x1 - y1 * (x2-x1)/(y2-y1) + y * (x2-x1)/(y2-y1)
        // (x1 * (y2 - y1) + (y - y1) * (x2 - x1)) / (y2 - y1)
        // (x1 * y2 + y * x2 - y * x1 - y1 * x2) / (y2 - y1)
        assert(y2 != y1);
        return ld((ld)x1 * y2 + (ld)y * x2 - (ld)y * x1 - (ld)y1 * x2) / (y2 - y1);
    };
    auto LessByIntersection = [&](const int &j1, const int &j2) {
        ld x1 = coordOfIntersection(j1, currY);
        ld x2 = coordOfIntersection(j2, currY);
        if (x1 > x2) return false;
        if (x1 < x2) return true;
        return j1 < j2;
    };
    // y1 + t * (y2-y1) = y => t = (y - y1)/(y2 - y1)
    // x1 + t * (x2-x1) = x => x1 + (y - y1) * (x2-x1) / (y2 - y1)
    // coeff = (x2 - x1) / (y2 - y1)
    // x1 + (y - y1) * coeff <= x
    // x1 - y1 * coeff + y * coeff <= x
    // A + y * B <= x -- по этим значениям всегда упорядоченность
    std::set<int, decltype(LessByIntersection)> T(LessByIntersection);
    
    auto insertEdgeInT = [&](int i) {
        int ei = getEdgeId(i);
        if (ei == -1) return;
        auto y = P[i].second;
        setCurrY(y);
        setCached(ei, coordOfIntersection(ei, currY));
        T.insert(ei);
        clearCached();
    };
    auto deleteEdgeFromT = [&](int i) {
        int j = getEdgeId(i);
        if (j == -1) return;
        auto it = T.find(j);
        assert(it != T.end());
        T.erase(it);
    };
    
    auto searchEdgeInT = [&](int i) {
        assert(0 <= i && i < isz(P));
        const auto [x, y] = P[i];
        setCurrY(y); setCurrX(x);
        int cand;
        setCached(isz(P), x);
        auto it = T.upper_bound(isz(P));
        assert(it != T.begin());
        cand = *std::prev(it);
        clearCached();
        return cand;
    };
    vpii diagonals;
    auto addEdgeInTriangles = [&](int u, int v) {
        if (getNext(P, u) != P[v] && getPrev(P, u) != P[v])
            diagonals.emplace_back(u,v);
    };
    for (auto [y,x,i] : pq) {
        x *= -1;
        setCurrY(y);
        switch (getTypeOfVertex(P,i)) {
            case START: {
                insertEdgeInT(i);
                setHelper(i, i);
                break;
            }
            case END: {
                addEdgeInTriangles(i, getHelper(i-1));
                deleteEdgeFromT(i-1);
                break;
            }
            case SPLIT: {
                int j = searchEdgeInT(i);
                addEdgeInTriangles(i, getHelper(j));
                setHelper(j, i);
                insertEdgeInT(i);
                setHelper(i, i);
                break;
            }
            case MERGE: {
                addEdgeInTriangles(i, getHelper(i-1));
                deleteEdgeFromT(i-1);
                int j = searchEdgeInT(i);
                addEdgeInTriangles(i, getHelper(j));
                setHelper(j, i);
                break;
            }
            case REGULAR: {
                if (liesAbove(getPrev(P,i), P[i]) && liesBelow(getNext(P,i), P[i])) {
                    addEdgeInTriangles(i, getHelper(i-1));
                    deleteEdgeFromT(i-1);
                    insertEdgeInT(i);
                    setHelper(i, i);
                } else {
                    int j = searchEdgeInT(i);
                    addEdgeInTriangles(i, getHelper(j));
                    setHelper(j, i);
                }
                break;
            }
        };
    }
    return diagonals;
}

struct Node {
    const vpii * parent = nullptr;
    Node * next = nullptr;
    Node * prev = nullptr;
    int where{}, id{};
    std::list<int> diagonals{};
    
    void setNext(Node *n) {
        next = n;
        n->prev = this;
    }
    void setPrev(Node *n) {
        prev = n;
        n->next = this;
    }
    vpii to_vector() const {
        vpii result(1, (*parent)[id]);
        for (Node *it = next; it != this; it = it->next)
            result.push_back((*parent)[it->id]);
        return result;
    }
    pii to_point() const {
        return (*parent)[id];
    }
};

inline std::ostream &operator<<(std::ostream &os, const Node * node) {
    return os << "(node #" << node->id+1 << " in list " << node->where << ")";
}

template<typename Func>
inline void splitByDiag(const vpii &P, const vpii &D, const Func &f) {
    if (isz(P) <= 2)
        return;
    if (isz(P) == 3) {
        assert(D.empty());
        f(P);
        return;
    }
    static std::vector<Node *> nodes;
    nodes.clear();
    for (int i = 0; i < isz(P); i++)
        nodes.emplace_back(new Node{&P, nullptr, nullptr, 0, i, {}});
    for (int i = 0; i+1 < isz(nodes); i++)
        nodes[i]->setNext(nodes[i+1]);
    nodes.front()->setPrev(nodes.back());
    static std::vector<std::pair<Node*, Node*>> diagonals;
    diagonals.clear();
    for (const auto &[u,v] : D) {
        assert(0 <= u && u < isz(nodes));
        assert(0 <= v && v < isz(nodes));
        int currDiag = isz(diagonals);
        diagonals.push_back({nodes[u], nodes[v]});
        nodes[u]->diagonals.push_back(currDiag);
        nodes[v]->diagonals.push_back(currDiag);
    }

    int cntPoly = 1;
    for (int id = 0; id < isz(diagonals); id++) {
        // будем делить относительно этой диагонали
        auto [startFi, startSe] = diagonals[id];
        auto currFi = startFi, currSe = startSe;
        while (currFi != startSe && currSe != startFi) {
            currFi = currFi->next;
            currSe = currSe->next;
        }
        // нужно скопировать две вершины
        nodes.push_back(new Node{&P, nullptr, nullptr, cntPoly, startFi->id, {}});
        Node *copyFi = nodes.back();
        nodes.push_back(new Node{&P, nullptr, nullptr, cntPoly, startSe->id, {}});
        Node *copySe = nodes.back();
        // выбираем список минимальной длины:
        if (currFi != startSe) {
            std::swap(copyFi, copySe);
            std::swap(startFi, startSe);
            std::swap(currFi, currSe);
        }
        assert(currFi == startSe);
        // проходим каждую вершину
        for (currFi = currFi->prev; currFi != startFi; currFi = currFi->prev) {
            auto &dd = currFi->diagonals;
            for (auto it = dd.begin(); it != dd.end(); ) {
                // валидная диагональ или нет?
                if (*it <= id) {
                    it = dd.erase(it);
                    continue;
                }
                auto &[lhs, rhs] = diagonals[*it];
                if (lhs == startFi) (lhs = copyFi)->diagonals.push_back(*it);
                if (rhs == startFi) (rhs = copyFi)->diagonals.push_back(*it);
                if (lhs == startSe) (lhs = copySe)->diagonals.push_back(*it);
                if (rhs == startSe) (rhs = copySe)->diagonals.push_back(*it);
                it = std::next(it);
            }
            // отмечаем где они теперь лежат:
            currFi->where = cntPoly;
        }
        // отсоединяем меньшую половину:
        copyFi->setNext(currFi->next);
        copySe->next = copyFi;
        copySe->setNext(copyFi);
        startSe->prev->setNext(copySe);
        startFi->setNext(startSe);
        cntPoly++;
    }
    static std::vector<Node *> anyNode;
    anyNode.resize(cntPoly);
    for (auto it : nodes)
        anyNode[it->where] = it;
    for (int i = 0; i < cntPoly; i++) {
        vpii temp = anyNode[i]->to_vector();
        removeSameLine(temp);
        //assert(isMonotone(temp));
        f(temp);
    }
    for (auto node : nodes)
        delete node;
}

inline vvpii splitByDiag(const vpii &P, const vpii &D) {
    vvpii result;
    splitByDiag(P, D, [&](const vpii &PP){ result.push_back(PP); });
    return result;
}

inline vpii TriangulateMonotonePolygon(const vpii &P) {
    // we need to create chains
    // удалим точки, лежащие на одной прямой
    if (isz(P) <= 3)
        return {};
    int ymax = INT_MIN, ymin = INT_MAX, imax = -1;
    int leftChainBegin = -1, leftChainEnd = -1;
    for (int i = 0; i < isz(P); i++) {
        if (P[i].second >= ymax) {
            imax = i;
            ymax = P[i].second;
        }
        if (P[i].second == ymax && getNext(P, i).second != ymax) {
            leftChainBegin = i;
        }
        remin(ymin, P[i].second);
    }
    
    const int LEFT_CHAIN = 0,  RIGHT_CHAIN = 1;
    assert(imax != -1);
    static vi chainType; chainType.assign(isz(P), -1);
    static vi chainPos; chainPos.assign(isz(P), -1);
    assert(leftChainBegin != -1);
    leftChainEnd = leftChainBegin;
    int pos = 0;
    while (!(P[leftChainEnd].second == ymin && getPrev(P, leftChainEnd).second != ymin)) {
        chainType[leftChainEnd] = LEFT_CHAIN;
        chainPos[leftChainEnd] = pos++;
        leftChainEnd++;
        if (leftChainEnd == isz(P))
            leftChainEnd = 0;
    }
    chainType[leftChainEnd] = LEFT_CHAIN;
    if (chainPos[leftChainEnd] == -1)
        chainPos[leftChainEnd] = pos++;
    pos = 0;
    for (int i = (leftChainBegin-1+isz(P)) % isz(P); chainType[i] == -1; ) {
        chainType[i] = RIGHT_CHAIN;
        chainPos[i] = pos++;
        i--;
        if (i < 0) i = isz(P)-1;
    }
    // {y, цепочка, позиция в этой цепочке}
    auto cmp = [&](pii a, pii b) {
        auto [ya, ida] = a;
        auto [yb, idb] = b;
        if (ya < yb) return true;
        if (ya > yb) return false;
        if (chainType[ida] != chainType[idb]) {
            return chainType[ida] < chainType[idb];
        }
        return chainPos[ida] > chainPos[idb];
    };
    static vpii pq;
    pq.clear();
    for (int i = 0; i < isz(P); i++) {
        auto [x,y] = P[i];
        pq.push_back({y,i});
    }
    std::sort(pq.rbegin(), pq.rend(), cmp);
    static vi S;
    S.clear();
    S.push_back(std::get<1>(pq[0]));
    S.push_back(std::get<1>(pq[1]));
    
    vpii diagonals;
    auto addDiagonal = [&](int i, int j) {
        if (getNext(P, i) != P[j] && getPrev(P, i) != P[j]) {
            diagonals.emplace_back(i, j);
            return true;
        }
        return false;
    };
    auto isSameChain = [&](int i, int j) {
        return chainType[i] == chainType[j];
    };
    
    for (const auto &[y, id] : pq) {
        if (!isSameChain(id,S.back())) {
            int last = S.back();
            while (isz(S) > 1) {
                addDiagonal(id, S.back());
                S.pop_back();
            }
            S = {last, id};
        } else {
            int want = LEFT, skip = RIGHT;
            if (chainType[id] == LEFT_CHAIN)
                std::swap(want, skip);
            pii first = P[id];
            while (isz(S) >= 2) {
                pii mid = P[S[isz(S)-1]];
                pii last = P[S[isz(S)-2]];
                ll rot = rotation(first, mid, last);
                if (rot == skip)
                    break;
                if (rot != want) {
                    S.pop_back();
                    continue;
                }
                assert(rot == want);
                addDiagonal(id, S[isz(S)-2]);
                S.pop_back();
            }
            S.push_back(id);
        }
    }
    return diagonals;
}

template<typename Func>
inline void triangulateFast(vpii inP, const Func &f) {
    ll fullSquare = orientedSquare(inP);
    removeSameLine(inP);
    vpii D = findDiagonals(inP);
    splitByDiag(inP, D, [&](vpii PP){
        removeSameLine(PP);
        vpii DD = TriangulateMonotonePolygon(PP);
        auto ff = [&](const vpii &t){
            fullSquare -= orientedSquare(t);
            f(t);
        };
        splitByDiag(PP, DD, ff);
    });
    assert(fullSquare == 0);
}

inline std::vector<Triangle> triangulateFast(const vpii &inP) {
    std::vector<Triangle> answ;
    triangulateFast(inP, [&](const vpii &t){
        assert(isz(t) <= 3);
        if (isz(t) == 3) answ.emplace_back(t[0], t[1], t[2]);
    });
    return answ;
}

inline std::vector<Triangle> triangulateSlow(const vpii &points)
{
// ушная триангуляция за O(n^2)
    std::vector<Triangle> triangles;
    std::list<pii> list(all(points));
    while (isz(list) > 3) {
        // ищем вершину, являющуюся ухом
        for (auto it = list.begin(); it != list.end(); ) {
            auto next = (std::next(it) == list.end() ? list.begin() : std::next(it));
            auto prev = (it == list.begin() ? std::prev(list.end()) : std::prev(it));
            ll rot = rotation(*prev, *it, *next);
            if (rot == 0) {
                it = list.erase(it);
            } else if (rot < 0) {
                // проверим на ухо
                bool ok = true;
                for (auto p : list) {
                    bool bad = isPointInsideTriangle({*prev, *it, *next}, p);
                    bad = bad && !isPointOnSegment(p, *prev, *it);
                    bad = bad && !isPointOnSegment(p, *it, *next);
                    bad = bad && !isPointOnSegment(p, *prev, *next);
                    if (bad) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    triangles.emplace_back(*prev, *it, *next);
                    it = list.erase(it);
                } else {
                    it++;
                }
            } else {
                it++;
            }
        }
    }
    if (isz(list) == 3)
        triangles.emplace_back(*list.begin(), *(++list.begin()), *(++++list.begin()));
    else assert(isz(list) < 3);
    return triangles;
}

inline std::vector<Triangle> triangulateConvex(const vpii &points) {
// на вход подаётся выпуклый многоугольник
// берём любую точку и проводим для неё стороны
    std::vector<Triangle> triangles;
    for (int i = 1; i + 1 < isz(points); i++)
        triangles.emplace_back(points[0], points[i], points[i+1]);
    return triangles;
}

inline std::vector<Triangle> triangulate(vpii points) {
    makeCounterClockwise(points);
    return triangulateFast(points);
}

} // namespace triangulate
} // namespace algos
#endif // __TRIANGULATE_HPP__