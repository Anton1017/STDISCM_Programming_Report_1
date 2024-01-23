#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
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

int main() {
  
  std::vector <int> primes;
  int limit = LIMIT, num_thread = 0;
  
  do {
    cout << "Enter upper bound of integers to check: ";
    cin >> limit;
  } while (limit > LIMIT);
  

  cout << "Enter the number of threads to use: ";
  cin >> num_thread;

  // Get the range for each thread
  int range = limit / num_thread;
  int start = 2;
  int end = start + range;
  // Create threads
  std::thread threads[num_thread];

  for (int i = 0; i < num_thread; ++i) {
    threads[i] = std::thread(find_primes_range, start, end, limit ,std::ref(primes));
    start = end + 1;
    end = start + range;
  }

  // Join threads
  for (int i = 0; i < num_thread; ++i) {
    threads[i].join();
  }

  for (int current_num = 2; current_num <= limit; current_num++) {
    if (check_prime(current_num)) {
      primes.push_back(current_num);
    }
  }

  std::cout << primes.size() << " primes were found." << std::endl;

  return 0;
}

void find_primes_range(int start, int end, int limit ,std::vector<int> &primes) {
  for (int current_num = start; current_num <= end && current_num <= limit; ++current_num) {
    if (check_prime(current_num)) {
      primes.push_back(current_num);
    }
  }
}

bool check_prime(const int &n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}