void main() {
    int i;
    int j;
    int n;
    bool[] mark;
    string ans;

    n = ReadInteger();
    mark = NewArray(n + 1, bool);

    for (i = 0; i <= n; i = i + 1) {
        mark[i] = false;
    }

    for (i = 2; i <= n; i = i + 1) {
        for (j = i + i; j <= n; j = j + i) {
            mark[j] = true;
        }
    }
    mark[1] = true;
    ans = "";
    for (i = 1; i <= n; i = i + 1)
        if (mark[i] == true)
            ans = ans + "a";
        else
            ans = ans + "b";
    Print(ans);
}