#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
private:
    struct vertex
    {
        int r, c;
        vertex(int _r, int _c) : r(_r), c(_c) {}
    };
    int row, col;
    vector<vector<int> > res;
public:
    bool isValid(int r, int c) {
        return r >= 0 && r < row && c >= 0 && c < col;
    }

    void insertQ(queue<vertex>& q, int r, int c, int val) {
        if (!isValid(r, c))
            return;
        if (res[r][c] == -1) {
            res[r][c] = val + 1;
            q.push(vertex(r, c));
        } else if (res[r][c] > val + 1) {
            res[r][c] = val + 1;
        }
    }

    vector<vector<int> > updateMatrix(vector<vector<int> >& A) {
        this -> row = A.size();
        this -> col = A[0].size();
        vector<int> rowvec(col, -1);
        vector<vector<int> > resRef(row, rowvec);
        this -> res = resRef;
        int i, j;
        queue<vertex> q;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (A[i][j] == 0) {
                    res[i][j] = 0;
                    q.push(vertex(i, j));
                }
            }
        }

        while (!q.empty()) {
            vertex v = q.front();
            q.pop();
            int val = res[v.r][v.c];
            insertQ(q, v.r + 1, v.c, val);
            insertQ(q, v.r - 1, v.c, val);
            insertQ(q, v.r, v.c + 1, val);
            insertQ(q, v.r, v.c - 1, val);
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    int r, c;
    cin >> r >> c;
    vector<int> rowvec(c);
    vector<vector<int> > map(r, rowvec);
    int t;
    int i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++) {
            cin >> t;
            map[i][j] = t;
        }
    vector<vector<int> > res = Solution().updateMatrix(map);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            cout << res[i][j] << " ";
        cout << endl;
    }
    return 0;
}