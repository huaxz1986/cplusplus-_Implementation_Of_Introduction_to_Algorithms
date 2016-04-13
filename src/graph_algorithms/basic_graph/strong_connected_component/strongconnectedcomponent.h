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
#ifndef STRONGCONNECTEDCOMPONENT
#define STRONGCONNECTEDCOMPONENT
#include"../graph_dfs/dfs.h"
#include<set>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {        
        //!scc：强连通分量，算法导论22章22.5节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \return:强连通分量的`std::vector`，每一个强连通分量，由一组顶点`id`组成的`std::vector`表示。
        *
        * 有向图G=(V,E)的强连通分量是一个最大结点集合C，C是V的子集。对于C中的任意一对结点u,v来说，路径u-->v和路径v-->u同时存在。即结点u和结点v之间相互可以到达。
        *
        * 在强连通分量的算法中，需要用到图G的转置G_T。定义G_T=(V,E_T),其中E_T={(u,v):(v,u)属于E}，即G_T中的边是G中的边进行反向获得。
        *
        * - 图G和图G_T的强连通分量相同
        * - 可以证明，`scc`算法得到的就是强连通分量。证明见《算法导论》
        *
        * 强连通分量算法步骤：
        *
        *   - 对原图G执行深度优先搜索，并获取每个结点的完成时间 finish_time
        *   - 对转置图G_T执行深度优先搜索，但是按照 G中结点的一个排序来搜索（这个排序是按照finish_time的降序）
        *   - G_T的深度优先森林就是强连通分量
        *
        * 性能：时间复杂度O(V+E)
        *
        */
        template<typename GraphType> const std::vector<std::vector<typename GraphType::VIDType>> scc(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::VIDType VIDType;
            if(!graph)
                throw std::invalid_argument("scc error: graph must not be nullptr!");

            //*********  原图的深度优先搜索 ***************
            std::vector<VIDType> finished_order;
            auto empty_action=[](VIDType v_id,int time){};
            auto finish_action=[&finished_order](VIDType v_id,int time){finished_order.insert(finished_order.begin(),v_id);}; //完成时间逆序
            depth_first_search(graph,empty_action,finish_action);
            //*********** 转置图的深度优先搜索*********
            std::vector<std::vector<typename GraphType::VIDType>> result;
            int current_root_id=-1;

            auto pre_root_action=[&result,&current_root_id](VIDType v_id,int time){result.push_back(std::vector<typename GraphType::VIDType>());current_root_id++;};//遇到深度优先森林的树根，开启一个新的强连通分量
            auto pre_action=[&result,&current_root_id](VIDType v_id,int time){result.at(current_root_id).push_back(v_id);}; //将结点`id`添加到强连通分量中

            auto inverse_G=graph->inverse();
            depth_first_search(inverse_G,pre_action,empty_action,pre_root_action,empty_action,finished_order);

            //**********  剔除单根树 *************
            std::vector<std::vector<typename GraphType::VIDType>> real_result;
            for(const auto& item:result)
                if(item.size()>1)
                    real_result.push_back(item);
            return real_result;
        }
    }
}
#endif // STRONGCONNECTEDCOMPONENT

