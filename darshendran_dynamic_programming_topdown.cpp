#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctime>
using namespace std;

// Returns true if there exists a subset of `array[0…n)` with the given sum
bool subsetSum(vector<int> const &nums, int sum)
{
    int n = nums.size();

    // `T[i][j]` stores true if subset with sum `j` can be attained
    // using items up to first `i` items
    bool T[n + 1][sum + 1];

    // if 0 items in the list and the sum is non-zero
    for (int j = 1; j <= sum; j++) {
        T[0][j] = false;
    }

    // if the sum is zero
    for (int i = 0; i <= n; i++) {
        T[i][0] = true;
    }

    // do for i'th item
    for (int i = 1; i <= n; i++)
    {
        // consider all sum from 1 to sum
        for (int j = 1; j <= sum; j++)
        {
            // don't include the i'th element if `j-nums[i-1]` is negative
            if (nums[i - 1] > j) {
                T[i][j] = T[i - 1][j];
            }
            else {
                // find the subset with sum `j` by excluding or including the i'th item
                T[i][j] = T[i - 1][j] || T[i - 1][j - nums[i - 1]];
            }
        }
    }

    // return maximum value
    return T[n][sum];
}

// Partition problem – Returns true if given array `nums[0…n-1]` can
// be divided into two subsets with equal sum
bool partition(vector<int> const &nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);

    // return true if the sum is even and the array can be divided into
    // two subsets with equal sum
    return !(sum & 1) && subsetSum(nums, sum/2);
}

struct RndIntGen
{
  RndIntGen(int l, int h)
    : low(l), high(h)
  { }
  int operator()() const {
    return low + (rand() % ((high - low) + 1));
  }
private:
  int low;
  int high;
};

int main()
{
    // random size of vector
    srand(time(0));
    //generate values between 10 to 50
    int size = rand() % (50 - 10) + 10;
    cout << "Size of Array: "<< size<<endl;

    vector<int> V(size, 0);
    // random values in vector
	generate(V.begin(), V.end(), RndIntGen(1, 10));

// To view inputs
        cout << "Inputs"<<endl;
        for (const int &n : V) {
            cout << n << " "<<endl;
        }


    if (partition(V)) {
        cout << "Set can be partitioned";
    }
    else {
        cout << "Set cannot be partitioned";
    }
     return 0;
}
