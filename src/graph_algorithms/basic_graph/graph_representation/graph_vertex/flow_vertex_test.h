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
#ifndef FLOWVERTEX_TEST
#define FLOWVERTEX_TEST
#include"src/google_test/gtest.h"
#include"flow_vertex.h"
using IntroductionToAlgorithm::GraphAlgorithm::FlowVertex;

//!flowvertex_test：测试 FlowVertex
/*!
*
* 测试FlowVertex的构造、以及方法
*/
TEST(test_flowvertex,flowvertex_test)
{
    {
        auto v=FlowVertex<int>(); //默认构造
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,0);
        EXPECT_EQ(v.h,0);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:0\t h:0");
    }
    {
        auto v=FlowVertex<int>(10); //指定了key
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,10);
        EXPECT_EQ(v.h,0);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:10\t h:0");
    }
    {
        auto v=FlowVertex<int>(0,1); //指定了key,id
        EXPECT_EQ(v.id,1);
        EXPECT_EQ(v.key,0);
        EXPECT_EQ(v.h,0);
        EXPECT_EQ(v.to_string(),"vertex id:1\t key:0\t h:0");
    }
}
#endif // FLOWVERTEX_TEST

