void convertRealToBase(double num, int base, int precision) {
    if (base < 2 || base > 16) {
        printf("Error: base must be between 2 and 16.\n");
        return;
    }

    char digits[] = "0123456789ABCDEF";

    // Xử lý dấu âm
    if (num < 0) {
        putchar('-');
        num = -num;
    }

    // Phần nguyên
    long long intPart = (long long)num;
    double fracPart = num - intPart;

    // Chuyển phần nguyên
    char intBuffer[65];
    int index = 0;
    if (intPart == 0) {
        intBuffer[index++] = '0';
    } else {
        while (intPart > 0) {
            intBuffer[index++] = digits[intPart % base];
            intPart /= base;
        }
    }
    // In phần nguyên (ngược chuỗi)
    for (int i = index - 1; i >= 0; i--) {
        putchar(intBuffer[i]);
    }

    putchar('.'); // dấu chấm thập phân

    // Chuyển phần thập phân
    for (int i = 0; i < precision; i++) {
        fracPart *= base;
        int digit = (int)fracPart;
        putchar(digits[digit]);
        fracPart -= digit;
    }

    putchar('\n');
}
