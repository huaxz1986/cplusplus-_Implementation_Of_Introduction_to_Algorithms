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
#ifndef GENERICPUSHRELABEL_TEST
#define GENERICPUSHRELABEL_TEST
#include"src/google_test/gtest.h"
#include"genericpushrelabel.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph/graph.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_vertex/flow_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::FlowVertex;
using IntroductionToAlgorithm::GraphAlgorithm::generic_push_relabel;
using IntroductionToAlgorithm::GraphAlgorithm::initialize_preflow;
using IntroductionToAlgorithm::GraphAlgorithm::min_v_at_Ef;
using IntroductionToAlgorithm::GraphAlgorithm::push;
using IntroductionToAlgorithm::GraphAlgorithm::relabel;
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;

namespace {
    const int PR_N= 6;  /*!< 测试的图顶点数量*/
}

//!GenericPushRelabelTest:测试类，用于为测试提供基础数据
/*!
*
* `GenericPushRelabelTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class GenericPushRelabelTest:public ::testing::Test
{
public:
typedef Graph<PR_N,FlowVertex<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`FlowVertex<int>`*/

protected:
    void SetUp()
    {

        //****  算法导论图26-6   ****
        _graph=std::make_shared<GType>(0); //边的无效权重为0
        for(int i=0;i<PR_N;i++)
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


//!GenericPushRelabelTest:测试 initialize_preflow 函数
/*!
*
* `test_initialize_preflow`：测试 initialize_preflow 函数
*/
TEST_F(GenericPushRelabelTest,test_initialize_preflow)
{
    std::array<std::array<int,PR_N>,PR_N> flow;
    initialize_preflow(_graph,0,flow);


    EXPECT_EQ(_graph->vertexes[0]->key,-29); // e(s)
    EXPECT_EQ(_graph->vertexes[0]->h,PR_N); // h(s)
    EXPECT_EQ(_graph->vertexes[1]->key,16); // e(v)
    EXPECT_EQ(_graph->vertexes[1]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[2]->key,13); // e(v)
    EXPECT_EQ(_graph->vertexes[2]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[3]->key,0); // e(v)
    EXPECT_EQ(_graph->vertexes[3]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[4]->key,0); // e(v)
    EXPECT_EQ(_graph->vertexes[4]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[5]->key,0); // e(t)
    EXPECT_EQ(_graph->vertexes[5]->h,0); // h(t)


    for(int i=0;i<PR_N;i++)
        for(int j=0;j<PR_N;j++)
        {
            if(i==0&&j==1) EXPECT_EQ(flow[i][j],16);
            else if(i==0&&j==2) EXPECT_EQ(flow[i][j],13);
            else EXPECT_EQ(flow[i][j],0);
        }
}
//!GenericPushRelabelTest:测试 min_v_at_Ef 函数
/*!
*
* `test_min_v_at_Ef`：测试 min_v_at_Ef 函数
*/
TEST_F(GenericPushRelabelTest,test_min_v_at_Ef)
{
    std::array<std::array<int,PR_N>,PR_N> flow;
    initialize_preflow(_graph,0,flow);

    EXPECT_EQ(min_v_at_Ef(_graph,1,flow),3);
    EXPECT_EQ(min_v_at_Ef(_graph,2,flow),1);
    EXPECT_EQ(min_v_at_Ef(_graph,3,flow),2);
    EXPECT_EQ(min_v_at_Ef(_graph,4,flow),3);
}
//!GenericPushRelabelTest:测试 push 函数
/*!
*
* `test_push`：测试 push 函数
*/
TEST_F(GenericPushRelabelTest,test_push)
{

    std::array<std::array<int,PR_N>,PR_N> flow;
    initialize_preflow(_graph,0,flow);
    _graph->vertexes[1]->h=1;  //手动提升

    push(_graph,1,3,flow);

    EXPECT_EQ(_graph->vertexes[0]->key,-29); // e(s)
    EXPECT_EQ(_graph->vertexes[0]->h,PR_N); // h(s)
    EXPECT_EQ(_graph->vertexes[1]->key,4); // e(v)
    EXPECT_EQ(_graph->vertexes[1]->h,1); // h(v)
    EXPECT_EQ(_graph->vertexes[2]->key,13); // e(v)
    EXPECT_EQ(_graph->vertexes[2]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[3]->key,12); // e(v)
    EXPECT_EQ(_graph->vertexes[3]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[4]->key,0); // e(v)
    EXPECT_EQ(_graph->vertexes[4]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[5]->key,0); // e(t)
    EXPECT_EQ(_graph->vertexes[5]->h,0); // h(t)



    for(int i=0;i<PR_N;i++)
        for(int j=0;j<PR_N;j++)
        {
            if(i==0&&j==1) EXPECT_EQ(flow[i][j],16);
            else if(i==0&&j==2) EXPECT_EQ(flow[i][j],13);
            else if(i==1&&j==3) EXPECT_EQ(flow[i][j],12);
            else EXPECT_EQ(flow[i][j],0);
        }

}
//!GenericPushRelabelTest:测试 relabel 函数
/*!
*
* `test_relabel`：测试 relabel 函数
*/
TEST_F(GenericPushRelabelTest,test_relabel)
{
    std::array<std::array<int,PR_N>,PR_N> flow;
    initialize_preflow(_graph,0,flow);
    relabel(_graph,1,flow);

    EXPECT_EQ(_graph->vertexes[0]->key,-29); // e(s)
    EXPECT_EQ(_graph->vertexes[0]->h,PR_N); // h(s)
    EXPECT_EQ(_graph->vertexes[1]->key,16); // e(v)
    EXPECT_EQ(_graph->vertexes[1]->h,1); // h(v)
    EXPECT_EQ(_graph->vertexes[2]->key,13); // e(v)
    EXPECT_EQ(_graph->vertexes[2]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[3]->key,0); // e(v)
    EXPECT_EQ(_graph->vertexes[3]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[4]->key,0); // e(v)
    EXPECT_EQ(_graph->vertexes[4]->h,0); // h(v)
    EXPECT_EQ(_graph->vertexes[5]->key,0); // e(t)
    EXPECT_EQ(_graph->vertexes[5]->h,0); // h(t)

    for(int i=0;i<PR_N;i++)
        for(int j=0;j<PR_N;j++)
        {
            if(i==0&&j==1) EXPECT_EQ(flow[i][j],16);
            else if(i==0&&j==2) EXPECT_EQ(flow[i][j],13);
            else EXPECT_EQ(flow[i][j],0);
        }

}
//!GenericPushRelabelTest:测试 generic_push_relabel 算法
/*!
*
* `test_generic_push_relabel`：测试 generic_push_relabel 算法
*/
TEST_F(GenericPushRelabelTest,test_generic_push_relabel)
{
    typedef std::array<std::array<typename GType::EWeightType,PR_N>,PR_N> MatrixType;
    MatrixType real_flow={std::array<typename GType::EWeightType,PR_N>({0,12,11,0,0,0}),\
                            std::array<typename GType::EWeightType,PR_N>({0,0,0,12,0,0}),\
                            std::array<typename GType::EWeightType,PR_N>({0,0,0,0,11,0}),\
                            std::array<typename GType::EWeightType,PR_N>({0,0,0,0,0,19}),\
                            std::array<typename GType::EWeightType,PR_N>({0,0,0,7,0,4}),\
                            std::array<typename GType::EWeightType,PR_N>({0,0,0,0,0,0})};
    EXPECT_EQ(generic_push_relabel(_graph,0,5),real_flow);
}

#endif // GENERICPUSHRELABEL_TEST

