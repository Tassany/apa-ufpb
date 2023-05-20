#include <iostream>
#include <vector>

using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    // Constructor
    DisjointSet(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);

        // Initialize each element as a separate set
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    // Find the root of the set to which the element belongs
    int find(int element)
    {
        if (parent[element] != element)
        {
            // Path compression: make the element directly point to the root
            parent[element] = find(parent[element]);
        }
        return parent[element];
    }

    // Union two sets by rank (union by rank)
    void unionSets(int set1, int set2)
    {
        int root1 = find(set1);
        int root2 = find(set2);

        if (root1 != root2)
        {
            // Attach the smaller rank tree under the root of the higher rank tree
            if (rank[root1] < rank[root2])
            {
                parent[root1] = root2;
            }
            else if (rank[root1] > rank[root2])
            {
                parent[root2] = root1;
            }
            else
            {
                // If ranks are the same, make one as the root and increment its rank by 1
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }
};

int main()
{
    int size = 10;

    DisjointSet ds(size);

    // Perform some operations on the disjoint set
    ds.unionSets(0, 1);
    ds.unionSets(2, 3);
    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(7, 8);
    ds.unionSets(1, 9);

    // Find representatives of some elements
    cout << "Parent of 4: " << ds.find(4) << endl;
    cout << "Parent of 6: " << ds.find(6) << endl;

    return 0;
}
