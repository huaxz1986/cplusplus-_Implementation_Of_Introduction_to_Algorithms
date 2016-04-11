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
#ifndef GOODSELECT
#define GOODSELECT
#include<vector>
#include"src/sort_algorithms/quick_sort/quicksort.h"
namespace IntroductionToAlgorithm
{
    namespace SelectAlgorithm
    {
    //! good_select： 算法导论第9章9.3 最坏时间为O(n)的顺序统计量选择算法
    /*!
     * \param begin : 待选取的序列的起始迭代器（也可以是指向数组中某元素的指针）
     * \param end: 待选取的序列的终止迭代器（也可以是指向数组中某元素的指针）
     * \param rank: 指定选取的顺序数，0为选取最小的元素，1为选取次小的元素....n表示选取排序为n的元素（从小排序）
     * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
     * \return 第rank小的元素值
     *
     * - 选择算法思想，假设对数组A[p...r]选择，选择第k小的元素：
     *      - 选择主元：
     *          - 首先将序列从前往后，按照5个元素一组分组。其中最后一组可能为1～5个元素（也就是可能不是满的）
     *          - 然后将这些分组进行排序（我采用的是快速排序）
     *          - 然后将这些分组中的中位数（即最中间的数）取出
     *          - 针对这些分组的中位数构成的序列，递归调用 good_select，找出中位数的中位数
     *          - 将这个中位数的中位数作为划分主元
     *      - 划分：根据找到的主元对原序列进行划分，假设划分完毕后，主元是第m小
     *      - 判定：
     *          - 若m==k，则找到了这个元素，返回这个主元
     *          - 若m<k ，则说明指定的元素在 A[m+1...r]中，且位于这个新数组的第(k-m-1)小，此时递归调用good_select(....)
     *          - 若m>k， 则说明指定的元素在 A[p...m-1]中，且位于这个新数组的第 k 小，此时递归调用good_select(...)
     * - 时间复杂度：最坏情况下时间为O(n)
     * - 非原地操作：因为这里要把所有分组的中位数构造成一个序列，然后把找到该序列的中位数作为good_select(...)的主元
    */
    template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                typename std::iterator_traits<Iterator>::value_type
                good_select(const Iterator begin,const Iterator end,typename std::iterator_traits<Iterator>::difference_type rank,CompareType compare=CompareType())
        {
            using IntroductionToAlgorithm::SortAlgorithm::quick_sort;
            using IntroductionToAlgorithm::SortAlgorithm::partition;

            typedef typename std::iterator_traits<Iterator>::value_type T;
            auto size=std::distance(begin,end);
            assert(size>0);
            assert(rank<size);
            if(size==1)
                return *begin;
            // *********  将序列划分为5个元素一组的区间，最后一组可能不满5个元素；对每组进行排序，取出其中值放入vector中  *********
            auto iter=begin;
            std::vector<T> middle_nums;
            while(iter<end)
            {
                auto from=iter;
                auto to=iter+5;
                if(to>end)
                    to=end;

                quick_sort(from,to,compare);
                middle_nums.push_back(*(from+(to-from-1)/2));
                iter+=5;
            }
            // ********* 取出这些中值的中值 ************
            T mid_of_middles=good_select(middle_nums.begin(),middle_nums.end(),middle_nums.size()/2,compare); //所有中值的中值
            iter=begin;
            while(std::distance(iter,end)>0&&*iter!=mid_of_middles) //得到中值的中值在原序列中的位置
            {
                iter++;
            }
            //********* 划分 **************
            auto mid_of_middles_iter=partition(begin,end,iter,compare); //以中值的中值作为一个划分值
            // ********** 判别 ***************
            auto mid_of_middles_rank=std::distance(begin,mid_of_middles_iter);//中值的中值在划分之后的排序
            if(mid_of_middles_rank== rank)  //找到了该排位的数
                return *mid_of_middles_iter;
            else if(mid_of_middles_rank<rank) //已知某排位的数位次较低，则指定排位数的元素在它右侧
                return good_select(mid_of_middles_iter+1,end,rank-mid_of_middles_rank-1,compare); //mid_of_middles_iter+1，则找右侧的第rank-mid_of_middles_rank-1位
            else                   //已知某排位的数位次较高，则指定排位数的元素在它左侧
                return good_select(begin,mid_of_middles_iter,rank,compare);
        }
    }
}

#endif // GOODSELECT

