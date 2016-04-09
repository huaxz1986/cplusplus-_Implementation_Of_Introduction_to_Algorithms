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
#ifndef MERGESORTE_H
#define MERGESORTE_H
#include<vector>
namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {

    //! merge：算法导论第二章 2.3.1
    /*!
    * \param begin : begin...middle之间为已排好序列
    * \param end: middle...end之间为已排好序列
    * \param middle: begin...middle之间为已排好序列
    * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
    * \return void
    *
    * - 归并思想，假设对数组A[p...q...r]归并：
    *   - 拷贝：将数组A[p...q]拷贝到数组L，将数组A[q...r]拷贝到数组R，
    *   - 归并： 从左到右依次取L、R中的较小的元素，存放到A中（具体算法见代码）
    * - 时间复杂度 O(n)
    * - 归并时需要额外的空间 O(n)
    */
        template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                void merge(const Iterator begin,const Iterator end,const Iterator middle,CompareType compare=CompareType())
        {
            typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            if(std::distance(begin,middle)<=0||std::distance(middle,end)<=0) return;
            std::vector<T> result(begin,end); //暂存结果
            auto current=result.begin();
            auto left_current=begin; //左侧序列当前比较位置
            auto right_current=middle;//右序列当前比较位置
            while(left_current!=middle && right_current!=end)
            {
                if(compare(*left_current,*right_current))
                {
                    *current++=*left_current++;//左侧较小

                }else
                {
                    *current++=*right_current++;//左侧较小
                }
            }
            if(left_current==middle&&right_current!=end) //当左侧序列为搬空
            {
                std::copy(right_current,end,current);
            }
            if(right_current==end&&left_current!=middle) //当右侧序列搬空
            {
                std::copy(left_current,middle,current);
            }
            std::copy(result.begin(),result.end(),begin); //复制回原序列，因此是非原地的
        }

    //! merge_sort：算法导论第二章 2.3.1
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
    * \return void
    *
    * - 归并排序思想，假设对数组A[p...r]排序：
    *   - 分解：将数组A[p...r]平均划分为2子数组A[p...q-1]个A[q...r]，一直划分直到每个子数组只有1个元素
    *   - 归并： 对 A[p...q-1]和A[q...r]这两个已排序好的数组进行合并
    * - 时间复杂度 O(nlgn)
    * - 非原地排序，归并时需要额外的空间 O(n)
    */
        template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                    void merge_sort(const Iterator begin,const Iterator end,CompareType compare=CompareType())
        {
            //typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            auto size=std::distance(begin,end);
            if(size>1)
            {
                Iterator middle=begin+size/2;
                merge_sort(begin,middle,compare);
                merge_sort(middle,end,compare);
                merge(begin,end,middle,compare);
            }
        }
    }
}
#endif // MERGESORTE_H

