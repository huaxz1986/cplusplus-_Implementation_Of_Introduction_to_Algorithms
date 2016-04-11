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
#ifndef GRAPH_TEST
#define GRAPH_TEST
#include"src/google_test/gtest.h"
#include"../graph_vertex/vertex.h"
#include"graph.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::Vertex;

namespace {
    const int G_N= 10; /*!< 测试的图顶点数量*/
}

//!GraphTest:测试类，用于为测试提供基础数据
/*!
*
* `GraphTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class GraphTest:public ::testing::Test
{
public:
typedef Graph<G_N,Vertex<double>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`Vertex<double>`*/

protected:
    void SetUp(){
        //****  空图：0个顶点，0条边   ****
        _empty_graph=std::make_shared<GType>(-1); //边的无效权重为-1

        //****  含顶点图：10个顶点   ****
        _n_vertexes_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<G_N;i++)
            _n_vertexes_graph->add_vertex(i/G_N);
        //****  含顶点图和边图：10个顶点，9条边   ****
        _n_vertexes_m_edges_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<G_N;i++)
            _n_vertexes_m_edges_graph->add_vertex(1+i/G_N);
        for(int i=0;i<G_N;i++)
            for(int j=i+1;j<G_N;j++)
                _n_vertexes_m_edges_graph->add_edge(std::make_tuple(i,j,i*10+j));
    }
    void TearDown(){}

    std::shared_ptr<GType> _empty_graph;    /*!< 指向一个空图*/
    std::shared_ptr<GType> _n_vertexes_graph; /*!< 指向一个含有n结点,0条边的图*/
    std::shared_ptr<GType> _n_vertexes_m_edges_graph; /*!< 指向一个含有n结点,m条边的图*/
};

//!graph_test:Graph
/*!
*
* 测试`add_vertex`方法成员。
*/
TEST_F(GraphTest,test_add_vertex)
{
    for(int i=0;i<G_N;i++) //空图：可以任意添加顶点
    {
        EXPECT_EQ(_empty_graph->add_vertex(i),i);
        EXPECT_NEAR(_empty_graph->vertexes.at(i)->key,i,0.01);
        EXPECT_EQ(_empty_graph->vertexes.at(i)->id,i);
    }
    for(int i=0;i<G_N;i++) //满图：不可以添加顶点
    {
        EXPECT_THROW(_empty_graph->add_vertex(i),std::invalid_argument);
        EXPECT_THROW(_n_vertexes_graph->add_vertex(i),std::invalid_argument);
        EXPECT_THROW(_n_vertexes_m_edges_graph->add_vertex(i),std::invalid_argument);
    }
}
//!graph_test:Graph
/*!
*
* 测试另一个`add_vertex`方法成员，该`add_vertex`添加了`id`信息。
*/
TEST_F(GraphTest,test_add_vertex_with_id)
{
    for(int i=0;i<G_N;i++) //空图：可以任意添加顶点
    {
        EXPECT_EQ(_empty_graph->add_vertex(i,G_N-i-1),G_N-i-1);
    }
    for(int i=0;i<G_N;i++)
    {
        EXPECT_NEAR(_empty_graph->vertexes.at(i)->key,G_N-i-1,0.01);
        EXPECT_EQ(_empty_graph->vertexes.at(i)->id,i);
    }
    for(int i=0;i<G_N;i++)//满图：不可以添加顶点
    {
        EXPECT_THROW(_empty_graph->add_vertex(i,i),std::invalid_argument);
        EXPECT_THROW(_n_vertexes_graph->add_vertex(i,i),std::invalid_argument);
        EXPECT_THROW(_n_vertexes_m_edges_graph->add_vertex(i,i),std::invalid_argument);
    }
}
//!graph_test:Graph
/*!
*
* 测试`modify_vertex`方法成员。
*/
TEST_F(GraphTest,test_modify_vertex)
{
    for(int i=0;i<G_N;i++) //空图：不可以修改顶点
    {
        EXPECT_THROW(_empty_graph->modify_vertex(1.0,i),std::invalid_argument);
    }
    for(int i=0;i<G_N;i++)  //满图：可以任意修改顶点
    {
        EXPECT_NEAR(_n_vertexes_graph->vertexes.at(i)->key,i/G_N,0.01);
        _n_vertexes_graph->modify_vertex(9.0,i);
        EXPECT_NEAR(_n_vertexes_graph->vertexes.at(i)->key,9.0,0.01);
        EXPECT_NEAR(_n_vertexes_m_edges_graph->vertexes.at(i)->key,1+i/G_N,0.01);
        _n_vertexes_m_edges_graph->modify_vertex(10.0,i);
        EXPECT_NEAR(_n_vertexes_m_edges_graph->vertexes.at(i)->key,10.0,0.01);
    }
}

