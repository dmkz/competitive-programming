# Задача: D, Вердикт: OK, Время: 687 мс, Память: 84 МБ, Язык: PyPy 3-64

# -------------------------
# RedBlackTree
# -------------------------

"""Компактный RedBlackTree для задач на ordered set.

Использование:
- tree = RedBlackTree(values=())
  Создаёт дерево и по очереди вставляет все значения из values.
- tree.insert(x) -> bool
  Возвращает True, если x был вставлен, и False, если x уже был в дереве.
- tree.insert(x, with_id=True) -> (node_id, was_inserted)
  Возвращает идентификатор узла и флаг успешной вставки.
  Если x уже есть в дереве, node_id указывает на существующий узел,
  а was_inserted == False.
- tree.lower_bound_with_id(x) -> (value, node_id)
  Возвращает первый ключ >= x и его node_id.
  Если такого ключа нет, возвращает (None, 0).
- tree.lower_bound(x) -> value
  Возвращает первый ключ >= x или None.
- tree.lower_bound(x, with_id=True) -> (value, node_id)
  Возвращает тот же результат, что и lower_bound_with_id(x).
- tree.prev(node_id) -> (value, prev_node_id)
  Возвращает предыдущий ключ в inorder и его node_id.
  Если соседа слева нет, возвращает (None, 0).
- tree.next(node_id) -> (value, next_node_id)
  Возвращает следующий ключ в inorder и его node_id.
  Если соседа справа нет, возвращает (None, 0).
- tree.erase(x) -> ((next_value, next_node_id), was_erased)
  Удаляет ключ x, если он есть в дереве.
  Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
  Если x не найден, возвращает ((None, 0), False).
- tree.erase_id(node_id) -> ((next_value, next_node_id), was_erased)
    Удаляет узел по его node_id без дополнительной проверки.
    Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
- tree.erase_id(node_id, check=True) -> ((next_value, next_node_id), was_erased)
    Сначала проверяет, что node_id указывает на текущий узел дерева.
    Если проверка не прошла, возвращает ((None, 0), False).

Замечание:
- node_id стабилен после поворотов и следующих вставок, потому что узлы
  хранятся в массивах и не перемещаются.
"""


