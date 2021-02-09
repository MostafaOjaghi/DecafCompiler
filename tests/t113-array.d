void main() {
	int[] a;
	int n;
	int i;
	int sum;
	n = ReadInteger();
	a = NewArray(n, int);
	for (i = 0; i < n; i = i + 1) {
		a[i] = ReadInteger();
	}
	sum = 0;
	for (i = 0; i < n; i = i + 1)
		sum = sum + a[i];
	Print(sum);
}
