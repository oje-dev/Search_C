/* 
 * test_search.c - unit tests of search functions.
 * 
 * 
 * DO NOT EDIT THIS FILE.
 */ 
#include <errno.h>
#include <stdio.h>
#include "search.h"
#include "test_search.h"

int run_munit_tests(int argc, char** argv) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

void assert_search(int (*search_f)(int, int[], int), char* aname, int arr[],
    int n, int res_arr[], int rn) {
    printf("\n    searching %s for: ", aname);
    for (int i = 0; i < rn; i++) {
        assert_int(search_f(i, arr, n), ==, res_arr[i]);
        printf("%d%c ", i, res_arr[i] == -1 ? 'x' : '\0');
    }
}

void assert_rlsearch(char* aname, int arr[], int n, int res_arr[], int rn) {
    printf("\n    searching %s for: ", aname);
    for (int i = 0; i < rn; i++) {
        assert_int(rlinearsearch(i, arr, n, 0), ==, res_arr[i]);
        printf("%d%c ", i, res_arr[i] == -1 ? 'x' : '\0');
    }
}

void assert_rbsearch(char* aname, int arr[], int n, int res_arr[], int rn) {
    printf("\n    searching %s for: ", aname);
    for (int i = 0; i < rn; i++) {
        assert_int(rbinarysearch(i, arr, 0, n - 1), ==, res_arr[i]);
        printf("%d%c ", i, res_arr[i] == -1 ? 'x' : '\0');
    }
}

