/*
 * Author      : Midhun P
 * Description : 0/1 Knapsack Problem
 * Remarks     : knap[i, w] = max(knap[i-1, w], profit[i] + knap[i-1, w - weight[i]]
 */
 
#include<iostream>
#define PRINT_DP_MATRIX 1

using namespace std;

int max(int m, int n) {
    return (m > n) ? m : n;
}

void swap(int* x, int* y) {
    *x += *y;
    *y = *x - *y;
    *x -= *y;
}

void knap(int nw, int n, int* w, int* p) {

    int arr[n+1][nw+1];

    // Sort weight array first.
    for(int i = 0; i < n - 1; ++i)
        for(int j = i + 1; j < n; ++j) 
            if(w[i] > w[j]) {
                swap(w[i], w[j]);
                swap(p[i], p[j]);
            }
    // Start solving sub problems.
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= nw; ++j) 
            if(i == 0 || j == 0)
                // Fill the sides with 0.
                arr[i][j] = 0;
            else if (j < w[i-1])
                // We will not be able to accomodate item i-1 with weight j.
                arr[i][j] = arr[i-1][j];
            else
                // Find the maximum of profit with or without choosing item i-1.
                arr[i][j] = max(arr[i-1][j], p[i-1] + arr[i-1][j-w[i-1]]);

#if PRINT_DP_MATRIX
    // Print the matrix
    cout << "DP matrix is as follows:" << endl << "\t";
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= nw; ++j) {
            if(i == 0 && j != 0)
                cout << j << " ";
            else if(i != 0 && j == 0)
                cout << w[i-1] << " ";
            else
                cout << arr[i][j] << " ";
        }
        cout << endl << "\t";
    }
    cout << endl;
#endif    
            
    cout << "We can make maximum profit of " << arr[n][nw] << " rupees ";

    int i = n;
    int j = nw;
    int index = arr[n][nw];
    bool result[n];

    // Find the selected items.

    while(i != 0 || j != 0) {
        if(arr[i][j] == arr[i-1][j]) {
            result[--i] = false;
        }
        else {
            result[i-1] = true;
            for(int k = 0; k < j; ++k)
                if(arr[i][k] == (arr[i][j] - p[i-1])) {
                    --i;
                    j = k;
                    break;
                }
        }
        
    }

    if(arr[n][nw] > 0) {
        cout << "by selecting items with following weights : ";

        for(int i = 0; i < n ; ++i) 
            if(result[i])
                cout << w[i] << "(" << p[i] << "), ";
        cout << "\b\b ";
    }

    cout << endl;
}

int main() {

    int n = 5;
    int nw = 10;
    int weight[] = {3, 4, 6, 5, 4};
    int profit[] = {2, 3, 1, 4, 7};

    cout << "Net weight = " << nw << endl 
         << "Available Weights are : " << endl;
    for(int i = 0; i < n; i++) 
        cout << "\tItem-" << i+1 << " : " << weight[i] << " (Profit: " << profit[i] << ") "<< endl;
    cout << endl;

    knap(nw, n, weight, profit);
}
