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
#ifndef DFSVERTEX_TEST
#define DFSVERTEX_TEST
#include"src/google_test/gtest.h"
#include"dfs_vertex.h"

using IntroductionToAlgorithm::GraphAlgorithm::DFS_Vertex;
//!DFSVertexTest:测试类，用于为测试提供基础数据
/*!
*
* `DFSVertexTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class DFSVertexTest:public ::testing::Test
{
public:
typedef DFS_Vertex<double> DFS_Vertex; /*!< 模板实例化的顶点类型为`DFS_Vertex<double>`*/

protected:
    void SetUp()
    {
        _default_vertex=std::make_shared<DFS_Vertex>();
        _normal_vertex=std::make_shared<DFS_Vertex>(1.0);
    }
    void TearDown(){}
    std::shared_ptr<DFS_Vertex> _default_vertex;    /*!< 指向一个默认构造的顶点*/
    std::shared_ptr<DFS_Vertex> _normal_vertex;    /*!< 指向一个显式构造的顶点*/
};
//!dfs_vertex_test:测试DFSVertex
/*!
*
* 测试`DFSVertex`的数据成员
*/
TEST_F(DFSVertexTest,test_data_member)
{

    EXPECT_NEAR(_default_vertex->key,0,0.001);
    EXPECT_EQ(_default_vertex->id,-1);
    EXPECT_EQ(_default_vertex->color,DFS_Vertex::COLOR::WHITE);
    EXPECT_EQ(_default_vertex->discover_time,-1);
    EXPECT_EQ(_default_vertex->finish_time,-1);
    EXPECT_FALSE(_default_vertex->parent);

    EXPECT_NEAR(_normal_vertex->key,1.0,0.001);
    EXPECT_EQ(_normal_vertex->id,-1);
    EXPECT_EQ(_normal_vertex->color,DFS_Vertex::COLOR::WHITE);
    EXPECT_EQ(_normal_vertex->discover_time,-1);
    EXPECT_EQ(_normal_vertex->finish_time,-1);
    EXPECT_FALSE(_normal_vertex->parent);
}
//!dfs_vertex_test:测试DFSVertex
/*!
*
* 测试`DFSVertex`的`set_disovered`方法
*/
TEST_F(DFSVertexTest,test_set_disovered)
{
    EXPECT_EQ(_default_vertex->color,DFS_Vertex::COLOR::WHITE);
    EXPECT_EQ(_default_vertex->discover_time,-1);
    _default_vertex->set_disovered(999);
    EXPECT_EQ(_default_vertex->color,DFS_Vertex::COLOR::GRAY);
    EXPECT_EQ(_default_vertex->discover_time,999);
}
//!dfs_vertex_test:测试DFSVertex
/*!
*
* 测试`DFSVertex`的`set_finished`方法
*/
TEST_F(DFSVertexTest,test_set_finished)
{
    EXPECT_EQ(_default_vertex->color,DFS_Vertex::COLOR::WHITE);
    EXPECT_EQ(_default_vertex->discover_time,-1);
    _default_vertex->set_finished(999);
    EXPECT_EQ(_default_vertex->color,DFS_Vertex::COLOR::BLACK);
    EXPECT_EQ(_default_vertex->finish_time,999);
}
//!dfs_vertex_test:测试测试DFSVertex
/*!
*
* 测试`测试DFSVertex`的`to_string`方法
*/
TEST_F(DFSVertexTest,test_to_string)
{
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:-1\t key:1\t color:WHITE\t parent-id:nullptr\t discover_time:-1\t finish_time:-1");
    _normal_vertex->parent=_default_vertex;
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:-1\t key:1\t color:WHITE\t parent-id:-1\t discover_time:-1\t finish_time:-1");
}
#endif // DFSVERTEX_TEST

