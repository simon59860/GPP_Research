#pragma once

namespace Elite 
{
	template <class T_NodeType, class T_ConnectionType>
	class BFS
	{
	public:
		BFS(IGraph<T_NodeType, T_ConnectionType>* pGraph);

		std::vector<T_NodeType*> FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode);
	private:
		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
	};

	template <class T_NodeType, class T_ConnectionType>
	BFS<T_NodeType, T_ConnectionType>::BFS(IGraph<T_NodeType, T_ConnectionType>* pGraph)
		: m_pGraph(pGraph)
	{

	}

	template <class T_NodeType, class T_ConnectionType>
	std::vector<T_NodeType*> BFS<T_NodeType, T_ConnectionType>::FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode)
	{
		std::queue<T_NodeType*> openList{};
		std::unordered_map<T_NodeType*, T_NodeType*> closedList{};

		openList.push(pStartNode);

		T_NodeType* pCurrentNode{};

		while (!openList.empty())
		{
			pCurrentNode = openList.front();

			// check if reached destination
			if (pCurrentNode == pDestinationNode)
			{
				break;
			}

			openList.pop();

			// add connections to open list
			for (auto& connection : m_pGraph->GetNodeConnections(pCurrentNode))
			{
				T_NodeType* pNode = m_pGraph->GetNode(connection->GetTo());

				if (closedList.find(pNode) == closedList.end()) //not found
				{
					openList.push(pNode);
					closedList.emplace(pNode, pCurrentNode);
				}
			}
		}

		// check if found node
		if (openList.empty()) // if found, pop won't be executed, so size will be 1
		{
			return std::vector<T_NodeType*>();
		}

		// backtrack path
		std::vector<T_NodeType*> path{};
		pCurrentNode = pDestinationNode;
		while (pCurrentNode != pStartNode)
		{
			path.push_back(pCurrentNode);
			pCurrentNode = closedList[pCurrentNode];
		}

		path.push_back(pStartNode); //loop exits before adding startnode

		std::reverse(path.begin(), path.end());

		return path;
	}
}

