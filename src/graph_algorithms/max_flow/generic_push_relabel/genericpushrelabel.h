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
#ifndef GENERICPUSHRELABEL
#define GENERICPUSHRELABEL
#include<memory>
#include<array>
#include<vector>
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!push：generic_push_relabel算法的push操作。算法导论26章26.4节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param u_id: 结点u的id，必须有效否则抛出异常
        * \param v_id: 结点v的id，必须有效否则抛出异常
        * \param flow: 预流的引用（执行过程中会更新预流）
        * \return: void
        *
        *  如果u_id或者v_id无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        * 如果一个结点 u是一个溢出结点，则至少有一条入边，假设为(v,u)，且f(v,u)>0。此时残留网络G_f中的边c_f(u,v)>0。如果此时还有h(u)=h(v)+1，
        * 则可以对边(u,v)执行push操作。
        *
        * 因为结点u有一个正的超额流u.e，且边(u,v)的残余容量为正，因此可以增加结点u到v的流，增加的幅度为min(u.e,c_f(u,v))，这种幅度的增加不会导致
        * u.e为负值或者容量 c(u,v) 被突破
        *
        * push操作步骤：
        *
        * - 计算残余容量 c_f(u,v)
        * - 计算流的增加幅度 delt_f=min(u.e,c_f(u,v))
        * - 更新流：
        *   - 如果 (u,v) 属于 E，则 f(u,v) += delt_f
        *   - 如果 (v,u) 属于 E，则 f(v,u) -= delt_f
        *
        * - 更新溢出流量：
        *   - u.e -= delt(u,v)
        *   - v.e += delt(u,v)
        *
        * > - 由顶点的`key`属性存储超额流量e        *
        * > - 执行push(u,v)时，要求存在残留边 (u,v)属于Ef，且c_f(u,v)>0；否则抛出异常
        * > - 执行push(u,v)时，要求 u.e>0；否则抛出异常
        *
        */
        template<typename GraphType> void
        push (std::shared_ptr<GraphType> graph,typename GraphType::VIDType u_id,typename GraphType::VIDType v_id,
                  std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {
            typedef typename GraphType::EWeightType EWeightType;

            if(!graph)
                throw std::invalid_argument("push error: graph must not be nullptr!");
            if(u_id<0||u_id>=GraphType::NUM||v_id<0||v_id>=GraphType::NUM)
                throw std::invalid_argument("push error:id must >=0 and <N.");
            if(!graph->vertexes.at(u_id) || !graph->vertexes.at(v_id))
                throw std::invalid_argument("push error: vertex of id does not exist.");

            EWeightType c_f; //c_f(u,v)
            EWeightType delt_f;//delt_f(u,v)

            if(graph->vertexes[u_id]->key==0)
                throw std::invalid_argument("push error:u.e must >0 !");

            //***********  获取 c_f(u,v) ***********
            if(graph->has_edge(u_id,v_id)) //(u,v)属于E
                c_f=graph->weight(u_id,v_id)-flow[u_id][v_id]; // c_f(u,v)=c(u,v)-f(u,v)
            else if(graph->has_edge(v_id,u_id)) //(v,u)属于E
                c_f=flow[v_id][u_id]; //c_f(u,v)=f(v,u)
            else
                throw std::invalid_argument("push error: must be (u,v) in E or (v,u) in E!");

            if(c_f==0) throw std::invalid_argument("push error:must be c_f > 0!");

            //************ 获取 /delt_f(u,v) *********
            delt_f=std::min(graph->vertexes[u_id]->key,c_f);

            //************ 更新 flow *************
            if(graph->has_edge(u_id,v_id)) //(u,v)属于E
                flow[u_id][v_id]+=delt_f;
            else if(graph->has_edge(v_id,u_id)) //(v,u)属于E
                flow[v_id][u_id]-=delt_f;
            else
                throw std::invalid_argument("push error: must be (u,v) in E or (v,u) in E!");

            //************ 更新 e ***************
            graph->vertexes[u_id]->key -= delt_f;
            graph->vertexes[v_id]->key += delt_f;
        }


        //!min_v_at_Ef：relabel操作中的min_v_at_Ef操作。算法导论26章26.4节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param u_id: 结点u的id，必须有效否则抛出异常
        * \param flow: 预流
        * \return: 所有边(u,v)属于E_f(残留网络G_f中的边)中，高度最小的结点v
        *
        *
        * 该方法扫描Ef中所有从u出发的边(u,v)，找出高度最小的结点v
        *
        */
        template<typename GraphType> typename GraphType::VIDType min_v_at_Ef(std::shared_ptr<GraphType> graph,typename GraphType::VIDType u_id,
                                                     const std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef typename GraphType::VIDType VIDType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;

            if(!graph)
                throw std::invalid_argument("min_v_at_Ef error: graph must not be nullptr!");
            if(u_id<0||u_id>=GraphType::NUM)
                throw std::invalid_argument("min_v_at_Ef error:id must >=0 and <N.");
            if(!graph->vertexes.at(u_id))
                throw std::invalid_argument("min_v_at_Ef error: vertex of id does not exist.");

            std::vector<VIDType> Ef_v; // {v:(u,v)属于Ef}
            const MatrixType& matrix_graph=graph->matrix.matrix; //图的矩阵描述
            auto invalid_weight=graph->matrix.invalid_weight; //无效权重
            //*************  获取所有边(u,v)属于E_f(残留网络G_f中的边)的结点 v *************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto c_u_v=matrix_graph[u_id][i];
                if(c_u_v!=invalid_weight) //(u,v)属于E
                    if(flow[u_id][i]<c_u_v) // f(u,v)<c(u,v)
                        Ef_v.push_back(i);

                auto c_v_u=matrix_graph[i][u_id];
                if(c_v_u!=invalid_weight) //(v,u)属于E
                    if(flow[i][u_id]>0) // f(v,u)>0
                        Ef_v.push_back(i);
            }
            int min_h=unlimit<int>();
            VIDType v_id=-1;
            for(const auto& id:Ef_v)
                if(graph->vertexes[id]->h<min_h)
                {
                    min_h=graph->vertexes[id]->h;
                    v_id=id;
                }
            return v_id;
        }


        //!relabel：generic_push_relabel算法的relabel操作。算法导论26章26.4节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param u_id: 结点u的id，必须有效否则抛出异常
        * \param flow: 预流
        * \return: void
        *
        * 如果结点u溢出（如果不是溢出则抛出异常），并且对于所有边(u,v)属于E_f(残留网络G_f中的边)，有u.h<=v.h，则可以对结点u执行relabel操作。
        * 当调用relabel操作时，E_f必须包含至少一条从结点u出发的边，否则抛出异常。
        *
        * relabel 步骤：
        *
        * - 计算 min{v.h:(u,v)属于E_f}
        * - u.h=1+ min{v.h:(u,v)属于E_f}
        *
        * 当对于存在边(u,v)属于E_f(残留网络G_f中的边)，有u.h>v.h时，抛出异常
        */
        template<typename GraphType> void relabel(std::shared_ptr<GraphType> graph,typename GraphType::VIDType u_id,
                                                  const std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {

            if(!graph)
                throw std::invalid_argument("relabel error: graph must not be nullptr!");
            if(u_id<0||u_id>=GraphType::NUM)
                throw std::invalid_argument("relabel error:id must >=0 and <N.");
            if(!graph->vertexes.at(u_id))
                throw std::invalid_argument("relabel error: vertex of id does not exist.");

            if(graph->vertexes[u_id]->key==0)
                throw std::invalid_argument("relabel error:u.e must >0 !");

            auto min_v_id=min_v_at_Ef(graph,u_id,flow);
            if(min_v_id<0)
                throw std::invalid_argument("relabel error: there must be edges in E_f start from u !");
            if(graph->vertexes[u_id]->h> graph->vertexes[min_v_id]->h)
                throw std::invalid_argument("relabel error: u.h already > min_v.h !");

            graph->vertexes[u_id]->h=1+graph->vertexes[min_v_id]->h;
        }

        //!initialize_preflow：generic_push_relabel算法的初始化操作。算法导论26章26.4节
        /*!
        *
        * \param graph:指定流网络。它必须非空，否则抛出异常
        * \param src: 流的源点，必须有效否则抛出异常
        * \param flow: 预流的引用（执行过程中会更新预流）
        * \return: void
        *
        *  如果src无效，则抛出异常：
        *
        * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
        * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
        *
        * 初始化操作执行下列操作：
        *
        *   - 初始化预流 flow: flow(u,v)=c(u,v)如果u=s;否则 flow(u,v)=0
        *   - 初始化高度函数 h: h(s)=|V|;h(u)=0, u属于 V-{s}
        *   - 初始化超额流量 e： e(u)=c(s,u)，u为与源s相邻的结点; e(u)=0，u为与源s不相邻的结点; e(s)初始化为所有s出发的管道之后的相反数
        * > 由顶点的`key`属性存储超额流量e
        */
        template<typename GraphType> void initialize_preflow(std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,
                         std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>&flow)
        {
                if(!graph)
                    throw std::invalid_argument("initialize_preflow error: graph must not be nullptr!");
                if(src<0||src>=GraphType::NUM)
                    throw std::invalid_argument("initialize_preflow error:id must >=0 and <N.");
                if(!graph->vertexes.at(src))
                    throw std::invalid_argument("initialize_preflow error: vertex of id does not exist.");


                //*********** 所有结点的 e为0, h为0 ***********
                for(auto& v:graph->vertexes)
                {
                     v->h=0;
                     v->key=0;
                }
                //************* 所有预流为0  **************
                for(int i=0;i<GraphType::NUM;i++)
                    for(int j=0;j<GraphType::NUM;j++)
                        flow[i][j]=0;

                graph->vertexes[src]->h=GraphType::NUM; // h(s)= |V|
                //**************  对s出发的边调整  *************
                auto edges=graph->vertex_edge_tuples(src);
                for(const auto&edge:edges)
                {
                    auto v_id=std::get<1>(edge); //{v:(s,v)属于E}
                    auto c_s_v=std::get<2>(edge);// c(s,v)
                    flow[src][v_id]=c_s_v; //f(s,v)
                    graph->vertexes[v_id]->key=c_s_v; // v.e=c(s,v)
                    graph->vertexes[src]->key -=c_s_v; // s.e-=c(s,v)
                }
        }

        //!generic_push_relabel：最大流的推送-重贴标签算法。算法导论26章26.4节
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
        * ## generic_push_relabel 算法
        *
        * ### 算法原理
        *
        * 目前最大流的最快实现是基于推送-重贴标签算法。推送-重贴标签算法比 Ford-fulkserson的局域性更强。它不是对整个残余网络进行检查，
        * 而是一个结点一个结点的查看，每一步只检查当前结点的邻结点。与 Ford-fulkerson 方法不同，
        * 推送-重贴标签算法并不在整个执行过程中保持流量守恒性质，而是维持一个预流，该流是一个 V*V --> R的函数f,它满足容量限制单不满足流量守恒性质。
        * 进入一个点的流量可以超过流出该结点的流量，我们称结点u的 （进入流量-流出流量）=e(u)为结点u的超额流。
        * 对于结点u属于V-{s,t}，如果 e(u)>0，则称结点u溢出。
        *
        * 考虑一个流网络G=(V,E)，我们将有向边看作管道，连接管道的结点有两个性质：
        *
        * - 为了容纳额外的流e，每个结点都隐藏有一个外流的管道，该管道通向一个容量无穷大的水库
        * - 每个结点都有一个高度h，高度的值随着算法的推进而增加
        *
        * 高度h满足下面性质：h(s)=|V|,h(t)=0,对于所有的边(u,v)属于E_f（残余网络中的边），则有 h(u)<=h(v)+1
        *
        * 结点的高度h决定了流的推送方向：我们只从高处向低处push流。我们将源的高度固定在|V|，将汇点的高度固定在0。其他结点的高度初始时为0，
        * 但是随着时间的推移而不断增加。
        *
        * generic_push_relabel算法首先从源结点往下发送尽可能多的流到汇点，发送的流量为源结点所发出的所有管道的流量之和。
        * 当流进入一个中间结点时，他们被收集在该结点的水库中。
        *
        * 算法过程中，可能发现所有离开结点u的未充满的管道高度都比u大或者和u相等。此时为了消除结点u的超额流量，必须增加结点u的高度。
        * 这就是“重贴标签”操作，我们将结点u的高度增加到比其最低的邻居结点的高度多1个单位的高度，这里要求结点u到该邻居结点的管道必须未充满。
        * 因此在执行重贴标签后，一个结点u至少有一个流出管道。可以通过它推送更多的流。
        *
        * 最终一旦所有水库为空，则预流不但是“合法”的流，也是一个最大流。
        *
        * ### 基本操作
        *
        * #### push 操作
        *
        * 如果一个结点 u是一个溢出结点，则至少有一条入边，假设为(v,u)，且f(v,u)>0。此时残留网络G_f中的边c_f(u,v)>0。如果此时还有h(u)=h(v)+1，
        * 则可以对边(u,v)执行push操作。
        *
        * 因为结点u有一个正的超额流u.e，且边(u,v)的残余容量为正，因此可以增加结点u到v的流，增加的幅度为min(u.e,c_f(u,v))，这种幅度的增加不会导致
        * u.e为负值或者容量 c(u,v) 被突破
        *
        * push操作步骤：
        *
        * - 计算残余容量 c_f(u,v)
        * - 计算流的增加幅度 delt_f=min(u.e,c_f(u,v))
        * - 更新流：
        *   - 如果 (u,v) 属于 E，则 f(u,v) += delt_f
        *   - 如果 (v,u) 属于 E，则 f(v,u) -= delt_f
        *
        * - 更新溢出流量：
        *   - u.e -= delt(u,v)
        *   - v.e += delt(u,v)
        *
        * #### relabel 操作
        *
        * 如果结点u溢出，并且对于所有边(u,v)属于E_f(残留网络G_f中的边)，有u.h<=v.h，则可以对结点u执行relabel操作。
        * 当调用relabel操作时，E_f必须包含至少一条从结点u出发的边。
        *
        * relabel 步骤：
        *
        * - 计算 min{v.h:(u,v)属于E_f}
        * - u.h=1+ min{v.h:(u,v)属于E_f}
        *
        * ### 算法步骤
        *
        * - 初始化操作：
        *   - 初始化预流 flow: flow(u,v)=c(u,v)如果u=s;否则 flow(u,v)=0
        *   - 初始化高度函数 h: h(s)=|V|;h(u)=0, u属于 V-{s}
        *   - 初始化超额流量 e： e(u)=c(s,u)，u为与源s相邻的结点; e(u)=0，u为与源s不相邻的结点; e(s)初始化为所有s出发的管道之后的相反数
        *
        * - 执行循环，直到所有结点u属于V-{s,t}不存在超额流量e为止。循环内执行：
        *   - 如果可以执行 push 操作，则执行push操作
        *   - 如果不能执行 push 操作，又由于存在超额流量 e>0 的结点，因此必然可以执行 relabel 操作。则执行 relabel 操作
        *
        *
        * ### 算法性能
        *
        * 算法性能：时间复杂度 O(V^2 E)
        *
        *
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType,GraphType::NUM>,GraphType::NUM>
        generic_push_relabel(std::shared_ptr<GraphType> graph,typename GraphType::VIDType src,typename GraphType::VIDType dst)
        {
               typedef typename GraphType::EWeightType EWeightType;
               typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;
                if(!graph)
                    throw std::invalid_argument("generic_push_relabel error: graph must not be nullptr!");
                if(src<0||src>=GraphType::NUM||dst<0||dst>=GraphType::NUM)
                    throw std::invalid_argument("generic_push_relabel error:id must >=0 and <N.");
                if(!graph->vertexes.at(src) || !graph->vertexes.at(dst))
                    throw std::invalid_argument("generic_push_relabel error: vertex of id does not exist.");
               MatrixType flow;

               initialize_preflow(graph,src,flow);
               while(true)
               {
                  int u_index;
                  //*********** 寻找 溢出结点 ***********

                  bool has_no_overflow=true;
                  for(u_index=0;u_index<GraphType::NUM;u_index++)
                  {
                     if(u_index==src||u_index==dst) continue; //跳过源点和汇点
                     if(graph->vertexes[u_index]->key>0) //有溢出结点
                     {
                         has_no_overflow=false;
                         break;
                     }
                  }

                  if(has_no_overflow) break; //没有溢出结点
                  else //存在溢出结点
                  {
                      auto v_id=min_v_at_Ef(graph,u_index,flow);
                      if(graph->vertexes[u_index]->h > graph->vertexes[v_id]->h) //满足push条件
                      {
                          push(graph,u_index,v_id,flow);
                      }
                      else
                      {
                          relabel(graph,u_index,flow);
                      }
                  }

               }
               return flow;
        }
    }
}
#endif // GENERICPUSHRELABEL

