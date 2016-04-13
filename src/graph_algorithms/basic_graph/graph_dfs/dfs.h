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
#ifndef DFS
#define DFS
#include<memory>
#include<functional>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!visit：深度优先搜索的辅助函数，用于访问顶点，算法导论22章22.3节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param v_id:待访问顶点的`id`，必须有效。如果无效则抛出异常
        * \param time:访问时刻，是一个引用参数，确保每次`visit`都访问同一个时钟。
        * \param pre_action:一个可调用对象，在每次发现一个顶点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次对一个顶点搜索完成时调用，调用参数为该顶点的`id`以及完成时间`time`。默认为空操作，即不进行任何操作
        *
        * `v_id`在以下情况下无效：
        *
        * - `v_id`不在区间`[0,N)`之间时，`v_id`无效
        * - `graph`中不存在某个顶点的`id`等于`v_id`时，`v_id`无效
        *
        * 在每次对一个结点调用visit的过程中，结点v_id的初始颜色都是白色。然后执行下列步骤：
        *
        * - 将全局时间 time 递增
        * - 发现结点 v_id
        * - 对结点 v_id 的每一个相邻结点进行检查，在相邻结点是白色的情况下递归访问该相邻结点
        * - 当结点 v_id 的相邻结点访问完毕，则全局时间 time 递增，然后将结点 v_id 设置为完成状态
        *
        */
        template<typename GraphType>
                    void visit(std::shared_ptr<GraphType> graph,typename GraphType::VIDType v_id,int&time,
                     std::function<void(typename GraphType::VIDType,int)> pre_action=[](typename GraphType::VIDType,int){},
                     std::function<void(typename GraphType::VIDType,int)> post_action=[](typename GraphType::VIDType,int){})
        {
            if(!graph)
                throw std::invalid_argument("visit error: graph must not be nullptr!");
            if(v_id<0||v_id>=GraphType::NUM||!graph->vertexes.at(v_id))
                throw std::invalid_argument("visit error: v_id muse belongs [0,N) and graph->vertexes[v_id] must not be nullptr!");

            time++;
            //*******  发现本顶点 *****************
            pre_action(v_id,time);
            graph->vertexes.at(v_id)->set_disovered(time);
            //********  搜索本顶点相邻的顶点*************
            for(const auto&edge:graph->vertex_edge_tuples(v_id))
            {
                auto another_id=std::get<1>(edge);
                auto another_vertex=graph->vertexes.at(another_id);
                if(another_vertex->color==GraphType::VertexType::COLOR::WHITE)
                {
                    another_vertex->parent=graph->vertexes.at(v_id);
                    visit(graph,another_id,time,pre_action,post_action);
                }
            }
            //*********** 完成本顶点的搜索
            time++;
            graph->vertexes.at(v_id)->set_finished(time);
            post_action(v_id,time);
        }

        //!depth_first_search：深度优先搜索，算法导论22章22.3节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param pre_root_action:一个可调用对象，在每次发现一个顶点且该顶点是深度优先森林的根节点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_root_action:一个可调用对象，在每次对一个顶点搜索完成时且该顶点是深度优先森林的根节点时调用调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param pre_action:一个可调用对象，在每次发现一个顶点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次对一个顶点搜索完成时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param search_order:指定搜索顶点的顺序（不同的搜索顺序可能形成的深度优先森林不同)，如果为空则按照顶点的`id`顺序。默认为空
        * \return:void
        *
        * 深度优先搜索：深度优先搜索总是对最近才发现的结点v的出发边进行搜索，直到该结点的所有出发边都被发现为止。一旦结点v的所有出发边都被发现，则“回溯”到v的前驱结点（v是经过该结点才被发现的）。
        * 该过程一直持续到源结点可以达到的所有结点都被发现为止。如果还存在尚未发现的结点，则深度优先搜索将从这些未被发现的结点中任选一个作为新的源结点，并重复同样的搜索过程。该算法重复整个过程，
        * 直到图中的所有结点被发现为止。
        *
        * 深度优先搜索维护一个全局的时间。每个结点v有两个时间戳，discover_time记录了v第一次被发现的时间（v涂上灰色的时刻）；finish_time记录了搜索完成v的相邻结点的时间（v涂上黑色的时刻）。
        * 结点v在v.discover_time之前为白色，在v.discover_time之后与v.finish_time之前为灰色，在v.finish_time之后为黑色
        *
        * 深度优先搜索步骤：
        *
        * - 初始化：将所有结点染白色，并将它们的父结点置为空(由于DFS_Vertex构造函数将结点color设为白色，且将父结点置为空，因此在本算法中这个步骤可以省略)
        * - 将全局时间 time 置为0
        * - 遍历结点集V，取出结点v
        *   -若v是白色的（尚未发现），则调用 visit 操作
        *   > 当这里调用 visit 操作时，结点v会成为一棵树的根
        *   >
        *   > 深度优先搜索的结果会依赖于遍历结点集V的顺序。不同的遍历顺序得到的结果会不同
        *
        * 深度优先搜索性能：时间复杂度 O(V+E)
        *
        * 深度优先搜索的性质：证明请参考《算法导论》:
        *
        * - 深度优先搜索生成的前驱子图G_pai是一个由多棵树构成的森林
        * - 结点 v 是结点 u 在深度优先森林中的后代当且仅当结点v在结点u为灰色的时间段内被发现
        * - 结点的发现时间和完成时间具有括号化结构：如果以左括号"(u"来表示结点u被发现，以后括号"u)"表示结点u完成。则发现和完成的历史记载会形成一个规整的表达式。
        *   在深度优先搜索中，对于任意两个结点u和v来说，下面三种情况只有一种成立
        *       - 区间[u.discover_time,u.finish_time]与区间[v.discover_time,v.finish_time]完全分离。
        *         此时在深度优先森林中，结点u不是结点v的后代，结点v也不是结点u的后代
        *       - 区间[u.discover_time,u.finish_time]完全包含在[v.discover_time,v.finish_time]，此时在深度优先森林中，结点u是结点v的后代
        *       - 区间[v.discover_time,v.finish_time]完全包含在[u.discover_time,u.finish_time]，此时在深度优先森林中，结点v是结点u的后代
        *
        * 深度优先森林的边：对于在图G上运行深度优先搜索算法所生成的深度优先森林G_pai，可以定义四种类型的边：
        *
        *  - 树边：它是深度优先森林的边。若结点v是因深度优先算法对边(u,v)的搜索而首先被发现，则(u,v)是一条树边
        *  - 后向边： 后向边(u,v)将结点u连接到其深度优先树中某个祖先结点v。对于有向图的自循环，自循环被认为是后向边
        *  - 前向边： 将结点u连接到其在深度优先树中一个后代结点v
        *  - 横向边： 其他的边。这些边可以连接同一棵深度优先树中的结点（只要其中一个结点不是另外一个结点的祖先），也可以连接不同深度优先树中的两个结点。
        *
        * 在深度优先搜索中，当第一次搜索边(u,v)时：
        *
        * - 若结点v为白色，表明边(u,v)是一条树边
        * - 若结点v为灰色，表明边(u,v)是一条后向边
        * - 若结点v为黑色，表明边(u,v)是一条前向边或者横向边
        *   - 在 u.discover_time< v.discover_time 时，为前向边
        *   - 在 u.discover_time< v.discover_time 时，为横向边
        *
        * 在无向图中，每条边要么是树边，要么是后向边。从来不会出现前向边和横向边。
        *
        */
         template<typename GraphType>
                    void  depth_first_search(std::shared_ptr<GraphType> graph,
                               std::function<void(typename GraphType::VIDType,int)> pre_action=[](typename GraphType::VIDType,int){},
                               std::function<void(typename GraphType::VIDType,int)> post_action=[](typename GraphType::VIDType,int){},
                               std::function<void(typename GraphType::VIDType,int)> pre_root_action=[](typename GraphType::VIDType,int){},
                               std::function<void(typename GraphType::VIDType,int)> post_root_action=[](typename GraphType::VIDType,int){},
                               const std::vector<typename GraphType::VIDType>& search_order=std::vector<typename GraphType::VIDType>())
        {
            typedef typename GraphType::VIDType VIDType;
            typedef typename GraphType::VertexType VertexType;
            if(!graph)
                throw std::invalid_argument("depth_first_search error: graph must not be nullptr!");
            //************  创建真实的 search_order ****************
            std::vector<VIDType> real_search_order;
            if(!search_order.size())
            {
                for(int i=0;i<GraphType::NUM;i++)
                    real_search_order.push_back(i);
            }else
                real_search_order=search_order;

            //************* 初始化顶点 ****************
            for(auto& v:graph->vertexes)
            {
                if(!v) continue;
                v->color=VertexType::COLOR::WHITE;
                v->key=0;
                v->parent=std::shared_ptr<VertexType>();
            }

            //*************** 深度优先搜索 *************
            int time=0;
            for(const auto& v_id :real_search_order)
            {
                if(v_id<0||v_id>=GraphType::NUM||!graph->vertexes.at(v_id)) //顶点为空
                    continue;
                auto v=graph->vertexes.at(v_id);
                if(v->color==GraphType::VertexType::COLOR::WHITE)
                {
                    pre_root_action(v_id,time);
                    visit(graph,v->id,time,pre_action,post_action);
                    post_root_action(v_id,time);
                }
            }
        }
   }
}


#endif // DFS

