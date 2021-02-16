class Factoriel {
    int getValue(int x) {
        if (x == 0) {
            return 1;
        }
        return x * getValue(x - 1);
    }
}

void main() {
    int n;
    Factoriel f;

    f = new Factoriel;
    n = ReadInteger();
    Print(f.getValue(n));
}