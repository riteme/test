#ifndef SATELLITE_H
#define SATELLITE_H

#include <cstddef>

void initialize(int n);
void search(int &u, int &v);

bool query(int a[], size_t na, int b[], size_t nb);

#endif  // SATELLITE_H
