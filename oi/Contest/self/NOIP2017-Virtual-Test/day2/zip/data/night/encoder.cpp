#include <cstdio>
#include <cstddef>
#include <cstring>

class Encoder {
 public:
    Encoder() : _pos(0) {
        memset(_buffer, 0, sizeof(_buffer));
    }

    void encode(int v) {
        _buffer[_pos] = _table[(v >> 18) & 63];
        _buffer[_pos + 1] = _table[(v >> 12) & 63];
        _buffer[_pos + 2] = _table[(v >> 6) & 63];
        _buffer[_pos + 3] = _table[v & 63];
        _pos += 4;
    }

    const char *str() const {
        return _buffer;
    }

 private:
    static const size_t MAX_LENGTH = 30000000;
    static char _table[65];

    size_t _pos;
    char _buffer[MAX_LENGTH];
};

char Encoder::_table[65] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "%@";

int main() {
    Encoder *encoder = new Encoder;

    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    encoder->encode(n);
    encoder->encode(m);
    encoder->encode(q);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        encoder->encode(u);
        encoder->encode(v);
    }

    for (int i = 0; i < q; i++) {
        int s, t, v;
        scanf("%d%d%d", &s, &t, &v);
        encoder->encode(s);
        encoder->encode(t);
        encoder->encode(v);
    }

    printf("%s", encoder->str());

    return 0;
}
