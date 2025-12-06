#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

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
            break;
        }
        printf("Loi: So B khong hop le! Vui long nhap lai.\n");
    } while (1);


    bigcalc(A, B, op, result);
    printf("\nKet qua: %s %c %s = %s\n", A, op, B, result);

    return 0;
}


int isValid(const char s[]){
    int i = 0, n = strlen(s);
    int dot = -1;
    int hasdigit = 0;

    if (n == 0) return 0;


    if (s[0] == '+' || s[0] == '-') i++;


    for(; i < n && s[i] != 'e' && s[i] != 'E'; i++){
        if (isdigit((unsigned char)s[i])){
            hasdigit = 1;
            continue;
        }
        if (s[i] == '.'){
            if (dot != -1) return 0;
            dot = i;
            continue;
        }
        return 0;
    }


    if (!hasdigit) return 0;


    if (i < n && (s[i] == 'e' || s[i] == 'E')){
        i++;
        if (i >= n) return 0;

        if (s[i] == '+' || s[i] == '-') i++;

        int hasDigitInExp = 0;
        for(; i < n; i++){
            if (!isdigit((unsigned char)s[i])) return 0;
            hasDigitInExp = 1;
        }

        if (!hasDigitInExp) return 0;
    }

    return 1;
}


void skipzerofirst(char s[]){
    int i = 0;
    int n = strlen(s);
    while (i < n-1 && s[i] == '0') i++;

    if (i > 0){
        memmove(s, s + i, n - i + 1);
    }


    if (strlen(s) == 0) strcpy(s, "0");
}


void skipzerolast(char s[]){
    int n = strlen(s);
    while (n > 0 && s[n-1] == '0') n--;
    if (n > 0 && s[n-1] == '.') n--;
    s[n] = '\0';
    if (n == 0) strcpy(s, "0");
}


void expandE(const char input[], char out[]){
    char s[Max];
    strncpy(s, input, Max-1);
    s[Max-1] = '\0';

    int len = strlen(s);
    int sign = 0;
    int startidx = 0;


    if (s[0] == '-') {
        sign = 1;
        startidx = 1;
    } else if(s[0] == '+') {
        startidx = 1;
    }


    int epos = -1;
    for(int i = startidx; i < len; i++){
        if (s[i] == 'e' || s[i] == 'E'){
            epos = i;
            break;
        }
    }


    if (epos == -1){
        out[0] = '\0';
        if (sign) {
            out[0] = '-';
            out[1] = '\0';
        }
        strcat(out, s + startidx);
        return;
    }


    char base[Max], expo[Max];


    int base_len = epos - startidx;
    if (base_len >= Max-1) base_len = Max-2;
    strncpy(base, s + startidx, base_len);
    base[base_len] = '\0';


    strncpy(expo, s + epos + 1, Max-1);
    expo[Max-1] = '\0';

    int exponent = atoi(expo);


    int dot_pos = -1;
    for(int i = 0; i < strlen(base); i++){
        if (base[i] == '.'){
            dot_pos = i;
            break;
        }
    }


    char digits[Max] = {0};
    if (dot_pos != -1){

        strncpy(digits, base, dot_pos);

        strcat(digits, base + dot_pos + 1);
    } else {
        strcpy(digits, base);
    }

    int num_digits = strlen(digits);


    int new_dot_pos = (dot_pos == -1 ? num_digits : dot_pos) + exponent;


    out[0] = '\0';
    int pos = 0;

    if (sign){
        out[pos++] = '-';
        out[pos] = '\0';
    }


    if (new_dot_pos <= 0){

        out[pos++] = '0';
        out[pos++] = '.';
        int zeros = -new_dot_pos;


        for(int i = 0; i < zeros && pos < Max-2; i++){
            out[pos++] = '0';
        }


        strncpy(out + pos, digits, Max - pos - 1);

    } else if (new_dot_pos >= num_digits){

        strncpy(out + pos, digits, Max - pos - 1);
        pos += strlen(digits);

        int add_zeros = new_dot_pos - num_digits;
        for(int i = 0; i < add_zeros && pos < Max-1; i++){
            out[pos++] = '0';
        }
        out[pos] = '\0';

    } else {

        strncpy(out + pos, digits, new_dot_pos);
        pos += new_dot_pos;

        out[pos++] = '.';
        strncpy(out + pos, digits + new_dot_pos, num_digits - new_dot_pos);
    }


    out[Max-1] = '\0';


    if (sign){
        skipzerofirst(out + 1);
    } else {
        skipzerofirst(out);
    }


    skipzerolast(out + (sign ? 1 : 0));


    if (sign && strlen(out) == 1){
        strcpy(out, "0");
    }
}


