#ifndef COUNTSORT_TEST
#define COUNTSORT_TEST
#include"src/google_test/gtest.h"
#include"countsort.h"
using IntrodunctionToAlgorithm::SortAlgorithm::count_sort;
//!count_sort_test：测试C数组的计数排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_count_sort, test_C_array)
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
    count_sort(data1+0,data1+10,20);
    std::sort(comparedata2,comparedata2+10);
    count_sort(data2+0,data2+10,20);
    std::sort(comparedata3,comparedata3+10);
    count_sort(data3+0,data3+10,20);
    std::sort(comparedata4,comparedata4+1);
    count_sort(data4+0,data4+1,20);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!count_sort_test：测试std::array的计数排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_count_sort, test_std_container)
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
    count_sort(data1.begin(),data1.end(),20);
    std::sort(comparedata2.begin(),comparedata2.end());
    count_sort(data2.begin(),data2.end(),20);
    std::sort(comparedata3.begin(),comparedata3.end());
    count_sort(data3.begin(),data3.end(),20);
    std::sort(comparedata4.begin(),comparedata4.end());
    count_sort(data4.begin(),data4.end(),20);
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
#endif // COUNTSORT_TEST

