#include <algorithm>

using namespace std;

#define SIZEMAX 10000

typedef int KeyType;
typedef int ValueType;

/////////////////
// IndexedHeap //
/////////////////

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) + 1)

struct Node {
    KeyType key;
    ValueType value;
};  // struct Node

static Node heap[SIZEMAX + 10];
static unsigned pos[SIZEMAX + 10];  // 如果键值不是整型，可以改用哈希表
static unsigned heapSize;

// O(n)
inline void make_heap(unsigned size) {
    for (unsigned i = 1; i <= size; i++) {
        pos[i] = 0;
    }  // for

    heapSize = 0;
}

// O(1)
inline unsigned heap_size() {
    return heapSize;
}

// O(logn)
/**
 * 将元素上调至合适位置
 * @param key 键索引
 */
inline void swim(KeyType key) {
    unsigned x = pos[key];

    while (x > 0 and heap[x].value < heap[PARENT(x)].value) {
        swap(pos[key], pos[heap[PARENT(x)].key]);
        swap(heap[x], heap[PARENT(x)]);

        x = PARENT(x);
    }  // while
}

// O(logn)
/**
 * 将元素下沉至合适位置
 * @param key 键索引
 */
inline void sink(KeyType key) {
    unsigned x = pos[key];

    while (x <= heapSize) {
        // 冒泡选取最小值
        unsigned next = x;

        if (LEFT(x) <= heapSize and heap[next].value > heap[LEFT(x)].value) {
            next = LEFT(x);
        }

        if (RIGHT(x) <= heapSize and heap[next].value > heap[RIGHT(x)].value) {
            next = RIGHT(x);
        }

        // 如果x就是最小，则堆的性质已维护完毕
        if (next == x) {
            break;
        } else {
            swap(pos[key], pos[heap[next].key]);
            swap(heap[x], heap[next]);
        }

        x = next;
    }  // while
}

inline Node top() {
    return heap[1];
}

inline void push(KeyType key, ValueType value) {
    heapSize++;
    heap[heapSize].key = key;
    heap[heapSize].value = value;
    pos[key] = heapSize;

    swim(key);
}

inline void pop() {
    pos[heap[1].key] = 0;
    heap[1] = heap[heapSize];
    pos[heap[1].key] = 1;
    heapSize--;

    sink(heap[1].key);
}

/**
 * 减低某个元素的值
 * @param key   建索引
 * @param value 新值，必须比原来的值要小
 */
inline void decrease(KeyType key, ValueType value) {
    heap[pos[key]].value = value;

    swim(key);
}

// 多数情况下只有decrease派得上用场
// increase与decrease类似
// 可以自动判断新值的大小来选择increase或decrease

inline bool contain(KeyType key) {
    return pos[key] != 0;
}

inline bool empty() {
    return heapSize == 0;
}

// IndexedHeap end
