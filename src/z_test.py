#!/usr/bin/env python
# encoding: utf8

import simhashindex


def test():
    si = simhashindex.SimhashIndex(3)
    vec = simhashindex.stl_vector_string()
    vec.append('abc')
    sh = si.simhash_vec(vec)
    print 'simhash:', sh
    fh = si.farmhash('abc')
    print 'farmhash:', fh


if __name__ == '__main__':
    test()
