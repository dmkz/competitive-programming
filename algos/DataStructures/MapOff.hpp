#ifndef __MAPOFF_HPP__
#define __MAPOFF_HPP__
#include <memory>
template<typename Key, typename Val>
struct MapOff {

    std::vector<Key> keys;
    std::vector<Val> vals;
    
    bool built{true}; // empty map is built
    bool isBuilt() const { return built; }
    
    int size() const { return (int)keys.size(); }
    
    struct Iterator {
        int pos{};
        std::vector<Key> *keys{};
        std::vector<Val> *vals{};
        Key& default_key() const { static Key def{}; return def; }
        Val& default_val() const { static Val def{}; return def; }
        using KeyRefWrap = std::reference_wrapper<Key>;
        using ValRefWrap = std::reference_wrapper<Val>;
        using RefWrap = std::pair<KeyRefWrap, ValRefWrap>;
        RefWrap pr = std::make_pair(std::ref(default_key()), std::ref(default_val()));
        Iterator &operator++() { return (++pos, *this); }
        Iterator operator++(int) { Iterator ret(*this); ++(*this); return ret; }
        Iterator &operator--() { return (--pos, *this); }
        Iterator operator--(int) { Iterator ret(*this); --(*this); return ret; }
        std::pair<const Key&, const Val&> operator*() const {
            #ifdef _GLIBCXX_DEBUG
                assert(keys != nullptr && "Vector with Keys must to be passed!");
                assert(vals != nullptr && "Vector with Vals must to be passed!");
                assert(0 <= pos && pos < (int)keys->size() &&
                       "The Iterator must to be valid!");
            #endif
            return std::pair<const Key&, const Val&>( (*keys)[pos], (*vals)[pos]);
        }
        RefWrap &operator*() {
            #ifdef _GLIBCXX_DEBUG
                assert(keys != nullptr && "Vector with Keys must to be passed!");
                assert(vals != nullptr && "Vector with Vals must to be passed!");
                assert(0 <= pos && pos < (int)keys->size() &&
                       "The Iterator must to be valid!");
            #endif
            return pr = {std::ref((*keys)[pos]), std::ref((*vals)[pos])};
        }
        RefWrap *operator->() { return &(this->operator*()); }
        std::pair<const Key&, const Val&>* operator->() const { return &(this->operator*()); }
        bool operator<(const Iterator & other) const {
            return pos < other.pos;
        }
        GEN_COMPARATORS_MEMBERS(Iterator)
    };
    
    struct ReverseIterator {
        int pos{};
        std::vector<Key> *keys{};
        std::vector<Val> *vals{};
        Key& default_key() const { static Key def{}; return def; }
        Val& default_val() const { static Val def{}; return def; }
        using KeyRefWrap = std::reference_wrapper<Key>;
        using ValRefWrap = std::reference_wrapper<Val>;
        using RefWrap = std::pair<KeyRefWrap, ValRefWrap>;
        RefWrap pr = std::make_pair(std::ref(default_key()), std::ref(default_val()));
        ReverseIterator &operator++() { return (--pos, *this); }
        ReverseIterator operator++(int) { ReverseIterator ret(*this); ++(*this); return ret; }
        ReverseIterator &operator--() { return (++pos, *this); }
        ReverseIterator operator--(int) { ReverseIterator ret(*this); --(*this); return ret; }
        std::pair<const Key&, const Val&> operator*() const {
            #ifdef _GLIBCXX_DEBUG
                assert(keys != nullptr && "Vector with Keys have to be passed!");
                assert(vals != nullptr && "Vector with Vals have to be passed!");
                assert(0 <= pos && pos < (int)keys->size() &&
                       "The ReverseIterator must to be valid!");
            #endif
            return std::pair<const Key&, const Val&>( (*keys)[pos], (*vals)[pos]);
        }
        RefWrap &operator*() {
            #ifdef _GLIBCXX_DEBUG
                assert(keys != nullptr && "Vector with Keys must to be passed!");
                assert(vals != nullptr && "Vector with Vals must to be passed!");
                assert(0 <= pos && pos < (int)keys->size() &&
                       "The ReverseIterator must to be valid!");
            #endif
            return pr = {std::ref((*keys)[pos]), std::ref((*vals)[pos])};
        }
        RefWrap *operator->() { return &(this->operator*()); }
        std::pair<const Key&, const Val&>* operator->() const { return &(this->operator*()); }
        bool operator<(const ReverseIterator & other) const { return pos > other.pos; }
        GEN_COMPARATORS_MEMBERS(ReverseIterator)
    };
    
    Iterator begin() { return Iterator{0,&keys,&vals}; }
    Iterator end() { return Iterator{(int)keys.size(),&keys,&vals}; }
    ReverseIterator rbegin() { return ReverseIterator{(int)keys.size()-1,&keys,&vals}; }
    ReverseIterator rend() { return ReverseIterator{-1,&keys,&vals}; }
    
    void add_key(const auto & ... key) {
        built = false;
        (keys.push_back(key),...);
    }

    void build() {
        std::sort(keys.begin(), keys.end());
        keys.erase(std::unique(keys.begin(),keys.end()),keys.end());
        vals.assign(keys.size(), Val{});
        built = true;
    }

    int findIndex(const Key &key) {
        #ifdef _GLIBCXX_DEBUG
            assert( built && "The MapOff must be built when you use findIndex!" );
        #endif
        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        return int(it - keys.begin());
    }

    Val &operator[](const Key &key) {
        int index = findIndex(key);
        #ifdef _GLIBCXX_DEBUG
            assert( index < size() && keys[index] == key && "Key must to exist!" );
        #endif
        return vals[index];
    }
    
    const Val &operator[](const Key &key) const {
        int index = findIndex(key);
        #ifdef _GLIBCXX_DEBUG
            assert( index < size() && keys[index] == key && "Key must to exist!" );
        #endif
        return vals[index];
    }
    
};
#endif // __MAPOFF_HPP__