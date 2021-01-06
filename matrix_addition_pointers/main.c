#include <stdio.h>
int nRows, nColumns;
void addMatrices(int m1[nRows][nColumns], int m2[nRows][nColumns], int destinationMatrix[nRows][nColumns],int nRows, int nColumns) {
    for (int i=0; i<nRows*nColumns;i++) {         //This loop has limit of the number of elements in the array as
                                                  //the addresses of these elements are consecutive in the memory even though the matrix is multidimensional
            *(*(destinationMatrix+i)+i) = *(*(m1+i)+i)+ *(*(m2+i)+i);//The content of each element is added and stored in the
                                                                     //corresponding element in the destinationMatrix
    }
}

int main() {
    int nRows = 3;
    int nColumns = 3;
    int destinationMatrix[nRows][nColumns];
    int m1[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
    int m2[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    addMatrices(&m1,&m2,&destinationMatrix,nRows,nColumns);
    for(int i=0; i<nRows;i++) {
        for(int j=0;j<nColumns;j++) {
            printf("%d ",destinationMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
