#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

#define LIMIT 10000000

/*
This function checks if an integer n is prime.

Parameters:
n : int - integer to check

Returns true if n is prime, and false otherwise.
*/

/*
Delegation of Tasks
Task 1 - Jacob
Task 2 - Anton
Task 3 - Joshua
Task 4 - Ryan
*/
bool check_prime(const int &n);

void find_primes_range(int start, int end, int limit, std::vector<int> &primes, mutex &primesMutex);

void mutualExclusion(int currentNum, vector<int> &primes, mutex &primesMutex);

int main() {
  
  std::vector <int> primes;
  string input_limit, input_num_thread;
  int limit = LIMIT, num_thread = 1;
  
  // do {
  //   cout << "Enter upper bound of integers to check: ";
  //   cin >> limit;
  // } while (limit > LIMIT);
  

  // cout << "Enter the number of threads to use: ";
  // cin >> num_thread;

  // Automate input for testing
  getline(cin, input_limit);
  getline(cin, input_num_thread);
  limit = stoi(input_limit);
  num_thread = stoi(input_num_thread);


  auto start_time{std::chrono::steady_clock::now()};

  // Get the range for each thread
  int range = limit / num_thread;
  int start = 2;
  int end = start + range;

  // Create threads
  std::thread threads[num_thread];

  // Create mutex for mutual exclusion
  mutex primesMutex;

  for (int i = 0; i < num_thread; i++) {
    threads[i] = std::thread(find_primes_range, start, end, limit ,std::ref(primes), std::ref(primesMutex));
    start = end + 1;
    end = start + range;
  }

  // Join threads
  for (int i = 0; i < num_thread; i++) {
    threads[i].join();
  }

  /*
  for (int current_num = 2; current_num <= limit; current_num++) {
    if (check_prime(current_num)) {
      primes.push_back(current_num);
    }
  }
  */
  
  auto end_time{std::chrono::steady_clock::now()};
  std::chrono::duration<double> elapsed{end_time - start_time};
  cout << "Number of threads: " << num_thread << endl;
  cout << "Time: " << elapsed.count() << "s\n";

  cout << primes.size() << " primes were found." << std::endl;

  return 0;
}

void find_primes_range(int start, int end, int limit, vector<int> &primes, mutex &primesMutex) {
  for (int current_num = start; current_num <= end && current_num <= limit; current_num++) {
    if (check_prime(current_num)) {
      // primes.push_back(current_num);
      mutualExclusion(current_num, primes, primesMutex);
    }
  }
}

void mutualExclusion(int currentNum, vector<int> &primes, mutex &primesMutex) {
  lock_guard<mutex> lock(primesMutex);
  primes.push_back(currentNum);
}

bool check_prime(const int &n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}