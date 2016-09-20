#include<iostream.h>
#include<string.h>
#include <algorithm>

void invers(int a[2][2], int (&b)[2][2]);
int invmod(int n, int b);
void enkrip(char plainTxt[], char *cipherTxt, int key[2][2]);
void dekrip(char cipherTxt[], char *plainTxt, int inv[2][2]);

int main(){
	int key[2][2];
	int inv[2][2];
	int detK, detInv;
	char plainTxt[99];
	char cipherTxt[99];
	bool req1=false;
	bool req2=false;
	bool req3=false;
	
	//masukan key
	cout<<"Masukan Key dalam bentuk matriks 2x2"<<endl;	
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			cin >> key[i][j];
		}
	}
	
	//cek apakah matriks ini bisa jadi key
	
	//cek apakah matrik invertible (req1)
	detK = (key[0][0]*key[1][1]) - (key[0][1]*key[1][0]);	
	if(detK != 0) req1=true;
	cout<< endl << "Determinan matrik ini adalah "<<detK<<endl;
	
	//cek apakah gcd = 1
	if(std::__gcd(detK,26) == 1) req2=true;
	cout << endl << "gcd(detK,26) = " << std::__gcd(detK,26) << endl;
	
	//cek apakah detK x detInvers (mod 26) = 1
	
	invers(key,inv);
	
	cout << endl << "Invers matriks key"<<endl;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			cout<<inv[i][j]<<"\t";;
		}
		cout<<endl;
	}
	detInv = (inv[0][0]*inv[1][1]) - (inv[0][1]*inv[1][0]);
	
	if(detK >= 0) detK = detK % 26;
	else detK = 26 - ((-detK) % 26);
	
	if(detInv >= 0) detInv = detInv % 26;
	else detInv = 26 - ((-detInv) % 26);
	
	if((detK*detInv)%26 == 1) req3=true;
	
	
	if(req1 && req2 && req3){
		cout << endl << "matriks k dapat menjadi key" << endl <<endl;
		cout << "masukan kalimat yang akan di enkripsi: ";
		cin >> plainTxt;
		enkrip(plainTxt, cipherTxt, key);
		int length = strlen(cipherTxt);
		
		cout << "Hasil enkripsi: ";
		for(int i=0; i<length-1; i++){
			cout<<cipherTxt[i];
		}
		cout<<endl;
		dekrip(cipherTxt, plainTxt, inv);
		cout << "Hasil dekripsi: ";
		
		for(int i=0; i<length-1; i++){
			cout<<plainTxt[i];
		}
		cout<<endl;
		
	}else{
		cout << endl << "matriks k tidak dapat menjadi key" << endl;
	}

}

int invmod(int n, int b){
	int n0,b0,q,r,temp;
	
	int t0 = 0;
	int t = 1;
	n0 = n;
	b0 = b;
	q = floor(n0/b0);
	r = n0 - q * b0;
	
	while (r > 0){
		temp = t0 - q * t;
		if(temp >= 0) temp = temp % n;
		else temp = n - ((-temp) % n);
		t0 = t;
		t = temp;
		n0 = b0;
		b0 = r;
		q = floor(n0/b0);
		r = n0 - q * b0;
	}
	
	return t;
}

void invers(int a[2][2], int (&b)[2][2]){
	
	int detK = (a[0][0]*a[1][1]) - (a[0][1]*a[1][0]);	
	
	b[0][0] = ((invmod(26,detK)) * a[1][1]);
	b[0][1] = ((invmod(26,detK)) * a[0][1]*(-1));
	b[1][0] = ((invmod(26,detK)) * a[1][0]*(-1));
	b[1][1] = ((invmod(26,detK)) * a[0][0]);
	
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			if(b[i][j] >= 0) b[i][j] = b[i][j] % 26;
			else b[i][j] = 26 - ((-b[i][j]) % 26);
		}
	}
}
void enkrip(char plainTxt[], char *cipherTxt, int key[2][2]){
	int length = strlen(plainTxt);
	for (int i = 0; i < length; i++){
		plainTxt[i] = tolower(plainTxt[i]);
		plainTxt[i] = plainTxt[i]-97;
	}
	for (int i = 0; i < length-1; i++){
		cipherTxt[i] = ((plainTxt[i]*key[0][0])+(plainTxt[i+1]*key[1][0]))%26;
		cipherTxt[i+1] = ((plainTxt[i]*key[0][1])+(plainTxt[i+1]*key[1][1]))%26;
		i++;
	}
	for (int i = 0; i < length; i++){
		cipherTxt[i] = cipherTxt[i]+97;
	}
}
void dekrip(char cipherTxt[], char *plainTxt, int inv[2][2]){
	int length = strlen(cipherTxt);
	for (int i = 0; i < length; i++){
		cipherTxt[i] = tolower(cipherTxt[i]);
		cipherTxt[i] = cipherTxt[i]-97;
	}
	for (int i = 0; i < length-1; i++){
		plainTxt[i] = (cipherTxt[i]*inv[0][0]+cipherTxt[i+1]*inv[1][0])%26;
		plainTxt[i+1] = (cipherTxt[i]*inv[0][1]+cipherTxt[i+1]*inv[1][1])%26;
		i++;
	}
	for (int i = 0; i < length; i++){
		plainTxt[i] = plainTxt[i]+97;
	}
}
