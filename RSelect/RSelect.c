#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void swap(void* a, char* b, size_t size)
{
    void* tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}

size_t partition(char* arr, size_t s, size_t n, int (*compFunc)(void const*, void const*))
{
    size_t i = 0;
    for (size_t j = 0; j < n; j++) {
        if ((*compFunc)(arr + j * s, arr) <= 0)
            swap(arr + s * i++, arr + j * s, s);
    }
    swap(arr, arr + (i - 1) * s, s);
    return i - 1;
}

void* RSelect(void* arr, size_t n, size_t sizeOfElem, int (*compFunc)(void const*, void const*), size_t i)
{
    if (n == 1)
        return arr;
    size_t p = rand() % n;
    size_t ip = partition(arr,sizeOfElem, n, compFunc);
    if (ip == i)
        return (char*)arr + i * sizeOfElem;
    else if (ip > i)
        return RSelect(arr, ip, sizeOfElem, compFunc, i);
    else
        return RSelect((char*)arr+sizeOfElem*(ip+1), n-ip-1, sizeOfElem, compFunc, i-ip-1);
}

int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n = 1000;
    int* a = (int*)calloc(n, sizeof(int));
    int* b = (int*)calloc(n, sizeof(int));
    if (!a || !b)
        exit(1);
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        for (int i = 0; i < n; i++)
            a[i] = rand();
        memcpy(b, a, n * sizeof(int));
        qsort(b, n, sizeof(int), compare);
        int j = rand() % n;
        printf("Порядковая х-ка %d случайного массива:\t", j);
        if (b[j] == *(int*)RSelect(a, n, sizeof(int), compare, j))
            printf("Сошлась\n");
        else
            printf("Не судьба\n");
    }
    return 0;
}