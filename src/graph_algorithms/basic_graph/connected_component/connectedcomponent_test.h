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
#ifndef CONNECTEDCOMPONENT_TEST
#define CONNECTEDCOMPONENT_TEST
#include"src/google_test/gtest.h"
#include"connectedcomponent.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
#include"../../basic_graph/graph_representation/graph_vertex/set_vertex.h"

using IntroductionToAlgorithm::GraphAlgorithm::SetVertex;
using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::connected_component;
using IntroductionToAlgorithm::GraphAlgorithm::same_component;
namespace{
    const int C_NUM=10;  /*!< 图顶点数量*/
}

//!ConnectedComponentTest:测试类，用于为测试提供基础数据
/*!
*
* `ConnectedComponentTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class ConnectedComponentTest:public ::testing::Test
{
public:
    typedef Graph<C_NUM,SetVertex<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`SetVertex<int>`*/
protected:
    void SetUp()
    {

        _graph=std::make_shared<GType>(-1);//边的无效权重为-1
        for(int i=0;i<C_NUM;i++)
            _graph->add_vertex(0);

        for(int i=1;i<C_NUM/2;i++) //边 0--1--2--...--C_NUM/2-1
            _graph->add_edge(std::make_tuple(i-1,i,9999));

        for(int i=C_NUM/2+1;i<C_NUM;i++)//边 C_NUM/2--C_NUM/2+1...--C_NUM-1
            _graph->add_edge(std::make_tuple(i-1,i,8888));
    }
    void TearDown(){}

    std::shared_ptr<GType> _graph; /*!< 测试连通分量的图的强指针*/
};

//!test_connected_component：测试connected_component
/*!
*
* `test_connected_component`：测试`connected_component()`函数
*/
TEST_F(ConnectedComponentTest,test_connected_component)
{
    connected_component(_graph);

    for(int i=0;i<C_NUM/2;i++) //tree_root:u, tree_root:v, rank小的挂在rank大的之下；若二者rank相等，则u挂在v下
        EXPECT_EQ(_graph->vertexes.at(i)->node->parent,_graph->vertexes.at(1)->node);//所以结点1是最终根结点

    for(int i=C_NUM/2;i<C_NUM;i++) //tree_root:u, tree_root:v, rank小的挂在rank大的之下；若二者rank相等，则u挂在v下
        EXPECT_EQ(_graph->vertexes.at(i)->node->parent,_graph->vertexes.at(C_NUM/2+1)->node);//所以结点`C_NUM/2+1`是最终根结点
}
//!test_same_component：测试same_component
/*!
*
* `test_same_component`：测试`same_component()`函数
*/
TEST_F(ConnectedComponentTest,test_same_component)
{
    connected_component(_graph);
    for(int i=0;i<C_NUM/2;i++)   //前一半：位于同一个连通分量
        for(int j=i+1;j<C_NUM/2;j++)
            EXPECT_TRUE(same_component(_graph,i,j));

    for(int i=C_NUM/2;i<C_NUM;i++)   //后一半：位于同一个连通分量
        for(int j=i+1;j<C_NUM;j++)
            EXPECT_TRUE(same_component(_graph,i,j));

    for(int i=0;i<C_NUM/2;i++)   //前一半与后一半：位于不同的连通分量
        for(int j=C_NUM/2;j<C_NUM;j++)
            EXPECT_FALSE(same_component(_graph,i,j));
}

#endif // CONNECTEDCOMPONENT_TEST

