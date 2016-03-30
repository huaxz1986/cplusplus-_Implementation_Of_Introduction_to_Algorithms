#ifndef LONGESTCOMMONSUBSEQUENCE_TEST
#define LONGESTCOMMONSUBSEQUENCE_TEST
#include"src/google_test/gtest.h"
#include"src/dynamic_programmitn_algorithms/longest_common_subsequence.h"
#include<string>
TEST(test_longest_common_subsequence, test1)
{
    using IntrodunctionToAlgorithm::DynamicProgrammingAlgorithm::longest_common_subsequence;
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

