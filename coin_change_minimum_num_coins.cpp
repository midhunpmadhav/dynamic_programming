/*
 * Author      : Midhun P
 * Description : Coin change problem - Minimum number of coins
 * Remarks     : Find minimum of including and excuding current coin.
 *               IF j < coins[i] : arr[i][j-coins[i]]
 *               ELSE : min(arr[i-1][j], 1 + arr[i][j-coins[i]])
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

    // Sort weight array first.
    for(int i = 0; i < n - 1; ++i)
        for(int j = i + 1; j < n; ++j) 
            if(coins[i] > coins[j]) 
                swap(coins[i], coins[j]);

    // Start solving sub problems.
    for(int i = 0; i < n; ++i)
        for(int j = 0; j <= nv; ++j) 
            if(j == 0)
                // Number of coins to make 0 is 0.
                arr[i][j] = 0;
            else if (j < coins[i])
                // Coin value is greater than required sum.
                // Hence copy previously computed count
                arr[i][j] = (i == 0) ? 0 : arr[i-1][j];
            else {
                if(i == 0 || arr[i-1][j] == 0)
                    // No previous computataion or it is zero.
                    arr[i][j] = ((arr[i][j-coins[i]] != 0) || ((j-coins[i]) == 0)) ? 
                                  1 + arr[i][j-coins[i]] : 0;
                else
                    arr[i][j] = ((arr[i][j-coins[i]] != 0) || ((j-coins[i]) == 0)) ? 
                                  min(arr[i-1][j], 1 + arr[i][j-coins[i]]) : 0;
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
            
    cout << "We can make " << nv << " rupees with " << arr[n-1][nv] << " coins";

    if (arr[n - 1][nv] != 0)
    {
        int i = n - 1;
        int j = nv;

        cout << " by choosing ";
        while (arr[i][j] != 0) {
            // if it is first row, or not same as previous calculation,
            // print the coin value.
            if (i == 0 || arr[i][j] != arr[i - 1][j]) {
                cout << coins[i] << ", ";
                j = j - coins[i];
            }
            else
                --i;
        }
        cout << "\b\b.";
    }
    cout << endl;
}

int main() {

    int n = 4;
    int nv = 16;
    int coins[] = {9, 5, 6, 7};

    cout << "Available coins are : ";
    for(int i = 0; i < n; i++) 
        cout << coins[i] << ", ";
    cout << "\b\b " << endl;

    coin_change(nv, n, coins);
}
