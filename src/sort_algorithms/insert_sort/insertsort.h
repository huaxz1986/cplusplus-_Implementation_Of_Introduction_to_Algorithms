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
#ifndef INSERTSORTE_H
#define INSERTSORTE_H
namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {
    //!insert_sort：算法导论第二章 2.1
    /*!
    * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
    * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
    * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
    * \return void
    *
    * - 插入排序思想，假设对数组A[p...r]排序：
    *   - 维持不变式：设当前排序的元素是 A[q]，则保持A[p...q-1]为排好的，A[q]在A[p...q-1]中找到它的位置坐下
    * - 时间复杂度 O(n^2)
    * - 原地排序
    */
    template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                void insert_sort(const Iterator begin,const Iterator end,CompareType compare=CompareType())
     {
            //typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            auto size=std::distance(begin,end);
            if(size<=1)
                return;
            Iterator current=begin;
            while(++current!=end)
            {
                auto small_next=current; //指向比*current小的元素中最大的那个元素
                while(small_next!=begin && compare(*current,*(small_next-1))) //current较小，则向前寻找插入的位置插入
                {
                    small_next--;
                }

                auto key=*current;
                auto iter=current;
                while(iter!=small_next) //插入
                {
                    *iter=*(iter-1); //后移
                    iter--;
                }
                *(iter)=key;
            }
        }
    }
}

#endif // INSERTSORTE_H
