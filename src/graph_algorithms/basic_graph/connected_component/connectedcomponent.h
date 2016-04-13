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
#ifndef CONNECTEDCOMPONENT
#define CONNECTEDCOMPONENT
#include"src/set_algorithms/disjoint_set/disjointset.h"


using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!connected_component：无向图的连通分量，算法导论21章21.1节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \return:void
        *
        * connected_component函数使用不相交集合操作来计算一个无向图的连通分量。一旦connected_component函数与处理了该图，same_component
        * 函数就会回答两个顶点是否在同一个连通分量。
        *
        * connected_component算法步骤：
        *
        * - 将每个顶点v放入它自己的集合中
        * - 对每一条边(u,v)，它将包含u和v的集合进行合并
        *
        * 在处理完搜有边之后，两个顶点在相同的连通分量当且仅当与之对应的对象在相同的集合中
        */
        template<typename GraphType> void connected_component(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::VertexType VertexType;
            typedef DisjointSetNode<VertexType> NodeType;
            if(!graph)
                throw std::invalid_argument("connected_component error: graph must not be nullptr!");
            //*********** 初始化 ****************
            std::vector<std::shared_ptr<NodeType>> sets;

            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex) //添加顶点到`disjoint_set`中
                {
                    auto set_node=std::make_shared<NodeType>(vertex);
                    sets.push_back(set_node);
                    vertex->node=set_node;
                    NodeType::make_set(set_node);
                }
            }
            //****************** 循环  ************************
            auto edges=graph->edge_tuples();
            for(const auto&edge:edges)
            {
                auto from_vertex_set_node=graph->vertexes.at(std::get<0>(edge))->node;
                auto to_vertex_set_node=graph->vertexes.at(std::get<1>(edge))->node;
                if(NodeType::find_set(from_vertex_set_node)!=NodeType::find_set(to_vertex_set_node))
                {
                     NodeType::union_set(from_vertex_set_node,to_vertex_set_node);
                }

            }
        }

        //!same_component：返回无向图的两个顶点是否位于同一个连通分量中。算法导论21章21.1节
        /*!
        *
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param id1:第一个顶点，必须有效。若无效则抛出异常
        * \param id2:第二个顶点，必须有效。若无效则抛出异常
        *
        * 当满足以下条件之一时，id无效的情况：
        *
        * - id小于0或者大于等于`GraphType::NUM`
        * - `graph->vertexes.at(id1)`为空
        *
        * 在执行 same_component函数之前必须先执行 connected_component函数对无向图进行预处理。
        *
        */
        template<typename GraphType> bool same_component(std::shared_ptr<GraphType> graph,
                         typename GraphType::VIDType id1,typename GraphType::VIDType id2)
        {

            typedef typename GraphType::VertexType VertexType;
            typedef DisjointSetNode<VertexType> NodeType;

            if(!graph)
                throw std::invalid_argument("same_component error: graph must not be nullptr!");
            if(id1<0||id1>=GraphType::NUM||!graph->vertexes.at(id1)||id2<0||id2>=GraphType::NUM||!graph->vertexes.at(id2))
                throw std::invalid_argument("same_component error: id muse belongs [0,N) and graph->vertexes[id] must not be nullptr!");

            if(NodeType::find_set(graph->vertexes.at(id1)->node)==NodeType::find_set(graph->vertexes.at(id2)->node))
            {
                    return true;
            }else
                return false;
        }
    }
}
#endif // CONNECTEDCOMPONENT

