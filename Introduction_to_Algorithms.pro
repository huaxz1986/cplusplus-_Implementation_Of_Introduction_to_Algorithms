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
    src/header.h \
    src/dynamic_programming_algorithms/lcs/longest_common_subsequence.h \
    src/dynamic_programming_algorithms/lcs/longest_common_subsequence_test.h \
    src/google_test/gtest.h \
    src/tree_algorithms/searchtree/searchtree.h \
    src/tree_algorithms/searchtree/searchtree_test.h \
    src/tree_algorithms/binarytreenode/binarytreenode.h \
    src/tree_algorithms/binarytreenode/binarytreenode_test.h \
    src/tree_algorithms/binarytree/binarytree.h \
    src/tree_algorithms/binarytree/binarytree_test.h \
    src/sort_algorithms/radix_sort/radixsort.h \
    src/sort_algorithms/radix_sort/radixsort_test.h \
    src/sort_algorithms/quick_sort/quicksort.h \
    src/sort_algorithms/quick_sort/quicksort_test.h \
    src/sort_algorithms/merge_sort/mergesort.h \
    src/sort_algorithms/merge_sort/mergesort_test.h \
    src/sort_algorithms/insert_sort/insertsort.h \
    src/sort_algorithms/insert_sort/insertsort_test.h \
    src/sort_algorithms/heap_sort/heapsort.h \
    src/sort_algorithms/heap_sort/heapsort_test.h \
    src/sort_algorithms/bucket_sort/bucketsort.h \
    src/sort_algorithms/bucket_sort/bucketsort_test.h \
    src/sort_algorithms/count_sort/countsort.h \
    src/sort_algorithms/count_sort/countsort_test.h \
    src/select_algorithms/randomized_select/randomizedselect.h \
    src/select_algorithms/randomized_select/randomizedselect_test.h \
    src/select_algorithms/good_select/goodselect.h \
    src/select_algorithms/good_select/goodselect_test.h \
    src/graph_algorithms/basic_graph/graph_representation/matrix_graph/matrixgraph.h \
    src/graph_algorithms/basic_graph/graph_representation/matrix_graph/matrixgraph_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/vertex_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_edge/edge.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_edge/edge_test.h \
    src/graph_algorithms/basic_graph/graph_dfs/dfs.h \
    src/graph_algorithms/basic_graph/graph_dfs/dfs_test.h \
    src/graph_algorithms/basic_graph/graph_bfs/bfs.h \
    src/graph_algorithms/basic_graph/graph_bfs/bfs_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph/graph.h \
    src/graph_algorithms/basic_graph/graph_representation/graph/graph_test.h \
    src/graph_algorithms/basic_graph/graph_representation/adjlist_graph/adjlistgraph.h \
    src/graph_algorithms/basic_graph/graph_representation/adjlist_graph/adjlistgraph_test.h \
    src/graph_algorithms/basic_graph/topology_sort/topologysort.h \
    src/graph_algorithms/basic_graph/topology_sort/topologysort_test.h \
    src/graph_algorithms/basic_graph/strong_connected_component/strongconnectedcomponent.h \
    src/graph_algorithms/basic_graph/strong_connected_component/strongconnectedcomponent_test.h \
    src/queue_algorithms/min_queue/minqueue.h \
    src/queue_algorithms/min_queue/minqueue_test.h \
    src/graph_algorithms/minimum_spanning_tree/prim/prim.h \
    src/graph_algorithms/minimum_spanning_tree/prim/prim_test.h \
    src/graph_algorithms/minimum_spanning_tree/kruskal/kruskal.h \
    src/graph_algorithms/minimum_spanning_tree/kruskal/kruskal_test.h \
    src/set_algorithms/disjoint_set/disjointset.h \
    src/set_algorithms/disjoint_set/disjointset_test.h \
    src/graph_algorithms/basic_graph/connected_component/connectedcomponent.h \
    src/graph_algorithms/basic_graph/connected_component/connectedcomponent_test.h \
    src/graph_algorithms/single_source_shortest_path/bellman_ford/bellmanford.h \
    src/graph_algorithms/single_source_shortest_path/bellman_ford/bellmanford_test.h \
    src/graph_algorithms/single_source_shortest_path/dag_shortest_path/dagshortpath.h \
    src/graph_algorithms/single_source_shortest_path/dag_shortest_path/dagshortpath_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/bfs_vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/bfs_vertex_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/dfs_vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/dfs_vertex_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/vertexp.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/vertexp_test.h \
    src/graph_algorithms/single_source_shortest_path/dijkstra/dijkstra.h \
    src/graph_algorithms/single_source_shortest_path/dijkstra/dijkstra_test.h \
    src/graph_algorithms/all_node_pair_shortest_path/matrix_shortest_path/matrix_shortest_path.h \
    src/graph_algorithms/all_node_pair_shortest_path/matrix_shortest_path/matrix_shortest_path_test.h \
    src/graph_algorithms/all_node_pair_shortest_path/floyd_warshall/floyd_warshall.h \
    src/graph_algorithms/all_node_pair_shortest_path/floyd_warshall/floyd_warshall_test.h \
    src/graph_algorithms/all_node_pair_shortest_path/johnson/johnson.h \
    src/graph_algorithms/all_node_pair_shortest_path/johnson/johnson_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/set_vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/set_vertex_test.h \
    src/graph_algorithms/max_flow/ford_fulkerson/fordfulkerson.h \
    src/graph_algorithms/max_flow/ford_fulkerson/fordfulkerson_test.h \
    src/graph_algorithms/max_flow/generic_push_relabel/genericpushrelabel.h \
    src/graph_algorithms/max_flow/generic_push_relabel/genericpushrelabel_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/flow_vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/flow_vertex_test.h \
    src/graph_algorithms/max_flow/relabel_to_front/relabeltofront.h \
    src/graph_algorithms/max_flow/relabel_to_front/relabeltofront_test.h \
    src/string_matching_algorithms/regular_match/match.h \
    src/string_matching_algorithms/regular_match/match_test.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/front_flow_vertex.h \
    src/graph_algorithms/basic_graph/graph_representation/graph_vertex/front_flow_vertex_test.h \
    src/string_matching_algorithms/rabin_karp_match/rabinkarpmatch.h \
    src/string_matching_algorithms/rabin_karp_match/rabinkarpmatch_test.h \
    src/string_matching_algorithms/finite_automaton_match/finiteautomatonmatch.h \
    src/string_matching_algorithms/finite_automaton_match/finiteautomatonmatch_test.h \
    src/string_matching_algorithms/kmp_match/kmp.h \
    src/string_matching_algorithms/kmp_match/kmp_test.h



