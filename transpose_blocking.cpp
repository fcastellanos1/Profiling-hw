/* Shows a way to do operations that require a specific order (e.g.,
 * transpositions) while avoiding cache misses. */

#include <iostream>
#include <cstdlib>
#include <algorithm>

int index1d(int ix, int iy, int iz, int n); // assumes square matrix
void fill(double * m1, double * m2, int n);
void direct_transpose(double * m1, double * m2, int n);
void cached_transpose(double * m1, double * m2, int n, int bsize);

int main(int argc, char *argv[]){
  if (argc < 3) {
    std::cerr << "Error. Usage:\n" << argv[0] << " n csize\nn: matriz size\ncsize: block size\n";
    std::exit(1);
  }
  int n = 0, csize = 0;
  n = std::atoi(argv[1]); // 512
  csize = std::atoi(argv[2]); // 32
  double *a, *b;

  int i, j, k, ii, jj, kk;

  // Allocating memory for array/matrix
  a = new double [n*n*n] {0.0};
  b = new double [n*n*n] {0.0};

  // function: fill(a, b, n)
  // Filling matrices with ones and minus ones
  fill(a, b, n);
  
  // function: direct_transpose(a, b, n)
  // Direct (inefficient) transposition
  direct_transpose(a, b, n);

  // function: cached_transpose(a, b, n, csize)
  // Transposition using cache-blocking
  cached_transpose(a, b, n, csize);

  // delete memory
  delete [] a;
  delete [] b;

  return 0;
}

int index1d(int ix, int iy, int iz, int n)
{
  return ix*n*n + iy*n + iz;
}
void fill(double * m1, double * m2, int n)
{
  int i, j, k, ii, jj, kk;
  for(i=0; i<n; ++i)
    for (j=0; j<n; ++j)
      for (k=0; k<n; ++k)
        m1[index1d(i, j, k, n)] = 1.0;
  for(i=0; i<n; ++i)
    for (j=0; j<n; ++j)
      for (k=0; k<n; ++k)
        m2[index1d(i, j, k, n)] = -1.0;
}
void direct_transpose(double * m1, double * m2, int n)
{
  int i, j, k, ii, jj, kk;
  for (i=0; i<n; ++i)
    for (j=0; j<n; ++j)
      for (k=0; k<n; ++k)
        m1[index1d(i, j, k, n)] = m2[index1d(k, j, i, n)];
}
void cached_transpose(double * m1, double * m2, int n, int bsize)
{
  int i, j, k, ii, jj, kk;
  for (ii=0; ii<n; ii+=bsize)
    for (jj=0; jj<n; jj+=bsize)
      for (kk=0; kk<n; kk+=bsize)
        for (i=ii; i<std::min(n,ii+bsize-1); ++i)
          for (j=jj; j<std::min(n,jj+bsize-1); ++j)
            for (k=kk; k<std::min(n,kk+bsize-1); ++k)
              m1[index1d(i, j, k, n)] = m2[index1d(k, j, i, n)];
}
