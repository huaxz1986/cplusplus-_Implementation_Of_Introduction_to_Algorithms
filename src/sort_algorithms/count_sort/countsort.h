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
#ifndef COUNTSORT
#define COUNTSORT
#include<vector>

namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {
    //!count_sort：算法导论第8章 8.2
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \param max_val:待排序序列的元素值的上界（不一定是最紧的上界）
    * \return void
    *
    * - 计数排序思想，假设对数组A[p...r]排序，其中数组中所有元素都为正整数，并且都是小于max_val：
    *   - 首先对A进行计数。对每一个元素A[i]，将它出现的次数存放在CounterArray[A[i]]中
    *   - 然后对CounterArray累加，得出A[i]应该在结果序列中排多少位
    *   - 最后在结果数组中直接放置A[i]（根据它的排位）
    * - 时间复杂度 O(n)
    * - 空间复杂度 O(n)
    *
    * >这里必须对整数才能采取计数排序。由static_assert(...,...)确保
    *
    */
    template<typename Iterator>
                void count_sort(const Iterator begin,const Iterator end,const typename std::iterator_traits<Iterator>::value_type& max_val)
     {
            typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            static_assert(std::is_integral<T>::value, "sequence to be sorted must be integer!"); //必须针对整数进行计数排序

            auto size=std::distance(begin,end);
            if(size <=1) return;

            std::vector<T> CounterArray(max_val+1); //存放计数结果
            std::vector<T> ResultArray(size); //暂存排序结果
            std::size_t n=0;
            while(begin+n!=end) //计个数
            {
               CounterArray.at(*(begin+n))++;
               n++;
            }
            for(std::size_t i=1;i<CounterArray.size();i++)//计排位数
            {
                  CounterArray.at(i)+=CounterArray.at(i-1);
            }
            int index=ResultArray.size()-1;
            while(index>=0)
            {
                 auto data=*(begin+index); //待排序的元素
                 T less_data_num=CounterArray[data]-1; //比它小的元素的个数
                 ResultArray[less_data_num]=data; //直接定位
                 CounterArray[data]--; //此行为了防止重复元素的定位
                 index--;
            }
            std::copy(ResultArray.begin(),ResultArray.end(),begin);
     }
    }
}
#endif // COUNTSORT

