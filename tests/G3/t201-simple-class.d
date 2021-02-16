
class Derived extends Base {
    int d1;
    int d2;
}

class Base {
    int b1;
    int b2;
}

class Derived3 extends Derived2 {

}

class Derived2 extends Base {

}

void main() {
    Derived d;
    d = new Derived;
    d.d1 = 1;
    d.d2 = 2;
    d.b1 = 11;
    d.b2 = 12;
    Print(d.d1);
    Print(d.d2);
    Print(d.b1);
    Print(d.b2);
}