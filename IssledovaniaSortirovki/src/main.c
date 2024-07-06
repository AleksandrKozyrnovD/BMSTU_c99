#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include "../inc/comparator.h"
#include "../inc/fileread.h"
#include "../inc/filter.h"
#include "../inc/sort.h"

#define LEN 1000
#define COUNT 1000

typedef void (*sort)(void *, size_t, size_t, comparator_t);

typedef struct diff_t
{
    // long long int data[10000];
    long long x, y;
} diff_t;

int cmp_diff(const void *left, const void *right)
{
    const diff_t *l = left;
    const diff_t *r = right;
    
    return (l->x - r->x); // + (l->y - l->y);
}

static diff_t init_rand_diff_el(void)
{
    diff_t diff;
    diff.x = rand() % LEN;
    diff.y = rand() % LEN;

    return diff;
}

static void init_incr_diff(diff_t *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i].x = i;
        array[i].y = i;
    }
}

static void init_decr_diff(diff_t *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i].x = size - 1 - i;
        array[i].y = size - 1 - i;
    }
}

static void init_rand_diff(diff_t *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = init_rand_diff_el();
}

int cmp(const void *l, const void *r)
{
    const int *left = l;
    int const *right = r;

    return *left - *right;
}


unsigned long long microseconds_now(void)
{
    struct timeval value;

    if (gettimeofday(&value, NULL))
        return (unsigned long long) -1;
    
    return value.tv_sec * 1000ULL * 1000ULL + value.tv_usec;
}

static void init_incr(int *array, int size)
{
    // printf("MAXLEN = %d, size = %d\n", LEN, size);
    for (int i = 0; i < size; i++)
        array[i] = i;
}

static void init_decr(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = size - i - 1;
}


//srand in main!!!!
void init(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = (rand() % (size + size));
}

static void get_avg_increasing(int *array, double *data, int count, const int *lens, int sizelens, sort sort)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        init_incr(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}

static void get_avg_decreasing(int *array, double *data, int count, const int *lens, int sizelens, sort sort)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        init_decr(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}


static void get_avg_random(int *array, double *data,  int count, const int *lens, int sizelens, sort sort, int seed)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        srand(seed + len);
        init(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}

static void get_avg_increasing_diff(diff_t *array, double *data, int count, const int *lens, int sizelens, sort sort)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        init_incr_diff(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}

static void get_avg_decreasing_diff(diff_t *array, double *data, int count, const int *lens, int sizelens, sort sort)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        init_decr_diff(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}


static void get_avg_random_diff(diff_t *array, double *data,  int count, const int *lens, int sizelens, sort sort, int seed)
{
    unsigned long long beg = 0;
    unsigned long long end = 0;
    int n = 0.0;
    double avg = 0.0;
    
    for (int len = 0; len < sizelens; len++)
    {
        srand(seed + len);
        init_rand_diff(array, lens[len]);
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
        for (int i = 0; i < count; i++)
        {
            beg = microseconds_now();
            sort(array, lens[len], sizeof(int), cmp);
            end = microseconds_now();
            // data[i] = end - beg;
            n++;
            avg += end - beg;
        }
        data[len] = avg / n;
        n = 0;
        // printf("=========\n");
        // print(stdout, array, array + lens[len]);
        // printf("=========\n");
    }
}


static void print_data_file(FILE *file, int *lens, int sizelens, double *data)
{
    for (int i = 0; i < sizelens; i++)
        fprintf(file, "%d %.2lf\n", lens[i], data[i]);
}

int lens[] = { 1, 2, 5, 10, 25,
    50, 75, 100, 150,
    200, 250, 300, 350,
    400, 450, 500, 600,
    700, 800, 900, 1000};

int array[LEN];

diff_t darray[LEN];

int main(void)
{
    FILE *file;
    double times[COUNT];
    int seed = rand();


    int size_lens = sizeof(lens) / sizeof(*lens);
    // printf("Size lens = %d\n", size_lens);
    
    printf("Mysort vla started\n");
    file = fopen("./data/mysortvla_incr.txt", "w");
    get_avg_increasing(array, times, COUNT, lens, size_lens, mysort_vla);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortvla_decr.txt", "w");
    get_avg_decreasing(array, times, COUNT, lens, size_lens, mysort_vla);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortvla_rand.txt", "w");
    get_avg_random(array, times, COUNT, lens, size_lens, mysort_vla, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);


    printf("Mysort swap started\n");
    file = fopen("./data/mysortswap_incr.txt", "w");
    get_avg_increasing(array, times, COUNT, lens, size_lens, mysort_swap);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortswap_decr.txt", "w");
    get_avg_decreasing(array, times, COUNT, lens, size_lens, mysort_swap);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortswap_rand.txt", "w");
    get_avg_random(array, times, COUNT, lens, size_lens, mysort_swap, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);


    printf("Qsort started\n");
    file = fopen("./data/qsort_incr.txt", "w");
    get_avg_increasing(array, times, COUNT, lens, size_lens, qsort);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/qsort_decr.txt", "w");
    get_avg_decreasing(array, times, COUNT, lens, size_lens, qsort);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/qsort_rand.txt", "w");
    get_avg_random(array, times, COUNT, lens, size_lens, qsort, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);





    printf("Mysort vla struct started\n");
    file = fopen("./data/mysortvla_sincr.txt", "w");
    get_avg_increasing_diff(darray, times, COUNT, lens, size_lens, mysort_vla);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortvla_sdecr.txt", "w");
    get_avg_decreasing_diff(darray, times, COUNT, lens, size_lens, mysort_vla);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortvla_srand.txt", "w");
    get_avg_random_diff(darray, times, COUNT, lens, size_lens, mysort_vla, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);


    printf("Mysort swap struct started\n");
    file = fopen("./data/mysortswap_sincr.txt", "w");
    get_avg_increasing_diff(darray, times, COUNT, lens, size_lens, mysort_swap);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortswap_sdecr.txt", "w");
    get_avg_decreasing_diff(darray, times, COUNT, lens, size_lens, mysort_swap);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/mysortswap_srand.txt", "w");
    get_avg_random_diff(darray, times, COUNT, lens, size_lens, mysort_swap, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);


    printf("Qsort struct started\n");
    file = fopen("./data/qsort_sincr.txt", "w");
    get_avg_increasing_diff(darray, times, COUNT, lens, size_lens, qsort);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/qsort_sdecr.txt", "w");
    get_avg_decreasing_diff(darray, times, COUNT, lens, size_lens, qsort);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    
    file = fopen("./data/qsort_srand.txt", "w");
    get_avg_random_diff(darray, times, COUNT, lens, size_lens, qsort, seed);
    print_data_file(file, lens, size_lens, times);
    fclose(file);
    return EXIT_SUCCESSFUL;
}

