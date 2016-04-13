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
#ifndef PRIM_TEST
#define PRIM_TEST
#include"src/google_test/gtest.h"
#include"prim.h"
#include"../../basic_graph/graph_representation/graph_vertex/vertexp.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::prim;
using IntroductionToAlgorithm::GraphAlgorithm::VertexP;

namespace {
    const int PRIM_N= 10;  /*!< 测试的图顶点数量*/
}

//!PrimTest:测试类，用于为测试提供基础数据
/*!
*
* `PrimTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class PrimTest:public ::testing::Test
{
public:
typedef Graph<PRIM_N,VertexP<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`VertexP<int>`*/
typedef std::function<void(VertexP<int>::VIDType v_id)> ActionType;/*!< 模板实例化的Action类型*/
protected:
    void SetUp()
    {
        _1v_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1v_graph->add_vertex(0);  //该图只有一个顶点

        _1e_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1e_graph->add_vertex(0);
        _1e_graph->add_vertex(0);
        _1e_graph->add_edge(std::make_tuple(0,1,1));  //该图只有一条边


        //****  含顶点图和边图：10个顶点，9条边   ****
        _list_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<PRIM_N;i++)
            _list_graph->add_vertex(0);
        for(int i=0;i<PRIM_N-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,i+1)); //该图的边是从左到右组成一个链条

        //****  含顶点图和边图：10个顶点，90条边   ****
        _all_edges_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<PRIM_N;i++)
            _all_edges_graph->add_vertex(0);
        for(int i=0;i<PRIM_N;i++)
            for(int j=0;j<PRIM_N;j++)
                if(i==j) continue;
                else _all_edges_graph->add_edge(std::make_tuple(i,j,i+j)); //该图中任意一对顶点之间都有边
    }
    void TearDown(){}
    std::shared_ptr<GType> _1v_graph;     /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GType> _1e_graph;     /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GType> _list_graph;   /*!< 指向一个图，该图的边组成一个链条*/
    std::shared_ptr<GType> _all_edges_graph;    /*!< 指向一个图，该图中任意一对顶点之间都有边*/
};
//!PrimTest:测试最小生成树的prim方法
/*!
* `test_prim`:测试最小生成树的prim方法
*/
TEST_F(PrimTest,test_prim)
{
    //************* 单点图 **************
    {
        std::vector<GType::VIDType> ids;
        ActionType pre_action=[&ids](GType::VIDType id){ids.push_back(id);};
        EXPECT_THROW(prim(_1v_graph,1,pre_action),std::invalid_argument);
        EXPECT_EQ(prim(_1v_graph,0,pre_action),0);
        EXPECT_EQ(ids.size(),1);
        EXPECT_EQ(ids.at(0),0);
    }
    //************** 单边图 ******************
    {
        std::vector<GType::VIDType> ids;
        ActionType pre_action=[&ids](GType::VIDType id){ids.push_back(id);};
        EXPECT_EQ(prim(_1e_graph,0,pre_action),1);
        EXPECT_EQ(ids,std::vector<GType::VIDType>({0,1}));
    }
    //************** 单链图 ******************
    {
        std::vector<GType::VIDType> ids;
        ActionType pre_action=[&ids](GType::VIDType id){ids.push_back(id);};
        EXPECT_EQ(prim(_list_graph,0,pre_action),(PRIM_N-1)*PRIM_N/2);
        std::vector<GType::VIDType> result_ids;
        for(int i=0;i<PRIM_N;i++)
        {
           result_ids.push_back(i);
           if(i==0) continue;
                EXPECT_EQ(_list_graph->vertexes.at(i)->parent,_list_graph->vertexes.at(i-1));
        }
        EXPECT_EQ(ids,result_ids);
    }
    //***************** 任意一对顶点之间都有边的图  **************
    {
        //边(u,v)的权重为(u.id+v.id)，因此最小生成树是一个星形状，中心点为id=0的源点
        std::vector<GType::VIDType> ids;
        ActionType pre_action=[&ids](GType::VIDType id){ids.push_back(id);};
        EXPECT_EQ(prim(_all_edges_graph,0,pre_action),(PRIM_N-1)*PRIM_N/2);
        std::vector<GType::VIDType> result_ids;
        for(int i=0;i<PRIM_N;i++)
        {
           result_ids.push_back(i);
           if(i==0) continue;
                EXPECT_EQ(_all_edges_graph->vertexes.at(i)->parent,_all_edges_graph->vertexes.at(0))<<"i:"<<i;
        }
        EXPECT_EQ(ids,result_ids);
    }
}

#endif // PRIM_TEST

