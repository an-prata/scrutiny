#include "../scrutiny/scrutiny.h"

static bool is_prime(uint64_t n)
{
    if (n == 0 || n == 1)
        return false;

    for (uint64_t i = 2; i < n / 2; i++)
        if (n % i == 0)
            return false;

    return true;
}

SCRUTINY_BENCHMARK primes_to_n_benchmark(void)
{
    const uint64_t n = 4096;
    uint64_t largest_prime = 0;

    /* Starts the benchmark timer. */
    scrutiny_benchamrk_start();

    /* Benchmark code, here we find the largest prime up to n. */
    for (uint64_t i = 0; i <= n; i++)
        if (is_prime(i))
            largest_prime = i;

    /* Ends the benchmark timer. */
    scrutiny_benchmark_finish();

    /* Use this space to free memory or I/O. */
}

int main()
{
    scrutiny_benchmark_t benchmarks[] = 
    {
        primes_to_n_benchmark,
        NULL
    };

    /* Run all given benchmarks once. */
    //scrutiny_run_benchmarks(benchmarks);

    /* Run all given benchmarks the given number of times. */
    scrutiny_run_benchmarks_n_times(benchmarks, 16);

    /* Output test results. */
    scrutiny_output_benchmark_results(stdout);
    
    /* Output a more parsable results text. */
    //file_t* file = fopen("out.txt", "w");
    //scrutiny_output_benchmark_results_parsable(file);
}

