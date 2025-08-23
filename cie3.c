//Modify the prgm to find the largest prime number less than n
 #include <stdio.h>
#include <omp.h>
#include <math.h>
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0) return 0;
    return 1;
}
int main() {
    int n;
    printf("Enter upper limit (n): ");
    scanf("%d", &n);
    if (n <= 2) {
        printf("No prime less than %d\n", n);
        return 0;
    }
    double start = omp_get_wtime();
    int largest_seq = -1;
    for (int i = n - 1; i >= 2; i--) {
        if (is_prime(i)) {
            largest_seq = i;
            break;
        }
    }
    double time_seq = omp_get_wtime() - start;
    printf("Sequential: Largest prime < %d is %d, time: %f s\n", n, largest_seq, time_seq);
    start = omp_get_wtime();
    int largest_par = -1;
    #pragma omp parallel for schedule(static)
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            #pragma omp critical
            if (i > largest_par) largest_par = i;
        }
    }
    double time_par = omp_get_wtime() - start;
    printf("Parallel:   Largest prime < %d is %d, time: %f s\n", n, largest_par, time_par);
    if (time_par > 0 && time_seq > 0)
        printf("Speedup: %.2fx\n", time_seq / time_par);
    return 0;
}