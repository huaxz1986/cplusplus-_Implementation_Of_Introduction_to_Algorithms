#ifndef BINARYTREENODE_TEST
#define BINARYTREENODE_TEST
#include"src/google_test/gtest.h"
#include"binarytreenode.h"
using IntrodunctionToAlgorithm::TreeAlgorithm::BinaryTreeNode;

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

#endif // BINARYTREENODE_TEST

