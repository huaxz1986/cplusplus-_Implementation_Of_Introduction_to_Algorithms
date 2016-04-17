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
#ifndef KMP_TEST
#define KMP_TEST
#include"src/google_test/gtest.h"
#include"kmp.h"
using IntroductionToAlgorithm::StringMatchingAlgorithm::get_pai;
using IntroductionToAlgorithm::StringMatchingAlgorithm::kmp_match;

//!test_get_pai：测试 get_pai 函数
TEST(MatchTest,test_get_pai)
{
    //*** 算法导论图32-11  ****
    std::vector<char> P={'a','b','a','b','a','c','a'};
    std::vector<int> real_pai={0,0,1,2,3,0,1};
    EXPECT_EQ(get_pai(P.begin(),P.end()),real_pai);
}

//!test_kmp_match：测试KMP字符串匹配算法
/*!
*
* 三组数据： 匹配字符串T为空字符串、匹配字符串T为非空字符串（同一个字符）、匹配字符串T为非空字符串（不同字符）
*/
TEST(MatchTest,test_kmp_match)
{

    {//******  测试T为空
        std::vector<int> T={0,1,2,3,4,5};
        std::vector<int> P;
        EXPECT_THROW(kmp_match(T.begin(),T.end(),P.begin(),P.end()),std::invalid_argument);
    }
    {//******  测试T为非空
        std::vector<int> T={90,90,90,90,90,90};
        std::vector<int> P={90,90};
        EXPECT_EQ(kmp_match(T.begin(),T.end(),P.begin(),P.end()),std::vector<int>({0,1,2,3,4}));
    }
    {//******  测试T为非空  《算法导论图32-1》
        std::vector<char> T={'a','b','c','a','b','a','a','b','c','a','b','a','c'};
        std::vector<char> P={'a','b','a','a'};
        EXPECT_EQ(kmp_match(T.begin(),T.end(),P.begin(),P.end()),std::vector<int>({3}));
    }
}

#endif // KMP_TEST

