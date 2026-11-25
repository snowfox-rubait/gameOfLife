// Exhaustive glider compatibility search on a 45x7 toroidal Game of Life board.
#include <bits/stdc++.h>
using namespace std;

static const int R = 7, C = 45, N = R * C, G = 1260;  // 1260 = lcm(45*4, 7*4): full recurrence period
typedef array<uint8_t, N> Grid;
static int nb[N][8];

static void initNb() {
  for (int r = 0; r < R; r++)
    for (int c = 0; c < C; c++) {
      int k = 0;
      for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++)
          if (dr || dc) nb[r * C + c][k++] = ((r + dr + R) % R) * C + ((c + dc + C) % C);
    }
}
static inline void stepG(const Grid& a, Grid& b) {
  for (int i = 0; i < N; i++) {
    int s = 0;
    for (int k = 0; k < 8; k++) s += a[nb[i][k]];
    b[i] = a[i] ? (s == 2 || s == 3) : (s == 3);
  }
}
static int popc(const Grid& g) { int p = 0; for (int i = 0; i < N; i++) p += g[i]; return p; }
static Grid shiftG(const Grid& g, int dr, int dc) {
  Grid o{};
  for (int r = 0; r < R; r++)
    for (int c = 0; c < C; c++)
      if (g[r * C + c]) o[(((r + dr) % R + R) % R) * C + (((c + dc) % C + C) % C)] = 1;
  return o;
}
static string canon(const Grid& g) {
  string best;
  for (int dr = 0; dr < R; dr++)
    for (int dc = 0; dc < C; dc++) {
      Grid s = shiftG(g, dr, dc);
      string k(s.begin(), s.end());
      if (best.empty() || k < best) best = k;
    }
  return best;
}
// true if the pattern keeps its population every generation and returns to itself after G generations
static bool survives(Grid u) {
  Grid init = u, v;
  int p0 = popc(u);
  for (int g = 0; g < G; g++) {
    stepG(u, v);
    if (popc(v) != p0) return false;
    u = v;
  }
  return u == init;
}

static const int NMAX = 16 * N;
typedef bitset<NMAX> BS;
static vector<BS> adj;
static int best; static vector<int> bestSet;
static chrono::steady_clock::time_point deadline;
static bool timedOut; static long long calls;

static void expand(vector<int>& cur, BS P) {
  if (timedOut) return;
  if ((++calls & 1023) == 0 && chrono::steady_clock::now() > deadline) { timedOut = true; return; }
  vector<int> order, col;
  BS U = P; int k = 0;
  while (U.any()) {
    k++; BS Q = U;
    while (Q.any()) {
      int v = Q._Find_first(); Q.reset(v); U.reset(v); Q &= ~adj[v];
      order.push_back(v); col.push_back(k);
    }
  }
  for (int i = (int)order.size() - 1; i >= 0; i--) {
    if ((int)cur.size() + col[i] <= best) return;
    int v = order[i]; cur.push_back(v);
    BS np = P & adj[v];
    if (np.none()) { if ((int)cur.size() > best) { best = cur.size(); bestSet = cur; } }
    else expand(cur, np);
    cur.pop_back(); P.reset(v);
    if (timedOut) return;
  }
}

int main() {
  initNb();
  int base[5][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
  set<string> seen; vector<Grid> reps;
  for (int t = 0; t < 8; t++) {
    Grid g{};
    for (auto& b : base) {
      int r = b[0], c = b[1];
      if (t & 1) swap(r, c);
      if (t & 2) r = -r;
      if (t & 4) c = -c;
      g[(((r + 3) % R + R) % R) * C + (((c + 3) % C + C) % C)] = 1;
    }
