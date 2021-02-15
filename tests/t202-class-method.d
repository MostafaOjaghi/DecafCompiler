
class Derived extends Base {
    int d1;
    int d2;
}

class Base {
    int b1;
    int b2;
    int f(int x) {
        Print(x);
    }
}

void main() {
    Derived d;
    d = new Derived;
    d.d1 = 1;
    d.f(10);
}
