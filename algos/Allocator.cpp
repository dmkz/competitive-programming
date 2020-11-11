namespace Memory {
    char buf[150*1024*1024];
    uint64_t ptr{0};
    void* malloc(uint64_t cnt) {
        ptr+=cnt;
        assert(ptr<sizeof(buf));
        return (void*)(buf+ptr-cnt);
    }
}
 
template <class T>
struct Allocator {
    using value_type = T;
    Allocator () = default;
    template <class U> constexpr Allocator (const Allocator <U>&) noexcept {}
    T* allocate(std::size_t n) { return (T*)(Memory::malloc(n*sizeof(T))); }
    void deallocate(T*, std::size_t) noexcept { }
};
 
template <class T, class U> bool operator==(const Allocator<T>&, const Allocator<U>&) { return true; }
template <class T, class U> bool operator!=(const Allocator<T>&, const Allocator<U>&) { return false; }
 
template<class T>
using Vec = std::vector<T,Allocator<T>>;
template<class T>
using List = std::list<T,Allocator<T>>;
template<class T, class C = std::less<T>>
using Set = std::set<T,C,Allocator<T>>;
template<class K, class V, class C = std::less<K>>
using Map = std::map<K,V,C,Allocator<std::pair<const K, V>>>;