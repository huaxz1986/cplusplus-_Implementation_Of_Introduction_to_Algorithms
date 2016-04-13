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
#ifndef DIJKSTRA
#define DIJKSTRA
#include<vector>
#include"../bellman_ford/bellmanford.h"
#include"src/queue_algorithms/min_queue/minqueue.h"

using IntroductionToAlgorithm::QueueAlgorithm::MinQueue;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!dijkstra：单源最短路径的dijkstra算法，算法导论24章24.3节
        /*!
        * \param graph:指向图的强指针，必须非空。若为空则抛出异常
        * \param source_id：最小生成树的根结点`id`，必须有效。若无效则抛出异常
        * \return: void
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
        * ## Dijkstra算法
        * ### 算法原理
        *
        * Dijkstra算法解决的是有向图中的单源最短路径问题。Dijkstra算法要求所有边的权重都为非负值。
        *
        * Dijkstra算法核心信息是一组结点集合 S 。从源结点s 到集合 S 中的每一个结点之间的最短路径已经被找到。算法重复从结点集合 V-S 中选择最短路径估计最小的结点u,
        * 将u加入到集合S中，然后对所有从u出发的边进行松弛。本算法利用最小优先队列Q来保存结点集合，每个结点的关键字为它的key值。
        *
        * ### 算法步骤
        *
        * - 调用 `initialize_single_source`函数对图的顶点进行初始化
        * - 将集合S置为空，将所有顶点放入最小优先队列Q
        * - 循环操作直到Q为空，循环内执行以下操作：
        *   - 弹出最小优先级队列队首元素u
        *   - 将u对应的结点放入集合S中
        *   - 对从u出发的边且另一端在Q中的边进行松弛。松弛过程隐含着Q的一个`decreate_key()`方法的调用
        *
        *
        * ### 算法性能
        *
        * 时间复杂度为O(V^2+E)
        *
        */
        template<typename GraphType> void dijkstra(std::shared_ptr<GraphType> graph, typename GraphType::VIDType source_id)
        {
            typedef typename GraphType::VIDType VIDType;
            typedef typename GraphType::VertexType VertexType;
            typedef typename VertexType::KeyType KeyType;

            if(!graph)
                throw std::invalid_argument("dijkstra error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("dijkstra error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            initialize_single_source(graph,source_id);
            std::vector<VIDType> current_S;

            auto vertex_compare=[](std::shared_ptr<VertexType> first,std::shared_ptr<VertexType> second){return first->key<second->key;};
            auto vertex_key_get=[](std::shared_ptr<VertexType> v)->KeyType& {return v->key;};
            MinQueue<VertexType,KeyType> min_queue(vertex_compare,vertex_key_get);

            //********** 添加顶点到最小优先级队列中  ****************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex) min_queue.insert(vertex);
            }
            while(!min_queue.is_empty())
            {
                auto node=min_queue.extract_min();
                current_S.push_back(vertex_key_get(node));
                for(const auto& edge:graph->vertex_edge_tuples(node->id))
                {
                    auto another_vertex=graph->vertexes.at(std::get<1>(edge));
                    relax(node,another_vertex,std::get<2>(edge));
                    auto index=min_queue.index_inqueue(another_vertex);
                    if(index>=0) //边的另一端在最小优先级队列Q中
                        min_queue.decreate_key(index,vertex_key_get(another_vertex));
                }
            }
        }
    }
}
#endif // DIJKSTRA

