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
#ifndef GOODSELECT_TEST
#define GOODSELECT_TEST
#include"src/google_test/gtest.h"
#include"goodselect.h"
using namespace IntroductionToAlgorithm::SelectAlgorithm;
//!good_select_test：测试C数组的顺序统计量
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
*/
TEST(test_good_select, test_C_array)
{

        for(int i=0;i<10;i++)
        {
            int data1[10]={1,2,3,4,5,6,7,8,9,10};
            auto val=good_select(data1+0,data1+10,i);
            EXPECT_EQ(val,i+1)<<"\ti:"<<i;
        }
        for(int i=0;i<10;i++)
        {
            int data2[10]={10,9,8,7,6,5,4,3,2,1};
            auto val=good_select(data2+0,data2+10,i);
            EXPECT_EQ(val,i+1)<<"\ti:"<<i;
        }
        {
            int data3[10]={5,5,5,5,5,4,4,4,4,4};
            auto val=good_select(data3+0,data3+10,0);
            EXPECT_EQ(val,4);
        }
        {
            int data3[10]={5,5,5,5,5,4,4,4,4,4};
            auto val=good_select(data3+0,data3+10,9);
            EXPECT_EQ(val,5);
        }
        {   int data4[1]={5};
            auto val=good_select(data4+0,data4+1,0);
            EXPECT_EQ(val,5);
        }

}
#endif // GOODSELECT_TEST

