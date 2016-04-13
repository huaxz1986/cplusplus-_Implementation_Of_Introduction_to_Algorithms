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
#ifndef SET_VERTEX
#define SET_VERTEX
#include"vertex.h"
#include"src/set_algorithms/disjoint_set/disjointset.h"
using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!SetVertex：图的顶点，它带一个node属性，算法导论22章22.1节
        /*!
        *
        * 它继承自Vertex，区别在于多了一个node成员变量，这个node是指向DisjointSetNode<SetVertex>对象的强指针。
        * 而DisjointSetNode<SetVertex>的value成员变量是指向SetVertex的弱指针，二者可以相互访问。
        * >SetVertex没有父结点指针。要想访问SetVertex的父结点，首先要取得它对应的DisjointSetNode结点。然后获取该DisjointSetNode结点的父结点。
        * 然后通过该父结点获取value指向的SetVertex即可。
        */
        template<typename KType> struct SetVertex:public Vertex<KType>
        {
            typedef KType KeyType;    /*!< 顶点存储数据的类型*/
            typedef int VIDType;      /*!< 顶点编号的数据类型*/


            //!默认构造函数
            SetVertex(){}
            //!显式构造函数，指定`key`
            /*!
            * \param  k:顶点存放的数据
            */
            explicit SetVertex(const KeyType&k):Vertex<KeyType>(k){}
            //!显式构造函数，指定`key`和编号
            /*!
            * \param  k:顶点存放的数据
            * \param  d:顶点的编号
            */
            SetVertex(const KeyType&k,VIDType d):Vertex<KeyType>(k,d){}

            //!to_string：返回顶点的字符串描述
            /*!
            * \return :顶点的字符串描述
            *
            * 依次输出顶点的`id`、`key`、`parent`信息。
            */
            virtual std::string to_string() const
            {
                std::ostringstream os;
                os<<Vertex<KeyType>::to_string()<<"\t parent:";
                auto nd=node;
                if(nd&&nd->parent&&nd->parent->value.lock())
                    os<<nd->parent->value.lock()->id;
                else
                    os<<"nullptr";

                return os.str();
            }

            std::shared_ptr<DisjointSetNode<SetVertex> > node;/*!< 顶点对应的DisjointSetNode的强指针*/
        };
    }
}

#endif // SET_VERTEX

