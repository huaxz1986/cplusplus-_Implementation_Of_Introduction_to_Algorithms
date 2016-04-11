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
#ifndef BINARYTREENODE_TEST
#define BINARYTREENODE_TEST
#include"src/google_test/gtest.h"
#include"binarytreenode.h"
using IntroductionToAlgorithm::TreeAlgorithm::BinaryTreeNode;
//!BinaryTreeNodeTest:测试类，用于为测试提供基础数据
/*!
*
* `BinaryTreeNodeTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class BinaryTreeNodeTest:public ::testing::Test
{
public:
    typedef BinaryTreeNode<int> Node;
protected:
    void SetUp()
    {
        default_node=std::shared_ptr<Node>(new Node());
        root_node=std::make_shared<Node>(0);
        root_node->lchild=std::make_shared<Node>(1);
        root_node->rchild=std::make_shared<Node>(2);
        root_node->lchild->parent=root_node;
        root_node->rchild->parent=root_node;
    }
    void TearDown()
    {}

    std::shared_ptr<Node> default_node; /*!< 指向一个默认构造的结点*/
    std::shared_ptr<Node> root_node;    /*!< 指向一个非默认构造的结点*/
};

//!binary_tree_node_test：测试二叉树节点
/*!
*
* 当创建默认节点时，节点应该满足的特征
*/
TEST_F(BinaryTreeNodeTest, test_default_node)
{
    EXPECT_EQ(default_node->key,0);
    EXPECT_FALSE(default_node->lchild); //shared_ptr<T> 直接代表真假
    EXPECT_EQ(default_node->rchild.get(),nullptr); //也可以抽取其指针
    EXPECT_FALSE(default_node->parent.lock());  //weak_ptr<T> 必须通过lock()获取一个shared_ptr<T>
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试`to_string()`方法正确执行
*/
TEST_F(BinaryTreeNodeTest, test_to_string)
{
    EXPECT_EQ(default_node->to_string(),"node:0\n\t parent:null_ptr\n\t left_child:nullptr\n\t right_child:nullptr");
    EXPECT_EQ(root_node->to_string(),"node:0\n\t parent:null_ptr\n\t left_child:1\n\t right_child:2");
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试`to_xml()`方法正确执行
*/
TEST_F(BinaryTreeNodeTest, test_to_xml)
{
    EXPECT_NE(default_node->to_xml(),"");
    EXPECT_NE(root_node->to_xml(),"");
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试 `is_left_child()`方法执行正确
*/
TEST_F(BinaryTreeNodeTest, test_is_left_child)
{
    EXPECT_FALSE(default_node->is_left_child());
    EXPECT_TRUE(root_node->lchild->is_left_child());
    EXPECT_FALSE(root_node->rchild->is_left_child());
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试 `is_right_child()`方法执行正确
*/
TEST_F(BinaryTreeNodeTest, test_is_right_child)
{
    EXPECT_FALSE(default_node->is_right_child());
    EXPECT_FALSE(root_node->lchild->is_right_child());
    EXPECT_TRUE(root_node->rchild->is_right_child());
}
#endif // BINARYTREENODE_TEST

