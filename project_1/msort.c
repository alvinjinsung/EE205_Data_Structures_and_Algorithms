#include <stdlib.h> // you can remove this if your code doesn't use it
#include <string.h> // you can remove this if your code doesn't use it

void msort(void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    // default implementation is using qsort()
    // replace the following body with yours!

    // base case
    if (nmemb == 1) {
        return;
    }

    // variable that indicates the number of memebers of left group, right group
    size_t nleft;
    size_t nright;

    // if nmemb is even
    if (nmemb % 2 == 0) {
        nleft = nmemb/2;
        nright = nmemb/2;
    }

    // if nmemb is odd
    if (nmemb % 2 ==1) {
        nleft = (nmemb+1)/2;
        nright = (nmemb-1)/2;
    }

    // void pointer to left and right group
    void* left = malloc(nleft*size);
    void* right = malloc(nright*size);

    memcpy(left, base, nleft*size);
    memcpy(right, base+nleft*size, nright*size);

    // call msort on left and right group
    msort(left, nleft, size, compar);
    msort(right, nright, size, compar);

    // merging left and right group by comparing 1 element each from each group
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while (i<nleft && j<nright) {
        if (compar(left+i*size, right+j*size) == 1) {
            memcpy(base+k*size, right+j*size, size);
            j++;
        }

        else {
            memcpy(base+k*size, left+i*size, size);
            i++;
        }

        k++;
    }

    while (i<nleft) {
        memcpy(base+k*size, left+i*size, size);
        i++;
        k++;
    }

    while (j<nright) {
        memcpy(base+k*size, right+j*size, size);
        j++;
        k++;
    }

    return;
}



