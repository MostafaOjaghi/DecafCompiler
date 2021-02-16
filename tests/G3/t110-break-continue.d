void main () {
	int i;
	for (i = 0; true; i = i + 1) {
		if (i % 2 == 0)
			continue;
		if (i == 21)
			break;
		Print(i);
	}
	i = 0;
	while (true) {
		i = i + 1;
		if (i%2 == 0)
			continue;
		if (i == 21)
			break;
		Print(i);
	}
}
