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
#ifndef GRAPHEDGE_TEST
#define GRAPHEDGE_TEST
#include"src/google_test/gtest.h"
#include"edge.h"
#include"../graph_vertex/vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::Vertex;
using IntroductionToAlgorithm::GraphAlgorithm::Edge;

//!EdgeTest:测试类，用于为测试`Edge`提供基础数据
/*!
*
* `EdgeTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class EdgeTest:public ::testing::Test
{
public:
    typedef Vertex<double> Node;
protected:
    void SetUp(){
        _edge=std::make_shared<Edge<Node>>(std::make_shared<Node>(16.0,0),std::make_shared<Node>(17.0,1),2);
    }
    void TearDown(){}

    std::shared_ptr<Edge<Node>> _edge;  /*!< 指向一条边*/
};
//!test_edge：测试边
/*!
*
* 依次测试测试边的各数据成员。
*/
TEST_F(EdgeTest,test_data_member)
{
    EXPECT_TRUE(_edge->vertex1->id==0 &&_edge->vertex2->id==1 &&_edge->weight==2 );
}

//!test_edge：测试边
/*!
* 测试边的` to_string`成员方法。
*/
TEST_F(EdgeTest,test_to_string)
{
    EXPECT_EQ(_edge->to_string(),"edge weight:2\t vertex[id1:0,id2:1]");
}
//!test_edge：测试边
/*!
* 测试边的` edge_tuple`成员方法。
*/
TEST_F(EdgeTest,test_edge_tuple)
{
    EXPECT_EQ(_edge->edge_tuple(),std::make_tuple(0,1,2));
}


#endif // GRAPHEDGE_TEST

