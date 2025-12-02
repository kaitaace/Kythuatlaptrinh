#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

#define Max 10005

int isValid(const char s[]);
void expandE(const char input[], char out[]);
void tach(const char s[], int *neg, char intp[], char fracp[]);
void skipzerofirst(char s[]);
void skipzerolast(char s[]);
void bigcalc(const char a[], const char b[], char op, char res[]);
int compareabs(const char ai[], const char af[], const char bi[], const char bf[]);
void addabs(const char ai[], const char af[], const char bi[], const char bf[], char ri[], char rf[]);
void subabs(const char ai[], const char af[], const char bi[], const char bf[], char ri[], char rf[]);

int main(){
    char A[Max], B[Max], op;
    char result[Max];

    printf("--- TINH TOAN SO LON ---\n");

    do {
        printf("Nhap so A: ");
        if (scanf("%s", A) != 1) {
            // Xóa lỗi scanf (nếu người dùng nhập ký tự)
            while(getchar() != '\n');
            continue;
        }
        if (isValid(A)) {
            break;
        }
        printf("Loi: So A khong hop le! Vui long nhap lai.\n");
    } while (1);

   do {
        printf("Nhap phep toan (+ hoac -): ");
        // ' %c' dung de bo qua ky tu khoang trang hoac xuong dong
        if (scanf(" %c", &op) != 1) {
            while(getchar() != '\n');
            continue;
        }
        if (op == '+' || op == '-') {
            break;
        }
        printf("Loi: Phep toan khong hop le! Vui long nhap lai.\n");
    } while (1);

    do {
        printf("Nhap so B: ");
        if (scanf("%s", B) != 1) {
            while(getchar() != '\n');
            continue;
        }
        if (isValid(B)) {
            break; // Hợp lệ, thoát vòng lặp
        }
        printf("Loi: So B khong hop le! Vui long nhap lai.\n");
    } while (1);

    bigcalc(A, B, op, result);

    printf("\nKet qua: %s %c %s = %s\n", A, op, B, result);

    return 0;
}

int isValid(const char s[]){
    int i=0, n=strlen(s);
    int dot=0, expcount=0;
    int hasdigitbeforeexp=0;

    if (s[0]=='+' || s[0]=='-') i++;

    for(; i<n && s[i]!='e' && s[i] !='E'; i++){
        if (isdigit(s[i])){
            hasdigitbeforeexp=1;
            continue;
        }
        if (s[i]=='.'){
            if (dot) return 0;
            dot=1;
            continue;
        }
        return 0;
    }
    if (!hasdigitbeforeexp && (dot==-1 || (dot != -1 && s[dot+1]=='\0'))) return 0;

   if (i<n && (s[i]=='e' || s[i]=='E')) {
        i++;
        if(i >= n) return 0;
        if(s[i] == '+' || s[i] == '-') i++;

        int hasDigitInExp = 0;
        for(; i < n; i++) {
            if (!isdigit(s[i])) return 0;
            hasDigitInExp = 1;
        }

        if (!hasDigitInExp) return 0;
    }


    return 1;
}
void skipzerofirst(char s[]){
    int i=0;
    int n=strlen(s);

    while (s[i]=='0' && s[i+1] != '\0' && s[i+1]!='.') i++;
    if (i>0) memmove(s,s+i,n-i+1);
    if (strlen(s)==0) strcpy(s,"0");
}

void skipzerolast(char s[]){
    int n=strlen(s);
    while (n>0 && s[n-1] =='0') n--;
    s[n]='\0';
}

