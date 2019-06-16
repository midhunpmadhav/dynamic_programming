/*
 * Author      : Midhun P
 * Description : Longest subsequence.
 * Remarks     : IF x[i] == y[j] -> a[i][j] = a[i-1][j-1]
 *               ELSE -> a[i][j] = max(arr[i-1][j], arr[i][j-1])
 */
 
#include<iostream>
#define PRINT_DP_MATRIX 0

using namespace std;

int max(int m, int n) {
    return (m > n) ? m : n;
}

void lcs(char* x, char* y, int x_len, int y_len) {
    
    int arr[x_len+1][y_len+1];

    // Find the length.
    for(int i = 0; i <= x_len; ++i)
        for(int j = 0; j <= y_len; ++j)
            if(i == 0 || j == 0)
                // Fill the sides with 0;
                arr[i][j] = 0;
            else
                if(x[i-1] == y[j-1])
                    //If we find common character, save prev diagonal element + 1.
                    arr[i][j] = 1 + arr[i-1][j-1];
                else
                    // Otherwise find save the max of non diagonal elements.
                    arr[i][j] = max(arr[i-1][j], arr[i][j-1]);

#if PRINT_DP_MATRIX
    // Print the matrix
    cout << "DP matrix is as follows:" << endl << "\t";
    for(int i = 0; i <= x_len; ++i) {
        for(int j = 0; j <= y_len; ++j) {
            if(i == 0 && j != 0)
                cout << y[j-1] << " ";
            else if(i != 0 && j == 0)
                cout << x[i-1] << " ";
            else
                cout << arr[i][j] << " ";
        }
        cout << endl << "\t";
    }
    cout << endl;
#endif

    cout << "Longest subsequence length is " << arr[x_len][y_len];

    int i = x_len;
    int j = y_len;
    int index = arr[x_len][y_len];
    char* result = (char*) malloc(index + 1);

    // Find the subseuence string.
    result[index--] = '\0';

    while(i != 0 && j != 0) {
        if(arr[i][j] == arr[i-1][j])
            --i;
        else if (arr[i][j] == arr[i][j-1])
            --j;
        else if(arr[i][j] == (1+ arr[i-1][j-1])) {
            result[index--] = x[i-1];
            --i;
            --j;
        }
        else {
            cout << "BUG: Something went wrong" << endl;
            return;
        }
    }

    if(arr[x_len][y_len] > 0)
        cout << " and subsequence is \"" << result << "\"" << endl;
    else
        cout << endl;
    
}

int main() {

    char x[] = "YABCD";
    char y[] = "AXAYBZCC";

    int x_len = strlen(x);
    int y_len = strlen(y);

    cout << "Input 1: " << x << endl;
    cout << "Input 2: " << y << endl << endl;

    lcs(x, y, x_len, y_len);
}
