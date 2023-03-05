#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

int h, v, s, E, b;
char t[1024];

int hits = 0;
int misses = 0;
int evictions = 0;

typedef struct {
  int tag;
  int valid;
  int time;
} cache_line;

cache_line **cache;

void init() {
  int nsets = 1 << s;
  cache = (cache_line**) malloc(nsets * sizeof(cache_line));
  for (int i = 0; i < nsets; ++i) {
    cache[i] = (cache_line*) malloc(E * sizeof(cache_line));
    memset(cache[i], 0, E * sizeof(cache_line));
  }
}

void clean() {
  int nsets = 1 << s;
  for (int i = 0; i < nsets; ++i) {
    free(cache[i]);
  }
  free(cache);
}

void lru_update() {
  int nsets = 1 << s;
  for (int i = 0; i < nsets; ++i) {
    for (int j = 0; j < E; ++j) {
      cache[i][j].time++;
    }
  }
}

void access(unsigned long addr) {
  unsigned long tag = addr >> (b + s);
  unsigned long nsets = (addr << (64 - b - s)) >> (64 - s);
  cache_line *sets = cache[nsets];

  for (int i = 0; i < E; ++i) {
    if (sets[i].valid && sets[i].tag == tag) {
      hits++;
      sets[i].time = 0;
      return ;
    }
  }

  misses++;
  for (int i = 0; i < E; ++i) {
    if (!sets[i].valid) {
      sets[i].valid = 1;
      sets[i].tag = tag;
      sets[i].time = 0;
      return ;
    }
  }

  evictions++;
  int e_idx = 0;
  int max_time = 0;
  for (int i = 0; i < E; ++i) {
    if (sets[i].time > max_time) {
      max_time = sets[i].time;
      e_idx = i;
    }
  }

  sets[e_idx].tag = tag;
  sets[e_idx].time = 0;
}

void simulate() {
  FILE *fp = fopen(t, "r");
  if (!fp) {
    printf("%s: No such file or directory\n", t);
    exit(-1);
  }

  char op;
  unsigned long addr;
  int size;
  while (~fscanf(fp, " %c %lx,%d", &op, &addr, &size)) {
    switch (op) {
      case 'M':
        access(addr);
      case 'L':
      case 'S':
        access(addr);
        break;
    }
    lru_update();
  }

  fclose(fp);
}

void print_help() {
  printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
  printf("Options:\n");
  printf("-h         Print this help message.\n");
  printf("-v         Optional verbose flag.\n");
  printf("-s <num>   Number of set index bits.\n");
  printf("-E <num>   Number of lines per set.\n");
  printf("-b <num>   Number of block offset bits.\n");
  printf("-t <file>  Trace file.\n\n\n");
  printf("Examples:\n");
  printf("linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
  printf("linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

int main(int argc, char **argv)
{
  char opt;
  while (~(opt = getopt(argc, argv, "hvs:E:b:t:"))) {
    switch (opt) {
      case 'v':
        v = 1;
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
        strcpy(t, optarg);
        break;
      case 'h':
        print_help();
        exit(0);
        break;
      default:
        print_help();
        exit(-1);
    }
  }
  init();
  simulate();
  printSummary(hits, misses, evictions);
  clean();
  return 0;
}