void assert_error_cases(int (*search_f)(int, int[], int)) {
    errno = 0;
    assert_int(search_f(1, NULL, 0), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
    int ax[] = { 1, 2 };
    assert_int(search_f(1, ax, -1), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
}

MunitResult test_generic_linear(int (*search_f)(int, int[], int)) {
    assert_error_cases(search_f);
    
    int a0[0];
    int r0[] = { -1, -1 };
    assert_search(search_f, "a0", a0, 0, r0, 2);
    
    int a1[] = { 1 };
    int r1[] = { -1, 0, -1};
    assert_search(search_f, "a1", a1, 1, r1, 3);
    
    int a2[] = { 6, 5 };
    int r2[] = { -1, -1, -1, -1, -1, 1, 0, -1 };
    assert_search(search_f, "a2", a2, 2, r2, 8);

    int a9[] = { 0, 3, 2, 5, 7, 9, 10, 11, 1 };
    int r9[] = { 0, 8, 2, 1, -1, 3, -1, 4, -1, 5, 6, 7, -1 };
    assert_search(search_f, "a9", a9, 9, r9, 13);

    int a10[] = { 3, 0, 2, 5, 7, 9, 10, 11, 1, 6 };
    int r10[] = { 1, 8, 2, 0, -1, 3, 9, 4, -1, 5, 6, 7, -1 };
    assert_search(search_f, "a10", a10, 10, r10, 13); 
    
    int adup[] = { 3, 0, 2, 5, 0, 7, 9, 10, 11, 1, 6 };
    int rdup[] = { 1, 9, 2, 0, -1, 3, 10, 5, -1, 6, 7, 8, -1 };
    assert_search(search_f, "adup", adup, 11, rdup, 13); 

    int aduplast[] = { 3, 0, 2, 5, 0, 7, 9, 10, 11, 1, 5 };
    int rduplast[] = { 1, 9, 2, 0, -1, 3, -1, 5, -1, 6, 7, 8, -1 };
    assert_search(search_f, "aduplast", aduplast, 11, rduplast, 13); 

    printf("\n");
    
    return MUNIT_OK;
}

MunitResult test_linearsearch(const MunitParameter params[], 
    void* fixture) {
    printf("\n    testing linearsearch ...");
    return test_generic_linear(linearsearch);
}

MunitResult test_rlinearsearch(const MunitParameter params[], 
    void* fixture) {
    printf("\n    testing rlinearsearch ...");
    errno = 0;
    assert_int(rlinearsearch(1, NULL, 0, 0), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
    int ax[] = { 1, 2 };
    assert_int(rlinearsearch(1, ax, -1, 0), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
        
    int a0[0];
    int r0[] = { -1, -1 };
    assert_rlsearch("a0", a0, 0, r0, 2);
    
    int a1[] = { 1 };
    int r1[] = { -1, 0, -1};
    assert_rlsearch("a1", a1, 1, r1, 3);
    
    int a2[] = { 6, 5 };
    int r2[] = { -1, -1, -1, -1, -1, 1, 0, -1 };
    assert_rlsearch("a2", a2, 2, r2, 8);

    int a9[] = { 0, 3, 2, 5, 7, 9, 10, 11, 1};
    int r9[] = { 0, 8, 2, 1, -1, 3, -1, 4, -1, 5, 6, 7, -1 };
    assert_rlsearch("a9", a9, 9, r9, 13);

    int a10[] = { 3, 0, 2, 5, 7, 9, 10, 11, 1, 6 };
    int r10[] = { 1, 8, 2, 0, -1, 3, 9, 4, -1, 5, 6, 7, -1 };
    assert_rlsearch("a10", a10, 10, r10, 13);    
    
    int adup[] = { 3, 0, 2, 5, 0, 7, 9, 10, 11, 1, 6 };
    int rdup[] = { 1, 9, 2, 0, -1, 3, 10, 5, -1, 6, 7, 8, -1 };
    assert_rlsearch("adup", adup, 11, rdup, 13); 

    int aduplast[] = { 3, 0, 2, 5, 0, 7, 9, 10, 11, 1, 5 };
    int rduplast[] = { 1, 9, 2, 0, -1, 3, -1, 5, -1, 6, 7, 8, -1 };
    assert_rlsearch("aduplast", aduplast, 11, rduplast, 13); 
    
    printf("\n");
    
    return MUNIT_OK;
}

MunitResult test_slinearsearch(const MunitParameter params[], 
    void* fixture) {
    printf("\n    testing slinearsearch ...");
    return test_generic_linear(slinearsearch);
}

MunitResult test_binarysearch(const MunitParameter params[], 
    void* fixture) {
    printf("\n    testing binarysearch ...");
    assert_error_cases(binarysearch);
        
    int a0[0];
    int r0[] = { -1, -1 };
    assert_search(binarysearch, "a0", a0, 0, r0, 2);
    
    int a1[] = { 1 };
    int r1[] = { -1, 0, -1};
    assert_search(binarysearch, "a1", a1, 1, r1, 3);
    
    int a2[] = { 5, 6 };
    int r2[] = { -1, -1, -1, -1, -1, 0, 1, -1 };
    assert_search(binarysearch, "a2", a2, 2, r2, 8);

    int a9[] = { 1, 2, 3, 5, 7, 9, 10, 11, 13 };
    int r9[] = { -1, 0, 1, 2, -1, 3, -1, 4, -1, 5, 6, 7, -1, 8, -1};
    assert_search(binarysearch, "a9", a9, 9, r9, 15);

    int a10[] = { 0, 3, 4, 6, 8, 10, 11, 13, 14, 15 };
    int r10[] = { 0, -1, -1, 1, 2, -1, 3, -1, 4, -1, 5, 6, -1, 7, 8, 9, -1 };
    assert_search(binarysearch, "a10", a10, 10, r10, 17);    
    
    int adup[] = { 0, 3, 4, 4, 6, 8, 10, 11, 13, 14, 15 };
    int rdup[] = { 0, -1, -1, 1, 2, -1, 4, -1, 5, -1, 6, 7, -1, 8, 9, 10, 
                        -1 };
    assert_search(binarysearch, "adup11", adup, 11, rdup, 17);    
                        
    int aduplast[] = { 0, 3, 4, 5, 6, 8, 10, 11, 13, 14, 15, 15 };
    int rduplast[] = { 0, -1, -1, 1, 2, 3, 4, -1, 5, -1, 6, 7, -1, 8, 9, 10, 
                        -1 };
    assert_search(binarysearch, "aduplast", aduplast, 12, rduplast, 17);    

    printf("\n");
    
    return MUNIT_OK;
}

MunitResult test_rbinarysearch(const MunitParameter params[], 
    void* fixture) {
    printf("\n  testing rbinarysearch ...");
    errno = 0;
    assert_int(rbinarysearch(1, NULL, 0, 1), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
    int ax[] = { 1, 2 };
    assert_int(rbinarysearch(1, ax, -1, 0), ==, -1);
    assert_int(errno, ==, EINVAL);
    errno = 0;
        
    int a0[0];
    int r0[] = { -1, -1 };
    assert_rbsearch("a0", a0, 0, r0, 2);
    
    int a1[] = { 1 };
    int r1[] = { -1, 0, -1};
    assert_rbsearch("a1", a1, 1, r1, 3);
    
    int a2[] = { 5, 6 };
    int r2[] = { -1, -1, -1, -1, -1, 0, 1, -1 };
    assert_rbsearch("a2", a2, 2, r2, 8);

    int a9[] = { 1, 2, 3, 5, 7, 9, 10, 11, 13 };
    int r9[] = { -1, 0, 1, 2, -1, 3, -1, 4, -1, 5, 6, 7, -1, 8, -1};
    assert_rbsearch("a9", a9, 9, r9, 15);

    int a10[] = { 0, 3, 4, 6, 8, 10, 11, 13, 14, 15 };
    int r10[] = { 0, -1, -1, 1, 2, -1, 3, -1, 4, -1, 5, 6, -1, 7, 8, 9, -1 };
    assert_rbsearch("a10", a10, 10, r10, 17);    
    
    int adup[] = { 0, 3, 4, 4, 6, 8, 10, 11, 13, 14, 15 };
    int rdup[] = { 0, -1, -1, 1, 2, -1, 4, -1, 5, -1, 6, 7, -1, 8, 9, 10, 
                        -1 };
    assert_rbsearch("adup11", adup, 11, rdup, 17);    
                        
    int aduplast[] = { 0, 3, 4, 5, 6, 8, 10, 11, 13, 14, 15, 15 };
    int rduplast[] = { 0, -1, -1, 1, 2, 3, 4, -1, 5, -1, 6, 7, -1, 8, 9, 10, 
                        -1 };
    assert_rbsearch("aduplast", aduplast, 12, rduplast, 17);    

    printf("\n");
    
    return MUNIT_OK;
    
}
