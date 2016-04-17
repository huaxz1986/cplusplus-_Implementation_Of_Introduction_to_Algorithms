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
#ifndef MATCH_TES
#define MATCH_TES
#include"src/google_test/gtest.h"
#include"match.h"

using IntroductionToAlgorithm::StringMatchingAlgorithm::match;

//!test_regular_match：测试常规的字符串匹配算法
/*!
*
* 两组数据： 匹配字符串T为空字符串、匹配字符串T为非空字符串
*/
TEST(MatchTest,test_regular_match)
{
    {//******  测试T为空
        std::vector<int> S={90,91,92,93,94,95};
        std::vector<int> T;
        EXPECT_EQ(match(S.begin(),S.end(),T.begin(),T.end()),std::vector<int>({0,1,2,3,4,5,6}));//S[6]不存在，但是他匹配T
    }
    {//******  测试T为非空
        std::vector<int> S={90,90,90,90,90,90};
        std::vector<int> T={90,90};
        EXPECT_EQ(match(S.begin(),S.end(),T.begin(),T.end()),std::vector<int>({0,1,2,3,4}));
    }

}

#endif // MATCH_TES

