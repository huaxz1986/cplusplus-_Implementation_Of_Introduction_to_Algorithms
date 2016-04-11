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
#ifndef RADIXSORT
#define RADIXSORT
#include"../insert_sort/insertsort.h"
#include<cmath>
#include<iostream>
#include<cassert>
namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {

    //!digi_on_N ： 获取正整数指定位数上的数字
    /*!
    * \param num : 待抽取数字的正整数
    * \param n: 指定的位数（0表示个位，1表示十位，...）
    * \return 指定正整数指定位数上的数字
    *
    *
    * 这里采用的 T 必须为某个整数类型，由static_assert(std::is_integral<T>::value,"..."")确保
    */
    template<typename T> T digi_on_N(T num,std::size_t n)
    {
       static_assert(std::is_integral<T>::value, "T must be integer!"); //必须针对整数才能取指定位数上的数字
       return num/(T)std::pow(10,n)-num/(T)std::pow(10,n+1)*10;
    }

    //!radix_sort：算法导论第8章 8.3
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \param radix_width: 待排序元素（必须是整数）的最大位宽，必须非0（由assert(radix_width!=0)确保）
    * \return void
    *
    * - 基数排序思想，假设对数组A[p...r]排序，其中数组中所有元素都为正整数，并且不超过RADIXWITH位（有模板的RADIXWITH参数指定）：
    *   - 首先对A中所有元素按照个位数大小进行排序（原地的）
    *   - 再对A中所有元素按照个十数大小进行排序（原地的）
    *   - 一直到最后按照A中所有元素的最高位的数字大小进行排序（原地的）
    *
    * - 时间复杂度 O(d(n+k))，其中d位数字的最大位宽(即这里都是d位数的整数），k为每个位数上数字取值（这里取0，1，2，3，...9）
    * - 原地排序
    *
    *  这里尤其要重点强调，用于对指定位上的数字进行排序时，必须要满足稳定性。
    *  - 快速排序就是非稳定的
    *  - 用小于比较的插入排序是稳定的；用小于等于比较的插入排序是不稳定的
    *
    * >这里必须对整数才能采取基数排序。由static_assert(...,...)确保
    */
    template<typename Iterator>
                void radix_sort(const Iterator begin,const Iterator end,std::size_t radix_width)
     {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        assert(radix_width!=0); //位数为有效的，0位数无效
        static_assert(std::is_integral<T>::value, "sequence to be sorted must be integer!"); //必须针对整数进行基数排序
        auto size=std::distance(begin,end);
        if(size<=1)
            return;
        for(std::size_t i=0;i<radix_width;i++) //从最低位(第0位为个位）到 （RADIXWITH-1）位的位数进行排序（一共RADIXWITH位）
        {
            auto compare=[i](T little, T big){return digi_on_N(little,i)<digi_on_N(big,i);}; //必须用 < 比较才是稳定排序，否则是不稳定排序，不能用快排（非稳定）
            insert_sort<Iterator,decltype(compare)>(begin,end,compare);
        }
     }
    }
}
#endif // RADIXSORT

