#include "cachelab.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

/**
 * Store information of a cache line:
 * Valid bit, tag bits, and block id
*/
typedef struct {
    
} Line;

void print_usage(const char *prog_name) {
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", prog_name);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("Examples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", prog_name);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", prog_name);
}

int main(int argc, char *argv[])
{
    bool isVerbose = 0;
    char* trace_file = NULL;
    int opt, s = 0, E = 0, b = 0;

    while (-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'v':
                isVerbose = true; 
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg); 
                break;
            case 'b':
                b = atoi(optarg); 
                break;
            case 't':
                trace_file = optarg; 
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("Missing required command line argument\n");
        print_usage(argv[0]); 
        return 1;
    }

    printf("s: %d\n", s);
    printf("E: %d\n", E);
    printf("b: %d\n", b);
    printf("Trace file: %s\n", trace_file ? trace_file : "None");
    if (isVerbose) {
        printf("Is Verbose\n");
    }

    FILE* pFile;
    pFile = fopen(trace_file, "r");
    char identifier;
    unsigned address;
    int size;

    while(fscanf(pFile, " %c %x,%d", &identifier, &address, &size) > 0) {
        printf("ident: %c\n", identifier);
        printf("address: %x\n", address);
        printf("size: %d\n", size);
    }
    
    printSummary(0, 0, 0);
    return 0;
}
