/*
    Copyright (c) 2013, veelion
    Author: veelion@ebuinfo.com
    All rights reserved.
*/

#ifndef SIMHASH_INDEX_H_
#define SIMHASH_INDEX_H_


#include <stdint.h>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>



class SimhashIndex{
    public:
        typedef uint64_t hash_t;
        typedef uint64_t docid_t;
        typedef uint32_t key_t;
        typedef std::map<hash_t, docid_t> hashpool_t;
        typedef std::map<key_t, std::set<hash_t> > table_t;

    public:
        SimhashIndex();
        explicit SimhashIndex(int k);
        virtual ~SimhashIndex();

        bool clear();

        hash_t farmhash(const std::string &str);
        hash_t simhash_txt(const std::string &text);
        hash_t simhash_vec(const std::vector<std::string> &words);

        bool add(hash_t simhash, docid_t docid);

        // return count of its simliar docs
        int get_similar(hash_t simhash, std::vector<docid_t> &docids);
        int get_poolsize() { return _hashpool.size(); }

        int* gen_offsets();
        bool split_to_keys(hash_t simhash, key_t* keys);

    private:
        void init();
        static const int _f; // the dimensions of fingerprints
        int _k; // the tolerance
        int _tables_count;
        table_t* _tables;
        int* _offsets;
        hashpool_t _hashpool;
};


#endif  // SIMHASH_INDEX_H_
