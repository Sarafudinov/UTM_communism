#include "libs.h"
#include "En_De_cryptor.h"

void En_De_cryptor::Encrypt()
{
	for (int i = 0; i < len; i++)
		Ciphertext[i] = Modular_Exonentiation(Plaintext[i], publicKey->e, publicKey->n);

	cout << "Use the public key (" << publicKey->e << ", " << publicKey->n << ") to encrypt:" << '\n';
	for (int i = 0; i < len; i++)
		cout << Ciphertext[i] << " ";
	cout << '\n' << '\n';
}

void En_De_cryptor::Decrypt()
{
	for (int i = 0; i < len; i++)
		Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], privateKey->d, privateKey->n);

	cout << "Use the private key (" << privateKey->d << ", " << privateKey->n << ") to decrypt:" << '\n';
	for (int i = 0; i < len; i++)
		cout << Ciphertext[i] << " ";
	cout << '\n' << '\n';
}

// Повторное возведение в квадрат в степень
long long En_De_cryptor::Modular_Exonentiation(long long a, int b, int n)
{
	int c = 0, bin_num[1000];
	long long d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c = 2 * c;
		d = (d * d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d * a) % n;
		}
	}
	return d;
}

// Двоичное преобразование
int En_De_cryptor::BianaryTransform(int num, int bin_num[])
{
	int i = 0, mod = 0;

	// Преобразуется в двоичный, временно сохраняется в массиве temp []
	while (num != 0)
	{
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}

	// Возвращает количество цифр в двоичных числах
	return i;
}
