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
#ifndef VERTEX_TEST
#define VERTEX_TEST
#include"src/google_test/gtest.h"
#include"vertex.h"
#include"src/header.h"
using IntroductionToAlgorithm::GraphAlgorithm::is_unlimit;
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;
using IntroductionToAlgorithm::GraphAlgorithm::Vertex;
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

//!test_vertex：测试Vertex
/*!
*
* 测试Vertex的构造、以及方法
*/
TEST(test_vertex,vertex_test)
{
    {
        auto v=Vertex<int>(); //默认构造
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,0);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:0");
    }
    {
        auto v=Vertex<int>(10); //指定了key
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,10);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:10");
    }
    {
        auto v=Vertex<int>(0,1); //指定了key,id
        EXPECT_EQ(v.id,1);
        EXPECT_EQ(v.to_string(),"vertex id:1\t key:0");
    }
}
#endif // VERTEX_TEST

