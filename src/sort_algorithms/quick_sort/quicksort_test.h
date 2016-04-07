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
#ifndef QUICKSORTER_TEST_H
#define QUICKSORTER_TEST_H
#include"src/google_test/gtest.h"
#include"quicksort.h"
using IntroductionToAlgorithm::SortAlgorithm::partition;
using IntroductionToAlgorithm::SortAlgorithm::quick_sort;
//!partition_test：测试C数组的划分
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
*/
TEST(test_partition, test_C_array)
{
        for(int i=0;i<10;i++)
        {
            int data1[10]={1,2,3,4,5,6,7,8,9,10};
            auto index=partition(data1+0,data1+10,data1+i);
            EXPECT_EQ(index-data1,i)<<"\ti:"<<i;;
            auto iter=data1+0;
            while(iter!=index)
            {
                EXPECT_LT(*iter,*index)<<"\ti:"<<i; //compare 小于比较
                iter++;
            }
            iter=index+1;
            while(iter!=data1+10)
            {
                EXPECT_GE(*iter,*index)<<"\ti:"<<i;//后面的非小于
                iter++;
            }
        }

        for(int i=0;i<10;i++)
        {
            int data2[10]={10,9,8,7,6,5,4,3,2,1};
            auto index=partition(data2+0,data2+10,data2+i);
            EXPECT_EQ(index-data2,9-i)<<"\ti:"<<i;
            auto iter=data2+0;
            while(iter!=index)
            {
                EXPECT_LT(*iter,*index)<<"\ti:"<<i;//compare 小于比较
                iter++;
            }
            iter=index+1;
            while(iter!=data2+10)
            {
                EXPECT_GE(*iter,*index)<<"\ti:"<<i;//后面的非小于
                iter++;
            }
        }



        {
            int data3[10]={5,5,5,5,5,4,4,4,4,4};
            auto index=partition(data3+0,data3+10,data3+1);
            EXPECT_EQ(*index,5);
            auto iter=data3+0;
            while(iter!=index)
            {
                    EXPECT_LT(*iter,*index);//compare 小于比较
                    iter++;
            }
            iter=index+1;
            while(iter!=data3+10)
            {
                    EXPECT_GE(*iter,*index);//后面的非小于
                    iter++;
            }
        }


        {   int data4[1]={5};
            auto index=partition(data4+0,data4+1,data4+0);
            EXPECT_EQ(index,data4); // 空序列和单元素序列，划分结果为begin迭代器
            auto iter=data4+0;
            while(iter<index)
            {
                    EXPECT_LT(*iter,*index);//compare 小于比较
                    iter++;
            }
            iter=index+1;
            while(iter<data4+1)
            {
                    EXPECT_GE(*iter,*index); //后面的非小于
                    iter++;
            }
        }        

}

//!partition_test：测试std::array的划分
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
*/
TEST(test_partition, test_std_container)
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
    quick_sort(data1.begin(),data1.end());
    std::sort(comparedata2.begin(),comparedata2.end());
    quick_sort(data2.begin(),data2.end());
    std::sort(comparedata3.begin(),comparedata3.end());
    quick_sort(data3.begin(),data3.end());
    std::sort(comparedata4.begin(),comparedata4.end());
    quick_sort(data4.begin(),data4.end());
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
//!quick_sort_test：测试C数组的快速排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_quick_sort, test_C_array)
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
    quick_sort(data1+0,data1+10);
    std::sort(comparedata2,comparedata2+10);
    quick_sort(data2+0,data2+10);
    std::sort(comparedata3,comparedata3+10);
    quick_sort(data3+0,data3+10);
    std::sort(comparedata4,comparedata4+1);
    quick_sort(data4+0,data4+1);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!quick_sort_test：测试std::array的快速排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_quick_sort, test_std_container)
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
    quick_sort(data1.begin(),data1.end());
    std::sort(comparedata2.begin(),comparedata2.end());
    quick_sort(data2.begin(),data2.end());
    std::sort(comparedata3.begin(),comparedata3.end());
    quick_sort(data3.begin(),data3.end());
    std::sort(comparedata4.begin(),comparedata4.end());
    quick_sort(data4.begin(),data4.end());
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
#endif // QUICKSORTER_TEST_H

