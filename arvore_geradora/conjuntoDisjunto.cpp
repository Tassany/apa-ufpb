#include <iostream>
#include <vector>

class DisjointSet
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);

        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
        {
            return;
        }

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

int main()
{
    DisjointSet ds(5);

    ds.unite(0, 1);
    ds.unite(2, 3);
    ds.unite(3, 4);

    std::cout << ds.find(0) << std::endl; // 1
    std::cout << ds.find(2) << std::endl; // 4
    std::cout << ds.find(4) << std::endl; // 4

    return 0;
}
