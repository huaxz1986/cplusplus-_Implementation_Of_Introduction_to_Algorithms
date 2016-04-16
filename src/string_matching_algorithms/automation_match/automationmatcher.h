#ifndef AUTOMATIONMATCHER
#define AUTOMATIONMATCHER
#include<vector>
#include"util.h"
#include<assert.h>
#include<algorithm>

template<typename T> class Automation_Matcher
{
public:
    Automation_Matcher(const std::vector<T>& ele):Elements(ele){}
    std::vector<unsigned> match(const std::vector<T>& S,const std::vector<T>& P)
    {
        std::vector<unsigned> result;
        std::cout<<"S:"<<S<<"\n";
        std::cout<<"P:"<<P<<"\n";
        get_transition(P);
        printTranslation();
        unsigned n=S.size();
        unsigned m=P.size();
        unsigned q=0;
        std::cout<<"q:";
        for(unsigned i=0;i<n;i++)
        {
            q=matrix[q][index(S[i])];
            std::cout<<q<<",";
            if(q==m)
                result.push_back(i-(m-1));
        }
        std::cout<<"\n";
        return result;
    }

private:
    void clear()
    {
        matrix.clear();
    }
    void get_transition(const std::vector<T>& P)
    {
         unsigned m=P.size();
         matrix.clear();
         for(unsigned i=0;i<=m;i++)
             matrix.push_back(std::vector<unsigned>());

         for(unsigned q=0;q<m+1;q++)
         {
             //std::cout<<"<q"<<q<<">\n";
             for(unsigned j=0;j<Elements.size();j++)
             {
                 //std::cout<<"<add_"<<Elements[j]<<">\n";
                 int len=0;
                 for(int k=std::min(m,q+1);k>=0;k--)
                 {
                     if(isEnd(P,k,q,j))
                     {
                         len=k;
                         break;
                     }
                 }

                 //std::cout<<"q:"<<q<<";   add:"<<Elements[j]<<";   k:"<<len<<"\n";
                 matrix[q].push_back(len);
                 //std::cout<<"</add_"<<Elements[j]<<">\n";
             }
             //std::cout<<"</q"<<q<<">\n";
         }
    }
    bool isEnd(const std::vector<T>& P,unsigned k,unsigned q,unsigned eleIndex)
    {
//        std::cout<<"<isEnd>";
//        std::cout<<"Pk(k="<<k<<"):";
//        printP(P,k);
//        std::cout<<"Pq(q="<<q<<"):";
//        printP(P,q);
//        std::cout<<"add:"<<Elements[eleIndex]<<"\n";
        assert(k<=q+1);

        if(P[k-1]!=Elements[eleIndex])
            return false;
        for(int ki=k-2,qi=q-1;ki>=0;ki--,qi--)
        {
            if(qi<0)
                return false;
            if(P[ki]!=P[qi])
                return false;
        }
        return true;
    }
    unsigned index(const T& t)
    {
        for(unsigned i=0;i<Elements.size();i++)
            if(t==Elements[i])
                return i;
        return std::numeric_limits<unsigned>::max();
    }

private:
   void printP(const std::vector<T>&P,unsigned k)
   {
       for(unsigned i=0;i<k;i++)
           std::cout<<P[i];
       std::cout<<"\n";
   }
   void printTranslation()
   {
       std::cout<<"    "<<Elements<<"\n";
       for(unsigned i=0;i<matrix.size();i++)
       {
           std::cout<<"q="<<i<<":";
           for(unsigned j=0;j<matrix[i].size();j++)
           {
               std::cout<<matrix[i][j]<<",";
           }
           std::cout<<"\n";
       }
   }

   std::vector<T> Elements;
   std::vector<std::vector<unsigned>> matrix;
};

#endif // AUTOMATIONMATCHER

