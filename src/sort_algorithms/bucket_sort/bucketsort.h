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
#ifndef BUCKETSORT
#define BUCKETSORT
#include"../quick_sort/quicksort.h"
#include<vector>
#include<cassert>
namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {
    //!bucket_sort：算法导论第8章 8.4
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \param min_val:待排序序列元素的下界（不一定是最紧下界）
    * \param max_val:待排序序列元素的上界（不一定是最紧上界）
    * \return void
    *
    * - 桶排序思想，假设对数组A[p...r]排序，首先将这些元素进行hash运算，根据其hash值放入桶的对应区间中；然后对每一个区间中的元素进行排序；最后合并桶中各区间排序好的结果得到排序的数据：
    *   - hash算法必须满足：若 a<b ，则hash(a)<hash(b)
    *   - 要求 hash的结果尽量好，使得各数据平均分布在各区间内
    * - 期望时间复杂度 O(n)
    * - 非原地排序
    */
        template<typename Iterator>
                void bucket_sort(const Iterator begin,const Iterator end,const typename std::iterator_traits<Iterator>::value_type& min_val,
                                 const typename std::iterator_traits<Iterator>::value_type& max_val)
        {
            assert(min_val<max_val);  //确保最小值小于最大值
            typedef typename std::iterator_traits<Iterator>::value_type T; // 迭代器指向对象的值类型
            std::size_t real_bucket_num=10; //划分10个区间
            std::vector<T> buckets[real_bucket_num];

            Iterator iter=begin;
            while(iter!=end)
            {
                auto value=*iter;
                auto index=(value-min_val)*real_bucket_num/(max_val-min_val); // 这里采取最简单的hash：线性分布
                if(index<real_bucket_num)
                    buckets[index].push_back(value); //放元素到桶中
                else
                    buckets[real_bucket_num-1].push_back(value); //最后一个区间放超大数
                iter++;
            }
            std::size_t inserted_total=0;
            for(std::size_t i=0;i<real_bucket_num;i++)
            {
                quick_sort<typename std::vector<T>::iterator>(buckets[i].begin(),buckets[i].end());//对某个区间排序
                std::copy(buckets[i].begin(),buckets[i].end(),begin+inserted_total);//排序后放回原容器（因此是非原地）
                inserted_total+=buckets[i].size();
            }
        }
    }
}
#endif // BUCKETSORT

