add_library(simhashindexc STATIC
    farmhash.cc
    simhashindex.cc
)

add_executable(test test.cpp)
target_link_libraries(test simhashindexc)


add_library(simhashindex SHARED 
    farmhash.cc
    simhashindex.cc
    wrap_pymod.cc
)
target_link_libraries(simhashindex boost_python)
set_target_properties(simhashindex PROPERTIES PREFIX "")


