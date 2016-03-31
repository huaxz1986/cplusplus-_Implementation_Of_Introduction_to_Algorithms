#ifndef LONGESTCOMMONSUBSEQUENCE_TEST
#define LONGESTCOMMONSUBSEQUENCE_TEST
#include"src/google_test/gtest.h"
#include"longest_common_subsequence.h"
#include<string>
using IntrodunctionToAlgorithm::DynamicProgrammingAlgorithm::longest_common_subsequence;
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

