class Base {
    int a;

    void setA(int noon) {
        this.a = noon;
    }

    int getA() {
        return this.a;
    }

}

void main() {
    Base b;
    b = new Base;
    b.setA(ReadInteger());
    Print(b.getA());
}