void expandE(const char input[], char out[]){
    char s[Max];
    strcpy(s,input);
    int len=strlen(s);
    int sign=0;

    // xu ly dau
    int startidx=0;
    if (s[0]=='-') {
        sign=1;
        startidx=1;
    }else if(s[0]='+'){
        startidx=1;
    }
    // tim vi tri cua e/E;
    int epos=-1;
    for(int i=startidx; i<len; i++){
        if (s[i]=='e' || s[i]=='E'){
            epos=i;
            break;
        }
    }

    if (epos == -1){ // khong co e/E
        if (sign) out[0]='-';
        else out[0]='\0';
        strcpy(out+(sign ? 1: 0), s + startidx);
        return;
    }
    //tach base va exponent
    char base[Max], expo[Max];
    strncpy(base, s+startidx, epos -startidx);
    base[epos -startidx]='\0';
    strcpy(expo, s+epos+1);

    int exponent=atoi(expo); // chuen chuoi expo thang kieu int
    int dot_pos=-1;
    for(int i=0; i<strlen(base); i++){
        if (base[i]=='.'){
            dot_pos=i;
            break;
        }
    }
    int curpos=(dot_pos==-1)?strlen(base): dot_pos;
    // bo dau cham ra khoi base de xu li chuoi so lien mach
    if (dot_pos!=-1) memmove(base +dot_pos, base +dot_pos +1, strlen(base)-dot_pos);
    int pos=0;
    if (sign) out[pos++]='-';
    int newdot=curpos + exponent;

    if (newdot <=0){
        // so mu am lon ( 1.2e-4 -> 0.00012)
        out[pos++] ='0';
        out[pos++] = '.';
        for(int i=0; i<fabs(newdot); i++){
            out[pos++]='0';
        }
        strcpy(out +pos, base);
    }else if (newdot >= strlen(base)){
        strcpy (out+pos, base);
        pos+=strlen(base);
        for(int i=0; i<newdot -strlen(base); i++){
            out[pos++]='0';
        }
        out[pos]='\0';
    }else {
        // dau cham nam giua sau khi da mo rong e
        strncpy(out+pos, base, newdot);
        pos+= newdot;
        out[pos++]='.';
        strcpy(out+pos, base+newdot);
    }
    // xu li th base rong
    if (strlen(out)== (sign ?1:0)) strcpy(out +(sign? 1:0),"0");
    skipzerofirst(out+(sign?1:0));
}
void tach(const char s[], int *neg, char intp[], char fracp[]){
    *neg=0;
    const char *ptr=s;
    if (ptr[0]=='-'){
        *neg=1;
        ptr++;

    }else if(ptr[0]=='+') {
        ptr++;
    }
    int dot = -1, n = strlen(ptr);
    for (int i = 0; i < n; i++) {
        if (ptr[i] == '.') { dot = i; break; }
    }
    if (dot==-1){
        strcpy(intp, ptr);
        fracp[0]='\0';
    }else{
        strncpy(intp, ptr, dot);
        intp[dot]='\0';
        strcpy(fracp,ptr +dot+1);
    }
}
void addabs(const char ai[], const char af[], const char bi[], const char bf[], char ri[], char rf[]){
    int la=strlen(af), lb=strlen(bf), L=(la>lb?la:lb);
    char A[Max], B[Max], RES[Max];

    for(int i=0; i<L; i++){
        A[i]=(i<la? af[i]:'0');
        B[i]=(i<lb ? bf[i]:'0');
    }
    A[L]=B[L]='\0';

    int carry=0;
    RES[L]='\0';

    for(int i=L-1; i>=0; i--){
        int t=(A[i]-'0') + (B[i]-'0') + carry;
        RES[i] = (t % 10) + '0';
        carry = t / 10;
    }
    strcpy(rf, RES);
    skipzerolast(rf);

    //phan nguyen
    int ai_len = strlen(ai), bi_len = strlen(bi);
    int p = (ai_len > bi_len ? ai_len : bi_len);
    char RA[Max];
    RA[p] = '\0';

    int i = ai_len-1, j = bi_len-1, k = p-1;
    while (k >= 0) {
        int da = (i >= 0 ? ai[i]-'0' : 0);
        int db = (j >= 0 ? bi[j]-'0' : 0);
        int t = da + db + carry;
        RA[k] = (t % 10) + '0';
        carry = t / 10;
        i--; j--; k--;
    }

    if (carry) {
        for (int x = p; x > 0; x--) RA[x] = RA[x-1];
        RA[0] = carry + '0';
        RA[p+1] = '\0';
        strcpy(ri, RA);
    } else {
        strcpy(ri, RA);
    }
    skipzerofirst(ri);
}
//tru abs
void subabs(const char ai[], const char af[], const char bi[], const char bf[], char ri[], char rf[]) {
    int la = strlen(af), lb = strlen(bf), L = (la > lb ? la : lb);
    char A[Max], B[Max];
    int borrow = 0;
    // phan thap phan
    char R_frac[Max];
    R_frac[L] = '\0';

    for (int i = 0; i < L; i++) {
        A[i]=(i < la? af[i]:'0');
        B[i]=(i < lb ? bf[i]:'0');
    }
    for (int i = L - 1; i >= 0; i--) {
        int da=A[i] - '0';
        int db=B[i] - '0';

        int diff = da - db - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1; // Muon 1 tu phan nguyen tiep theo
        } else {
            borrow = 0;
        }
        R_frac[i] = diff + '0';
    }
    strcpy(rf,R_frac);
    skipzerolast(rf);
    // phan nguyen
    int ai_len=strlen(ai), bi_len=strlen(bi);
    int p= (ai_len > bi_len ? ai_len : bi_len);
    char R_int[Max];
    R_int[p]='\0';

    int i_idx=ai_len - 1, j_idx = bi_len - 1;

    // Tru phan nguyen tu phai sang trai, su dung borrow tu phan thap phan
    for (int k=p - 1; k >= 0; k--) {
        int da=(i_idx >= 0 ? ai[i_idx] - '0' : 0);
        int db=(j_idx >= 0 ? bi[j_idx] - '0' : 0);

        int diff = da - db - borrow; // Su dung borrow tu buoc tru truoc

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        R_int[k] = diff + '0';
        i_idx--; j_idx--;
    }

    strcpy(ri, R_int);
    skipzerofirst(ri);
}
int compareabs(const char ai[], const char af[], const char bi[], const char bf[]){
    char ai_cp[Max], bi_cp[Max];
    strcpy(ai_cp, ai);
    strcpy(bi_cp, bi);

    int la=strlen(ai_cp), lb=strlen(bi_cp);
    if (la!=lb) return (la>lb ?1:-1);

    int cmp=strcmp(ai_cp, bi_cp);
    if (cmp!=0) return (cmp>0?1:-1);

    int lfa=strlen(af), lfb=strlen(bf);
    int m=(lfa>lfb ?lfa : lfb);
    for(int i=0; i<m; i++){
        char ca= (i<lfa? af[i]:'0');
        char cb= (i<lfb ? bf[i] :'0');
        if (ca != cb) return (ca >cb ? 1: -1);
    }
    return 0;
}
void bigcalc(const char a[], const char b[], char op, char res[]){
    char fixedA[Max], fixedB[Max];
    char ai[Max], af[Max], bi[Max], bf[Max];
    int negA, negB, negR = 0;
    char ri[Max], rf[Max];

    expandE(a, fixedA);
    expandE(b, fixedB);

    tach(fixedA, &negA, ai, af);
    tach(fixedB, &negB, bi, bf);

    skipzerofirst(ai);skipzerolast(af);
    skipzerofirst(bi); skipzerolast(bf);

    int pheptoan;// xac dinh phep toan + hay - abs
    if (op=='+') pheptoan=(negA==negB) ?0:1;
    else pheptoan=(negA != negB) ?0:1;

    int cmp = compareabs(ai, af, bi, bf);

    if (pheptoan ==0){
        addabs(ai,af,bi,bf, ri, rf);
        negR=negA;
    }else// phep tru |a|-|b| hoac nguoc lai
        if (cmp==0){
            strcpy(res, "0"); return;
        }
        if (cmp>0){//|a|>|b|;
            subabs(ai,af, bi,bf, ri,rf);
            negR=negA;

        } else{
            subabs(bi,bf,ai,af,ri,rf);
            // Xác định dấu: Dấu ngược lại (ví dụ: A + (-B) = -(B - A) nếu |B|>|A|)
            // Dấu của kết quả sẽ là dấu của số bị trừ trong phép toán tương đương
            if (op=='+'){// A + (-B) = B - A
                negR=negB;
            }else{// A - B = A - (B)
                negR = !negA;
            }
        }
        // tao ket qua
        int pos=0;
        if (negR) res[pos++]='-';
        //phan nguyen
        if (strlen(ri) == 0) strcpy(ri, "0");
        strcpy(res + pos, ri);
        pos += strlen(ri);

        //phan thap phan
        if (strlen(rf) > 0) {
        res[pos++] = '.';
        strcpy(res + pos, rf);
        }
        res[strlen(res)] = '\0';
}
