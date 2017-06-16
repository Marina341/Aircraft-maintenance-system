//Title: Sustav za odrzavanje zrakoplova (Aircraft maintenance system)
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>

using namespace std;

class Vozila {
	//varijable napravljene radi vjezbe klasa, nisu koristene dalje
protected:
	int max_brzina, brzina;
	bool power, P;

public:
	void set_power(bool P) {
		power = P;
	}
	bool get_power() {
		return power;
	}
	void set_ugasi() {
		power = false;
		brzina = 0;
	}
	void set_upali(int x) {
		power = true;
		brzina = x;
	}
};
class Zrakoplovi; //deklaracija klase
class Check {
private:
	bool D_check;
	bool C_check;
	bool B_check;
	bool A_check;
public:
	void setD_check(bool x) {
		D_check = x;
	}
	bool getD_check() {
		return D_check;
	}
	void setC_check(bool x) {
		C_check = x;
	}
	bool getC_check() {
		return C_check;
	}
	void setB_check(bool x) {
		B_check = x;
	}
	bool getB_check() {
		return B_check;
	}
	void setA_check(bool x) {
		A_check = x;
	}
	bool getA_check() {
		return A_check;
	}
};

class Zrakoplovi : public Vozila {
public:
	Check maintenence;
protected:
	//varijable napravljene radi vjezbe - nisu dio klase vozila ali su bitne i za avion i helic:
	int uzgon;
	int tlak;
	int gravitacija;
	//varijable koje se koriste u programu:
	string naziv;
	string call_sign;
	int sati_naletaD;    //Sati naleta od zadnjeg D check-a
	int sati_naletaC;   //Sati naleta od zadnjeg D check-a
	int sati_naletaB;   //Sati naleta od zadnjeg D check-a
	int sati_naletaA;   //Sati naleta od zadnjeg D check-a
	int vrijemeD;   //Mjeseci od zadnjeg D check-a
	int vrijemeB;   //Mjeseci od zadnjeg B check-a
public:
	static int broj_zrakoplova;
	static int broj_helikoptera;
	static int broj_aviona;
	/*static int: za bilo koji objekt ce dati isti iznos - iskoristeno za pracenje broja aviona i helikoptera
	koji ce biti potrebno za funkcije OutputNakonCheckaAvion i OutputNakonCheckaHelic
	*/
public:
	void set_broj_helikoptera() {
		broj_helikoptera++;
	}
	int get_broj_helikoptera() {
		return broj_helikoptera;
	}
	void set_broj_aviona() {
		broj_aviona++;
	}
	int get_broj_aviona() {
		return broj_aviona;
	}

	void set_naziv(string x) {
		naziv = x;
	}
	string get_naziv() {
		return naziv;
	}
	void set_call_sign(string x) {
		call_sign = x;
	}
	string get_call_sign() {
		return call_sign;
	}
	void set_sati_naletaD(int x) {
		sati_naletaD = x;
	}
	int getsati_naletaD() {
		return sati_naletaD;
	}
	void set_sati_naletaC(int x) {
		sati_naletaC = x;
	}
	int getsati_naletaC() {
		return sati_naletaC;
	}
	void set_sati_naletaB(int x) {
		sati_naletaB = x;
	}
	int getsati_naletaB() {
		return sati_naletaB;
	}
	void set_sati_naletaA(int x) {
		sati_naletaA = x;
	}
	int getsati_naletaA() {
		return sati_naletaA;
	}
	void set_vrijemeD(int x) {
		vrijemeD = x;
	}
	int get_vrijemeD() {
		return vrijemeD;
	}
	void set_vrijemeB(int x) {
		vrijemeB = x;
	}
	int get_vrijemeB() {
		return vrijemeB;
	}
	void set_maintenance_D_check(bool x) {
		maintenence.setD_check(x);
	}
	bool get_maintenance_D_check() {
		return maintenence.getD_check();
	}
	void set_maintenance_C_check(bool x) {
		maintenence.setC_check(x);
	}
	bool get_maintenance_C_check() {
		return maintenence.getC_check();
	}
	void set_maintenance_B_check(bool x) {
		maintenence.setB_check(x);
	}
	bool get_maintenance_B_check() {
		return maintenence.getB_check();
	}
	void set_maintenance_A_check(bool x) {
		maintenence.setA_check(x);
	}
	bool get_maintenance_A_check() {
		return maintenence.getA_check();
	}
};
int Zrakoplovi::broj_zrakoplova = 0;
int Zrakoplovi::broj_helikoptera = 0;
int Zrakoplovi::broj_aviona = 0;
class Avion : public Zrakoplovi {
private:
	//varijable radi vjezbe - primjenive na avion ali ne na helic
	int min_brzina;
	int raspon_krila;
	int broj_motora;
public:
	//izrada konstruktora i destruktora radi vjezbe - nisu koristeni
	Avion::Avion() {
	}
	Avion::~Avion() {
	}
};
class Helikopter : public Zrakoplovi {
private:
	//varijabla radi vjezbe - primjenive na helic ali ne na avion
	int broj_propelera;
};

