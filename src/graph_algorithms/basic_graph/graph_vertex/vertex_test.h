#ifndef GRAPHVERTEX_TEST
#define GRAPHVERTEX_TEST
#include"src/google_test/gtest.h"
#include"src/algorithms.h"
#include"vertex.h"
using IntrodunctionToAlgorithm::GraphAlgorithm::is_unlimit;
using IntrodunctionToAlgorithm::GraphAlgorithm::unlimit;
using IntrodunctionToAlgorithm::GraphAlgorithm::Vertex;

//!test_unlimit：测试 unlimit和is_unlimit函数
/*!
*
* 通过测试正无穷本身、正无穷加小整数、正无穷减小整数，验证正无穷的实现算法。
*/
TEST(test_unlimit, unlimit_is_unlimit_test)
{
  auto unlt=unlimit<int>();
  EXPECT_TRUE(is_unlimit(unlt));  //正无穷自身必须是正无穷
  for(int i=0;i<10;i++)
  {
      EXPECT_TRUE(is_unlimit(unlt+i));//正无穷加小数必须是正无穷
      EXPECT_TRUE(is_unlimit(unlt-i));//正无穷减小数必须是正无穷
  }
  EXPECT_TRUE(is_unlimit(unlt*2/3));//正无穷的边界
  EXPECT_TRUE(is_unlimit(unlt*2/3+1));//正无穷的边界之上
  EXPECT_FALSE(is_unlimit(unlt*2/3-1));//正无穷的边界之下
}

//!test_unlimit：测试Vertex
/*!
*
* 测试Vertex的构造、以及方法
*/
TEST(test_vertex,vertex_test)
{
    {
        auto v=Vertex<int>(); //默认构造
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.parent_id,-1);
        EXPECT_EQ(v.key,0);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:0\t parent_id:-1");
    }
    {
        auto v=Vertex<int>(10); //指定了key
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.parent_id,-1);
        EXPECT_EQ(v.key,10);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:10\t parent_id:-1");
    }
    {
        auto v=Vertex<int>(unlimit<int>(),1); //指定了key,id
        EXPECT_EQ(v.id,1);
        EXPECT_EQ(v.parent_id,-1);
        EXPECT_TRUE(is_unlimit<int>(v.key));
        EXPECT_EQ(v.to_string(),"vertex id:1\t key: +OO \t parent_id:-1");
    }
}

#endif // GRAPHVERTEX_TEST

