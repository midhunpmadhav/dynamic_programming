/*
 * Author      : Midhun P
 * Description : Subset sum.
 * Remarks     : a[i][j] = arr[i-1][j-set[i]];
 */
 
#include<iostream>
#define PRINT_DP_MATRIX 0

using namespace std;

void swap(int* x, int* y) {
    *x += *y;
    *y = *x - *y;
    *x -= *y;
}

bool subset_sum(int sum, int n, int* set) {

    int arr[n][sum+1];

    // Sort set array first.
    for(int i = 0; i < n - 1; ++i)
        for(int j = i + 1; j < n; ++j) 
            if(set[i] > set[j]) 
                swap(set[i], set[j]);

    // Start solving sub problems.
    for(int i = 0; i < n; ++i)
        for(int j = 0; j <= sum; ++j) 
            if(j == 0)
                arr[i][j] = 1;
            else if(j < set[i])
                // If sum is less than current element,
                // copy previous result.
                arr[i][j] = (i == 0) ? 0 : arr[i-1][j];
            else
                arr[i][j] = (i == 0) ? (j == set[i]) : arr[i-1][j-set[i]];

#if PRINT_DP_MATRIX
    // Print the matrix
    cout << "DP matrix is as follows:" << endl << "\t";
    for(int i = 0; i < n; ++i) {
        printf("%3d -> ", set[i]);
        for(int j = 0; j <= sum; ++j) 
            printf("%3d ", arr[i][j]);
        cout << endl << "\t";
    }
    cout << endl;
#endif    

    return arr[n-1][sum] ? true : false;
}

int main() {

    int n = 4;
    int sum = 15;
    int set[] = {10, 3, 5, 2};

    cout << "Set is : ";
    for(int i = 0; i < n; i++) 
        cout << set[i] << ", ";
    cout << "\b\b " << endl;

    if(subset_sum(sum, n, set))
        cout << "We can make " << sum << " with the given set" << endl;
    else
        cout << "We will not be able to make " << sum << " with the given set" << endl;
}
