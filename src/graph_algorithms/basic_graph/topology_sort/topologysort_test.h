#ifndef TOPOLOGYSORT_TEST
#define TOPOLOGYSORT_TEST
#include"src/google_test/gtest.h"
#include"topologysort.h"

using IntroductionToAlgorithm::GraphAlgorithm::Graph;
using IntroductionToAlgorithm::GraphAlgorithm::DFS_Vertex;
using IntroductionToAlgorithm::GraphAlgorithm::topology_sort;

const int TPS_N= 10;  /*!< 测试的图顶点数量*/

//!TopologySortTest:测试类，用于为测试提供基础数据
/*!
*
* `TopologySortTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class TopologySortTest:public ::testing::Test
{
public:
typedef Graph<TPS_N,DFS_Vertex<double>> GType; /*!< 模板实例化的图类型，该图的顶点类型为`DFS_Vertex<double>`*/

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
        for(int i=0;i<BFS_N;i++)
            _list_graph->add_vertex(1+i/BFS_N);
        for(int i=0;i<BFS_N-1;i++)
                _list_graph->add_edge(std::make_tuple(i,i+1,10+i)); //该图的边是从左到右组成一个链条
    }
    void TearDown(){}
    std::shared_ptr<GType> _1v_graph;    /*!< 指向一个图，该图只有一个顶点*/
    std::shared_ptr<GType> _1e_graph;    /*!< 指向一个图，该图只有一条边*/
    std::shared_ptr<GType> _list_graph;    /*!< 指向一个图，该图的边组成一个链条*/
};


//!test_topology_sort:测试topology_sort方法
/*!
*
* 测试`topology_sort`方法
*/
TEST_F(TopologySortTest,test_topology_sort)
{
    typedef  DFS_Vertex<double>::VIDType VIDType;
    //****** 测试只有一个顶点的图**********
    EXPECT_EQ(topology_sort(_1v_graph),std::vector<VIDType>({0}));
    //****** 测试只有一条边的图**********
    EXPECT_EQ(topology_sort(_1e_graph),std::vector<VIDType>({0,1}));
    //****** 测试测试链边的图**********
    std::vector<VIDType>  real_result;
    for(int i=0;i<TPS_N;i++)
    {
        real_result.push_back(i);
    }
    EXPECT_EQ(topology_sort(_list_graph),real_result);
}

#endif // TOPOLOGYSORT_TEST

