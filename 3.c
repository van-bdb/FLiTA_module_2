#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_TYPE long

typedef unsigned long vertex;

typedef struct {
    vertex start;
    vertex end;
} edge;


void sort(unsigned long long len, DATA_TYPE arr[]);

edge* read_file(FILE* fp, unsigned long long len){
    edge* arr = malloc(len * sizeof(edge));
    for(unsigned long long i = 0; i<len; i++)
        fscanf(fp, "%Ld %Ld", &((arr+i)->start), &((arr+i)->end));
    return arr;
}

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
    edge* arr = read_file(fp, len);
    fclose(fp);
    time_t begin = clock();
    search_max(len, arr);
    time_t end = clock();
    printf("Time taken \t%f\n", ((double)(end - begin))/CLOCKS_PER_SEC);
}

vertex count(unsigned long long len, edge arr[]){
    vertex vertex_len = 0;
    for (unsigned long long i = 0; i<len; i++){
        if (arr[i].end > vertex_len) vertex_len = arr[i].end;
        if (arr[i].start > vertex_len) vertex_len = arr[i].start;
    }
    return vertex_len;
}

void search_max(unsigned long long len_e, edge arr_e[]){
    printf("\nHighest degree vertexes:\t");
    vertex len_v = count(len_e, arr_e);
    unsigned long* arr_v = malloc(len_v * sizeof(unsigned long));
    for (vertex i = 0; i<len_v; i++) arr_v[i] = 0;
    for (unsigned long long i = 0; i<len_e; i++){
        arr_v[arr_e[i].end]++;
        arr_v[arr_e[i].start]++;
    }
    unsigned long max_v = 0;
    for (vertex i = 0; i<len_v; i++) if (arr_v[i] > max_v) max_v = arr_v[i];
    for (vertex i = 0; i<len_v; i++) if (arr_v[i] == max_v) printf("%d ", i);
    printf("\nwith a degree of %d\n", max_v);
}
