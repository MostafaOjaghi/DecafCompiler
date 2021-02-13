
class Derived extends Base {
    int d1;
    int d2;
}

class Base {
    int b1;
    int b2;
    int f(int x) {

    }
}

class Derived3 extends Derived2 {

}

class Derived2 extends Base {

}

void main() {
    Derived d;
    d = new Derived;
    d.d1 = 1;
    d.f(10);
}