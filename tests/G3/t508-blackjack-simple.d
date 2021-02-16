class A {
    int num;

    int getNum() {
        return num;
    }

    int setAndGet(int a) {
        num = a;
        return getNum();
    }
}

void main() {
    A ca;
    int inp;

    ca = new A;
    inp = ReadInteger();
    Print(ca.setAndGet(inp));
    Print(ca.getNum(inp));
}