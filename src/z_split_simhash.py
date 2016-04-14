#!/usr/bin/env python
# encoding: utf8


def get_keys(simhash):
    f = 64
    offsets = [0, 16, 32, 48]
    ret = []
    for i, offset in enumerate(offsets):
        if i == (len(offsets) - 1):
            m = 2 ** (f - offset) - 1
        else:
            m = 2 ** (offsets[i + 1] - offset) - 1
        c = simhash >> offset & m
        ret.append(c)
    return ret


if __name__ == '__main__':
    lines = open('zlog').readlines()
    for l in lines:
        if '==>' not in l:
            continue
        a, b = l.split('==>')
        simhash = long(a.split(':')[1])
        kk = b.split(':')[1].split(',')
        keys = [int(k) for k in kk]
        zz = get_keys(simhash)
        if zz == keys:
            print 'good:', zz, ' != ', keys
        else:
            print '\tbad:', l

