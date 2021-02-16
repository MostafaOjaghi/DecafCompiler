
void main() {
    int[] a;
    int[] b;
    int[] c;
    int i;

    a = NewArray(5, int);
    for (i = 0; i < 5; i = i + 1) {
        a[i] = i + 50;
    }
    b = NewArray(6, int);
    for (i = 0; i < 6; i = i + 1) {
        b[i] = i + 40;
    }
    for (i = 0; i < 5; i = i + 1) {
        Print(a[i]);
    }
    for (i = 0; i < 6; i = i + 1) {
        Print(b[i]);
    }
    c = a + b;
    for (i = 0; i < 11; i = i + 1) {
        Print(c[i]);
    }
}