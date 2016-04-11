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
#ifndef BINARYTREE_TEST
#define BINARYTREE_TEST
#include"src/google_test/gtest.h"
#include"binarytree.h"
#include"../binarytreenode/binarytreenode.h"
#include<sstream>

using IntroductionToAlgorithm::TreeAlgorithm::BinaryTree;
using IntroductionToAlgorithm::TreeAlgorithm::BinaryTreeNode;
using IntroductionToAlgorithm::TreeAlgorithm::inorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::preorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::postorder_walk;
using IntroductionToAlgorithm::TreeAlgorithm::transplant;
//!BinaryTreeTest:测试类，用于为测试提供基础数据
/*!
*
* `BinaryTreeTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class BinaryTreeTest:public ::testing::Test
{
public:
    typedef BinaryTreeNode<int> Node;
protected:
    BinaryTreeTest(){}

    //!SetUp:在每一个测试开始之前执行
    /*!
    *
    * `SetUp`是 `::testing::Test` 的的虚函数。它主要用于为每一个测试提供测试环境
    */
    void SetUp()
    {
        std::shared_ptr<Node> nodes[9];
        for(int i=0;i<9;i++)
            nodes[i]=std::make_shared<Node>(i);
        nodes[1]->parent=std::weak_ptr<Node>(nodes[0]);
        nodes[2]->parent=std::weak_ptr<Node>(nodes[0]);
        nodes[0]->lchild=nodes[1];
        nodes[0]->rchild=nodes[2];

        nodes[3]->parent=std::weak_ptr<Node>(nodes[1]);
        nodes[4]->parent=std::weak_ptr<Node>(nodes[1]);
        nodes[1]->lchild=nodes[3];
        nodes[1]->rchild=nodes[4];

        nodes[5]->parent=std::weak_ptr<Node>(nodes[2]);
        nodes[6]->parent=std::weak_ptr<Node>(nodes[2]);
        nodes[2]->lchild=nodes[5];
        nodes[2]->rchild=nodes[6];

        nodes[7]->parent=std::weak_ptr<Node>(nodes[3]);
        nodes[8]->parent=std::weak_ptr<Node>(nodes[3]);
        nodes[3]->lchild=nodes[7];
        nodes[3]->rchild=nodes[8];

        _normal_tree.root=(nodes[0]);
        /*           0
        *          /   \
        *         1     2
        *        / \   /  \
        *       3   4  5   6
        *      / \
        *     7   8
        */
    }
    //!TearDown:在每一个测试结束之后执行
    /*!
    *
    * `TearDown`是 `::testing::Test` 的的虚函数。它主要用于为每个测试销毁测试环境
    */
    void TearDown(){}

    BinaryTree<Node> _empty_tree;   /*!< 一个空的树*/
    BinaryTree<Node> _normal_tree;   /*!< 一个非空的数*/
};

