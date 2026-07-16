# Вердикт: ..., Время: ..., Память: ..., Язык: PyPy 3-64

# -------------------------
# RedBlackTree
# -------------------------

"""Компактный RedBlackTree для задач на ordered map<int, int>.

Использование:
- tree = RedBlackTree(items=())
  Создаёт дерево и по очереди вставляет пары (key, value) из items.
- tree.set(key, value) -> node_id
  Вставляет ключ, если его ещё нет, либо перезаписывает значение.
  Возвращает node_id этого ключа.
- tree.set(key, value, with_id=True) -> (node_id, was_inserted)
  Возвращает node_id и флаг, был ли ключ создан заново.
- tree.set_value(node_id, value) -> None
    Меняет значение по существующему node_id за O(1).
    Этот метод предполагает, что node_id живой и не был удалён.
- tree.add(key, delta) -> node_id
  Увеличивает значение по ключу на delta. Если ключа нет, создаёт его.
- tree.get(key, default=None) -> value
  Возвращает значение по ключу или default, если ключ не найден.
- tree.get_key(node_id) -> key
  Возвращает ключ по node_id.
- tree.get_value(node_id) -> value
  Возвращает значение по node_id.
- tree.upper_bound_with_id(x) -> (key, value, node_id)
  Возвращает первый ключ > x, его значение и node_id.
  Если такого ключа нет, возвращает (None, None, 0).
- tree.prev(node_id) -> (key, value, prev_node_id)
  Возвращает предыдущий ключ в inorder, его значение и node_id.
  Если соседа слева нет, возвращает (None, None, 0).
- tree.last() -> (key, value, node_id)
  Возвращает максимальный ключ, его значение и node_id.
  Если дерево пусто, возвращает (None, None, 0).
- tree.erase_id(node_id) -> bool
  Удаляет узел по его node_id.
  Возвращает True, если удаление произошло, иначе False.

Замечание:
- node_id стабилен после поворотов и следующих вставок, пока сам узел не удалён.
"""


class RedBlackTree:
    __slots__ = ("root", "key", "value", "left", "right", "parent", "color", "prev_id", "next_id")

    RED = 1
    BLACK = 0

    def __init__(self, items=()):
        self.root = 0
        self.key = [0]
        self.value = [0]
        self.left = [0]
        self.right = [0]
        self.parent = [0]
        self.color = [self.BLACK]
        self.prev_id = [0]
        self.next_id = [0]
        for key, value in items:
            self.set(key, value)

    def _new_node(self, key, value, color, pred, succ):
        self.key.append(key)
        self.value.append(value)
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

    def _find_node(self, key):
        node = self.root
        keys = self.key
        left = self.left
        right = self.right

        while node:
            node_key = keys[node]
            if key < node_key:
                node = left[node]
            elif key > node_key:
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

    def _node_entry(self, node_id):
        if node_id == 0:
            return None, None, 0
        return self.key[node_id], self.value[node_id], node_id

    def set(self, key, value, with_id=False):
        root = self.root
        if root == 0:
            self.root = self._new_node(key, value, self.BLACK, 0, 0)
            return (self.root, True) if with_id else self.root

        keys = self.key
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = keys[node]
            if key < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(key, value, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else new_node
                node = next_node
            elif key > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(key, value, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else new_node
                node = next_node
            else:
                self.value[node] = value
                return (node, False) if with_id else node

    def set_value(self, node_id, value):
        self.value[node_id] = value

    def add(self, key, delta):
        root = self.root
        if root == 0:
            self.root = self._new_node(key, delta, self.BLACK, 0, 0)
            return self.root

        keys = self.key
        values = self.value
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = keys[node]
            if key < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(key, delta, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return new_node
                node = next_node
            elif key > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(key, delta, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return new_node
                node = next_node
            else:
                values[node] += delta
                return node

    def get(self, key, default=None):
        node = self._find_node(key)
        return default if node == 0 else self.value[node]

    def get_key(self, node_id):
        if node_id == 0:
            return None
        return self.key[node_id]

    def get_value(self, node_id):
        if node_id == 0:
            return None
        return self.value[node_id]

    def upper_bound_with_id(self, x):
        node = self.root
        answer_node = 0
        keys = self.key
        left = self.left
        right = self.right

        while node:
            if keys[node] > x:
                answer_node = node
                node = left[node]
            else:
                node = right[node]

        return self._node_entry(answer_node)

    def prev(self, node_id):
        if node_id == 0:
            return None, None, 0
        return self._node_entry(self.prev_id[node_id])

    def last(self):
        node = self.root
        if node == 0:
            return None, None, 0
        right = self.right
        while right[node]:
            node = right[node]
        return self._node_entry(node)

    def erase_id(self, node_id):
        if not self._contains_node(node_id):
            return False
        self._erase_node(node_id)
        return True


# -------------------------
# Основное решение
# -------------------------


def solve() -> None:
    # храним свободные отрезки в map<int, int>: ключ - левая граница L,
    # значение - правая граница R. Тогда upper_bound(l) найдёт первый
    # отрезок, который начинается строго правее l, а предыдущий отрезок
    # и будет тем самым [L, R], который содержит запрос [l, r].
    # Вместо multiset длин храним ещё один map<int, int>: ключ - длина,
    # значение - количество отрезков такой длины.
    n, q = map(int, input().split())
    segments = RedBlackTree(((1, n),))
    lengths = RedBlackTree(((0, 1), (n, 1)))
    _, _, max_length_id = lengths.last()
    answers = []
    while q > 0:
        c, l, r = input().split()
        l = int(l)
        r = int(r)
        # находим отрезок, в который попадает граница l:
        _, _, next_segment_id = segments.upper_bound_with_id(l)
        if next_segment_id == 0:
            L, R, segment_id = segments.last()
        else:
            L, R, segment_id = segments.prev(next_segment_id)
        # запоминаем его левую и правую границу, затем обновляем структуру
        # свободных отрезков и счётчики длин:
        lengths.add(R - L + 1, -1)
        # Если левая часть [L, l-1] осталась, переиспользуем тот же node_id:
        if L < l:
            segments.set_value(segment_id, l - 1)
            lengths.add(l - L, +1)
        else:
            segments.erase_id(segment_id)
        # Правую часть при необходимости всё равно добавляем как новый узел:
        if r < R:
            segments.set(r + 1, R)
            lengths.add(R - r, +1)
        # максимальная длина могла только уменьшиться, поэтому двигаемся влево,
        # пока количество отрезков текущей длины не станет положительным:
        while lengths.get_value(max_length_id) == 0:
            _, _, max_length_id = lengths.prev(max_length_id)
        # выводим ответ - максимальную длину отрезка:
        answers.append(str(lengths.get_key(max_length_id)))
        q -= 1
    print("\n".join(answers))


t = int(input())
for _ in range(t):
    solve()