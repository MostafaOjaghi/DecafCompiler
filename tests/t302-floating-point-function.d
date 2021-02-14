void f(double a) {
    double b;
    double c;
    int ia;
    int ib;
    double ex;

    ia = 10;
    ib = 20;
    ex = itod(ia) + itod(ib);
    Print(ex);
    b = 3.1;
    c = a + b;
    Print(a);
    Print(b);
    Print(c);
}

void main() {
    f(2.3);
}