void tach(const char s[], int *neg, char intp[], char fracp[]){
    *neg = 0;
    const char *ptr = s;

    if (ptr[0] == '-'){
        *neg = 1;
        ptr++;
    } else if(ptr[0] == '+') {
        ptr++;
    }

    int dot = -1, n = strlen(ptr);
    for (int i = 0; i < n; i++) {
        if (ptr[i] == '.') {
            dot = i;
            break;
        }
    }

    if (dot == -1){
        strcpy(intp, ptr);
        fracp[0] = '\0';
    } else {

        int int_len = dot;
        if (int_len >= Max-1) int_len = Max-2;
        strncpy(intp, ptr, int_len);
        intp[int_len] = '\0';


        int frac_len = n - dot - 1;
        if (frac_len >= Max-1) frac_len = Max-2;
        if (frac_len > 0){
            strncpy(fracp, ptr + dot + 1, frac_len);
            fracp[frac_len] = '\0';
        } else {
            fracp[0] = '\0';
        }
    }
}

void addabs(const char ai[], const char af[], const char bi[], const char bf[],
            char ri[], char rf[]){


    int la = strlen(af), lb = strlen(bf);
    int L = (la > lb ? la : lb);

    char A[Max], B[Max], RES[Max];


    for(int i = 0; i < L; i++){
        A[i] = (i < la ? af[i] : '0');
        B[i] = (i < lb ? bf[i] : '0');
    }
    A[L] = B[L] = '\0';


    int carry = 0;
    RES[L] = '\0';

    for(int i = L-1; i >= 0; i--){
        int t = (A[i] - '0') + (B[i] - '0') + carry;
        RES[i] = (t % 10) + '0';
        carry = t / 10;
    }

    strcpy(rf, RES);
    skipzerolast(rf);


    int ai_len = strlen(ai);
    int bi_len = strlen(bi);


    int max_len = (ai_len > bi_len ? ai_len : bi_len) + 1;
    char temp_ri[Max] = {0};

    int i = ai_len - 1;
    int j = bi_len - 1;
    int k = max_len - 1;
    int idx = 0;


    while (i >= 0 || j >= 0 || carry > 0){
        int digit_a = (i >= 0) ? ai[i] - '0' : 0;
        int digit_b = (j >= 0) ? bi[j] - '0' : 0;

        int sum = digit_a + digit_b + carry;
        temp_ri[idx++] = (sum % 10) + '0';
        carry = sum / 10;

        if (i >= 0) i--;
        if (j >= 0) j--;
        k--;
    }


    temp_ri[idx] = '\0';


    for(int x = 0; x < idx/2; x++){
        char temp = temp_ri[x];
        temp_ri[x] = temp_ri[idx - 1 - x];
        temp_ri[idx - 1 - x] = temp;
    }

    strcpy(ri, temp_ri);
    skipzerofirst(ri);
}

