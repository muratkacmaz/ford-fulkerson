/*
Murat Kaçmaz
150140052
*/
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <stack>
#include <iterator>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;
int i = 0;
class Node {

public : 
	int id;
	bool visited;
	Node() { visited = false; id = i; i++; };
	list<Node*> adj;
};



class Graph {
public:
	vector<Node*> nodeList;
	Node * head;
	Graph() {  };
	void edgeConnection(int, int);
	int dfs(int,int);

	int fordFulkerson(int , int);
};

void Graph::edgeConnection(int i, int j)   // directed graphs
{
	nodeList[i]->adj.push_back(nodeList[j]);
    nodeList[j]->adj.push_back(nodeList[i]);
}

int Graph::dfs(int s, int t)
{
	stack<Node*> stack;
	Node* temp = new Node;
	Node* v = new Node;
	int reachedSink = 0;
	list<Node*> ::iterator inList;

	for (int i = 0; i <= t; i++)
	{
		nodeList[i]->visited = false;
	}

	stack.push(nodeList[s]);
	nodeList[s]->visited = true;

	while (!stack.empty())
	{
		temp = stack.top();
		temp->visited = true;
		stack.pop();

		if (temp == nodeList[t]) { return ++reachedSink; }
		
		for (inList = temp->adj.begin(); inList != temp->adj.end(); inList++)
		{
			v = *inList;
			if (v->visited == false)
			{
				stack.push(*inList);	
			}
		}
	}
	return reachedSink;
}
 
int Graph::fordFulkerson(int s , int t)
{
	Node* temp = new Node;
	Node* v = new Node;
	list<Node*> ::iterator inList;
	int deletedNodeNumber = 0;
	
	while (dfs(s, t) > 0)    // dfs checks that if there is a way from source to sink
	{
		for (int i = s; i <= t; i++)  
		{
			temp = nodeList[i];
			if (temp->visited == true)
			{
				for (inList = temp->adj.begin(); inList != temp->adj.end(); inList++)
				{
					v = *inList;
					
					if (v->visited == true)
					{
						temp->adj.remove(v);
						temp->visited = false;
						break;    // 1 eleman silinicek sadece
					}
				}
			}
		}
		if (nodeList[s]->adj.size() == 0)  // source tarafýnda 1 tane eleman kalmamasý icin 2ye geciyor
		{
			s++;
		}
	}
	 
	//tersten gelmeliii
	for (int i = t; i >= s; i--)
	{
		temp = nodeList[i];
		for (inList = temp->adj.begin(); inList != temp->adj.end(); inList++)   
		{
			v = *inList;
			if (v == nodeList[s])      
			{
				delete nodeList[i];
				deletedNodeNumber++;
				break;
			}

		}

	}
	if (nodeList.size() - deletedNodeNumber < 3)
		return 0;

	else
		return deletedNodeNumber;
	 
}

int main(int argc, char* argv[])
{
	ifstream fileRead;
	fileRead.open(argv[1]);
	string totalNodes, totalEdges;
	string lineRead;
	Graph graph;
	
	getline(fileRead, lineRead);
	istringstream iss(lineRead);
	getline(iss, totalNodes, ' ');
	getline(iss, totalEdges, ' ');

	int ttotalNodes = atoi(totalNodes.c_str());
	int ttotalEdges = atoi(totalEdges.c_str());
	
	for (int i = 0; i <ttotalNodes; i++)
	{
		Node* newNode = new Node;
		graph.nodeList.push_back(newNode);
	}

	string edge1, edge2;
	while (getline(fileRead, lineRead))
	{
		istringstream iss(lineRead);
		 
		getline(iss, edge1, ' ');
		getline(iss, edge2, ' ');

		int e1 = atoi(edge1.c_str());
		int e2 = atoi(edge2.c_str());

		graph.edgeConnection(e1 - 1, e2 - 1);
	}

	cout << graph.fordFulkerson(0, (ttotalNodes-1));



	getchar();
	return 0;
}

