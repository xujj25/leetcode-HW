#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 1)
            return 0;

        int i, j, max = 0, low, high;
        int stockCount = prices.size();
        bool flag = false;
        for (i = 0; i < stockCount - 1; i++)
            if (prices[i] < prices[i + 1]) {
                low = i;
                flag = true;
                break;
            }

        if (!flag)
            return 0;

        for (j = stockCount - 1; j >= low + 1; j--)
            if (prices[j] > prices[j - 1]) {
                high = j;
                break;
            }


        for (i = low; i <= high - 1; i++) {
            for (j = i + 1; j <= high; j++) {
                if (max < prices[j] - prices[i])
                    max = prices[j] - prices[i];
            }
        }
        return max;
    }
};

int main(int argc, char const *argv[])
{
    int stockCount, i, price;
    cin >> stockCount;
    vector<int> prices;
    for (i = 0; i < stockCount; i++) {
        cin >> price;
        prices.push_back(price);
    }
    cout << Solution().maxProfit(prices) << endl;
    return 0;
}