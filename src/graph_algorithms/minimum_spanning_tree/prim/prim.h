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
#ifndef PRIM
#define PRIM
#include<functional>
#include"src/queue_algorithms/min_queue/minqueue.h"
#include"src/header.h"
using IntroductionToAlgorithm::QueueAlgorithm::MinQueue;
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!prim：最小生成树的Prim算法，算法导论23章23.2节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
        * \param pre_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次从最小优先级队列中弹出最小顶点并处理完它的边时立即调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \return: 最小生成树的权重
        *
        * `source_id`在以下情况下无效：
        *
        * - `source_id`不在区间`[0,N)`之间时，`source_id`无效
        * - `graph`中不存在某个顶点的`id`等于`source_id`时，`source_id`无效
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
        * ## Prim算法
        *
        * ### 算法原理
        *
        * 在Prim算法所具有的一个性质是集合A中的边总是构成一棵树。这棵树从一个任意的根结点r开始，一直长大到覆盖V中的所有结点为止。算法每一步在连接集合A和A之外的结点的所有边中，
        * 选择一条边加入到A中（经特殊选择的边）。
        *
        * 为了有效地实现Prim算法，需要一种快速的方法来选择一条新的边以便加入到由集合A中的边所构成的树中。在算法执行过程中，所有不在树A中的结点都存放在一个基于key的属性的最小优先级队列Q中。
        * 对于每个结点v，属性v.key保存的是连接v和树中结点的所有边中最小边的权重。若这样的边不存在则权重为正无穷。属性v.pai给出的是结点v在树中的父结点。
        *
        * ### 算法步骤
        *
        * - 初始化：将所有结点的key设为正无穷，所有结点的父结点置为空(结点构造时，父结点默认为空）
        * - 设置源点：将源点的key设为0，
        * - 构造最小优先级队列：将所有顶点放入最小优先级队列Q中
        * - 循环，直到最小优先级队列为空。循环中执行下列操作：
        *   - 弹出最小优先级队列的头部顶点u
        *   - 从结点u出发的所有边，找出它的另一端的结点v。如果v也在Q中，且w(u,v)<v.key，则证明(u,v)是v到集合A的最短边，因此设置v.pai=u,v.key=w(u,v)
        *   >这里隐含着一个最小优先级队列的decreate_key操作
        *
        * ### 算法性能
        *
        * Prim总时间代价为O(VlgV+ElgV)=O(ElgV)(使用最小堆实现的最小优先级队列），或者O(E+VlgV)（使用斐波那契堆实现最小优先级队列）
        */
        template<typename GraphType,typename ActionType=std::function< void(typename GraphType::VIDType)>>
        typename GraphType::EWeightType prim(std::shared_ptr<GraphType> graph,typename GraphType::VIDType source_id,
             ActionType pre_action=[](typename GraphType::VIDType){},ActionType post_action=[](typename GraphType::VIDType){})
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename VertexType::KeyType KeyType;
            if(!graph)
                throw std::invalid_argument("prim error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("prim error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            auto vertex_compare=[](std::shared_ptr<VertexType> first,std::shared_ptr<VertexType> second){return first->key<second->key;};
            auto vertex_key_get=[](std::shared_ptr<VertexType> v)->KeyType& {return v->key;};
            MinQueue<VertexType,KeyType> min_queue(vertex_compare,vertex_key_get);

            //********** 初始化顶点  ****************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex)
                {
                    if(i==source_id) vertex->key=0;
                    else vertex->key=unlimit<KeyType>();
                    vertex->parent=std::shared_ptr<VertexType>();//初始化所有结点
                    min_queue.insert(vertex);                  //添加顶点到最小优先级队列中
                }
            }

            typename GraphType::EWeightType weight=0;
            while(!min_queue.is_empty())
            {
                auto minNode=min_queue.extract_min();
                pre_action(minNode->id);

                auto edges =graph->vertex_edge_tuples(minNode->id);
                for(const auto& edge_tuple:edges)
                {
                    auto another_id=std::get<1>(edge_tuple);
                    auto another_vertex=graph->vertexes.at(another_id);
                    auto edge_weight=std::get<2>(edge_tuple);

                    auto index=min_queue.index_inqueue(another_vertex);
                    if(index>=0&& edge_weight<another_vertex->key)
                    {
                        another_vertex->parent=minNode;
                        another_vertex->key=edge_weight;
                        min_queue.decreate_key(index,edge_weight); //这里隐含着一个最小优先级队列的decreate_key操作
                    }
                }
                post_action(minNode->id);
                weight+=minNode->key;
            }
            return weight;
        }
    }
}
#endif // PRIM

