/*
 * Author      : Midhun P
 * Usage       : Educational purpose
 * Description : Fibonacci series using map
 */
 
#include <iostream>
#include <map>

using namespace std;

map<int, long> store;

long fib(int key) {
    auto i = store.find(key);
    
    if(i != store.end()) {
        return i->second;
    }
    else {
        long value;
         
        if(key < 0)
            value = -1;
        else if(key == 0 || key == 1)
            value = key;
        else
            value = fib(key-1) + fib(key-2);
        
        // Store it for performance improvement.
        store.insert(pair<int, long>(key, value));
        
        return value;
    }
}

int main() {

    int num, opt;
    cout << "Do you want 1) nth term  or 2) series ?" << endl << "Enter youre input (1/2) : ";
    cin >> opt;
    cout << "Enter the number : ";
    cin >> num;
    
    if(opt == 1) 
        cout << "Fibnocci's nth term is " << fib(num-1) << endl;
    else
        for(int iter = 0; iter < num; iter++) {
            if(iter == 0)
                cout << "Fibonocci series : ";
            else
                cout << ", ";
                
            cout << fib(iter);
        }
}
