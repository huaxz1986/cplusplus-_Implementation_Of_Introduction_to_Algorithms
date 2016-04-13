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
#ifndef BINARYTREE
#define BINARYTREE
#include<memory>
#include<functional>
namespace IntroductionToAlgorithm
{
namespace TreeAlgorithm
{
//!BinaryTree：二叉树，算法导论10章10.4节
    /*!
    *
    * 二叉树通过一个root（若引用）指向一个节点对象。当root为空时，树为空
    */
    template<typename NodeT> struct BinaryTree
    {
        typedef NodeT NodeType; /*!< 树的节点类型*/
        typedef typename NodeT::KeyType KeyType; /*!< 树的节点存储数据的类型*/
        //! 默认函数
        /*!
        *
        * 新建的二叉树默认为空
        */
        BinaryTree():root(std::shared_ptr<NodeType>())
        {
        }
        //! to_xml:返回本树的`xml`描述。
        /*!
         *
         * \return : 树的`xml`描述的字符串
         *
         * 该函数获取本树的`xml`描述
         */
        std::string  to_xml()
        {
            if(root)
                return root->to_xml();
            else
                return "tree is empty!";
        }

        std::shared_ptr<NodeType> root; /*!< 树的根节点，时一个指向节点对象的强引用*/
    };

    //!inorder_walk：二叉树的中序遍历
    /*!
    * \param root: 二叉树的根节点，强引用
    * \param func: 对二叉树节点的操作
    * \return void
    *
    * 本函数执行对二叉树的中序遍历，遍历时执行指定操作
    * 算法：
    * - 对左子节点前序遍历
    * - 对本节点执行操作
    * - 对右子节点前序遍历
    *
    * 时间复杂度O(n)，空间复杂度O(1)
    */
    template<typename NodeType,typename ActionType=std::function<void (typename NodeType::T)> >
        void  inorder_walk( std::shared_ptr<NodeType> root,ActionType action=[](typename NodeType::T){})
    {
        if (root)
        {
            if(root->lchild) inorder_walk(root->lchild,action);
            action(root->key);
            if(root->rchild) inorder_walk(root->rchild,action);
        }
    }
    //!preorder_walk：二叉树的前序遍历
    /*!
    * \param root: 二叉树的根节点，强引用
    * \param func: 对二叉树节点的操作
    * \return void
    *
    * 本函数执行对二叉树的前序遍历，遍历时执行指定操作
    * 算法：
    * - 对本节点执行操作
    * - 对左子节点前序遍历
    * - 对右子节点前序遍历
    *
    * 时间复杂度O(n)，空间复杂度O(1)
    */
    template<typename NodeType,typename ActionType=std::function<void (typename NodeType::T)> >
        void   preorder_walk( std::shared_ptr<NodeType> root,ActionType action=[](typename NodeType::T){})
    {
        if (root)
        {
            action(root->key);
            if(root->lchild) preorder_walk(root->lchild,action);
            if(root->rchild) preorder_walk(root->rchild,action);
        }
    }

    //!postorder_walk：二叉树的后序遍历
    /*!
    * \param root: 二叉树的根节点，强引用
    * \param func: 对二叉树节点的操作
    * \return void
    *
    * 本函数执行对二叉树的后序遍历，遍历时执行指定操作。
    * 算法：
    *
    * - 对左子节点后续遍历
    * - 对右子节点后续遍历
    * - 对本节点执行操作
    *
    * 时间复杂度O(n)，空间复杂度O(1)
    */
    template<typename NodeType,typename ActionType=std::function<void (typename NodeType::T)> >
        void  postorder_walk( std::shared_ptr<NodeType> root,ActionType action=[](typename NodeType::T){})
    {
        if (root)
        {
            if(root->lchild) postorder_walk(root->lchild,action);
            if(root->rchild) postorder_walk(root->rchild,action);
            action(root->key);
        }
    }

