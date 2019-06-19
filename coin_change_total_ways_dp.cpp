/*
 * Author      : Midhun P
 * Description : Coin change problem - Total number of ways
 * Remarks     : count (include coin) + count(exclude coin)
 *               a[i][j] = a[i-1][j] + arr[i][j-coins[i]];
 */
 
#include<iostream>
#define PRINT_DP_MATRIX 0

using namespace std;

void swap(int* x, int* y) {
    *x += *y;
    *y = *x - *y;
    *x -= *y;
}

void coin_change(int nv, int n, int* coins) {

    int arr[n][nv+1];

    // Sort coins array first.
    for(int i = 0; i < n - 1; ++i)
        for(int j = i + 1; j < n; ++j) 
            if(coins[i] > coins[j]) 
                swap(coins[i], coins[j]);

    // Start solving sub problems.
    for(int i = 0; i < n; ++i)
        for(int j = 0; j <= nv; ++j) 
            if(j == 0)
                // Number of ways to make 0 is 1.
                arr[i][j] = 1;
            else if (j < coins[i]) {
                // Coin value less than sum.
                // Hence only count(exclude).
                if(i == 0)
                    // It is first row. No count(exclude)
                    arr[i][j] = 0;
                else
                    arr[i][j] = arr[i-1][j];
            }
            else {
                // Count both include and exclude.
                if(i == 0)
                    // It is first row. No count(exclude)
                    arr[i][j] = arr[i][j-coins[i]];
                else
                    arr[i][j] = arr[i-1][j] + arr[i][j-coins[i]];
            }

#if PRINT_DP_MATRIX
    // Print the matrix
    cout << "DP matrix is as follows:" << endl << "\t";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= nv; ++j) 
            printf("%3d ", arr[i][j]);
        cout << endl << "\t";
    }
    cout << endl;
#endif    
            
    cout << "We can make " << nv << " by " << arr[n-1][nv] << " ways using the given coins." << endl;
}

int main() {

    int n = 4;
    int nv = 15;
    int coins[] = {10, 3, 5, 2};

    cout << "Available coins are : ";
    for(int i = 0; i < n; i++) 
        cout << coins[i] << ", ";
    cout << "\b\b " << endl;

    coin_change(nv, n, coins);
}
