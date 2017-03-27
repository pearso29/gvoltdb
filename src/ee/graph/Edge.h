#ifndef EDGE_H
#define EDGE_H

#include "GraphElement.h"
namespace voltdb {

class Edge 
	: public GraphElement
{
protected:
	int m_startVertexId;
	int m_endVertexId;

public:
	Edge(void);
	~Edge(void);

	int getStartVertexId();
	int getEndVertexId();
	void setStartVertexId(int id);
	void setEndVertexId(int id);
	Vertex* getStartVertex();
	Vertex* getEndVertex();
	string toString();
};

}

#endif