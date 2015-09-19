class Node(object):

    """docstring for Node"""

    def __init__(self):
        super(Node, self).__init__()
        self.item = None
        self.prev = None
        self.next = None


class List(object):

    """docstring for List"""

    def __init__(self):
        super(List, self).__init__()
        self.first = None
        self.last = None
        self.n = 0

    def is_empty(self):
        return self.n == 0

    def size(self):
        return self.n

    def push_back(self, value):
        new_node = Node()
        new_node.item = value
        if self.last is None:
            self.last = self.first = new_node
        else:
            new_node.prev = self.last
            self.last.next = new_node
            self.last = new_node

        self.n += 1

    def pop_back(self):
        if self.n == 0:
            return None

        old_last = self.last
        self.last = self.last.prev
        if self.last is None:
            self.first = None
        else:
            self.last.next = None

        self.n -= 1
        return old_last.item

    def push_front(self, value):
        new_node = Node()
        new_node.item = value
        new_node.next = self.first
        self.first = new_node

        if self.last is None:
            self.last = self.first

        self.n += 1

    def pop_front(self):
        if self.n == 0:
            return None

        old_first = self.first
        self.first = self.first.next

        if self.first is None:
            self.last = None
        else:
            self.first.prev = None

        self.n -= 1

        return old_first.item

    def __repr__(self):
        iterator = self.first
        L = []
        while iterator is not None:
            L.append(str(iterator.item))
            iterator = iterator.next
        return '<algs>\n[' + ', '.join(L) + ']'


class Queue(object):

    """docstring for Queue"""

    def __init__(self):
        super(Queue, self).__init__()
        self._list = List()

    def is_empty(self):
        return self._list.is_empty()

    def size(self):
        return self._list.size()

    def enqueue(self, value):
        self._list.push_back(value)

    def dequeue(self):
        return self._list.pop_front()

    def __repr__(self):
        return repr(self._list)


class Stack(object):

    """docstring for Stack"""

    def __init__(self):
        super(Stack, self).__init__()
        self._list = List()

    def is_empty(self):
        return self._list.is_empty()

    def size(self):
        return self._list.size()

    def push(self, value):
        self._list.push_front(value)

    def pop(self):
        return self._list.pop_front()

    def __repr__(self):
        return repr(self._list)
