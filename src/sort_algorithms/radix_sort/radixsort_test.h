#ifndef RADIXSORT_TEST
#define RADIXSORT_TEST
#include"src/google_test/gtest.h"
#include"radixsort.h"
//!radix_sort_test：测试test_digi_on_N:获取指定自然数某个位数上的数字（个位为第0位）
/*!
*
* 自然数 123456789： 依次测试每一位
*/
TEST(test_radix_sort,test_digi_on_N)
{
   for(int i=0;i<9;i++)
        EXPECT_EQ(IntrodunctionToAlgorithm::SortAlgorithm::digi_on_N(123456789,i),9-i)<<"\t in i:"<<i ;
}

//!radix_sort_test：测试C数组的基数排序
/*!
*
* 四组数组： 增序排列、降序排列、有重复数字、单元素的数组
* 参考函数： std::sort()函数
*/
TEST(test_radix_sort, test_C_array)
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
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<int*,int,3>(data1+0,data1+10);
    std::sort(comparedata2,comparedata2+10);
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<int*,int,3>(data2+0,data2+10);
    std::sort(comparedata3,comparedata3+10);
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<int*,int,3>(data3+0,data3+10);
    std::sort(comparedata4,comparedata4+1);
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<int*,int,3>(data4+0,data4+1);
    EXPECT_EQ(std::vector<int>(data1,data1+10),std::vector<int>(comparedata1,comparedata1+10));
    EXPECT_EQ(std::vector<int>(data2,data2+10),std::vector<int>(comparedata2,comparedata2+10));
    EXPECT_EQ(std::vector<int>(data3,data3+10),std::vector<int>(comparedata3,comparedata3+10));
    EXPECT_EQ(std::vector<int>(data4,data4+1),std::vector<int>(comparedata4,comparedata4+1));
}

//!radix_sort_test：测试std::array的基数排序
/*!
*
* 四组std::array： 增序排列、降序排列、有重复数字、单元素的std::array
* 参考函数： std::sort()函数
*/
TEST(test_radix_sort, test_std_container)
{
    std::vector<int> data1={123,234,345,456,567,678,789,890,901,912};
    std::vector<int> data2={912,901,890,789,678,567,456,345,234,123};
    std::vector<int> data3={555,555,544,554,545,444,455,445,454,444};
    std::vector<int> data4={555};
    std::vector<int> comparedata1={123,234,345,456,567,678,789,890,901,912};
    std::vector<int> comparedata2={912,901,890,789,678,567,456,345,234,123};
    std::vector<int> comparedata3={555,555,544,554,545,444,455,445,454,444};
    std::vector<int> comparedata4={555};

    typedef typename std::vector<int>::iterator Iterator;
    std::sort(comparedata1.begin(),comparedata1.end());
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<Iterator,int,3>(data1.begin(),data1.end());
    std::sort(comparedata2.begin(),comparedata2.end());
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<Iterator,int,3>(data2.begin(),data2.end());
    std::sort(comparedata3.begin(),comparedata3.end());
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<Iterator,int,3>(data3.begin(),data3.end());
    std::sort(comparedata4.begin(),comparedata4.end());
    IntrodunctionToAlgorithm::SortAlgorithm::radix_sort<Iterator,int,3>(data4.begin(),data4.end());
    EXPECT_EQ(data1,comparedata1);
    EXPECT_EQ(data2,comparedata2);
    EXPECT_EQ(data3,comparedata3);
    EXPECT_EQ(data4,comparedata4);
}
#endif // RADIXSORT_TEST

