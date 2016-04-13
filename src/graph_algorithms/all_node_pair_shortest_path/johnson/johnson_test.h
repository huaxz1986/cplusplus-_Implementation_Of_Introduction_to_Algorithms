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
#ifndef JOHNSON_TEST
#define JOHNSON_TEST
#include"src/google_test/gtest.h"
#include"johnson.h"
#include"../../basic_graph/graph_representation/graph_vertex/vertexp.h"
#include"../../basic_graph/graph_representation/graph/graph.h"

using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::VertexP;
using IntroductionToAlgorithm::GraphAlgorithm::johnson;
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;

namespace {
    const int JS_N= 5;  /*!< 测试的图顶点数量*/
}

//!JohnsonTest:测试类，用于为测试提供基础数据
/*!
*
* `JohnsonTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class JohnsonTest:public ::testing::Test
{
public:
typedef Graph<JS_N,VertexP<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`VertexP<int>`*/

protected:
    void SetUp()
    {

        //****  算法导论图25-1   ****
        _graph=std::make_shared<GType>(unlimit<int>()); //边的无效权重为正无穷
        for(int i=0;i<JS_N;i++)
            _graph->add_vertex(0);

        _graph->add_edge(std::make_tuple(0,1,3));
        _graph->add_edge(std::make_tuple(0,2,8));
        _graph->add_edge(std::make_tuple(0,4,-4));
        _graph->add_edge(std::make_tuple(1,3,1));
        _graph->add_edge(std::make_tuple(1,4,7));
        _graph->add_edge(std::make_tuple(2,1,4));
        _graph->add_edge(std::make_tuple(3,2,-5));
        _graph->add_edge(std::make_tuple(3,0,2));
        _graph->add_edge(std::make_tuple(4,3,6));
    }
    void TearDown(){}
    std::shared_ptr<GType> _graph;    /*!< 指向一个图，算法导论图25-1*/
};

//!JohnsonTest:测试 johnson 算法
/*!
*
* `test_johnson`：测试 johnson 算法
*/
TEST_F(JohnsonTest,test_johnson)
{
    typedef std::array<std::array<typename GType::EWeightType,JS_N>,JS_N> MatrixType;
    MatrixType real_D={std::array<typename GType::EWeightType,JS_N>({0,1,-3,2,-4}),\
                            std::array<typename GType::EWeightType,JS_N>({3,0,-4,1,-1}),\
                            std::array<typename GType::EWeightType,JS_N>({7,4,0,5,3}),\
                            std::array<typename GType::EWeightType,JS_N>({2,-1,-5,0,-2}),\
                            std::array<typename GType::EWeightType,JS_N>({8,5,1,6,0})};
    EXPECT_EQ(johnson(_graph),real_D);
}

#endif // JOHNSON_TEST