//!graph_test:Graph
/*!
*
* 测试`weight`方法成员。
*/
TEST_F(GraphTest,test_weight)
{
    for(int i=0;i<G_N;i++)
        for(int j=0;j<G_N;j++)
        {
            EXPECT_THROW(_empty_graph->weight(i,j),std::invalid_argument);    //空图：没有顶点没有边
            EXPECT_THROW(_n_vertexes_graph->weight(i,j),std::invalid_argument);//无边有顶点的图：没有边
            if(j<=i)
                EXPECT_THROW(_n_vertexes_m_edges_graph->weight(i,j),std::invalid_argument);
            else
                EXPECT_EQ(_n_vertexes_m_edges_graph->weight(i,j),i*10+j);
        }
}
//!graph_test:Graph
/*!
*
* 测试`has_edge`方法成员。
*/
TEST_F(GraphTest,test_has_edge)
{
    for(int i=0;i<G_N;i++)
        for(int j=0;j<G_N;j++)
        {
            EXPECT_THROW(_empty_graph->has_edge(i,j),std::invalid_argument); //空图：没有顶点没有边
            EXPECT_FALSE(_n_vertexes_graph->has_edge(i,j));   //无边有顶点的图：没有边
            if(j<=i)
                EXPECT_FALSE(_n_vertexes_m_edges_graph->has_edge(i,j));
            else
                EXPECT_TRUE(_n_vertexes_m_edges_graph->has_edge(i,j));
        }
}
//!graph_test:Graph
/*!
*
* 测试`add_edge`方法成员。
*/
TEST_F(GraphTest,test_add_edge)
{
    for(int i=0;i<G_N;i++)
        for(int j=0;j<G_N;j++)
        {
            EXPECT_THROW(_empty_graph->add_edge(std::make_tuple(i,j,i*j)),std::invalid_argument);  //空图：没有顶点没有边
            _n_vertexes_graph->add_edge(std::make_tuple(i,j,i*j));  //无边有顶点的图：没有边
            EXPECT_EQ(_n_vertexes_graph->weight(i,j),i*j);
            if(j<=i)
            {
                _n_vertexes_m_edges_graph->add_edge(std::make_tuple(i,j,i*j));
                EXPECT_EQ(_n_vertexes_m_edges_graph->weight(i,j),i*j);
            }else
            {
                EXPECT_THROW(_n_vertexes_m_edges_graph->add_edge(std::make_tuple(i,j,i*j)),std::invalid_argument);
            }
        }
}
//!graph_test:Graph
/*!
*
* 测试`add_edges`方法成员。
*/
TEST_F(GraphTest,test_add_edges)
{
    std::vector<typename GType::EdgeTupleType> tuples;
    for(int i=0;i<G_N;i++)
        for(int j=0;j<G_N;j++)
        {
            tuples.push_back(std::make_tuple(i,j,9));
        }
    EXPECT_THROW(_empty_graph->add_edges(tuples.begin(),tuples.end()),std::invalid_argument);  //空图：没有顶点没有边
    _n_vertexes_graph->add_edges(tuples.begin(),tuples.end());  //无边有顶点的图：没有边
    EXPECT_EQ(_n_vertexes_graph->edge_tuples(),tuples);
    EXPECT_THROW(_n_vertexes_m_edges_graph->add_edges(tuples.begin(),tuples.end()),std::invalid_argument);
}
//!graph_test:Graph
/*!
*
* 测试`adjust_edge`方法成员。
*/
TEST_F(GraphTest,test_adjust_edge)
{
    for(int i=0;i<G_N;i++)
        for(int j=0;j<G_N;j++)
        {
            EXPECT_THROW(_empty_graph->adjust_edge(i,j,0),std::invalid_argument);//空图：没有顶点没有边
            EXPECT_THROW(_n_vertexes_graph->adjust_edge(i,j,0),std::invalid_argument); //无边有顶点的图：没有边
            if(j<=i)
            {
                EXPECT_THROW(_n_vertexes_m_edges_graph->adjust_edge(i,j,0),std::invalid_argument);
            }else
            {
                _n_vertexes_m_edges_graph->adjust_edge(i,j,i*j);
                EXPECT_EQ(_n_vertexes_m_edges_graph->weight(i,j),i*j);
            }
        }
}
//!graph_test:Graph
/*!
*
* 测试`edge_tuples`方法成员。
*/
TEST_F(GraphTest,test_edge_tuples)
{
    EXPECT_EQ(_empty_graph->edge_tuples().size(),0);//空图：没有顶点没有边
    EXPECT_EQ(_n_vertexes_graph->edge_tuples().size(),0);//无边有顶点的图：没有边
    std::vector<typename GType::EdgeTupleType> real_tuples;
    for(int i=0;i<G_N;i++)
        for(int j=i+1;j<G_N;j++)
            real_tuples.push_back(std::make_tuple(i,j,i*10+j));
    EXPECT_EQ(_n_vertexes_m_edges_graph->edge_tuples(),real_tuples);
}

