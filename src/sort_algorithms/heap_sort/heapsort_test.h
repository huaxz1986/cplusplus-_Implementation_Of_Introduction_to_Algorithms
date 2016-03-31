#ifndef HEAP_SORT_TEST
#define HEAP_SORT_TEST
#include"src/google_test/gtest.h"
#include"heapsort.h"
using IntrodunctionToAlgorithm::SortAlgorithm::Sort_Heap;
//!heap_sort_test：测试C数组的堆排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_heap_sort, test_C_array)
{
    int data1[10]={1,2,3,4,5,6,7,8,9,10};
    int data2[10]={10,9,8,7,6,5,4,3,2,1};
    int data3[10]={5,5,5,5,5,4,4,4,4,4};
    int data4[1]={5};
    int comparedata1[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata2[10]={10,9,8,7,6,5,4,3,2,1};
    int comparedata3[10]={5,5,5,5,5,4,4,4,4,4};
    int comparedata4[1]={5};

    Sort_Heap<int*>sorter;
    std::sort(comparedata1,comparedata1+10);
    sorter(data1+0,10);
    std::sort(comparedata2,comparedata2+10);
    sorter(data2+0,10);
    std::sort(comparedata3,comparedata3+10);
    sorter(data3+0,10);
    std::sort(comparedata4,comparedata4+1);
    sorter(data4+0,1);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!heap_sort_test：测试std::array的堆排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_heap_sort, test_std_container)
{
    std::vector<int> data1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> data2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> data3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> data4={5};
    std::vector<int> comparedata1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> comparedata3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> comparedata4={5};

    Sort_Heap<std::vector<int>::iterator>sorter;
    std::sort(comparedata1.begin(),comparedata1.end());
    sorter(data1.begin(),data1.size());
    std::sort(comparedata2.begin(),comparedata2.end());
    sorter(data2.begin(),data2.size());
    std::sort(comparedata3.begin(),comparedata3.end());
    sorter(data3.begin(),data3.size());
    std::sort(comparedata4.begin(),comparedata4.end());
    sorter(data4.begin(),data4.size());
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
#endif // HEAP_SORT_TEST

