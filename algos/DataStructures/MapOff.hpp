#ifndef __MAPOFF_HPP__
#define __MAPOFF_HPP__
#include <memory>
template<typename Key, typename Val>
struct MapOff {

    std::vector<Key> keys;
    std::vector<Val> vals;
    
    struct Iterator {
        typedef std::random_access_iterator_tag iterator_category;
        int pos{};
        std::vector<Key> *keys{};
        std::vector<Val> *vals{};
        Iterator &operator++() { return (++pos, *this); }
        Iterator operator++(int) { Iterator ret(*this); ++(*this); return ret; }
        Iterator &operator--() { return (--pos, *this); }
        Iterator operator--(int) { Iterator ret(*this); --(*this); return ret; }
        const Key & first() const { return (*keys)[pos]; }
        const Val & second() const { return (*keys)[pos]; }
        Val & second() { return (*vals)[pos]; }
        auto operator*() {
            return std::pair<const Key &, Val &>((*keys)[pos], (*vals)[pos]);
        }
        auto operator*() const {
            return std::pair<const Key &, const Val &>((*keys)[pos], (*vals)[pos]);
        }
        auto operator->() {
            return std::make_unique<std::pair<const Key &, Val &>>
                ((*keys)[pos], (*vals)[pos]); }
        auto operator->() const {
            return std::make_unique<std::pair<const Key &, const Val &>>
                ((*keys)[pos], (*vals)[pos]); }
        bool operator<(const Iterator & other) const {
            return pos < other.pos;
        }
        GEN_COMPARATORS_MEMBERS(Iterator)
    };
    
    
    struct ReverseIterator {
        typedef std::random_access_iterator_tag iterator_category;
        int pos{};
        std::vector<Key> *keys{};
        std::vector<Val> *vals{};
        ReverseIterator &operator++() { return (--pos, *this); }
        ReverseIterator operator++(int) { ReverseIterator ret(*this); ++(*this); return ret; }
        ReverseIterator &operator--() { return (++pos, *this); }
        ReverseIterator operator--(int) { ReverseIterator ret(*this); --(*this); return ret; }
        const Key & first() const { return (*keys)[pos]; }
        const Val & second() const { return (*keys)[pos]; }
        Val & second() { return (*vals)[pos]; }
        auto operator*() {
            return std::pair<const Key &, Val &>((*keys)[pos], (*vals)[pos]);
        }
        auto operator*() const {
            return std::pair<const Key &, const Val &>((*keys)[pos], (*vals)[pos]);
        }
        auto operator->() {
            return std::make_unique<std::pair<const Key &, Val &>>
                ((*keys)[pos], (*vals)[pos]); }
        auto operator->() const {
            return std::make_unique<std::pair<const Key &, const Val &>>
                ((*keys)[pos], (*vals)[pos]); }
        bool operator<(const ReverseIterator & other) const { return pos > other.pos; }
        GEN_COMPARATORS_MEMBERS(ReverseIterator)
    };
    
    Iterator begin() { return Iterator{0,&keys,&vals}; }
    Iterator end() { return Iterator{(int)keys.size(),&keys,&vals}; }
    ReverseIterator rbegin() { return ReverseIterator{(int)keys.size()-1,&keys,&vals}; }
    ReverseIterator rend() { return ReverseIterator{-1,&keys,&vals}; }
    
    void add_key(const auto & ... key) {
        (keys.push_back(key),...);
    }

    void build() {
        std::sort(keys.begin(), keys.end());
        keys.erase(std::unique(keys.begin(),keys.end()),keys.end());
        vals.assign(keys.size(), Val{});
    }

    int findIndex(const Key &key) {
        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        return int(it - keys.begin());
    }

    Val &operator[](const Key &key) {
        return vals[findIndex(key)];
    }
    
    const Val &operator[](const Key &key) const {
        return vals[findIndex(key)];
    }
    
};
#endif // __MAPOFF_HPP__