class Rezervni {
private:
	string naziv_rez;
	int potrebno;   //propisani minimum rezervnog dijela
	int rez_stanje; //koliko trenutno ima rezervnog dijela u skladistu

public:
	void set_naziv_rez(string x) {
		naziv_rez = x;
	}
	string get_naziv_rez() {
		return naziv_rez;
	}

	void set_rez_nastanju(int x) {
		rez_stanje = x;
}
	int get_rez_nastanju() {
		return rez_stanje;
	}

	void set_potrebno(int x) {
		potrebno = x;
	}
	int get_potrebno() {
		return potrebno;
	}
};
//Funkcije za provjeru treba li neki zrakoplov na odrzavanje
void D(vector<Zrakoplovi>zrakoplov) {
	int indetifikacija;
	for (int i = 0; i < zrakoplov.size(); i++) {
		if (zrakoplov[i].getsati_naletaD() > 1500 || zrakoplov[i].get_vrijemeD() > 48) {
			indetifikacija = i;
			zrakoplov[indetifikacija].maintenence.setD_check(true);
			if (zrakoplov[indetifikacija].maintenence.getD_check() == true) {
				cout << "Slanje automatskog e-mail-a i upororenje na ekranu: " << endl;
				cout << "Na zrakoplovu" << zrakoplov[indetifikacija].get_call_sign() << " potrebno je provesti glavnu provjeru (D check)" << endl << endl;
			}
		}
	}
}
void C(vector<Zrakoplovi>zrakoplov) {
	int indetifikac;
	for (int i = 0; i < zrakoplov.size(); i++) {
		if (zrakoplov[i].getsati_naletaC() > 3500) {
			indetifikac = i;
			zrakoplov[indetifikac].maintenence.setC_check(true);
			if (zrakoplov[indetifikac].maintenence.getC_check() == true) {
				cout << "Slanje automatskog e-mail-a i upororenje na ekranu: " << endl;
				cout << "Na zrakoplovu" << zrakoplov[indetifikac].get_call_sign() << " potrebno je provesti medju provjeru (C check)." << endl << endl;
			}
		}
	}
}
void B(vector<Zrakoplovi>zrakoplov) {
	int indetifikacija;
	for (int i = 0; i < zrakoplov.size(); i++) {
		if (zrakoplov[i].getsati_naletaB() > 800 || zrakoplov[i].get_vrijemeB() > 6) {
			indetifikacija = i;
			zrakoplov[indetifikacija].maintenence.setB_check(true);
			if (zrakoplov[indetifikacija].maintenence.getB_check() == true) {
				cout << "Slanje automatskog e-mail-a i upororenje na ekranu: " << endl;
				cout << "Na zrakoplovu" << zrakoplov[indetifikacija].get_call_sign() << " potrebno je provesti servisni pregled (B check)." << endl << endl;
			}
		}
	}
}

void A(vector<Zrakoplovi>zrakoplov) {
	int indetifikacija;

	for (int i = 0; i < zrakoplov.size(); i++) {
		if (zrakoplov[i].getsati_naletaA() > 125) {
			indetifikacija = i;
			zrakoplov[indetifikacija].maintenence.setA_check(true);
			if (zrakoplov[indetifikacija].maintenence.getA_check() == true) {
				cout << "Slanje automatskog e-mail-a i upororenje na ekranu: " << endl;
				cout << "Na zrakoplovu" << zrakoplov[indetifikacija].get_call_sign() << " potrebno je provesti pregled na platformi (A check)." << endl << endl;
			}
		}
	}
}
void provjeraa(vector<Zrakoplovi>zrakoplov) {
	D(zrakoplov);
	C(zrakoplov);
	B(zrakoplov);
	A(zrakoplov);
}

