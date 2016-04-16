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
#ifndef JOHNSON
#define JOHNSON
#include<memory>
#include"src/header.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
#include"../../single_source_shortest_path/bellman_ford/bellmanford.h"
#include"../../single_source_shortest_path/dijkstra/dijkstra.h"

namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!graph_plus_1v：根据图graph生成一个新图。算法导论25章25.2节
        /*!
        *
        * \param graph:指定的有向图。它必须非空，否则抛出异常
        * \return: 一个新图
        *
        * 根据图graph生成一个新图new_graph。new_graph的顶点 graph的顶点加上一个新顶点s；
        * new_graph的边为graph的边加上{(s,v):v属于graph的顶点};
        * new_graph的边的权重为graph的边权重，以及 w(s,v)=0
        * >注意：设原图有N个顶点，则新图有N+1个顶点
        *
        * 本函数是 johnson 算法的辅助函数
        */
        template<typename GraphType> std::shared_ptr<Graph<GraphType::NUM+1,typename GraphType::VertexType>>
            graph_plus_1v(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename VertexType::VIDType VIDType;
            typedef typename GraphType::EWeightType EWeightType;
            typedef Graph<GraphType::NUM+1,VertexType> NewGrapyType; //新的图类型
            typedef typename  GraphType::EdgeTupleType EdgeTupleType;


            if(!graph)
                throw std::invalid_argument("graph_plus_1v error: graph must not be nullptr!");

            std::shared_ptr<NewGrapyType> new_graph=std::make_shared<NewGrapyType>(graph->matrix.invalid_weight);
            //*************  创建新图的顶点  ******************
            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex)
                    new_graph->add_vertex(vertex->key,vertex->id);
            }
            new_graph->add_vertex(0,GraphType::NUM); //新的顶点s，id为N

            //**********   创建新图的边  ***********************
            std::vector<EdgeTupleType> source_edges=graph->edge_tuples();
            for(int i=0;i<GraphType::NUM;i++) // 边 (s,v)
            {
                source_edges.push_back(std::make_tuple((VIDType)GraphType::NUM,(VIDType)i,(EWeightType) 0));
            }
            new_graph->add_edges(source_edges.begin(),source_edges.end());
            return new_graph;
        }

        //!johnson：返回所有节点对的最短路径的johnson算法。算法导论25章25.3节
        /*!
        *
        * \param graph:指定的有向图。它必须非空，否则抛出异常
        * \return: 一个n*n的矩阵(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重
        *
        * ## 所有结点对的最短路径
        *
        * 给定一个带权重的有向图G=(V,E)，其权重函数为w:E->R，该函数将边映射到实值权重上。我们希望找到对于所有的结点对u,v属于V，找出一条从结点u
        * 到结点v的最短路径，以及这条路径的权重。
        *
        * 与单源最短路径不同中使用邻接表来表示图不同，本章的多数算法使用邻接矩阵来表示图。该矩阵代表的是一个有n个结点的有向图G=(V,E)的边的权重W=(w_i_j)，
        * 其中 w_i_j =:
        *
        *   - 0:若i=j
        *   - 有向边(i,j)的权重，若i!=j且(i,j)属于E
        *   - 正无穷，若 i!=j且(i,j)不属于E
        *
        * 我们允许存在负权重的边，目前仍然假定图中不存在权重为负值的环路。
        *
        * 本章讨论的所有结点对最短路径的算法的输出也是一个n*n的矩阵D=(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重。
        *
        * 有时候为了解决所有结点对最短路径问题，我们不仅要计算出最短路径权重，还需要计算出前驱结点矩阵 II=(pai_i_j)，其中 pai_i_j在i=j或者从i到j
        * 不存在路径时为NIL，在其他情况下给出的是从结点i到结点j的某条最短路径上结点j的前驱结点。由矩阵II的第i行所诱导的子图应当是一棵根节点为i
        * 的最短路径树。
        *
        * ## Johnson算法
        *
        * ### 算法原理
        *
        * 对于稀疏图来说Johnson算法的渐近表现要优于重复平方法和Floyd-Warshall算法。Johnson算法要么返回一个包含所有结点对的最短路径权重的矩阵，
        * 要么报告输入图中包含一个权重为负值的环路。Johnson算法在运行中需要使用Dijkstra算法和Bellman-Ford算法作为自己的子程序。
        *
        * Johnson算法使用一种称为重赋权重的技术。若图G=(V,E)中所有边权重w都为非负值，则可以通过对每一对顶点运行一次Dijkstra
        * 算法来找到所有顶点对直接的最短路径。如果图G包含负权重的边，但没有权重为负值的环路，则需要计算出一组新的非负权重值，然后用同样的方法。
        * 新赋的权重w'要求满足一下性质：
        *
        * - 对于所有结点对u,v属于V，一条路径p实在使用权重函数w时从u到v的一条最短路径，当且仅当p实在使用权重函数w'
        * 时从u到v的一条最短路径
        * - 对于所有的边(u,v)，新权重w'(u,v)非负
        *
        * 对于给定的有向图G=(V,E)，权重函数w：E->R 。我们制作一副新图G'=(V',E')，其中V'=V并上{s}，s是一个新结点，s不属于V。
        * E'=E并上{(s,v);v属于V}。我们对权重函数w进行扩展，使得对于所有结点v属于V，有w(s,v)=0。
        * 对所有的结点v属于V'，我们定义h(v)=delt(s,v)。定义w'(u,v)=w(u,v)+h(u)-h(v)
        *
        * ### 算法步骤
        *
        * - 重赋权重：
        *   - 创建新图 new_graph
        *   - 对新图执行 bellman_ford 的调用，源点为新创建的结点s
        *   - 如果有负权值的环路，则抛出异常。
        *   - 如果没有负权重环路，则创建h函数，并对new_graph中的所有边执行重新赋权
        * - 在 new_graph上，除了新的顶点s之外的所有顶点v,以v为源顶点执行dijkstra过程。D[i][j]等于 new_graph 中以i为源点到j的最短路径的权重的修正值，
        * 修正的方法就是重新赋权的逆过程。
        * - 返回矩阵 D
        *
        * ###算法性能
        *
        *  时间复杂度 O（V^2 lgV + VE)
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType ,GraphType::NUM>,GraphType::NUM>
        johnson(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef typename GraphType::VertexType VertexType;
            typedef Graph<GraphType::NUM+1,VertexType> NewGrapyType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;

            if(!graph)
                throw std::invalid_argument("johnson error: graph must not be nullptr!");

            //*******************  重赋权值  **************
            auto new_graph=graph_plus_1v(graph);  //新的图
            if(!bellman_ford(new_graph,GraphType::NUM)) //新顶点s的id为 GraphType::NUM
                throw std::invalid_argument("johnson error: graph must not contain minus circle!");
            int H[NewGrapyType::NUM]; //创建h函数， h(v)=delt(s,v)
            for(int i=0;i<GraphType::NUM;i++)
            {
                H[i]=new_graph->vertexes.at(i)->key;
            }
            for(int i=0;i<NewGrapyType::NUM;i++) //重新赋权值
                for(int j=0;j<NewGrapyType::NUM;j++)
                    if(new_graph->has_edge(i,j))  //只有边存在的情况下才调整
                        new_graph->adjust_edge(i,j,new_graph->weight(i,j)+H[i]-H[j]);


            //******************  在新图上以每个顶点为源点，计算单源最短路径  *********
            MatrixType D;
            for(int i=0;i<GraphType::NUM;i++) //剔除新顶点s作为源点
            {
                dijkstra(new_graph,i);
                for(int j=0;j<GraphType::NUM;j++)
                {
                    D[i][j]=new_graph->vertexes.at(j)->key+H[j]-H[i];// 恢复权值
                }
            }
            return D;
        }

    }
}
#endif // JOHNSON

