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
#ifndef TOPOLOGYSORT
#define TOPOLOGYSORT
#include"../graph_dfs/dfs.h"
#include<vector>
#include<functional>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!topology_sort：拓扑排序，算法导论22章22.4节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \return:拓扑排序结果，它是顶点`id`组成的`std::vector`，表示顶点的拓扑排序后的顺序
        *
        * 对于一个有向无环图G=（V，E)，其拓扑排序是G中所有结点的一种线性次序，该次序满足如下条件：
        * 如果图G包含边(u,v)，则结点u在拓扑排序中处于结点v的前面。
        *
        * 拓扑排序原理：对有向无环图G进行深度优先搜索。每当完成一个结点时，将该结点插入到拓扑排序结果的头部。
        * 因此如果将结点按照完成时间降序排列，则得到的就是拓扑排序的结果。
        *
        * 引理：一个有向图G=(V,E)是无环的当且仅当对其进行深度优先搜索时不产生后向边。
        *
        * 性能：时间复杂度O(V+E)
        *
        */
        template<typename GraphType> std::vector<typename GraphType::VIDType> topology_sort(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::VIDType VIDType;
            typedef std::function<void(VIDType v_id,int time)> ActionType;
            if(!graph)
                throw std::invalid_argument("topology_sort error: graph must not be nullptr!");

            std::vector<VIDType> sorted_result;
            ActionType empty_action=[](VIDType v_id,int time){};
            ActionType finish_action=[&sorted_result](VIDType v_id,int time){sorted_result.insert(sorted_result.begin(),v_id);};
            depth_first_search(graph,empty_action,finish_action,empty_action,empty_action);
            return sorted_result;
        }
    }
}

#endif // TOPOLOGYSORT

