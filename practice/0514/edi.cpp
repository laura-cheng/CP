#include <cassert>

#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 13, inf = 0x3f3f3f3f, kMaxVal = 10000;

int main() {
    int n; cin >> n;
    assert(n <= kMaxN);

    vector<vector<int>> config_cost(n, vector<int>(1 << n, +inf));
    vector<vector<int>> cost(n, vector<int>(n, 0));

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            cin >> cost[i][j];
            assert(0 <= cost[i][j]);
            assert(cost[i][j] <= kMaxVal);
        }
    }

    for (int i = 0; i < n; i += 1) {
        config_cost[i][1 << i] = 0;
    }

    for (int config = 0; config < (1 << n); config += 1) {
        vector<int> current_elements;
        for (int el = 0; el < n; el += 1) {
            if (config & (1 << el)) {
                current_elements.push_back(el);
            }
        }

        for (int current_elements_config = 1; current_elements_config < (1 << (int)current_elements.size()); current_elements_config += 1) {
            int child_config = 0;
            for (int i = 0; i < (int)current_elements.size(); i += 1) {
                if ((1 << i) & current_elements_config) {
                    child_config |= (1 << current_elements[i]);
                }
            }

            for (auto father : current_elements) {
                if ((1 << father) & child_config) {
                    continue;
                } 

                for (auto child : current_elements) {
                    if (((1 << child) & child_config) == 0) {
                        continue;
                    }

                    config_cost[father][config] = min(config_cost[father][config],
                            max(config_cost[father][config ^ child_config],
                                config_cost[child][child_config]) + cost[father][child]);
                }
            }
        }
    }

    cout << config_cost[0][(1 << n) - 1] << '\n';
    return 0;
}
