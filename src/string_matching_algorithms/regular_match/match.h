
#ifndef MATCH
#define MATCH
#include<vector>

namespace IntroductionToAlgorithm {
    namespace StringMatchingAlgorithm{

        //! match： 朴素字符串匹配算法，算法导论第32章,32.1节
        /*!
         * \param iterT_begin : 被文本序列T的起始迭代器
         * \param iterT_end: 文本序列T的终止迭代器
         * \param iterP_begin : 模式序列P的起始迭代器
         * \param iterP_end: 模式序列P的终止迭代器
         * \return: 有效偏移组成的 std::vector
         *
         * ## 字符串匹配
         *
         * 字符串匹配的形式化定义如下：假设文本是一个长度为n的数组 T[1...n]，而模式是一个长度为m的数组P[1...m]，
         * 其中m<=n。进一步假设P和T的元素都是来自一个有限字母集合M的字符。如M={0,1}或者M={a,b,c,...z}。
         * 字符数组P和T通常称为字符串。
         *
         * ## 朴素字符串匹配算法
         *
         * ### 算法原理
         *
         * 朴素字符串匹配算法是通过一个循环找到所有的有效偏移，该循环对n-m+1各可能的偏移值s进行检查，
         * 看是否满足条件 P[1...m]=T[s+1,...s+m]。
         *
         * ### 算法步骤
         *
         * - 对T，遍历其从 0~n-m 的位置，在每一个位置上比较
         * - 比较时，设当前偏移为s,则比较 T[s+1,s+2,...s+m]与P[1...m]。当二者每一个字符都相等时，则匹配
         * - 将找到的有效偏移存入std::vector中然后返回
         *
         * >这里要求n>=0，m>=0(模式序列可以为空字符串)；否则抛出异常
         * >
         * >这里要文本序列T和模式序列P的元素类型相等，否则编译失败
         *
         *
         * ### 算法性能
         *
         * 朴素字符串匹配算法的时间复杂度 O(m*n)
         *
         */
        template<typename IteratorT,typename IteratorP>
        std::vector<int> match(const IteratorT iterT_begin,const IteratorT iterT_end,
              const IteratorP iterP_begin,const IteratorP iterP_end)
        {
            typedef typename std::iterator_traits<IteratorT>::value_type T1;
            typedef typename std::iterator_traits<IteratorP>::value_type T2;

            static_assert(std::is_same<T1, T2>::value,"match error:sequence T and P must contain same type value!");

            auto lenT=std::distance(iterT_begin,iterT_end);
            auto lenP=std::distance(iterP_begin,iterP_end);
            if(lenT<0)
                throw std::invalid_argument("match error:iterT_begin must <= iterT_end");
            if(lenP<0)
                throw std::invalid_argument("match error:iterP_begin must <= iterP_end");


            std::vector<int> result;
            for(int i=0;i<=lenT-lenP;i++)
            {
                bool matched=true;
                for(int j=0;j<lenP;j++)
                {
                    if(*(iterT_begin+i+j)!=*(iterP_begin+j))
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

