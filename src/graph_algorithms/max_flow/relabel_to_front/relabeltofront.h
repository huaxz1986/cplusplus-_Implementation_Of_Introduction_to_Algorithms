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
#ifndef RELABELTOFRONT
#define RELABELTOFRONT
#include<memory>
#include"../generic_push_relabel/genericpushrelabel.h"
#include"../../basic_graph/graph_representation/graph_vertex/front_flow_vertex.h"

namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!discharge：最大流的前置重贴标签算法中的释放操作。算法导论26章26.5节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param u_id: 图的顶点id，必须有效否则抛出异常
        * \param flow: 预流
        * \return: void
        *
        *  如果顶点无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        *
        * 对于溢出结点u,如果将其所有多余的流通过许可边推送到相邻的结点上，则称该结点得到释放。
        * 在释放过程中，需要对结点u进行重贴标签操作，这使得从结点u发出的边成为许可边。discharge(u) 操作步骤如下：
        *
        * - 循环，条件为u.e>0，循环内操作为：
        *   - 获取u.current，假设为v
        *   - 如果v为空，即遍历到u.N链表的末尾，则对u执行relabel操作，然后将u.current指向u.N链表的头部
        *   - 如果 v非空，且满足 push 操作的条件(c_f(u,v)>0且 u.h=v.h+1)，则执行push操作
        *   - 如果 v 非空，但不满足 push 操作，则 u.current指向u.N链表的下一个结点
        *
        */
        template<typename GraphType> void discharge(std::shared_ptr<GraphType> graph,typename GraphType::VIDType u_id,
                                               std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {

            typedef typename GraphType::EWeightType EWeightType;

            if(!graph)
                throw std::invalid_argument("discharge error: graph must not be nullptr!");
            if(u_id<0||u_id>=GraphType::NUM)
                throw std::invalid_argument("discharge error:id must >=0 and <N.");
            auto vertex_u=graph->vertexes.at(u_id);
            if(!vertex_u)
                throw std::invalid_argument("discharge error: vertex of id does not exist.");
            //**************  开始循环  *******************
            while(vertex_u->key>0)
            {
                 auto node_v=vertex_u->N_List.current; //
                 if(!node_v)
                 {
                     relabel(graph,u_id,flow);
                     vertex_u->N_List.current=vertex_u->N_List.head;
                 }else
                 {
                     EWeightType c_f=0;
                     auto vertex_v=node_v->value.lock();
                     //***********  获取 c_f(u,v)  **************
                     assert(vertex_v);
                     auto v_id=vertex_v->id;
                     if(graph->has_edge(u_id,v_id))
                         c_f=graph->weight(u_id,v_id)-flow[u_id][v_id];
                     else if(graph->has_edge(v_id,u_id))
                         c_f=flow[v_id][u_id];
                     else throw std::invalid_argument("discharge error: (u,v) belongs E or (v,u) belongs E must be true!");

                     //************  根据 c_f(u,v)以及 h函数决定是否 push  **************
                     if(c_f>0 &&(vertex_u->h==vertex_v->h+1))
                         push(graph,u_id,v_id,flow);
                     else
                         vertex_u->N_List.current=vertex_u->N_List.current->next;

                 }

            }
        }
        //!create_L：前置重贴标签算法中的创建L链表操作
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param src: 流的源点，必须有效否则抛出异常
        * \param dst: 流的汇点，必须有效否则抛出异常
        * \return: 初始化的L链表
        *
        *  如果src、dst任何一个顶点无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        * 该操作将所有的除s、t之外的顶点加入到L链表中
        */
        template<typename GraphType> List<ListNode<typename GraphType::VertexType>>
        create_L (std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,typename GraphType::VIDType dst)
        {
            typedef ListNode<typename GraphType::VertexType> LNodeType;
            typedef List<LNodeType> LType;

            if(!graph)
                throw std::invalid_argument("create_L error: graph must not be nullptr!");
            if(src<0||src>=GraphType::NUM||dst<0||dst>=GraphType::NUM)
                throw std::invalid_argument("create_L error:id must >=0 and <N.");
            if(!graph->vertexes.at(src) || !graph->vertexes.at(dst))
                throw std::invalid_argument("create_L error: vertex of id does not exist.");

            LType L;
            for(int i=0;i<GraphType::NUM;i++)
            {
                if(i==src||i==dst) continue;
                std::shared_ptr<LNodeType> node=std::make_shared<LNodeType>();
                node->value=graph->vertexes[i];
                L.add(node);
            }
            return L;
        }


        //!initial_vertex_NList：前置重贴标签算法中的初始化邻接链表操作
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param src: 流的源点，必须有效否则抛出异常
        * \param dst: 流的汇点，必须有效否则抛出异常
        * \return: void
        *
        *  如果src、dst任何一个顶点无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        * 该操作将初始化除了s、t之外所有顶点的邻接链表
        */
        template<typename GraphType> void
        initial_vertex_NList(std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,typename GraphType::VIDType dst)
        {
            typedef ListNode<typename GraphType::VertexType> VertexNListNodeType;

            if(!graph)
                throw std::invalid_argument("initial_vertex_NList error: graph must not be nullptr!");
            if(src<0||src>=GraphType::NUM||dst<0||dst>=GraphType::NUM)
                throw std::invalid_argument("initial_vertex_NList error:id must >=0 and <N.");
            if(!graph->vertexes.at(src) || !graph->vertexes.at(dst))
                throw std::invalid_argument("initial_vertex_NList error: vertex of id does not exist.");
            for(int i=0;i<GraphType::NUM;i++)
            {
                if(i==src||i==dst) continue;
                auto vertex_u=graph->vertexes[i];
                //************ 扫描邻接矩阵  **************
                const auto& matrix=graph->matrix.matrix;
                const auto & invalid_weight=graph->matrix.invalid_weight;
                for(int j=0;j<GraphType::NUM;j++)
                {
                    if(matrix[i][j]!=invalid_weight)//从u出发的边
                    {
                        std::shared_ptr<VertexNListNodeType> node=std::make_shared<VertexNListNodeType>();
                        node->value=graph->vertexes[j];
                        vertex_u->N_List.add(node);
                    }
                    if(matrix[j][i]!=invalid_weight)//进入u的边
                    {
                        std::shared_ptr<VertexNListNodeType> node=std::make_shared<VertexNListNodeType>();
                        node->value=graph->vertexes[j];
                        vertex_u->N_List.add(node);
                    }
                }
                vertex_u->N_List.current=vertex_u->N_List.head;//将 u.N.current设为u.N.head
            }
        }

        //!relabel_to_front：最大流的前置重贴标签算法。算法导论26章26.5节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param src: 流的源点，必须有效否则抛出异常
        * \param dst: 流的汇点，必须有效否则抛出异常
        * \return: 最大流矩阵
        *
        *  如果src、dst任何一个顶点无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        * ## 最大流
        *
        *
        * 流网络G=（V,E）是一个有向图，图中每条边(u,v)属于E都有一个正的容量值c(u,v)>0。而且如果边集合E中包含一条边(u,v)，则图中不存在反向边
        * (v,u)。为方便起见，假设(u,v)不属于E,定义c(u,v)=0（即无效权重为0），并且在图中不允许自循环。
        *
        * 在流网络中存在两个特殊点：源结点s和汇点t。假定每一个结点都在从源点s到汇点t的某条路径上。即对于每个结点v属于E，存在某条路径
        * s-->v-->t。
        *
        * G中的流是一个实值函数f:V*V-->R，满足下面两条性质：
        *
        * - 容量限制：对于所有结点u,v属于V，要求0<= f(u,v) <= c(u,v)
        * - 流量守恒： 对于所有结点u属于V-{s,t}，要求：从u进入的流等于从u出去的流
        *
        * 对于(u,v)不属于E的情况，从结点u到v之间没有流，因此f(u,v)=0。我们称非负数值f(u,v)为从结点u到v的流。一个流f的值
        * |f|=从源点流出的总流量- 流入源结点的总流量
        *
        * 最大流问题：给定流网络G、一个源结点s、一个汇点t,找出值最大的一个流
        *
        * ## relabel_to_front 算法
        *
        * ### 算法原理
        *
        * >本节的一些概念参考  generic_push_relabel 算法
        *
        * 推送-重贴标签方法允许我们以任意次序执行基本操作。但是，如果仔细选择这个次序，并且对网络数据结构进行高效管理，我们可以获取更高的算法性能。
        *
        * 前置重贴标签算法在执行过程中维持一个网络中的结点的链表。算法从头到尾对链表进行扫描，每次选择一个溢出结点u。
        * 然后对结点u进行“释放”，即对所选结点执行推送操作和重贴标签操作，直到结点u不再拥有正值的超额流量为止。
        * 每次在算法对一个结点进行重贴标签操作时，我们都将该结点移动到链表的最前面（也就是“前置重贴标签算法”的名字由来），然后算法进行一次新的扫描。
        *
        * 设图G=(V,E)是一个源点s汇点t的流网络，f是G中的一个预流（它满足容量限制单不满足流量守恒性质），h是一个高度函数。
        * 对于边(u,v)，如果c_f(u,v)>0且h(u)=h(v)+1，则边(u,v)是一条许可边；否则边(u,v)是一条非许可边。许可边意义是：在残余网络中，
        * 流可以经过它进行推送的边。许可网络指图G_f_h=(V,E_f_h)，其中E_f_h是许可边的集合。
        *
        * 在前置重贴标签算法中，我们将所有边都组织为“邻接链表”。给定流网络G=(V,E)，对于结点u属于V，其邻接链表u.N是结点u在图G
        * 中的邻接结点所构成的一个单链表（包括了u的上游和下游的邻接结点）：若边(u,v)属于E或者边(v,u)属于E，则结点v将出现在链表u.N中。
        * >邻接链表u.N包含的结点是所有可能存在残留边(u,v)的结点v
        *
        * 属性u.N.head指向的是邻接表u.N中的第一个结点；v.next-neighbor指向的是邻接链表u.N中位于结点v后面的一个结点。如果v是链表中最后一个结点，
        * 则该指针的值为NIL
        *
        * 前置重贴标签算法以任意次序遍历每一个邻接链表，该次序在算法整个执行过程中不变。对于每个结点u，属性u.current指向的是u.N
        * 链表中当前正在考虑的结点。初始情况下u.current指向u.N.head
        *
        *
        * ### 基本操作
        *
        * #### discharge 操作
        *
        * 对于溢出结点u,如果将其所有多余的流通过许可边推送到相邻的结点上，则称该结点得到释放。
        * 在释放过程中，需要对结点u进行重贴标签操作，这使得从结点u发出的边成为许可边。discharge(u) 操作步骤如下：
        *
        * - 循环，条件为u.e>0，循环内操作为：
        *   - 获取u.current，假设为v
        *   - 如果v为空，即遍历到u.N链表的末尾，则对u执行relabel操作，然后将u.current指向u.N链表的头部
        *   - 如果 v非空，且满足 push 操作的条件(c_f(u,v)>0且 u.h=v.h+1)，则执行push操作
        *   - 如果 v 非空，但不满足 push 操作，则 u.current指向u.N链表的下一个结点
        *
        * ### 算法步骤
        *
        * - 初始化预流操作（与 generic_push_relabel 算法相同）
        * - 对所有的非s、t的结点，将它们加入到链表L中（顺序任意）
        * - 对所有的非s、t的结点u,初始化u.current为u.N.head
        * - 设置u为L.head
        * - 循环，条件为u!=NIL，循环中操作：
        *   - 保留u.h为oldh
        *   - 对u执行discharge操作
        *   - 如果u.h>oldh，证明对u执行了重贴标签操作，此时将u移动到L的头部
        *   - u=u.next（提取u在L中的下一个）
        *
        * ### 算法性能
        *
        * 算法性能：时间复杂度 O(V^3)
        *
        *
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>
        relabel_to_front(std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,typename GraphType::VIDType dst)
        {
               typedef typename GraphType::EWeightType EWeightType;
               typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;



                if(!graph)
                    throw std::invalid_argument("relabel_to_front error: graph must not be nullptr!");
                if(src<0||src>=GraphType::NUM||dst<0||dst>=GraphType::NUM)
                    throw std::invalid_argument("relabel_to_front error:id must >=0 and <N.");
                if(!graph->vertexes.at(src) || !graph->vertexes.at(dst))
                    throw std::invalid_argument("relabel_to_front error: vertex of id does not exist.");

               MatrixType flow;
               initialize_preflow(graph,src,flow);

               auto L=create_L(graph,src,dst); // create List L
               initial_vertex_NList(graph,src,dst); //create u.N for each u

               //************   循环 **************

               auto node_u=L.head;
               while(node_u)
               {
                   auto vertex_u=node_u->value.lock();
                   assert(vertex_u);
                   auto old_height=vertex_u->h;   //保存旧h值
                   discharge(graph,vertex_u->id,flow); //释放u
                   if(vertex_u->h>old_height)        //若重贴标签则h值增加，则u前置到L头部
                   {
                        if(node_u!=L.head) //当u已经是L头时无需操作
                        {
                            L.front_of(node_u)->next=node_u->next;
                            node_u->next=L.head;
                            L.head=node_u;
                        }
                   }
                   node_u=node_u->next;
               }
               return flow;
        }
    }
}
#endif // RELABELTOFRONT

