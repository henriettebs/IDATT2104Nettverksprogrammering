#include <iostream>
#include <thread>
#include <vector>

using namespace std;

bool checkIfPrime(int num) {
    for (int i = 2; i <= num/2; i++){
        if (num % i == 0 && num!=2) {
            return false;
        }
    }
    return true;
}

void goThroughRange(int low, int high, vector<int> *primes, int numberOfIntervals){
    for(int i = low; i <= high; i+= numberOfIntervals){
        if(checkIfPrime(i)){
            primes ->emplace_back(i);
        }
    }
}
int main() {
    int lowerLimit, upperLimit, numberOfThreads;
    cout << "Enter lower and upper ranges: ";
    cin >> lowerLimit >> upperLimit;
    cout << "Enter number of threads: ";
    cin >> numberOfThreads;

    vector<int> array[numberOfThreads];
    vector<thread> threads;
    vector<int> primes;

    for(int i = 0; i < numberOfThreads; i++){
        threads.emplace_back(goThroughRange, lowerLimit + i, upperLimit, &array[i], numberOfThreads);
        cout << "Thread " << i + 1 << ", ID: " << threads.at(i).get_id() << endl;
    }

    for(auto &thread: threads){
        thread.join();
    }

    for(int i = 0; i < numberOfThreads; i++) {
        primes.insert(primes.end(), array[i].begin(), array[i].end());
    }

    sort(primes.begin(), primes.end());

    for(int i = 0; i < primes.size(); i++){
        cout << primes.at(i) << "\n";
    }
}
