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
#ifndef DFS_TEST
#define DFS_TEST
#include"src/google_test/gtest.h"
#include"dfs.h"
#include"src/header.h"
#include"../graph_representation/graph/graph.h"
#include"../graph_representation/graph_vertex/dfs_vertex.h"
namespace  {
    const int DFS_N= 10;  /*!< 测试的图顶点数量*/
}


using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::DFS_Vertex;
using IntroductionToAlgorithm::GraphAlgorithm::depth_first_search;



//!DFSTest:测试类，用于为测试提供基础数据
/*!
*
* `DFSTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class DFSTest:public ::testing::Test
{
public:
typedef Graph<DFS_N,DFS_Vertex<double>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`DFS_Vertex<double>`*/
typedef std::function<void(DFS_Vertex<double>::VIDType v_id,int time)> ActionType;/*!< 模板实例化的Action类型*/
protected:
    void SetUp()
    {
        _1v_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1v_graph->add_vertex(1.0);  //该图只有一个顶点

        _1e_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1e_graph->add_vertex(2.0);
        _1e_graph->add_vertex(2.1);
        _1e_graph->add_edge(std::make_tuple(0,1,1));  //该图只有一条边


        //****  含顶点图和边图：10个顶点，9条边   ****
        _list_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<DFS_N;i++)
            _list_graph->add_vertex(1+i/DFS_N);
        for(int i=0;i<DFS_N-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,10+i)); //该图的边是从左到右组成一个链条

        //****  含顶点图和边图：10个顶点，9条边   ****
        _rlist_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<DFS_N;i++)
            _rlist_graph->add_vertex(1+i/DFS_N);
        for(int i=0;i<DFS_N-1;i++)
                _rlist_graph->add_edge(std::make_tuple(i,i+1,10+i)); //该图的边是从左到右组成一个链条
    }
    void TearDown(){}
    std::shared_ptr<GType> _1v_graph;    /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GType> _1e_graph;    /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GType> _list_graph;    /*!< 指向一个图，该图的边组成一个链条，该图用顺序搜索*/
    std::shared_ptr<GType> _rlist_graph;    /*!< 指向一个图，该图的边组成一个链条，该图用逆序搜索*/
};
//!test_dfs:测试depth_first_search方法
/*!
*
* 测试`depth_first_search`方法
*/
TEST_F(DFSTest,test_dfs)
{
    {
        std::ostringstream discover_os;
        std::ostringstream finished_os;
        ActionType print_discover=[&discover_os](DFS_Vertex<double>::VIDType v_id,int time){discover_os<<v_id<<",";};
        ActionType print_finished=[&finished_os](DFS_Vertex<double>::VIDType v_id,int time){finished_os<<v_id<<",";};
        //****** 测试只有一个顶点的图**********

        depth_first_search(_1v_graph,print_discover,print_finished);
        EXPECT_EQ(discover_os.str(),"0,");
        EXPECT_EQ(finished_os.str(),"0,");
    }
    {
        std::ostringstream discover_os;
        std::ostringstream finished_os;
        ActionType print_discover=[&discover_os](DFS_Vertex<double>::VIDType v_id,int time){discover_os<<v_id<<",";};
        ActionType print_finished=[&finished_os](DFS_Vertex<double>::VIDType v_id,int time){finished_os<<v_id<<",";};
        //****** 测试只有一条边的图**********
        depth_first_search(_1e_graph,print_discover,print_finished);
        EXPECT_EQ(discover_os.str(),"0,1,");
        EXPECT_EQ(finished_os.str(),"1,0,");
    }
    {
        std::ostringstream discover_os;
        std::ostringstream finished_os;
        ActionType print_discover=[&discover_os](DFS_Vertex<double>::VIDType v_id,int time){discover_os<<v_id<<",";};
        ActionType print_finished=[&finished_os](DFS_Vertex<double>::VIDType v_id,int time){finished_os<<v_id<<",";};
        //****** 测试测试链边的图**********
        std::string real_discover_str,real_finish_str;
        char char_from_int[2];
        for(int i=0;i<DFS_N;i++)
        {
            itoa(i,char_from_int,10);
            real_discover_str+=std::string(char_from_int)+",";
            itoa(DFS_N-i-1,char_from_int,10);
            real_finish_str+=std::string(char_from_int)+",";
        }
        depth_first_search(_list_graph,print_discover,print_finished);
        EXPECT_EQ(discover_os.str(),real_discover_str);
        EXPECT_EQ(finished_os.str(),real_finish_str);
    }
    {
        ActionType empty_action=[](DFS_Vertex<double>::VIDType v_id,int time){};
        std::ostringstream discover_os;
        std::ostringstream finished_os;
        ActionType print_discover=[&discover_os](DFS_Vertex<double>::VIDType v_id,int time){discover_os<<v_id<<",";};
        ActionType print_finished=[&finished_os](DFS_Vertex<double>::VIDType v_id,int time){finished_os<<v_id<<",";};
        //****** 测试测试链边的图，逆序**********

        std::string real_discover_str,real_finish_str;
        std::vector<DFS_Vertex<double>::VIDType> search_order;
        char char_from_int[2];
        for(int i=DFS_N-1;i>=0;i--)
        {
            search_order.push_back(i);
            itoa(i,char_from_int,10);
            real_discover_str+=std::string(char_from_int)+",";
            real_finish_str+=std::string(char_from_int)+",";
        }
        depth_first_search(_rlist_graph,print_discover,print_finished,empty_action,empty_action,search_order);
        EXPECT_EQ(discover_os.str(),real_discover_str);
        EXPECT_EQ(finished_os.str(),real_finish_str);
    }
}

//!test_get_path:测试get_path方法
/*!
*
* 测试`get_path`方法
*/
TEST_F(DFSTest,test_get_path)
{

    std::ostringstream discover_os;
    std::ostringstream finished_os;
    ActionType print_discover=[&discover_os](DFS_Vertex<double>::VIDType v_id,int time){discover_os<<v_id<<",";};
    ActionType print_finished=[&finished_os](DFS_Vertex<double>::VIDType v_id,int time){finished_os<<v_id<<",";};
   //**** 测试链边的图**********
   depth_first_search(_list_graph,print_discover,print_finished);
   for(int i=0;i<DFS_N;i++)
   {
       std::vector<int> real;
       for(int j=i;j<DFS_N;j++)
           real.push_back(j);
       EXPECT_EQ(get_path(_list_graph->vertexes.at(i),_list_graph->vertexes.at(DFS_N-1)),real)<<"i:"<<i;
   }
}

#endif //DFS_TEST
