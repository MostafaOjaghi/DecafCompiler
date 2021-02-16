void main() {
	int a;
	a = 5;
	{
		int a;
		a = 10;
		Print(a);
	}
	Print(a);
	{
		a = 22;
		Print(a);
	}
	Print(a);
}
