#include <iostream>
#include <string>

using namespace std;

// fibo1 is the smaller one and fibo2 is the larger one
void fibRecursion(int target, int fibo1, int fibo2){
    // Base case: If fibo2 is greater than or equal to the target
    if(fibo1 == target || fibo2 == target) {
        cout << 1 << endl; 
        return;
    }

    if(fibo2 >= target) {
        cout << 0 << endl; 
        cout << fibo2 << endl;  
        return;
    }
    
    fibRecursion(target, fibo2, fibo1 + fibo2);
}

int main(int argc, char* argv[]) {
    int num = atoi(argv[1]); 

    fibRecursion(num, 0, 1);
    
    return 0;
}
