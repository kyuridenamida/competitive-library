#include "../include/math/matrix.cpp"
#include "../include/math/lup_decomposition.cpp"

#define REP(i,n) for(int i=0;i<(n);++i)

struct Bool {
  int n;
  Bool () : n(0) {;}
  Bool (int m) : n(m & 1) {;}
  explicit operator int() const { return n; }
  explicit operator ll() const { return n; }
  bool operator==(const Bool &a) const { return n == a.n; }
  Bool &operator+=(const Bool &a) { n ^= a.n; return *this; }
  Bool &operator-=(const Bool &a) { n ^= a.n; return *this; }
  Bool &operator*=(const Bool &a) { n &= a.n; return *this; }
  Bool operator+(const Bool &a) const { return n ^ a.n; }
  Bool operator-(const Bool &a) const { return n ^ a.n; }
  Bool operator*(const Bool &a) const { return n & a.n; }
  Bool operator^(const int&) const { return *this; }
  Bool operator/(const Bool&) const { return *this; }
  Bool &operator/=(const Bool&) { return *this; }
};

bool is_zero(Bool x) { return int(x) == 0; }
int abs(Bool x) { return int(x); }

int main() {
  int N, T;
  cin >> N;
  Matrix<Bool> mat(N, N, 0);
  Vec<Bool> ary(N);
  REP(i,N) REP(j,N) {
    int in; cin >> in;
    mat[i][j] = Bool(in);
  }
  REP(i,N) {
    int in;
    cin >> in;
    ary[i] = Bool(in);
  }
  cin >> T;
  mat = mat ^ T;
  int rank1 = mat.rank();
  if (rank1 < N) {
    REP(i,N) mat[i].push_back(ary[i]);
    int rank2 = mat.rank();
    if (rank1 == rank2) cout << "ambiguous" << endl;
    else cout << "none" << endl;
    return 0;
  }
  auto lup = LUPDecomposition(mat);
  Vec<Bool> res = LUPBackSubstitution(lup, ary);
  REP(i,res.size()) {
    if (i > 0) cout << " ";
    cout << int(res[i]);
  }
  cout << endl;
  return 0;
}
