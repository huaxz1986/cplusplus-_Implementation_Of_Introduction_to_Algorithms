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
#ifndef MATRIXGRAPH_TEST
#define MATRIXGRAPH_TEST
#include"src/google_test/gtest.h"
#include"matrixgraph.h"
#include<memory>
namespace  {
    const int MTXNUM =10; /*!< 测试的图顶点数量*/
}

using IntroductionToAlgorithm::GraphAlgorithm::MatrixGraph;
//!GraphMatrixTest:测试类，用于为测试提供基础数据
/*!
*
* `GraphMatrixTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class GraphMatrixTest:public ::testing::Test
{
protected:
    void SetUp(){
        graph=std::make_shared<MatrixGraph<MTXNUM> >(-1);
    }
    void TearDown(){}

    std::shared_ptr<MatrixGraph<MTXNUM> > graph;/*!< 指向一个图*/
};

//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`weight`方法成员。
*/
TEST_F(GraphMatrixTest,test_weight)
{
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
            EXPECT_THROW(graph->weight(i,j),std::invalid_argument)<<"i:"<<i<<"\t j:"<<j;
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`has_edge`方法成员。
*/
TEST_F(GraphMatrixTest,test_has_edge)
{
    EXPECT_THROW(graph->has_edge(-1,0),std::invalid_argument);
    EXPECT_THROW(graph->has_edge(MTXNUM,0),std::invalid_argument);
    EXPECT_THROW(graph->has_edge(0,-1),std::invalid_argument);
    EXPECT_THROW(graph->has_edge(0,MTXNUM),std::invalid_argument);
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
            EXPECT_FALSE(graph->has_edge(i,j))<<"i:"<<i<<"\t j:"<<j;
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`add_edge`方法成员。
*/
TEST_F(GraphMatrixTest,test_add_edge)
{
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            graph->add_edge(std::make_tuple(i,j,i*j));
            EXPECT_EQ(graph->weight(i,j),i*j)<<"i:"<<i<<"\t j:"<<j;
        }
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            EXPECT_THROW(graph->add_edge(std::make_tuple(i,j,9)),std::invalid_argument)<<"i:"<<i<<"\t j:"<<j;
        }
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`add_edges`方法成员。
*/
TEST_F(GraphMatrixTest,test_add_edges)
{
    std::vector<typename MatrixGraph<MTXNUM>::EdgeTupleType> tuples;
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            tuples.push_back(std::make_tuple(i,j,9));
        }
    graph->add_edges(tuples.begin(),tuples.end());

    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
            EXPECT_TRUE(graph->has_edge(i,j))<<"i:"<<i<<"\t j:"<<j;
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`adjust_edge`方法成员。
*/
TEST_F(GraphMatrixTest,test_adjust_edge)
{
    for(int i=0;i<MTXNUM;i++)
            for(int j=0;j<MTXNUM;j++)
                EXPECT_THROW(graph->adjust_edge(i,j,99),std::invalid_argument)<<"i:"<<i<<"\t j:"<<j;
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            graph->add_edge(std::make_tuple(i,j,9));
        }
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            graph->adjust_edge(i,j,i*j);
            EXPECT_EQ(graph->weight(i,j),i*j);
        }
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`edge_tuples`方法成员。
*/
TEST_F(GraphMatrixTest,test_edge_tuples)
{
    std::vector<typename MatrixGraph<MTXNUM>::EdgeTupleType> real;
    EXPECT_EQ(graph->edge_tuples(), real);
    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            real.push_back(std::make_tuple(i,j,i*j));
            graph->add_edge(std::make_tuple(i,j,i*j));
            EXPECT_EQ(graph->edge_tuples(),real)<<"i:"<<i<<"\t j:"<<j;
        }
}

//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`vertex_edge_tuples`方法成员。
*/
TEST_F(GraphMatrixTest,test_vertex_edge_tuples)
{

    for(int i=0;i<MTXNUM;i++)
        EXPECT_EQ(graph->vertex_edge_tuples(i).size(), 0);

    for(int i=0;i<MTXNUM;i++)
        for(int j=0;j<MTXNUM;j++)
        {
            graph->add_edge(std::make_tuple(i,j,i*j));
        }
    for(int i=0;i<MTXNUM;i++)
    {
        std::vector<typename MatrixGraph<MTXNUM>::EdgeTupleType> real;
        for(int j=0;j<MTXNUM;j++)
        {
            real.push_back(std::make_tuple(i,j,i*j));
        }
        EXPECT_EQ(graph->vertex_edge_tuples(i),real)<<"i:"<<i;
    }
}

#endif // MATRIXGRAPH_TEST

