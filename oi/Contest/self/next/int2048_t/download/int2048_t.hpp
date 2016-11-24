#ifndef INT2048_T_HPP_
#define INT2048_T_HPP_

#include <cstdint>

#include <string>
#include <bitset>

#define INT_LENGTH 2048
#define COST 1

struct int2048_t {
    static uint64_t cost;

    int2048_t() {}

    int2048_t(const std::string &literal) : _num(literal) {}

    int2048_t operator+(const int2048_t &b) const {
        int2048_t c;

        int upload = 0;
        for (int i = 0; i < INT_LENGTH; i++) {
            upload += static_cast<int>(_num[i]) +
                      static_cast<int>(b._num[i]);

            c._num[i] = upload & 1;
            upload >>= 1;
        }

        cost += COST;

        return c;
    }

    int2048_t operator-() const {
        int2048_t c = *this;

        for (int i = 0; i < INT_LENGTH - 1; i++)
            c._num[i] = !c._num[i];
        c._num[INT_LENGTH - 1] = 1;

        int i;
        for (i = 0; i < INT_LENGTH && c._num[i]; i++)
            c._num[i] = 0;
        
        if (i < INT_LENGTH)
            c._num[i] = 1;

        cost += COST;

        return c;
    }

    int2048_t operator-(const int2048_t &b) const {
        return *this + (-b);
    }

    int2048_t operator~() const {
        int2048_t c = *this;
        c._num = ~c._num;

        cost += COST;

        return c;
    }

    int2048_t operator&(const int2048_t &b) const {
        int2048_t c = *this;
        c._num &= b._num;

        cost += COST;

        return c;
    }

    int2048_t operator|(const int2048_t &b) const {
        int2048_t c = *this;
        c._num |= b._num;
        
        cost += COST;

        return c;
    }

    int2048_t operator^(const int2048_t &b) const {
        int2048_t c = *this;
        c._num ^= b._num;

        cost += COST;

        return c;
    }

    int2048_t operator<<(const int b) const {
        int2048_t c = *this;
        c._num <<= b;

        cost += COST;

        return c;
    }

    int2048_t operator>>(const int b) const {
        int2048_t c = *this;
        c._num >>= b;

        cost += COST;

        return c;
    }

    bool operator==(const int2048_t &b) const {
        cost += COST;
        
        return _num == b._num;
    }

    bool operator!=(const int2048_t &b) const {
        return !(*this == b);
    }

    bool operator<(const int2048_t &b) const {
        cost += COST;

        if (_num[INT_LENGTH - 1] == 1 && b._num[INT_LENGTH - 1] == 0)
            return true;
        else if (_num[INT_LENGTH - 1] == 0 && b._num[INT_LENGTH - 1] == 1)
            return false;

        bool reversed = _num[INT_LENGTH - 1];
        for (int i = INT_LENGTH - 2; i >= 0; i--) {
            if (_num[i] == 0 && b._num[i] == 1)
                return true ^ reversed;
            else if (_num == 1 && b._num[i] == 0)
                return reversed;
        }

        return false;
    }

    bool operator>(const int2048_t &b) const {
        cost += COST;

        if (_num[INT_LENGTH - 1] == 1 && b._num[INT_LENGTH - 1] == 0)
            return false;
        else if (_num[INT_LENGTH - 1] == 0 && b._num[INT_LENGTH - 1] == 1)
            return true;

        bool reversed = _num[INT_LENGTH - 1];
        for (int i = INT_LENGTH - 2; i >= 0; i--) {
            if (_num[i] == 0 && b._num[i] == 1)
                return reversed;
            else if (_num == 1 && b._num[i] == 0)
                return true ^ reversed;
        }

        return false;
    }

    bool operator<=(const int2048_t &b) const {
        return !(*this > b);
    }

    bool operator>=(const int2048_t &b) const {
        return !(*this < b);
    }

    explicit operator bool() const {
        cost += COST;

        if (_num.any())
            return true;
        return false;
    }

 private:
    std::bitset<INT_LENGTH> _num;
};

#undef INT_LENGTH
#undef COST

#endif  // INT2048_T_HPP_
