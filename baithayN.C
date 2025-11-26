#include<stdio.h>
#include<math.h>
#include<string.h>

double EPS =1e-9;
void nhapmatran(double a[][100], int m, int n);
void inmatran(double a[][100], int m, int n);
void nhanmatran(double c[][100],double a[][100], double b[][100], int m1, int n1, int m2, int n2);
void hoanvi(double *a, double *b);
void chuyenvi(double cv[][100], double c[][100], int m1, int n2);
void maxlencheochinh (double a[][100], int m1, int n1, double *sum);
void doicoso(double a);
void minlencheophu(double b[][100], int m2, int n2);
int tinhHang(double a[][100], int m, int n);

int main(){
    freopen("tsc.txt","r", stdin);
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
    int base;
    printf("Tong la: %g\n", sum);

    doicoso(sum);
    }
//6
     double subB[100][100];
        for(int i=0; i<m2; i++){
            for(int j=0; j<n2; j++){
            subB[i][j]=b[i][j];
            }
        }
    if (m2!=n2) printf("Khong the thuc hien vi B khong phai la ma tran vuong!\n");
    else{

        minlencheophu(b,m2,n2);

        printf("Ket qua ma tran B sau khi dua gia tri nho nhat cua tung hang len duong cheo phu la: \n");

        inmatran(b,m2,n2);
    }
//7

    printf("Hang cua ma tran B la: %d",tinhHang(subB,m2,n2) );
    return 0;
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
    int base;
    int pre;
    printf("Nhap co so:\n");
    scanf("%d",&base);

    if (base<2 || base>16) {
            printf("Khong the doi sang co so ban vua chon\n");
            return;
    }

    printf("Nhap so chu so thap phan sau dau '.' ban muon giu lai\n");
    scanf("%d",&pre);


    char s[]="0123456789ABCDF";
    int isnegative=0;
    if (a<0) {
        isnegative=1;
        a=-a;
    }
    long long phannguyen=(long long)a;
    double phanthphan=  a-phannguyen ;


    // doiphannguyen
    int len=0;
    char nguyen[100];
    if (phannguyen==0){
        nguyen[len++]='0';
    }
    else{
        while (phannguyen>0){
            int du=phannguyen%base;
            nguyen[len++]=s[du];
            phannguyen/=base;
        }
    }
    printf("Tong o co so %d la: \n",base);
    if(isnegative) printf("-");
    for(int i=len-1; i>=0; i--){
        printf("%c",nguyen[i]);
    }
    if (pre>0){
    printf(".");
    // doiphanthapphan

    int tmp=0;


    for(int i=0;i<pre; i++){
        phanthphan*=base;
        tmp= (int)phanthphan ;
        printf("%c", s[tmp]);
        phanthphan-=tmp;

    }
    }
    printf("\n");

}

void minlencheophu (double b[][100], int m2, int n2){

    for(int i=0; i<n2; i++){
        int minindx=0;
        for(int j=1; j<m2; j++){
            if (b[j][i] < b[minindx][i]) minindx=j;
        }

        hoanvi(&b[minindx][i], &b[m2-1-i][i]);
    }

}

int tinhHang(double a[][100], int m, int n) {
    int row, col;
    row=0;
    col=0;
   while (row<m && col<n) {

        // Tim max cua chot
        int chot = row;
        for (int i = row + 1; i < m; i++)
            if (fabs(a[i][col]) > fabs(a[chot][col]))
                chot = i;

        // chot xap xi 0 → loai bo
        if (fabs(a[chot][col]) < EPS){
             col++;
             continue;
        }


        // hoan doi hang chot voi hang row
        if (chot != row) {
            for (int j = 0; j < n; j++) {
                double tmp = a[row][j];
                a[row][j] = a[chot][j];
                a[chot][j] = tmp;
            }
        }

        // chuan hoa row
        double div = a[row][col];
        for (int j = 0; j < n; j++)
            a[row][j] /= div;

        //khu cac hang con lai
        for (int i = 0; i < m; i++) {
            if (i != row && fabs(a[i][col]) > EPS) {
                double factor = a[i][col];
                for (int j = 0; j < n; j++)
                    a[i][j] -= factor * a[row][j];
            }
        }

        row++;
        col++;
    }

    // dem so hang khac 0
    int rank = 0;
    for (int i = 0; i < m; i++) {
        int nonzero = 0;
        for (int j = 0; j < n; j++)
            if (fabs(a[i][j]) > EPS)
                nonzero = 1;

        if (nonzero) rank++;
    }

    return rank;
}



