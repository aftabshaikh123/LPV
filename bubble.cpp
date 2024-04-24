#include <iostream>
#include <omp.h>

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b) {
    int temp = a; a = b; b = temp;
}

int main() {
    int *a, n;
    std::cout << "Enter total number of elements: "; std::cin >> n;
    a = new int[n];
    std::cout << "Enter elements: ";
    for (int i = 0; i < n; i++) std::cin >> a[i];
    bubble(a, n);
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << std::endl;
    delete[] a;
    return 0;
}
