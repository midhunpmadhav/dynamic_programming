/*
 * Author      : Midhun P
 * Description : Longest substring.
 * Remarks     : IF x[i] == y[j] -> a[i][j] = a[i-1][j-1]
 *               ELSE -> a[i][j] = 0
 */
 
#include<iostream>
#define PRINT_DP_MATRIX 0

using namespace std;

void lcs(char* x, char* y, int x_len, int y_len) {
    
    int max = 0;
    int end_x = 0, end_y = 0;
    int arr[x_len+1][y_len+1];

    // Find the length.
    for(int i = 0; i <= x_len; ++i)
        for(int j = 0; j <= y_len; ++j)
            if(i == 0 || j == 0)
                // Fill the sides with 0;
                arr[i][j] = 0;
            else
                if(x[i-1] == y[j-1]) {
                    //If we find common character, save prev diagonal element + 1.
                    arr[i][j] = 1 + arr[i-1][j-1];
                    if (max < arr[i][j]) {
                        max = arr[i][j];
                        end_x = i;
                        end_y = j;
                    }
                }
                else
                    // Otherwise 0.
                    arr[i][j] = 0;
#if PRINT_DP_MATRIX
    // Print the matrix
    cout << "DP matrix is as follows:" << endl << "\t";
    for(int i = 0; i <= x_len; ++i) {
        for(int j = 0; j <= y_len; ++j) {
            if(i == 0 && j != 0)
                printf("%3c ", y[j-1]);
            else if(i != 0 && j == 0)
                printf("%3c ", x[i-1]);
            else
                printf("%3d ", arr[i][j]);
        }
        cout << endl << "\t";
    }
    cout << endl;
#endif
    cout << "Longest substring length is " << arr[end_x][end_y];

    int i = end_x;
    int j = end_y;
    int index = max;
    char* result = (char*) malloc(index + 1);

    // Find the subseuence string.
    result[index--] = '\0';

    while(i != 0 && j != 0) {
        if(arr[i][j] == 0)
            break;
        else if(arr[i][j] == (1 + arr[i-1][j-1])) {
            result[index--] = x[i-1];
            --i;
            --j;
        }
        else {
            cout << endl << "BUG: Something went wrong"<< endl;
            return;
        }
    }

    if(arr[end_x][end_y] > 0)
        cout << " and substring is \"" << result << "\"" << endl;
    else
        cout << endl;
    
}

int main() {

    char x[] = "XABABCFCDY";
    char y[] = "AXYABCYBZCC";

    int x_len = strlen(x);
    int y_len = strlen(y);

    cout << "Input 1: " << x << endl;
    cout << "Input 2: " << y << endl << endl;

    lcs(x, y, x_len, y_len);
}
