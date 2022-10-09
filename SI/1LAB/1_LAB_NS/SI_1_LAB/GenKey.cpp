#include "GenKey.h"

int GenKey::ProducePrimeNumber(int prime[], int size)
{
	// Генерация простых чисел в пределах 1000
	int n = size;

	int c = 0;
	int vis[1001];

	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= n; i++) if (!vis[i])
	{
		prime[c++] = i;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}

	return c;
}

// Расширенный алгоритм Евклида
int GenKey::Exgcd(int m, int n, int& x)
{
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m % n;
	int q = (m - r) / n;
	while (r)
	{
		x = x0 - q * x1; y = y0 - q * y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		m = n; n = r; r = m % n;
		q = (m - r) / n;
	}
	return n;
}


void GenKey::Init()
{
	// Вынимаем простые числа в пределах 1000 и сохраняем их в массиве prime []
	int prime[5000];
	int count_Prime = ProducePrimeNumber(prime, 1000);

	// Случайно возьмем два простых числа p, q
	srand((unsigned)time(NULL));
	int min = 2, max = 1000;

	int randNum1 = (min + rand() % (max - min)) % count_Prime;
	int randNum2 = (min + rand() % (max - min)) % count_Prime;
	int p = prime[randNum1], q = prime[randNum2];

	int n = p * q;
	publicKey->n = n;
	privateKey->n = n;

	int phi = (p - 1) * (q - 1);
	
	// Используем расширенный алгоритм Евклида, чтобы найти e, d
	for (int j = 3; j < phi; j += 1331)
	{
		int gcd = Exgcd(j, phi, privateKey->d);
		if (gcd == 1 && privateKey->d > 0)
		{
			publicKey->e = j;
			break;
		}

	}
}

GenKey::GenKey(PublicKey *pubKey, PrivateKey* privKey) {
	this->privateKey = privKey;
	this->publicKey = pubKey;
	Init();
};

