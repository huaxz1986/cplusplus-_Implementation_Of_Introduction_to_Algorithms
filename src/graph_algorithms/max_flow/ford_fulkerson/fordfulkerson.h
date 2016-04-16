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
#ifndef FORDFULKERSON
#define FORDFULKERSON
#include<memory>
#include<array>
#include<vector>
#include<functional>
#include"src/header.h"
#include"../../basic_graph/graph_bfs/bfs.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!create_Gf：根据指定流网络生成一个残余网络。算法导论26章26.2节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param flow: 一个流
        * \return: 残余网络
        *
        * ## 残余网络
        * 给定网络G(V,E)和流量f，残余网络Gf(V,Ef)由那些仍有空间对流量进行调整的边构成。Gf中的顶点就是原图G中的顶点。残余网络Gf中的边可以由以下组成：
        *
        * - 若(u,v)属于E，且f(u,v)<c(u,v)，则存在边(u,v)属于Ef，且cf(u,v)=c(u,v)-f(u,v)，表示沿着该方向图G中还能流通cf大小的流量
        * - 若(u,v)属于E，则存在边(v,u)属于Ef,且 cf(v,u)=c(u,v)，表示沿着(u,v)的反方向（即(v,u)方向)可以压入cf大小的反向流量
        * > 这里f(u,v)为边(u,v)上的流；c(u,v)为图G的边(u,v)的容量；cf(u,v)为残余网络Gf上的边(u,v)的容量
        *
        * 这里假定容量c>0，一旦容量c=0表示边不存在（禁止流通）；f>=0，表示流是正向的。同时假定图中不存在双向边：
        * 图G中不可能同时存在边(u,v)以及边(v,u)（即管道是单向的）
        *
        * 要求graph的无效权重为0，否则抛出异常
        *
        * 性能：时间复杂度 O(V+E)
        *
        */
        template<typename GraphType> std::shared_ptr<GraphType>
            create_Gf(const std::shared_ptr<GraphType> graph,
                      std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {
            typedef typename GraphType::EdgeTupleType EdgeTupleType;
            if(!graph)
                throw std::invalid_argument("create_Gf error: graph must not be nullptr!");
            if(graph->matrix.invalid_weight!=0)
                throw std::invalid_argument("create_Gf error: graph invalid weight must be 0!");

            int new_invalid_weight=0;
            std::shared_ptr<GraphType> new_graph=std::make_shared<GraphType>(new_invalid_weight);
            //*************  创建新图的顶点  ******************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex)
                    new_graph->add_vertex(vertex->key,vertex->id);
            }

            //**********   创建新图的边  ***********************
            std::vector<EdgeTupleType> new_edges;
            for(int i=0;i<GraphType::NUM;i++)
                for(int j=0;j<GraphType::NUM;j++)
                {
                   if(i==j) continue;
                   if(!graph->vertexes[i]||!graph->vertexes[j]) continue;
                   if(graph->has_edge(i,j)) //(u,v)属于E
                       new_edges.push_back(std::make_tuple(i,j,graph->weight(i,j)-flow[i][j]));
                   else if(graph->has_edge(j,i))  //(v,u)属于E
                       new_edges.push_back(std::make_tuple(i,j,flow[j][i]));
                }
            new_graph->add_edges(new_edges.begin(),new_edges.end());
            return new_graph;
        }


        //!ford_fulkerson：最大流的ford_fulkerson算法。算法导论26章26.2节
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
        * ## ford_fulkerson算法
        *
        * ### 算法原理
        *
        * ford_fulkerson 算法更准确的称呼是一种方法而不是算法，因为它包含了几种运行时间各不相同的具体实现。
        * 它依赖于三种重要思想：残余网络、增广路径和切割。
        *
        * #### 残余网络
        *
        *  给定流网络G(V,E)和流量f，残余网络Gf(V,Ef)由那些仍有空间对流量进行调整的边构成。
        *  Gf中的顶点就是原图G中的顶点。残余网络Gf中的边可以由以下组成：
        *
        * - 若(u,v)属于E，且f(u,v)<c(u,v)，则存在边(u,v)属于Ef，且cf(u,v)=c(u,v)-f(u,v)，表示沿着该方向图G中还能流通cf大小的流量
        * - 若(u,v)属于E，则存在边(v,u)属于Ef,且 cf(v,u)=c(u,v)，表示沿着(u,v)的反方向（即(v,u)方向)可以压入cf大小的反向流量
        * > 这里f(u,v)为边(u,v)上的流；c(u,v)为图G的边(u,v)的容量；cf(u,v)为残余网络Gf上的边(u,v)的容量
        *
        * #### 增广路径
        *
        * 给定流网络G=(V,E)和流f，增广路径p是残余网络Gf中一条源结点s到汇点t的简单路径。我们称一条增广路径
        * p上能够为每条边增加的流量的最大值为路径p的残余容量，定义为 cf(p)= min {cf(u,v):(u,v)属于路径p}
        *
        * #### 最大流和最小切割定理
        *
        * 流网络G=(V,E)的一个切割(S,T)是将结点集合V划分为S和T=V-S两个集合，使得s属于S，t属于T。切割(S,T)
        * 的容量c(S,T)=c(u,v)的累加，其中u属于S,v属于T
        *
        * 设f为流网络G=(V,E)中的一个流，该流网络的源点为s，汇点为t，则下面的条件是等价的：
        *
        * - f是G的一个最大流
        * - 残余网络Gf不包括任何增广路径
        * - |f|=c(S,T)，其中(S,T)是流网络G的某个切割
        *
        * ### 算法步骤
        *
        * ford_fulkerson算法循环增加流的值。在开始的时候对于所有的结点u,v属于V，f(u,v)=0。在每一轮迭代中，
        * 我们将图G的流值进行增加，方法就是在G的残余网络Gf中寻找一条增广路径。算法步骤如下：
        *
        * - 初始化： 创建流矩阵flow，flow[i][j]均初始化为0
        * - 循环迭代：
        *   - 根据flow和G创建残余网络Gf，寻找增广路径
        *   - 若增广路径不存在，则跳出迭代，证明现在的流就是最大流
        *   - 若增广路径存在，则更新流矩阵。更新方法为：
        *       - 取出增广路径的残余容量 cf(p)= min {cf(u,v):(u,v)属于路径p}，然后更新增广路径p中的边(u,v)：
        *           - 若(u,v)属于图G的边E，则 flow[u][v]=flow[u][v]+cf(p)
        *           - 若(v,u)属于图G的边E，则 flow[u][v]=flow[u][v]-cf(p)
        * - 返回流矩阵 flow
        *
        * ### 算法性能
        *
        * ford_fulkerson算法运行时间取决于如何寻找增广路径。如果选择不好，算法可能不会终止：流的值会随着后续的递增而增加，
        * 但是它却不一定收敛于最大的流值。如果用广度优先搜索来寻找增广路径，算法的运行时间将会是多项式数量级。
        *
        * 假定最大流问题中的容量均为整数，由于流量值每次迭代中最少增加一个单位，因此算法运行时间为 O(E|f*|) ,|f*|为最大流的值
        *
        *
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>
        ford_fulkerson(const std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,typename GraphType::VIDType dst)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef typename GraphType::VIDType VIDType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;
            typedef std::function<void(VIDType v_id)> ActionType;

            if(!graph)
                throw std::invalid_argument("ford_fulkerson error: graph must not be nullptr!");
            if(src<0||src>=GraphType::NUM||dst<0||dst>=GraphType::NUM)
                throw std::invalid_argument("ford_fulkerson error:id must >=0 and <N.");
            if(!graph->vertexes.at(src) || !graph->vertexes.at(dst))
                throw std::invalid_argument("ford_fulkerson error: vertex of id does not exist.");


            ActionType empty_action=[](VIDType v_id){};
            //********** 初始化 flow 为全 0 **********
            MatrixType flow;
            for(int i=0;i<GraphType::NUM;i++)
                for(int j=0;j<GraphType::NUM;j++)
                    flow[i][j]=0;

            std::shared_ptr<GraphType> Gf;
            while(true)
            {
                Gf=create_Gf(graph,flow); //创建残余网络
                //************ 寻找增广路径  *************
                breadth_first_search<GraphType>(Gf,src,empty_action,empty_action);
                auto path=get_path(Gf->vertexes.at(src),Gf->vertexes.at(dst));
                if(path.size()==0) break;  //不存在增广路径

                EWeightType cf=unlimit<EWeightType>();
                for(int i=1;i<path.size();i++)  //求取增广路径的残余容量
                {
                    auto u=path[i-1];
                    auto v=path[i];
                    auto w=Gf->weight(u,v);
                    if(w<cf) cf=w;
                }
                //*****************  更新流矩阵  ***************
                for(int i=1;i<path.size();i++)
                {
                    auto u=path[i-1];
                    auto v=path[i];
                    if(graph->has_edge(u,v)) //(u,v)属于E
                        flow[u][v]+=cf;
                    else if(graph->has_edge(v,u))  //(v,u)属于E
                        flow[v][u]-=cf;
                }
            }
            return flow;
        }
    }
}
#endif // FORDFULKERSON

