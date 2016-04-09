#ifndef PRIM
#define PRIM
#include"../../basic_graph/graph_representation/graph/graph.h"
#include"src/queue_algorithms/min_queue/minqueue.h"
using IntroductionToAlgorithm::QueueAlgorithm::MinQueue;
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {
        template<typename GraphType> void prim(std::shared_ptr<GraphType> graph,typename GraphType::VIDType source_id)
        {
            typedef typename GraphType::VertexType VertexType;
            typedef typename VertexType::KeyType KeyType;
            if(!graph)
                throw std::invalid_argument("prim error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("prim error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            auto vertex_compare=[](std::shared_ptr<VertexType> first,std::shared_ptr<VertexType> second){return first->key<second->key;};
            auto vertex_key_get=[](std::shared_ptr<VertexType> v)->double& {return v->key;};
            MinQueue<VertexType,KeyType> min_queue(vertex_compare,vertex_key_get);

            graph->vertexes.at(source_id)->key=0;
            for(int i=0;i<GraphType::NUM;i++)
            {
                if(graph->vertexes.at(i)) //添加顶点到最小优先级队列中
                    min_queue.insert(graph->vertexes.at(i));
            }

            GraphType::EWeightType weight=0;
            while(!min_queue.is_empty())
            {
                auto minNode=min_queue.extract_min();
                auto edges =graph->vertex_edge_tuples(minNode->id);//      graph.edges(minNode->id);
                for(auto& edge_tuple:edges)
                {
                    auto another_id=std::get<1>(edge_tuple);
                    auto another_vertex=graph->vertexes.at(another_id);
                    auto edge_weight=std::get<2>(edge_tuple);

                    if(min_queue.is_inqueue(another_vertex)&& edge_weight<another_vertex->key)
                    {
                        another_vertex->parent=minNode;
                        another_vertex->key=edge_weight;
                    }
                }
                weight+=minNode->key;
            }
            return weight;
        }
    }
}
#endif // PRIM

