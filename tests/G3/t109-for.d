void main() {
	int i;
	for (i = 0; i < 10; i = i + 1) {
		int a;
		a = 2 * i + 1;
		Print(a,i);
	}
	i = 0;
	for (;i < 10;) {
		int a;
		a = 2 * i + 1;
		Print(a,i);
		i = i + 1;
	}
}
