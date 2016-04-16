#ifndef MATCH
#define MATCH
#include<vector>

namespace IntroductionToAlgorithm {
    namespace StringMatchingAlgorithm{

        //! match： 常规的字符串匹配算法，算法导论第xx章
        /*!
         * \param iter1_begin : 被比较序列S的起始迭代器
         * \param iter1_end: 被比较序列S的终止迭代器
         * \param iter2_begin : 比较序列T的起始迭代器
         * \param iter2_end: 比较序列T的终止迭代器
         * \return: 被比较序列S中的匹配位置组成的 std::vector
         *
         * 设被比较序列S的长度为len1，比较序列T的长度为len2，则match算法执行一一比较来计算匹配位置：
         *
         * - 对S，遍历其从 0~len1-len2的位置，在每一个位置上比较
         * - 比较时，假设S的当前位置为i,则比较 S[i,i+len2-1]与T。当二者每一个字符都相等时，则匹配
         * - 将找到的每一个匹配点存入std::vector中然后返回
         *
         * >这里要求len1大于0，len2>=0(比较序列可以为空字符串)；否则抛出异常
         * >
         * >这里要求比较序列S和比较序列T的元素类型相等，否则编译失败
         *
         * 算法性能： 时间复杂度 O(m*n)，其中被比较序列S长度为n ,比较序列T长度为m
         */
        template<typename Iterator1,typename Iterator2>
        std::vector<int> match(const Iterator1 iter1_begin,const Iterator1 iter1_end,
              const Iterator2 iter2_begin,const Iterator2 iter2_end)
        {
            typedef typename std::iterator_traits<Iterator1>::value_type T1;
            typedef typename std::iterator_traits<Iterator2>::value_type T2;

            static_assert(std::is_same<T1, T2>::value,"两个序列必须包含相同类型的元素");

            auto len1=std::distance(iter1_begin,iter1_end);
            auto len2=std::distance(iter2_begin,iter2_end);
            if(len1<=0)
                throw std::invalid_argument("iter1_begin must < iter1_end");
            if(len2<0)
                throw std::invalid_argument("iter2_begin must <= iter2_end");


            std::vector<int> result;
            for(int i=0;i<=len1-len2;i++)
            {
                bool matched=true;
                for(int j=0;j<len2;j++)
                {
                    if(*(iter1_begin+i+j)!=*(iter2_begin+j))
                    {
                        matched=false;
                        break;
                    }
                }
                if(matched)
                    result.push_back(i);
            }
            return result;
        }
    }
}
#endif // MATCH

