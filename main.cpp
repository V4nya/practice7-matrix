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

bool input(int ** m, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> m[i][j];
      if (!std::cin) {
        return false;
      }
    }
  }
  return true;
}

void transpose(int ** from, int ** to, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      to[j][i] = from[i][j];
    }
  }
}

void output(int ** m, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
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
  size_t rows = 0, cols = 0;
  std::cin >> rows >> cols;
  if (!std::cin) {
    std::cerr << "Bad input\n";
    return 1;
  }

  int ** m = create(rows, cols);
  if (m == nullptr) {
    std::cerr << "Bad alloc\n";
    return 2;
  }

  if (!input(m, rows, cols)) {
    destroy(m, rows);
    std::cerr << "Bad input\n";
    return 1;
  }

  int ** t = create(cols, rows);
  if (t == nullptr) {
    destroy(m, rows);
    std::cerr << "Bad alloc\n";
    return 2;
  }

  transpose(m, t, rows, cols);
  output(t, cols, rows);

  destroy(t, cols);
  destroy(m, rows);
  return 0;
}

