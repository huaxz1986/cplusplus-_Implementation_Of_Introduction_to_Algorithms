#ifndef KMP
#define KMP
#include<vector>
#include"util.h"
template<typename T> class KMP_Matcher
{
public:
    std::vector<unsigned> match(const std::vector<T>& S,const std::vector<T>& P)
    {
        std::cout<<"S:"<<S<<"\n";
        std::cout<<"P:"<<P<<"\n";
        std::vector<unsigned> result;
        getPi(P);
        std::cout<<pi<<"\n";
        unsigned n=S.size();
        unsigned m=P.size();
        int q=0;
        for(unsigned i=0;i<n;i++)
        {
            std::cout<<"<"<<i<<">\n";
            while(q!=0&&P[q]!=S[i])
            {
                std::cout<<"in while:q("<<q<<"),P[q]("<<P[q]<<"),"<<"S[i]("<<S[i]<<")\n";
                q=pi[q-1];
            }
            std::cout<<"out while:q("<<q<<"),P[q]("<<P[q]<<"),"<<"S[i]("<<S[i]<<")\n";
            if(P[q]==S[i])
            {
                std::cout<<"P[q]==S[i]:"<<"P[q]("<<P[q]<<"),"<<"S[i]("<<S[i]<<")\n";
                q++;
            }
            if(q==m)
            {
                result.push_back(i-(m-1));
                q=pi[q-1];
            }
            std::cout<<"</"<<i<<">\n";
        }
        return result;
    }
private:
    void getPi(const std::vector<T>&P)
    {
        std::cout<<"<getPi>\n";
        pi.clear();
        unsigned m=P.size();
        pi.resize(m);
        pi[0]=0;
        int k=0;
        for(unsigned q=1;q<m;q++)
        {
            std::cout<<"<q"<<q<<">";
            while(k!=0 && P[k]!=P[q])
            {
                std::cout<<"in while:k("<<k<<"),P[k]("<<P[k]<<"),"<<"P[q]("<<P[q]<<")\n";
                k=pi[k];
            }
            std::cout<<"out while:k("<<k<<"),P[k]("<<P[k]<<"),"<<"P[q]("<<P[q]<<")\n";
            if(P[k]==P[q])
            {
                std::cout<<"P[k]==P[q]:P[k]("<<P[k]<<"),"<<"P[q]("<<P[q]<<")\n";
                k++;
            }
            pi[q]=k;
            std::cout<<"pi["<<q<<"]="<<k<<"\n";
            std::cout<<"</q"<<q<<">"<<"\n";
        }
        std::cout<<"</getPi>\n";
    }

private:
std::vector<int> pi;
};

#endif // KMP