//Funkcije za unos zavrsene provjere:
void OutputNakonChecka(vector<Zrakoplovi>zrakoplov);       //deklaracija
void OutputNakonCheckaHelic(vector<Zrakoplovi>zrakoplov);  //deklaracija
void OutputNakonCheckaAvion(vector<Zrakoplovi>zrakoplov);  //deklaracija
void unosCheck(vector<Zrakoplovi>zrakoplov) {
	string call_signS;
	cout << "Upisite call sign zrakoplova: ";
	cin >> call_signS;
	int b = 1;
	bool uFloti = false;
	int indetifikacija;
	for (int i = 0; i < zrakoplov.size(); i++) {
		if (zrakoplov[i].get_call_sign() == call_signS) {
			indetifikacija = i;
			uFloti = true;
			break;
		}
	}
	if (uFloti) {
		char izbor;
		cout << "Izaberite Check (D/C/B/A) koji zelite unijeti: ";
		cin >> izbor;
		switch (izbor) {
		case 'D':
			zrakoplov[indetifikacija].set_sati_naletaD(0); //Glavnu provjera (D check) je zavrsena, sati naleta i vrijeme proteklo od zadnje glavne provjere su 0
			zrakoplov[indetifikacija].set_vrijemeD(0);
			break;
		case 'C':
			zrakoplov[indetifikacija].set_sati_naletaC(0);
		case 'B':
			zrakoplov[indetifikacija].set_sati_naletaB(0);
			zrakoplov[indetifikacija].set_vrijemeB(0);
			break;
		case 'A':
			zrakoplov[indetifikacija].set_sati_naletaA(0);
			break;
		default:
			cout << "Unesite valjani izbor";
		}
	}
	else {
		cout << "Call sign ne postoji";
	}
	OutputNakonChecka(zrakoplov);
}
void OutputNakonChecka(vector<Zrakoplovi>zrakoplov) {
	OutputNakonCheckaAvion(zrakoplov);
	OutputNakonCheckaHelic(zrakoplov);
}
void OutputNakonCheckaAvion(vector<Zrakoplovi>zrakoplov) {
	ofstream outavion;
	Avion koko;
	//  koko.get_broj_aviona() -kolicina aviona
	int rew = koko.get_broj_aviona();
	outavion.open("avioni.txt");
	for (int i = 0; i < koko.get_broj_aviona(); i++) {
		outavion << zrakoplov[i].get_naziv() << "|" << zrakoplov[i].get_call_sign() << "|" << zrakoplov[i].getsati_naletaD() << " ";
		outavion << zrakoplov[i].getsati_naletaC() << " " << zrakoplov[i].getsati_naletaB() << " " << zrakoplov[i].getsati_naletaA() << " ";
		outavion << zrakoplov[i].get_vrijemeD() << " " << zrakoplov[i].get_vrijemeB();
		rew--;
		if (rew > 0) {
			outavion << endl;
		}
		else {
			break;
		}
	}
	outavion.close();
}
void OutputNakonCheckaHelic(vector<Zrakoplovi>zrakoplov) {
	Helikopter bleko;
	Avion koko;
	// bleko.get_broj_helikoptera() -kolicina helikoptera
	//  koko.get_broj_aviona() -kolicina aviona
	ofstream outhelic;
	outhelic.open("Helikopteri.txt");
	int rew = bleko.get_broj_helikoptera();
	for (int i = koko.get_broj_aviona(); i < zrakoplov.size(); i++) {
		outhelic << zrakoplov[i].get_naziv() << "|" << zrakoplov[i].get_call_sign() << "|" << zrakoplov[i].getsati_naletaD() << " ";
		outhelic << zrakoplov[i].getsati_naletaC() << " " << zrakoplov[i].getsati_naletaB() << " " << zrakoplov[i].getsati_naletaA() << " ";
		outhelic << zrakoplov[i].get_vrijemeD() << " " << zrakoplov[i].get_vrijemeB();
		rew--;
		if (rew > 0) {
			outhelic << endl;
		}
		else {
			break;
		}
	}
	outhelic.close();
}

void OutputAvion(vector<Avion>novi); //deklaracija
void OutputHelic(vector<Helikopter>novih); //deklaracija

 //Funkcije za unos i ispis zrakoplova:
