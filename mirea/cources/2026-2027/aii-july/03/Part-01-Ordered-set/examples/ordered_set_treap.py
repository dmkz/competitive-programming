from random import randint


class OrderedSet:
    class _Node:
        __slots__ = ("key", "prior", "left", "right", "size")

        def __init__(self, key):
            self.key = key
            self.prior = randint(1, 1 << 30)
            self.left = None
            self.right = None
            self.size = 1

    def __init__(self, values=()):
        self.root = None
        for x in values:
            self.insert(x)

    @staticmethod
    def _size(node):
        return 0 if node is None else node.size

    @classmethod
    def _pull(cls, node):
        if node is not None:
            node.size = 1 + cls._size(node.left) + cls._size(node.right)
        return node

    @classmethod
    def _split(cls, node, x):
        if node is None:
            return None, None
        if node.key < x:
            left_part, right_part = cls._split(node.right, x)
            node.right = left_part
            return cls._pull(node), right_part
        left_part, right_part = cls._split(node.left, x)
        node.left = right_part
        return left_part, cls._pull(node)

    @classmethod
    def _merge(cls, left, right):
        if left is None:
            return right
        if right is None:
            return left
        if left.prior > right.prior:
            left.right = cls._merge(left.right, right)
            return cls._pull(left)
        right.left = cls._merge(left, right.left)
        return cls._pull(right)

    @classmethod
    def _erase(cls, node, x):
        if node is None:
            return None, False
        if x < node.key:
            node.left, erased = cls._erase(node.left, x)
            return cls._pull(node), erased
        if x > node.key:
            node.right, erased = cls._erase(node.right, x)
            return cls._pull(node), erased
        return cls._merge(node.left, node.right), True

    def __contains__(self, x):
        node = self.root
        while node is not None:
            if x < node.key:
                node = node.left
            elif x > node.key:
                node = node.right
            else:
                return True
        return False

    def __len__(self):
        return self._size(self.root)

    def __bool__(self):
        return self.root is not None

    def __iter__(self):
        stack = []
        node = self.root
        while stack or node is not None:
            while node is not None:
                stack.append(node)
                node = node.left
            node = stack.pop()
            yield node.key
            node = node.right

    def size(self):
        return len(self)

    def empty(self):
        return len(self) == 0

    def count(self, x):
        return 1 if x in self else 0

    def find(self, x):
        node = self.root
        answer = 0
        while node is not None:
            if x < node.key:
                node = node.left
            elif x > node.key:
                answer += self._size(node.left) + 1
                node = node.right
            else:
                return answer + self._size(node.left)
        return None

    def insert(self, x):
        if x in self:
            return False
        left, right = self._split(self.root, x)
        self.root = self._merge(self._merge(left, self._Node(x)), right)
        return True

    def erase(self, x):
        self.root, erased = self._erase(self.root, x)
        return erased

    def lower_bound(self, x):
        node = self.root
        answer = None
        while node is not None:
            if node.key >= x:
                answer = node.key
                node = node.left
            else:
                node = node.right
        return answer

    def upper_bound(self, x):
        node = self.root
        answer = None
        while node is not None:
            if node.key > x:
                answer = node.key
                node = node.left
            else:
                node = node.right
        return answer

    def find_by_order(self, k):
        if k < 0 or k >= len(self):
            return None
        node = self.root
        while node is not None:
            left_size = self._size(node.left)
            if k < left_size:
                node = node.left
            elif k == left_size:
                return node.key
            else:
                k -= left_size + 1
                node = node.right
        return None

    def order_of_key(self, x):
        node = self.root
        answer = 0
        while node is not None:
            if x <= node.key:
                node = node.left
            else:
                answer += self._size(node.left) + 1
                node = node.right
        return answer

    def __getitem__(self, k):
        value = self.find_by_order(k)
        if value is None:
            raise IndexError("OrderedSet index out of range")
        return value