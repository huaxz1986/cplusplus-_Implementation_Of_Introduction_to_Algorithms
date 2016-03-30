//#ifndef SEARCHTREE
//#define SEARCHTREE
//#include"binarytree.h"

//template<typename NodeType>class SearchTree:public BinaryTree<NodeType>
//{
//public:
//    typedef typename NodeType<NodeType>::KeyType T;
//    std::shared_ptr<NodeType> search(std::shared_ptr<NodeType> node,const T& key)
//    {
//        while(node!=std::shared_ptr<NodeType>()&&node->key!=key)
//        {
//            if(key<node->key)
//            {
//                node=node->lchild;
//            }else
//            {
//                node=node->rchild;
//            }
//        }
//        return node;
//    }
//    std::shared_ptr<NodeType> min(std::shared_ptr<NodeType> node)
//    {
//        if(node==std::shared_ptr<NodeType>())
//        {
//            throw std::invalid_argument("min() should not be aplied on nullptr");
//        }
//        while(node->lchild!=std::shared_ptr<NodeType>())
//        {
//            node=node->lchild;
//        }
//        return node;
//    }
//    std::shared_ptr<NodeType> max(std::shared_ptr<NodeType> node)
//    {
//        if(node==std::shared_ptr<NodeType>())
//        {
//            throw std::invalid_argument("max() should not be aplied on nullptr");
//        }
//        while(node->rchild!=std::shared_ptr<NodeType>())
//        {
//            node=node->rchild;
//        }
//        return node;
//    }
//    std::shared_ptr<NodeType>successor(std::shared_ptr<NodeType> node)
//    {
//        if(node==std::shared_ptr<NodeType>())
//        {
//            throw std::invalid_argument("successor() should not be aplied on nullptr");
//        }
//        if(node->rchild!=std::shared_ptr<NodeType>())
//        {
//            return min(node->rchild);
//        }
//        auto parent=node->parent;
//        auto shared_p=parent.lock();
//        while(shared_p && node->is_right_child())
//        {
//            node=parent;
//            parent=parent->parent;
//            shared_p=parent.lock();
//        }
//        return parent;

//    }
//    std::shared_ptr<NodeType>predecesor(std::shared_ptr<NodeType> node)
//    {
//        if(!node)
//        {
//            throw std::invalid_argument("predecesor() should not be aplied on nullptr");
//        }
//        if(node->lchild)
//        {
//            return max(node->lchild);
//        }
//        auto parent=node->parent;
//        auto shared_p=parent.lock();
//        while(shared_p&&node->is_left_child())
//        {
//            node=parent;
//            parent=parent->parent;
//            shared_p=parent.lock();
//        }
//        return parent;
//    }
//    virtual void insert(std::shared_ptr<NodeType> node)
//    {
//        if(this->root==nullptr)
//        {
//            this->root=node;
//            return;
//        }else
//        {
//            Node* temp=this->_root;
//            Node* nodeParent=nullptr;
//            while(temp!=nullptr)
//            {
//                nodeParent=temp;
//                if(node->key>=temp->key)
//                {
//                    temp=temp->rchild;
//                }else
//                {
//                    temp=temp->lchild;
//                }
//            }
//            node->parent=nodeParent;
//            if(node->key>=nodeParent->key)
//                nodeParent->rchild=node;
//            else
//                nodeParent->lchild=node;
//        }

//    }
//    virtual void remove(Node* node)
//    {
//        if(node==nullptr)
//        {
//            return;
//        }else
//        {
//            if(node->lchild==nullptr&&node->rchild==nullptr)
//            {
//                this->transplant(nullptr,node);
//            }else if(node->lchild!=nullptr&&node->rchild==nullptr)
//            {
//                this->transplant(node->lchild,node);
//            }else if(node->lchild==nullptr&&node->rchild!=nullptr)
//            {
//                this->transplant(node->rchild,node);
//            }else
//            {
//                Node* nextNode=successor(node);
//                if(nextNode!=node->rchild)
//                {
//                    this->transplant(nextNode->rchild,nextNode);
//                    nextNode->rchild=node->rchild;
//                    node->rchild->parent=nextNode;
//                    node->rchild=nextNode;
//                }
//                this->transplant(node->rchild,node);
//                nextNode->lchild=node->lchild;
//                node->lchild->parent=nextNode;
//            }

//        }
//    }
//    bool isSatisfied(Node* node)
//    {
//        if(node==nullptr) return true;
//        if(node->lchild!=nullptr)
//        {
//            if(!this->isSatisfied(node->lchild)) return false;
//            if(maxChild(node->lchild)->key>node->key) return false;
//        }
//        if(node->rchild!=nullptr)
//        {
//            if(!this->isSatisfied(node->rchild)) return false;
//            if(minChild(node->rchild)->key < node->key) return false;
//        }
//        return true;
//    }
//    Node * maxChild(Node *node)
//    {
//        if(node==nullptr || node->rchild==nullptr)
//            return node;
//        Node *child=nullptr;
//        while((child=node->rchild)!=nullptr )
//        {
//            node=node->rchild;
//        }
//        return node;
//    }
//    Node *minChild(Node* node)
//    {
//        if(node==nullptr || node->lchild==nullptr)
//            return node;
//        Node *child=nullptr;
//        while((child=node->lchild)!=nullptr )
//        {
//            node=node->lchild;
//        }
//        return node;
//    }
//};

//#endif // SEARCHTREE

