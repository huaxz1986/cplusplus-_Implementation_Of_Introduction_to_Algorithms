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
#ifndef BELLMAN_FORD
#define BELLMAN_FORD
#include<memory>
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!initialize_single_source：单源最短路径的初始化操作，算法导论24章24.1节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
        * \return: void
        *
        * `source_id`在以下情况下无效：
        *
        * - `source_id`不在区间`[0,N)`之间时，`source_id`无效
        * - `graph`中不存在某个顶点的`id`等于`source_id`时，`source_id`无效
        *
        * 单源最短路径的初始化操作将所有的结点的`key`设置为正无穷，将所有结点的`parent`设为空。然后将源结点的`key`设为0。
        *
        * 性能：时间复杂度O(V)
        *
        */
        template<typename GraphType> void initialize_single_source(std::shared_ptr<GraphType> graph, typename GraphType::VIDType source_id)
        {
            if(!graph)
                throw std::invalid_argument("initialize_single_source error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("initialize_single_source error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            //**************** 设置所有结点 *****************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex)
                {
                    vertex->key=unlimit<typename GraphType::VertexType::KeyType>();
                    vertex->parent=std::shared_ptr<typename GraphType::VertexType>();
                }
            }
            //**************  设置源结点 ***************
            graph->vertexes.at(source_id)->key=0;

        }

        //!relax：单源最短路径的松弛操作，算法导论24章24.1节
        /*!
        * \param from:松弛有向边的起始结点，必须非空。若为空则抛出异常
        * \param to：松弛有向边的终止结点，必须非空且不等于from。若为空或者等于from则抛出异常
        * \param weight:有向边的权重
        * \return: void
        *
        *
        * 对每一个结点v来说，我们维持一个属性v.key，它记录了从源结点s到结点v的最短路径权重的上界。我们称v.key为s到v的最短路径估计。
        *
        * 松弛过程是测试一下是否可以对从s到v的最短路径进行改善的过程，测试方法为：
        * 将结点s到u之间的最短路径估计加上(u,v)边的权重，并与当前的s到v之间的最短路径估计进行比较。如果前者较小则对v.key和v.parent进行更新。
        *
        * 性能：时间复杂度O(1)
        *
        *
        */
        template<typename VertexType> void relax(std::shared_ptr<VertexType> from,std::shared_ptr<VertexType> to,typename VertexType::KeyType weight)
        {
            if(!from || !to)
                throw std::invalid_argument("relax error: from_vertex and to_vertex must not be nullptr!");
            if(from==to)
                throw std::invalid_argument("relax error: from_vertex must not be to_vertex!");
            if((from->key+weight)>=unlimit<typename VertexType::KeyType>()) //u.key+weight为正无穷，则不可能松弛
                return;
            if(to->key>from->key+weight)
            {
                to->key=from->key+weight;
                to->parent=from;
            }

        }

        //!bellman_ford：单源最短路径的bellman_ford算法，算法导论24章24.1节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
        * \return: 是否不包含可以从源结点可达的权重为负值的环路。若返回值为true，则说明不包含可以从源结点可达的权重为负值的环路
        *
        * ## 单源最短路径
        *
        * 单源最短路径问题：给定一个带权重的有向图G=(V,E)和权重函数w:E->R，该权重函数将每条边映射到实数值的权重上。图中一条路径p=<v0,v1,...vk>的权重
        * w(p)=w(v0,v1)+w(v1,v2)+...+w(v(k-1),vk)。定义结点u到结点v的最短路径权重 delt(u,v)为：
        *
        * - min{w(p):u-->v(通过路径p)}，如果存在一条从结点u到结点v的路径
        * - 正无穷 ，如果不存在一条从结点u到结点v的路径
        *
        * 从结点u到结点v的最短路径定义为任何一条权重w(p)=delt(u,v)的从u到v的路径p。
        *
        * 给定图G=(V,E)，对每个结点v我们维持一个前驱结点v.pai。在最短路径算法中，由pai值诱导的前驱子图G_pai=(V_pai,E_pai)，其中 V_pai={v属于V:v.pai!=nil}并上源点s，
        * E_pai是V_pai中所有结点的pai值诱导的边的集合：E_pai={(v.pai,v)属于E:v属于V_pai-{s} }。算法终止时，G_pai是一棵最短路径树：该树包含了从源结点s
        * 到每个可以从s到达的结点的一条最短路径。
        *
        * 需要指出的是：最短路径不一定是唯一的，最短路径树叶不一定是唯一的。
        *
        *
        * ## Bellman-Ford算法
        *
        * ### 算法原理
        *
        * Bellman-Ford算法解决的是一般情况下的单源最短路径问题。在这里边的权重可以为负值。给定带权的有向图G=(V,E)和权重函数w:E->R，Bellman-Ford
        * 算法返回一个bool值，表明是否存在一个从源结点可达的权重为负值的环路。若存在这样的一个环路，算法告诉我们不存在解决方案；若不存在这样的环路，
        * 算法将给出最短路径和它们的权重。
        *
        * Bellman-Ford算法通过对边的松弛操作来渐近的降低从源s到每个结点v的最短路径估计值v.key，直到该估计值与实际的最短路径权重相同为止。
        *
        * ### 算法步骤
        *
        * - 执行单源最短路径的初始化过程
        * - 进行|V|-1次处理，每次处理过程为：对图的每一条边进行一次松弛操作
        * - 检查图中是否存在权重为负的环路并返回与之相适应的布尔值
        *
        *
        * ### 算法性能
        *
        * 时间复杂度为O(VE)
        *
        */
        template<typename GraphType> bool bellman_ford(std::shared_ptr<GraphType> graph, typename GraphType::VIDType source_id)
        {

            if(!graph)
                throw std::invalid_argument("bellman_ford error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("bellman_ford error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            initialize_single_source(graph,source_id);
            //************* 循环处理  ***************
            for(int i=0;i<GraphType::NUM-1;i++)
            {
                for(const auto&edge:graph->edge_tuples())
                {
                    relax(graph->vertexes[std::get<0>(edge)],graph->vertexes[std::get<1>(edge)],std::get<2>(edge));
                }
            }
            //**********  检验是否存在从源点可达的权重为负的环路 *************
            for(const auto&edge:graph->edge_tuples())
            {
                if(graph->vertexes[std::get<1>(edge)]->key>graph->vertexes[std::get<0>(edge)]->key+std::get<2>(edge))
                    return false;
            }
            return true;
        }
    }
}
#endif // BELLMAN_FORD

