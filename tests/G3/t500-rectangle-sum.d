class Rectangle {
    private int width;
    private int height;

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

    int calcSurface() {
        return width * height;
    }
}

void main() {
    int n;
    int sum;
    int i;
    Rectangle[] r;

    n = ReadInteger();
    sum = 0;
    r = NewArray(n, Rectangle);
    for (i = 0; i < n; i = i + 1) {
        int w;
        int h;

        r[i] = new Rectangle;
        w = ReadInteger();
        h = ReadInteger();
        r[i].setWidth(w);
        r[i].setHeight(h);
        sum = sum + r[i].calcSurface();
    }
    Print(sum);
}