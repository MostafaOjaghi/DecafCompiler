void main() {
	bool a;
	bool b;
	bool c;
	a = true;
	b = true;
	c = a || b;
	Print(c);
	c = a && b;
	Print(c);

	a = true;
	b = false;
	c = a || b;
	Print(c);
	c = a && b;
	Print(c);

	a = false;
	b = true;
	c = a || b;
	Print(c);
	c = a && b;
	Print(c);

	a = false;
	b = false;
	c = a || b;
	Print(c);
	c = a && b;
	Print(c);
}