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
#ifndef DAGSHORTPATH
#define DAGSHORTPATH
#include<memory>
#include<functional>
#include"../bellman_ford/bellmanford.h"
#include"../../basic_graph/topology_sort/topologysort.h"

namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!dag_shortest_path：有向无环图的单源最短路径的dag_shortest_path算法，算法导论24章24.2节
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
        * ## dag_shortest_path算法
        *
        * ### 算法原理
        *
        * dag_shortest_path算法解决的是有向无环图中的单源最短路径问题。在有向无环图中不存在环路因此也就不存在权重为负值的环路，最短路径都是存在的。
        * dag_shortest_path根据结点的拓扑排序次数来对带权重的有向无环图进行边的松弛操作，可以再O(V+E)时间内计算出单源最短路径。
        *
        * ### 算法步骤
        *
        * - 对有向无环图进行拓扑排序
        * - 执行单源最短路径的初始化过程
        * - 按照顶点的拓扑排序的顺序依次处理，每次处理过程为：对该顶点出发的每一条边进行一次松弛操作
        *
        *
        * ### 算法性能
        *
        * 时间复杂度为O(V+E)
        *
        */
        template<typename GraphType> void dag_shortest_path(std::shared_ptr<GraphType> graph, typename GraphType::VIDType source_id)
        {
            typedef typename GraphType::VIDType VIDType;
            if(!graph)
                throw std::invalid_argument("dag_shortest_path error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("dag_shortest_path error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            auto sorted_vertexs=topology_sort(graph);
            initialize_single_source(graph,source_id);

            for(const VIDType& v_id:sorted_vertexs)
            {
                for(const auto&edge:graph->vertex_edge_tuples(v_id))
                   relax(graph->vertexes.at(v_id),graph->vertexes.at(std::get<1>(edge)),std::get<2>(edge));
            }
        }
    }
}


#endif // DAGSHORTPATH