//!test_tree:测试空树、非空树
TEST_F(BinaryTreeTest,test_tree)
{
    EXPECT_EQ(_empty_tree.to_xml(),"tree is empty!");
    EXPECT_NE(_normal_tree.to_xml(),"tree is empty!");
}
//!test_inorder_walk:测试树的中序遍历
/*!
*
* 测试空树、非空树的中序遍历
*/
TEST_F(BinaryTreeTest,test_inorder_walk)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};
    inorder_walk(_empty_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string());
    os.flush();
    inorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("7;3;8;1;4;0;5;2;6;"));
    /*           0               中序遍历: 7;3;8;1;4;0;5;2;6;
    *          /   \
    *         1     2
    *        / \   /  \
    *       3   4  5   6
    *      / \
    *     7   8
    */
}
//!test_preorder_walk:测试树的前序遍历
/*!
*
* 测试空树、非空树的前序遍历
*/
TEST_F(BinaryTreeTest,test_preorder_walk)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};
    preorder_walk(_empty_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string());
    os.flush();
    preorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("0;1;3;7;8;4;2;5;6;"));
    /*           0               前序遍历: 0;1;3;7;8;4;2;5;6;
    *          /   \
    *         1     2
    *        / \   /  \
    *       3   4  5   6
    *      / \
    *     7   8
    */
}
//!test_postorder_walk:测试树的后序遍历
/*!
*
* 测试空树、非空树的后序遍历
*/
TEST_F(BinaryTreeTest,test_postorder_walk)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};
    postorder_walk(_empty_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string());
    os.flush();
    postorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("7;8;3;4;1;5;6;2;0;"));
    /*           0               后序遍历: 7;8;3;4;1;5;6;2;0;
    *          /   \
    *         1     2
    *        / \   /  \
    *       3   4  5   6
    *      / \
    *     7   8
    */
}
//!test_left_rotate:测试树的左旋
/*!
*
* 测试空树、非空树的左旋
*/
TEST_F(BinaryTreeTest,test_left_rotate)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};

    left_rotate(_empty_tree.root,_empty_tree.root);

    auto old_root=_normal_tree.root; //原根节点
    auto old_root_right=old_root->rchild;//原根节点的右子
    left_rotate(_normal_tree.root,_normal_tree.root);
    EXPECT_NE(old_root.get(),_normal_tree.root.get());
    EXPECT_EQ(_normal_tree.root->lchild.get(),old_root.get());
    EXPECT_EQ(old_root_right.get(),_normal_tree.root.get());

    inorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("7;3;8;1;4;0;5;2;6;"));
    /*           0               左旋                      2
    *          /   \                                    /    \
    *         1     2                                  0      6
    *        / \   /  \                              /  \
    *       3   4  5   6                            1    5
    *      / \                                    /   \
    *     7   8                                  3     4
    *                                          /   \
    *                                         7     8
    */
}
//!test_right_rotate:测试树的右旋
/*!
*
* 测试空树、非空树的右旋
*/
TEST_F(BinaryTreeTest,test_right_rotate)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};
    right_rotate(_empty_tree.root,_empty_tree.root);

    auto old_root=_normal_tree.root;  //原根节点
    auto old_root_left=old_root->lchild;//原根节点的左子
    right_rotate(_normal_tree.root,_normal_tree.root);
    EXPECT_NE(old_root.get(),_normal_tree.root.get());
    EXPECT_EQ(_normal_tree.root->rchild.get(),old_root.get());
    EXPECT_EQ(old_root_left.get(),_normal_tree.root.get());

    inorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("7;3;8;1;4;0;5;2;6;"));
    /*           0               右旋                       1
    *          /   \                                    /      \
    *         1     2                                  3        0
    *        / \   /  \                              /   \     /  \
    *       3   4  5   6                            7     8   4    2
    *      / \                                                    /  \
    *     7   8                                                  5    6
    *
    *
    */
}
//!test_right_transplant:测试树的剪切
/*!
*
* 测试空树、非空树的剪切
*/
TEST_F(BinaryTreeTest,test_right_transplant)
{
    std::ostringstream os;
    auto do_work=[&os](int val){ os<<val<<";";};
    EXPECT_THROW(transplant(_empty_tree.root,_empty_tree.root,_empty_tree.root),std::invalid_argument);

    auto old_root=_normal_tree.root;  //原根节点
    auto old_src=old_root->lchild;//原根节点的左子
    auto old_dst=old_root->rchild; //原根节点的右子
    transplant(old_src,old_dst,_normal_tree.root); //左子剪切到右子
    EXPECT_EQ(old_root,_normal_tree.root);
    EXPECT_EQ(_normal_tree.root->rchild.get(),old_src.get());
    EXPECT_EQ(old_src->parent.lock().get(),_normal_tree.root.get());

    inorder_walk(_normal_tree.root,do_work);
    EXPECT_EQ(os.str(),std::string("7;3;8;1;4;0;7;3;8;1;4;"));
    /*           0               剪切 1-->2                  0                0
    *         //   \\                            (父-->子)/     \\           |(子-->父)
    *         1      2                                  1        1           2
    *       //  \\ //  \\                             // \\    //  \\      //   \\
    *       3    4 5    6                             3   4    3    4      5     6
    *     // \\                                     // \\    //  \\
    *     7   8                                    7    8    7    8
    *
    *
    */
}

#endif // BINARYTREE_TEST

