#!/usr/bin/env python
# encoding: utf8

import simhashindex


def test():
    si = simhashindex.SimhashIndex(3)
    vec = simhashindex.stl_vector_string()
    vec.append('abc')
    sh = si.simhash_vec(vec)
    print sh


if __name__ == '__main__':
    test()