//!graph_test:Graph
/*!
*
* 测试`vertex_edge_tuples`方法成员。
*/
TEST_F(GraphTest,test_vertex_edge_tuples)
{
    for(int i=0;i<G_N;i++)
    {
        EXPECT_THROW(_empty_graph->vertex_edge_tuples(i),std::invalid_argument);//空图：没有顶点没有边
        EXPECT_EQ(_n_vertexes_graph->vertex_edge_tuples(i).size(),0);//无边有顶点的图：没有边
    }

    for(int i=0;i<G_N;i++)
    {
        std::vector<typename GType::EdgeTupleType> real_tuples;
        for(int j=i+1;j<G_N;j++)
            real_tuples.push_back(std::make_tuple(i,j,i*10+j));
        EXPECT_EQ(_n_vertexes_m_edges_graph->vertex_edge_tuples(i),real_tuples);
    }
}
//!graph_test:Graph
/*!
*
* 测试`inverse`方法成员。
*/
TEST_F(GraphTest,test_inverse)
{
    auto empty_inverse=_empty_graph->inverse();
    auto _n_vertexes_inverse=_n_vertexes_graph->inverse();
    auto _n_vertexes_m_edges_inverse=_n_vertexes_m_edges_graph->inverse();

    //无效边权重相同
    EXPECT_EQ(empty_inverse->matrix.invalid_weight,_empty_graph->matrix.invalid_weight);
    EXPECT_EQ(_n_vertexes_inverse->matrix.invalid_weight,_n_vertexes_graph->matrix.invalid_weight);
    EXPECT_EQ(_n_vertexes_m_edges_inverse->matrix.invalid_weight,_n_vertexes_m_edges_graph->matrix.invalid_weight);

    //顶点相同
    for(int i=0;i<G_N;i++)
    {
        if(empty_inverse->vertexes.at(i))
        {
                EXPECT_EQ(empty_inverse->vertexes.at(i)->id,_empty_graph->vertexes.at(i)->id);
                EXPECT_EQ(empty_inverse->vertexes.at(i)->key,_empty_graph->vertexes.at(i)->key);
        }else   EXPECT_FALSE(_empty_graph->vertexes.at(i));

        if(_n_vertexes_inverse->vertexes.at(i))
        {
                EXPECT_EQ(_n_vertexes_inverse->vertexes.at(i)->id,_n_vertexes_graph->vertexes.at(i)->id);
                EXPECT_EQ(_n_vertexes_inverse->vertexes.at(i)->key,_n_vertexes_graph->vertexes.at(i)->key);
        }else   EXPECT_FALSE(_n_vertexes_graph->vertexes.at(i));

        if(_n_vertexes_m_edges_inverse->vertexes.at(i))
        {
                EXPECT_EQ(_n_vertexes_m_edges_inverse->vertexes.at(i)->id,_n_vertexes_m_edges_graph->vertexes.at(i)->id);
                EXPECT_EQ(_n_vertexes_m_edges_inverse->vertexes.at(i)->key,_n_vertexes_m_edges_graph->vertexes.at(i)->key);
        }else   EXPECT_FALSE(_n_vertexes_m_edges_graph->vertexes.at(i));
    }
    //边反向
    EXPECT_EQ(empty_inverse->edge_tuples().size(),0);
    EXPECT_EQ(_n_vertexes_inverse->edge_tuples().size(),0);
    EXPECT_EQ(_n_vertexes_m_edges_inverse->edge_tuples().size(),_n_vertexes_m_edges_graph->edge_tuples().size());
    auto edges=_n_vertexes_m_edges_graph->edge_tuples();
    auto r_edges=_n_vertexes_m_edges_inverse->edge_tuples();
    for(int i=0;i<edges.size();i++)
    {
        auto edge=edges.at(i);
        auto r_edge=std::make_tuple(std::get<1>(edge),std::get<0>(edge),std::get<2>(edge));
        bool founded=false;
        for(int j=0;j<r_edges.size();j++)
        {
            if(r_edges.at(j)==r_edge)
            {
                founded=true;
                break;
            }
        }
        EXPECT_TRUE(founded);
    }
}
#endif // GRAPH_TEST

