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
#ifndef BFS
#define BFS
#include<memory>
#include<queue>
#include<functional>
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!breadth_first_search：广度优先搜索，算法导论22章22.2节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param source_id：广度优先搜索的源点`id`，必须有效。若无效则抛出异常
        * \param pre_action:一个可调用对象，在每次发现一个顶点时调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次对一个顶点搜索完成时调用，调用参数为该顶点的`id`。默认为空操作，即不进行任何操作
        * \return:void
        *
        * `source_id`在以下情况下无效：
        *
        * - `source_id`不在区间`[0,N)`之间时，`source_id`无效
        * - `graph`中不存在某个顶点的`id`等于`source_id`时，`source_id`无效
        *
        *
        * 广度优先搜索：该算法维护已经发现结点和未发现结点的边界，沿着其广度方向向外扩展。每个结点有三种颜色：白色、灰色、黑色。
        * 白色结点表示未发现；灰色结点表示已发现但是未处理完成；黑色结点表示已处理完成。其中灰色结点就是边界。
        *
        * 给定图 G=(V,E)和一个可以识别的源点`s`。。所有的结点在一开始都被涂上白色。每个结点的颜色存放在属性`color`中；
        * 每个结点的前驱结点放在属性`parent`中。每个结点的属性`key`存放的是从源点到本结点的距离。该算法使用一个先进先出的队列Q来管理灰色结点集。
        *
        * - 将所有结点涂为白色，`key`属性设置为正无穷，父结点置为空；
        * - 将源点涂为灰色，源点前驱设为空，源点的`key`设为0；
        * - 将源点加入队列Q中；Q中存放的都是已发现但是尚未处理完成的结点
        * - 循环直到队列Q为空，在循环中执行以下操作：
        *   - 取出队列Q头部的结点`v`
        *   - 对结点`v`的邻接表中的白色结点进行发现操作，并将这些结点加入队列Q中
        *   - 对结点`v`染成黑色；
        *
        * 算法的时间复杂度为 O(E+V)
        *
        * 最短路径：广度优先搜索能找出给定源结点s到所有可以到达的结点之间的距离。定义从源s到结点v之间的最短路径距离 delt(s,v) 为从结点s到v之间的所有路径里面最少的边数。
        * 如果从s到v没有路径，则 delt(s,v)=正无穷大 。我们定义从s到v之间的长度为 delt(s,v) 的路径为 s 到 v 的最短路径。可以证明：广度优先搜索可以正确计算出最短路径距离。
        *
        * 广度优先树：对于G=(V,E)和源点s，定义图G的前驱子图为 G_pai=(V_pai,E_pai)，其中 V_pai={ v属于V: v.parent!=NIL}并上{s}，E_pai={(v.parent,v):v属于(V_pai-{s})}。
        * 即V_pai由从源s可达的所有结点组成（包括s本身），E_pai由V_pai中去掉s之后的结点的入边组成，其中该入边的对端为结点的父结点。
        * BFS算法获取的前驱子图G_pai包含一条从源结点s到结点v的唯一简单路径，而且该路径也是图G里面从源s到v之间的一条最短路径，因此前驱子图也称为广度优先树。
        *
        */
    template<typename GraphType> void breadth_first_search(std::shared_ptr<GraphType> graph,
                      typename GraphType::VIDType source_id,
                      std::function< void(typename GraphType::VIDType)> pre_action=[](typename GraphType::VIDType){},
                      std::function< void(typename GraphType::VIDType)> post_action=[](typename GraphType::VIDType){})
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename GraphType::VIDType VIDType;

            if(!graph)
                throw std::invalid_argument("breadth_first_search error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("breadth_first_search error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            std::queue<std::shared_ptr<VertexType>> v_queue;
            //************* 初始化顶点 ****************
            for(auto& v:graph->vertexes)
            {
                if(!v) continue;
                v->color=VertexType::COLOR::WHITE;
                v->key=unlimit<typename VertexType::KeyType>();
                v->parent=std::shared_ptr<VertexType>();
            }
            //************* 处理源顶点 ****************
            graph->vertexes.at(source_id)->set_source();
            v_queue.push(graph->vertexes.at(source_id));
            pre_action(source_id);
            //************ 处理其他顶点 ***************
            while(!v_queue.empty())
            {
                auto front=v_queue.front();
                v_queue.pop();

                for(const auto& edge :graph->vertex_edge_tuples(front->id))
                {
                    VIDType next_id=std::get<1>(edge);
                    auto next_vertex=graph->vertexes.at(next_id);
                    if(next_vertex->color==VertexType::COLOR::WHITE)
                    {
                        next_vertex->set_found(front);
                        v_queue.push(next_vertex);
                        pre_action(next_id);
                    }
                }
                front->color=VertexType::COLOR::BLACK;
                post_action(front->id);
            }
        }

    }
}


#endif // BFS

