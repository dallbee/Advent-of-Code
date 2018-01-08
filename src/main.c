#define _GNU_SOURCE

#include "common.h"
#include <argp.h>
#include <klib/kvec.h>
#include <regex.h>
#include <sds/sds.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_bug_address = "<dylan@allbee.org>";
const char *doc = "Advent of Code 2017 Solver";
const char *args_doc = "challenge";

static struct argp_option options[] = {
    {"", 'a', 0, 0, "Only display solution to part a"},
    {"", 'b', 0, 0, "Only display solution to part b"},
    {"output", 'o', "FILE", 0, "Output to FILE instead of standard output"},
    {0}};

struct arguments {
  int problem;
  enum { ALL, A, B } part;
  char *output_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
  case 'a':
    arguments->part = A;
    break;
  case 'b':
    arguments->part = B;
    break;
  case 'o':
    arguments->output_file = arg;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num > 1) {
      argp_usage(state);
    }
    arguments->problem = arg ? atoi(arg) : -1;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1) {
      argp_usage(state);
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

sdsvec read_lines(FILE *stream) {
  sdsvec input;
  kv_init(input);

  ssize_t nread;
  size_t size;
  char *line = NULL;

  while ((nread = getline(&line, &size, stream)) != -1) {
    kv_push(sds, input, sdsnewlen(line, nread));
  }
  free(line);

  return input;
}

void destroy_lines(sdsvec input) {
  while (kv_size(input)) {
    sdsfree(kv_pop(input));
  }
  kv_destroy(input);
}

solver_t solvers[50] = {
    solve_01_a, solve_01_b, solve_02_a, solve_02_b, solve_03_a, solve_03_b,
    solve_04_a, solve_04_b, solve_05_a, solve_05_b, solve_06_a, solve_06_b,
    solve_07_a, solve_07_b, solve_08_a, solve_08_b, solve_09_a, solve_09_b,
    solve_10_a, solve_10_b, solve_11_a, solve_11_b, solve_12_a, solve_12_b,
    solve_13_a, solve_13_b, solve_14_a, solve_14_b, solve_15_a, solve_15_b,
    solve_16_a, solve_16_b, solve_17_a, solve_17_b, solve_18_a, solve_18_b,
    solve_19_a, solve_19_b, solve_20_a, solve_20_b, solve_21_a, solve_21_b,
    solve_22_a, solve_22_b, solve_23_a, solve_23_b, solve_24_a, solve_24_b,
    solve_25_a, solve_25_b,
};

static int write_solution(FILE *fp, sdsvec input, solver_t solver) {
  sds output = sdscat(solver(input), "\n");
  size_t len = sdslen(output);
  size_t bytes_written = fwrite(output, sizeof(output[0]), len, fp);
  sdsfree(output);
  return bytes_written == len ? 0 : -1;
}

int main(int argc, char *argv[]) {
  struct argp argp = {
      .options = options,
      .parser = parse_opt,
      .args_doc = args_doc,
      .doc = doc,
  };

  struct arguments args = {0};
  args.output_file = "-";
  args.part = ALL;

  if (argp_parse(&argp, argc, argv, 0, 0, &args)) {
    return -1;
  }

  if (args.problem < 1 || args.problem > (int)(count(solvers) / 2)) {
    return -1;
  }

  FILE *fp = stdout;
  if (strncmp(args.output_file, "-", 2) != 0) {
    if ((fp = fopen(args.output_file, "we")) == NULL) {
      return -1;
    }
  }

  sdsvec input = read_lines(stdin);
  if (kv_size(input) == 0) {
    fprintf(stderr, "empty input provided\n");
    goto cleanup;
  }

  if (args.part == ALL || args.part == A) {
    if (write_solution(fp, input, solvers[2 * (args.problem - 1)])) {
      return -1;
    }
  }

  if (args.part == ALL || args.part == B) {
    if (write_solution(fp, input, solvers[2 * (args.problem - 1) + 1])) {
      return -1;
    }
  }

cleanup:
  destroy_lines(input);
  fclose(fp);
  return 0;
}
