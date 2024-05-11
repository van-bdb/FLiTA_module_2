#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_TYPE long

void sort(unsigned long long len, DATA_TYPE arr[]);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("No filename provided\n");
        return(0);
    }
    FILE* fp;
    if (!(fp=fopen(argv[1],"r"))){
        printf("Can't open file\n");
        return(0);
    }
    unsigned long long len;
    if (argc < 3) {
        fscanf(fp, "%ULLd", &len);
    } else {
        len = atoi(argv[2]);
    }
    DATA_TYPE* arr = malloc(len * sizeof(DATA_TYPE));
    for(unsigned long long i = 0; i<len; i++) fscanf(fp, "%LLd", arr+i);
    time_t begin = clock();
    sort(len, arr);
    time_t end = clock();
    printf("Time taken \t%f\n", ((double)(end - begin))/CLOCKS_PER_SEC);
    int flag = 1;
    for(unsigned long long i = 1; i<len; i++) if (arr[i]<arr[i-1]) flag = 0;
    if(flag){
        printf("Array became sorted\n");
    } else {
        printf("Array NOT sorted\n");
        for(unsigned long long i = 0; i<len; i++) printf("%i\n", arr[i]);
    }
    fclose(fp);
}


void sort(unsigned long long len, DATA_TYPE arr[]){
    DATA_TYPE min = arr[0];
    DATA_TYPE max = arr[0];
    for (unsigned long long i = 0; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        else if (arr[i] > max) {
            max = arr[i];
        }
    }

    DATA_TYPE counts_len = max - min + 1;
    //printf("counts_len=%i\n", counts_len);
    unsigned long* counts = malloc(counts_len * sizeof(unsigned long));
    for(DATA_TYPE i = 0; i<counts_len; i++) counts[i] = 0;
    for(unsigned long long i = 0; i<len; i++) counts[arr[i] - min]++;

    unsigned long long index = 0;
    for(DATA_TYPE i = 0; i<counts_len; i++){
        for(unsigned long j = 0; j<counts[i]; j++){
            arr[index]=min+i;
            index++;
        }
    }
};
/*

void fast_sort(unsigned long long l, unsigned long long r, DATA_TYPE a[]);
unsigned long long int partition(unsigned long long l, unsigned long long r, DATA_TYPE a[]);
void swap(DATA_TYPE* ptr1, DATA_TYPE* ptr2);
void print(DATA_TYPE a[]);

void sort(unsigned long long len, DATA_TYPE arr[]){
    fast_sort(0, len, arr);
}

unsigned long long int partition(unsigned long long l, unsigned long long r, DATA_TYPE a[]) {
    //print(a);
    DATA_TYPE pivot = a[r-1];
    unsigned long long i = l;
    unsigned long long m = r-1;
    while (i < m) {
        if (a[i] > pivot) {
            swap(&a[i], &a[m - 1]);
            swap(&a[m - 1], &a[m]);
            m--;
        }
        if (a[i] <= pivot) {
            i++;
        }
    }
    return m;
}

//void print(DATA_TYPE a[]) {
//    int len = 15;
//    for (int i = 0; i < len; i++) printf("%d ", *(a + i));
//    printf("\n");
//}

void swap(DATA_TYPE* ptr1, DATA_TYPE* ptr2) {
    DATA_TYPE temp;
    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void fast_sort(unsigned long long l, unsigned long long r, DATA_TYPE a[]) {
    //printf("%d   %d   ", l, r);
    if (r - l <= 1) {
        return;
    }
    unsigned long long m = partition(l, r, a);
    fast_sort(l, m, a);
    fast_sort(m, r, a);
}
*/
