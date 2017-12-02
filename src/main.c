#define _GNU_SOURCE

#include <argp.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include "common.h"

const char *argp_program_bug_address = "<dylan@allbee.org>";
const char *doc = "Advent of Code 2017 Solver";
const char *args_doc = "challenge[:part]";

static struct argp_option options[] = {
    {"output", 'o', "FILE", 0, "Output to FILE instead of standard output"},
    { 0 }
};

struct arguments {
    char *args[1];
    char *output_file;
};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    struct arguments *arguments = state->input;

    switch(key) {
    case 'o':
        arguments->output_file = arg;
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num > 2)
            argp_usage(state);
        arguments->args[state->arg_num] = arg;
    break;
    case ARGP_KEY_END:
        if (state->arg_num < 1)
            argp_usage(state);
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
    for (size_t i = kv_size(input); i != 0; --i) {
        sdsfree(kv_A(input, i));
    }
    kv_destroy(input);
}

solver_t solvers[50] = {
    solve_01_a, solve_01_b,
    solve_02_a, solve_02_b,
    solve_03_a, solve_03_b,
    solve_04_a, solve_04_b,
    solve_05_a, solve_05_b,
    solve_06_a, solve_06_b,
    solve_07_a, solve_07_b,
    solve_08_a, solve_08_b,
    solve_09_a, solve_09_b,
    solve_10_a, solve_10_b,
    solve_11_a, solve_11_b,
    solve_12_a, solve_12_b,
    solve_13_a, solve_13_b,
    solve_14_a, solve_14_b,
    solve_15_a, solve_15_b,
    solve_16_a, solve_16_b,
    solve_17_a, solve_17_b,
    solve_18_a, solve_18_b,
    solve_19_a, solve_19_b,
    solve_20_a, solve_20_b,
    solve_21_a, solve_21_b,
    solve_22_a, solve_22_b,
    solve_23_a, solve_23_b,
    solve_24_a, solve_24_b,
    solve_25_a, solve_25_b,
};

solver_t lookup_solver(char *arg) {
    regex_t regex;
    if (regcomp(&arg_regex, "^(\\d){1,2}:(\\d)?$", REG_EXTENDED))
        return NULL;

    regmatch_t matches[3];
    if (regexec(&arg_regex, arg, 3, matches, 0))
        return NULL;

    return solvers[0];
}

int main(int argc, char *argv[]) {
    struct argp argp = {
        .options = options,
        .parser = parse_opt,
        .args_doc = args_doc,
        .doc = doc,
    };

    struct arguments arguments = { 0 };
    arguments.output_file = "-";

    if (argp_parse(&argp, argc, argv, 0, 0, &arguments))
        return -1;

    sdsvec input = read_lines(stdin);
    solver_t solver = lookup_solver(arguments.args[0]);
    if (solver == NULL)
        return -1;

    sds output = solver(input);
    destroy_lines(input);

    FILE *fp = stdout;
    if (strncmp(arguments.output_file, "-", 2)) {
        if ((fp = fopen(arguments.output_file, "w")) == NULL)
            return -1;
    }

    if (fwrite(output, sizeof(output[0]), sdslen(output), fp) < sdslen(output))
        return -1;

    sdsfree(output);
    fclose(fp);
    return 0;
}


