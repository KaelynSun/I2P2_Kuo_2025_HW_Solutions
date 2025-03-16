#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void swap(int *a, int*b);

int partition(int arr[], int l, int r){
    int x = arr[r], i = l;
    for(int j = l; j <= r-1; j++){
        if(arr[j] <= x){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int kthSmallest(int arr[], int l, int r, int k){
    if(l == r) return arr[l];
    int index = partition(arr, l, r);

    if(index == k) return arr[index];

    if(index > k) return kthSmallest(arr, l, index - 1, k);
    else return kthSmallest(arr, index + 1, r, k);
}

void swap(int *a, int *b){
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    long long int n;
    scanf("%lld", &n);

    int coordX[n+1], coordY[n+1];

    for(int i = 0; i < n; i++){
        scanf("%lld %lld", &coordX[i], &coordY[i]);
    }

    int bestX, bestY;

    bestX = kthSmallest(coordX, 0, n-1, (n/2));
    bestY = kthSmallest(coordY, 0, n-1, (n/2));

    long long int sum = 0;

    for(long long int i = 0; i < n; i++){
        sum += llabs(coordX[i] - bestX) + llabs(coordY[i] - bestY);
    }

    printf("%lld", sum);
    return 0;
}
