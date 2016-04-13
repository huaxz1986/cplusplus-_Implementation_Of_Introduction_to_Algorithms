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
#ifndef STRONGCONNECTEDCOMPONENT_TEST
#define STRONGCONNECTEDCOMPONENT_TEST
#include"src/google_test/gtest.h"
#include"strongconnectedcomponent.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph/graph.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_vertex/dfs_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::DFS_Vertex;
using IntroductionToAlgorithm::GraphAlgorithm::scc;

namespace {
    const int SCC_N= 10;  /*!< 测试的图顶点数量*/
}


//!SCCTest:测试类，用于为测试提供基础数据
/*!
*
* `SCCTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class SCCTest:public ::testing::Test
{
public:
typedef Graph<SCC_N,DFS_Vertex<double>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`DFS_Vertex<double>`*/

protected:
    void SetUp()
    {



        //****  含顶点图和边图：10个顶点，9条边  ****
        _list_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<SCC_N;i++)
            _list_graph->add_vertex(1+i/SCC_N);
        for(int i=0;i<SCC_N-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,10+i)); //该图的边是从左到右组成一个链条

        //****  含顶点图和边图：10个顶点，10条边  ****
        _scc_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<SCC_N;i++)
            _scc_graph->add_vertex(1+i/SCC_N);
        for(int i=0;i<SCC_N-1;i++)
                _scc_graph->add_edge(std::make_tuple(i,i+1,10+i));
        _scc_graph->add_edge(std::make_tuple(SCC_N-1,0,10+SCC_N-1));
    }
    void TearDown(){}
    std::shared_ptr<GType> _list_graph;  /*!< 指向一个图，该图的边组成一个链条*/
    std::shared_ptr<GType> _scc_graph;   /*!< 指向一个图，该图的边组成一个环*/
};


//!test_scc:测试scc方法
/*!
*
* 测试`scc`方法
*/
TEST_F(SCCTest,test_scc)
{
    typedef  DFS_Vertex<double>::VIDType VIDType;
    //****** 测试一条链边的图**********
    EXPECT_EQ(scc(_list_graph).size(),0);
    //****** 测试环状图**********
    auto result=scc(_scc_graph);
    std::vector<VIDType> real_vertexes;
    for(int i=0;i<SCC_N;i++)
        real_vertexes.push_back(i);
    std::sort(real_vertexes.begin(),real_vertexes.end());


    EXPECT_EQ(result.size(),1);
    auto scc_vertexes=result.at(0);
    std::sort(scc_vertexes.begin(),scc_vertexes.end());
    EXPECT_EQ(scc_vertexes,real_vertexes);

}
#endif // STRONGCONNECTEDCOMPONENT_TEST

