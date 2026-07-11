from ordered_set_treap import OrderedSet


def print_set(name, s):
    print(f"{name} = {{{','.join(map(str, s))}}}")


s = OrderedSet()
for x in [6, 1, 1, 7, 7, 5, 4, 4, 2]:
    s.insert(x)

print_set("s", s)
print("size =", s.size())
print("empty =", s.empty())
print("count(7) =", s.count(7))
print("count(3) =", s.count(3))
print("find(6) =", s.find(6))
print("find(3) =", s.find(3))
print("lower_bound(3) =", s.lower_bound(3))
print("upper_bound(5) =", s.upper_bound(5))
print("find_by_order(0) =", s.find_by_order(0))
print("find_by_order(3) =", s.find_by_order(3))
print("s[4] =", s[4])
print("order_of_key(5) =", s.order_of_key(5))
print("erase(4) =", s.erase(4))
print_set("s", s)
print("erase(4) =", s.erase(4))
print_set("s", s)
print("insert(3) =", s.insert(3))
print("insert(3) =", s.insert(3))
print_set("s", s)