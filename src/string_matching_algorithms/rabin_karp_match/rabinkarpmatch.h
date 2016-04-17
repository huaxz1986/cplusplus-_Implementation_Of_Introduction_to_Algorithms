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
#ifndef ROBIN_KARPMATCH
#define ROBIN_KARPMATCH
#include<type_traits>
#include<vector>

namespace IntroductionToAlgorithm {
    namespace StringMatchingAlgorithm{

        //! get_h： rabin_karp匹配算法的 get_h 操作，算法导论第32章32.2节
         /*!
         * \param radix_d : 基数，一般选取大于等于序列最大值的一个整数
         * \param len_m:  用于指数计算的m
         * \param mod_q : 取模的质数
         * \return: radix_d的(len_m-1)次方再取模mod_q
         *
         * 要求`radix_q`、`len_m`、`mod_q`都非0.若有任何一个为0则抛出异常。
         */
        template<typename T>   T get_h(T  radix_d,T  len_m,T  mod_q)
        {
            static_assert(std::is_integral<T>::value, "get_h error:type T must be integer!");

            if(len_m==0) throw std::invalid_argument("get_h error: len_m must >=1 !");
            if(radix_d==0) throw std::invalid_argument("get_h error: radix_d must >=1 !");
            if(mod_q==0) throw std::invalid_argument("get_h error: mod_q must >=1 !");
            T result=1;
            for(int i=0;i<len_m-1;i++)
                result=result*radix_d % mod_q;
            return result;
        }

