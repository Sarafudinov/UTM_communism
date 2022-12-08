static int serial_putchar(char c, FILE *f)
{
	return Serial.write(c);
}

static int serial_getchar(FILE *)
{
	while(Serial.available() <= 0) {}
	return Serial.read();
}