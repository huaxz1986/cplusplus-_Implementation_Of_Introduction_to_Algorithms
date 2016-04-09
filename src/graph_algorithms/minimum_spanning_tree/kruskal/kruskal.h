#ifndef KRUSKAL
#define KRUSKAL
#include"src/set_algorithms/disjoint_set/disjointset.h"
#include"../../basic_graph/graph_representation/graph/graph.h"
using IntroductionToAlgorithm::SetAlgorithm::DiskointSetNode;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        template<typename GraphType> void kruskal(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename VertexType::KeyType KeyType;
            typedef typename GraphType::EdgeTupleType EdgeTupleType;
            if(!graph)
                throw std::invalid_argument("kruskal error: graph must not be nullptr!");
            std::shared_ptr<DiskointSetNode> sets[GraphType::NUM];

            for(int i=0;i<GraphType::NUM;i++)
            {
                auto vertex=graph->vertexes.at(i);
                if(vertex) //添加顶点到`disjoint_set`中
                {
                    sets[vertex->id]=std::make_shared<DiskointSetNode>(vertex);
                    DiskointSetNode<VertexType>::make_set(sets[vertex->id]);
                }
            }
            GraphType::EWeightType weight=0;
            auto edges=graph->edge_tuples();
            std::sort(edges.begin(),edges.end(),
               [](const EdgeTupleType&edge1,const EdgeTupleType&edge2)->bool{ return std::get<2>(edge1)<std::get<2>(edge2);});
            for(const auto&edge:edges)
            {
                auto from_id=std::get<0>(edge);
                auto to_id=std::get<1>(edge);
                auto edge_weight=std::get<2>(edge);
                auto from_vertex=graph->vertexes.at(from_id);
                auto to_vertex=graph->vertexes.at(to_id);
                if(DiskointSetNode::find_set(sets[from_id])!=DiskointSetNode::find_set(sets[to_id_id]))
                {
                        DiskointSetNode::union_set(sets[from_id],sets[to_id_id]);
                        weight+=edge_weight;
                }

            }
        }
    }
}


#endif // KRUSKAL

