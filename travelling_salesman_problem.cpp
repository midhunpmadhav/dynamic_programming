/*
 * Author      : Midhun P
 * Usage       : Educational purpose
 * Description : Travelling sales man problem (Dynamic Programming)
 */
 
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int tsp(vector<vector<int>> cities, vector<vector<int>> stateStore, int currentPosition, int visited) {
    
    // We have reached the end, now we have to go back to starting poing.
    if(visited == ((1 << cities.size()) - 1))
         return cities[currentPosition][0];
        
    // If we already done the sub problem, return result.
    if(stateStore[currentPosition][visited] != INT_MAX)
        return stateStore[currentPosition][visited];
    
    // Hmm, we have to calculate.
    for(int i = 0; i < cities.size(); i++) {

        // Whether we already visited this city? If yes, continue.
        if((i == currentPosition) || ((1 << i) & visited))
            continue;

        int subcost = cities[currentPosition][i] + tsp(cities, stateStore, i, visited | (1 << i));
        
        if(subcost < stateStore[currentPosition][visited])
            stateStore[currentPosition][visited] = subcost;
    }
    
    return stateStore[currentPosition][visited];
}
        
int main()
{
    vector<vector<int>> cities = {{ 0, 20, 42, 35 },
                                  { 20, 0, 30, 34 },
                                  { 42, 30, 0, 12 },
                                  { 35, 34, 12, 0 }};

    cout << "Input adjacency matrix : " << endl << endl;

    for(int i = 0; i < cities.size(); i++) {
        cout << "\t";
        for(int j = 0; j < cities.size(); j++)
            cout << cities[i][j] << " ";
        cout << endl; 
    }

    vector<vector<int>> stateStore (cities.size());

    for(auto& iter : stateStore)
        iter = vector<int>((1 << cities.size()) - 1, INT_MAX);
       
    int cost = tsp(cities, stateStore, 0, 1);
    
    cout << endl << "Minimum cost = " << cost << endl;

}
