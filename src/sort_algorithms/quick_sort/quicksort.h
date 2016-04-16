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
#ifndef QUICKSORTE_H
#define QUICKSORTE_H
#include<assert.h>
namespace IntroductionToAlgorithm
{
    namespace SortAlgorithm
    {
    //! partition： 算法导论第7章快速排序中的划分算法
    /*!
     * \param begin : 待划分序列的起始迭代器（也可以是指向数组中某元素的指针）
     * \param end: 待划分序列的终止迭代器（也可以是指向数组中某元素的指针）
     * \param partition_iter: 指定划分元素的对应的迭代器（也可以是指向数组中某元素的指针）
     * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
     * \return :划分之后该划分元素值在序列中对应的新迭代器（也可以是指向数组中某元素的指针）
     *
     * - 划分思想，假设对数组A[p...r]划分，划分主元为A[q]：
     *   - 交换：首先将A[q]与A[r]交换，使得新的A[r]成为划分元素
     *   - 循环：维持循环不变式： A[p...smaller_next-1]始终小于A[r]，A[smaller_next...current-1]始终大于A[r]。开始对A[current]进行判别：
     *          - 若A[current]<A[r] 则交换 A[current]与 A[smaller_next], current右移（进行下一个元素的判断），smaller_next右移（维持不变式）
     *          - 若A[current]>=A[r], current右移（进行下一个元素的判断）
     * - 时间复杂度 O(n)
     * - 原地操作
    */
        template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                        Iterator partition(const Iterator begin,const Iterator end,const Iterator partition_iter,CompareType compare=CompareType())
        {
            //typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            auto size=std::distance(begin,end);
            assert(size>=0);
            if(size==0) return end;  //空序列，返回end
//            if(size<=1)
//                return begin;
            assert(std::distance(begin,partition_iter)>=0 &&std::distance(partition_iter,end)>0);
            auto smaller_next=begin;  //指向比key小的元素区间的下一个(即大于等于key元素区间的第一个），其中key为序列最后一个元素
            auto current=begin;  //指向当前待处理的元素
            std::swap(*partition_iter,*(end-1));//交换partition元素到末尾
            while(current!=end-1)
            {
                if(compare(*current,*(end-1)))
                {
                    std::swap(*smaller_next,*current);
                    smaller_next++;
                }
                current++;
            }
            std::swap(*smaller_next,*(end-1));//交换partition元素到它的位置
            return smaller_next;
        }
        //! quick_sort： 算法导论第7章
        /*!
         * \param begin : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
         * \param end: 待排序序列的终止迭代器（也可以是指向数组中某元素的指针）
         * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
         * \return void
         *
         * - 快速排序思想，假设对数组A[p...r]排序：
         *   - 分解：将数组A[p...r]划分为两个（可能为空）的子数组A[p...q-1]个A[q+1...r]，使得A[q]大于前面一个数组中每个元素，小于后面一个数组中每个元素（划分算法见partition算法）
         *   - 解决： 对 A[p...q-1]和A[q+1...r]递归调用快速排序
         * - 最坏时间复杂度 O(n^2)， 期望时间复杂度 O(nlgn)。它平均性能非常好，是实际排序应用中最好的选择
         * - 原地排序
        */
        template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                        void quick_sort(const Iterator begin,const Iterator end,CompareType compare=CompareType())
        {
            //typedef typename std::iterator_traits<Iterator>::value_type T;// 迭代器指向对象的值类型
            auto size=std::distance(begin,end);
            if(size<=1)
                return;
            auto partitioned_iter=partition(begin,end,end-1,compare); // 以最后一个元素作为划分元素，返回其顺序统计量
            quick_sort(begin,partitioned_iter,compare);
            quick_sort(partitioned_iter+1,end,compare);
        }
    }
}
#endif // QUICKSORTE_H

