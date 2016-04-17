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
#ifndef AUTOMATONMATCH_TEST
#define AUTOMATONMATCH_TEST
#include"src/google_test/gtest.h"
#include"finiteautomatonmatch.h"
using IntroductionToAlgorithm::StringMatchingAlgorithm::index_of_M;
using IntroductionToAlgorithm::StringMatchingAlgorithm::finite_automaton_match;
using IntroductionToAlgorithm::StringMatchingAlgorithm::get_delta;
using IntroductionToAlgorithm::StringMatchingAlgorithm::is_end_with;

//!test_index_of_M：测试 index_of_M 函数
TEST(MatchTest,test_index_of_M)
{
    {
        std::vector<char> M={'a','b','c'};
        EXPECT_EQ(index_of_M(M.begin(),M.end(),'a'),0);
        EXPECT_EQ(index_of_M(M.begin(),M.end(),'b'),1);
        EXPECT_EQ(index_of_M(M.begin(),M.end(),'c'),2);
        EXPECT_THROW(index_of_M(M.begin(),M.end(),'d'),std::invalid_argument);
    }
    {
        std::vector<char> M={'a','b','c','c'};
        EXPECT_EQ(index_of_M(M.begin(),M.end(),'a'),0);
        EXPECT_EQ(index_of_M(M.begin(),M.end(),'b'),1);
        EXPECT_THROW(index_of_M(M.begin(),M.end(),'c'),std::invalid_argument);
    }
}

//!test_is_end_with：测试 is_end_with 函数
TEST(MatchTest,test_is_end_with)
{
    std::vector<int> P={2,2,2,2,2,2,2};
    for(int a=1;a<4;a++)
    {
       for(int k=0;k<P.size();k++)
           for(int q=0;q<P.size();q++)
               if(k==0) EXPECT_TRUE(is_end_with(P.begin(),P.begin()+k,P.begin()+q,a))<<"a:"<<a<<"\t k:"<<k<<"\t q:"<<q;// Pk是否是( Pq a)的后缀
               else if(a==2&&(k<=q+1)) EXPECT_TRUE(is_end_with(P.begin(),P.begin()+k,P.begin()+q,a))<<"a:"<<a<<"\t k:"<<k<<"\t q:"<<q;// Pk是否是( Pq a)的后缀
               else EXPECT_FALSE(is_end_with(P.begin(),P.begin()+k,P.begin()+q,a))<<"a:"<<a<<"\t k:"<<k<<"\t q:"<<q;// Pk是否是( Pq a)的后缀
    }
}

//!test_get_delta：测试 get_delta 函数
TEST(MatchTest,test_get_delta)
{
    //*** 算法导论图32-7  ****
    std::vector<char> M={'a','b','c'};
    std::vector<char> P={'a','b','a','b','a','c','a'};
    std::vector<std::vector<int>> delta;
    get_delta(P.begin(),P.end(),M.begin(),M.end(),delta);
    std::vector<std::vector<int>> real_delta={
    std::vector<int>({1,0,0}),std::vector<int>({1,2,0}),
    std::vector<int>({3,0,0}),std::vector<int>({1,4,0}),
    std::vector<int>({5,0,0}),std::vector<int>({1,4,6}),
    std::vector<int>({7,0,0}),std::vector<int>({1,2,0})};
    EXPECT_EQ(delta,real_delta);
}

//!test_finite_automaton_match：测试有限状态机字符串匹配算法
/*!
*
* 三组数据： 匹配字符串T为空字符串、匹配字符串T为非空字符串（同一个字符）、匹配字符串T为非空字符串（不同字符）
*/
TEST(MatchTest,test_finite_automaton_match)
{

    {//******  测试T为空
        std::vector<int> T={0,1,2,3,4,5};
        std::vector<int> P;
        std::vector<int> M={0,1,2,3,4,5};
        EXPECT_THROW(finite_automaton_match(T.begin(),T.end(),P.begin(),P.end(),M.begin(),M.end()),std::invalid_argument);
    }
    {//******  测试T为非空
        std::vector<int> T={90,90,90,90,90,90};
        std::vector<int> P={90,90};
        std::vector<int> M={90};
        EXPECT_EQ(finite_automaton_match(T.begin(),T.end(),P.begin(),P.end(),M.begin(),M.end()),std::vector<int>({0,1,2,3,4}));
    }
    {//******  测试T为非空  《算法导论图32-1》
        std::vector<char> T={'a','b','c','a','b','a','a','b','c','a','b','a','c'};
        std::vector<char> P={'a','b','a','a'};
        std::vector<char> M={'a','b','c'};
        EXPECT_EQ(finite_automaton_match(T.begin(),T.end(),P.begin(),P.end(),M.begin(),M.end()),std::vector<int>({3}));
    }
}
#endif // AUTOMATIONMATCH_TEST

