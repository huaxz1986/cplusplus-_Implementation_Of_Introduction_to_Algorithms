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
#ifndef ROBIN_KARPMATCH_TEST
#define ROBIN_KARPMATCH_TEST
#include"src/google_test/gtest.h"
#include"rabinkarpmatch.h"

using IntroductionToAlgorithm::StringMatchingAlgorithm::rabin_karp_match;
using IntroductionToAlgorithm::StringMatchingAlgorithm::get_h;

//!test_get_h：测试 get_h 函数
TEST(MatchTest,test_get_h)
{
    EXPECT_EQ(get_h(1,10,3),1) ;// 1^(10-1) mod (3) == 1
    EXPECT_EQ(get_h(10,1,3),1) ;// 10^(1-1) mod (3) == 1
    EXPECT_EQ(get_h(10,2,3),1) ;// 10^(2-1) mod (3) == 1
    EXPECT_EQ(get_h(10,3,8),4) ;// 10^(3-1) mod (8) == 4
    EXPECT_THROW(get_h(10,0,3),std::invalid_argument) ;// 10^(2-1) mod (3) == 1
}

//!test_rabin_karp_match：测试rabin_karp_match字符串匹配算法
/*!
*
* 两组数据： 匹配字符串T为空字符串、匹配字符串T为非空字符串
*/
TEST(MatchTest,test_rabin_karp_match)
{

    {//******  测试T为空
        std::vector<int> S={0,1,2,3,4,5};
        std::vector<int> T;
        EXPECT_THROW(rabin_karp_match(S.begin(),S.end(),T.begin(),T.end(),100,97),std::invalid_argument);
    }
    {//******  测试T为非空
        std::vector<int> S={90,90,90,90,90,90};
        std::vector<int> T={90,90};
        EXPECT_EQ(rabin_karp_match(S.begin(),S.end(),T.begin(),T.end(),100,97),std::vector<int>({0,1,2,3,4}));
    }
}

#endif // ROBIN_KARPMATCH_TEST

