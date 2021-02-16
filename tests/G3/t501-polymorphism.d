class Animal {
    void makeSound() {

    }
}

class Dog extends Animal {
    void makeSound() {
        Print("bark!");
    }
}

class Cat extends Animal {
    void makeSound() {
        Print("miaw!");
    }
}

void main() {
    Animal[] animals;
    int i;
    int n;

    n = ReadInteger();
    animals = NewArray(n, Animal);
    for (i = 0; i < n; i = i + 1) {
        if (i % 2 == 0) {
            animals[i] = new Cat;
        } else {
            animals[i] = new Dog;
        }
    }

    for (i = 0; i < n; i = i + 1) {
        animals[i].makeSound();
    }
}