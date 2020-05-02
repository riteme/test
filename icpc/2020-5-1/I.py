#!/usr/bin/pypy

def fmt_ok(eq):
    try:
        left, num3 = eq.split('=', maxsplit=1)
        # num1, num2 = left.split('+-*/', maxsplit=1)
        if '+' in left:
            num1, num2 = left.split('+', maxsplit=1)
        elif '-' in left:
            num1, num2 = left.split('-', maxsplit=1)
        elif '*' in left:
            num1, num2 = left.split('*', maxsplit=1)
        elif '/' in left:
            num1, num2 = left.split('/', maxsplit=1)
        else:
            return

        op = left[len(num1)]
        if num1[0] in '0+-*/=':
            return
        if num2[0] in '0+-*/=':
            return
        if num3[0] in '0+-*/=':
            return

        v1 = int(num1)
        v2 = int(num2)
        v3 = int(num3)

        M = 10**9
        assert 0 < v1 <= M
        assert 0 < v2 <= M
        assert 0 < v3 <= M

        return v1, v2, v3, op
    except Exception as e:
        # print(e)
        return

def math_ok(v1, v2, v3, op):
    if op == '+':
        return v1 + v2 == v3
    elif op == '-':
        return v1 - v2 == v3
    elif op == '*':
        return v1 * v2 == v3
    elif op == '/':
        return v1 == v2 * v3
    else:
        return False

eq = raw_input()

fok = fmt_ok(eq)
mok = math_ok(*fok) if fok != None else False

S = '0123456789+-*/='
if fok != None and mok:
    print('Correct')
elif fok == None:
    print('Format Error')
else:
    # mok = False
    for i in xrange(len(eq)):
        for ic in S:
            for j in xrange(i + 1, len(eq)):
                for jc in S:
                    tmp = list(eq)
                    tmp[i] = ic
                    tmp[j] = jc
                    ts = ''.join(tmp)
                    fok = fmt_ok(ts)
                    mok = math_ok(*fok) if fok != None else False
                    if fok != None and mok:
                        print('Typo: %s instead of %s' % (eq, ts))
                        exit(0)

    print('Math Error')