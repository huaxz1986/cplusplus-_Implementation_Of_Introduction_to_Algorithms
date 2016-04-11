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
#ifndef DISJOINTSET_TEST
#define DISJOINTSET_TEST
#include"src/google_test/gtest.h"
#include"disjointset.h"
using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;
namespace {
    const int S_NUM=20;
}

//!DisjointSetNodeTest:测试类，用于为测试提供基础数据
/*!
*
* `DisjointSetNodeTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class DisjointSetNodeTest:public ::testing::Test
{
public:
typedef DisjointSetNode<int> NodeType;
protected:
    void SetUp()
    {
        for(int i=0;i<S_NUM;i++) //创建结点
            nodes[i]=std::make_shared<NodeType>(std::make_shared<int>(i));
    }
    void TearDown(){}
    std::shared_ptr<NodeType> nodes[S_NUM];    /*!< 指向结点指针的数组*/

};

//!DisjointSetNodeTest:测试DisjointSetNodeTest
/*!
*
* `test_make_set`:测试 make_set方法
*/
TEST_F(DisjointSetNodeTest,test_make_set)
{
    EXPECT_THROW(NodeType::make_set(std::shared_ptr<NodeType>()),std::invalid_argument);
    for(int i=0;i<S_NUM;i++)
    {
        NodeType::make_set(nodes[i]);
        EXPECT_EQ(nodes[i]->rank,0);
        EXPECT_EQ(nodes[i]->parent,nodes[i]);
    }
}
//!DisjointSetNodeTest:测试DisjointSetNodeTest
/*!
*
* `test_find_set`:测试 find_set 方法
*/
TEST_F(DisjointSetNodeTest,test_find_set)
{
    EXPECT_THROW(NodeType::find_set(std::shared_ptr<NodeType>()),std::invalid_argument);
    for(int i=0;i<S_NUM;i++)
    {
        NodeType::make_set(nodes[i]);
        EXPECT_EQ(NodeType::find_set(nodes[i]),nodes[i]);
    }
}
//!DisjointSetNodeTest:测试DisjointSetNodeTest
/*!
*
* `test_link`:测试 link 方法
*/
TEST_F(DisjointSetNodeTest,test_link)
{
    for(int i=0;i<S_NUM;i++)
    {
        NodeType::make_set(nodes[i]);
    }

    NodeType::link_set(nodes[0],nodes[1]);
    EXPECT_EQ(nodes[0]->parent,nodes[1]);
    EXPECT_EQ(nodes[0]->rank,0);
    EXPECT_EQ(nodes[1]->parent,nodes[1]);
    EXPECT_EQ(nodes[1]->rank,1);

    EXPECT_THROW(NodeType::link_set(nodes[2],nodes[0]),std::invalid_argument);
    NodeType::link_set(nodes[2],nodes[1]);
    EXPECT_EQ(nodes[2]->parent,nodes[1]);
    EXPECT_EQ(nodes[2]->rank,0);
    EXPECT_EQ(nodes[1]->parent,nodes[1]);
    EXPECT_EQ(nodes[1]->rank,1);

    EXPECT_EQ(NodeType::find_set(nodes[0]),nodes[1]);
    EXPECT_EQ(nodes[0]->parent,nodes[1]);
    EXPECT_EQ(NodeType::find_set(nodes[2]),nodes[1]);
    EXPECT_EQ(nodes[2]->parent,nodes[1]);
}
//!DisjointSetNodeTest:测试DisjointSetNodeTest
/*!
*
* `test_union`:测试 union 方法
*/
TEST_F(DisjointSetNodeTest,test_union)
{
    for(int i=0;i<S_NUM;i++)
    {
        NodeType::make_set(nodes[i]);
    }
    for(int i=1;i<S_NUM/3;i++)
    {
        NodeType::union_set(nodes[i],nodes[0]);
        EXPECT_EQ(nodes[0]->rank,1);
        EXPECT_EQ(nodes[i]->rank,0);
        EXPECT_EQ(nodes[i]->parent,nodes[0]);
    }
    for(int i=S_NUM/3+1;i<S_NUM*2/3;i++)
    {
        NodeType::union_set(nodes[i],nodes[S_NUM/3]);
        EXPECT_EQ(nodes[0]->rank,1);
        EXPECT_EQ(nodes[i]->rank,0);
        EXPECT_EQ(nodes[i]->parent,nodes[S_NUM/3]);
    }
    for(int i=S_NUM*2/3+1;i<S_NUM;i++)
    {
        NodeType::union_set(nodes[i],nodes[S_NUM*2/3]);
        EXPECT_EQ(nodes[0]->rank,1);
        EXPECT_EQ(nodes[i]->rank,0);
        EXPECT_EQ(nodes[i]->parent,nodes[S_NUM*2/3]);
    }

    NodeType::union_set(nodes[S_NUM/3],nodes[0]);
    EXPECT_EQ(nodes[S_NUM/3]->rank,1);
    EXPECT_EQ(nodes[S_NUM/3]->parent,nodes[0]);
    EXPECT_EQ(nodes[0]->rank,2);
    for(int i=S_NUM/3+1;i<S_NUM*2/3;i++)
    {
        EXPECT_EQ(nodes[i]->rank,0);
        EXPECT_EQ(NodeType::find_set(nodes[i]),nodes[0]);//路径压缩
        EXPECT_EQ(nodes[i]->parent,nodes[0]);
    }
}

#endif // DISJOINTSET_TEST

