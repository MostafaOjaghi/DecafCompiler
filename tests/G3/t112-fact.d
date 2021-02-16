int fact(int x) {
	if (x == 0)
		return 1;
	return x * fact(x - 1);
}

void main() {
	int n;
	int i;
	n = ReadInteger();
	for (i = 0; i < n; i = i + 1) {
		int a;
		a = ReadInteger();
		Print(fact(a)); 
	}
}
