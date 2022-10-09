#include "libs.h"

class GenKey
{
	PrivateKey* privateKey;
	PublicKey* publicKey;

public:
	GenKey(PublicKey* pubKey, PrivateKey* privKey);
private:
	int ProducePrimeNumber(int prime[], int size);
	int Exgcd(int m, int n, int& x);
	void Init();
};
