/*
    Copyright (c) 2016, ebuinfo.com
    Author: veelion@ebuinfo.com
    All rights reserved.
*/

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "simhashindex.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(simhashindex) {
    // This will enable user-defined docstrings and python signatures,
    // while disabling the C++ signatures
    scope().attr("__version__") = "1.0.8";
    scope().attr("__doc__") = "[simhashindex] module is created by Ebu info-tech Inc.\n"
        "It's a Simhash index to find similar docs implemented in C++\n"
        "and exported as Python module using boost-python";
    docstring_options local_docstring_options(true, false, false);
    class_<SimhashIndex>("SimhashIndex", "to create an SimhashIndex instance:\nsi = simhashindex.SimhashIndex(3)", init<int>())
        // methods for add to index
        .def(
                "add", &SimhashIndex::add,
                "Function: add simhash and its docid to the index\n"
                "Definition: add(simhash, docid)\n"
                "PARAM-1: [simhash] is what to be add\n"
                "PARAM-2: [docid] doc's id\n"
                "RETURN : true if added, false if the simhash is already in the index\n"
            )
        .def(
                "simhash_vec", &SimhashIndex::simhash_vec,
                "Function: calculate the simhash of a sequence of words/strings\n"
                "Definition: simhash_vec(words)\n"
                "PARAM-1: [words] a vector of words/strings\n"
                "RETURN : simhash\n"
            )
        .def(
                "get_similar", &SimhashIndex::get_similar,
                "Function: get similar docids of the inputted simhash\n"
                "Definition: get_similar(simhash, docids)\n"
                "PARAM-1: [simhash] input document's simhash\n"
                "PARAM-2: [docids] a set of docid_t to save the similars\n"
                "RETURN : the count of similars\n"
            )
        .def(
                "farmhash", &SimhashIndex::farmhash,
                "Function: calculate 64-bit farmhash of a string\n"
                "Definition: farmhash(string)\n"
                "PARAM-1: [string] the string inputted\n"
                "RETURN: the 64-bit simhash value\n"
            )
        .enable_pickling()
        ;

    class_<std::vector<std::string> >("stl_vector_string")
        .def(vector_indexing_suite<std::vector<std::string> >())
        ;
    class_<std::vector<SimhashIndex::docid_t> >("stl_vector_docid")
        .def(vector_indexing_suite<std::vector<SimhashIndex::docid_t> >())
        ;
}

