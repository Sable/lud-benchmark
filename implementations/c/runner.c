/*
 * =====================================================================================
 *
 *       Filename:  runner.c
 *
 *    Description:  The main wrapper for the suite
 *
 *        Version:  1.0
 *        Created:  10/22/2009 08:40:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liang Wang (lw2aw), lw2aw@virginia.edu
 *        Company:  CS@UVa
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "ostrich_twister_rand.h"

static int do_verify = 0;

static struct option long_options[] = {
    /* name, has_arg, flag, val */
    {"input", 1, NULL, 'i'},
    {"size", 1, NULL, 's'},
    {"verify", 0, NULL, 'v'},
    {0,0,0,0}
};

extern void
lud_base(double *m, int matrix_dim);

int
main ( int argc, char *argv[] )
{
    int matrix_dim = 32; /* default matrix_dim */
    int opt, option_index=0, error=0;
    func_ret_t ret;
    char *output_path = NULL;
    FILE *file;
    double *m;
    stopwatch sw;
    int i,j;
    int debug = 0;
    size_t linesiz=0;
    char* linebuf=NULL;
    ssize_t linelen=0;
    char* token;
    const char comma[2] = ",";

    while ((opt = getopt_long(argc, argv, ":s:",
                              long_options, &option_index)) != -1 ) {
        switch(opt){
        case 's':
            matrix_dim = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "invalid option\n");
            error=1;
            break;
        case ':':
            fprintf(stderr, "missing argument\n");
            error=1;
            break;
        default:
            error=1;
        }
    }

    if ((optind < argc) || (optind == 1) || error) {
        fprintf(stderr, "Usage: %s -s size \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    m = (double *)malloc(sizeof(double) * matrix_dim * matrix_dim);

    ostrich_rand_seed(1337);

    // The matrix is stored row-major, but the
    // numbers are generated column-wise to follow
    // the rand function convention in Matlab
    for (i = 0; i < matrix_dim; ++i) {
        for ( j = 0; j < matrix_dim; ++j) {
            m[j*matrix_dim + i] = floor(ostrich_rand_double()*10000);
        }
    }


    /*
    printf("Input:\n");
    for (i = 0; i < matrix_dim; ++i) {
        for ( j = 0; j < matrix_dim; ++j) {
            printf("%d ", (int)m[i*matrix_dim + j]);
        }
        printf("\n");
    }
    */

    int checksum_input = fletcher_sum_2d_array(m, matrix_dim, matrix_dim);

    printf("input checksum: %d\n", checksum_input);

    stopwatch_start(&sw);
    lud_base(m, matrix_dim);
    stopwatch_stop(&sw);

    for (i = 0; i < matrix_dim*matrix_dim; ++i) {
        m[i] = floor(m[i]*100);
    }

    /*
    printf("Output:\n");
    for (i = 0; i < matrix_dim; ++i) {
        for ( j = 0; j < matrix_dim; ++j) {
            printf("%d ", (int)m[i*matrix_dim + j]);
        }
        printf("\n");
    }
    */

    int checksum = fletcher_sum_2d_array(m, matrix_dim, matrix_dim);

    free(m);
    printf("{ \"status\": %d, \"options\": \"-s %d\", \"time\": %f, \"output\": %d }\n", 1, matrix_dim, get_interval_by_sec(&sw), checksum);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
