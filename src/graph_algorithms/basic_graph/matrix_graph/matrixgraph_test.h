#ifndef MATRIXGRAPH_TEST
#define MATRIXGRAPH_TEST
#include"src/google_test/gtest.h"
#include"matrixgraph.h"
#define NUM 10
using IntrodunctionToAlgorithm::GraphAlgorithm::MatrixGraph;
//!GraphMatrixTest:测试类，用于为测试提供基础数据
/*!
*
* `GraphMatrixTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class GraphMatrixTest:public ::testing::Test
{
protected:
    void SetUp(){
        graph=std::make_shared<MatrixGraph<NUM> >(-1);
    }
    void TearDown(){}

    std::shared_ptr<MatrixGraph<NUM> > graph;/*!< 指向一个图*/
};

//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`weight`方法成员。
*/
TEST_F(GraphMatrixTest,test_weight)
{
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
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
    EXPECT_THROW(graph->has_edge(NUM,0),std::invalid_argument);
    EXPECT_THROW(graph->has_edge(0,-1),std::invalid_argument);
    EXPECT_THROW(graph->has_edge(0,NUM),std::invalid_argument);
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
            EXPECT_FALSE(graph->has_edge(i,j))<<"i:"<<i<<"\t j:"<<j;
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`add_edge`方法成员。
*/
TEST_F(GraphMatrixTest,test_add_edge)
{
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
        {
            graph->add_edge(std::make_tuple(i,j,i*j));
            EXPECT_EQ(graph->weight(i,j),i*j)<<"i:"<<i<<"\t j:"<<j;
        }
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
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
    std::vector<typename MatrixGraph<NUM>::EdgeTupleType> tuples;
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
        {
            tuples.push_back(std::make_tuple(i,j,9));
        }
    graph->add_edges(tuples.begin(),tuples.end());

    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
            EXPECT_TRUE(graph->has_edge(i,j))<<"i:"<<i<<"\t j:"<<j;
}
//!matrix_graph_test:MatrixGraph
/*!
*
* 测试`adjust_edge`方法成员。
*/
TEST_F(GraphMatrixTest,test_adjust_edge)
{
    for(int i=0;i<NUM;i++)
            for(int j=0;j<NUM;j++)
                EXPECT_THROW(graph->adjust_edge(i,j,99),std::invalid_argument)<<"i:"<<i<<"\t j:"<<j;
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
        {
            graph->add_edge(std::make_tuple(i,j,9));
        }
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
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
    std::vector<typename MatrixGraph<NUM>::EdgeTupleType> real;
    EXPECT_EQ(graph->edge_tuples(), real);
    for(int i=0;i<NUM;i++)
        for(int j=0;j<NUM;j++)
        {
            real.push_back(std::make_tuple(i,j,i*j));
            graph->add_edge(std::make_tuple(i,j,i*j));
            EXPECT_EQ(graph->edge_tuples(),real)<<"i:"<<i<<"\t j:"<<j;
        }
}

#endif // MATRIXGRAPH_TEST

