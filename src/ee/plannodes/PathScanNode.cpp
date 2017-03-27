/*
 * PathScan.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: msaberab
 */

#include "PathScanNode.h"
#include "graph/GraphView.h"
#include "execution/VoltDBEngine.h"
#include "graph/GraphViewCatalogDelegate.h"

using namespace std;

namespace voltdb
{

PathScanPlanNode::PathScanPlanNode() {

}

PathScanPlanNode::~PathScanPlanNode() {
	// TODO Auto-generated destructor stub
}

PlanNodeType PathScanPlanNode::getPlanNodeType() const { return PLAN_NODE_TYPE_PATHSCAN; }

std::string PathScanPlanNode::debugInfo(const string& spacer) const
{
    std::ostringstream buffer;
    buffer << "PathScan Plan Node";
    return buffer.str();
}

GraphView* PathScanPlanNode::getTargetGraphView() const
{
	if (m_gcd == NULL)
	{
		return NULL;
	}
	return m_gcd->getGraphView();
}

void PathScanPlanNode::loadFromJSONObject(PlannerDomValue obj)
{
	m_target_graph_name = obj.valueForKey("TARGET_GRAPH_NAME").asStr();
	startVertexId = obj.valueForKey("STARTVERTEX").asInt();
	endVertexId = obj.valueForKey("ENDVERTEX").asInt();

	m_isEmptyScan = obj.hasNonNullKey("PREDICATE_FALSE");

	// Set the predicate (if any) only if it's not a trivial FALSE expression
	if (!m_isEmptyScan)
	{
		m_predicate.reset(loadExpressionFromJSONObject("PREDICATE", obj));
	}

	m_isSubQuery = obj.hasNonNullKey("SUBQUERY_INDICATOR");

	if (m_isSubQuery) {
		m_gcd = NULL;
	} else
	{
		VoltDBEngine* engine = ExecutorContext::getEngine();
		m_gcd = engine->getGraphViewDelegate(m_target_graph_name);
		if ( ! m_gcd) {
			VOLT_ERROR("Failed to retrieve target graph view from execution engine for PlanNode '%s'",
			debug().c_str());
				//TODO: throw something
		}
		else
		{
			std::stringstream paramsToPrint;
			paramsToPrint << "Target graph view name = " << m_gcd->getGraphView()->name()
					<< ", StartVertexId = " << startVertexId << ", EndVertexId = " << endVertexId;

			LogManager::GLog("PathScanPlanNode", "loadFromJSONObject", 72, paramsToPrint.str());
		}
	}

}

}