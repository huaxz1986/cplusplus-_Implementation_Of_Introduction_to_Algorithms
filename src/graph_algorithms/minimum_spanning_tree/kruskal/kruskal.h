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
#ifndef KRUSKAL
#define KRUSKAL
#include"src/set_algorithms/disjoint_set/disjointset.h"

using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;

namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!kruskal：最小生成树的Kruskal算法，算法导论23章23.2节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
        * \param pre_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点并处理完它的边时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \return: 最小生成树的权重
        *
        * ## 最小生成树
        *
        * 最小生成树：对于一个连通无向图G=(V,E)，对于每一条边(u,v)属于E都赋予了一个权重w(u,v)。我们希望找出一个无环子集T，其中T为E的子集，使得所有的顶点V位于T中，
        * 同时T具有最小的权重。由于T是无环的，且连通所有结点因此T必然是一棵树。我们称这样的树为生成树。称从G中求取该生成树的问题为最小生成树问题。
        *
        * 通用的最小生成树使用贪心策略。该策略在每个时刻找到最小生成树的一条边，并在整个策略过程中维持循环不变式：边的集合A在每次循环之前是某棵最小生成树的一个子集。
        *
        * 在每一步，选择一条边(u,v)，将其加入集合A中，使得A不违反循环不变式。称这样的边(u,v)为边集合A的安全边。
        *
        * ## Kruskal 算法
        *
        * ### 算法原理
        *
        * 在Kruskal算法中集合A是一个森林，其结点就是G的结点。Kruskal算法找到安全边的办法是：在所有连接森林中两棵不同树的边里面，找到权重最小的边(u,v)。
        * Kruskal算法使用一个不相交集合数据结构来维护几个互不相交的元素集合。每个集合代表当前森林中的一棵树
        *
        * ### 算法步骤
        *
        * - 初始化：将集合A置为空；对G中的每一个结点v,以它为根构造一棵单根树
        * - 将G中的边E按照权重单调递增的顺序排序
        * - 循环挑选E中的(u,v)，按照单调增的顺序。在循环内执行：
        *   - 如果u所在的树不等于v所在的树，则将(u,v)加入A中，并且合并u所在的树与v所在的树
        *
        * >根据算法的特征，如果图中只有一个顶点，算法得到的集合A为空集；但是实际上集合A应该包含该顶点。这是算法在极端情况下的BUG。
        *
        * ### 算法性能
        *
        * Kruskal算法运行时间依赖于不相交集合数据结构的实现方式。如果采用算法导论21.3节讨论的不相交集合森林实现（也是我在src/set_algorithms/disjoint_set中实现的），
        * 则Kruskal算法的时间为 O(ElgV)
        */
        template<typename GraphType,typename ActionType=std::function< void(typename GraphType::VIDType,typename GraphType::VIDType)>>
        typename GraphType::EWeightType kruskal(std::shared_ptr<GraphType> graph,
        ActionType pre_action=[](typename GraphType::VIDType,typename GraphType::VIDType){},
        ActionType post_action=[](typename GraphType::VIDType,typename GraphType::VIDType){})
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename GraphType::EdgeTupleType EdgeTupleType;
            typedef DisjointSetNode<VertexType> NodeType;
            if(!graph)
                throw std::invalid_argument("kruskal error: graph must not be nullptr!");
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
            typename GraphType::EWeightType weight=0;
            auto edges=graph->edge_tuples();
            std::sort(edges.begin(),edges.end(),
               [](const EdgeTupleType&edge1,const EdgeTupleType&edge2)->bool{ return std::get<2>(edge1)<std::get<2>(edge2);});
            for(const auto&edge:edges)
            {
                auto from_id=std::get<0>(edge);
                auto to_id=std::get<1>(edge);
                auto edge_weight=std::get<2>(edge);
                auto from_vertex_set_node=graph->vertexes.at(from_id)->node;
                auto to_vertex_set_node=graph->vertexes.at(to_id)->node;
                if(NodeType::find_set(from_vertex_set_node)!=NodeType::find_set(to_vertex_set_node))
                {
                        pre_action(from_id,to_id);
                        NodeType::union_set(from_vertex_set_node,to_vertex_set_node);
                        weight+=edge_weight;
                        post_action(from_id,to_id);
                }

            }
            return weight;
        }
    }
}


#endif // KRUSKAL

