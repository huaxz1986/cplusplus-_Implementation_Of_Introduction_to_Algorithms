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
#ifndef KRUSKAL_TEST
#define KRUSKAL_TEST
#include"src/google_test/gtest.h"
#include"kruskal.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
#include"src/graph_algorithms/basic_graph/graph_representation/graph_vertex/set_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::kruskal;
using IntroductionToAlgorithm::SetAlgorithm::DisjointSetNode;
using IntroductionToAlgorithm::GraphAlgorithm::SetVertex;
namespace{
    const int K_NUM=10;  /*!< 图顶点数量*/
}

//!KruskalTest:测试类，用于为测试提供基础数据
/*!
*
* `KruskalTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class KruskalTest:public ::testing::Test
{
public:
    typedef Graph<K_NUM,SetVertex<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`SetVertex<int>`*/
    typedef std::function<void(SetVertex<int>::VIDType ,SetVertex<int>::VIDType)> ActionType;/*!< 模板实例化的Action类型*/
protected:
    void SetUp()
    {
        _1v_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1v_graph->add_vertex(0);  //该图只有一个顶点
        _1v_graph->add_edge(std::make_tuple(0,0,1));//该图只有一个顶点，必须有一条边指向自己

        _1e_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1e_graph->add_vertex(0);
        _1e_graph->add_vertex(0);
        _1e_graph->add_edge(std::make_tuple(0,1,1));  //该图只有一条边


        //****  含顶点图和边图：10个顶点，9条边   ****
        _list_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<K_NUM;i++)
            _list_graph->add_vertex(0);
        for(int i=0;i<K_NUM-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,i+1)); //该图的边是从左到右组成一个链条

        //****  含顶点图和边图：10个顶点，90条边   ****
        _all_edges_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<K_NUM;i++)
            _all_edges_graph->add_vertex(0);
        for(int i=0;i<K_NUM;i++)
            for(int j=0;j<K_NUM;j++)
                if(i==j) continue;
                else _all_edges_graph->add_edge(std::make_tuple(i,j,i+j)); //该图中任意一对顶点之间都有边
    }
    void TearDown(){}
    std::shared_ptr<GType> _1v_graph;     /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GType> _1e_graph;     /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GType> _list_graph;   /*!< 指向一个图，该图的边组成一个链条*/
    std::shared_ptr<GType> _all_edges_graph;    /*!< 指向一个图，该图中任意一对顶点之间都有边*/
};

//!KruskalTest:测试最小生成树的kruskal方法
/*!
* `test_kruskal`:测试最小生成树的kruskal方法
*/
TEST_F(KruskalTest,test_kruskal)
{
    typedef  std::pair<GType::VIDType,GType::VIDType> PairType;
    //************* 单点图 **************
    {
        std::vector<PairType> edges;
        ActionType pre_action=[&edges](GType::VIDType id1,GType::VIDType id2){edges.push_back(std::make_pair(id1,id2));};
        EXPECT_EQ(kruskal(_1v_graph,pre_action),0);
        EXPECT_EQ(edges,std::vector<PairType>({}));
    }
    //************** 单边图 ******************
    {
        std::vector<PairType> edges;
        ActionType pre_action=[&edges](GType::VIDType id1,GType::VIDType id2){edges.push_back(std::make_pair(id1,id2));};
        EXPECT_EQ(kruskal(_1e_graph,pre_action),1);
        EXPECT_EQ(edges,std::vector<PairType>({std::make_pair(0,1)}));

        auto node0=_1e_graph->vertexes.at(0)->node;
        auto node1=_1e_graph->vertexes.at(1)->node;
        ASSERT_TRUE(node0&&node0->parent);
        ASSERT_TRUE(node1&&node1->parent);
        EXPECT_EQ(node0->parent,node1); //tree_root:u, tree_root:v, rank小的挂在rank大的之下；若二者rank相等，则u挂在v下
        EXPECT_EQ(node1->parent,node1); //所以结点1是最终根结点
    }
    //************** 单链图 ******************
    {
        std::vector<PairType> edges;
        ActionType pre_action=[&edges](GType::VIDType id1,GType::VIDType id2){edges.push_back(std::make_pair(id1,id2));};
        EXPECT_EQ(kruskal(_list_graph,pre_action),(K_NUM-1)*K_NUM/2);
        std::vector<PairType> result_edges;
        for(int i=1;i<K_NUM;i++)
            result_edges.push_back(std::make_pair(i-1,i));

        for(int i=0;i<K_NUM;i++) //tree_root:u, tree_root:v, rank小的挂在rank大的之下；若二者rank相等，则u挂在v下
            EXPECT_EQ(_list_graph->vertexes.at(i)->node->parent,_list_graph->vertexes.at(1)->node);//所以结点1是最终根结点

        //检验添加边的数量和顺序
        EXPECT_EQ(edges.size(),result_edges.size());
        for(int i=0;i<edges.size();i++)
            EXPECT_TRUE((edges[i].first==result_edges[i].first && edges[i].second==result_edges[i].second)||\
                        (edges[i].first==result_edges[i].second && edges[i].second==result_edges[i].first));
    }
    //***************** 任意一对顶点之间都有边的图  **************
    {
        //边(u,v)的权重为(u.id+v.id)
        std::vector<PairType> edges;
        ActionType pre_action=[&edges](GType::VIDType id1,GType::VIDType id2){edges.push_back(std::make_pair(id1,id2));};
        EXPECT_EQ(kruskal(_all_edges_graph,pre_action),(K_NUM-1)*K_NUM/2);
        std::vector<PairType> result_edges;
        for(int i=1;i<K_NUM;i++)
            result_edges.push_back(std::make_pair(0,i));

        for(int i=0;i<K_NUM;i++) //tree_root:u, tree_root:v, rank小的挂在rank大的之下；若二者rank相等，则u挂在v下
            EXPECT_EQ(_all_edges_graph->vertexes.at(i)->node->parent,_all_edges_graph->vertexes.at(1)->node);//所以结点1是最终根结点

        //检验添加边的数量和顺序
        EXPECT_EQ(edges.size(),result_edges.size());
        for(int i=0;i<edges.size();i++)
            EXPECT_TRUE((edges[i].first==result_edges[i].first && edges[i].second==result_edges[i].second)||\
                        (edges[i].first==result_edges[i].second && edges[i].second==result_edges[i].first));
    }
}
#endif // KRUSKAL_TEST

