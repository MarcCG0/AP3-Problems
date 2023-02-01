 #include <iostream>
#include <vector>
#include <climits>

using namespace std;
using Matrix = vector<vector<double>>;
const double UNDEF = -1;

double max_expr(int i, int j, Matrix& M, vector<double>& nums)
{
    double& res = M[i][j];

    if (i == j)
        return res = nums[i];

    if (res != UNDEF) {
        return res;
    }

    else {
        double result = INT_MIN; 
        // For every possible parenthesization, compute maximum expression
        for(int k = i+1; k<= j; ++k){
            int mid = k;
            double l = max_expr(i, mid-1, M, nums);
            double r = max_expr(mid, j, M, nums);
            result = max(max(l + r, l * r), result);
        }
        return res = result;
    }
}

int main()
{
    cout.setf(ios::fixed);
    cout.precision(4);
    int n;
    while (cin >> n) {
        vector<double> nums(n);
        for (int i = 0; i < n; ++i)
            cin >> nums[i];

        Matrix M(n, vector<double>(n, UNDEF));
        cout << max_expr(0, n-1, M, nums) << endl;

    }
}
