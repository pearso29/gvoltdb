#include "GraphElement.h"

namespace voltdb {

GraphElement::GraphElement(void)
{
}

GraphElement::GraphElement(int id, TableTuple* t, GraphView* graphView, bool remote)
{
	this->m_id = id;
	this->m_tuple = t;
	this->m_gview = graphView;
	this->m_isRemote = remote;
}


bool GraphElement::isRemote()
{
	return m_isRemote;
}


void GraphElement::setId(int id)
{
	this->m_id = id;
}

int GraphElement::getId()
{
	return this->m_id;
}

void GraphElement::setTuple(TableTuple* t) 
{
	this->m_tuple = t;
}

TableTuple* GraphElement::getTuple()
{
	return this->m_tuple;
}

GraphView* GraphElement::getGraphView()
{
	return this->m_gview;
}


void GraphElement::setGraphView(GraphView* gView)
{
	this->m_gview = gView;
}

GraphElement::~GraphElement(void)
{
}

}
