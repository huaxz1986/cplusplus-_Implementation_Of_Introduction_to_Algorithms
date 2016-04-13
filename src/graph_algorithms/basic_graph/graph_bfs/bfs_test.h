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
#ifndef BFS_TEST
#define BFS_TEST
#include"src/google_test/gtest.h"
#include"bfs.h"
#include"../graph_representation/graph/graph.h"
#include"../graph_representation/graph_vertex/bfs_vertex.h"
namespace  {
    const int BFS_N= 10;  /*!< 测试的图顶点数量*/
}


using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::breadth_first_search;
using IntroductionToAlgorithm::GraphAlgorithm::get_path;
using IntroductionToAlgorithm::GraphAlgorithm::BFS_Vertex;


//!BFSTest:测试类，用于为测试提供基础数据
/*!
*
* `BFSTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class BFSTest:public ::testing::Test
{
public:
typedef Graph<BFS_N,BFS_Vertex<int>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`BFS_Vertex<int>`*/
typedef std::function<void(BFS_Vertex<int>::VIDType v_id)> ActionType;/*!< 模板实例化的Action类型*/
protected:
    void SetUp(){
        _1v_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1v_graph->add_vertex(0);  //该图只有一个顶点

        _1e_graph=std::make_shared<GType>(-1);//边的无效权重为-1
        _1e_graph->add_vertex(0);
        _1e_graph->add_vertex(0);
        _1e_graph->add_edge(std::make_tuple(0,1,1));  //该图只有一条边


        //****  含顶点图和边图：10个顶点，9条边   ****
        _list_graph=std::make_shared<GType>(-1); //边的无效权重为-1
        for(int i=0;i<BFS_N;i++)
            _list_graph->add_vertex(i);
        for(int i=0;i<BFS_N-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,10+i)); //该图的边是从左到右组成一个链条
    }
    void TearDown(){}
    std::shared_ptr<GType> _1v_graph;    /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GType> _1e_graph;    /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GType> _list_graph;    /*!< 指向一个图，该图的边组成一个链条*/
};
//!test_bfs:测试breadth_first_search方法
/*!
*
* 测试`breadth_first_search`方法
*/
TEST_F(BFSTest,test_bfs)
{
    {
        std::ostringstream os;
        ActionType print_bfs=[&os](BFS_Vertex<int>::VIDType v_id){os<<v_id<<",";};
        //****** 测试只有一个顶点的图**********
        EXPECT_THROW(breadth_first_search(_1v_graph,1,print_bfs),std::invalid_argument);
        breadth_first_search(_1v_graph,0,print_bfs);
        EXPECT_EQ(os.str(),"0,");
        EXPECT_EQ(_1v_graph->vertexes.at(0)->key,0);
    }
    {
        std::ostringstream os;
        ActionType print_bfs=[&os](BFS_Vertex<double>::VIDType v_id){os<<v_id<<",";};
        //***** 测试只有一条边的图*********
        breadth_first_search(_1e_graph,0,print_bfs);
        EXPECT_EQ(os.str(),"0,1,");
        EXPECT_EQ(_1e_graph->vertexes.at(0)->key,0);
        EXPECT_EQ(_1e_graph->vertexes.at(1)->key,1);
    }
    {
        std::ostringstream os;
        ActionType print_bfs=[&os](BFS_Vertex<double>::VIDType v_id){os<<v_id<<",";};
        //**** 测试链边的图**********
        std::string real_str;
        char char_from_int[2];
        for(int i=0;i<BFS_N;i++)
        {
            itoa(i,char_from_int,10);
            real_str+=std::string(char_from_int)+",";
        }
        breadth_first_search(_list_graph,0,print_bfs);
        EXPECT_EQ(os.str(),real_str);
        for(int i=0;i<BFS_N;i++)
        {
            EXPECT_EQ(_list_graph->vertexes.at(i)->key,i);
        }
    }
}

//!test_get_path:测试get_path方法
/*!
*
* 测试`get_path`方法
*/
TEST_F(BFSTest,test_get_path)
{
    std::ostringstream os;
    ActionType print_bfs=[&os](BFS_Vertex<double>::VIDType v_id){os<<v_id<<",";};
    //****** 测试只有一个顶点的图**********
    EXPECT_EQ(get_path(_1v_graph->vertexes.at(0),_1v_graph->vertexes.at(0)).size(),1);
    EXPECT_THROW(get_path(_1v_graph->vertexes.at(0),_1v_graph->vertexes.at(1)),std::invalid_argument);
    //***** 测试只有一条边的图*********
   _1e_graph->vertexes.at(1)->set_found(_1e_graph->vertexes.at(0));
   EXPECT_EQ(get_path(_1e_graph->vertexes.at(0),_1e_graph->vertexes.at(1)),std::vector<int>({0,1}));

   //**** 测试链边的图**********
   breadth_first_search(_list_graph,0,print_bfs);
   for(int i=0;i<BFS_N;i++)
   {
        std::vector<int> real;
       for(int j=i;j<BFS_N;j++)
           real.push_back(j);
       EXPECT_EQ(get_path(_list_graph->vertexes.at(i),_list_graph->vertexes.at(BFS_N-1)),real)<<"i:"<<i;
   }
}
#endif // BFS_TEST

