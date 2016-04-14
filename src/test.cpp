#include "simhashindex.h"
#include "base_const.h"

#include <iostream>
#include <sys/time.h>

using namespace std;

int main(int argc, char **argv) {
    vector<string> words;
    for(int i=0; i<10000; i++){
        words.push_back("唱歌");
        words.push_back("歌唱");
        words.push_back("市场");
        words.push_back("市长");
        words.push_back("长春");
        words.push_back("北京");
    }

    struct timeval b, e;
    SimhashIndex si;
    gettimeofday(&b, 0);
    SimhashIndex::hash_t simhash = si.simhash_vec(words);
    gettimeofday(&e, 0);
    double timecost = (e.tv_sec - b.tv_sec)*1000 + (e.tv_usec - b.tv_usec)/1000;
    cout << "simhash_vec time cost: "<< timecost << endl;
    cout << "simhash:" << simhash << endl;
    int loop = 10000;
    SimhashIndex::hash_t sh = simhash;
    gettimeofday(&b, 0);
    for(int i=0; i<loop; i++) {
        si.add(sh, i);
        //sh <<= 1;
        sh += 1;
    }
    gettimeofday(&e, 0);
    timecost = (e.tv_sec - b.tv_sec)*1000 + (e.tv_usec - b.tv_usec)/1000;
    cout << "add time cost: "<< timecost << " millisecond" << endl;
    cout << "docpool size: " << si.get_poolsize() << endl;

    vector<SimhashIndex::docid_t> similars;
    words.clear();
    sh = simhash/30;
    int count;
    gettimeofday(&b, 0);
    for(int i=0; i<loop; i++) {
         count = si.get_similar(sh, similars);
         sh += 8;
    }
    gettimeofday(&e, 0);
    timecost = (e.tv_sec - b.tv_sec)*1000 + (e.tv_usec - b.tv_usec)/1000;
    cout << "get_similar time cost: "<< timecost << " millisecond" << endl;
    // cout << "to clearing input integer" << endl;
    // int i;
    // cin >> i;
    // si.clear();
    // cout << "clearing...."<< endl;
    // cin >> i;
    count = si.get_similar(simhash, similars);
    cout << "\nsimilars: " << count << " : ";
    foreach(similars, itr) {
         cout << *itr << ',';
    }
    cout << endl;

    return 0;
}
