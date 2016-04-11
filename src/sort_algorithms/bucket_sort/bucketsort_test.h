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
#ifndef BUCKETSORT_TEST
#define BUCKETSORT_TEST
#include"src/google_test/gtest.h"
#include"bucketsort.h"
using IntroductionToAlgorithm::SortAlgorithm::bucket_sort;
//!bucket_sort_test：测试C数组的桶排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_bucket_sort, test_C_array)
{
    int data1[10]={123,234,345,456,567,678,789,890,901,912};
    int data2[10]={912,901,890,789,678,567,456,345,234,123};
    int data3[10]={555,555,544,554,545,444,455,445,454,444};
    int data4[1]={555};
    int comparedata1[10]={123,234,345,456,567,678,789,890,901,912};
    int comparedata2[10]={912,901,890,789,678,567,456,345,234,123};
    int comparedata3[10]={555,555,544,554,545,444,455,445,454,444};
    int comparedata4[1]={555};

    std::sort(comparedata1,comparedata1+10);
    bucket_sort(data1+0,data1+10,100,1000);
    std::sort(comparedata2,comparedata2+10);
    bucket_sort(data2+0,data2+10,100,1000);
    std::sort(comparedata3,comparedata3+10);
    bucket_sort(data3+0,data3+10,100,1000);
    std::sort(comparedata4,comparedata4+1);
    bucket_sort(data4+0,data4+1,100,1000);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!bucket_sort_test：测试std::array的桶排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_bucket_sort, test_std_container)
{
    std::vector<int> data1={123,234,345,456,567,678,789,890,901,912};
    std::vector<int> data2={912,901,890,789,678,567,456,345,234,123};
    std::vector<int> data3={555,555,544,554,545,444,455,445,454,444};
    std::vector<int> data4={555};
    std::vector<int> comparedata1={123,234,345,456,567,678,789,890,901,912};
    std::vector<int> comparedata2={912,901,890,789,678,567,456,345,234,123};
    std::vector<int> comparedata3={555,555,544,554,545,444,455,445,454,444};
    std::vector<int> comparedata4={555};


    std::sort(comparedata1.begin(),comparedata1.end());
    bucket_sort(data1.begin(),data1.end(),100,1000);
    std::sort(comparedata2.begin(),comparedata2.end());
    bucket_sort(data2.begin(),data2.end(),100,1000);
    std::sort(comparedata3.begin(),comparedata3.end());
    bucket_sort(data3.begin(),data3.end(),100,1000);
    std::sort(comparedata4.begin(),comparedata4.end());
    bucket_sort(data4.begin(),data4.end(),100,1000);
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
#endif // BUCKETSORT_TEST

