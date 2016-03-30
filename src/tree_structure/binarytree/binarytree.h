#ifndef BINARYTREE
#define BINARYTREE
#include<iostream>
#include<exception>
#include<stdexcept>
#include<stack>
#include"binarytreenode.h"

template<typename NodeType> struct BinaryTree
{
    typedef typename NodeType<NodeType>::KeyType T;
    BinaryTree():root(std::weak_ptr<NodeType>)
    {
    }
    std::string  to_string()
    {
        root->to_string();
    }
    std::string  to_xml()
    {
        root->to_xml;
    }

    std::weak_ptr<NodeType> root;
};

template<typename NodeType>void  inorder_walk( std::shared_ptr<NodeType> root,std::ostream& os)
{
    if (root != std::shared_ptr<NodeType>())
    {
        if(root->lchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->lchild,os);
        os<<root->root->key<<",";
        if(root->rchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->rchild,os);
    }


}
template<typename NodeType>void   preorder_walk( std::shared_ptr<NodeType> root,std::ostream& os)
{
    if (root != std::shared_ptr<NodeType>())
    {
        os<<root->key<<",";
        if(root->lchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->lchild,os);
        if(root->rchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->rchild,os);
    }
}
template<typename NodeType>void  postorder_walk( std::shared_ptr<NodeType> root,std::ostream& os)
{
    if (root != std::shared_ptr<NodeType>())
    {
        if(root->lchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->lchild,os);
        if(root->rchild!=std::shared_ptr<NodeType>())
            inorder_walk(root->rchild,os);
        os<<root->key<<",";
    }
}

template<typename NodeType> void left_rotate(std::shared_ptr<NodeType> root)
{

    if (root != std::shared_ptr<NodeType>())
    {
        auto right=root->rchild;
        if(right ==std::shared_ptr<NodeType>())
            return;
        right->parent=root->parent;//node's parent <-----> r
        if(!root->parent.lock())
        {
            this->_root=r;
        }else
        {
           if(root->is_left_child())
               root->parent->lchild=right;
           else
               root->parent->rchild=right;
        }
        //r's left <-----> node
        root->rchild=right->lchild;
        if(right->lchild!=std::shared_ptr<NodeType>())
            right->lchild->parent=root;
        // node <-----> r
        root->parent=right;
        right->lchild=root;
    }
}

 template<typename NodeType> void  right_rotate(std::shared_ptr<NodeType> root)
 {
        if (root != std::shared_ptr<NodeType>())
        {
            auto left=root->lchild;
            if(left ==std::shared_ptr<NodeType>())
                return;
            //node's parent <-----> L
            left->parent=root->parent;
            if(!root->parent.lock())
            {
               this-> _root=left;
            }else
            {
                if(root->is_right_child())
                    root->parent->lchild=left;
                else
                    root->parent->rchild=left;
            }
            //L's right <-----> node
            root->lchild=left->rchild;
            if(root->rchild!=std::shared_ptr<NodeType>())
                left->rchild->parent=node;
            //node <-----------> L
            root->parent=left;
            left->rchild=root;
        }
}
#endif // BINARYTREE

