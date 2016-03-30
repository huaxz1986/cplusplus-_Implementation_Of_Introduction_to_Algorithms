#ifndef BINARYTREENODE
#define BINARYTREENODE
#include<memory>
#include<string>
#include<sstream>
namespace IntrodunctionToAlgorithm {
namespace TreeAlgorithm {
template<typename T> struct BinaryTreeNode
{
public:
    BinaryTreeNode()
        :parent(std::weak_ptr<BinaryTreeNode>()),lchild(std::shared_ptr<BinaryTreeNode>()),rchild(std::shared_ptr<BinaryTreeNode>()),key(T())
    {}
    explicit BinaryTreeNode(const T& keyvalue)
        :parent(std::weak_ptr<BinaryTreeNode>()),lchild(std::shared_ptr<BinaryTreeNode>()),rchild(std::shared_ptr<BinaryTreeNode>()),key(keyvalue)
    {}
    typedef T KeyType;
    virtual std::string to_string(){
        std::ostringstream os;
        os<<"node:"<<key;
        if(auto shared_p=parent.lock()) os<<"\n\t parent:"<<shared_p->key;
        else os<<"\n\t parent:"<<"null_ptr";

        os<<"\n\t left_child:";
        if(lchild)  os<<lchild->key;
        else   os<<"nullptr";

        os<<"\n\t right_child:";
        if(rchild) os<<rchild->key;
        else os<<"nullptr";
        return os.str();
    }
    virtual std::string to_xml(){
        std::ostringstream os;
        os<<"\n<node>"<<key<<"\n";
        if(auto shared_p=parent.lock())
        {
            os<<"\t <parent>"<<shared_p->key<<"</parent>";
        }else
        {
            os<<"\t <parent>"<<"null_ptr"<<"</parent>";
        }
        os<<"\n\t <left_child>"<<(lchild? lchild->to_xml(): "nullptr")<<"</left_child>"\
          <<"\n\t<right_child>"<<(rchild? rchild->to_xml():"nullptr")<<"</right_child>"\
          <<"\n</node>";
        return os.str();
    }
    bool is_left_child()
    {
       if (auto shared_p = parent.lock())
       {
            if (this==shared_p->lchild.get())
                return true;
       }
       return false;
    }
    bool is_right_child()
    {
       if (auto shared_p = parent.lock())
       {
            if (this==shared_p->rchild.get())
                return true;
       }
       return false;
    }
    std::weak_ptr<BinaryTreeNode> parent;
    std::shared_ptr<BinaryTreeNode> lchild;
    std::shared_ptr<BinaryTreeNode> rchild;
    T key;
};
}
}

#endif // BINARYTREENODE

