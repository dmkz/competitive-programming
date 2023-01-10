#ifndef __ORDEREDSET_HPP__
#define __ORDEREDSET_HPP__
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template<typename T, typename Comp = std::less<T>>
using OrdTreeBase = __gnu_pbds::tree<T, __gnu_pbds::null_type, Comp,
                                     __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;


template<typename T, typename Comp = std::less<T>>
struct OrderedSet : public OrdTreeBase<T, Comp>
{
    using Base = OrdTreeBase<T, Comp>;
    
    OrderedSet(const auto &...pack)
        : Base(pack...) { }
    
    virtual size_t count_less(const T &key) const {
        return this->order_of_key(key);
    }
    
    virtual size_t count_less_equal(const T &key) const {
        return upper_bound_with_order(key).second;
    }
    
    virtual size_t count_greater(const T &key) const {
        return this->size() - count_less_equal(key);
    }
    
    virtual size_t count_equal(const T &key) const {
        return count_less_equal(key) - count_less(key);
    }
    
    virtual
    std::pair<typename Base::const_iterator, size_t>
    lower_bound_with_order(const T &key) const
    {
        auto prev = this->m_p_head;
        auto curr = this->m_p_head->m_p_parent;
        size_t order{};
        while (curr != 0)
            if (Comp()(curr->m_value, key)) {
                order += curr->m_metadata;
                if ((curr = curr->m_p_right))
                    order -= curr->m_metadata;
            } else {
                prev = curr;
                curr = curr->m_p_left;
            }
        return std::make_pair(prev, order);
    }
    
    virtual
    std::pair<typename Base::const_iterator, size_t>
    upper_bound_with_order(const T &key) const
    {
        auto prev = this->m_p_head;
        auto curr = this->m_p_head->m_p_parent;
        size_t order{};
        while (curr != 0)
            if (Comp()(key, curr->m_value)) {
                prev = curr;
                curr = curr->m_p_left;
            } else {
                order += curr->m_metadata;
                if ((curr = curr->m_p_right))
                    order -= curr->m_metadata;
            }
        return std::make_pair(prev, order);
    }
    
};

template<typename T, typename Comp = std::less_equal<T>>
struct OrderedMultiset
    : public OrderedSet<T, Comp>
{
    using Base = OrderedSet<T, Comp>;
    
    OrderedMultiset(const auto & ... pack) : Base(pack...) { }
    
    auto lower_bound(const T &key) const {
        return Base::upper_bound(key);
    }
    
    auto upper_bound(const T &key) const {
        return Base::lower_bound(key);
    }

    auto find(const T &key) const {
        if (auto it = lower_bound(key); it != this->end() && *it == key)
            return it;
        return this->end();
    }
    
    const auto erase(typename Base::iterator iter) {
        return Base::erase(iter);
    }
    
    const auto erase(const T &key) {
        auto it = lower_bound(key);
        while (it != this->end() && *it == key)
            it = Base::erase(it);
        return it;
    }
    
    std::pair<typename Base::const_iterator, size_t>
    lower_bound_with_order(const T &key) const override 
    {
        return Base::upper_bound_with_order(key);
    }
    
    std::pair<typename Base::const_iterator, size_t>
    upper_bound_with_order(const T &key) const override
    {
        return Base::lower_bound_with_order(key);
    }
    
    size_t count_less(const T &key) const override {
        return this->order_of_key(key);
    }
    
    size_t count_less_equal(const T &key) const override {
        return upper_bound_with_order(key).second;
    }
    
    size_t count_greater(const T &key) const override {
        return this->size() - count_less_equal(key);
    }
    
    size_t count_equal(const T &key) const override {
        return count_less_equal(key) - count_less(key);
    }
};
#endif // __ORDEREDSET_HPP__