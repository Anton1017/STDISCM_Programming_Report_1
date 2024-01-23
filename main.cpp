#include <iostream>
#include <vector>

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
  std::vector<int> primes;
    
  for (int current_num = 2; current_num <= LIMIT; current_num++) {
    if (check_prime(current_num)) {
      primes.push_back(current_num);
    }
  }

  std::cout << primes.size() << " primes were found." << std::endl;

  return 0;
}

bool check_prime(const int &n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}