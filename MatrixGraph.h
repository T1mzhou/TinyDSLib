#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "Graph.h"

namespace DSLib
{

template < int N, typename V, typename E >
class MatrixGraph : public Graph<V, E>
{
public:

protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
};

}
#endif // !__MATRIXGRAPH_H__