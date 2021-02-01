#include <iostream>
#include <vector>
#include <array>
#define N 4
using namespace std;

class nqueen
{
public:
    array<int, N> state;
    
    nqueen() {
    	 state = {3, 2, 3, 1};
	}

    void hillClimb()
    {
        int heuristic = calculateConflicts(state);
        
        auto ngh = getNeighbors();
        
        for(int i = 0; i < ngh.size(); i++) {
        	for(int j = 0; j < N; j++) {
        		cout << ngh[i][j] << " ";
			}
			cout << endl;
		}
    }

    vector<array<int, N>> getNeighbors()
    {
        vector<array<int, N>> neighbors;
        
        for (int i = 0; i < N; i++)
        {    
        	auto current = state;
        	// [3, 2, 3, 1]
			for(int j = 0; j < N; j++) {
				
				current[j] = j;
				neighbors.push_back(current);
			}   	
        }

        return neighbors;
    }

    int calculateConflicts(array<int, N> arr)
    {
        int conflict = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (arr[i] == arr[j] || abs(arr[i] - arr[j]) == j - i)
                    conflict++;
            }
        }
        return conflict;
    }
};

int main()
{
    nqueen nq = nqueen();
    nq.hillClimb();
}