void subabs(const char ai[], const char af[], const char bi[], const char bf[],
            char ri[], char rf[]){

    int la = strlen(af), lb = strlen(bf);
    int L = (la > lb ? la : lb);

    char A[Max], B[Max], R_frac[Max];

    for(int i = 0; i < L; i++){
        A[i] = (i < la ? af[i] : '0');
        B[i] = (i < lb ? bf[i] : '0');
    }
    A[L] = B[L] = '\0';


    int borrow = 0;
    R_frac[L] = '\0';

    for(int i = L-1; i >= 0; i--){
        int da = A[i] - '0' - borrow;
        int db = B[i] - '0';

        if (da < db){
            da += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        R_frac[i] = (da - db) + '0';
    }

    strcpy(rf, R_frac);
    skipzerolast(rf);


    int ai_len = strlen(ai);
    int bi_len = strlen(bi);


    char temp_ai[Max];
    if (ai_len < bi_len + 1){

        int zeros_needed = bi_len + 1 - ai_len;
        strcpy(temp_ai, ai);
        memmove(temp_ai + zeros_needed, temp_ai, ai_len + 1);
        for(int z = 0; z < zeros_needed; z++){
            temp_ai[z] = '0';
        }
        ai_len = strlen(temp_ai);
    } else {
        strcpy(temp_ai, ai);
    }

    char temp_bi[Max];
    if (bi_len < ai_len){

        int zeros_needed = ai_len - bi_len;
        strcpy(temp_bi, bi);
        memmove(temp_bi + zeros_needed, temp_bi, bi_len + 1);
        for(int z = 0; z < zeros_needed; z++){
            temp_bi[z] = '0';
        }
        bi_len = strlen(temp_bi);
    } else {
        strcpy(temp_bi, bi);
    }


    char R_int[Max] = {0};
    int new_borrow = borrow;

    for(int i = ai_len - 1; i >= 0; i--){
        int da = temp_ai[i] - '0' - new_borrow;
        int db = temp_bi[i] - '0';

        if (da < db){
            da += 10;
            new_borrow = 1;
        } else {
            new_borrow = 0;
        }

        R_int[i] = (da - db) + '0';
    }

    R_int[ai_len] = '\0';
    strcpy(ri, R_int);
    skipzerofirst(ri);
}


int compareabs(const char ai[], const char af[], const char bi[], const char bf[]){
    char ai_cp[Max], bi_cp[Max];
    strcpy(ai_cp, ai);
    strcpy(bi_cp, bi);

    skipzerofirst(ai_cp);
    skipzerofirst(bi_cp);

    int la = strlen(ai_cp);
    int lb = strlen(bi_cp);

    if (la != lb) return (la > lb ? 1 : -1);

    int cmp = strcmp(ai_cp, bi_cp);
    if (cmp != 0) return (cmp > 0 ? 1 : -1);


    int lfa = strlen(af);
    int lfb = strlen(bf);
    int m = (lfa > lfb ? lfa : lfb);

    for(int i = 0; i < m; i++){
        char ca = (i < lfa ? af[i] : '0');
        char cb = (i < lfb ? bf[i] : '0');
        if (ca != cb) return (ca > cb ? 1 : -1);
    }

    return 0;
}


void bigcalc(const char a[], const char b[], char op, char res[]){
    char fixedA[Max], fixedB[Max];
    char ai[Max], af[Max], bi[Max], bf[Max];
    int negA, negB, negR = 0;
    char ri[Max], rf[Max];


    strcpy(res, "0");


    expandE(a, fixedA);
    expandE(b, fixedB);


    tach(fixedA, &negA, ai, af);
    tach(fixedB, &negB, bi, bf);


    skipzerofirst(ai); skipzerolast(af);
    skipzerofirst(bi); skipzerolast(bf);


    int cmp = compareabs(ai, af, bi, bf);


    int do_add = 0;

    if (op == '+'){
        do_add = (negA == negB) ? 0 : 1;
    } else {
        do_add = (negA != negB) ? 0 : 1;
    }


    if (do_add == 0){

        addabs(ai, af, bi, bf, ri, rf);
        negR = negA;
    } else {

        if (cmp == 0){
            strcpy(res, "0");
            return;
        }

        if (cmp > 0){

            subabs(ai, af, bi, bf, ri, rf);

            if (op == '+'){

                negR = negA;
            } else {

                negR = negA;
            }
        } else {

            subabs(bi, bf, ai, af, ri, rf);

            if (op == '+'){

                negR = !negA;
            } else {

                negR = !negA;  // Đảo dấu
            }
        }
    }


    int pos = 0;

    if (negR){
        res[pos++] = '-';
    }

    if (strlen(ri) == 0){
        res[pos++] = '0';
    } else {
        strcpy(res + pos, ri);
        pos += strlen(ri);
    }

    if (strlen(rf) > 0){
        res[pos++] = '.';
        strcpy(res + pos, rf);
    }

    res[strlen(res)] = '\0';

    if (strcmp(res, "-0") == 0 || strcmp(res, "-0.0") == 0){
        strcpy(res, "0");
    }
}
