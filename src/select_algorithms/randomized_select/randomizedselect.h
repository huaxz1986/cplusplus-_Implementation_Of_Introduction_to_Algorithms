#ifndef RANDOMIZED_SELECT
#define RANDOMIZED_SELECT
#include<src/sort_algorithms/quick_sort/quicksort.h>
#include <random>
namespace IntroductionToAlgorithm
{
    namespace SelectAlgorithm
    {

    //! radom_index： 生成随机整数
    /*!
     * \param begin: 整数范围的开始数（生成的随机数在闭区间[begin,end]中）
     * \param end: 整数范围的截止数（生成的随机数在闭区间[begin,end]中）
     * \return 生成的随机数
     *
     * 这里采用[begin,end]之间的均匀分布
    */
     template<typename IntType> IntType  radom_index(IntType begin,IntType end)
     {
         assert(end>=begin);
         static std::random_device rd; //每一个std::random_device维持相同的伪随机序列，因此需要用静态变量保证只有一个std::random_device
         std::mt19937 gen(rd());
         std::uniform_int_distribution<IntType> dis(begin, end);
         return dis(gen);
     }

    //! randomized_select： 算法导论第9章9.2 顺序统计量的随机选择算法
    /*!
     * \param begin : 待选取的序列的起始迭代器（也可以是指向数组中某元素的指针）
     * \param end: 待选取的序列的终止迭代器（也可以是指向数组中某元素的指针）
     * \param rank: 指定选取的顺序数，0为选取最小的元素，1为选取次小的元素....n表示选取排序为n的元素（从小排序）
     * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
     * \return 第rank小的元素值
     *
     * - 选择算法思想，假设对数组A[p...r]选择，选择第k小的元素：
     *      - 随机选择主元：随机选取数组的一个下标q,A[q]作为划分元素
     *      - 划分：利用A[q]划分数组，获得A[q]在序列中是第 m 小
     *      - 判定：
     *          - 若m==k，则找到了这个元素，返回  A[q]
     *          - 若m<k ，则说明指定的元素在 A[q+1...r]中，且位于这个新数组的第(k-m-1)小，此时递归调用randomized_select(q+1,end,k-m-1)
     *          - 若m>k， 则说明指定的元素在 A[p...q-1]中，且位于这个新数组的第 k 小，此时递归调用randomized_select(begin,q,k)
     * - 时间复杂度：最坏情况下为O(n^2)，期望时间为O(n)
     * - 原地操作
    */
        template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
                    typename std::iterator_traits<Iterator>::value_type
                    randomized_select(const Iterator begin,const Iterator end,typename std::iterator_traits<Iterator>::difference_type rank,CompareType compare=CompareType())
        {
            //typedef typename std::iterator_traits<Iterator>::value_type T;
            auto size=std::distance(begin,end);
            assert(size>=0);
            assert(rank<size);
            using IntroductionToAlgorithm::SortAlgorithm::partition;
            auto partitioned_iter=partition(begin,end,begin+radom_index(0,size-1),compare); //随机划分
            auto distance=std::distance(begin,partitioned_iter);
            if(distance== rank)  //找到了该排位的数
                return *partitioned_iter;
            else if(distance<rank) //已知某排位的数位次较低，则指定排位数的元素在它右侧
                return randomized_select(partitioned_iter+1,end,rank-distance-1,compare); //从partitioned_iter+1，则找右侧的第rank-distance-1位
            else                   //已知某排位的数位次较高，则指定排位数的元素在它左侧
                return randomized_select(begin,partitioned_iter,rank,compare);
        }
    }
}

#endif // RANDOMIZED_SELECT

