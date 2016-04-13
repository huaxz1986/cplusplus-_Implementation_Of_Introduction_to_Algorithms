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
#ifndef DISJOINTSET
#define DISJOINTSET
#include<memory>
#include<vector>
namespace IntroductionToAlgorithm
{
    namespace SetAlgorithm
    {

    //!DisjointSetNode：不相交集合森林的节点，算法导论第21章21.3节
    /*!
    *
    * 一个不相交集合数据结构维护了一个不相交动态集的集合{S1,S2,...Sk}。我们用一个代表来标识每个集合，它是这个集合的某个成员。
    * 不相交集合支持三个操作：（x,y等都是集合中的对象)
    *
    * - make_set(x):建立一个新的集合，它的唯一成员是x
    * - unionx(x,y):将包含x和y的两个动态集合(表示为Sx和Sy)合并成一个新的集合。由于我们要求各个集合不相交，因此这里要消除原有的集合Sx和Sy。实际操作中，
    *   我们把其中的一个集合的元素并入另一个集合中，来代替删除操作。
    * - find_set(x):返回一个指针，该指针指向包含x的唯一集合的代表。
    *
    * 在某些图的算法中，图和不相交集数据结构的表示需要相互引用。即一个表示顶点的对象会包含一个指向与之对应的不相交集合对象的指针；反之亦然
    *
    * 不相交集合森林：不相交集合森林是不相交集合的一种更快的实现。用有根数来表示集合，树中的每个结点都包含一个成员，每棵树代表一个集合。
    * 在不相交集合森林中，每个成员仅仅指向它的父节点。每棵树的根就是集合的代表并且它的父节点就是自己。
    *
    * 这里采用了启发式策略改进运行时间，使用了两种启发式策略：
    *   - 按秩合并：每个结点x维持一个整数值属性rank,它代表了x的高度（从x到某一后代叶结点的最长简单路径上的结点数目）的一个上界。在按秩合并的union操作中，
    *   我们让具有较小秩的根指向具有较大秩的根
    *   - 路径压缩：在`find_set`操作中，使查找路径中的每个结点直接指向树根
    *
    * 如果单独采用按秩合并或者路径压缩，它们每一个都能改善不相交集合森林上操作的运行时间；而一起使用这两种启发式策略时，这种改善更大。
    * 当同时使用按秩合并和路径压缩时，最坏情况下的运行时间为O(m*alpha*n))，这里alpha(n)是一个增长非常慢的函数。在任何一个可以想得到的不相交集合数据结构的应用中，
    * alpha(n)<=4。其中n为结点个数，m为操作次数（运用了摊还分析）
    *
    */
    template<typename KType> struct DisjointSetNode
    {
        typedef KType KeyType;  /*!< 结点保存的数据类型*/

        //!DisjointSetNode的显式构造函数
        /*!
        *
        * \param v:结点保存的数据的指针
        *
        * 将v存入结点的value中
        */
        explicit DisjointSetNode(std::shared_ptr<KeyType>v):value(v){}

        std::weak_ptr<KeyType> value;/*!< 结点保存的数据的弱指针*/
        int rank;/*!< 结点的秩*/
        std::shared_ptr<DisjointSetNode> parent;/*!< 结点的父指针*/

        //!find_set：返回结点所在集合的代表结点
        /*!
        *
        * \param node:要查找的结点。它必须非空，否则抛出异常
        * \return: 结点所在集合的代表结点的强指针
        *
        * 该操作简单沿着指向父节点的指针找到树的根。树的根的特征是：它的父节点就是它本身。
        * 若结点不在不相交集合森林中（当结点的父节点指针为空时），则抛出异常。
        *
        * find_set过程是一个 two_pass method，当它递归时，第一趟沿着查找路径向上直到找到树根；
        * 当递归回溯时，第二趟沿着搜索树向下更新每个节点，使其父节点直接指向树根
        *
        */
       static  std::shared_ptr<DisjointSetNode> find_set(std::shared_ptr<DisjointSetNode>node)
        {
            if(!node)
                throw std::invalid_argument("find_set error: node must not be nullptr!");
            if(node->parent!=node)
                node->parent=find_set(node->parent);
            return node->parent;
        }
        //!make_set：创建集合
        /*!
        *
        * \param node:创建集合的结点。它必须非空，否则抛出异常
        *
        * 该操作简单地创建一棵只有一个结点的树。它将树根的秩设为0，将树根的父节点指向树根本身
        *
        */
        static void make_set(std::shared_ptr<DisjointSetNode>node)
        {
            if(node)
            {
               node->parent=node;
               node->rank=0;
            }else
            {
                throw std::invalid_argument("make_set error: node must not be nullptr!");
            }
        }

        //!link_set：链接集合
        /*!
        *
        * \param nodeX:待链接的第一个集合中的根节点。
        * \param nodeY:待合并的第二个集合中的根节点
        *
        * 每个结点x维持一个整数值属性rank,它代表了x的高度（从x到某一后代叶结点的最长简单路径上的结点数目）的一个上界。在链接时我们让具有较小秩的根指向具有较大秩的根.
        *
        * - 如果 nodeX或者nodeY为空，则直接返回
        * - 如果 nodeX 和 nodeY非空，但是nodeX或者nodeY不是根结点，抛出异常
        *
        */
        static void link_set(std::shared_ptr<DisjointSetNode>nodeX,std::shared_ptr<DisjointSetNode>nodeY)
        {
            if(!nodeX|| !nodeY)
                return;
            if(nodeX!=nodeX->parent||nodeY!=nodeY->parent)
                throw std::invalid_argument("link_set error: node must be root of the set!");
            if(nodeX->rank>nodeY->rank)
            {
                nodeY->parent=nodeX;
            }else
            {
                nodeX->parent=nodeY;
                if(nodeX->rank==nodeY->rank)
                {
                    nodeY->rank++;
                }
            }
        }
        //!union_set：合并集合
        /*!
        *
        * \param nodeX:待合并的第一个集合中的某个结点
        * \param nodeY:待合并的第二个集合中的某个结点
        *
        * 该操作首先获取每个结点所在集合的代表结点，然后将它们合并起来
        *
        */
        static void union_set(std::shared_ptr<DisjointSetNode>nodeX,std::shared_ptr<DisjointSetNode>nodeY)
        {
            link_set(find_set(nodeX),find_set(nodeY));
        }
    };

  }
}


#endif // DISJOINTSET

