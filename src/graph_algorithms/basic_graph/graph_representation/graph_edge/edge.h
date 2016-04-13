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
#ifndef GRAPHEDGE
#define GRAPHEDGE
#include<tuple>
#include<memory>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!Edge：图的边，算法导论22章22.1节
        /*!
        *
        * 边主要包含三个数据：
        *
        * - `vertex1`：第一个顶点的强引用：
        * - `vertex2`为第二个顶点的强引用。
        * - `weight`: 边的权重（为int类型，可为正、负值）
        *
        * 为了便于计算，这里定义了一个元组，类型为`std::tuple<VIDType,VIDType,EWeightType>`，元组的第一个元素为第一个顶点的`id`；元组的第二个元素为第二个顶点的`id`；
        * 元组的第三个元素为边的权重。
        */
        template<typename VType> struct Edge
        {
        public:
            typedef int VIDType;     /*!< 顶点编号的类型*/
            typedef int EWeightType; /*!< 权重的类型*/
            typedef VType VertexType; /*!< 顶点的类型*/
            typedef std::tuple<VIDType,VIDType,EWeightType> EdgeTupleType; /*!< 边的三元素（顶点1编号，顶点2编号，权重)组成的元组*/
            //! 显式构造函数，必须指定两个顶点和一个权重
            /*!
            * \param v1:第一个顶点的强引用
            * \param v2:第二个顶点的强引用
            * \param w: 边的权重
            */
            Edge(std::shared_ptr<VertexType>v1,std::shared_ptr<VertexType>v2,EWeightType w):
                vertex1(v1),vertex2(v2),weight(w)
            {
                assert(vertex1&&vertex2);
            }
            //!to_string：返回边的字符串描述
            /*!
            *\return:边的字符串描述
            *
            */
            virtual std::string  to_string()const
            {
                std::ostringstream os;
                os<<"edge weight:"<<weight<<"\t vertex[id1:"<<vertex1->id<<",id2:"<<vertex2->id<<"]";
                return os.str();
            }
            //!edge_tuple：获取边的三元素元组
            /*!
            * \return:边的三元素元组
            */
            const EdgeTupleType edge_tuple() const
            {
                return std::make_tuple(vertex1->id,vertex2->id,weight);
            }
            std::shared_ptr<VertexType> vertex1;   /*!< 边的第一个顶点*/
            std::shared_ptr<VertexType> vertex2;   /*!< 边的第二个顶点*/
            EWeightType weight;                    /*!< 边的权重*/
        };
    }
}
#endif // GRAPHEDGE

