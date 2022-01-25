#include <iostream>
#include <thread>
#include <vector>

using namespace std;

bool checkIfPrime(int num) {
    for (int i = 2; i <= num/2; i++){
        if (num % i == 0 && num!=2) {
            return false; //Returnerer false dersom num ikke er et primtall
        }
    }
    if(num >= 2){
        return true; //Returnerer true dersom num er et primtall større enn eller lik 2
    }

}

void goThroughRange(int low, int high, vector<int> *primes, int numberOfIntervals){
    for(int i = low; i <= high; i+= numberOfIntervals){
        if(checkIfPrime(i)){
            primes ->emplace_back(i); //Dersom i er ett primtall blir primtallet lagt til på slutten i
            // pointeren til vektoren primes
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
        threads.emplace_back(goThroughRange, lowerLimit + i, upperLimit, &array[i], numberOfThreads); //Pointeren til vektoren primes(med primtallene), blir lagt til i vektoren threads
        // og trådene begynner å kjøre pga. emplace_back()
        cout << "Thread " << i + 1 << ", ID: " << threads.at(i).get_id() << endl; //Skriver ut tråd-id
    }

    for(auto &thread: threads){
        thread.join(); //Venter til alle trådene har kjørt ferdig
    }

    for(int i = 0; i < numberOfThreads; i++) {
        primes.insert(primes.end(), array[i].begin(), array[i].end()); //Alle primtallene blir lagt til i vektoren primes
    }

    sort(primes.begin(), primes.end()); //Primtallene blir sortert, med C++ sin egen sorteringsmetode

    for(int i = 0; i < primes.size(); i++){
        cout << primes.at(i) << "\n"; //Primtallene blir skrive ut i sortert rekkefølge
    }
}
