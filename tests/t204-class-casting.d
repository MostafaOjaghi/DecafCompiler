
class Base {
    int b1;
}

class Derived1 extends Base {
    int d11;
}

class Derived2 extends Base {
    int d12;
}

void main() {
    Base b_obj;
    Derived1 d1_obj;
    Derived2 d2_obj;

    b_obj = new Base;
    d1_obj = new Derived1;
    d2_obj = new Derived2;
    b_obj = d1_obj;
    d2_obj = d1_obj;
}