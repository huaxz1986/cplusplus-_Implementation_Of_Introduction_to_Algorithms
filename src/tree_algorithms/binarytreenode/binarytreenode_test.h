#ifndef BINARYTREENODE_TEST
#define BINARYTREENODE_TEST
#include"src/google_test/gtest.h"
#include"binarytreenode.h"
using IntrodunctionToAlgorithm::TreeAlgorithm::BinaryTreeNode;
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 当创建默认节点时，节点应该满足的特征
*/
TEST(test_binary_tree_node, test_default_node)
{
    BinaryTreeNode<int> node;
    EXPECT_EQ(node.key,0);
    EXPECT_FALSE(node.lchild); //shared_ptr<T> 直接代表真假
    EXPECT_EQ(node.rchild.get(),nullptr); //也可以抽取其指针
    EXPECT_FALSE(node.parent.lock());  //weak_ptr<T> 必须通过lock()获取一个shared_ptr<T>
    EXPECT_FALSE(node.is_left_child());
    EXPECT_FALSE(node.is_right_child());
    std::cout<<node.to_string()<<std::endl;
    std::cout<<node.to_xml()<<std::endl;
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 当创建多个节点时，`to_string()` 方法 和 `to_xml()`方法执行正确
*/
TEST(test_binary_tree_node, test_many_nodes)
{
    typedef BinaryTreeNode<int> Node;
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
    for(int i=0;i<9;i++)
        std::cout<<nodes[i]->to_string()<<std::endl;
    std::cout<<nodes[0]->to_xml()<<std::endl;
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试 `is_left_child()`方法执行正确
*/
TEST(test_binary_tree_node, test_is_left_child)
{
    typedef BinaryTreeNode<int> Node;
    std::shared_ptr<Node> nodes[3];
    for(int i=0;i<3;i++)
        nodes[i]=std::make_shared<Node>(i);
    nodes[1]->parent=std::weak_ptr<Node>(nodes[0]);
    nodes[2]->parent=std::weak_ptr<Node>(nodes[0]);
    nodes[0]->lchild=nodes[1];
    nodes[0]->rchild=nodes[2];
    EXPECT_FALSE(nodes[0]->is_left_child());
    EXPECT_TRUE(nodes[1]->is_left_child());
    EXPECT_FALSE(nodes[2]->is_left_child());
}
//!binary_tree_node_test：测试二叉树节点
/*!
*
* 测试 `is_right_child()`方法执行正确
*/
TEST(test_binary_tree_node, test_is_right_child)
{
    typedef BinaryTreeNode<int> Node;
    std::shared_ptr<Node> nodes[3];
    for(int i=0;i<3;i++)
        nodes[i]=std::make_shared<Node>(i);
    nodes[1]->parent=std::weak_ptr<Node>(nodes[0]);
    nodes[2]->parent=std::weak_ptr<Node>(nodes[0]);
    nodes[0]->lchild=nodes[1];
    nodes[0]->rchild=nodes[2];
    EXPECT_FALSE(nodes[0]->is_right_child());
    EXPECT_FALSE(nodes[1]->is_right_child());
    EXPECT_TRUE(nodes[2]->is_right_child());
}
#endif // BINARYTREENODE_TEST

