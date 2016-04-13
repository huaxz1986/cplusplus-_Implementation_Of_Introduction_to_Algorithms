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
#ifndef VERTEXP
#define VERTEXP
#include"vertex.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!VertexP：图的顶点，它带一个parent属性，算法导论22章22.1节
        /*!
        *
        * 它继承自Vertex，区别在于多了一个parent成员变量
        */
        template<typename KType> struct VertexP:public Vertex<KType>
        {
            typedef KType KeyType;    /*!< 顶点存储数据的类型*/
            typedef int VIDType;      /*!< 顶点编号的数据类型*/

            //!默认构造函数
            VertexP(){}
            //!显式构造函数，指定`key`
            /*!
            * \param  k:顶点存放的数据
            */
            explicit VertexP(const KeyType&k):Vertex<KeyType>(k){}
            //!显式构造函数，指定`key`和编号
            /*!
            * \param  k:顶点存放的数据
            * \param  d:顶点的编号
            */
            VertexP(const KeyType&k,VIDType d):Vertex<KeyType>(k,d){}

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
                if(parent) os<<parent->id;
                else os<<"nullptr";
                return os.str();
            }
            std::shared_ptr<VertexP> parent;/*!< 顶点的父顶点的强指针*/
        };
    }
}

#endif // VERTEXP

