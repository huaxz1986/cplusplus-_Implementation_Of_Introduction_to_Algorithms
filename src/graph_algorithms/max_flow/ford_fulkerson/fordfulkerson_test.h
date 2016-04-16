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
#ifndef FORDFULKERSON_TEST
#define FORDFULKERSON_TEST
#include"src/google_test/gtest.h"
#include"fordfulkerson.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph/graph.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_vertex/bfs_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::BFS_Vertex;
using IntroductionToAlgorithm::GraphAlgorithm::ford_fulkerson;
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;

namespace {
    const int FF_N= 6;  /*!< 测试的图顶点数量*/
}

//!FordFulkersonTest:测试类，用于为测试提供基础数据
/*!
*
* `FordFulkersonTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class FordFulkersonTest:public ::testing::Test
{
public:
typedef Graph<FF_N,BFS_Vertex<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`BFS_Vertex<int>`*/

protected:
    void SetUp()
    {

        //****  算法导论图26-6   ****
        _graph=std::make_shared<GType>(0); //边的无效权重为0
        for(int i=0;i<FF_N;i++)
            _graph->add_vertex(0);

        _graph->add_edge(std::make_tuple(0,1,16));
        _graph->add_edge(std::make_tuple(0,2,13));
        _graph->add_edge(std::make_tuple(1,3,12));
        _graph->add_edge(std::make_tuple(2,1,4));
        _graph->add_edge(std::make_tuple(2,4,14));
        _graph->add_edge(std::make_tuple(3,2,9));
        _graph->add_edge(std::make_tuple(3,5,20));
        _graph->add_edge(std::make_tuple(4,3,7));
        _graph->add_edge(std::make_tuple(4,5,4));
    }
    void TearDown(){}
    std::shared_ptr<GType> _graph;    /*!< 指向一个图，算法导论图26-6*/
};

//!FordFulkersonTest:测试 ford_fulkerson 算法
/*!
*
* `test_ford_fulkerson`：测试 ford_fulkerson 算法
*/
TEST_F(FordFulkersonTest,test_ford_fulkerson)
{
    typedef std::array<std::array<typename GType::EWeightType,FF_N>,FF_N> MatrixType;
    MatrixType real_flow={std::array<typename GType::EWeightType,FF_N>({0,12,11,0,0,0}),\
                            std::array<typename GType::EWeightType,FF_N>({0,0,0,12,0,0}),\
                            std::array<typename GType::EWeightType,FF_N>({0,0,0,0,11,0}),\
                            std::array<typename GType::EWeightType,FF_N>({0,0,0,0,0,19}),\
                            std::array<typename GType::EWeightType,FF_N>({0,0,0,7,0,4}),\
                            std::array<typename GType::EWeightType,FF_N>({0,0,0,0,0,0})};
    EXPECT_EQ(ford_fulkerson(_graph,0,5),real_flow);
}

#endif // FORDFULKERSON_TEST

