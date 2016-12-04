#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        int n;
        scanf("%d", &n);
        int *c = (int*)malloc(sizeof(int) * n);
        int maxValIndex = 0;
        for(int j = 0; j < n; j++) {
            scanf("%d", &c[j]);

            if (j > 0 && c[j] > c[maxValIndex])
                maxValIndex = j;
        }

        int count = 0;
        int equal = 0;  // complete bool
        int **operations = 0;
        do {
            int *diff = (int*)malloc(sizeof(int) * n);
            int minDiffIndex1 = -1;
            int minDiffIndex2 = -1;
            for(int j = 0; j < n; j++) {
                diff[j] = c[maxValIndex] - c[j];

                if (j != maxValIndex) {
                    if (minDiffIndex1 == -1 || diff[j] < diff[minDiffIndex1]) {
                        minDiffIndex2 = minDiffIndex1;
                        minDiffIndex1 = j;
                    }
                    else if (diff[j] != diff[minDiffIndex1] &&  (minDiffIndex2 == -1 || diff[j] < diff[minDiffIndex2]))
                        minDiffIndex2 = j;
                }
            }

            int minDiff;
            int focusIndex;
            if (minDiffIndex2 == -1) {  // all numbers are the same except for the max number
                minDiff = diff[minDiffIndex1];
                focusIndex = maxValIndex;
            }
            else if (diff[minDiffIndex1] == diff[maxValIndex]) {
                minDiff = 5-diff[minDiffIndex2];
                if (minDiff == 0) {
                    minDiff = 5;
                    focusIndex = maxValIndex;
                }
                else
                    focusIndex = minDiffIndex2;
            }
            else {
                minDiff = diff[minDiffIndex2] - diff[minDiffIndex1];
                focusIndex = minDiffIndex1;
            }

            int op = 0;
            if (minDiff >= 5)
                op = 5;
            else if (minDiff >=2)
                op = 2;
            else
                op = 1;


            operations = (int**) realloc(operations, (count+1) * sizeof(*operations));
            operations[count] = (int*)malloc(2 * sizeof(int));
            operations[count][0] = focusIndex;
            operations[count][1] = op;

            /*
            if (count >= 0) {
                //printf("max[%d], min1[%d], min2[%d], ", maxValIndex, minDiffIndex1, minDiffIndex2);
                //printf("%d, diff[%d] -> ", count, minDiff);

                printf("%d, op[%d], focus[%d] -> ", count, op, focusIndex);
            }
            */
            equal = 1;
            for(int j = 0; j < n; j++) {
                if (j != focusIndex) {
                    c[j] = c[j] + op;
                }
            }

            for(int j = 0; j < n; j++) {
                if (c[j] != c[maxValIndex]) {
                    //printf("\nc[%d]=%d, c[%d]=%d\n", j, c[j], maxValIndex, c[maxValIndex]);
                    equal = 0;
                }
                /*
                   if(focusIndex == j)
                       printf("[%d] ", c[j]);
                   else
                       printf(" %d  ", c[j]);
                */
            }

            free(diff);
            //printf("\n");
            count++;
        } while(!equal);

        free(c);

        int countNew = count;
        for (int j=0; j<n; j++) { // focusIndex
            int op1Count = 0;
            int op2Count = 0;
            int op5Count = 0;

            for (int k=0; k<count; k++) {  // op history
                if (operations[k][0] == j) {
                    switch (operations[k][1]) {
                        case 1:
                            op1Count++;
                            break;
                        case 2:
                            op2Count++;
                            break;
                        case 5:
                            op5Count++;
                            break;
                    }
                }
            }

            int mag = op1Count-(op1Count%5);
            countNew -= mag - (mag/5);
            op1Count -= mag;
            op5Count += mag/5;
            mag = op1Count-(op1Count%2);
            countNew -= mag - (mag/2);
            op1Count -= mag;
            op2Count += mag/2;
            
            mag = op2Count-(op2Count%5);
            countNew -= mag - (mag/5);
            op2Count -= mag;
            op5Count += mag/5;
            

            //printf("[%d], 1=%d, 2=%d, 5=%d\n", j, op1Count, op2Count, op5Count);
        }
        


        printf("%d\n", countNew);
    }

    return 0;
}
