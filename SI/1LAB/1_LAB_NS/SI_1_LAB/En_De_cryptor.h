#pragma once
class En_De_cryptor
{

	PrivateKey* privateKey;
	PublicKey* publicKey;

	int len;
	int* Plaintext; // Открытый текст
	long long* Ciphertext; // Зашифрованный текст

public:
	En_De_cryptor(PublicKey* publicKey, PrivateKey* privateKey, int* msg, int len) {

		Plaintext = new int[len];
		Ciphertext = new long long[len];
		
		this->len = len;
		for (size_t i = 0; i < len; i++)
			Plaintext[i] = msg[i];
		
		this->privateKey = privateKey;
		this->publicKey = publicKey;
	};
	void Encrypt();
	void Decrypt();

private:
	long long Modular_Exonentiation(long long a, int b, int n);
	int BianaryTransform(int num, int bin_num[]);
};

