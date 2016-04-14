Simhash Index
==========


Overview
========
This package implenments a simhash indexer for lots of documents, to find similar simhash for inputted simhash

Code specific to this project is covered by [The MIT License](http://opensource.org/licenses/MIT)

Issues
=======
Why diffrent result with diffrent build tools?

test step:
> (a) cmake build:
> > 1. mkdir cmake-build
> > 2. cd cmake-build && cmake ..
> > 3. make
> > 4. you'll get simhashindex.so in ../bin/
> > 5. run the test python script src/z_test.py with this simhashindex.so
> > 6. result: 12671429521584770134
> 
> (b) setup.py build:
> > 1. python setup.py build
> > 2. you'll get the python module: ./build/lib.linux-x86_64-2.7/simhashindex.so 
> > 3. run the test python script src/z_test.py with this simhashindex.so
> > 4. result: 3287573147730790984


Why diffrent?!!!



Usage
=====
The library is pretty simple to use, see z_test.py
