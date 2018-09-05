#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

int M, N;
struct Node {
  int x, y, dist;
};

int row[] = {-1, 0, 0, 1};
int col[] = {0, -1, 1, 0};

bool isValid(int **mat, bool **visited, int row, int col) {
  return (row >= 0) && (row < M) && (col >= 0) && (col < N) && mat[row][col] &&
         !visited[row][col];
}

bool BFS(int **mat, int i, int j, int x, int y) {
  bool **visited = new bool *[M];
  for (int i = 0; i < M; i++) {
    visited[i] = new bool[N];
  }

  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      visited[i][j] = false;

  queue<Node> q;

  visited[i][j] = true;
  q.push({i, j, 0});

  int min_dist = INT_MAX;

  while (!q.empty()) {
    Node node = q.front();
    q.pop();

    int i = node.x, j = node.y, dist = node.dist;

    if (i == x && j == y) {
      min_dist = dist;
      break;
    }

    for (int k = 0; k < 4; k++) {
      if (isValid(mat, visited, i + row[k], j + col[k])) {
        visited[i + row[k]][j + col[k]] = true;
        q.push({i + row[k], j + col[k], dist + 1});
      }
    }
  }

  if (min_dist != INT_MAX)
    return true;
  else
    return false;
  ;
}

int main() {
  int testCases;
  ifstream in;
  ofstream out;
  in.open("path-input.txt");
  out.open("path-output.txt");
  in >> testCases;
  while (testCases--) {
    int p, q, r, s;
    in >> M >> N;
    int **mat = new int *[M];
    for (int i = 0; i < M; i++) {
      mat[i] = new int[N];
    }
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        in >> mat[i][j];
        if (mat[i][j] == 1) {
          p = i;
          q = j;
        } else if (mat[i][j] == 2) {
          r = i;
          s = j;
          mat[i][j] = 1;
        } else if (mat[i][j] == 3) {
          mat[i][j] = 1;
        }
      }
    }
    if (BFS(mat, p, q, r, s))
      out << "Yes\n";
    else
      out << "No\n";
  }
  return 0;
}
