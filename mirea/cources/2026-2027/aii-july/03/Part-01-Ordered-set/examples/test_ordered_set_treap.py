import argparse
import random
from concurrent.futures import ThreadPoolExecutor, as_completed

from ordered_set_treap import OrderedSet


def assert_tree(node, low=None, high=None):
    if node is None:
        return 0
    if low is not None:
        assert low < node.key
    if high is not None:
        assert node.key < high
    if node.left is not None:
        assert node.prior >= node.left.prior
    if node.right is not None:
        assert node.prior >= node.right.prior
    left_size = assert_tree(node.left, low, node.key)
    right_size = assert_tree(node.right, node.key, high)
    assert node.size == 1 + left_size + right_size
    return node.size


def assert_matches(ordered_set, expected):
    assert list(ordered_set) == expected
    assert len(ordered_set) == len(expected)
    assert ordered_set.size() == len(expected)
    assert ordered_set.empty() == (len(expected) == 0)
    assert bool(ordered_set) == (len(expected) > 0)
    assert_tree(ordered_set.root)


def test_init_and_iter():
    random.seed(1)
    ordered_set = OrderedSet([6, 1, 1, 7, 7, 5, 4, 4, 2])
    assert_matches(ordered_set, [1, 2, 4, 5, 6, 7])


def test_len_size_empty_bool():
    random.seed(2)
    ordered_set = OrderedSet()
    assert ordered_set.empty() is True
    assert bool(ordered_set) is False
    ordered_set.insert(10)
    ordered_set.insert(3)
    assert len(ordered_set) == 2
    assert ordered_set.size() == 2
    assert ordered_set.empty() is False
    assert bool(ordered_set) is True
    assert_matches(ordered_set, [3, 10])


def test_contains_and_count():
    random.seed(3)
    ordered_set = OrderedSet([5, 1, 9])
    assert 5 in ordered_set
    assert 4 not in ordered_set
    assert ordered_set.count(5) == 1
    assert ordered_set.count(4) == 0
    assert_matches(ordered_set, [1, 5, 9])


def test_find_returns_position_or_none():
    random.seed(4)
    ordered_set = OrderedSet([6, 1, 1, 7, 7, 5, 4, 4, 2])
    assert ordered_set.find(1) == 0
    assert ordered_set.find(4) == 2
    assert ordered_set.find(6) == 4
    assert ordered_set.find(3) is None
    assert_matches(ordered_set, [1, 2, 4, 5, 6, 7])


def test_insert():
    random.seed(5)
    ordered_set = OrderedSet()
    assert ordered_set.insert(5) is True
    assert ordered_set.insert(1) is True
    assert ordered_set.insert(5) is False
    assert ordered_set.insert(3) is True
    assert_matches(ordered_set, [1, 3, 5])


def test_erase():
    random.seed(6)
    ordered_set = OrderedSet([1, 3, 5, 7])
    assert ordered_set.erase(3) is True
    assert ordered_set.erase(3) is False
    assert ordered_set.erase(8) is False
    assert ordered_set.erase(1) is True
    assert_matches(ordered_set, [5, 7])


def test_lower_bound():
    random.seed(7)
    ordered_set = OrderedSet([1, 4, 6, 9])
    assert ordered_set.lower_bound(0) == 1
    assert ordered_set.lower_bound(4) == 4
    assert ordered_set.lower_bound(5) == 6
    assert ordered_set.lower_bound(10) is None
    assert_matches(ordered_set, [1, 4, 6, 9])


def test_upper_bound():
    random.seed(8)
    ordered_set = OrderedSet([1, 4, 6, 9])
    assert ordered_set.upper_bound(0) == 1
    assert ordered_set.upper_bound(4) == 6
    assert ordered_set.upper_bound(8) == 9
    assert ordered_set.upper_bound(9) is None
    assert_matches(ordered_set, [1, 4, 6, 9])


def test_find_by_order():
    random.seed(9)
    ordered_set = OrderedSet([8, 2, 5, 1])
    assert ordered_set.find_by_order(0) == 1
    assert ordered_set.find_by_order(2) == 5
    assert ordered_set.find_by_order(3) == 8
    assert ordered_set.find_by_order(4) is None
    assert ordered_set.find_by_order(-1) is None
    assert_matches(ordered_set, [1, 2, 5, 8])


def test_order_of_key():
    random.seed(10)
    ordered_set = OrderedSet([1, 4, 6, 9])
    assert ordered_set.order_of_key(0) == 0
    assert ordered_set.order_of_key(1) == 0
    assert ordered_set.order_of_key(5) == 2
    assert ordered_set.order_of_key(10) == 4
    assert_matches(ordered_set, [1, 4, 6, 9])


def test_getitem():
    random.seed(11)
    ordered_set = OrderedSet([8, 2, 5, 1])
    assert ordered_set[0] == 1
    assert ordered_set[1] == 2
    assert ordered_set[3] == 8
    try:
        ordered_set[4]
        raise AssertionError("IndexError was expected")
    except IndexError:
        pass
    assert_matches(ordered_set, [1, 2, 5, 8])


def test_randomized_against_sorted_list():
    random.seed(12)
    ordered_set = OrderedSet()
    expected = []
    values = set()
    for _ in range(400):
        op = random.choice(
            [
                "insert",
                "erase",
                "count",
                "find",
                "lower_bound",
                "upper_bound",
                "find_by_order",
                "order_of_key",
            ]
        )
        x = random.randint(0, 30)
        if op == "insert":
            result = ordered_set.insert(x)
            expected_result = x not in values
            if expected_result:
                values.add(x)
                expected.append(x)
                expected.sort()
            assert result == expected_result
        elif op == "erase":
            result = ordered_set.erase(x)
            expected_result = x in values
            if expected_result:
                values.remove(x)
                expected.remove(x)
            assert result == expected_result
        elif op == "count":
            assert ordered_set.count(x) == (1 if x in values else 0)
        elif op == "find":
            expected_result = expected.index(x) if x in values else None
            assert ordered_set.find(x) == expected_result
        elif op == "lower_bound":
            expected_result = next((v for v in expected if v >= x), None)
            assert ordered_set.lower_bound(x) == expected_result
        elif op == "upper_bound":
            expected_result = next((v for v in expected if v > x), None)
            assert ordered_set.upper_bound(x) == expected_result
        elif op == "find_by_order":
            k = random.randint(-2, len(expected) + 2)
            expected_result = expected[k] if 0 <= k < len(expected) else None
            assert ordered_set.find_by_order(k) == expected_result
        elif op == "order_of_key":
            expected_result = sum(1 for v in expected if v < x)
            assert ordered_set.order_of_key(x) == expected_result
        assert_matches(ordered_set, expected)


TESTS = [
    test_init_and_iter,
    test_len_size_empty_bool,
    test_contains_and_count,
    test_find_returns_position_or_none,
    test_insert,
    test_erase,
    test_lower_bound,
    test_upper_bound,
    test_find_by_order,
    test_order_of_key,
    test_getitem,
    test_randomized_against_sorted_list,
]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--jobs", type=int, default=12)
    args = parser.parse_args()

    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        futures = {executor.submit(test): test.__name__ for test in TESTS}
        for future in as_completed(futures):
            name = futures[future]
            future.result()
            print(f"OK {name}")

    print(f"PASSED {len(TESTS)} tests")


if __name__ == "__main__":
    main()