#ifndef __GROUPEDSEGMENTTREE_HPP__
#define __GROUPEDSEGMENTTREE_HPP__
/*******************************************************************************************
 * File "GroupedSegmentTree.hpp" is a part of competitive programming C++ library "algos". *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include <algorithm>
#include <cassert>
#include <vector>
namespace algos {
namespace GroupedSegmentTree {
/**
 * A decomposition of an array into consecutive groups with a segment tree built over group
 * aggregates. GroupTraits must provide:
 *
 * - static GroupType neutral();
 * - static void merge(GroupType &dst, const GroupType &lhs, const GroupType &rhs);
 * - static GroupType build(const std::vector<ItemType> &items,int begin,int end);
 *
 * `build` receives a half-interval [begin, end).
 *
 * SegmentTreeType must provide:
 *
 *     void build(const std::vector<GroupType> &groups);
 *     void update(int pos, GroupType value);
 *     GroupType get(int left, int right) const;
 *
 * The tree query uses an inclusive group interval [left, right].
 *
 * Aggregation order is preserved, so non-commutative operations are
 * supported if the underlying segment tree supports them.
 */
template<typename ItemType, typename GroupType, typename GroupTraits,
         typename SegmentTreeType>
struct GroupedSegmentTree {
    int n = 0;
    int groupSize = 1;
    int nGroups = 0;
    std::vector<ItemType> items;
    SegmentTreeType tree;
    GroupedSegmentTree() = default;
    GroupedSegmentTree(const std::vector<ItemType> &items_, int groupSize_) {
        build(items_,groupSize_);
    }
    int groupIndex(int pos) const {
        assert(0 <= pos && pos < n);
        return pos/groupSize;
    }
    int groupBegin(int gi) const {
        assert(0 <= gi && gi <= nGroups);
        return gi*groupSize;
    }
    int groupEnd(int gi) const {
        assert(0 <= gi && gi < nGroups);
        return std::min(groupBegin(gi)+groupSize,n);
    }
    int groupEndByPosition(int pos) const {
        return groupEnd(groupIndex(pos));
    }
    GroupType buildGroup(int gi) const {
        assert(0 <= gi && gi < nGroups);
        return GroupTraits::build(items,groupBegin(gi),groupEnd(gi));
    }
    void build(const std::vector<ItemType> &items_, int groupSize_) {
        assert(!items_.empty());
        assert(groupSize_ > 0);
        items = items_;
        n = (int)items.size();
        groupSize = groupSize_;
        nGroups = (n+groupSize-1)/groupSize;
        std::vector<GroupType> groups(nGroups,GroupTraits::neutral());
        for (int gi = 0; gi < nGroups; gi++)
            groups[gi] = buildGroup(gi);
        tree.build(groups);
    }
    void rebuildGroup(int gi) {
        assert(0 <= gi && gi < nGroups);
        tree.update(gi,buildGroup(gi));
    }
    void rebuild(int pos) {
        rebuildGroup(groupIndex(pos));
    }
    void update(int pos, const ItemType &value) {
        assert(0 <= pos && pos < n);
        items[pos] = value;
        rebuild(pos);
    }
    template<typename Function>
    void modify(int pos, Function function) {
        assert(0 <= pos && pos < n);
        function(items[pos]);
        rebuild(pos);
    }
    ItemType &operator[](int pos) {
        assert(0 <= pos && pos < n);
        return items[pos];
    }
    const ItemType &operator[](int pos) const {
        assert(0 <= pos && pos < n);
        return items[pos];
    }
    GroupType getGroups(int gl, int gr) const {
        assert(0 <= gl && gl < gr && gr <= nGroups);
        return tree.get(gl,gr-1);
    }
    GroupType getGroupsInclusive(int gl, int gr) const {
        assert(0 <= gl && gl <= gr && gr < nGroups);
        return tree.get(gl,gr);
    }
    struct RangeParts {
        int leftBegin, leftEnd;
        int groupsBegin, groupsEnd;
        int rightBegin, rightEnd;
    };
    RangeParts splitRange(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        int leftEnd = std::min(r,((l+groupSize-1)/groupSize)*groupSize);
        int rightBegin = std::max(leftEnd,(r/groupSize)*groupSize);
        return {l, leftEnd,leftEnd/groupSize,rightBegin/groupSize,rightBegin,r};
    }
};
} // namespace GroupedSegmentTree
} // namespace algos
#endif // __GROUPEDSEGMENTTREE_HPP__