#include<stdio.h>


void nhapmatran(double a[][100], int m, int n);
void inmatran(double a[][100], int m, int n);
void nhanmatran(double c[][100],double a[][100], double b[][100], int m1, int n1, int m2, int n2);
void hoanvi(double *a, double *b);
void chuyenvi(double cv[][100], double c[][100], int m1, int n2);
void maxlencheochinh (double a[][100], int m1, int n1, double *sum);

int main(){
    freopen("input.txt","r", stdin);
    int m1, m2, n1, n2;
    double a[100][100 ], b[100][100], c[100][100];
    printf("Nhap so hang va so cot cua ma tran A\n");
    scanf("%d %d",&m1, &n1);
    printf("Nhap so hang va so cot cua ma tran B\n");
    scanf("%d %d", &m2, &n2);
//1.
    nhapmatran(a, m1, n1);
    nhapmatran(b, m2, n2);
//2.
    inmatran(a, m1, n1);
    inmatran(b, m2, n2);
//3.

    nhanmatran(c, a, b, m1, n1, m2, n2);
    printf("Ket qua A*B:\n");
    inmatran(c, m1, n2);
//4.
    double cv[100][100];
    chuyenvi(cv, c, m1, n2);
    printf("Ma tran chuyen vi cua ma tran tich A*B la:\n");
    inmatran(cv, n2, m1);
//5.
    double sum;
    sum=0;
    maxlencheochinh(a, m1, n1, &sum);
    if (m1 == n1){
    printf("Sau khi dua gia tri lon nhat cua tung hang len duong cheo chinh\n");
    inmatran(a, m1, n1);

    printf("Tong la: %g", sum);
    }
//6

}

void nhapmatran(double a[][100], int m , int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            scanf("%lf", &a[i][j]);
        }
    }
}

void inmatran(double a[][100], int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%g ", a[i][j]);
        }
        printf("\n");
    }
}

void nhanmatran(double c[][100],double a[][100], double b[][100], int m1, int n1, int m2, int n2){
    if (n1!=m2){
        printf("Khong the nhan ma tran!");
    }else{
        for(int i=0; i<m1 ;i++){
            for(int j=0; j<n2; j++){
                double tmp;
                tmp=0;
                for(int k=0; k<n1; k++){
                    tmp= tmp+ a[i][k]*b[k][j];
                }
                c[i][j]=tmp;
            }
        }
    }
}

void hoanvi(double *a, double *b){
    double tmp=*a;
    *a=*b;
    *b=tmp;
}

void chuyenvi(double cv[][100], double c[][100], int m1, int n2){
    for(int i=0; i<n2; i++){
        for(int j=0; j<m1; j++){
            cv[i][j]=c[j][i];
        }
    }
}

void maxlencheochinh (double a[][100], int m1, int n1, double *sum){
    if (m1!=n1) printf("Khong the thuc hien vi A khong phai la ma tran vuong!\n");
    for(int i=0; i<m1; i++){
        int maxindx=0;
        for(int j=1; j<n1; j++){
            if (a[i][j] > a[i][maxindx]) maxindx=j;
        }
        *sum+= a[i][maxindx];
        hoanvi(&a[i][maxindx], &a[i][i]);
    }
}

void doicoso(double a){
    
}