         //! rabin_karp_match： rabin_karp字符串匹配算法，算法导论第32章32.2节
         /*!
         * \param iterT_begin : 被文本序列T的起始迭代器
         * \param iterT_end: 文本序列T的终止迭代器
         * \param iterP_begin : 模式序列P的起始迭代器
         * \param iterP_end: 模式序列P的终止迭代器
         * \param radix_d: 数字基数（有限字母集合M的字符个数）
         * \param mod_q: 用于取模的质数
         * \return: 有效偏移组成的 std::vector
         *
         * ## 字符串匹配
         *
         * 字符串匹配的形式化定义如下：假设文本是一个长度为n的数组 T[1...n]，而模式是一个长度为m的数组P[1...m]，
         * 其中m<=n。进一步假设P和T的元素都是来自一个有限字母集合M的字符。如M={0,1}或者M={a,b,c,...z}。
         * 字符数组P和T通常称为字符串。
         *
         * ## rabin_karp 字符串匹配算法
         *
         * ### 算法原理
         *
         * 假设 M={0,1,2,3...,9}，这样每个字符都是十进制数字。我们可以用长度为k的十进制数来表示由
         * k个连续的字符组成的字符串。
         *
         * 给定一个模式P[1...m]，假设p为它对应的十进制数值。给定一个文本T[1...n]，假设t_s表示长度为
         * m的字符串T[s+1,...s+m]所对应的十进制值，其中s=0,1,...,n-m。则当且仅当
         * T[s+1,...s+m]=P[1...m]时有p=t_s。则总能够在O(m)时间内计算出p的值，
         * 在O(n-m+1)时间内计算所有t_s的值。则通过比较p和每一个t_s的值，能在O(m)+O(n-m+1)=O(n)
         * 时间内计算出所有的有效偏移。
         * > 通常假定每个字符都是以d为基数表示的数字，其中d=|M|，表示有限字母集合M的大小
         *
         * 可以利用霍纳法则在O(m)时间内计算出p与t_0:
         *
         * - p=P[m]+10(P[m-1]+10(P[m-2]+...+10(P[2]+10P[1])...))
         * - t_0=T[m]+10(T[m-1]+10(T[m-2]+...+10(T[2]+10T[1])...))
         *
         * 然后在O(n-m)内计算出t_1、t_2、...t_<n-m>: t_<s+1>=10(t_s-10^(m-1)*T[s+1])+T[s+m+1]
         *
         * 但是有可能p和t_s的值太大，导致不方便对其进行操作。如果P包含m各字符，那么p(m位数)上 每次算术运算需要
         * “常数”时间这一假设就不成立。我们可以选择一个合适的模q来计算p和t_s的模。
         * 我们可以在O(m)时间内计算出模q的p值，然后在O(n-m+1)时间内计算出模q的所有t_s值。
         * 另 h = d^(m-1)(mod q) ，则：
         * t_<s+1>=(d(t_s-T[s+1]h)+T[s+m+1]) mod q
         *
         * 但是基于模q得出的结果： t_s = p (mod q) 并不能说明 t_s=p。我们对于这样的s称为伪命中点，
         * 还需要进一步检测条件 P[1...m]=T[s+1,...s+m] 成立
         *
         * ### 算法步骤
         *
         * - 初始化：计算 p 和 t_0
         * - 遍历 s从0到n-m(包含n-m)：
         *      - 找到所有的p=t_s的偏移s，检查若P[1...m]=T[s+1,...s+m]，则将结果s放入结果std::vector中
         * - 返回结果std::vector
         *
         * >这里要求n>=0，m>0；否则抛出异常
         * >
         * >这里要文本序列T和模式序列P的元素类型相等，否则编译失败
         *
         *
         * ### 算法性能
         *
         * rabin_karp 匹配算法的预处理时间为O(m)，最坏情况下的运行时间为O((n-m+1)m)，
         * 在平均情况下他的运行时间还是比较好的
         *
         */
        template<typename IteratorT,typename IteratorP>
        std::vector<int> rabin_karp_match(const IteratorT iterT_begin,const IteratorT iterT_end,
              const IteratorP iterP_begin,const IteratorP iterP_end,unsigned radix_d,unsigned mod_q)
        {
            typedef typename std::iterator_traits<IteratorT>::value_type T1;
            typedef typename std::iterator_traits<IteratorP>::value_type T2;

            static_assert(std::is_same<T1, T2>::value,"rabin_karp_match error:sequence T and P must contain same type value!");
            static_assert(std::is_integral<T1>::value, "rabin_karp_match error:sequence element must be integer!");

            auto len_T=std::distance(iterT_begin,iterT_end);
            auto len_P=std::distance(iterP_begin,iterP_end);
            if(len_T<=0)
                throw std::invalid_argument("rabin_karp_match error:iterT_begin must <= iterT_end");
            if(len_P<=0)
                throw std::invalid_argument("rabin_karp_match error:iterP_begin must <= iterP_end");


            std::vector<int> result;
            if(len_T<len_P) //模式串P较长，直接返回
                return result;

            //************** 初始化，计算p和 t_0 **************
            int p=0;
            int t_0=0;
            for(int i=0;i<len_P;i++)
            {
                p=(radix_d*p+*(iterP_begin+i))%mod_q;
                t_0=(radix_d*t_0+*(iterT_begin+i))%mod_q;
            }
            //************* 遍历匹配   ****************
            auto t_s=t_0;
            auto h=get_h<unsigned>(radix_d,len_P,mod_q);
            for(int s=0;s<=len_T-len_P;s++)
            {
                if(p==t_s) //伪命中点
                {
                    //********* 一一匹配  **********
                    bool matched=true;
                    for(int j=0;j<len_P;j++)
                    {
                        if(*(iterT_begin+s+j)!=*(iterP_begin+j))
                        {
                            matched=false;
                            break;
                        }
                    }
                    if(matched)
                        result.push_back(s);
                }
                if(s<len_T-len_P) //当 s!=n-m时，向后递推
                    t_s=(radix_d*(t_s+*(iterT_begin+s)*h*(mod_q-1))+*(iterT_begin+s+len_P))%mod_q;//注意负溢出
            }
            return result;
        }
    }
}
#endif // ROBIN_KARPMATCH

