/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "cwh", /* Team name */

    "Harry Q. Bovik",    /* First member full name */
    "bovik@nowhere.edu", /* First member email address */

    "Harry Q. Bovik",   /* Second member full name (leave blank if none) */
    "bovik@nowhere.edu" /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

char rotate1_descr[] = "rotate1";
void rotate1(int dim, pixel *src, pixel *dst)
{
    int i, j;
    for (j = 0; j < dim; j++)
        for (i = 0; i < dim; i++)
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

char rotate2_descr[] = "rotate2";
void rotate2(int dim, pixel *src, pixel *dst)
{
    const int block_size = 16;
    for (int i = 0; i < dim; i += block_size)
        for (int j = 0; j < dim; j += block_size)
            for (int x = i; x < i + block_size; ++x)
                for (int y = j; y < j + block_size; ++y)
                {
                    dst[RIDX(dim - 1 - y, x, dim)] = src[RIDX(x, y, dim)];
                }
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
    // RIDX(i,j,n) ((i)*(n)+(j))
    const int block_size = 8;

    for (int j = 0; j < dim; j += block_size)
        for (int i = 0; i < dim; i += block_size)
            for (int x = i; x < i + block_size; ++x)
                for (int y = j; y < j + block_size; ++y)
                {
                    dst[RIDX(dim - 1 - y, x, dim)] = src[RIDX(x, y, dim)];
                }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions()
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    add_rotate_function(&rotate1, rotate1_descr);
    add_rotate_function(&rotate2, rotate2_descr);
    add_rotate_function(&rotate, rotate_descr);
    /* ... Register additional test functions here */
}

/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct
{
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
    sum->red += (int)p.red;
    sum->green += (int)p.green;
    sum->blue += (int)p.blue;
    sum->num++;
    return;
}

static void minus_sum(pixel_sum *sum, pixel p)
{
    sum->red -= (int)p.red;
    sum->green -= (int)p.green;
    sum->blue -= (int)p.blue;
    sum->num--;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short)(sum.red / sum.num);
    current_pixel->green = (unsigned short)(sum.green / sum.num);
    current_pixel->blue = (unsigned short)(sum.blue / sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel_sum avg_sum(int dim, int i, int j, pixel *src)
{
    int ii, jj;
    pixel_sum sum;

    initialize_pixel_sum(&sum);
    for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
        for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    return sum;
}

static pixel avg(int dim, int i, int j, pixel *src)
{
    pixel current_pixel;
    assign_sum_to_pixel(&current_pixel, (avg_sum(dim, i, j, src)));
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

char smooth1_descr[] = "smooth1";
void smooth1(int dim, pixel *src, pixel *dst)
{
    // edge
    for (int i = 0; i < dim; i++)
        dst[RIDX(i, 0, dim)] = avg(dim, i, 0, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(i, dim - 1, dim)] = avg(dim, i, dim - 1, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(0, i, dim)] = avg(dim, 0, i, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(dim - 1, i, dim)] = avg(dim, dim - 1, i, src);

    // center
    for (int i = 1; i < dim - 1; i++)
    {
        pixel_sum sum = avg_sum(dim, i, 0, src);
        for (int j = 1; j < dim - 1; j++)
        {
            accumulate_sum(&sum, src[RIDX(i - 1, j + 1, dim)]);
            accumulate_sum(&sum, src[RIDX(i, j + 1, dim)]);
            accumulate_sum(&sum, src[RIDX(i + 1, j + 1, dim)]);
            // if (sum.blue != avg_sum(dim, i, j, src).blue)
            // {
            //     printf("%d,%d,%d\n", i, j, sum.num);
            //     return;
            // }
            // pixel_sum sum = avg_sum(dim, i, j, src);
            assign_sum_to_pixel(&dst[RIDX(i, j, dim)], sum);
            // dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
            // printf("%d,%d,%d\n", i, j, sum.num);
            minus_sum(&sum, src[RIDX(i - 1, j - 1, dim)]);
            minus_sum(&sum, src[RIDX(i, j - 1, dim)]);
            minus_sum(&sum, src[RIDX(i + 1, j - 1, dim)]);
            // printf("%d,%d,%d\n", i, j, sum.num);
        }
    }
}

typedef struct
{
    int red;
    int green;
    int blue;
} pixel_long;

void add_pixel(pixel_long *a, pixel_long b)
{
    a->red += (int)b.red;
    a->green += (int)b.green;
    a->blue += (int)b.blue;
}

void minus_pixel(pixel_long *a, pixel_long b)
{
    a->red -= (int)b.red;
    a->green -= (int)b.green;
    a->blue -= (int)b.blue;
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    pixel_long *prefix_sum = (pixel_long *)
        malloc(dim * dim * sizeof(pixel_long));

    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j)
        {
            // prefix_sum[i][j] = prefix_sum[i][j - 1] +
            //                    prefix_sum[i - 1][j] +
            //                    w[i][j] -
            //                    prefix_sum[i - 1][j - 1];
            int idx = RIDX(i, j, dim);
            pixel_long sum;
            sum.blue = src[idx].blue;
            sum.green = src[idx].green;
            sum.red = src[idx].red;
            if (j - 1 >= 0)
                add_pixel(&sum, prefix_sum[idx - 1]);
            if (i - 1 >= 0)
                add_pixel(&sum, prefix_sum[idx - dim]);
            if (i - 1 >= 0 && j - 1 >= 0)
                minus_pixel(&sum, prefix_sum[idx - dim - 1]);
            prefix_sum[idx] = sum;
        }

    // edge
    for (int i = 0; i < dim; i++)
        dst[RIDX(i, 0, dim)] = avg(dim, i, 0, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(i, dim - 1, dim)] = avg(dim, i, dim - 1, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(0, i, dim)] = avg(dim, 0, i, src);
    for (int i = 0; i < dim; i++)
        dst[RIDX(dim - 1, i, dim)] = avg(dim, dim - 1, i, src);

    // center
    for (int i = 1; i < dim - 1; i++)
        for (int j = 1; j < dim - 1; j++)
        {
            int idx = RIDX(i, j, dim);
            pixel_long sum = prefix_sum[idx + dim + 1];
            if (j - 2 >= 0)
                minus_pixel(&sum, prefix_sum[idx - 2 + dim]);
            if (i - 2 >= 0)
                minus_pixel(&sum, prefix_sum[idx - 2 * dim + 1]);
            if (i - 2 >= 0 && j - 2 >= 0)
                add_pixel(&sum, prefix_sum[idx - 2 * dim - 2]);
            dst[idx].red = (unsigned short)(sum.red / 9);
            dst[idx].green = (unsigned short)(sum.green / 9);
            dst[idx].blue = (unsigned short)(sum.blue / 9);
        }
    free(prefix_sum);
}

/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions()
{
    add_smooth_function(&smooth1, smooth1_descr);
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}
