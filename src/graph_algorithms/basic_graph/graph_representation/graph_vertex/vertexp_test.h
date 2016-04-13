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
#ifndef VERTEXP_TEST
#define VERTEXP_TEST
#include"src/google_test/gtest.h"
#include"vertexp.h"
using IntroductionToAlgorithm::GraphAlgorithm::VertexP;
//!test_vertex_p：测试VertexP
/*!
*
* 测试VertexP的构造、以及方法
*/
TEST(test_vertex_p,vertexp_test)
{
    {
        auto v=VertexP<int>(); //默认构造
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,0);
        EXPECT_FALSE(v.parent);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:0\t parent:nullptr");
    }
    {
        auto v=VertexP<int>(10); //指定了key
        EXPECT_EQ(v.id,-1);
        EXPECT_EQ(v.key,10);
        EXPECT_FALSE(v.parent);
        EXPECT_EQ(v.to_string(),"vertex id:-1\t key:10\t parent:nullptr");
    }
    {
        auto v=VertexP<int>(0,1); //指定了key,id
        EXPECT_EQ(v.id,1);
        EXPECT_EQ(v.key,0);
        EXPECT_FALSE(v.parent);
        EXPECT_EQ(v.to_string(),"vertex id:1\t key:0\t parent:nullptr");
    }
}
#endif // VERTEXP_TEST

