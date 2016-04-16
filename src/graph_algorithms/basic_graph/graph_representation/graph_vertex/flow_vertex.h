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
#ifndef FLOWVERTEX
#define FLOWVERTEX
#include"vertex.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {        
        //!FlowVertex：推送-重贴标签算法图的顶点，算法导论26章26.4节
        /*!
        *
        * FlowVertex 是 Vertex的子类。它比Vertex多了一个`int h` 成员变量。其中：
        *
        * - `KType key`：表示顶点的超额流量
        * - `int h`：表示顶点的高度
        */
        template<typename KType> struct FlowVertex:public Vertex<KType>
        {
            typedef KType KeyType;    /*!< 顶点存储数据的类型*/
            typedef int VIDType;      /*!< 顶点编号的数据类型*/

            //!默认构造函数
            FlowVertex():h(0){}
            //!显式构造函数，指定`key`
            /*!
            * \param  k:顶点存放的数据
            */
            explicit FlowVertex(const KeyType&k):h(0),Vertex<KType>(k){}
            //!显式构造函数，指定`key`和编号
            /*!
            * \param  k:顶点存放的数据
            * \param  d:顶点的编号
            */
            FlowVertex(const KeyType&k,VIDType d):h(0),Vertex<KType>(k,d){}

            //!to_string：返回顶点的字符串描述
            /*!
            * \return :顶点的字符串描述
            *
            * 在`Vertex`基类的基础上输出`h`信息
            */
            virtual std::string to_string() const
            {
                std::ostringstream os;
                os<<Vertex<KType>::to_string()<<"\t h:"<<h;
                return os.str();
            }
            int h;  /*!< 顶点高度*/
        };        
    }
}
#endif // FLOWVERTEX

