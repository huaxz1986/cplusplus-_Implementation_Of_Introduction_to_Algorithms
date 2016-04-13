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
#ifndef SEARCHTREE_TEST
#define SEARCHTREE_TEST
#include"src/google_test/gtest.h"
#include"searchtree.h"
#include"../binarytreenode/binarytreenode.h"
#include"../binarytree/binarytree.h"
#include<sstream>

namespace   {
 const int NODE_NUM=9;
}

using IntroductionToAlgorithm::TreeAlgorithm::SearchTree;
using IntroductionToAlgorithm::TreeAlgorithm::BinaryTreeNode;
using IntroductionToAlgorithm::TreeAlgorithm::inorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::preorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::postorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::transplant;



//!SearchTreeTest:测试类，用于为测试提供基础数据
/*!
*
* `SearchTreeTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class SearchTreeTest:public ::testing::Test
{
public:
    typedef BinaryTreeNode<int> Node;
protected:
    SearchTreeTest(){}

    //!SetUp:在每一个测试开始之前执行
    /*!
    *
    * `SetUp`是 `::testing::Test` 的的虚函数。它主要用于为每一个测试提供测试环境
    */
    void SetUp()
    {
        std::shared_ptr<Node> nodes[NODE_NUM];
        for(int i=0;i<NODE_NUM;i++)
            nodes[i]=std::make_shared<Node>(i);
        nodes[3]->parent=std::weak_ptr<Node>(nodes[5]);
        nodes[7]->parent=std::weak_ptr<Node>(nodes[5]);
        nodes[5]->lchild=nodes[3];
        nodes[5]->rchild=nodes[7];

        nodes[1]->parent=std::weak_ptr<Node>(nodes[3]);
        nodes[4]->parent=std::weak_ptr<Node>(nodes[3]);
        nodes[3]->lchild=nodes[1];
        nodes[3]->rchild=nodes[4];

        nodes[6]->parent=std::weak_ptr<Node>(nodes[7]);
        nodes[8]->parent=std::weak_ptr<Node>(nodes[7]);
        nodes[7]->lchild=nodes[6];
        nodes[7]->rchild=nodes[8];

        nodes[0]->parent=std::weak_ptr<Node>(nodes[1]);
        nodes[2]->parent=std::weak_ptr<Node>(nodes[1]);
        nodes[1]->lchild=nodes[0];
        nodes[1]->rchild=nodes[2];

        _normal_tree.root=(nodes[5]);
        /*           5
        *          /   \
        *         3     7
        *        / \   /  \
        *       1   4 6    8
        *      / \
        *     0   2
        */
    }
    //!TearDown:在每一个测试结束之后执行
    /*!
    *
    * `TearDown`是 `::testing::Test` 的的虚函数。它主要用于为每个测试销毁测试环境
    */
    void TearDown(){}

    SearchTree<Node> _empty_tree;   /*!< 一个空的树*/
    SearchTree<Node> _normal_tree;   /*!< 一个非空的数*/
};

//!search_test:测试二叉搜索树的搜索
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的搜索
*/
TEST_F(SearchTreeTest,search_test)
{
    // ***  空树  *******
    auto result1=_empty_tree.search(0);
    EXPECT_FALSE(result1);
    //***   非空树 *******
    auto result2=_normal_tree.search(5);
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2.get(),_normal_tree.root.get());

    auto result3=_normal_tree.search(NODE_NUM);   //无效的值
    EXPECT_FALSE(result3);

    auto result4=_normal_tree.search(NODE_NUM-1);
    ASSERT_TRUE(result4);
    EXPECT_EQ(result4->key,NODE_NUM-1);
}
//!min_test:测试二叉搜索树的最小值
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的最小值
*/
TEST_F(SearchTreeTest,min_test)
{
    // ***  空树  *******
    EXPECT_THROW(_empty_tree.min(_empty_tree.root),std::invalid_argument);
    //***   非空树 *******
    auto result2=_normal_tree.min(_normal_tree.root);
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2->key,0);
}

//!max_test:测试二叉搜索树的最大值
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的最大值
*/
TEST_F(SearchTreeTest,max_test)
{
    // ***  空树  *******
    EXPECT_THROW(_empty_tree.max(_empty_tree.root),std::invalid_argument);
    //***   非空树 *******
    auto result2=_normal_tree.max(_normal_tree.root);
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2->key,NODE_NUM-1);
}

