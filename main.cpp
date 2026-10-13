#include <iostream>
#include <cstddef>

void destroy(int ** m, size_t rows)
{
  for (size_t i = 0; i < rows; ++i) {
    delete[] m[i];
  }
  delete[] m;
}

int ** create(size_t rows, size_t cols)
{
  int ** m = nullptr;
  size_t created = 0;
  try {
    m = new int * [rows];
    for (; created < rows; ++created) {
      m[created] = new int[cols];
    }
  } catch (...) {
    destroy(m, created);
    return nullptr;
  }
  return m;
}

int ** read_matrix(size_t & rows, size_t & cols, int & err)
{
  std::cin >> rows >> cols;
  if (!std::cin) {
    err = 1;
    return nullptr;
  }
  int ** m = create(rows, cols);
  if (!m) {
    err = 2;
    return nullptr;
  }
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> m[i][j];
    }
  }
  if (!std::cin) {
    destroy(m, rows);
    err = 1;
    return nullptr;
  }
  return m;
}

size_t max_size(size_t a, size_t b)
{
  if (a > b) {
    return a;
  }
  return b;
}

size_t row_len(size_t i, size_t n1, size_t m1, size_t n2, size_t m2)
{
  size_t len = 0;
  if (i < n1) {
    len += m1;
  }
  if (i < n2) {
    len += m2;
  }
  return len;
}

int ** concat_rows(
  const int * const * lhs, size_t n1, size_t m1,
  const int * const * rhs, size_t n2, size_t m2)
{
  size_t n = max_size(n1, n2);
  int ** res = nullptr;
  size_t created = 0;
  try {
    res = new int * [n];
    for (; created < n; ++created) {
      res[created] = new int[row_len(created, n1, m1, n2, m2)];
    }
  } catch (...) {
    destroy(res, created);
    return nullptr;
  }
  for (size_t i = 0; i < n; ++i) {
    size_t k = 0;
    for (size_t j = 0; i < n1 && j < m1; ++j) {
      res[i][k++] = lhs[i][j];
    }
    for (size_t j = 0; i < n2 && j < m2; ++j) {
      res[i][k++] = rhs[i][j];
    }
  }
  return res;
}

void output(const int * const * m, size_t n1, size_t m1, size_t n2, size_t m2)
{
  for (size_t i = 0; i < max_size(n1, n2); ++i) {
    size_t len = row_len(i, n1, m1, n2, m2);
    for (size_t j = 0; j < len; ++j) {
      if (j != 0) {
        std::cout << " ";
      }
      std::cout << m[i][j];
    }
    std::cout << "\n";
  }
}

int main()
{
  size_t n1 = 0, m1 = 0, n2 = 0, m2 = 0;
  int err = 0;
  int ** a = read_matrix(n1, m1, err);
  if (!a) {
    return err;
  }
  int ** b = read_matrix(n2, m2, err);
  if (!b) {
    destroy(a, n1);
    return err;
  }
  int ** c = concat_rows(a, n1, m1, b, n2, m2);
  if (!c) {
    destroy(b, n2);
    destroy(a, n1);
    return 2;
  }
  output(c, n1, m1, n2, m2);
  destroy(c, max_size(n1, n2));
  destroy(b, n2);
  destroy(a, n1);
}
