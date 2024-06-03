// Program for DSatur Algorithm for graph coloring.
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <deque>
#include <math.h>
using namespace std;

vector<int> storage[5];

// Function to add edge between two vertices.
void addEdgeBetween(vector<int> graph[], int a, int b)
{
    graph[a].push_back(b);
    graph[b].push_back(a);
}

// For storing information related to vertices.
class vertexInfo
{
public:
    // Saturation degree of the vertex.
    int sat;

    // degree in uncolored graph
    int deg;

    // index of vertex.
    int vertex;
};

struct maxSat
{
    bool operator()(const vertexInfo &lhs,
                    const vertexInfo &rhs) const
    {
        return tie(lhs.sat, lhs.deg, lhs.vertex) > tie(rhs.sat, rhs.deg, rhs.vertex);
    }
};

// Function to print color of each vertex of graph.
void printcolor(vector<int> &color, deque<int> ID)
{
    for (int i = 0; i < color.size(); i++)
    {
        //cout << "The Color of the vertex " << ID[i] << " is " << color[i] << endl;
        storage[color[i]].push_back(ID[i]);
    }
}

// Function for DSatur algo.
int DSatur(vector<int> graph[], int V, deque<int> ID)
{
    int u, i;
    // Create vector to store status of used colors.
    vector<bool> use(V, false);


    // Create vector to store colors.
    vector<int> color(V), d(V);
    vector<set<int>> adjCols(V);
    set<vertexInfo, maxSat> Q;
    set<vertexInfo, maxSat>::iterator maxPtr;

    for (u = 0; u < V; u++)
    {
        color[u] = -1;
        d[u] = graph[u].size();
        adjCols[u] = set<int>();
        Q.emplace(vertexInfo{0, d[u], u});
    }

    while (!Q.empty())
    {
        maxPtr = Q.begin();
        u = (*maxPtr).vertex;
        Q.erase(maxPtr);

        for (int v : graph[u])
            if (color[v] != -1)
                use[color[v]] = true;
        i = 0;
        while (i != use.size())
        {
            if (use[i] == false)
                break;
            i++;
        }
        for (auto v : graph[u])
            if (color[v] != -1)
                use[color[v]] = false;

        color[u] = i;
        for (auto v : graph[u])
        {
            if (color[v] == -1)
            {
                Q.erase(
                    {int(adjCols[v].size()),
                     d[v], v});
                adjCols[v].insert(i);
                d[v]--;
                Q.emplace(vertexInfo{
                    int(adjCols[v].size()),
                    d[v], v});
            }
        }
    }
    set<int> ans;
    for (int i = 0; i < V; i++)
        ans.insert(color[i]);

    printcolor(color, ID);
    // Return Chromatic number.

    // Print the Chromatic number of graph coloring.
    //cout << "The Chromatic number is : ";
    return ans.size();
}

// Function to calculate Chromatic numvber.
int getChromaticNumber(deque<int> ID)
{
    // Input number of vertices 'V' and edges 'E'.
    int V = ID.size();
    // cin >> V >> E;

    // Create graph of ‘V’ vertices from 0 to V - 1.
    vector<int> graph[V];
    for (int i = 0; i < V; i++){
        // Input edge from vertex 'A' to vertex 'B'.
        for(int j = i + 1; j < V; j++){
            // Insert edge between the vertices.
            addEdgeBetween(graph, i, j);
        }
    }
    DSatur(graph, V, ID);
    return 0;
}

int main()
{
    int n; //number of positions
    int x; //
    string posName;
    deque<int> EmployeeID;
    string days[5] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    deque<int> splitIds;
    cout << "Input amount of positions: " << endl;
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "What is the name of this Position? " << endl;
        cin >> posName;
        cout << "Input amount of employess for the " << posName << " position" << endl;
        cin >> x;
        for(int j = 0; j < x; j++){
            EmployeeID.push_back(j);
        }
        cout << endl;
        storage[0].clear();
        storage[1].clear();
        storage[2].clear();
        storage[3].clear();
        storage[4].clear();
        EmployeeID.clear();
    }
    return 0;
}
