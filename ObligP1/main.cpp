#include <iostream>
#include <thread>

using namespace std;

void checkIfPrime(int num) {
    int div = 0;

    for (int i = 1; i <= num; i++){
        if (num % i == 0) {
            div++;
        }
    }
    if(div == 2){
        cout << num << endl;
        this_thread::sleep_for(1s);
    }
}
void goThroughRange(int low, int high){
    for(int i = low; i <= high; i++){
        checkIfPrime(i);
    }
}
int main() {
    int lowerLimit, upperLimit;
    cout << "Enter lower and upper ranges: ";
    cin >> lowerLimit >> upperLimit;

    thread t1(checkIfPrime, lowerLimit);
    t1.join();
    thread t2(goThroughRange, lowerLimit, upperLimit);
    t2.join();
}
