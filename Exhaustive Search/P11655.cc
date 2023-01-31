/*

Write a program that, given a natural number s and n natural numbers x1, …, xn, prints all the subsets (maybe with repeated numbers, but using every xi at most once) whose sum is exactly s.

Input consists of a natural number s, followed by a number n > 0, followed by x1, …, xn.

Print all the subsets whose sum is s that can be made up with x1, …, xn.

*/

#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& nums, const vector<bool>& used)
{
    cout << "{";
    bool first = true;
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) {
            if (first) {
                first = false;
                cout << nums[i];
            } else
                cout << "," << nums[i];
        }
    }
    cout << "}" << endl;
}

void exh(vector<int>& nums, vector<bool>& used, int k, int partial_sum,
    int s, int total_sum, bool nw)
{
    if (partial_sum == s and nw)
        write(nums, used);
        /*
            Branch & Bound: If there's not enough numbers left
            to accomplish the sum s, then stop recursion
        */
    if (partial_sum + total_sum < s)
        return;
    if (partial_sum > s)
        return;
    if (k < nums.size()) {
        /*
            Decide whether the k-th number is in partial solution or not 
        */
        used[k] = true;
        exh(nums, used, k + 1, partial_sum + nums[k], s, total_sum - nums[k], true);
        used[k] = false;
        exh(nums, used, k + 1, partial_sum, s, total_sum - nums[k], false);
    }
}

int main()
{
    int s, n;
    cin >> s >> n;
    vector<int> nums(n);
    vector<bool> used(n);
    int total_sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        total_sum += nums[i];
    }
    exh(nums, used, 0, 0, s, total_sum, true);
}