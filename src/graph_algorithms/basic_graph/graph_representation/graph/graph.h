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
#ifndef GRAPH
#define GRAPH
#include"../matrix_graph/matrixgraph.h"
#include"../adjlist_graph/adjlistgraph.h"
#include<array>
#include<memory>
#include<assert.h>
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        //!Graph：图，算法导论22章22.1节
        /*!
        * 图的矩阵主要包含四个数据：
        *
        * - `matrix`：图的矩阵表示，类型为`MatrixGraph<N>`
        * - `adjList`：图的邻接表表示，类型为`ADJListGraph<N>`
        * - `vertexes`：顶点集合，类型为`std::array<std::shared_ptr<VertexType>,N>`。它是一个`std::array`，其元素类型为指向顶点的强引用
        * - `next_empty_vertex`：顶点集合中，下一个为空的位置，类型为`std::size_t`。它用于添加顶点。

        * 图支持插入、修改顶点操作，插入、修改边操作（由图的矩阵以及图的邻接表来代理），以及返回边、返回权重（由图的矩阵以及图的邻接表来代理）。
        *
        */
        template<unsigned N,typename VType> struct Graph
        {
            typedef int VIDType;     /*!< 顶点编号的类型*/
            typedef int EWeightType; /*!< 权重的类型*/
            typedef std::tuple<VIDType,VIDType,EWeightType> EdgeTupleType; /*!< 边的三元素（顶点1编号，顶点2编号，权重)组成的元组*/
            typedef VType VertexType; /*!< 顶点的类型*/
            static const unsigned NUM=N; /*!< 顶点的最大容量*/

            //!显式构造函数，为图的矩阵指定`invalid_weight`
            /*!
            * \param  val:无效权重值
            */
            explicit Graph(EWeightType val):matrix(val),next_empty_vertex(0)
            {}
            //!默认构造函数
            Graph():next_empty_vertex(0){}

            //!add_vertex:添加一个顶点
            /*!
            * \param  key:顶点存放的数据
            * \return: 顶点的id
            *
            * 如果已经有了N个顶点，则图的顶点已满，则抛出`std::invalid_argument`异常.
            *
            * 在每一次添加顶点之前会从`next_empty_vertex·指定的位置处开始寻找可以添加顶点的地方。如果找不到可以添加顶点的地方，则抛出`std::invalid_argument`异常
            */
            VIDType add_vertex(const typename VertexType::KeyType& key)
            {
                while(next_empty_vertex<N&&vertexes.at(next_empty_vertex))
                    next_empty_vertex++;
                if(next_empty_vertex>=N)
                    throw std::invalid_argument("add_vertex error:Graph Vertex is full, can not add vertex.");
                VIDType v_id=next_empty_vertex;
                vertexes.at(next_empty_vertex)=std::make_shared<VertexType>(key,v_id);
                next_empty_vertex++;
                return v_id;
            }
            //!add_vertex:添加一个顶点
            /*!
            * \param  key:顶点存放的数据
            * \param id:指定该顶点的`id`
            * \return: 顶点的id
            *
            * - 如果`id<0`或者`id>=N`，则抛出异常。因为正常的顶点`id`在`[0,N)`之间
            * - 如果已经存在某个顶点的`id`为指定的`id`，则抛出异常
            */
            VIDType add_vertex(const typename VertexType::KeyType &key,VIDType id)
            {
                if(id<0||id>=N)
                    throw std::invalid_argument("add_vertex error:id must >=0 and <N.");
                if(vertexes.at(id))
                    throw std::invalid_argument("add_vertex error: vertex of id has existed.");
                vertexes.at(id)=std::make_shared<VertexType>(key,id);
                return id;
            }
            //!modify_vertex:修改一个顶点的数据
            /*!
            * \param  newkey:新的数据
            * \param id:指定该顶点的`id`
            *
            * - 如果`id<0`或者`id>=N`，则抛出异常。因为正常的顶点`id`在`[0,N)`之间
            * - 如果不存在某个顶点的`id`为指定的`id`，则抛出异常
            */
            void modify_vertex(const typename VertexType::KeyType &newkey,VIDType id)
            {
                if(id<0||id>=N)
                    throw std::invalid_argument("modify_vertex error:id must >=0 and <N.");
                if(!vertexes.at(id))
                    throw std::invalid_argument("modify_vertex error: vertex of id does not exist.");
                vertexes.at(id)->key=newkey;
            }

            //!add_edge:添加一条边
            /*!
            * \param  edge_tuple:一条边的三元素元组
            *
            * 为了便于计算，添加边时并不是添加`Edge`类型，而是`std::tuple<VIDType,VIDType,EWeightType>`类型的值。
            *
            * 添加边之前如果边指定的任何一个顶点无效，则抛出异常：
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
            *
            * 在添加边时，同时向图的矩阵、图的邻接表中添加边
            *
            * 如果添加的边是无效权重，则直接返回而不添加
            */
            void add_edge(const EdgeTupleType& edge_tuple)
            {
                auto id1=std::get<0>(edge_tuple);
                auto id2=std::get<1>(edge_tuple);

                if(id1<0||id1>=N||id2<0||id2>=N)
                    throw std::invalid_argument("add edge error:id must >=0 and <N.");
                if(!vertexes.at(id1) || !vertexes.at(id2))
                    throw std::invalid_argument("add edge error: vertex of id does not exist.");
                if(std::get<2>(edge_tuple)==matrix.invalid_weight) return;
                matrix.add_edge(edge_tuple);
                adjList.add_edge(edge_tuple);
            }
            //!add_edges:添加一组边
            /*!
            * \param  begin:边容器的起始迭代器
            * \param  end:边容器的终止迭代器
            *
            * 为了便于计算，添加边时并不是添加`Edge`类型，而是`std::tuple<VIDType,VIDType,EWeightType>`类型的值
            *
            * 在添加边时，同时向图的矩阵、图的邻接表中添加边
            */
            template<typename Iterator> void add_edges(const Iterator&begin ,const Iterator&end)
            {

                if(std::distance(begin,end)<=0)
                    return;
                Iterator iter=begin;
                while(iter!=end)
                {
                    add_edge(*iter);
                    iter++;
                }
            }
            //!adjust_edge:修改一条边的权重
            /*!
            * \param  id1:待修改边的第一个顶点
            * \param  id2:待修改边的第二个顶点
            * \param  wt:新的权重
            *
            * 修改边权重之前如果边指定的任何一个顶点无效，则抛出异常：
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
            */
            void adjust_edge(VIDType id1,VIDType id2,EWeightType wt)
            {
                if(id1<0||id1>=N||id2<0||id2>=N)
                    throw std::invalid_argument("adjust edge error:id must >=0 and <N.");
                if(!vertexes.at(id1) || !vertexes.at(id2))
                    throw std::invalid_argument("adjust edge error: vertex of id does not exist.");
                matrix.adjust_edge(id1,id2,wt);
                adjList.adjust_edge(id1,id2,wt);
            }
            //!edge_tuples:返回图中所有边的三元素元组集合，这里集合采用`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
            /*!
            * \return  :图中所有边的三元素元组集合
            *
            * 要求图的矩阵和图的邻接表都返回同样的结果
            */
            const std::vector<EdgeTupleType> edge_tuples() const
            {
                auto edges1=matrix.edge_tuples();
                auto edges2=adjList.edge_tuples();
                auto compare=[](const EdgeTupleType& e1,const EdgeTupleType&e2)->bool {
                    if(
                            (std::get<0>(e1) < std::get<0>(e2))||
                            ( (std::get<0>(e1) == std::get<0>(e2))&&(std::get<1>(e1) < std::get<1>(e2)) ) ||
                            ( (std::get<0>(e1) == std::get<0>(e2))&&(std::get<1>(e1) == std::get<1>(e2))&&(std::get<2>(e1) < std::get<2>(e2)) )
                        ) return true;
                   return false;
                };
                std::sort(edges1.begin(),edges1.end(),compare);
                std::sort(edges2.begin(),edges2.end(),compare);
                assert(edges1==edges2);
                return edges1;
            }

            //!vertex_edge_tuples:返回图中从指定顶点出发的边的三元素元组集合，这里集合采用`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
            /*!
            * \param id: 指定顶点`id`
            * \return  :图中指定顶点出发的边的三元素元组集合
            *
            * 要求图的矩阵和图的邻接表都返回同样的结果
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
            */
            const std::vector<EdgeTupleType> vertex_edge_tuples(VIDType id) const
            {
                if(id<0||id>=N)
                    throw std::invalid_argument("vertex_edge_tuples error:id must >=0 and <N.");
                if(!vertexes.at(id))
                    throw std::invalid_argument("vertex_edge_tuples error: vertex of id does not exist.");

                auto edges1=matrix.vertex_edge_tuples(id);
                auto edges2=adjList.vertex_edge_tuples(id);
                auto compare=[](const EdgeTupleType& e1,const EdgeTupleType&e2)->bool {
                    if(
                            (std::get<0>(e1) < std::get<0>(e2))||
                            ( (std::get<0>(e1) == std::get<0>(e2))&&(std::get<1>(e1) < std::get<1>(e2)) ) ||
                            ( (std::get<0>(e1) == std::get<0>(e2))&&(std::get<1>(e1) == std::get<1>(e2))&&(std::get<2>(e1) < std::get<2>(e2)) )
                        ) return true;
                   return false;
                };
                std::sort(edges1.begin(),edges1.end(),compare);
                std::sort(edges2.begin(),edges2.end(),compare);
                assert(edges1==edges2);
                return edges1;
            }

            //!has_edge:返回图中指定顶点之间是否存在边
            /*!
            * \param id_from: 第一个顶点的`id`
            * \param id_to: 第二个顶点的`id`
            * \return  :第一个顶点和第二个顶点之间是否存在边
            *
            * 要求图的矩阵和图的邻接表都返回同样的结果
            *
            *  如果边指定的任何一个顶点无效，则抛出异常：
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
            */
            bool has_edge(VIDType id_from,VIDType id_to) const
            {
                if(id_from<0||id_from>=N||id_to<0||id_to>=N)
                    throw std::invalid_argument("has edge error:id must >=0 and <N.");
                if(!vertexes.at(id_from) || !vertexes.at(id_to))
                    throw std::invalid_argument("has edge error: vertex of id does not exist.");
               auto m=matrix.has_edge(id_from,id_to);
               auto a=adjList.has_edge(id_from,id_to);
               assert(matrix.has_edge(id_from,id_to)==adjList.has_edge(id_from,id_to));
               return matrix.has_edge(id_from,id_to);
            }

            //!weight:返回图中指定顶点之间的边的权重
            /*!
            * \param id_from: 第一个顶点的`id`
            * \param id_to: 第二个顶点的`id`
            * \return  :第一个顶点和第二个顶点之间的边的权重
            *
            * 要求图的矩阵和图的邻接表都返回同样的结果
            *
            *  如果边指定的任何一个顶点无效，则抛出异常：
            *
            * - 如果指定的顶点`id`不在`[0,N)`之间，则无效
            * - 如果不存在某个顶点与指定的顶点`id`相同，则无效
            */
            EWeightType weight(VIDType id_from,VIDType id_to) const
            {
                if(id_from<0||id_from>=N||id_to<0||id_to>=N)
                    throw std::invalid_argument("edge weight error:id must >=0 and <N.");
                if(!vertexes.at(id_from) || !vertexes.at(id_to))
                    throw std::invalid_argument("edge weight error: vertex of id does not exist.");
                assert(matrix.weight(id_from,id_to)==adjList.weight(id_from,id_to));
                return matrix.weight(id_from,id_to);
            }

            //!inverse:返回图的一个镜像
            /*!
            * \return  :图的一个镜像的一个强引用
            *
            * 图的一个镜像也是一个图，它与原图有以下关系：
            *
            * - 图的镜像的顶点与原图的顶点相同
            * - 图的镜像的边是原图的边的反向
            *
            * `inverse`方法首先新建一个图，再根据原图的顶点来执行顶点的深拷贝。然后再获取原图的边的反向边，将该反向边作为镜像图的边
            */
            std::shared_ptr<Graph> inverse()
            {
                std::shared_ptr<Graph> graph=std::make_shared<Graph>(matrix.invalid_weight);
                for(int i=0;i<vertexes.size();i++)
                {
                    if(vertexes.at(i))
                    {
                        graph->vertexes.at(i)=std::make_shared<VertexType>(vertexes.at(i)->key,vertexes.at(i)->id);
                    }
                }
                auto edges=edge_tuples();
                for(auto&edge :edges)
                    std::swap(std::get<0>(edge),std::get<1>(edge));
                graph->add_edges(edges.begin(),edges.end());
                return graph;
            }

            std::array<std::shared_ptr<VertexType>,N> vertexes;
            std::size_t next_empty_vertex;
            MatrixGraph<N> matrix;
            ADJListGraph<N> adjList;
        };
    }
}


#endif // GRAPH

