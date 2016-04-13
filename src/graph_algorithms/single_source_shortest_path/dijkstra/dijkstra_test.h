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
#ifndef DIJKSTRA_TEST
#define DIJKSTRA_TEST
#include"src/google_test/gtest.h"
#include"dijkstra.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
#include"../../basic_graph/graph_representation/graph_vertex/vertexp.h"

using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::VertexP;
using IntroductionToAlgorithm::GraphAlgorithm::dijkstra;

namespace{
    const int DIJK_NUM=10;  /*!< 图顶点数量*/
}


//!DijkstraTest:测试类，用于为测试提供基础数据
/*!
*
* `DijkstraTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class DijkstraTest:public ::testing::Test
{
public:
    typedef Graph<DIJK_NUM,VertexP<int>> GraphType; /*!< 模板实例化的图类型，该图的顶点类型为`VertexP<int>`*/
    typedef VertexP<int> VertexType; /*!< 图的顶点类型为`VertexP<int>`*/
protected:
    void SetUp()
    {
        _1v_graph=std::make_shared<GraphType>(-1);//边的无效权重为-1
        _1v_graph->add_vertex(0);  //该图只有一个顶点

        _1e_graph=std::make_shared<GraphType>(-1);//边的无效权重为-1
        _1e_graph->add_vertex(0);
        _1e_graph->add_vertex(0);
        _1e_graph->add_edge(std::make_tuple(0,1,1));  //该图只有一条边


        //****  含顶点图和边图：10个顶点，9条边：0-->1-->2....-->9(权重均为1)   ****
        _normal_graph=std::make_shared<GraphType>(-1); //边的无效权重为-1
        for(int i=0;i<DIJK_NUM;i++)
            _normal_graph->add_vertex(0);
        for(int i=0;i<DIJK_NUM-1;i++)
                _normal_graph->add_edge(std::make_tuple(i,i+1,1)); //该图的边是从左到右组成一个链条
    }
    void TearDown(){}

    std::shared_ptr<GraphType> _1v_graph; /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GraphType> _1e_graph; /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GraphType> _normal_graph; /*!< 指向一个图，该图的边组成一条链条*/
};

//!DijkstraTest:测试单源最短路径的的dijkstra算法
/*!
* `test_dijkstra`:测试单源最短路径的的dijkstra算法
*/
TEST_F(DijkstraTest,test_dijkstra)
{
    //************  只有一个顶点的图  ************
    EXPECT_THROW(dijkstra(_1v_graph,1),std::invalid_argument);
    dijkstra(_1v_graph,0);
    EXPECT_EQ(_1v_graph->vertexes[0]->key,0);
    //**********  只有一条边的图  ***************
    dijkstra(_1e_graph,0);
    EXPECT_EQ(_1e_graph->vertexes[0]->key,0);
    EXPECT_EQ(_1e_graph->vertexes[1]->key,1);
    EXPECT_EQ(_1e_graph->vertexes[1]->parent,_1e_graph->vertexes[0]);
    //**********  链边的图 ***************
    dijkstra(_normal_graph,0);
    EXPECT_EQ(_normal_graph->vertexes[0]->key,0);
    for(int i=1;i<DIJK_NUM;i++)
    {
        EXPECT_EQ(_normal_graph->vertexes[i]->key,i);
        EXPECT_EQ(_normal_graph->vertexes[i]->parent,_normal_graph->vertexes[i-1]);
    }
}

#endif // DIJKSTRA_TEST

