#include <bits/stdc++.h>
using namespace std;

struct Reaction {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> initial(n);
        vector<int> chemicals;

        for (int i = 0; i < n; i++) {
            cin >> initial[i];
            chemicals.push_back(initial[i]);
        }

        vector<Reaction> rules(m);

        for (int i = 0; i < m; i++) {
            cin >> rules[i].x >> rules[i].y >> rules[i].z;

            chemicals.push_back(rules[i].x);
            chemicals.push_back(rules[i].y);
            chemicals.push_back(rules[i].z);
        }

        sort(chemicals.begin(), chemicals.end());

        chemicals.erase(
            unique(chemicals.begin(), chemicals.end()),
            chemicals.end()
        );

        auto getIndex = [&](int chemical) {
            return int(
                lower_bound(
                    chemicals.begin(),
                    chemicals.end(),
                    chemical
                ) - chemicals.begin()
            );
        };

        int total = chemicals.size();

        vector<Reaction> indexedRules(m);

        vector<vector<int>> dependent(total);

        for (int i = 0; i < m; i++) {
            int x = getIndex(rules[i].x);
            int y = getIndex(rules[i].y);
            int z = getIndex(rules[i].z);

            indexedRules[i] = {x, y, z};

            dependent[x].push_back(i);
            dependent[y].push_back(i);
        }

        vector<bool> present(total, false);

        vector<int> reactionCount(m, 0);

        queue<int> q;
        int answer = 0;

        for (int chemical : initial) {
            int c = getIndex(chemical);

            if (!present[c]) {
                present[c] = true;
                q.push(c);
                answer++;
            }
        }

        while (!q.empty()) {
            int c = q.front();
            q.pop();

            for (int reactionId : dependent[c]) {
                reactionCount[reactionId]++;

                if (reactionCount[reactionId] == 2) {
                    int product = indexedRules[reactionId].z;

                    if (!present[product]) {
                        present[product] = true;
                        q.push(product);
                        answer++;
                    }
                }
            }
        }

        cout << answer << '\n';
    }

    return 0;
}