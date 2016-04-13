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
#ifndef SET_VERTEX_TEST
#define SET_VERTEX_TEST
#include"src/google_test/gtest.h"
#include"set_vertex.h"

using IntroductionToAlgorithm::GraphAlgorithm::SetVertex;

//!SetVertexTest:测试类，用于为测试提供基础数据
/*!
*
* `SetVertexTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class SetVertexTest:public ::testing::Test
{
public:

protected:
    void SetUp()
    {
        _default_vertex=std::make_shared<SetVertex<double>>();
        _normal_vertex=std::make_shared<SetVertex<double>>(1.5,1);
    }
    void TearDown(){}
    std::shared_ptr<SetVertex<double>> _default_vertex;     /*!< 指向顶点，默认构造*/
    std::shared_ptr<SetVertex<double>> _normal_vertex;     /*!< 指向顶点，显式构造*/
};
//!test_data_member：测试SetVertex
/*!
*
* `test_data_member`：测试SetVertex的成员变量
*/
TEST_F(SetVertexTest,test_data_member)
{
    EXPECT_EQ(_default_vertex->id,-1);
    EXPECT_NEAR(_default_vertex->key,0.0,0.001);
    EXPECT_FALSE(_default_vertex->node);

    EXPECT_EQ(_normal_vertex->id,1);
    EXPECT_NEAR(_normal_vertex->key,1.5,0.001);
    EXPECT_FALSE(_normal_vertex->node);
}
//!test_to_string：测试SetVertex
/*!
*
* `test_to_string`：测试SetVertex的`to_string()`方法
*/
TEST_F(SetVertexTest,test_to_string)
{
    typedef DisjointSetNode<SetVertex<double>> NodeType;
    EXPECT_EQ(_default_vertex->to_string(),"vertex id:-1\t key:0\t parent:nullptr");
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:1\t key:1.5\t parent:nullptr");

    std::shared_ptr<NodeType>node1=std::make_shared<NodeType>(_default_vertex);
    _default_vertex->node=node1;

    std::shared_ptr<NodeType>node2=std::make_shared<NodeType>(_normal_vertex);
    _normal_vertex->node=node2;

    node2->parent=node1;

    EXPECT_EQ(_default_vertex->to_string(),"vertex id:-1\t key:0\t parent:nullptr");
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:1\t key:1.5\t parent:-1");
}

#endif // SET_VERTEX_TEST

