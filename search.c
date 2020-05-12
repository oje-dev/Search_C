/*
 * search.c - the implementation of search functions.
 *
 * This is the file you edit.
 */
#include <errno.h>
#include "search.h"
#include <stddef.h>

/*
 * See search.h for the specification of this iterative linear search
 * function.
 *
 * You have to implement this function.
 */
int linearsearch(int x, int arr[], int n) {
    if (n <= 0 || arr == NULL){
        errno = EINVAL;
        return -1;

    } else{
        for (int i = 0; i < n; ++i){
            if (arr[i] == x){
                return i;
            }
        }
        return -1;
    }
 }

/*
 * See search.h for the specification of this recursive linear search
 * function.
 *
 * You have to implement this function.
 */
int rlinearsearch(int x, int arr[], int n, int i) {
    if (n <= 0 || arr == NULL){
        errno = EINVAL;
        return -1;

    } else if (i == n && arr[i] != x){
        return -1;

    } else if (arr[i] == x){
        return i;

    } else{
        return rlinearsearch(x, arr, n, i + 1);
    }
 }

/*
 * See search.h for the specification of this sentinel linear search
 * function.
 *
 * You have to implement this function.
 */
int slinearsearch(int x, int arr[], int n) {
    return -1;
}

/*
 * See search.h for the specification of this iterative binary search
 * function.
 *
 * You have to implement this function.
 */
int binarysearch(int x, int arr[], int n) {
    return -1;
}

/*
 * See search.h for the specification of this recursive binary search
 * function.
 *
 * You have to implement this function.
 */
int rbinarysearch(int x, int arr[], int li, int hi) {
    return -1;
}