class RedBlackTree:
    __slots__ = ("root", "key", "left", "right", "parent", "color", "prev_id", "next_id")

    RED = 1
    BLACK = 0

    def __init__(self, values=()):
        self.root = 0
        self.key = [0]
        self.left = [0]
        self.right = [0]
        self.parent = [0]
        self.color = [self.BLACK]
        self.prev_id = [0]
        self.next_id = [0]
        for x in values:
            self.insert(x)

    def _new_node(self, x, color, pred, succ):
        self.key.append(x)
        self.left.append(0)
        self.right.append(0)
        self.parent.append(0)
        self.color.append(color)
        self.prev_id.append(pred)
        self.next_id.append(succ)
        node = len(self.key) - 1
        if pred:
            self.next_id[pred] = node
        if succ:
            self.prev_id[succ] = node
        return node

    def _rotate_left(self, node):
        right_node = self.right[node]
        self.right[node] = self.left[right_node]
        if self.left[right_node]:
            self.parent[self.left[right_node]] = node

        parent = self.parent[node]
        self.parent[right_node] = parent
        if parent == 0:
            self.root = right_node
        elif self.left[parent] == node:
            self.left[parent] = right_node
        else:
            self.right[parent] = right_node

        self.left[right_node] = node
        self.parent[node] = right_node

    def _rotate_right(self, node):
        left_node = self.left[node]
        self.left[node] = self.right[left_node]
        if self.right[left_node]:
            self.parent[self.right[left_node]] = node

        parent = self.parent[node]
        self.parent[left_node] = parent
        if parent == 0:
            self.root = left_node
        elif self.left[parent] == node:
            self.left[parent] = left_node
        else:
            self.right[parent] = left_node

        self.right[left_node] = node
        self.parent[node] = left_node

    def _fix_insert(self, node):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[parent[node]] == self.RED:
            parent_node = parent[node]
            grand = parent[parent_node]

            if parent_node == left[grand]:
                uncle = right[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == right[parent_node]:
                        node = parent_node
                        self._rotate_left(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_right(grand)
            else:
                uncle = left[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == left[parent_node]:
                        node = parent_node
                        self._rotate_right(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_left(grand)

        color[self.root] = self.BLACK

    def _find_node(self, x):
        node = self.root
        key = self.key
        left = self.left
        right = self.right

        while node:
            node_key = key[node]
            if x < node_key:
                node = left[node]
            elif x > node_key:
                node = right[node]
            else:
                return node
        return 0

    def _contains_node(self, node_id):
        return 0 < node_id < len(self.key) and self._find_node(self.key[node_id]) == node_id

    def _transplant(self, old_node, new_node):
        parent = self.parent[old_node]
        if parent == 0:
            self.root = new_node
        elif self.left[parent] == old_node:
            self.left[parent] = new_node
        else:
            self.right[parent] = new_node

        if new_node:
            self.parent[new_node] = parent

    def _fix_delete(self, node, node_parent):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[node] == self.BLACK:
            if node == left[node_parent]:
                sibling = right[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_left(node_parent)
                    sibling = right[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_right] == self.BLACK:
                        color[sibling_left] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_right(sibling)
                        sibling = right[node_parent]
                        sibling_right = right[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_right] = self.BLACK
                    self._rotate_left(node_parent)
                    node = self.root
            else:
                sibling = left[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_right(node_parent)
                    sibling = left[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_left] == self.BLACK:
                        color[sibling_right] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_left(sibling)
                        sibling = left[node_parent]
                        sibling_left = left[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_left] = self.BLACK
                    self._rotate_right(node_parent)
                    node = self.root

        color[node] = self.BLACK

    def _erase_node(self, node):
        next_node = self.next_id[node]
        prev_node = self.prev_id[node]
        if prev_node:
            self.next_id[prev_node] = next_node
        if next_node:
            self.prev_id[next_node] = prev_node

        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        moved_up = node
        moved_up_original_color = color[moved_up]
        if left[node] == 0:
            fix_node = right[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        elif right[node] == 0:
            fix_node = left[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        else:
            moved_up = next_node
            moved_up_original_color = color[moved_up]
            fix_node = right[moved_up]
            if parent[moved_up] == node:
                fix_parent = moved_up
            else:
                fix_parent = parent[moved_up]
                self._transplant(moved_up, fix_node)
                right[moved_up] = right[node]
                parent[right[moved_up]] = moved_up

            self._transplant(node, moved_up)
            left[moved_up] = left[node]
            parent[left[moved_up]] = moved_up
            color[moved_up] = color[node]

        left[node] = 0
        right[node] = 0
        parent[node] = 0
        color[node] = self.BLACK
        self.prev_id[node] = 0
        self.next_id[node] = 0

        if moved_up_original_color == self.BLACK:
            self._fix_delete(fix_node, fix_parent)

        return next_node

    def _iter_pair(self, node_id):
        if node_id == 0:
            return None, 0
        return self.key[node_id], node_id

    def insert(self, x, with_id=False):
        root = self.root
        if root == 0:
            self.root = self._new_node(x, self.BLACK, 0, 0)
            return (self.root, True) if with_id else True

        key = self.key
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = key[node]
            if x < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            elif x > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            else:
                return (node, False) if with_id else False

    def lower_bound_with_id(self, x):
        node = self.root
        answer_node = 0
        key = self.key
        left = self.left
        right = self.right

        while node:
            if key[node] >= x:
                answer_node = node
                node = left[node]
            else:
                node = right[node]

        if answer_node == 0:
            return None, 0
        return key[answer_node], answer_node

    def lower_bound(self, x, with_id=False):
        answer, node_id = self.lower_bound_with_id(x)
        return (answer, node_id) if with_id else answer

    def prev(self, node_id):
        prev_id = self.prev_id[node_id]
        if prev_id == 0:
            return None, 0
        return self.key[prev_id], prev_id

    def next(self, node_id):
        next_id = self.next_id[node_id]
        if next_id == 0:
            return None, 0
        return self.key[next_id], next_id

    def erase(self, x):
        node = self._find_node(x)
        if node == 0:
            return (None, 0), False
        next_node = self._erase_node(node)
        return self._iter_pair(next_node), True

    def erase_id(self, node_id, check=False):
        if check and not self._contains_node(node_id):
            return (None, 0), False
        next_node = self._erase_node(node_id)
        return self._iter_pair(next_node), True


# -------------------------
# Основное решение
# -------------------------

BOUND = 10**9


def solve() -> None:
    points = RedBlackTree((-BOUND, BOUND))
    q = int(input())
    values = list(map(int, input().split()))
    answers = []
    for x in values:
        # читаем + вставляем + запоминаем идентификатор вставленного узла:
        node_id, was_inserted = points.insert(x, with_id=True)
        if not was_inserted:  # данный x уже есть
            answers.append("0")
        else:  # расстояние до ближайшего - это минимум из расстояний до соседей:
            left, _ = points.prev(node_id)
            right, _ = points.next(node_id)
            answers.append(str(min(x - left, right - x)))
    print("\n".join(answers))


t = int(input())
for _ in range(t):
    solve()
