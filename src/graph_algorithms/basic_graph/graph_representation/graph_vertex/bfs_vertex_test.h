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
#ifndef BFSVERTEX_TEST
#define BFSVERTEX_TEST

#include"src/google_test/gtest.h"
#include"bfs_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::BFS_Vertex;

//!BFSVertexTest:测试类，用于为测试提供基础数据
/*!
*
* `BFSVertexTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class BFSVertexTest:public ::testing::Test
{
public:
typedef BFS_Vertex<double> BFS_Vertex; /*!< 模板实例化的顶点类型为`BFS_Vertex<double>`*/

protected:
    void SetUp(){
        _default_vertex=std::make_shared<BFS_Vertex>();
        _normal_vertex=std::make_shared<BFS_Vertex>(1.0);
    }
    void TearDown(){}
    std::shared_ptr<BFS_Vertex> _default_vertex;    /*!< 指向一个默认构造的顶点*/
    std::shared_ptr<BFS_Vertex> _normal_vertex;    /*!< 指向一个显式构造的顶点*/
};
//!bfs_vertex_test:测试BFSVertex
/*!
*
* 测试`BFSVertex`的数据成员
*/
TEST_F(BFSVertexTest,test_data_member)
{

    EXPECT_NEAR(_default_vertex->key,0,0.001);
    EXPECT_EQ(_default_vertex->id,-1);
    EXPECT_EQ(_default_vertex->color,BFS_Vertex::COLOR::WHITE);
    EXPECT_FALSE(_default_vertex->parent);

    EXPECT_NEAR(_normal_vertex->key,1.0,0.001);
    EXPECT_EQ(_normal_vertex->id,-1);
    EXPECT_EQ(_normal_vertex->color,BFS_Vertex::COLOR::WHITE);
    EXPECT_FALSE(_normal_vertex->parent);
}
//!bfs_vertex_test:测试BFSVertex
/*!
*
* 测试`BFSVertex`的`set_source`方法
*/
TEST_F(BFSVertexTest,test_set_source)
{
    EXPECT_EQ(_default_vertex->color,BFS_Vertex::COLOR::WHITE);
    _default_vertex->set_source();
    EXPECT_EQ(_default_vertex->color,BFS_Vertex::COLOR::GRAY);

    EXPECT_EQ(_normal_vertex->color,BFS_Vertex::COLOR::WHITE);
    _normal_vertex->set_source();
    EXPECT_EQ(_normal_vertex->color,BFS_Vertex::COLOR::GRAY);
}
//!bfs_vertex_test:测试BFSVertex
/*!
*
* 测试`BFSVertex`的`set_found`方法
*/
TEST_F(BFSVertexTest,test_set_found)
{
    EXPECT_THROW(_normal_vertex->set_found(std::shared_ptr<BFS_Vertex>()),std::invalid_argument);
    EXPECT_FALSE(_normal_vertex->parent);
    EXPECT_EQ(_normal_vertex->color,BFS_Vertex::COLOR::WHITE);
    _normal_vertex->set_found(_default_vertex);
    EXPECT_EQ(_normal_vertex->parent,_default_vertex);
    EXPECT_EQ(_normal_vertex->color,BFS_Vertex::COLOR::GRAY);

}
//!bfs_vertex_test:测试BFSVertex
/*!
*
* 测试`BFSVertex`的`to_string`方法
*/
TEST_F(BFSVertexTest,test_to_string)
{
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:-1\t key:1\t color:WHITE\t parent-id:nullptr");
    _normal_vertex->set_found(_default_vertex);
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:-1\t key:1\t color:GRAY\t parent-id:-1");
}
#endif // BFSVERTEX_TEST

