#include <cstdio>
#include <cstddef>
#include <cstring>

class Decoder {
 public:
    Decoder(FILE *file) : _pos(0) {
        fread(_buffer, 1, MAX_LENGTH, file);

        int v = 0;
        for (int i = 'a'; i <= 'z'; i++)
            _table[i] = v++;
        for (int i = 'A'; i <= 'Z'; i++)
            _table[i] = v++;
        for (int i = '0'; i <= '9'; i++)
            _table[i] = v++;
        _table['%'] = v++;
        _table['@'] = v++;
    }

    int next() {
        int r = _table[_buffer[_pos++]] << 18;
        r |= _table[_buffer[_pos++]] << 12;
        r |= _table[_buffer[_pos++]] << 6;
        r |= _table[_buffer[_pos++]];
        return r;
    }

 private:
    static const size_t MAX_LENGTH = 30000000;

    size_t _pos;
    char _buffer[MAX_LENGTH];
    int _table[256];
};

int main() {
    Decoder *decoder = new Decoder(stdin);

    int n, m, q;
    n = decoder->next();
    m = decoder->next();
    q = decoder->next();
    printf("%d %d %d\n", n, m, q);

    for (int i = 0; i < m; i++) {
        int u, v;
        u = decoder->next();
        v = decoder->next();
        printf("%d %d\n", u, v);
    }

    for (int i = 0; i < q; i++) {
        int s, t, v;
        s = decoder->next();
        t = decoder->next();
        v = decoder->next();
        printf("%d %d %d\n", s, t, v);
    }

    return 0;
}
