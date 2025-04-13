#include <iostream>
#include <vector>

using namespace std;

void fibDP(int num) {
    vector<int> fib;
    fib.push_back(0);
    fib.push_back(1);

    while (fib.back() < num) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);  
    }

    if (fib.back() == num) {
        cout << 1 << endl;  
    } else {
        cout << 0 << endl;
        cout << fib.back() << endl;  
    }
}

int main(int argc, char* argv[]) {
    int num = atoi(argv[1]); 

    fibDP(num);
    
    return 0;
}