    //!left_rotate：二叉树的左旋转操作
    /*!
    * \param node: 待旋转的节点，强引用
    * \param root： 二叉树的根节点的强引用（当node指向树根时，旋转会导致丢失树根信息，此时由root返回新的树根）
    * \return void
    *
    * 本函数执行二叉树进行左旋转。设node为被旋转的点，l_node为它的左子节点，r_node为它的右子节点。
    * 则旋转的效果是：r_node取代了node的位置；而node现在挂靠在r_node的左子；r_node原来的左子现在成为node的右子
    *
    * <code><pre>
    *         |                                                |
    *        node                                            r_node
    *       /    \                                           /    \
    *   l_node  r_node        -- 左旋  -->                  node  r_r_node
    *          /    \                                     /    \
    *     l_r_node r_r_node                           l_node  l_r_node
    * </pre></code>
    *
    * 时间复杂度O(1)，空间复杂度O(1)
    */
    template<typename NodeType> void left_rotate(std::shared_ptr<NodeType> node,std::shared_ptr<NodeType>& root)
    {

        if (node)  //node非空
        {
            auto right=node->rchild; //r_node
            if(right)  //r_node非空
            {
                auto l_right=right->lchild; //l_r_node;
                right->parent=node->parent;       //r_node提至node的原位置
                auto shared_p=node->parent.lock(); //node的父节点
                if(shared_p)                      //node的父节点修订
                {
                   if(node->is_left_child()) shared_p->lchild=right;
                   if(node->is_right_child()) shared_p->rchild=right;
                }else
                {
                    root=right;
                }
                node->rchild=l_right; //r_node的左子节点剪切到 node的右侧
                if(l_right) l_right->parent=node;

                node->parent=right;  //node剪切到 r_node的左侧
                right->lchild=node;
               }
          }
    }

    //!right_rotate：二叉树的右旋转操作
    /*!
    * \param node: 待旋转的节点，强引用
    * \param root： 二叉树的根节点的强引用（当node指向树根时，旋转会导致丢失树根信息，此时由root返回新的树根）
    * \return void
    *
    * 本函数执行二叉树进行右旋转。设node为被旋转的点，l_node为它的左子节点，r_node为它的右子节点。
    * 则旋转的效果是：l_node取代了node的位置；而node现在挂靠在r_node的右子；l_node原来的右子现在成为node的左子
    *
    * <code><pre>
    *                   |                                                |
    *                  node                                            l_node
    *                 /    \                                           /    \
    *              l_node  r_node        -- 右旋  -->              l_l_node  node
    *             /    \                                                    /    \
    *        l_l_node r_l_node                                         r_l_node  r_node
    * </pre></code>
    * 时间复杂度O(1)，空间复杂度O(1)
    */
     template<typename NodeType> void  right_rotate(std::shared_ptr<NodeType> node,std::shared_ptr<NodeType>& root)
     {
            if (node)  //node非空
            {
                auto left=node->lchild;//l_node非空
                if(left)//l_node非空
                {
                    auto r_left=left->rchild; //r_l_node
                    left->parent=node->parent;//l_node提至node的原位置
                    auto shared_p=node->parent.lock();
                    if(shared_p)//node的父节点修订
                    {
                        if(node->is_right_child()) shared_p->rchild=left;
                        if(node->is_left_child()) shared_p->lchild=left;
                    }else
                    {
                        root=left;
                    }
                    node->lchild=r_left; //l_node的右子节点剪切到 node的左侧
                    if(r_left) r_left->parent=node;

                    node->parent=left;  //node剪切到 l_node的右侧
                    left->rchild=node;
                }
    }
  }

    //!transplant：二叉树的剪切操作
    /*!
    * \param node_src: 剪切源节点
    * \param root： 二叉树的根节点的强引用（当node指向树根时，剪切导致丢失树根信息，此时由root返回新的树根）
    * \param node_dst: 剪切目的节点
    * \return void
    *
    * 本函数执行二叉树的剪切操作。剪切操作要求目的节点是非空节点（若是空节点则抛出异常）。本操作将node_src剪切到node_dst中。下图中，两个节点之间有两个链接：一个是父-->子，另一个是子-->父
    * 剪切操作可能会仅仅剪断一个连接
    *
    *  <code><pre>
    *                 src_p         dst_p                                    src_p         dst_p             dst_p
    *                   ||            ||                               (父-->子)|             ||                |(子--->父)
    *                 node_src     node_dst         ---剪切 -->               node_src      node_src        node_dst
    *                 //   \\      //    \\                                 //     \\      //     \\        //     \\
    * </pre></code>
    * 时间复杂度O(1)，空间复杂度O(1)
    */
    template<typename NodeType> void  transplant(std::shared_ptr<NodeType> node_src,std::shared_ptr<NodeType>node_dst,std::shared_ptr<NodeType>& root)
     {
            if(!node_dst)
            {
                throw std::invalid_argument("transparent() should not be aplied on dst:nullptr ");
            }
            if(node_src) //替换掉parent
            {
                node_src->parent=node_dst->parent;
            }
            auto shared_p=node_dst->parent.lock();
            if(!shared_p) //node_dst是根节点
            {
                root=node_src;
                return;
            }else //node_dst不是根节点
            {
                if(node_dst->is_left_child()) //node_dst是左子
                {
                    shared_p->lchild=node_src;
                }else                         //node_dst是右子
                {
                    shared_p->rchild=node_src;
                }
            }
      }
}
}
#endif // BINARYTREE

