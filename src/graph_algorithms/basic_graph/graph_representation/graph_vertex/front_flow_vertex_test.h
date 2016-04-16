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
#ifndef FRONTFLOWVERTEX_TEST
#define FRONTFLOWVERTEX_TEST
#include"src/google_test/gtest.h"
#include"front_flow_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::FrontFlowVertex;
using IntroductionToAlgorithm::GraphAlgorithm::List;
using IntroductionToAlgorithm::GraphAlgorithm::ListNode;

namespace{
    const int FFV_NUM=5;
}
class FrontFlowVertexTest:public ::testing::Test
{
public:
typedef FrontFlowVertex<int> VertexType; /*!< 模板实例化的顶点类型*/
typedef ListNode<VertexType> NodeType;  /*!< 模板实例化的Node类型*/
typedef List<NodeType> ListType;        /*!< 模板实例化的链表类型*/

protected:
    void SetUp()
    {
        _default_vertex=std::make_shared<VertexType>();
        _normal_vertex=std::make_shared<VertexType>(21,1);

        _list=std::make_shared<ListType>();

        for(int i=0;i<FFV_NUM;i++)
            _nodes[i]=std::make_shared<NodeType>();

    }
    void TearDown(){}

    std::shared_ptr<VertexType> _default_vertex;/*!< 默认构造的顶点*/
    std::shared_ptr<VertexType> _normal_vertex;/*!< 正常构造的顶点*/

    std::shared_ptr<ListType> _list;/*!< 列表顶点*/
    std::shared_ptr<NodeType> _nodes[FFV_NUM];/*!< 顶点*/
};

//!FrontFlowVertexTest：测试 FrontFlowVertex
/*!
*
* 测试FrontFlowVertex的构造、以及方法
*/
TEST_F(FrontFlowVertexTest,test_FrontFlowVertex_member)
{
    EXPECT_EQ(_default_vertex->id,-1);
    EXPECT_EQ(_default_vertex->key,0);
    EXPECT_EQ(_default_vertex->h,0);
    EXPECT_FALSE(_default_vertex->N_List.head);
    EXPECT_EQ(_default_vertex->to_string(),"vertex id:-1\t key:0\t h:0\t N_List:list:\n\ncurrent:\tnullptr");

    EXPECT_EQ(_normal_vertex->id,1);
    EXPECT_EQ(_normal_vertex->key,21);
    EXPECT_EQ(_normal_vertex->h,0);
    EXPECT_FALSE(_normal_vertex->N_List.head);
    EXPECT_EQ(_normal_vertex->to_string(),"vertex id:1\t key:21\t h:0\t N_List:list:\n\ncurrent:\tnullptr");
}
//!FrontFlowVertexTest：测试 FrontFlowVertex
/*!
*
* 测试ListNode的构造、以及方法
*/
TEST_F(FrontFlowVertexTest,test_node)
{
 EXPECT_FALSE(_nodes[0]->next);
 EXPECT_FALSE(_nodes[0]->value.lock());
 EXPECT_EQ(_nodes[0]->to_string(),"list_node:nullptr");

 _nodes[0]->value=_default_vertex;
 EXPECT_EQ(_nodes[0]->to_string(),"list_node:vertex id:-1\t key:0\t h:0\t N_List:list:\n\ncurrent:\tnullptr");
}
//!FrontFlowVertexTest：测试 FrontFlowVertex
/*!
*
* 测试List的构造、以及方法
*/
TEST_F(FrontFlowVertexTest,test_list)
{
    EXPECT_FALSE(_list->head);
    EXPECT_FALSE(_list->current);
    EXPECT_EQ(_list->to_string(),"list:\n\ncurrent:\tnullptr");
    for(int i=0;i<FFV_NUM-1;i++)
    {
        _list->add(_nodes[i]);
        EXPECT_EQ(_list->head,_nodes[i]);
    }
    EXPECT_EQ(_list->to_string(),"list:\nlist_node:nullptr;\tlist_node:nullptr;\tlist_node:nullptr;\tlist_node:nullptr;\t\ncurrent:\tnullptr");

    EXPECT_THROW(_list->front_of(_nodes[FFV_NUM-1]),std::invalid_argument);
    EXPECT_FALSE(_list->front_of(_list->head));
    for(int i=FFV_NUM-3;i>=0;i--)
        EXPECT_EQ(_list->front_of(_nodes[i]),_nodes[i+1]);
}


#endif // FRONTFLOWVERTEX_TEST

