/*
 * Copyright 2016- huaxz <huaxz1986@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: huaxz1986@163.com (huaxz)
 */

#include <iostream>
#include"src/google_test/gtest.h"
#include"src/sort_algorithms/insert_sort/insertsort_test.h"
#include"src/sort_algorithms/quick_sort/quicksort_test.h"
#include"src/sort_algorithms/merge_sort/mergesort_test.h"
#include"src/sort_algorithms/heap_sort/heapsort_test.h"
#include"src/sort_algorithms/count_sort/countsort_test.h"
#include"src/sort_algorithms/radix_sort/radixsort_test.h"
#include"src/sort_algorithms/bucket_sort/bucketsort_test.h"
#include"src/select_algorithms/randomized_select/randomizedselect_test.h"
#include"src/select_algorithms/good_select/goodselect_test.h"
#include"src/dynamic_programming_algorithms/lcs/longest_common_subsequence_test.h"
#include"src/tree_algorithms/binarytreenode/binarytreenode_test.h"
#include"src/tree_algorithms/binarytree/binarytree_test.h"
#include"src/tree_algorithms/searchtree/searchtree_test.h"
#include"src/queue_algorithms/min_queue/minqueue_test.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_vertex/vertex_test.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_edge/edge_test.h"
#include"src/graph_algorithms/basic_graph/graph_representation/matrix_graph/matrixgraph_test.h"
#include"src/graph_algorithms/basic_graph/graph_representation/adjlist_graph/adjlistgraph_test.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph/graph_test.h"
#include"src/graph_algorithms/basic_graph/graph_bfs/bfs_test.h"
#include"src/graph_algorithms/basic_graph/graph_dfs/dfs_test.h"
#include"src/graph_algorithms/basic_graph/topology_sort/topologysort_test.h"
#include"src/graph_algorithms/basic_graph/strong_connected_component/strongconnectedcomponent_test.h"
#include"src/queue_algorithms/min_queue/minqueue_test.h"
#include"src/set_algorithms/disjoint_set/disjointset_test.h"
int main(int argc,char** argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

