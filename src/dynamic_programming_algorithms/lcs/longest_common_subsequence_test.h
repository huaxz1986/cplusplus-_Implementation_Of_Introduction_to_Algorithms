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
#ifndef LONGESTCOMMONSUBSEQUENCE_TEST
#define LONGESTCOMMONSUBSEQUENCE_TEST
#include"src/google_test/gtest.h"
#include"longest_common_subsequence.h"
#include<string>
using IntroductionToAlgorithm::DynamicProgrammingAlgorithm::longest_common_subsequence;
//!longest_common_subsequence_test：测试最长公共子数组
/*!
*
* 三组数据： s1为空字符串s2为非空字符串、s1和s2为常规字符串且二者内容不等、s1和s2为常规字符串且二者内容相等
*/
TEST(test_longest_common_subsequence, test1)
{

    {
        std::string s1;
        std::string s2("abcdefg");
        std::string result(s2);
        auto length=longest_common_subsequence(s1.begin(),s1.end(),s2.begin(),s2.end(),result.begin());
        result.resize(length);
        EXPECT_EQ(length,0);
    }
    {
        std::string s1("ABCBDAB");
        std::string s2("BDCABA");
        std::string result(s1);
        auto length=longest_common_subsequence(s1.begin(),s1.end(),s2.begin(),s2.end(),result.begin());
        result.resize(length);
        EXPECT_EQ(result,std::string("BCBA"));
    }
    {
        std::string s1("ABCDEFGHIJ");
        std::string s2("ABCDEFGHIJ");
        std::string result(s1);
        auto length=longest_common_subsequence(s1.begin(),s1.end(),s2.begin(),s2.end(),result.begin());
        result.resize(length);
        EXPECT_EQ(result,std::string("ABCDEFGHIJ"));
    }
}
#endif // LONGESTCOMMONSUBSEQUENCE_TEST