//!predecesor_test:测试二叉搜索树的前驱
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的前驱
*/
TEST_F(SearchTreeTest,predecesor_test)
{
    // ***  空树  *******
    EXPECT_THROW(_empty_tree.predecesor(_empty_tree.root),std::invalid_argument);
    //***   非空树 *******
    auto max=_normal_tree.max(_normal_tree.root);
    auto predecesor=_normal_tree.predecesor(max);
    EXPECT_EQ(predecesor->key,NODE_NUM-2);
    for(int i=1;i<NODE_NUM-1;i++)    //从最大值节点开始依次查找前驱
    {
        predecesor=_normal_tree.predecesor(predecesor);
        EXPECT_EQ(predecesor->key,NODE_NUM-2-i)<<"i:"<<i;
    }   
}
//!successor_test:测试二叉搜索树的后继
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的后继
*/
TEST_F(SearchTreeTest,successor_test)
{
    // ***  空树  *******
    EXPECT_THROW(_empty_tree.successor(_empty_tree.root),std::invalid_argument);
    //***   非空树 *******
    auto min=_normal_tree.min(_normal_tree.root);
    auto successor=_normal_tree.successor(min);
    EXPECT_EQ(successor->key,1);
    for(int i=1;i<NODE_NUM-1;i++)  //从最小值节点开始依次查找后继
    {
        successor=_normal_tree.successor(successor);
        EXPECT_EQ(successor->key,i+1)<<"i:"<<i;
    }
}

//!successor_test:测试二叉搜索树的插入
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的插入
*/
TEST_F(SearchTreeTest,insert_test)
{
    // ****  空树  ********
   {
        auto node=std::make_shared<BinaryTreeNode<int>>(1234);
        _empty_tree.insert(node);
        EXPECT_EQ(_empty_tree.root,node);
    }
    // *****  非空树 ************
    {


        auto node=std::make_shared<BinaryTreeNode<int>>(1234);
        _normal_tree.insert(node);
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            inorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"0;1;2;3;4;5;6;7;8;1234;");
        }
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            preorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"5;3;1;0;2;4;7;6;8;1234;");
        }

                /*           5
                *          /   \
                *         3     7
                *        / \   /  \
                *       1   4 6    8
                *      / \           \
                *     0   2          1234
                */

        auto node2=std::make_shared<BinaryTreeNode<int>>(10);
        _normal_tree.insert(node2);
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            inorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"0;1;2;3;4;5;6;7;8;10;1234;");
        }
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            preorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"5;3;1;0;2;4;7;6;8;1234;10;");
        }

                /*           5
                *          /   \
                *         3     7
                *        / \   /  \
                *       1   4 6    8
                *      / \           \
                *     0   2          1234
                *                   /
                *                  10
                */
    }
}
//!successor_test:测试二叉搜索树的删除
/*!
*
* 测试空二叉搜索树、非空二叉搜索树的删除
*/
TEST_F(SearchTreeTest,remove_test)
{
    // ****  空树  ********
   {
        auto node=std::make_shared<BinaryTreeNode<int>>(1234);
        EXPECT_THROW(_empty_tree.remove(node),std::invalid_argument);
    }
    // *****  非空树 ************
   {
        auto node=std::make_shared<BinaryTreeNode<int>>(1234);  //不是树的子节点
        EXPECT_THROW(_normal_tree.remove(node),std::invalid_argument);

        _normal_tree.remove(_normal_tree.root);  //删除一个拥有两个子节点的节点
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            inorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"0;1;2;3;4;6;7;8;");
        }
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            preorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"6;3;1;0;2;4;7;8;");
        }
        /*           6
        *          /   \
        *         3     7
        *        / \      \
        *       1   4      8
        *      / \
        *     0   2
        *
        *
        */

        _normal_tree.remove(_normal_tree.max(_normal_tree.root)->parent.lock());  //删除一个只有单子节点的节点
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            inorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"0;1;2;3;4;6;8;");
        }
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            preorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"6;3;1;0;2;4;8;");
        }
        /*           6
        *          /   \
        *         3     8
        *        / \
        *       1   4
        *      / \
        *     0   2
        *
        *
        */
        _normal_tree.remove(_normal_tree.min(_normal_tree.root)); //删除一个叶子节点
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            inorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"1;2;3;4;6;8;");
        }
        {
            std::ostringstream os;
            auto do_work=[&os](int val){ os<<val<<";";};
            preorder_walk(_normal_tree.root,do_work);
            EXPECT_EQ(os.str(),"6;3;1;2;4;8;");
        }
        /*           6
        *          /   \
        *         3     8
        *        / \
        *       1   4
        *        \
        *         2
        *
        *
        */
   }
}

#endif // SEARCHTREE_TEST

