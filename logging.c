// logging.c

#include "logging.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct log {
  char info[256];
  struct log *next;
};

struct logging {
  struct log *first;
  struct log *last;
};

Logging *create_logging() {
  Logging *logging = (Logging *)malloc(sizeof(Logging));

  logging->first = NULL;
  logging->last = NULL;
  return logging;
}

void write_log(Logging *logging, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char info[256];
  vsnprintf(info, sizeof(info), format, args);

  va_end(args);

  Log *new_log = (Log *)malloc(sizeof(Log));
  strncpy(new_log->info, info, sizeof(new_log->info));
  new_log->next = NULL;

  if (logging->last == NULL) {
    logging->first = new_log;
    logging->last = new_log;
  } else {
    logging->last->next = new_log;
    logging->last = new_log;
  }

  // Imprimir no console
  printf("%s\n", info);
}

void print_logs(Logging *logging, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  Log *current_log = logging->first;
  while (current_log != NULL) {
    fprintf(file, "%s\n", current_log->info);
    current_log = current_log->next;
  }

  fclose(file);
}
