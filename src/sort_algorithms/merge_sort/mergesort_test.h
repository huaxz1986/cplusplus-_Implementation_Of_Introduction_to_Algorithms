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
#ifndef MERGESORTER_TEST_H
#define MERGESORTER_TEST_H
#include"src/google_test/gtest.h"
#include"mergesort.h"
using IntroductionToAlgorithm::SortAlgorithm::merge;
using IntroductionToAlgorithm::SortAlgorithm::merge_sort;
//!merge_sort_test：测试C数组的归并排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_merge_sort, test_C_array)
{
    int data1[10]={1,2,3,4,5,6,7,8,9,10};
    int data2[10]={10,9,8,7,6,5,4,3,2,1};
    int data3[10]={5,5,5,5,5,4,4,4,4,4};
    int data4[1]={5};
    int comparedata1[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata2[10]={10,9,8,7,6,5,4,3,2,1};
    int comparedata3[10]={5,5,5,5,5,4,4,4,4,4};
    int comparedata4[1]={5};

    std::sort(comparedata1,comparedata1+10);
    merge_sort(data1+0,data1+10);
    std::sort(comparedata2,comparedata2+10);
    merge_sort(data2+0,data2+10);
    std::sort(comparedata3,comparedata3+10);
    merge_sort(data3+0,data3+10);
    std::sort(comparedata4,comparedata4+1);
    merge_sort(data4+0,data4+1);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!merge_sort_test：测试std::array的归并排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_merge_sort, test_std_container)
{
    std::vector<int> data1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> data2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> data3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> data4={5};
    std::vector<int> comparedata1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> comparedata3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> comparedata4={5};

    std::sort(comparedata1.begin(),comparedata1.end());
    merge_sort(data1.begin(),data1.end());
    std::sort(comparedata2.begin(),comparedata2.end());
    merge_sort(data2.begin(),data2.end());
    std::sort(comparedata3.begin(),comparedata3.end());
    merge_sort(data3.begin(),data3.end());
    std::sort(comparedata4.begin(),comparedata4.end());
    merge_sort(data4.begin(),data4.end());
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
//!merge_test：测试C数组的归并
/*!
*
* 五组数组： 左右对半、左边只有1个元素、右边只有一个1元素、左边只有0个元素、右边只有一个0元素
* 参考函数： std::sort()函数
*/
TEST(test_merge, test_C_array)
{
    int data1[10]={1,3,5,7,9,2,4,6,8,10};
    int data2[10]={1,2,3,4,5,6,7,8,9,10};
    int data3[10]={1,2,3,4,5,6,7,8,9,0};
    int data4[10]={1,2,3,4,5,6,7,8,9,10};
    int data5[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata1[10]={1,3,5,7,9,2,4,6,8,10};
    int comparedata2[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata3[10]={1,2,3,4,5,6,7,8,9,0};
    int comparedata4[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata5[10]={1,2,3,4,5,6,7,8,9,10};

    std::sort(comparedata1,comparedata1+10);
    merge(data1+0,data1+10,data1+5);
    std::sort(comparedata2,comparedata2+10);
    merge(data2+0,data2+10,data2+1);
    std::sort(comparedata3,comparedata3+10);
    merge(data3+0,data3+10,data3+9);
    std::sort(comparedata4,comparedata4+10);
    merge(data4+0,data4+10,data4+0);
    std::sort(comparedata5,comparedata5+10);
    merge(data5+0,data5+10,data5+10);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+10),std::vector<int>(comparedata4,comparedata4+10));
    EXPECT_EQ(std::vector<int>(data5,data5+10),std::vector<int>(comparedata5,comparedata5+10));
}

//!merge_test：测试std::array的归并
/*!
*
* 五组std::array： 左右对半、左边只有1个元素、右边只有一个1元素、左边只有0个元素、右边只有一个0元素
* 参考函数： std::sort()函数
*/
TEST(test_merge, test_std_container)
{
    std::vector<int> data1={1,3,5,7,9,2,4,6,8,10};
    std::vector<int> data2={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> data3={1,2,3,4,5,6,7,8,9,0};
    std::vector<int> data4={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> data5={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata1={1,3,5,7,9,2,4,6,8,10};
    std::vector<int> comparedata2={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata3={1,2,3,4,5,6,7,8,9,0};
    std::vector<int> comparedata4={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata5={1,2,3,4,5,6,7,8,9,10};

    std::sort(comparedata1.begin(),comparedata1.end());
    merge(data1.begin(),data1.end(),data1.begin()+5);
    std::sort(comparedata2.begin(),comparedata2.end());
    merge(data2.begin(),data2.end(),data2.begin()+1);
    std::sort(comparedata3.begin(),comparedata3.end());
    merge(data3.begin(),data3.end(),data3.begin()+9);
    std::sort(comparedata4.begin(),comparedata4.end());
    merge(data4.begin(),data4.end(),data4.begin()+0);
    std::sort(comparedata5.begin(),comparedata5.end());
    merge(data5.begin(),data5.end(),data5.begin()+10);
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
    EXPECT_EQ(data5,comparedata5);
}

#endif // MERGESORTER_TEST_H

