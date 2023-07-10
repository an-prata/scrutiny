#include "../scrutiny/scrutiny.h"
#include <time.h>
#include <unistd.h>

static bool is_prime(unsigned long n) {
    if (n == 0 || n == 1)
        return false;

    for (unsigned long i = 2; i < n / 2; i++)
        if (n % i == 0)
            return false;

    return true;
}

SCRUTINY_BENCHMARK(primes_to_n) {
    const unsigned long n = 4096;
    unsigned long largest_prime = 0;

    for (unsigned long i = 0; i <= n; i++)
        if (is_prime(i))
            largest_prime = i;

    scrutiny_bench_return();
}

// This benchmark will take a long time but much of it will be idle.
SCRUTINY_BENCHMARK(wait_1_sec) {
    sleep(1);
    scrutiny_bench_return();
}

int main()
{
    scrutiny_benchmark_t benchmarks[] = 
    {
        primes_to_n,
        wait_1_sec,
        NULL
    };

    // Scrutiny will output both the actual time and CPU time used when running
    // a benchmark. Unlike when unit testing scrutiny will not exit the program
    // here.
    scrutiny_run_benchmarks(benchmarks, 1);
}

