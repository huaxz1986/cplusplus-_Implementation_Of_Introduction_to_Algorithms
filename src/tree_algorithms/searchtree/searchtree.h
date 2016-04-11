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
#ifndef SEARCHTREE
#define SEARCHTREE
#include"../binarytree/binarytree.h"
namespace IntroductionToAlgorithm
{
    namespace TreeAlgorithm
    {
        //!SearchTree：二叉搜索树，算法导论12章
        /*!
        *
        * 二叉搜索树是一种特殊的二叉树。在二叉树中的任何一个节点，该节点的左子节点值小于它；该节点的右子节点值大于它。
        *
        * > 这里节点值指的是节点存储的数据的值
        */
        template<typename NodeType> class SearchTree:public BinaryTree<NodeType>
        {
    public:
            typedef typename NodeType::KeyType T; /*!< 树的节点存储数据的类型*/

            //! search:在二叉搜索树中搜索指定内容的节点。
            /*!
             * \param value: 搜索指定的内容
             * \param node:从指定节点开始搜索（默认为树的根节点）
             * \return : 存储内容等于value的节点的强引用或者空
             *
             * 在二叉搜索树中搜索指定内容的节点。其中可以指定从哪个节点开始搜索。若不指定搜索节点，则默认为树的根节点.
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             */
            std::shared_ptr<NodeType> search(const T& value,std::shared_ptr<NodeType> node=std::shared_ptr<NodeType>())
            {
                if(!node) node=this->root;
                while(node&&node->key!=value)
                {
                    if(value<node->key)
                    {
                        node=node->lchild;
                    }else
                    {
                        node=node->rchild;
                    }
                }
                return node;
            }

            //! min:在二叉搜索树中最小值的节点。
            /*!
             * \param node:从指定节点开始搜索（默认为树的根节点）
             * \return : 二叉树种的最小节点的强引用
             *
             * 在二叉搜索树中搜索最小值的节点。其中可以指定从哪个节点开始搜索。若不指定搜索节点，则默认为树的根节点。
             *
             * 算法：由于二叉树的性质，搜索最小值很简单。从指定节点沿着左子节点一路向下遍历，最左下方的节点即为最小值节点
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             */
            std::shared_ptr<NodeType> min(std::shared_ptr<NodeType> node)
            {
                if(!node)
                {
                    throw std::invalid_argument("min() should not be aplied on nullptr");
                }
                while(node->lchild)
                {
                    node=node->lchild;
                }
                return node;
            }

            //! max:在二叉搜索树中最大值的节点。
            /*!
             * \param node:从指定节点开始搜索（默认为树的根节点）
             * \return : 二叉树种的最大节点的强引用
             *
             * 在二叉搜索树中搜索最小值的节点。其中可以指定从哪个节点开始搜索。若不指定搜索节点，则默认为树的根节点
             *
             * 算法：由于二叉树的性质，搜索最大值很简单。从指定节点沿着右子节点一路向下遍历，最右下方的节点即为最小值节点
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             */
            std::shared_ptr<NodeType> max(std::shared_ptr<NodeType> node)
            {
                if(!node)
                {
                    throw std::invalid_argument("max() should not be aplied on nullptr");
                }
                while(node->rchild)
                {
                    node=node->rchild;
                }
                return node;
            }
            //! successor:二叉搜索树指定节点的后继节点。
            /*!
             * \param node:要搜索后继的节点
             * \return : 该节点的后继节点的强引用或者空
             *
             * 给定二叉搜索树的某个节点，搜索其后继节点。所谓的某节点`node`的后继节点就是在二叉搜索树中，值大于等于`node`的所有节点中最小的那一个（排除它自身）。
             *
             * 一个节点`node`的后继有以下情况：
             *
             * - 如果`node`有右子节点，则以右子节点为根的子树中的最小值节点就是`node`的后继节点
             * - 如果`node`没有右子节点，则查看父节点
             *      - 若`node`是父节点的左子节点；则`node`的后继节点是`node`的父节点
             *      - 若`node`是父节点的右子节点；则`node`设置为`node->parent`，递归向直到`node`是它父亲的左子节点；此时`node`的后继节点是`node`的父节点
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             */
            std::shared_ptr<NodeType> successor(std::shared_ptr<NodeType> node)
            {
                if(!node)
                {
                    throw std::invalid_argument("successor() should not be aplied on nullptr");
                }
                if(node->rchild) //以右子节点为根的子树中的最小值节点就是`node`的后继节点
                {
                    return min(node->rchild);
                }
                auto shared_p=node->parent.lock();  //取出父节点
                while(shared_p && node->is_right_child())  //向上迭代，直到父节点为空或者node是父节点的左子节点，则迭代终止
                {
                    node=shared_p;
                    shared_p=shared_p->parent.lock();
                }
                return shared_p;
            }
            //! predecesor:二叉搜索树指定节点的前驱。
            /*!
             * \param node:要搜索前驱的节点
             * \return : 该节点的前驱节点的强引用或者空
             *
             * 给定二叉搜索树的某个节点，搜索其前驱节点。所谓的某节点`node`的前驱节点就是在二叉搜索树中，值小于`node`的所有节点中最大的那一个。
             *
             * 一个节点`node`的前驱有以下情况：
             *
             * - 如果`node`有左子节点，则以左子节点为根的子树中的最大值节点就是`node`的前驱节点
             * - 如果`node`没有左子节点，则查看父节点
             *      - 若`node`是父节点的右子节点；则`node`的前驱节点是`node`的父节点
             *      - 若`node`是父节点的左子节点；则`node`设置为`node->parent`，递归向直到`node`是它父亲的右子节点；此时`node`的前驱节点是`node`的父节点
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             */
            std::shared_ptr<NodeType>predecesor(std::shared_ptr<NodeType> node)
            {
                if(!node)
                {
                    throw std::invalid_argument("predecesor() should not be aplied on nullptr");
                }
                if(node->lchild) //以左子节点为根的子树中的最大值节点就是`node`的前驱节点
                {
                    return max(node->lchild);
                }
                auto shared_p=node->parent.lock();//取出父节点
                while(shared_p&&node->is_left_child())//向上迭代，直到父节点为空或者node是父节点的右子节点，则迭代终止
                {
                    node=shared_p;
                    shared_p=shared_p->parent.lock();
                }
                return shared_p;
            }
            //! insert:向二叉搜索树中插入节点。
            /*!
             * \param node:要插入的节点
             * \return : void
             *
             * 给定新节点`node`，将该节点插入到二叉搜索树中。
             *
             * 算法：遍历二叉搜索树，若当前节点的值大于`node`的值，则向左侧遍历；若当前节点值小于`node`的值，则向右侧遍历。直到碰到`nullptr`则挂载该节点
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             *
             */
            void insert(std::shared_ptr<NodeType> node)
            {
                node->lchild=std::shared_ptr<NodeType>();
                node->rchild=std::shared_ptr<NodeType>();

                if(!this->root)
                {
                    this->root=node;
                    return;
                }
                else
                {
                    auto temp=this->root;
                    auto temp_parent=std::shared_ptr<NodeType>();
                    bool left=true;
                    while(temp)  //遍历
                    {
                        temp_parent=temp;         //指向父节点
                        if(node->key<temp->key)   //向左侧遍历
                        {
                            temp=temp->lchild;
                            left=true;
                        }
                        else
                        {
                            temp=temp->rchild;    //向右侧遍历
                            left=false;
                        }
                    }
                    //现在temp为空，node挂载到temp_parent下
                    node->parent=temp_parent;
                    if(left) temp_parent->lchild=node;
                    else temp_parent->rchild=node;
                }

            }
            //! remove:从二叉搜索树中删除节点。
            /*!
             * \param node:要删除的节点
             * \return : void
             *
             * 给定节点`node`，从二叉搜索树中删除它。如果`node`不在二叉搜索树中则抛出异常。
             *
             * 算法：
             *
             * - 如果`node`是一个叶子节点：则直接删除它
             * - 如果`node`有左子节点，但是没有右子节点：将左子剪切到`node`所在位置
             * - 如果`node`有右子节点，但是没有左子节点：将右子剪切到`node`所在位置
             * - 如果`node`既有左子节点，又有右子节点：首先获取`node`的后继节点`next_node`
             *      - 如果`next_node`就是`node`的右子节点，则证明`next_node`没有左子（如果`next_node`有左子，则`node`的后继节点必然不是`next_node`）。
             *        此时将`next_node`剪切到`node`所在位置，并且将`node`的左子挂载到`next_node`的左子
             *      - 如果`next_node`不是`node`的右子节点，则`next_node`必然位于`node`右子为根的子树中。且`next_node`必然没有左子（否则`node`的后继节点必然不是`next_node`）
             *          - 把`next_node`的右子节点剪切到`next_node`的位置
             *          - 将`next_node`剪切到`node`的右子位置
             *          - 执行`next_node`就是`node`的右子节点的操作
             *
             * 算法时间复杂度O(h)，空间复杂度O(1)。其中h为树的高度
             *
             */
            void remove(std::shared_ptr<NodeType> node)
            {
                if(!node)
                {
                    throw std::invalid_argument("node removed is nullptr");
                }
                //*************  判定 node 必须位于树中 ***********
                auto temp_node=this->root;
                while(temp_node&& temp_node.get()!=node.get())
                {
                    if(node->key<temp_node->key)temp_node=temp_node->lchild;
                    else temp_node=temp_node->rchild;
                }
                if(temp_node.get()!=node.get())
                    throw std::invalid_argument("node removed must be in the tree");

                //************** 执行删除过程  *****************
                    if((!node->lchild)&&(!node->rchild)) //node是个叶子节点
                    {
                        auto shared_p=node->parent.lock();
                        if(shared_p) //父节点非空
                        {
                            if(node->is_left_child()) shared_p->lchild=std::shared_ptr<NodeType>();
                            if(node->is_right_child()) shared_p->rchild=std::shared_ptr<NodeType>();
                        }else
                        {
                            this->root=std::shared_ptr<NodeType>();
                        }
                    }else if(node->lchild&& !node->rchild) //node有左子，但是没有右子
                    {
                        transplant(node->lchild,node,this->root);  //左子剪切到node位置
                    }else if(node->rchild&& !node->lchild)//node有右子，但是没有左子
                    {
                        transplant(node->rchild,node,this->root);//右子剪切到node位置
                    }else                                    //node既有左子，又有右子
                    {
                        auto next_node=successor(node);      //node的后继节点
                        if(next_node!=node->rchild)   //node后继不是node的右子，则转换成node的后继是node的右子情形
                        {
                             transplant(next_node->rchild,next_node,this->root); //将后继的右子剪切到后继的位置
                             next_node->rchild=node->rchild;  //后继的右子设为node的右子
                             node->rchild->parent=next_node;   //后继的右子设为node的右子
                             node->rchild=next_node;           //后继的右子设为node的右子
                        }
                        //node后继是node的右子
                        transplant(node->rchild,node,this->root);
                        next_node->lchild=node->lchild;
                        node->lchild->parent=next_node;
                    }
            }
        };
    }
}


#endif // SEARCHTREE