void UnesiNoviAvion() {
	vector<Avion>novi;
	Avion objektaa;
	cout << "Unesi naziv novog aviona: ";
	string imee;
	cin >> imee;
	objektaa.set_naziv(imee);
	cout << "Unesite call sign aviona: ";
	string call_signn;
	cin >> call_signn;
	objektaa.set_call_sign(call_signn);
	cout << "Koliko sati naleta ima avion od zadnjeg D check-a? ";
	int naletD;
	cin >> naletD;
	objektaa.set_sati_naletaD(naletD);
	cout << "Koliko sati naleta ima avion od zadnjeg C check-a? ";
	int naletC;
	cin >> naletC;
	objektaa.set_sati_naletaC(naletC);
	cout << "Koliko sati naleta ima avion od zadnjeg B check-a? ";
	int satiB;
	cin >> satiB;
	objektaa.set_sati_naletaB(satiB);
	cout << "Koliko sati naleta ima avion od zadnjeg A check-a? ";
	int naletAa;
	cin >> naletAa;
	objektaa.set_sati_naletaA(naletAa);

	cout << "Koliko je vremena proslo od zadnjeg D check-a? ";
	int vrijeme_naletDd;
	cin >> vrijeme_naletDd;
	objektaa.set_vrijemeD(vrijeme_naletDd);

	cout << "Koliko je vremena proslo od zadnjeg B check-a? ";
	int vrijeme_naletB;
	cin >> vrijeme_naletB;
	objektaa.set_vrijemeB(vrijeme_naletB);
	objektaa.set_broj_aviona();
	novi.push_back(objektaa);

	OutputAvion(novi);
}
void OutputAvion(vector<Avion>novi) {
	ofstream fout;
	fout.open("avioni.txt", ios::app);
	for (int i = 0; i < novi.size(); i++) {
		fout << "\n";
		fout << novi[i].get_naziv() << "|" << novi[i].get_call_sign() << "|" << novi[i].getsati_naletaD() << " ";
		fout << novi[i].getsati_naletaC() << " " << novi[i].getsati_naletaB() << " " << novi[i].getsati_naletaA() << " ";
		fout << novi[i].get_vrijemeD() << " " << novi[i].get_vrijemeB();
	}
	fout.close();
}
void UnesiNoviHelikopter() {
	vector<Helikopter>novih;
	Helikopter objekthh;
	cout << "Unesi naziv novog helikoptera: ";
	string ime;
	cin >> ime;
	objekthh.set_naziv(ime);
	cout << "Unesite call sign helikoptera: ";
	string call_sign;
	cin >> call_sign;
	objekthh.set_call_sign(call_sign);
	cout << "Koliko sati naleta helikopter ima od zadnjeg D check-a? ";
	int naletD;
	cin >> naletD;
	objekthh.set_sati_naletaD(naletD);
	cout << "Koliko sati naleta helikopter ima od zadnjeg C check-a? ";
	int naletC;
	cin >> naletC;
	objekthh.set_sati_naletaC(naletC);
	cout << "Koliko sati naleta helikopter ima od zadnjeg B check-a? ";
	int satiB;
	cin >> satiB;
	objekthh.set_sati_naletaB(satiB);
	cout << "Koliko sati naleta helikopter ima od zadnjeg A check-a? ";
	int naletA;
	cin >> naletA;
	objekthh.set_sati_naletaA(naletA);

	cout << "Koliko je vremena proslo od zadnjeg D check-a? ";
	int vrijeme_naletD;
	cin >> vrijeme_naletD;
	objekthh.set_vrijemeD(vrijeme_naletD);

	cout << "Koliko je vremena proslo od zadnjeg B check-a? ";
	int vrijeme_naletB;
	cin >> vrijeme_naletB;
	objekthh.set_vrijemeB(vrijeme_naletB);
	objekthh.set_broj_helikoptera();
	novih.push_back(objekthh);

	for (int i = 0; i < novih.size(); i++) {
		cout << novih[i].get_naziv() << "\t" + novih[i].get_call_sign() << "\t" << novih[i].getsati_naletaD() << "\t";
		cout << novih[i].getsati_naletaC() << "\t" << novih[i].getsati_naletaB() << "\t" << novih[i].getsati_naletaA() << "\t";
		cout << novih[i].get_vrijemeD() << "\t" << novih[i].get_vrijemeB() << endl;
	}
	OutputHelic(novih);
}
void OutputHelic(vector<Helikopter>novih) {
	ofstream fout;
	fout.open("Helikopteri.txt", ios::app);
	for (int i = 0; i < novih.size(); i++) {
		fout << "\n";
		fout << novih[i].get_naziv() << "|" << novih[i].get_call_sign() << "|" << novih[i].getsati_naletaD() << " ";
		fout << novih[i].getsati_naletaC() << " " << novih[i].getsati_naletaB() << " " << novih[i].getsati_naletaA() << " ";
		fout << novih[i].get_vrijemeD() << " " << novih[i].get_vrijemeB();
	}
	fout.close();
}
void UnesiNoviZrakoplov() {
	vector<Avion>novi;
	vector<Helikopter>novih;
	cout << "Zelite li unjeti novi avion ili novi helikopter?" << endl;
	cout << "1. Avion 2. Helikopter" << endl;
	int izbor;
	cin >> izbor;
	switch (izbor) {
	case 1:
		UnesiNoviAvion();
		OutputAvion(novi);
		break;
	case 2:
		UnesiNoviHelikopter();
		OutputHelic(novih);
		break;
	default:
		cout << "Unesite valjani izbor." << endl;
	}
}
void InputAvion(vector<Zrakoplovi>&zrakoplov) {
	ifstream input;
	input.open("avioni.txt");
	Avion objekt;
	string line;
	int satiD, satiC, satiB, satiA, vriD, vriB;
	while (input) {

		getline(input, line, '|');//naziv
		objekt.set_naziv(line);
		getline(input, line, '|');
		objekt.set_call_sign(line);

		input >> satiD;  //sati_naleta
		objekt.set_sati_naletaD(satiD);
		input >> satiC;
		objekt.set_sati_naletaC(satiC);
		input >> satiB;
		objekt.set_sati_naletaB(satiB);
		input >> satiA;
		objekt.set_sati_naletaA(satiA);

		input >> vriD; //Vrijeme
		objekt.set_vrijemeD(vriD);
		input >> vriB;
		objekt.set_vrijemeB(vriB);
		input.ignore();
		objekt.set_broj_aviona();
		zrakoplov.push_back(objekt);

	}
	input.close();
}
void InputHelic(vector<Zrakoplovi>&zrakoplov) {
	ifstream inputh;
	inputh.open("Helikopteri.txt");
	string line;
	int satiD, satiC, satiB, satiA, vriD, vriB;
	Helikopter objekth;
	while (inputh) {
		getline(inputh, line, '|');//naziv
		objekth.set_naziv(line);
		getline(inputh, line, '|');  //call_sign
		objekth.set_call_sign(line);

		inputh >> satiD;  //sati_naleta
		objekth.set_sati_naletaD(satiD);
		inputh >> satiC;
		objekth.set_sati_naletaC(satiC);
		inputh >> satiB;
		objekth.set_sati_naletaB(satiB);
		inputh >> satiA;
		objekth.set_sati_naletaA(satiA);

		inputh >> vriD; //Vrijeme
		objekth.set_vrijemeD(vriD);
		inputh >> vriB;
		objekth.set_vrijemeB(vriB);

		inputh.ignore();
		objekth.set_broj_helikoptera();
		zrakoplov.push_back(objekth);
	}
	inputh.close();
}
void IspisZrakoplova(vector<Zrakoplovi>zrakoplov) {
	for (int i = 0; i < zrakoplov.size(); i++) {
		cout << zrakoplov[i].get_naziv() << "\t" + zrakoplov[i].get_call_sign() << "\t" << zrakoplov[i].getsati_naletaD() << "\t";
		cout << zrakoplov[i].getsati_naletaC() << "\t" << zrakoplov[i].getsati_naletaB() << "\t" << zrakoplov[i].getsati_naletaA() + "\t";
		cout << zrakoplov[i].get_vrijemeD() << "\t" << zrakoplov[i].get_vrijemeB() << endl;
	}
}

