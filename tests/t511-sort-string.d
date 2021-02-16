
void sort(string[] items) {

    /* implementation of bubble sort */
    int i;
    int j;

    int n;
    n = items.length();

    for (i = 0; i < n-1; i = i + 1)
        for (j = 0; j < n - i - 1; j = j + 1)
            if (items[j] > items[j + 1]) {
                string t;
                t = items[j];
                items[j] = items[j + 1];
                items[j + 1] = t;
            }
}

int main() {
    int i;
    int j;
    string[] rawitems;
    string[] items;

    Print("Please enter the strings (max count: 100, enter END to end sooner): ");

    rawitems = NewArray(100, string);
    for (i = 0; i < 100; i = i + 1) {
        string x;
        x = ReadLine();
        if (x == "END") break;

        rawitems[i] = x;
    }

    items = NewArray(i, string);

    // copy to a more convenient location
    for (j = 0; j < i; j = j + 1) {
        items[j] = rawitems[j];
    }

    sort(items);

    Print("After sort: ");

    for (i = 0; i < items.length(); i = i + 1) {
        Print(items[i]);
    }
}
