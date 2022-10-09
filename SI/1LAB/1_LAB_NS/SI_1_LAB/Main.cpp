#include "libs.h"
#include "GenKey.h"
#include "En_De_cryptor.h"

int length = 10;
int* Plaintext = new int[length]; // Открытый текст

// Инициализация алгоритма
void Initialize()
{
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < length; i++)
		Plaintext[i] = rand() % 1000;

	cout << "Generate " << length << " random numbers:" << endl;
	for (i = 0; i < length; i++)
		cout << Plaintext[i] << " ";
	cout << endl << endl;
}

int main()
{
	Initialize();

	PublicKey* publicKey = new PublicKey();
	PrivateKey* privateKey = new PrivateKey();

	GenKey* gk = new GenKey(publicKey, privateKey);
	En_De_cryptor* edCryptor = new En_De_cryptor(publicKey, privateKey, Plaintext, length);

	edCryptor->Encrypt();
	edCryptor->Decrypt();
}