//Funkcije sustava rezervnih dijelova:
void InputRezervni(vector<Rezervni>&dio) {
	ifstream inrez;
	inrez.open("rezervni.txt");
	string line;
	int x;
	Rezervni objektr;

	while (inrez) {
		getline(inrez, line, '|');//naziv
		objektr.set_naziv_rez(line);

		inrez >> x;
		objektr.set_rez_nastanju(x);
		inrez >> x;
		objektr.set_potrebno(x);

		inrez.ignore();
		dio.push_back(objektr);
	}
	inrez.close();

}
void IspisRezervni(vector<Rezervni>&dio) {
	for (int i = 0; i < dio.size(); i++) {
		cout << dio[i].get_naziv_rez() << "\t" << dio[i].get_rez_nastanju() << "\t" << dio[i].get_potrebno() << endl;
	}
}
void NoviRezervni(vector<Rezervni>&dio) {
	//taj dio nije do sada postojao u skladistu
	Rezervni object;
	cout << "Unesi naziv novog rezevnog dijela: " << endl;
	string ime;
	cin >> ime;
	object.set_naziv_rez(ime);
	cout << "Unesite koliko ima novih dijelova: " << endl;
	int broj;
	cin >> broj;
	object.set_rez_nastanju(broj);
	cout << "Upisite minimalu propisanu kolicinu rezervnog dijela: " << endl;
	int min;
	cin >> min;
	object.set_potrebno(min);
	dio.push_back(object);
}
void Promjena_stanja_Rezervni(vector<Rezervni>&dio) {
	cout << "Kojiem rezervnom dijelu zelite promjeniti kolicinu na stanju?" << endl;
	string part;
	cin >> part;
	int indetifikacija, novostanje;
	for (int i = 0; i < dio.size(); i++) {
		if (dio[i].get_naziv_rez() == part) {
			indetifikacija = i;

			cout << "Koliko dijelova ima na stanju?";
			cin >> novostanje;
			dio[indetifikacija].set_rez_nastanju(novostanje);
		}
	}
}

