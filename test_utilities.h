#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include <stdbool.h>
#include <stdio.h>

/**
 * These macros are here to help you create tests more easily and keep them
 * clear.
 *
 * The basic idea with unit-testing is create a test function for every real
 * function and inside the test function declare some variables and execute the
 * function under test.
 *
 * Use the ASSERT_TEST and ASSERT_TEST_WITH_FREE to verify correctness of
 * values.
 */

/**
 * Evaluates expr and continues if expr is true.
 * If expr is false, ends the test by returning false, prints a detailed
 * message about the failure, and frees resources by evaluating destroy.
 */

/**
 * Evaluates expr and continues if expr is true.
 * If expr is false, ends the test by returning false and prints a detailed
 * message about the failure.
 */

#define ASSERT_TEST(expr) ASSERT_TEST_WITH_FREE(expr, NULL)

/**
 * Macro used for running a test from the main function
 */
#define ASSERT_TEST_WITH_FREE(expr, destroy)                                      \
    do {                                                                          \
        if (!(expr)) {                                                            \
            printf("\nAssertion failed at %s:%d %s ", __FILE__, __LINE__, #expr); \
            destroy;                                                              \
            return false;                                                         \
        }                                                                         \
    } while (0)

#define RUN_TEST(test, name)                  \
    do {                                 \
      printf("Running %s ... ", name);   \
        if (test()) {                    \
            printf("[OK]\n");            \
        } else {                         \
            printf("[Failed]\n");        \
        }                                \
    } while (0)

int compareFiles(char *c1, char *c2)
{
    FILE* fp1 = fopen(c1, "r");
    FILE* fp2 = fopen(c2, "r");

    // fetching character of two file
    // in two variable ch1 and ch2
    char ch1 = getc(fp1);
    char ch2 = getc(fp2);

    // error keeps track of number of errors
    // pos keeps track of position of errors
    // line keeps track of error line
    int error = 0, pos = 0, line = 1;

    // iterate loop till end of file
    while (ch1 != EOF && ch2 != EOF)
    {
        pos++;

        // if both variable encounters new
        // line then line variable is incremented
        // and pos variable is set to 0
        if (ch1 == '\n' && ch2 == '\n')
        {
            line++;
            pos = 0;
        }

        // if fetched data is not equal then
        // error is incremented
        if (ch1 != ch2)
        {
            error++;
        }

        // fetching character until end of file
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return error==0;
}

#endif /* TEST_UTILITIES_H_ */
