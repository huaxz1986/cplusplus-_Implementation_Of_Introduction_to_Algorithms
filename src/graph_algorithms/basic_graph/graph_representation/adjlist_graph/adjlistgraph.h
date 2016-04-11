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
#ifndef ADJLISTGRAPH
#define ADJLISTGRAPH
#include<vector>
#include<array>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!ADJListGraph：图的邻接表表示，算法导论22章22.1节
        /*!
        * 图的邻接表主要包含一个数据：
        *
        * - `array`：邻接表，类型为`std::array<std::vector<std::pair<VIDType,EWeightType>>,N> `，为`N`行，每一行代表一个节点：
        *
        * 为了便于计算，这里并不管理边和顶点，只是维护邻接表。边、顶点与邻接表的同步由使用者确保。
        */
        template<unsigned N> struct ADJListGraph
        {
            typedef int VIDType;     /*!< 顶点编号的类型*/
            typedef int EWeightType; /*!< 权重的类型*/
            typedef std::tuple<VIDType,VIDType,EWeightType> EdgeTupleType; /*!< 边的三元素（顶点1编号，顶点2编号，权重)组成的元组*/
            static const unsigned NUM=N; /*!< 顶点的最大容量*/
            //!add_edge:添加一条边
            /*!
            * \param  edge_tuple:一条边的三元素元组
            *
            * 为了便于计算，添加边时并不是添加`Edge`类型，而是`std::tuple<VIDType,VIDType,EWeightType>`类型的值。
            *
            * 如果指定节点之间的边已经存在，则抛出`std::invalid_argument`异常
            * > 要求边的顶点均在`[0,N)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效，直接返回而不作添加
            */
            void add_edge(const EdgeTupleType& edge_tuple)
            {
                auto id1=std::get<0>(edge_tuple);
                auto id2=std::get<1>(edge_tuple);
                auto wt=std::get<2>(edge_tuple);
                if(id1<0||id1>=N||id2<0||id2>=N)
                    return;
                if(has_edge(id1,id2))
                    throw std::invalid_argument("edge add error,edge has already exist.");
                array.at(id1).push_back(std::make_pair(id2,wt));
            }
            //!add_edges:添加一组边
            /*!
            * \param  begin:边容器的起始迭代器
            * \param  end:边容器的终止迭代器
            *
            * 为了便于计算，添加边时并不是添加`Edge`类型，而是`std::tuple<VIDType,VIDType,EWeightType>`类型的值
            *
            * 如果指定节点之间的边已经存在，则抛出`std::invalid_argument`异常
            * > 要求边的顶点均在`[0,N)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效，直接返回而不作添加
            */
            template<typename Iteator> void add_edges(const Iteator&begin ,const Iteator&end)
            {
                if(std::distance(begin,end)<=0)
                    return;
                auto iter=begin;
                while(iter!=end)
                {
                    add_edge(*iter);
                    iter++;
                }
            }
            //!adjust_edge:修改一条边的权重
            /*!
            * \param  id1:待修改边的第一个顶点
            * \param  id2:待修改边的第二个顶点
            * \param  wt:新的权重
            *
            * 修改顶点`id1`和`id2`直接的边的权重为`wt`。如果指定结点之间的边不存在，则抛出`std::invalid_argument`异常。
            * > 要求`id1`和`id2`均在`[0,N)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效，直接返回而不作权重修改
            *
            */
            void adjust_edge(VIDType id1,VIDType id2,EWeightType wt)
            {
                if(id1<0||id1>=N||id2<0||id2>=N)
                    return;
                if(!has_edge(id1,id2))
                    throw std::invalid_argument("edge adjust error,edge does not exist.");
                auto& vec=array.at(id1);  //这里必须用引用类型，因为要修改邻接表
                for(auto& pair:vec)
                {
                    if(pair.first==id2)
                    {
                        pair.second=wt;
                        break;
                    }
                }
            }            
            //!edge_tuples:返回图中所有边的三元素元组集合，这里集合采用`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
            /*!
            * \return  :图中所有边的三元素元组集合
            *
            */
            const std::vector<EdgeTupleType> edge_tuples() const
            {
                std::vector<EdgeTupleType> result;
                for(unsigned i=0;i<N;i++)
                    for(const auto& pair:array.at(i))
                    {
                        result.push_back(std::make_tuple(i,pair.first,pair.second));
                    }
                return result;
            }
            //!vertex_edge_tuples:返回图中从指定顶点出发的边的三元素元组集合，这里集合采用`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
            /*!
            * \param id: 指定顶点`id`
            * \return  :图中指定顶点出发的边的三元素元组集合
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            */
            const std::vector<EdgeTupleType> vertex_edge_tuples(VIDType id) const
            {
                if(id<0||id>=N)
                {
                    throw std::invalid_argument("vertex_edge_tuples: id must belongs [0,N),");
                }
                std::vector<EdgeTupleType> result;
                for(const auto& pair:array.at(id))
                {
                        result.push_back(std::make_tuple(id,pair.first,pair.second));
                }
                return result;
            }
            //!has_edge:返回图中指定顶点之间是否存在边
            /*!
            * \param id_from: 第一个顶点的`id`
            * \param id_to: 第二个顶点的`id`
            * \return  :第一个顶点和第二个顶点之间是否存在边
            *
            * - 当`id_from`与`id_to`无效时，抛出异常
            * >这里的无效值得是`id_from`、`id_to`不在区间`[0,N)`之间
            * - 当`id_from`与`id_to`之间有边时，返回`true`
            * - 当`id_from`与`id_to`之间没有边时，返回`false`
            */
            bool has_edge(VIDType id_from,VIDType id_to) const
            {
                if(id_from<0||id_from>=N||id_to<0||id_to>=N)
                {
                    throw std::invalid_argument("has_edge: id_from  and id _to must belongs [0,N),");
                }
                const auto& vec=array.at(id_from);
                for(const auto& pair:vec)
                {
                    if(pair.first==id_to)
                        return true;
                }
                return false;
            }
            //!weight:返回图中指定顶点之间的边的权重
            /*!
            * \param id_from: 第一个顶点的`id`
            * \param id_to: 第二个顶点的`id`
            * \return  :第一个顶点和第二个顶点之间的边的权重
            *
            * 当且仅当`id_from`与`id_to`之间存在边时返回该边的权重。其他情况下都会抛出`std::invalid_argument`异常
            *
            * - 当`id_from`与`id_to`无效时，抛出异常
            * >这里的无效值得是`id_from`、`id_to`不在区间`[0,N)`之间
            * - 当`id_from`与`id_to`之间无边时，抛出异常
            */
            EWeightType weight(VIDType id_from,VIDType id_to) const
            {
                if(has_edge(id_from,id_to))
                {
                    const auto& vec=array.at(id_from);
                    for(const auto& pair:vec)
                    {
                        if(pair.first==id_to)
                            return pair.second;
                    }
                }else
                {
                    throw std::invalid_argument("weight error: the edge does not exist.");
                }
            }
            std::array<std::vector<std::pair<VIDType,EWeightType>>,N> array; /*!< 图的邻接表*/
        };
    }
}
#endif // ADJLISTGRAPH