void OutputunosRezervni(vector<Rezervni>dio) {
	ofstream outrez;
	outrez.open("rezervni.txt");
	int rew = dio.size();
	for (int i = 0; i < dio.size(); i++) {
		outrez << dio[i].get_naziv_rez() << "|" << dio[i].get_rez_nastanju() << " " << dio[i].get_potrebno();
		rew--;
		if (rew > 0) {
			outrez << endl;
		}
		else {
			break;
		}
	}
	outrez.close();
}
void ProvjeraRezervnih(vector<Rezervni>&dio) {
	int k;
	for (int i = 0; i < dio.size(); i++) {
		if (dio[i].get_rez_nastanju() < dio[i].get_potrebno()) {
			k = dio[i].get_potrebno() - dio[i].get_rez_nastanju();
			cout << "U skladistu ima premalo rezervnog dijela: " << dio[i].get_naziv_rez() << ". Potrebno je nabaviti jos minimalno " << k << endl;
		}
	}
}
void SustavRezervni(vector<Rezervni>&dio) {
	cout << "Dobrodosli u sustav rezervnih dijelova." << endl;
	cout << "Izbornik : \n1. Ispis rezervnih dijelova \n2. Unos novih rezervnih dijelova \n3. Promjena stanja rezervnih dijelova \n4. Provjera rezervnih dijelova";
	int izbor;
	cin >> izbor;
	switch (izbor) {
	case 1:
		IspisRezervni(dio);
		break;
	case 2:
		NoviRezervni(dio);
		OutputunosRezervni(dio);
		break;
	case 3:
		Promjena_stanja_Rezervni(dio);
		OutputunosRezervni(dio);
		break;
	case 4:
		ProvjeraRezervnih(dio);
		break;
	}
}
int main()
{
	vector<Zrakoplovi>zrakoplov;
	vector<Rezervni>dio;
	InputAvion(zrakoplov);
	InputHelic(zrakoplov);
	InputRezervni(dio);
	cout << "Dobrodosli u sustav odrzavanja zrakoplova." << endl;
	cout << "Izbornik \n1. Popis zrakoplova HZNS-a  \n2. Provjera za odrzavanje \n3. Unos novih zrakoplova u flotu HZNS-a" << endl;
	cout << "4. Sustav rezervnih dijelova \n5. Upis zavrsene provjere za flotu HZNS-a" << endl;
	int izbor;
	cin >> izbor;
	switch (izbor) {
	case 1:
		IspisZrakoplova(zrakoplov);
		break;
	case 2:
		provjeraa(zrakoplov);
		break;
	case 3:
		UnesiNoviZrakoplov();
		break;
	case 4:
		SustavRezervni(dio);
		break;
	case 5:
		unosCheck(zrakoplov);
		break;
	default:
		cout << "Unesite valjani izbor" << endl;
	}
	system("pause");
	return 0;
}