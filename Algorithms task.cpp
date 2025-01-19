//1-dfs
#include <iostream>
using namespace std;

const int MAX_N = 100; 


int state[MAX_N];
int dfs_number[MAX_N];
int finish_number[MAX_N];
int parent[MAX_N];
int adj[MAX_N][MAX_N];
int dfs_counter = 0;
int finish_counter = 0;
int n, m;

// دالة DFS
void dfs(int v) {
    state[v] = 1;
    dfs_number[v] = dfs_counter++;

    for (int i = 0; i < n; ++i) {
        if (adj[v][i] == 1 && state[i] == 0) { 
            parent[i] = v; 
            dfs(i);
        }
    }

    state[v] = 2; 
    finish_number[v] = finish_counter++;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        state[i] = 0;
        dfs_number[i] = -1;
        finish_number[i] = -1;
        parent[i] = -1;
        for (int j = 0; j < n; ++j) {
            adj[i][j] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            dfs(i);
        }
    }
    cout << "DFS Numbers: ";
    for (int i = 0; i < n; ++i) {
        cout << dfs_number[i] << " ";
    }
    cout << "\nFinish Numbers: ";
    for (int i = 0; i < n; ++i) {
        cout << finish_number[i] << " ";
    }
    cout << "\nParent Array: ";
    for (int i = 0; i < n; ++i) {
        cout << parent[i] << " ";
    }
    cout << endl;
    return 0;
}



//2-scs 
#include <iostream>
#include <vector>
using namespace std;

// Function to perform DFS on the graph
bool dfs(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

// Function to check if the directed graph is strongly connected
bool isStronglyConnected(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);

    // Perform DFS from the first node
    dfs(graph, 0, visited);

    // Check if all nodes were visited
    for (bool v : visited) {
        if (!v) {
            return false; // Not strongly connected
        }
    }

    // Create the reverse graph
    vector<vector<int>> reverseGraph(n);
    for (int i = 0; i < n; i++) {
        for (int j : graph[i]) {
            reverseGraph[j].push_back(i);
        }
    }

    // Reset visited array for the second DFS
    fill(visited.begin(), visited.end(), false);

    // Perform DFS on the reverse graph
    dfs(reverseGraph, 0, visited);

    // Check if all nodes were visited in the reverse graph
    for (bool v : visited) {
        if (!v) {
            return false; // Not strongly connected
        }
    }

    return true; // The graph is strongly connected
}

int main() {
    // Example usage
    vector<vector<int>> graph = {
        {1},    // Node 0 -> Node 1
        {2},    // Node 1 -> Node 2
        {0},    // Node 2 -> Node 0
        {4},    // Node 3 -> Node 4
        {3}     // Node 4 -> Node 3
    };

    if (isStronglyConnected(graph)) {
        cout << "The graph is strongly connected." << endl;
    } else {
        cout << "The graph is not strongly connected." << endl;
    }

    return 0;
}

//3-Melhorn gabow


#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class GabowScc
{
vector<vector<int>> adjacencyList;
vector<int> discoveryTime, lowLink;
vector<bool> visited;
stack<int> Qstack, Rstack;
int counter, numscc;
vector<vector<int>> scccomponents;

  public:
GabowScc(int Vertices)
{
  adjacencyList.resize(Vertices);
  discoveryTime.resize(Vertices, -1);
  lowLink.resize(Vertices);
  visited.resize(Vertices, false);
  counter = 0;
  numscc = 0;
}

void addEdge(int from, int to)
{
  adjacencyList[from].push_back(to);
}

void findSCCs()
{
  for (int i = 0; i < adjacencyList.size(); ++i)
  {
   if (discoveryTime[i] == -1)
   {
    depthFirstSearch(i);
   }
  }
}

  private:
void depthFirstSearch(int v)
{
  discoveryTime[v] = lowLink[v] = counter++;
  Qstack.push(v);
  Rstack.push(v);
  visited[v] = true;

  for (int neighbor : adjacencyList[v])
  {
   if (discoveryTime[neighbor] == -1)
   {
    depthFirstSearch(neighbor);
    lowLink[v] = min(lowLink[v], lowLink[neighbor]);
   }
   else if (visited[neighbor])
   {
    lowLink[v] = min(lowLink[v], discoveryTime[neighbor]);
   }
  }

  if (lowLink[v] == discoveryTime[v])
  {
   vector<int> currentComponent;
   int w;
   do
   {
    w = Qstack.top();
    Qstack.pop();
    visited[w] = false;
    currentComponent.push_back(w);
   } while (w != v);
   scccomponents.push_back(currentComponent);
   Rstack.pop();
   numscc++;
  }
}

  public:
void printComponents()
{
  cout << "Strongly Connected Components:" << endl;
  for (const auto &currentComponent : scccomponents)
  {
   for (int vertex : currentComponent)
   {
    cout << vertex << " ";
   }
   cout << endl;
  }
}
};

int main()
{
GabowScc Finder(5);

Finder.addEdge(0, 2);
Finder.addEdge(2, 1);
Finder.addEdge(1, 0);
Finder.addEdge(0, 3);
Finder.addEdge(3, 4);

Finder.findSCCs();
Finder.printComponents();

return 0;
}

//4-The statement is doubly interconnected, connective or complex

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Graph {
	int graph[100][100];
	int n;
public:
	void constracter (int n)
	{
		this->n = n;
		srand (time (0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if ( i == j || graph[j][i] == 1 )
					graph[i][j] = 0;
				else
					graph[i][j] = rand() % 2;
					
	}

	void cnostructerZero()       //تابع زيادة يستخدم في حال كان كائن من الكلاس مهيء عشوائيا من قبل و نريد اعطاءه قيم يدوية
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				graph[i][j]=0;
	}

	void input ()
	{
		cout << "enter a number vertices : ";
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if ( i == j || graph[j][i] == 1 )
					graph[i][j] = 0;
				else
				{
					cout << " enter " << "graph["<<i<<"]["<<j<<"] : ";
					cin >> graph[i][j];
					graph[i][j]=graph[i][j]%2;
				}
	}

	void output()
	{
		this->cnostructerZero(); // حالة استخدام زائد
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << graph[i][j] << " ";
			}
			cout<<endl;
		}
	}
};
void main()
{
	Graph x;
	x.output();
	x.input();
	x.output();
}