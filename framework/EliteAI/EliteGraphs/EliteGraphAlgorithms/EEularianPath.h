#pragma once
#include <stack>

namespace Elite
{
	enum class Eulerianity
	{
		notEulerian,
		semiEulerian,
		eulerian,
	};

	template <class T_NodeType, class T_ConnectionType>
	class EulerianPath
	{
	public:

		EulerianPath(IGraph<T_NodeType, T_ConnectionType>* pGraph);

		Eulerianity IsEulerian() const;
		std::vector<T_NodeType*> FindPath(Eulerianity& eulerianity) const;

	private:
		void VisitAllNodesDFS(int startIdx, std::vector<bool>& visited) const;
		bool IsConnected() const;

		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
	};

	template<class T_NodeType, class T_ConnectionType>
	inline EulerianPath<T_NodeType, T_ConnectionType>::EulerianPath(IGraph<T_NodeType, T_ConnectionType>* pGraph)
		: m_pGraph(pGraph)
	{
	}

	template<class T_NodeType, class T_ConnectionType>
	inline Eulerianity EulerianPath<T_NodeType, T_ConnectionType>::IsEulerian() const
	{

		// If the graph is not connected, there can be no Eulerian Trail
		if (!IsConnected())
		{
			return Eulerianity::notEulerian;
		}

		// Count nodes with odd degree 
		auto nodes = m_pGraph->GetAllNodes();
		int oddCount = 0;
		for (auto n : nodes)
		{
			auto connections = m_pGraph->GetNodeConnections(n);
			if (connections.size() & 1)
			{
				++oddCount;
			}
		}


		// A connected graph with more than 2 nodes with an odd degree (an odd amount of connections) is not Eulerian
		if (oddCount > 2)
		{
			return Eulerianity::notEulerian;
		}

		// A connected graph with exactly 2 nodes with an odd degree is Semi-Eulerian (unless there are only 2 nodes)
		// An Euler trail can be made, but only starting and ending in these 2 nodes
		if (oddCount == 2 && nodes.size() != 2)
		{
			return Eulerianity::semiEulerian;
		}

		// A connected graph with no odd nodes is Eulerian
		if (oddCount == 0)
		{
			return Eulerianity::eulerian;
		}

		//not possible to have 1 odd, so this will never happen
		return Eulerianity::notEulerian;
	}

	template<class T_NodeType, class T_ConnectionType>
	inline std::vector<T_NodeType*> EulerianPath<T_NodeType, T_ConnectionType>::FindPath(Eulerianity& eulerianity) const
	{
		// Get a copy of the graph because this algorithm involves removing edges
		auto graphCopy = m_pGraph->Clone();
		auto path = std::vector<T_NodeType*>();
		int nrOfNodes = graphCopy->GetNrOfNodes();

		// Check if there can be an Euler path
		// If this graph is not eulerian, return the empty path
		// Else we need to find a valid starting index for the algorithm
		std::stack<int> nodeStack;
		auto nodes{ m_pGraph->GetAllNodes() };

		switch (eulerianity)
		{
		case Eulerianity::eulerian:
			nodeStack.push(0);
			break;
		case Eulerianity::semiEulerian:
			for (auto node : nodes)
			{
				if (graphCopy->GetNodeConnections(node).size() & 1)
				{
					nodeStack.push(node->GetIndex());
					break;
				}
			}
			break;
		case Eulerianity::notEulerian:
			return path;
			break;
		}

		// Start algorithm loop
		
		while (nodeStack.size() > 0)
		{
			auto connections{ graphCopy->GetNodeConnections(nodes[nodeStack.top()]) };
			if (connections.size() == 0)
			{
				path.push_back(nodes[nodeStack.top()]);
				nodeStack.pop();
			}
			else
			{
				int connectedNodeId{ connections.front()->GetTo() };
				graphCopy->RemoveConnection(connections.front());
				nodeStack.push(connectedNodeId);
			}
		}
		

		std::reverse(path.begin(), path.end()); // reverses order of the path
		return path;
	}

	template<class T_NodeType, class T_ConnectionType>
	inline void EulerianPath<T_NodeType, T_ConnectionType>::VisitAllNodesDFS(int startIdx, std::vector<bool>& visited) const
	{
		// mark the visited node
		visited[startIdx] = true;

		// recursively visit any valid connected nodes that were not visited before
		for (T_ConnectionType* connection : m_pGraph->GetNodeConnections(startIdx))
		{
			if (visited[connection->GetTo()] == false)
			{
				VisitAllNodesDFS(connection->GetTo(), visited);
			}
		}

	}

	template<class T_NodeType, class T_ConnectionType>
	inline bool EulerianPath<T_NodeType, T_ConnectionType>::IsConnected() const
	{
		auto nodes = m_pGraph->GetAllNodes();
		vector<bool> visited(m_pGraph->GetNrOfNodes(), false);

		// find a valid starting node that has connections
		if (nodes.size() == 0)
		{
			return false;
		}

		if (nodes.size() > 1 && m_pGraph->GetAllConnections().size() == 0)
		{
			return false;
		}

		int connectedId = invalid_node_index;

		if (m_pGraph->GetNodeConnections(nodes[0]).size() == 0)
		{
			return false;
		}
		else
		{
			connectedId = nodes[0]->GetIndex();
		}


		/*for (auto n : nodes)
		{
			auto connections = m_pGraph->GetNodeConnections(n);
			if (connections.size() != 0)
			{
				connectedId = n->GetIndex();
				break;
			}
		}*/
		
		// if no valid node could be found, return false
		if (connectedId == invalid_node_index)
		{
			return false;
		}

		// start a depth-first-search traversal from the node that has at least one connection
		VisitAllNodesDFS(connectedId, visited);

		// if a node was never visited, this graph is not connected
		for (auto n : nodes)
		{
			if (visited[n->GetIndex()] == false)
			{
				return false;
			}
		}

		return true;
	}

}