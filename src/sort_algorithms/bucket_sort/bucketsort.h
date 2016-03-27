#ifndef BUCKETSORT
#define BUCKETSORT
#include"src/sort_algorithms/quick_sort/quicksort.h"
#include<vector>

namespace IntrodunctionToAlgorithm
{
    namespace SortAlgorithm
    {
    //!bucket_sort：算法导论第8章 8.4
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \return void
    *
    * - 桶排序思想，假设对数组A[p...r]排序，首先将这些元素进行hash运算，根据其hash值放入桶的对应区间中；然后对每一个区间中的元素进行排序；最后合并桶中各区间排序好的结果得到排序的数据：
    *   - hash算法必须满足：若 a<b ，则hash(a)<hash(b)
    *   - 要求 hash的结果尽量好，使得各数据平均分布在各区间内
    * - 期望时间复杂度 O(n)
    * - 非原地排序
    */
        template<typename Iterator,typename T,size_t BUCKETNUM >
                void bucket_sort(Iterator begin,Iterator end)
        {
            std::size_t real_bucket_num=BUCKETNUM+1;
            std::vector<T> buckets[BUCKETNUM+1];

            auto iter=begin;
            while(iter!=end)
            {
                auto value=*iter;
                auto index=value/real_bucket_num; // 这里采取最简单的hash：将 hash(x)= x/real_bucket_num
                if(index<BUCKETNUM)
                    buckets[index].push_back(value); //放元素到桶中
                else
                    buckets[BUCKETNUM].push_back(value); //最后一个区间放超大数
                iter++;
            }
            std::size_t inserted_total=0;
            for(std::size_t i=0;i<real_bucket_num;i++)
            {
                quick_sort<typename std::vector<T>::iterator,T>(buckets[i].begin(),buckets[i].end());//对某个区间排序
                std::copy(buckets[i].begin(),buckets[i].end(),begin+inserted_total);//排序后放回原容器
                inserted_total+=buckets[i].size();
            }
        }
    }
}
#endif // BUCKETSORT

