TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    src/google_test/gtest-all.cc

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/google_test/gtest.h \
    src/sort_algorithms/insert_sort/insertsort.h \
    src/sort_algorithms/insert_sort/insertsort_test.h \
    src/sort_algorithms/merge_sort/mergesort.h \
    src/sort_algorithms/merge_sort/mergesort_test.h \
    src/sort_algorithms/quick_sort/quicksort.h \
    src/sort_algorithms/quick_sort/quicksort_test.h \
    src/sort_algorithms/heap_sort/heapsort.h \
    src/sort_algorithms/heap_sort/heapsort_test.h \
    src/sort_algorithms/count_sort/countsort.h \
    src/sort_algorithms/count_sort/countsort_test.h \
    src/sort_algorithms/radix_sort/radixsort.h \
    src/sort_algorithms/radix_sort/radixsort_test.h \
    src/sort_algorithms/bucket_sort/bucketsort.h \
    src/sort_algorithms/bucket_sort/bucketsort_test.h \
    src/algorithms.h \
    src/select_algorithms/randomized_select/randomizedselect.h \
    src/select_algorithms/randomized_select/randomizedselect_test.h \
    src/select_algorithms/good_select/goodselect.h \
    src/select_algorithms/good_select/goodselect_test.h \
    src/dynamic_programming_algorithms/longest_common_subsequence.h \
    src/dynamic_programming_algorithms/longest_common_subsequence_test.h \
    src/tree_algorithms/binarytreenode/binarytreenode.h \
    src/tree_algorithms/binarytreenode/binarytreenode_test.h \
    src/tree_algorithms/binarytree/binarytree.h \
    src/tree_algorithms/binarytree/binarytree_test.h \
    src/tree_algorithms/searchtree/searchtree.h \
    src/tree_algorithms/searchtree/searchtree_test.h \
    src/graph_algorithms/basic_graph/matrix_graph/matrixgraph.h \
    src/graph_algorithms/basic_graph/matrix_graph/matrixgraph_test.h \
    src/graph_algorithms/basic_graph/adjlist_graph/adjlistgraph.h \
    src/graph_algorithms/basic_graph/adjlist_graph/adjlistgraph_test.h \
    src/graph_algorithms/basic_graph/graph_vertex/vertex.h \
    src/graph_algorithms/basic_graph/graph_vertex/vertex_test.h \
    src/graph_algorithms/basic_graph/graph_edge/edge.h \
    src/graph_algorithms/basic_graph/graph_edge/edge_test.h

