/*
    Copyright (c) 2013, veelion
    Author: veelion@ebuinfo.com
    All rights reserved.
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

#include "base_const.h"
#include "farmhash.h"
#include "simhashindex.h"

#define hamdist(x, y) __builtin_popcountll((x)^(y))

using namespace std;
using namespace NAMESPACE_FOR_HASH_FUNCTIONS;


const int SimhashIndex::_f = 64;

SimhashIndex::SimhashIndex() {
    _k = 3;
    init();
}


SimhashIndex::SimhashIndex(int k) {
    _k = k;
    init();
}


void SimhashIndex::init() {
    _tables_count = _k + 1;

    _tables = new table_t[_tables_count];
    _offsets = gen_offsets();
    _hashpool.clear();
}


SimhashIndex::~SimhashIndex() {
    clear();
    delete [] _tables;
    delete [] _offsets;
}


bool SimhashIndex::clear() {
    _hashpool.clear();
    for(int i=0; i<_tables_count; i++) {
        _tables[i].clear();
    }
    return true;
}

int* SimhashIndex::gen_offsets() {
    int* offsets = new int[_tables_count];
    for(int i=0; i<_tables_count; i++) {
         int off = _f / _tables_count * i;
         offsets[i] = off;
    }
    return offsets;
}


bool SimhashIndex::split_to_keys(hash_t simhash, key_t* keys) {
    // cout << "!!! simhash: " << simhash << endl;
    hash_t m = 0, c;
    for(int i=0; i<_tables_count; i++) {
        if(i == _tables_count -1) {
            //m = powl(2, _f - _offsets[i]) - 1;
            m = (1 << (_f - _offsets[i])) - 1;
        }else{
            // m = powl(2, _offsets[i+1] - _offsets[i]) - 1;
            m = (1 << (_offsets[i+1] - _offsets[i])) - 1;
        }
        // cout << "\tm: " << m << endl;
        c = (simhash >> _offsets[i]) & m;
        // cout << "m: " << m << ", c: " << c << endl;
        keys[i] = c;
    }
    return true;
}


SimhashIndex::hash_t SimhashIndex::simhash_txt(const string &text) {
    return 0;
}


SimhashIndex::hash_t SimhashIndex::simhash_vec(const vector<string> &words) {
    int sums[_f] = {0};
    foreach(words, itr) {
         hash_t hv = Hash64(itr->c_str(), itr->size());
         for(int i = 0; i < _f; i++) {
             if(hv & 1) {
                 ++sums[i];
             }else{
                 --sums[i];
             }
             hv >>= 1;
         }
    }
    hash_t result = 0;
    for(int i = 0; i < _f; i++) {
        if(sums[i] > 0) {
            result |= 1;
        }
        result <<= 1;
    }
    return result;
}


bool SimhashIndex::add(hash_t simhash, docid_t docid) {
    hashpool_t::iterator doc = _hashpool.find(simhash);
    if(doc != _hashpool.end()) {
        return false;
    }
    _hashpool[simhash] = docid;

    key_t keys[_tables_count];
    split_to_keys(simhash, keys);
    // cout << "simhash: " << simhash << " ==> keys: " << keys[0] << "," << keys[1] << "," << keys[2]<< "," << keys[3]<< endl;
    table_t::iterator itr;
    for(int i=0; i<_tables_count; i++) {
        if(_tables[i].find(keys[i]) == _tables[i].end()) {
            set<hash_t> v;
            v.insert(simhash);
            _tables[i][keys[i]] = v;
        }else{
             _tables[i][keys[i]].insert(simhash);
        }
    }
    return true;
}


int SimhashIndex::get_similar(hash_t simhash, vector<docid_t> &docids) {
    key_t keys[_tables_count];
    split_to_keys(simhash, keys);
    set<docid_t> similars;
    for(int i=0; i<_tables_count; i++) {
        table_t::iterator docs = _tables[i].find(keys[i]);
        if(docs == _tables[i].end()) {
            continue;
        }
        // cout << "comparing.... " << simhash << ", key: " << keys[i] << ", table-id:" << i << ", size: " << docs->second.size() << endl;
        foreach(docs->second, itr) {
            int dist = hamdist(simhash, *itr);
            if(dist < _k) {
                 similars.insert(_hashpool[*itr]);
            }
        }
    }
    docids.clear();
    foreach(similars, itr) {
         docids.push_back(*itr);
    }
    return similars.size();
}

