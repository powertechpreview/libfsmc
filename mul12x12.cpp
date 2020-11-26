#include <iostream>
using namespace std;
#include <altivec.h>
#include <cstdlib>

// printa a multiplicacao de duas matrizes a e b de tamanho 4x4
double* result (double* a, double* b) {
	int tam = 12;
	double* out;
	out = new double[tam*tam];
	double aux;
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			aux = 0;
			for (int k = 0; k < tam; k++) {
				aux += a[tam*i + k]*b[tam*k + j];
			}
			out[j + tam*i] = aux;
		}
	}
	return out;
}

/*
	TODO: a gente tem que ver como vai ser a entrada,
	se vai ser matrix, ponteiro	ou array
*/
double* mul(double* mLHS, double* mRHS, int boolean_mLHSisRowMajor = 1) {

	__vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41, mLHScol51, mLHScol61, mLHScol71, mLHScol81, mLHScol91, mLHScol101, mLHScol111, mLHScol121,
									mLHScol12, mLHScol22, mLHScol32, mLHScol42, mLHScol52, mLHScol62, mLHScol72, mLHScol82, mLHScol92, mLHScol102, mLHScol112, mLHScol122,
									mLHScol13, mLHScol23, mLHScol33, mLHScol43, mLHScol53, mLHScol63, mLHScol73, mLHScol83, mLHScol93, mLHScol103, mLHScol113, mLHScol123,
									mLHScol14, mLHScol24, mLHScol34, mLHScol44, mLHScol54, mLHScol64, mLHScol74, mLHScol84, mLHScol94, mLHScol104, mLHScol114, mLHScol124,
									mLHScol15, mLHScol25, mLHScol35, mLHScol45, mLHScol55, mLHScol65, mLHScol75, mLHScol85, mLHScol95, mLHScol105, mLHScol115, mLHScol125,
									mLHScol16, mLHScol26, mLHScol36, mLHScol46, mLHScol56, mLHScol66, mLHScol76, mLHScol86, mLHScol96, mLHScol106, mLHScol116, mLHScol126,
									mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81, mRHSrow91, mRHSrow101, mRHSrow111, mRHSrow121,
									mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82, mRHSrow92, mRHSrow102, mRHSrow112, mRHSrow122,
									mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83, mRHSrow93, mRHSrow103, mRHSrow113, mRHSrow123,
									mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84, mRHSrow94, mRHSrow104, mRHSrow114, mRHSrow124,
									mRHSrow15, mRHSrow25, mRHSrow35, mRHSrow45, mRHSrow55, mRHSrow65, mRHSrow75, mRHSrow85, mRHSrow95, mRHSrow105, mRHSrow115, mRHSrow125,
									mRHSrow16, mRHSrow26, mRHSrow36, mRHSrow46, mRHSrow56, mRHSrow66, mRHSrow76, mRHSrow86, mRHSrow96, mRHSrow106, mRHSrow116, mRHSrow126;

	if (boolean_mLHSisRowMajor) {

		const static __vector unsigned char GETCOL1 = { 0, 1, 2, 3, 4, 5, 6, 7,
																					16, 17, 18, 19, 20, 21, 22, 23};

		const static __vector unsigned char GETCOL2 = { 8, 9, 10, 11, 12, 13, 14, 15,
																					24, 25, 26, 27, 28, 29, 30, 31};

		// pegando as linhas 1 e 2 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux1 = vec_xl(0, mLHS);
		__vector double mLHSaux2 = vec_xl(0, mLHS + 12);
		mLHScol11 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
		mLHScol21 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux3 = vec_xl(0, mLHS + 2);
		__vector double mLHSaux4 = vec_xl(0, mLHS + 14);
		mLHScol31 = vec_perm(mLHSaux3, mLHSaux4, GETCOL1);
		mLHScol41 = vec_perm(mLHSaux3, mLHSaux4, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux5 = vec_xl(0, mLHS + 4);
		__vector double mLHSaux6 = vec_xl(0, mLHS + 16);
		mLHScol51 = vec_perm(mLHSaux5, mLHSaux6, GETCOL1);
		mLHScol61 = vec_perm(mLHSaux5, mLHSaux6, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux7 = vec_xl(0, mLHS + 6);
		__vector double mLHSaux8 = vec_xl(0, mLHS + 18);
		mLHScol71 = vec_perm(mLHSaux7, mLHSaux8, GETCOL1);
		mLHScol81 = vec_perm(mLHSaux7, mLHSaux8, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux9 = vec_xl(0, mLHS + 8);
		__vector double mLHSaux10 = vec_xl(0, mLHS + 20);
		mLHScol91 = vec_perm(mLHSaux9, mLHSaux10, GETCOL1);
		mLHScol101 = vec_perm(mLHSaux9, mLHSaux10, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux11 = vec_xl(0, mLHS + 10);
		__vector double mLHSaux12 = vec_xl(0, mLHS + 22);
		mLHScol111 = vec_perm(mLHSaux11, mLHSaux12, GETCOL1);
		mLHScol121 = vec_perm(mLHSaux11, mLHSaux12, GETCOL2);

		// pegando as linhas 3 e 4 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux13 = vec_xl(0, mLHS + 24);
		__vector double mLHSaux14 = vec_xl(0, mLHS + 36);
		mLHScol12 = vec_perm(mLHSaux13, mLHSaux14, GETCOL1);
		mLHScol22 = vec_perm(mLHSaux13, mLHSaux14, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux15 = vec_xl(0, mLHS + 26);
		__vector double mLHSaux16 = vec_xl(0, mLHS + 38);
		mLHScol32 = vec_perm(mLHSaux15, mLHSaux16, GETCOL1);
		mLHScol42 = vec_perm(mLHSaux15, mLHSaux16, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux17 = vec_xl(0, mLHS + 28);
		__vector double mLHSaux18 = vec_xl(0, mLHS + 40);
		mLHScol52 = vec_perm(mLHSaux17, mLHSaux18, GETCOL1);
		mLHScol62 = vec_perm(mLHSaux17, mLHSaux18, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux19 = vec_xl(0, mLHS + 30);
		__vector double mLHSaux20 = vec_xl(0, mLHS + 42);
		mLHScol72 = vec_perm(mLHSaux19, mLHSaux20, GETCOL1);
		mLHScol82 = vec_perm(mLHSaux19, mLHSaux20, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux21 = vec_xl(0, mLHS + 32);
		__vector double mLHSaux22 = vec_xl(0, mLHS + 44);
		mLHScol92 = vec_perm(mLHSaux21, mLHSaux22, GETCOL1);
		mLHScol102 = vec_perm(mLHSaux21, mLHSaux22, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux23 = vec_xl(0, mLHS + 34);
		__vector double mLHSaux24 = vec_xl(0, mLHS + 46);
		mLHScol112 = vec_perm(mLHSaux23, mLHSaux24, GETCOL1);
		mLHScol122 = vec_perm(mLHSaux23, mLHSaux24, GETCOL2);

		// pegando as linhas 5 e 6 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux25 = vec_xl(0, mLHS + 48);
		__vector double mLHSaux26 = vec_xl(0, mLHS + 60);
		mLHScol13 = vec_perm(mLHSaux25, mLHSaux26, GETCOL1);
		mLHScol23 = vec_perm(mLHSaux25, mLHSaux26, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux27 = vec_xl(0, mLHS + 50);
		__vector double mLHSaux28 = vec_xl(0, mLHS + 62);
		mLHScol33 = vec_perm(mLHSaux27, mLHSaux28, GETCOL1);
		mLHScol43 = vec_perm(mLHSaux27, mLHSaux28, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux29 = vec_xl(0, mLHS + 52);
		__vector double mLHSaux30 = vec_xl(0, mLHS + 64);
		mLHScol53 = vec_perm(mLHSaux29, mLHSaux30, GETCOL1);
		mLHScol63 = vec_perm(mLHSaux29, mLHSaux30, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux31 = vec_xl(0, mLHS + 54);
		__vector double mLHSaux32 = vec_xl(0, mLHS + 66);
		mLHScol73 = vec_perm(mLHSaux31, mLHSaux32, GETCOL1);
		mLHScol83 = vec_perm(mLHSaux31, mLHSaux32, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux33 = vec_xl(0, mLHS + 56);
		__vector double mLHSaux34 = vec_xl(0, mLHS + 68);
		mLHScol93 = vec_perm(mLHSaux33, mLHSaux34, GETCOL1);
		mLHScol103 = vec_perm(mLHSaux33, mLHSaux34, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux35 = vec_xl(0, mLHS + 58);
		__vector double mLHSaux36 = vec_xl(0, mLHS + 70);
		mLHScol113 = vec_perm(mLHSaux35, mLHSaux36, GETCOL1);
		mLHScol123 = vec_perm(mLHSaux35, mLHSaux36, GETCOL2);

		// pegando as linhas 7 e 8 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux37 = vec_xl(0, mLHS + 72);
		__vector double mLHSaux38 = vec_xl(0, mLHS + 84);
		mLHScol14 = vec_perm(mLHSaux37, mLHSaux38, GETCOL1);
		mLHScol24 = vec_perm(mLHSaux37, mLHSaux38, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux39 = vec_xl(0, mLHS + 74);
		__vector double mLHSaux40 = vec_xl(0, mLHS + 86);
		mLHScol34 = vec_perm(mLHSaux39, mLHSaux40, GETCOL1);
		mLHScol44 = vec_perm(mLHSaux39, mLHSaux40, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux41 = vec_xl(0, mLHS + 76);
		__vector double mLHSaux42 = vec_xl(0, mLHS + 88);
		mLHScol54 = vec_perm(mLHSaux41, mLHSaux42, GETCOL1);
		mLHScol64 = vec_perm(mLHSaux41, mLHSaux42, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux43 = vec_xl(0, mLHS + 78);
		__vector double mLHSaux44 = vec_xl(0, mLHS + 90);
		mLHScol74 = vec_perm(mLHSaux43, mLHSaux44, GETCOL1);
		mLHScol84 = vec_perm(mLHSaux43, mLHSaux44, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux45 = vec_xl(0, mLHS + 80);
		__vector double mLHSaux46 = vec_xl(0, mLHS + 92);
		mLHScol94 = vec_perm(mLHSaux45, mLHSaux46, GETCOL1);
		mLHScol104 = vec_perm(mLHSaux45, mLHSaux46, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux47 = vec_xl(0, mLHS + 82);
		__vector double mLHSaux48 = vec_xl(0, mLHS + 94);
		mLHScol114 = vec_perm(mLHSaux47, mLHSaux48, GETCOL1);
		mLHScol124 = vec_perm(mLHSaux47, mLHSaux48, GETCOL2);

		// pegando as linhas 9 e 10 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux49 = vec_xl(0, mLHS + 96);
		__vector double mLHSaux50 = vec_xl(0, mLHS + 108);
		mLHScol15 = vec_perm(mLHSaux49, mLHSaux50, GETCOL1);
		mLHScol25 = vec_perm(mLHSaux49, mLHSaux50, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux51 = vec_xl(0, mLHS + 98);
		__vector double mLHSaux52 = vec_xl(0, mLHS + 110);
		mLHScol35 = vec_perm(mLHSaux51, mLHSaux52, GETCOL1);
		mLHScol45 = vec_perm(mLHSaux51, mLHSaux52, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux53 = vec_xl(0, mLHS + 100);
		__vector double mLHSaux54 = vec_xl(0, mLHS + 112);
		mLHScol55 = vec_perm(mLHSaux53, mLHSaux54, GETCOL1);
		mLHScol65 = vec_perm(mLHSaux53, mLHSaux54, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux55 = vec_xl(0, mLHS + 102);
		__vector double mLHSaux56 = vec_xl(0, mLHS + 114);
		mLHScol75 = vec_perm(mLHSaux55, mLHSaux56, GETCOL1);
		mLHScol85 = vec_perm(mLHSaux55, mLHSaux56, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux57 = vec_xl(0, mLHS + 104);
		__vector double mLHSaux58 = vec_xl(0, mLHS + 116);
		mLHScol95 = vec_perm(mLHSaux57, mLHSaux58, GETCOL1);
		mLHScol105 = vec_perm(mLHSaux57, mLHSaux58, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux59 = vec_xl(0, mLHS + 106);
		__vector double mLHSaux60 = vec_xl(0, mLHS + 118);
		mLHScol115 = vec_perm(mLHSaux59, mLHSaux60, GETCOL1);
		mLHScol125 = vec_perm(mLHSaux59, mLHSaux60, GETCOL2);

		// pegando as linhas 11 e 12 de cada coluna
		// colunas 1 e 2
		__vector double mLHSaux61 = vec_xl(0, mLHS + 120);
		__vector double mLHSaux62 = vec_xl(0, mLHS + 132);
		mLHScol16 = vec_perm(mLHSaux61, mLHSaux62, GETCOL1);
		mLHScol26 = vec_perm(mLHSaux61, mLHSaux62, GETCOL2);

		// colunas 3 e 4
		__vector double mLHSaux63 = vec_xl(0, mLHS + 122);
		__vector double mLHSaux64 = vec_xl(0, mLHS + 134);
		mLHScol36 = vec_perm(mLHSaux63, mLHSaux64, GETCOL1);
		mLHScol46 = vec_perm(mLHSaux63, mLHSaux64, GETCOL2);

		// colunas 5 e 6
		__vector double mLHSaux65 = vec_xl(0, mLHS + 124);
		__vector double mLHSaux66 = vec_xl(0, mLHS + 136);
		mLHScol56 = vec_perm(mLHSaux65, mLHSaux66, GETCOL1);
		mLHScol66 = vec_perm(mLHSaux65, mLHSaux66, GETCOL2);

		// colunas 7 e 8
		__vector double mLHSaux67 = vec_xl(0, mLHS + 126);
		__vector double mLHSaux68 = vec_xl(0, mLHS + 138);
		mLHScol76 = vec_perm(mLHSaux67, mLHSaux68, GETCOL1);
		mLHScol86 = vec_perm(mLHSaux67, mLHSaux68, GETCOL2);

		// colunas 9 e 10
		__vector double mLHSaux69 = vec_xl(0, mLHS + 128);
		__vector double mLHSaux70 = vec_xl(0, mLHS + 140);
		mLHScol96 = vec_perm(mLHSaux69, mLHSaux70, GETCOL1);
		mLHScol106 = vec_perm(mLHSaux69, mLHSaux70, GETCOL2);

		// colunas 11 e 12
		__vector double mLHSaux71 = vec_xl(0, mLHS + 130);
		__vector double mLHSaux72 = vec_xl(0, mLHS + 142);
		mLHScol116 = vec_perm(mLHSaux71, mLHSaux72, GETCOL1);
		mLHScol126 = vec_perm(mLHSaux71, mLHSaux72, GETCOL2);
	} else {
		// coluna 1
		mLHScol11 = vec_xl(0, mLHS);
		mLHScol12 = vec_xl(0, mLHS + 2);
		mLHScol13 = vec_xl(0, mLHS + 4);
		mLHScol14 = vec_xl(0, mLHS + 6);
		mLHScol15 = vec_xl(0, mLHS + 8);
		mLHScol16 = vec_xl(0, mLHS + 10);

		// coluna 2
		mLHScol21 = vec_xl(0, mLHS + 12);
		mLHScol22 = vec_xl(0, mLHS + 14);
		mLHScol23 = vec_xl(0, mLHS + 16);
		mLHScol24 = vec_xl(0, mLHS + 18);
		mLHScol25 = vec_xl(0, mLHS + 20);
		mLHScol26 = vec_xl(0, mLHS + 22);

		// coluna 3
		mLHScol31 = vec_xl(0, mLHS + 24);
		mLHScol32 = vec_xl(0, mLHS + 26);
		mLHScol33 = vec_xl(0, mLHS + 28);
		mLHScol34 = vec_xl(0, mLHS + 30);
		mLHScol35 = vec_xl(0, mLHS + 32);
		mLHScol36 = vec_xl(0, mLHS + 34);

		// coluna 4
		mLHScol41 = vec_xl(0, mLHS + 36);
		mLHScol42 = vec_xl(0, mLHS + 38);
		mLHScol43 = vec_xl(0, mLHS + 40);
		mLHScol44 = vec_xl(0, mLHS + 42);
		mLHScol45 = vec_xl(0, mLHS + 44);
		mLHScol46 = vec_xl(0, mLHS + 46);

		// coluna 5
		mLHScol51 = vec_xl(0, mLHS + 48);
		mLHScol52 = vec_xl(0, mLHS + 50);
		mLHScol53 = vec_xl(0, mLHS + 52);
		mLHScol54 = vec_xl(0, mLHS + 54);
		mLHScol55 = vec_xl(0, mLHS + 56);
		mLHScol56 = vec_xl(0, mLHS + 58);

		// coluna 6
		mLHScol61 = vec_xl(0, mLHS + 60);
		mLHScol62 = vec_xl(0, mLHS + 62);
		mLHScol63 = vec_xl(0, mLHS + 64);
		mLHScol64 = vec_xl(0, mLHS + 66);
		mLHScol65 = vec_xl(0, mLHS + 68);
		mLHScol66 = vec_xl(0, mLHS + 70);

		// coluna 7
		mLHScol71 = vec_xl(0, mLHS + 72);
		mLHScol72 = vec_xl(0, mLHS + 74);
		mLHScol73 = vec_xl(0, mLHS + 76);
		mLHScol74 = vec_xl(0, mLHS + 78);
		mLHScol75 = vec_xl(0, mLHS + 80);
		mLHScol76 = vec_xl(0, mLHS + 82);

		// coluna 8
		mLHScol81 = vec_xl(0, mLHS + 84);
		mLHScol82 = vec_xl(0, mLHS + 86);
		mLHScol83 = vec_xl(0, mLHS + 88);
		mLHScol84 = vec_xl(0, mLHS + 90);
		mLHScol85 = vec_xl(0, mLHS + 92);
		mLHScol86 = vec_xl(0, mLHS + 94);

		// coluna 9
		mLHScol91 = vec_xl(0, mLHS + 96);
		mLHScol92 = vec_xl(0, mLHS + 98);
		mLHScol93 = vec_xl(0, mLHS + 100);
		mLHScol94 = vec_xl(0, mLHS + 102);
		mLHScol95 = vec_xl(0, mLHS + 104);
		mLHScol96 = vec_xl(0, mLHS + 106);

		// coluna 10
		mLHScol101 = vec_xl(0, mLHS + 108);
		mLHScol102 = vec_xl(0, mLHS + 110);
		mLHScol103 = vec_xl(0, mLHS + 112);
		mLHScol104 = vec_xl(0, mLHS + 114);
		mLHScol105 = vec_xl(0, mLHS + 116);
		mLHScol106 = vec_xl(0, mLHS + 118);

		// coluna 11
		mLHScol111 = vec_xl(0, mLHS + 120);
		mLHScol112 = vec_xl(0, mLHS + 122);
		mLHScol113 = vec_xl(0, mLHS + 124);
		mLHScol114 = vec_xl(0, mLHS + 126);
		mLHScol115 = vec_xl(0, mLHS + 128);
		mLHScol116 = vec_xl(0, mLHS + 130);

		// coluna 12
		mLHScol121 = vec_xl(0, mLHS + 132);
		mLHScol122 = vec_xl(0, mLHS + 134);
		mLHScol123 = vec_xl(0, mLHS + 136);
		mLHScol124 = vec_xl(0, mLHS + 138);
		mLHScol125 = vec_xl(0, mLHS + 140);
		mLHScol126 = vec_xl(0, mLHS + 142);
	}

	// coluna 1
	mRHSrow11 = vec_xl(0, mRHS);
	mRHSrow12 = vec_xl(0, mRHS + 2);
	mRHSrow13 = vec_xl(0, mRHS + 4);
	mRHSrow14 = vec_xl(0, mRHS + 6);
	mRHSrow15 = vec_xl(0, mRHS + 8);
	mRHSrow16 = vec_xl(0, mRHS + 10);

	// coluna 2
	mRHSrow21 = vec_xl(0, mRHS + 12);
	mRHSrow22 = vec_xl(0, mRHS + 14);
	mRHSrow23 = vec_xl(0, mRHS + 16);
	mRHSrow24 = vec_xl(0, mRHS + 18);
	mRHSrow25 = vec_xl(0, mRHS + 20);
	mRHSrow26 = vec_xl(0, mRHS + 22);

	// coluna 3
	mRHSrow31 = vec_xl(0, mRHS + 24);
	mRHSrow32 = vec_xl(0, mRHS + 26);
	mRHSrow33 = vec_xl(0, mRHS + 28);
	mRHSrow34 = vec_xl(0, mRHS + 30);
	mRHSrow35 = vec_xl(0, mRHS + 32);
	mRHSrow36 = vec_xl(0, mRHS + 34);

	// coluna 4
	mRHSrow41 = vec_xl(0, mRHS + 36);
	mRHSrow42 = vec_xl(0, mRHS + 38);
	mRHSrow43 = vec_xl(0, mRHS + 40);
	mRHSrow44 = vec_xl(0, mRHS + 42);
	mRHSrow45 = vec_xl(0, mRHS + 44);
	mRHSrow46 = vec_xl(0, mRHS + 46);

	// coluna 5
	mRHSrow51 = vec_xl(0, mRHS + 48);
	mRHSrow52 = vec_xl(0, mRHS + 50);
	mRHSrow53 = vec_xl(0, mRHS + 52);
	mRHSrow54 = vec_xl(0, mRHS + 54);
	mRHSrow55 = vec_xl(0, mRHS + 56);
	mRHSrow56 = vec_xl(0, mRHS + 58);

	// coluna 6
	mRHSrow61 = vec_xl(0, mRHS + 60);
	mRHSrow62 = vec_xl(0, mRHS + 62);
	mRHSrow63 = vec_xl(0, mRHS + 64);
	mRHSrow64 = vec_xl(0, mRHS + 66);
	mRHSrow65 = vec_xl(0, mRHS + 68);
	mRHSrow66 = vec_xl(0, mRHS + 70);

	// coluna 7
	mRHSrow71 = vec_xl(0, mRHS + 72);
	mRHSrow72 = vec_xl(0, mRHS + 74);
	mRHSrow73 = vec_xl(0, mRHS + 76);
	mRHSrow74 = vec_xl(0, mRHS + 78);
	mRHSrow75 = vec_xl(0, mRHS + 80);
	mRHSrow76 = vec_xl(0, mRHS + 82);

	// coluna 8
	mRHSrow81 = vec_xl(0, mRHS + 84);
	mRHSrow82 = vec_xl(0, mRHS + 86);
	mRHSrow83 = vec_xl(0, mRHS + 88);
	mRHSrow84 = vec_xl(0, mRHS + 90);
	mRHSrow85 = vec_xl(0, mRHS + 92);
	mRHSrow86 = vec_xl(0, mRHS + 94);

	// coluna 9
	mRHSrow91 = vec_xl(0, mRHS + 96);
	mRHSrow92 = vec_xl(0, mRHS + 98);
	mRHSrow93 = vec_xl(0, mRHS + 100);
	mRHSrow94 = vec_xl(0, mRHS + 102);
	mRHSrow95 = vec_xl(0, mRHS + 104);
	mRHSrow96 = vec_xl(0, mRHS + 106);

	// coluna 10
	mRHSrow101 = vec_xl(0, mRHS + 108);
	mRHSrow102 = vec_xl(0, mRHS + 110);
	mRHSrow103 = vec_xl(0, mRHS + 112);
	mRHSrow104 = vec_xl(0, mRHS + 114);
	mRHSrow105 = vec_xl(0, mRHS + 116);
	mRHSrow106 = vec_xl(0, mRHS + 118);

	// coluna 11
	mRHSrow111 = vec_xl(0, mRHS + 120);
	mRHSrow112 = vec_xl(0, mRHS + 122);
	mRHSrow113 = vec_xl(0, mRHS + 124);
	mRHSrow114 = vec_xl(0, mRHS + 126);
	mRHSrow115 = vec_xl(0, mRHS + 128);
	mRHSrow116 = vec_xl(0, mRHS + 130);

	// coluna 12
	mRHSrow121 = vec_xl(0, mRHS + 132);
	mRHSrow122 = vec_xl(0, mRHS + 134);
	mRHSrow123 = vec_xl(0, mRHS + 136);
	mRHSrow124 = vec_xl(0, mRHS + 138);
	mRHSrow125 = vec_xl(0, mRHS + 140);
	mRHSrow126 = vec_xl(0, mRHS + 142);

	// column 1
	__vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
	__vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
	__vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
	__vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};
	__vector double vAuxLHS15 = {mLHScol13[0], mLHScol13[0]};
	__vector double vAuxLHS16 = {mLHScol13[1], mLHScol13[1]};
	__vector double vAuxLHS17 = {mLHScol14[0], mLHScol14[0]};
	__vector double vAuxLHS18 = {mLHScol14[1], mLHScol14[1]};
	__vector double vAuxLHS19 = {mLHScol15[0], mLHScol15[0]};
	__vector double vAuxLHS110 = {mLHScol15[1], mLHScol15[1]};
	__vector double vAuxLHS0111 = {mLHScol16[0], mLHScol16[0]};
	__vector double vAuxLHS0112 = {mLHScol16[1], mLHScol16[1]};

	// column 2
	__vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
	__vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
	__vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
	__vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};
	__vector double vAuxLHS25 = {mLHScol23[0], mLHScol23[0]};
	__vector double vAuxLHS26 = {mLHScol23[1], mLHScol23[1]};
	__vector double vAuxLHS27 = {mLHScol24[0], mLHScol24[0]};
	__vector double vAuxLHS28 = {mLHScol24[1], mLHScol24[1]};
	__vector double vAuxLHS29 = {mLHScol25[0], mLHScol25[0]};
	__vector double vAuxLHS210 = {mLHScol25[1], mLHScol25[1]};
	__vector double vAuxLHS211 = {mLHScol26[0], mLHScol26[0]};
	__vector double vAuxLHS212 = {mLHScol26[1], mLHScol26[1]};

	// column 3
	__vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
	__vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
	__vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
	__vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};
	__vector double vAuxLHS35 = {mLHScol33[0], mLHScol33[0]};
	__vector double vAuxLHS36 = {mLHScol33[1], mLHScol33[1]};
	__vector double vAuxLHS37 = {mLHScol34[0], mLHScol34[0]};
	__vector double vAuxLHS38 = {mLHScol34[1], mLHScol34[1]};
	__vector double vAuxLHS39 = {mLHScol35[0], mLHScol35[0]};
	__vector double vAuxLHS310 = {mLHScol35[1], mLHScol35[1]};
	__vector double vAuxLHS311 = {mLHScol36[0], mLHScol36[0]};
	__vector double vAuxLHS312 = {mLHScol36[1], mLHScol36[1]};

	// column 4
	__vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
	__vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
	__vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
	__vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
	__vector double vAuxLHS45 = {mLHScol43[0], mLHScol43[0]};
	__vector double vAuxLHS46 = {mLHScol43[1], mLHScol43[1]};
	__vector double vAuxLHS47 = {mLHScol44[0], mLHScol44[0]};
	__vector double vAuxLHS48 = {mLHScol44[1], mLHScol44[1]};
	__vector double vAuxLHS49 = {mLHScol45[0], mLHScol45[0]};
	__vector double vAuxLHS410 = {mLHScol45[1], mLHScol45[1]};
	__vector double vAuxLHS411 = {mLHScol46[0], mLHScol46[0]};
	__vector double vAuxLHS412 = {mLHScol46[1], mLHScol46[1]};

	// column 5
	__vector double vAuxLHS51 = {mLHScol51[0], mLHScol51[0]};
	__vector double vAuxLHS52 = {mLHScol51[1], mLHScol51[1]};
	__vector double vAuxLHS53 = {mLHScol52[0], mLHScol52[0]};
	__vector double vAuxLHS54 = {mLHScol52[1], mLHScol52[1]};
	__vector double vAuxLHS55 = {mLHScol53[0], mLHScol53[0]};
	__vector double vAuxLHS56 = {mLHScol53[1], mLHScol53[1]};
	__vector double vAuxLHS57 = {mLHScol54[0], mLHScol54[0]};
	__vector double vAuxLHS58 = {mLHScol54[1], mLHScol54[1]};
	__vector double vAuxLHS59 = {mLHScol55[0], mLHScol55[0]};
	__vector double vAuxLHS510 = {mLHScol55[1], mLHScol55[1]};
	__vector double vAuxLHS511 = {mLHScol56[0], mLHScol56[0]};
	__vector double vAuxLHS512 = {mLHScol56[1], mLHScol56[1]};

	// column 6
	__vector double vAuxLHS61 = {mLHScol61[0], mLHScol61[0]};
	__vector double vAuxLHS62 = {mLHScol61[1], mLHScol61[1]};
	__vector double vAuxLHS63 = {mLHScol62[0], mLHScol62[0]};
	__vector double vAuxLHS64 = {mLHScol62[1], mLHScol62[1]};
	__vector double vAuxLHS65 = {mLHScol63[0], mLHScol63[0]};
	__vector double vAuxLHS66 = {mLHScol63[1], mLHScol63[1]};
	__vector double vAuxLHS67 = {mLHScol64[0], mLHScol64[0]};
	__vector double vAuxLHS68 = {mLHScol64[1], mLHScol64[1]};
	__vector double vAuxLHS69 = {mLHScol65[0], mLHScol65[0]};
	__vector double vAuxLHS610 = {mLHScol65[1], mLHScol65[1]};
	__vector double vAuxLHS611 = {mLHScol66[0], mLHScol66[0]};
	__vector double vAuxLHS612 = {mLHScol66[1], mLHScol66[1]};

	// column 7
	__vector double vAuxLHS71 = {mLHScol71[0], mLHScol71[0]};
	__vector double vAuxLHS72 = {mLHScol71[1], mLHScol71[1]};
	__vector double vAuxLHS73 = {mLHScol72[0], mLHScol72[0]};
	__vector double vAuxLHS74 = {mLHScol72[1], mLHScol72[1]};
	__vector double vAuxLHS75 = {mLHScol73[0], mLHScol73[0]};
	__vector double vAuxLHS76 = {mLHScol73[1], mLHScol73[1]};
	__vector double vAuxLHS77 = {mLHScol74[0], mLHScol74[0]};
	__vector double vAuxLHS78 = {mLHScol74[1], mLHScol74[1]};
	__vector double vAuxLHS79 = {mLHScol75[0], mLHScol75[0]};
	__vector double vAuxLHS710 = {mLHScol75[1], mLHScol75[1]};
	__vector double vAuxLHS711 = {mLHScol76[0], mLHScol76[0]};
	__vector double vAuxLHS712 = {mLHScol76[1], mLHScol76[1]};

	// column 8
	__vector double vAuxLHS81 = {mLHScol81[0], mLHScol81[0]};
	__vector double vAuxLHS82 = {mLHScol81[1], mLHScol81[1]};
	__vector double vAuxLHS83 = {mLHScol82[0], mLHScol82[0]};
	__vector double vAuxLHS84 = {mLHScol82[1], mLHScol82[1]};
	__vector double vAuxLHS85 = {mLHScol83[0], mLHScol83[0]};
	__vector double vAuxLHS86 = {mLHScol83[1], mLHScol83[1]};
	__vector double vAuxLHS87 = {mLHScol84[0], mLHScol84[0]};
	__vector double vAuxLHS88 = {mLHScol84[1], mLHScol84[1]};
	__vector double vAuxLHS89 = {mLHScol85[0], mLHScol85[0]};
	__vector double vAuxLHS810 = {mLHScol85[1], mLHScol85[1]};
	__vector double vAuxLHS811 = {mLHScol86[0], mLHScol86[0]};
	__vector double vAuxLHS812 = {mLHScol86[1], mLHScol86[1]};

	// column 9
	__vector double vAuxLHS91 = {mLHScol91[0], mLHScol91[0]};
	__vector double vAuxLHS92 = {mLHScol91[1], mLHScol91[1]};
	__vector double vAuxLHS93 = {mLHScol92[0], mLHScol92[0]};
	__vector double vAuxLHS94 = {mLHScol92[1], mLHScol92[1]};
	__vector double vAuxLHS95 = {mLHScol93[0], mLHScol93[0]};
	__vector double vAuxLHS96 = {mLHScol93[1], mLHScol93[1]};
	__vector double vAuxLHS97 = {mLHScol94[0], mLHScol94[0]};
	__vector double vAuxLHS98 = {mLHScol94[1], mLHScol94[1]};
	__vector double vAuxLHS99 = {mLHScol95[0], mLHScol95[0]};
	__vector double vAuxLHS910 = {mLHScol95[1], mLHScol95[1]};
	__vector double vAuxLHS911 = {mLHScol96[0], mLHScol96[0]};
	__vector double vAuxLHS912 = {mLHScol96[1], mLHScol96[1]};

	// column 10
	__vector double vAuxLHS101 = {mLHScol101[0], mLHScol101[0]};
	__vector double vAuxLHS102 = {mLHScol101[1], mLHScol101[1]};
	__vector double vAuxLHS103 = {mLHScol102[0], mLHScol102[0]};
	__vector double vAuxLHS104 = {mLHScol102[1], mLHScol102[1]};
	__vector double vAuxLHS105 = {mLHScol103[0], mLHScol103[0]};
	__vector double vAuxLHS106 = {mLHScol103[1], mLHScol103[1]};
	__vector double vAuxLHS107 = {mLHScol104[0], mLHScol104[0]};
	__vector double vAuxLHS108 = {mLHScol104[1], mLHScol104[1]};
	__vector double vAuxLHS109 = {mLHScol105[0], mLHScol105[0]};
	__vector double vAuxLHS1010 = {mLHScol105[1], mLHScol105[1]};
	__vector double vAuxLHS1011 = {mLHScol106[0], mLHScol106[0]};
	__vector double vAuxLHS1012 = {mLHScol106[1], mLHScol106[1]};

	// column 11
	__vector double vAuxLHS111 = {mLHScol111[0], mLHScol111[0]};
	__vector double vAuxLHS112 = {mLHScol111[1], mLHScol111[1]};
	__vector double vAuxLHS113 = {mLHScol112[0], mLHScol112[0]};
	__vector double vAuxLHS114 = {mLHScol112[1], mLHScol112[1]};
	__vector double vAuxLHS115 = {mLHScol113[0], mLHScol113[0]};
	__vector double vAuxLHS116 = {mLHScol113[1], mLHScol113[1]};
	__vector double vAuxLHS117 = {mLHScol114[0], mLHScol114[0]};
	__vector double vAuxLHS118 = {mLHScol114[1], mLHScol114[1]};
	__vector double vAuxLHS119 = {mLHScol115[0], mLHScol115[0]};
	__vector double vAuxLHS1110 = {mLHScol115[1], mLHScol115[1]};
	__vector double vAuxLHS1111 = {mLHScol116[0], mLHScol116[0]};
	__vector double vAuxLHS1112 = {mLHScol116[1], mLHScol116[1]};

	// column 12
	__vector double vAuxLHS121 = {mLHScol121[0], mLHScol121[0]};
	__vector double vAuxLHS122 = {mLHScol121[1], mLHScol121[1]};
	__vector double vAuxLHS123 = {mLHScol122[0], mLHScol122[0]};
	__vector double vAuxLHS124 = {mLHScol122[1], mLHScol122[1]};
	__vector double vAuxLHS125 = {mLHScol123[0], mLHScol123[0]};
	__vector double vAuxLHS126 = {mLHScol123[1], mLHScol123[1]};
	__vector double vAuxLHS127 = {mLHScol124[0], mLHScol124[0]};
	__vector double vAuxLHS128 = {mLHScol124[1], mLHScol124[1]};
	__vector double vAuxLHS129 = {mLHScol125[0], mLHScol125[0]};
	__vector double vAuxLHS1210 = {mLHScol125[1], mLHScol125[1]};
	__vector double vAuxLHS1211 = {mLHScol126[0], mLHScol126[0]};
	__vector double vAuxLHS1212 = {mLHScol126[1], mLHScol126[1]};

	double* mResult;
	mResult = new double[144];
	
	// row 1 of mResult
	vec_xst(vec_madd(vAuxLHS121, mRHSrow121, vec_madd(vAuxLHS111, mRHSrow111, vec_madd(vAuxLHS101, mRHSrow101, vec_madd(vAuxLHS91, mRHSrow91, vec_madd(vAuxLHS81, mRHSrow81, vec_madd(vAuxLHS71, mRHSrow71, vec_madd(vAuxLHS61, mRHSrow61, vec_madd(vAuxLHS51, mRHSrow51, vec_madd(vAuxLHS41, mRHSrow41, vec_madd(vAuxLHS31, mRHSrow31, vec_madd(vAuxLHS21, mRHSrow21, vec_mul(vAuxLHS11, mRHSrow11)))))))))))), 0, mResult);
	vec_xst(vec_madd(vAuxLHS121, mRHSrow122, vec_madd(vAuxLHS111, mRHSrow112, vec_madd(vAuxLHS101, mRHSrow102, vec_madd(vAuxLHS91, mRHSrow92, vec_madd(vAuxLHS81, mRHSrow82, vec_madd(vAuxLHS71, mRHSrow72, vec_madd(vAuxLHS61, mRHSrow62, vec_madd(vAuxLHS51, mRHSrow52, vec_madd(vAuxLHS41, mRHSrow42, vec_madd(vAuxLHS31, mRHSrow32, vec_madd(vAuxLHS21, mRHSrow22, vec_mul(vAuxLHS11, mRHSrow12)))))))))))), 0, mResult + 2);
	vec_xst(vec_madd(vAuxLHS121, mRHSrow123, vec_madd(vAuxLHS111, mRHSrow113, vec_madd(vAuxLHS101, mRHSrow103, vec_madd(vAuxLHS91, mRHSrow93, vec_madd(vAuxLHS81, mRHSrow83, vec_madd(vAuxLHS71, mRHSrow73, vec_madd(vAuxLHS61, mRHSrow63, vec_madd(vAuxLHS51, mRHSrow53, vec_madd(vAuxLHS41, mRHSrow43, vec_madd(vAuxLHS31, mRHSrow33, vec_madd(vAuxLHS21, mRHSrow23, vec_mul(vAuxLHS11, mRHSrow13)))))))))))), 0, mResult + 4);
	vec_xst(vec_madd(vAuxLHS121, mRHSrow124, vec_madd(vAuxLHS111, mRHSrow114, vec_madd(vAuxLHS101, mRHSrow104, vec_madd(vAuxLHS91, mRHSrow94, vec_madd(vAuxLHS81, mRHSrow84, vec_madd(vAuxLHS71, mRHSrow74, vec_madd(vAuxLHS61, mRHSrow64, vec_madd(vAuxLHS51, mRHSrow54, vec_madd(vAuxLHS41, mRHSrow44, vec_madd(vAuxLHS31, mRHSrow34, vec_madd(vAuxLHS21, mRHSrow24, vec_mul(vAuxLHS11, mRHSrow14)))))))))))), 0, mResult + 6);
	vec_xst(vec_madd(vAuxLHS121, mRHSrow125, vec_madd(vAuxLHS111, mRHSrow115, vec_madd(vAuxLHS101, mRHSrow105, vec_madd(vAuxLHS91, mRHSrow95, vec_madd(vAuxLHS81, mRHSrow85, vec_madd(vAuxLHS71, mRHSrow75, vec_madd(vAuxLHS61, mRHSrow65, vec_madd(vAuxLHS51, mRHSrow55, vec_madd(vAuxLHS41, mRHSrow45, vec_madd(vAuxLHS31, mRHSrow35, vec_madd(vAuxLHS21, mRHSrow25, vec_mul(vAuxLHS11, mRHSrow15)))))))))))), 0, mResult + 8);
	vec_xst(vec_madd(vAuxLHS121, mRHSrow126, vec_madd(vAuxLHS111, mRHSrow116, vec_madd(vAuxLHS101, mRHSrow106, vec_madd(vAuxLHS91, mRHSrow96, vec_madd(vAuxLHS81, mRHSrow86, vec_madd(vAuxLHS71, mRHSrow76, vec_madd(vAuxLHS61, mRHSrow66, vec_madd(vAuxLHS51, mRHSrow56, vec_madd(vAuxLHS41, mRHSrow46, vec_madd(vAuxLHS31, mRHSrow36, vec_madd(vAuxLHS21, mRHSrow26, vec_mul(vAuxLHS11, mRHSrow16)))))))))))), 0, mResult + 10);

	// row 2 of mResult
	vec_xst(vec_madd(vAuxLHS122, mRHSrow121, vec_madd(vAuxLHS112, mRHSrow111, vec_madd(vAuxLHS102, mRHSrow101, vec_madd(vAuxLHS92, mRHSrow91, vec_madd(vAuxLHS82, mRHSrow81, vec_madd(vAuxLHS72, mRHSrow71, vec_madd(vAuxLHS62, mRHSrow61, vec_madd(vAuxLHS52, mRHSrow51, vec_madd(vAuxLHS42, mRHSrow41, vec_madd(vAuxLHS32, mRHSrow31, vec_madd(vAuxLHS22, mRHSrow21, vec_mul(vAuxLHS12, mRHSrow11)))))))))))), 0, mResult + 12);
	vec_xst(vec_madd(vAuxLHS122, mRHSrow122, vec_madd(vAuxLHS112, mRHSrow112, vec_madd(vAuxLHS102, mRHSrow102, vec_madd(vAuxLHS92, mRHSrow92, vec_madd(vAuxLHS82, mRHSrow82, vec_madd(vAuxLHS72, mRHSrow72, vec_madd(vAuxLHS62, mRHSrow62, vec_madd(vAuxLHS52, mRHSrow52, vec_madd(vAuxLHS42, mRHSrow42, vec_madd(vAuxLHS32, mRHSrow32, vec_madd(vAuxLHS22, mRHSrow22, vec_mul(vAuxLHS12, mRHSrow12)))))))))))), 0, mResult + 14);
	vec_xst(vec_madd(vAuxLHS122, mRHSrow123, vec_madd(vAuxLHS112, mRHSrow113, vec_madd(vAuxLHS102, mRHSrow103, vec_madd(vAuxLHS92, mRHSrow93, vec_madd(vAuxLHS82, mRHSrow83, vec_madd(vAuxLHS72, mRHSrow73, vec_madd(vAuxLHS62, mRHSrow63, vec_madd(vAuxLHS52, mRHSrow53, vec_madd(vAuxLHS42, mRHSrow43, vec_madd(vAuxLHS32, mRHSrow33, vec_madd(vAuxLHS22, mRHSrow23, vec_mul(vAuxLHS12, mRHSrow13)))))))))))), 0, mResult + 16);
	vec_xst(vec_madd(vAuxLHS122, mRHSrow124, vec_madd(vAuxLHS112, mRHSrow114, vec_madd(vAuxLHS102, mRHSrow104, vec_madd(vAuxLHS92, mRHSrow94, vec_madd(vAuxLHS82, mRHSrow84, vec_madd(vAuxLHS72, mRHSrow74, vec_madd(vAuxLHS62, mRHSrow64, vec_madd(vAuxLHS52, mRHSrow54, vec_madd(vAuxLHS42, mRHSrow44, vec_madd(vAuxLHS32, mRHSrow34, vec_madd(vAuxLHS22, mRHSrow24, vec_mul(vAuxLHS12, mRHSrow14)))))))))))), 0, mResult + 18);
	vec_xst(vec_madd(vAuxLHS122, mRHSrow125, vec_madd(vAuxLHS112, mRHSrow115, vec_madd(vAuxLHS102, mRHSrow105, vec_madd(vAuxLHS92, mRHSrow95, vec_madd(vAuxLHS82, mRHSrow85, vec_madd(vAuxLHS72, mRHSrow75, vec_madd(vAuxLHS62, mRHSrow65, vec_madd(vAuxLHS52, mRHSrow55, vec_madd(vAuxLHS42, mRHSrow45, vec_madd(vAuxLHS32, mRHSrow35, vec_madd(vAuxLHS22, mRHSrow25, vec_mul(vAuxLHS12, mRHSrow15)))))))))))), 0, mResult + 20);
	vec_xst(vec_madd(vAuxLHS122, mRHSrow126, vec_madd(vAuxLHS112, mRHSrow116, vec_madd(vAuxLHS102, mRHSrow106, vec_madd(vAuxLHS92, mRHSrow96, vec_madd(vAuxLHS82, mRHSrow86, vec_madd(vAuxLHS72, mRHSrow76, vec_madd(vAuxLHS62, mRHSrow66, vec_madd(vAuxLHS52, mRHSrow56, vec_madd(vAuxLHS42, mRHSrow46, vec_madd(vAuxLHS32, mRHSrow36, vec_madd(vAuxLHS22, mRHSrow26, vec_mul(vAuxLHS12, mRHSrow16)))))))))))), 0, mResult + 22);

	// row 3 of mResult
	vec_xst(vec_madd(vAuxLHS123, mRHSrow121, vec_madd(vAuxLHS113, mRHSrow111, vec_madd(vAuxLHS103, mRHSrow101, vec_madd(vAuxLHS93, mRHSrow91, vec_madd(vAuxLHS83, mRHSrow81, vec_madd(vAuxLHS73, mRHSrow71, vec_madd(vAuxLHS63, mRHSrow61, vec_madd(vAuxLHS53, mRHSrow51, vec_madd(vAuxLHS43, mRHSrow41, vec_madd(vAuxLHS33, mRHSrow31, vec_madd(vAuxLHS23, mRHSrow21, vec_mul(vAuxLHS13, mRHSrow11)))))))))))), 0, mResult + 24);
	vec_xst(vec_madd(vAuxLHS123, mRHSrow122, vec_madd(vAuxLHS113, mRHSrow112, vec_madd(vAuxLHS103, mRHSrow102, vec_madd(vAuxLHS93, mRHSrow92, vec_madd(vAuxLHS83, mRHSrow82, vec_madd(vAuxLHS73, mRHSrow72, vec_madd(vAuxLHS63, mRHSrow62, vec_madd(vAuxLHS53, mRHSrow52, vec_madd(vAuxLHS43, mRHSrow42, vec_madd(vAuxLHS33, mRHSrow32, vec_madd(vAuxLHS23, mRHSrow22, vec_mul(vAuxLHS13, mRHSrow12)))))))))))), 0, mResult + 26);
	vec_xst(vec_madd(vAuxLHS123, mRHSrow123, vec_madd(vAuxLHS113, mRHSrow113, vec_madd(vAuxLHS103, mRHSrow103, vec_madd(vAuxLHS93, mRHSrow93, vec_madd(vAuxLHS83, mRHSrow83, vec_madd(vAuxLHS73, mRHSrow73, vec_madd(vAuxLHS63, mRHSrow63, vec_madd(vAuxLHS53, mRHSrow53, vec_madd(vAuxLHS43, mRHSrow43, vec_madd(vAuxLHS33, mRHSrow33, vec_madd(vAuxLHS23, mRHSrow23, vec_mul(vAuxLHS13, mRHSrow13)))))))))))), 0, mResult + 28);
	vec_xst(vec_madd(vAuxLHS123, mRHSrow124, vec_madd(vAuxLHS113, mRHSrow114, vec_madd(vAuxLHS103, mRHSrow104, vec_madd(vAuxLHS93, mRHSrow94, vec_madd(vAuxLHS83, mRHSrow84, vec_madd(vAuxLHS73, mRHSrow74, vec_madd(vAuxLHS63, mRHSrow64, vec_madd(vAuxLHS53, mRHSrow54, vec_madd(vAuxLHS43, mRHSrow44, vec_madd(vAuxLHS33, mRHSrow34, vec_madd(vAuxLHS23, mRHSrow24, vec_mul(vAuxLHS13, mRHSrow14)))))))))))), 0, mResult + 30);
	vec_xst(vec_madd(vAuxLHS123, mRHSrow125, vec_madd(vAuxLHS113, mRHSrow115, vec_madd(vAuxLHS103, mRHSrow105, vec_madd(vAuxLHS93, mRHSrow95, vec_madd(vAuxLHS83, mRHSrow85, vec_madd(vAuxLHS73, mRHSrow75, vec_madd(vAuxLHS63, mRHSrow65, vec_madd(vAuxLHS53, mRHSrow55, vec_madd(vAuxLHS43, mRHSrow45, vec_madd(vAuxLHS33, mRHSrow35, vec_madd(vAuxLHS23, mRHSrow25, vec_mul(vAuxLHS13, mRHSrow15)))))))))))), 0, mResult + 32);
	vec_xst(vec_madd(vAuxLHS123, mRHSrow126, vec_madd(vAuxLHS113, mRHSrow116, vec_madd(vAuxLHS103, mRHSrow106, vec_madd(vAuxLHS93, mRHSrow96, vec_madd(vAuxLHS83, mRHSrow86, vec_madd(vAuxLHS73, mRHSrow76, vec_madd(vAuxLHS63, mRHSrow66, vec_madd(vAuxLHS53, mRHSrow56, vec_madd(vAuxLHS43, mRHSrow46, vec_madd(vAuxLHS33, mRHSrow36, vec_madd(vAuxLHS23, mRHSrow26, vec_mul(vAuxLHS13, mRHSrow16)))))))))))), 0, mResult + 34);

	// row 4 of mResult
	vec_xst(vec_madd(vAuxLHS124, mRHSrow121, vec_madd(vAuxLHS114, mRHSrow111, vec_madd(vAuxLHS104, mRHSrow101, vec_madd(vAuxLHS94, mRHSrow91, vec_madd(vAuxLHS84, mRHSrow81, vec_madd(vAuxLHS74, mRHSrow71, vec_madd(vAuxLHS64, mRHSrow61, vec_madd(vAuxLHS54, mRHSrow51, vec_madd(vAuxLHS44, mRHSrow41, vec_madd(vAuxLHS34, mRHSrow31, vec_madd(vAuxLHS24, mRHSrow21, vec_mul(vAuxLHS14, mRHSrow11)))))))))))), 0, mResult + 36);
	vec_xst(vec_madd(vAuxLHS124, mRHSrow122, vec_madd(vAuxLHS114, mRHSrow112, vec_madd(vAuxLHS104, mRHSrow102, vec_madd(vAuxLHS94, mRHSrow92, vec_madd(vAuxLHS84, mRHSrow82, vec_madd(vAuxLHS74, mRHSrow72, vec_madd(vAuxLHS64, mRHSrow62, vec_madd(vAuxLHS54, mRHSrow52, vec_madd(vAuxLHS44, mRHSrow42, vec_madd(vAuxLHS34, mRHSrow32, vec_madd(vAuxLHS24, mRHSrow22, vec_mul(vAuxLHS14, mRHSrow12)))))))))))), 0, mResult + 38);
	vec_xst(vec_madd(vAuxLHS124, mRHSrow123, vec_madd(vAuxLHS114, mRHSrow113, vec_madd(vAuxLHS104, mRHSrow103, vec_madd(vAuxLHS94, mRHSrow93, vec_madd(vAuxLHS84, mRHSrow83, vec_madd(vAuxLHS74, mRHSrow73, vec_madd(vAuxLHS64, mRHSrow63, vec_madd(vAuxLHS54, mRHSrow53, vec_madd(vAuxLHS44, mRHSrow43, vec_madd(vAuxLHS34, mRHSrow33, vec_madd(vAuxLHS24, mRHSrow23, vec_mul(vAuxLHS14, mRHSrow13)))))))))))), 0, mResult + 40);
	vec_xst(vec_madd(vAuxLHS124, mRHSrow124, vec_madd(vAuxLHS114, mRHSrow114, vec_madd(vAuxLHS104, mRHSrow104, vec_madd(vAuxLHS94, mRHSrow94, vec_madd(vAuxLHS84, mRHSrow84, vec_madd(vAuxLHS74, mRHSrow74, vec_madd(vAuxLHS64, mRHSrow64, vec_madd(vAuxLHS54, mRHSrow54, vec_madd(vAuxLHS44, mRHSrow44, vec_madd(vAuxLHS34, mRHSrow34, vec_madd(vAuxLHS24, mRHSrow24, vec_mul(vAuxLHS14, mRHSrow14)))))))))))), 0, mResult + 42);
	vec_xst(vec_madd(vAuxLHS124, mRHSrow125, vec_madd(vAuxLHS114, mRHSrow115, vec_madd(vAuxLHS104, mRHSrow105, vec_madd(vAuxLHS94, mRHSrow95, vec_madd(vAuxLHS84, mRHSrow85, vec_madd(vAuxLHS74, mRHSrow75, vec_madd(vAuxLHS64, mRHSrow65, vec_madd(vAuxLHS54, mRHSrow55, vec_madd(vAuxLHS44, mRHSrow45, vec_madd(vAuxLHS34, mRHSrow35, vec_madd(vAuxLHS24, mRHSrow25, vec_mul(vAuxLHS14, mRHSrow15)))))))))))), 0, mResult + 44);
	vec_xst(vec_madd(vAuxLHS124, mRHSrow126, vec_madd(vAuxLHS114, mRHSrow116, vec_madd(vAuxLHS104, mRHSrow106, vec_madd(vAuxLHS94, mRHSrow96, vec_madd(vAuxLHS84, mRHSrow86, vec_madd(vAuxLHS74, mRHSrow76, vec_madd(vAuxLHS64, mRHSrow66, vec_madd(vAuxLHS54, mRHSrow56, vec_madd(vAuxLHS44, mRHSrow46, vec_madd(vAuxLHS34, mRHSrow36, vec_madd(vAuxLHS24, mRHSrow26, vec_mul(vAuxLHS14, mRHSrow16)))))))))))), 0, mResult + 46);

	// row 5 of mResult
	vec_xst(vec_madd(vAuxLHS125, mRHSrow121, vec_madd(vAuxLHS115, mRHSrow111, vec_madd(vAuxLHS105, mRHSrow101, vec_madd(vAuxLHS95, mRHSrow91, vec_madd(vAuxLHS85, mRHSrow81, vec_madd(vAuxLHS75, mRHSrow71, vec_madd(vAuxLHS65, mRHSrow61, vec_madd(vAuxLHS55, mRHSrow51, vec_madd(vAuxLHS45, mRHSrow41, vec_madd(vAuxLHS35, mRHSrow31, vec_madd(vAuxLHS25, mRHSrow21, vec_mul(vAuxLHS15, mRHSrow11)))))))))))), 0, mResult + 48);
	vec_xst(vec_madd(vAuxLHS125, mRHSrow122, vec_madd(vAuxLHS115, mRHSrow112, vec_madd(vAuxLHS105, mRHSrow102, vec_madd(vAuxLHS95, mRHSrow92, vec_madd(vAuxLHS85, mRHSrow82, vec_madd(vAuxLHS75, mRHSrow72, vec_madd(vAuxLHS65, mRHSrow62, vec_madd(vAuxLHS55, mRHSrow52, vec_madd(vAuxLHS45, mRHSrow42, vec_madd(vAuxLHS35, mRHSrow32, vec_madd(vAuxLHS25, mRHSrow22, vec_mul(vAuxLHS15, mRHSrow12)))))))))))), 0, mResult + 50);
	vec_xst(vec_madd(vAuxLHS125, mRHSrow123, vec_madd(vAuxLHS115, mRHSrow113, vec_madd(vAuxLHS105, mRHSrow103, vec_madd(vAuxLHS95, mRHSrow93, vec_madd(vAuxLHS85, mRHSrow83, vec_madd(vAuxLHS75, mRHSrow73, vec_madd(vAuxLHS65, mRHSrow63, vec_madd(vAuxLHS55, mRHSrow53, vec_madd(vAuxLHS45, mRHSrow43, vec_madd(vAuxLHS35, mRHSrow33, vec_madd(vAuxLHS25, mRHSrow23, vec_mul(vAuxLHS15, mRHSrow13)))))))))))), 0, mResult + 52);
	vec_xst(vec_madd(vAuxLHS125, mRHSrow124, vec_madd(vAuxLHS115, mRHSrow114, vec_madd(vAuxLHS105, mRHSrow104, vec_madd(vAuxLHS95, mRHSrow94, vec_madd(vAuxLHS85, mRHSrow84, vec_madd(vAuxLHS75, mRHSrow74, vec_madd(vAuxLHS65, mRHSrow64, vec_madd(vAuxLHS55, mRHSrow54, vec_madd(vAuxLHS45, mRHSrow44, vec_madd(vAuxLHS35, mRHSrow34, vec_madd(vAuxLHS25, mRHSrow24, vec_mul(vAuxLHS15, mRHSrow14)))))))))))), 0, mResult + 54);
	vec_xst(vec_madd(vAuxLHS125, mRHSrow125, vec_madd(vAuxLHS115, mRHSrow115, vec_madd(vAuxLHS105, mRHSrow105, vec_madd(vAuxLHS95, mRHSrow95, vec_madd(vAuxLHS85, mRHSrow85, vec_madd(vAuxLHS75, mRHSrow75, vec_madd(vAuxLHS65, mRHSrow65, vec_madd(vAuxLHS55, mRHSrow55, vec_madd(vAuxLHS45, mRHSrow45, vec_madd(vAuxLHS35, mRHSrow35, vec_madd(vAuxLHS25, mRHSrow25, vec_mul(vAuxLHS15, mRHSrow15)))))))))))), 0, mResult + 56);
	vec_xst(vec_madd(vAuxLHS125, mRHSrow126, vec_madd(vAuxLHS115, mRHSrow116, vec_madd(vAuxLHS105, mRHSrow106, vec_madd(vAuxLHS95, mRHSrow96, vec_madd(vAuxLHS85, mRHSrow86, vec_madd(vAuxLHS75, mRHSrow76, vec_madd(vAuxLHS65, mRHSrow66, vec_madd(vAuxLHS55, mRHSrow56, vec_madd(vAuxLHS45, mRHSrow46, vec_madd(vAuxLHS35, mRHSrow36, vec_madd(vAuxLHS25, mRHSrow26, vec_mul(vAuxLHS15, mRHSrow16)))))))))))), 0, mResult + 58);

	// row 6 of mResult
	vec_xst(vec_madd(vAuxLHS126, mRHSrow121, vec_madd(vAuxLHS116, mRHSrow111, vec_madd(vAuxLHS106, mRHSrow101, vec_madd(vAuxLHS96, mRHSrow91, vec_madd(vAuxLHS86, mRHSrow81, vec_madd(vAuxLHS76, mRHSrow71, vec_madd(vAuxLHS66, mRHSrow61, vec_madd(vAuxLHS56, mRHSrow51, vec_madd(vAuxLHS46, mRHSrow41, vec_madd(vAuxLHS36, mRHSrow31, vec_madd(vAuxLHS26, mRHSrow21, vec_mul(vAuxLHS16, mRHSrow11)))))))))))), 0, mResult + 60);
	vec_xst(vec_madd(vAuxLHS126, mRHSrow122, vec_madd(vAuxLHS116, mRHSrow112, vec_madd(vAuxLHS106, mRHSrow102, vec_madd(vAuxLHS96, mRHSrow92, vec_madd(vAuxLHS86, mRHSrow82, vec_madd(vAuxLHS76, mRHSrow72, vec_madd(vAuxLHS66, mRHSrow62, vec_madd(vAuxLHS56, mRHSrow52, vec_madd(vAuxLHS46, mRHSrow42, vec_madd(vAuxLHS36, mRHSrow32, vec_madd(vAuxLHS26, mRHSrow22, vec_mul(vAuxLHS16, mRHSrow12)))))))))))), 0, mResult + 62);
	vec_xst(vec_madd(vAuxLHS126, mRHSrow123, vec_madd(vAuxLHS116, mRHSrow113, vec_madd(vAuxLHS106, mRHSrow103, vec_madd(vAuxLHS96, mRHSrow93, vec_madd(vAuxLHS86, mRHSrow83, vec_madd(vAuxLHS76, mRHSrow73, vec_madd(vAuxLHS66, mRHSrow63, vec_madd(vAuxLHS56, mRHSrow53, vec_madd(vAuxLHS46, mRHSrow43, vec_madd(vAuxLHS36, mRHSrow33, vec_madd(vAuxLHS26, mRHSrow23, vec_mul(vAuxLHS16, mRHSrow13)))))))))))), 0, mResult + 64);
	vec_xst(vec_madd(vAuxLHS126, mRHSrow124, vec_madd(vAuxLHS116, mRHSrow114, vec_madd(vAuxLHS106, mRHSrow104, vec_madd(vAuxLHS96, mRHSrow94, vec_madd(vAuxLHS86, mRHSrow84, vec_madd(vAuxLHS76, mRHSrow74, vec_madd(vAuxLHS66, mRHSrow64, vec_madd(vAuxLHS56, mRHSrow54, vec_madd(vAuxLHS46, mRHSrow44, vec_madd(vAuxLHS36, mRHSrow34, vec_madd(vAuxLHS26, mRHSrow24, vec_mul(vAuxLHS16, mRHSrow14)))))))))))), 0, mResult + 66);
	vec_xst(vec_madd(vAuxLHS126, mRHSrow125, vec_madd(vAuxLHS116, mRHSrow115, vec_madd(vAuxLHS106, mRHSrow105, vec_madd(vAuxLHS96, mRHSrow95, vec_madd(vAuxLHS86, mRHSrow85, vec_madd(vAuxLHS76, mRHSrow75, vec_madd(vAuxLHS66, mRHSrow65, vec_madd(vAuxLHS56, mRHSrow55, vec_madd(vAuxLHS46, mRHSrow45, vec_madd(vAuxLHS36, mRHSrow35, vec_madd(vAuxLHS26, mRHSrow25, vec_mul(vAuxLHS16, mRHSrow15)))))))))))), 0, mResult + 68);
	vec_xst(vec_madd(vAuxLHS126, mRHSrow126, vec_madd(vAuxLHS116, mRHSrow116, vec_madd(vAuxLHS106, mRHSrow106, vec_madd(vAuxLHS96, mRHSrow96, vec_madd(vAuxLHS86, mRHSrow86, vec_madd(vAuxLHS76, mRHSrow76, vec_madd(vAuxLHS66, mRHSrow66, vec_madd(vAuxLHS56, mRHSrow56, vec_madd(vAuxLHS46, mRHSrow46, vec_madd(vAuxLHS36, mRHSrow36, vec_madd(vAuxLHS26, mRHSrow26, vec_mul(vAuxLHS16, mRHSrow16)))))))))))), 0, mResult + 70);

	// row 7 of mResult
	vec_xst(vec_madd(vAuxLHS127, mRHSrow121, vec_madd(vAuxLHS117, mRHSrow111, vec_madd(vAuxLHS107, mRHSrow101, vec_madd(vAuxLHS97, mRHSrow91, vec_madd(vAuxLHS87, mRHSrow81, vec_madd(vAuxLHS77, mRHSrow71, vec_madd(vAuxLHS67, mRHSrow61, vec_madd(vAuxLHS57, mRHSrow51, vec_madd(vAuxLHS47, mRHSrow41, vec_madd(vAuxLHS37, mRHSrow31, vec_madd(vAuxLHS27, mRHSrow21, vec_mul(vAuxLHS17, mRHSrow11)))))))))))), 0, mResult + 72);
	vec_xst(vec_madd(vAuxLHS127, mRHSrow122, vec_madd(vAuxLHS117, mRHSrow112, vec_madd(vAuxLHS107, mRHSrow102, vec_madd(vAuxLHS97, mRHSrow92, vec_madd(vAuxLHS87, mRHSrow82, vec_madd(vAuxLHS77, mRHSrow72, vec_madd(vAuxLHS67, mRHSrow62, vec_madd(vAuxLHS57, mRHSrow52, vec_madd(vAuxLHS47, mRHSrow42, vec_madd(vAuxLHS37, mRHSrow32, vec_madd(vAuxLHS27, mRHSrow22, vec_mul(vAuxLHS17, mRHSrow12)))))))))))), 0, mResult + 74);
	vec_xst(vec_madd(vAuxLHS127, mRHSrow123, vec_madd(vAuxLHS117, mRHSrow113, vec_madd(vAuxLHS107, mRHSrow103, vec_madd(vAuxLHS97, mRHSrow93, vec_madd(vAuxLHS87, mRHSrow83, vec_madd(vAuxLHS77, mRHSrow73, vec_madd(vAuxLHS67, mRHSrow63, vec_madd(vAuxLHS57, mRHSrow53, vec_madd(vAuxLHS47, mRHSrow43, vec_madd(vAuxLHS37, mRHSrow33, vec_madd(vAuxLHS27, mRHSrow23, vec_mul(vAuxLHS17, mRHSrow13)))))))))))), 0, mResult + 76);
	vec_xst(vec_madd(vAuxLHS127, mRHSrow124, vec_madd(vAuxLHS117, mRHSrow114, vec_madd(vAuxLHS107, mRHSrow104, vec_madd(vAuxLHS97, mRHSrow94, vec_madd(vAuxLHS87, mRHSrow84, vec_madd(vAuxLHS77, mRHSrow74, vec_madd(vAuxLHS67, mRHSrow64, vec_madd(vAuxLHS57, mRHSrow54, vec_madd(vAuxLHS47, mRHSrow44, vec_madd(vAuxLHS37, mRHSrow34, vec_madd(vAuxLHS27, mRHSrow24, vec_mul(vAuxLHS17, mRHSrow14)))))))))))), 0, mResult + 78);
	vec_xst(vec_madd(vAuxLHS127, mRHSrow125, vec_madd(vAuxLHS117, mRHSrow115, vec_madd(vAuxLHS107, mRHSrow105, vec_madd(vAuxLHS97, mRHSrow95, vec_madd(vAuxLHS87, mRHSrow85, vec_madd(vAuxLHS77, mRHSrow75, vec_madd(vAuxLHS67, mRHSrow65, vec_madd(vAuxLHS57, mRHSrow55, vec_madd(vAuxLHS47, mRHSrow45, vec_madd(vAuxLHS37, mRHSrow35, vec_madd(vAuxLHS27, mRHSrow25, vec_mul(vAuxLHS17, mRHSrow15)))))))))))), 0, mResult + 80);
	vec_xst(vec_madd(vAuxLHS127, mRHSrow126, vec_madd(vAuxLHS117, mRHSrow116, vec_madd(vAuxLHS107, mRHSrow106, vec_madd(vAuxLHS97, mRHSrow96, vec_madd(vAuxLHS87, mRHSrow86, vec_madd(vAuxLHS77, mRHSrow76, vec_madd(vAuxLHS67, mRHSrow66, vec_madd(vAuxLHS57, mRHSrow56, vec_madd(vAuxLHS47, mRHSrow46, vec_madd(vAuxLHS37, mRHSrow36, vec_madd(vAuxLHS27, mRHSrow26, vec_mul(vAuxLHS17, mRHSrow16)))))))))))), 0, mResult + 82);

	// row 8 of mResult
	vec_xst(vec_madd(vAuxLHS128, mRHSrow121, vec_madd(vAuxLHS118, mRHSrow111, vec_madd(vAuxLHS108, mRHSrow101, vec_madd(vAuxLHS98, mRHSrow91, vec_madd(vAuxLHS88, mRHSrow81, vec_madd(vAuxLHS78, mRHSrow71, vec_madd(vAuxLHS68, mRHSrow61, vec_madd(vAuxLHS58, mRHSrow51, vec_madd(vAuxLHS48, mRHSrow41, vec_madd(vAuxLHS38, mRHSrow31, vec_madd(vAuxLHS28, mRHSrow21, vec_mul(vAuxLHS18, mRHSrow11)))))))))))), 0, mResult + 84);
	vec_xst(vec_madd(vAuxLHS128, mRHSrow122, vec_madd(vAuxLHS118, mRHSrow112, vec_madd(vAuxLHS108, mRHSrow102, vec_madd(vAuxLHS98, mRHSrow92, vec_madd(vAuxLHS88, mRHSrow82, vec_madd(vAuxLHS78, mRHSrow72, vec_madd(vAuxLHS68, mRHSrow62, vec_madd(vAuxLHS58, mRHSrow52, vec_madd(vAuxLHS48, mRHSrow42, vec_madd(vAuxLHS38, mRHSrow32, vec_madd(vAuxLHS28, mRHSrow22, vec_mul(vAuxLHS18, mRHSrow12)))))))))))), 0, mResult + 86);
	vec_xst(vec_madd(vAuxLHS128, mRHSrow123, vec_madd(vAuxLHS118, mRHSrow113, vec_madd(vAuxLHS108, mRHSrow103, vec_madd(vAuxLHS98, mRHSrow93, vec_madd(vAuxLHS88, mRHSrow83, vec_madd(vAuxLHS78, mRHSrow73, vec_madd(vAuxLHS68, mRHSrow63, vec_madd(vAuxLHS58, mRHSrow53, vec_madd(vAuxLHS48, mRHSrow43, vec_madd(vAuxLHS38, mRHSrow33, vec_madd(vAuxLHS28, mRHSrow23, vec_mul(vAuxLHS18, mRHSrow13)))))))))))), 0, mResult + 88);
	vec_xst(vec_madd(vAuxLHS128, mRHSrow124, vec_madd(vAuxLHS118, mRHSrow114, vec_madd(vAuxLHS108, mRHSrow104, vec_madd(vAuxLHS98, mRHSrow94, vec_madd(vAuxLHS88, mRHSrow84, vec_madd(vAuxLHS78, mRHSrow74, vec_madd(vAuxLHS68, mRHSrow64, vec_madd(vAuxLHS58, mRHSrow54, vec_madd(vAuxLHS48, mRHSrow44, vec_madd(vAuxLHS38, mRHSrow34, vec_madd(vAuxLHS28, mRHSrow24, vec_mul(vAuxLHS18, mRHSrow14)))))))))))), 0, mResult + 90);
	vec_xst(vec_madd(vAuxLHS128, mRHSrow125, vec_madd(vAuxLHS118, mRHSrow115, vec_madd(vAuxLHS108, mRHSrow105, vec_madd(vAuxLHS98, mRHSrow95, vec_madd(vAuxLHS88, mRHSrow85, vec_madd(vAuxLHS78, mRHSrow75, vec_madd(vAuxLHS68, mRHSrow65, vec_madd(vAuxLHS58, mRHSrow55, vec_madd(vAuxLHS48, mRHSrow45, vec_madd(vAuxLHS38, mRHSrow35, vec_madd(vAuxLHS28, mRHSrow25, vec_mul(vAuxLHS18, mRHSrow15)))))))))))), 0, mResult + 92);
	vec_xst(vec_madd(vAuxLHS128, mRHSrow126, vec_madd(vAuxLHS118, mRHSrow116, vec_madd(vAuxLHS108, mRHSrow106, vec_madd(vAuxLHS98, mRHSrow96, vec_madd(vAuxLHS88, mRHSrow86, vec_madd(vAuxLHS78, mRHSrow76, vec_madd(vAuxLHS68, mRHSrow66, vec_madd(vAuxLHS58, mRHSrow56, vec_madd(vAuxLHS48, mRHSrow46, vec_madd(vAuxLHS38, mRHSrow36, vec_madd(vAuxLHS28, mRHSrow26, vec_mul(vAuxLHS18, mRHSrow16)))))))))))), 0, mResult + 94);

	// row 9 of mResult
	vec_xst(vec_madd(vAuxLHS129, mRHSrow121, vec_madd(vAuxLHS119, mRHSrow111, vec_madd(vAuxLHS109, mRHSrow101, vec_madd(vAuxLHS99, mRHSrow91, vec_madd(vAuxLHS89, mRHSrow81, vec_madd(vAuxLHS79, mRHSrow71, vec_madd(vAuxLHS69, mRHSrow61, vec_madd(vAuxLHS59, mRHSrow51, vec_madd(vAuxLHS49, mRHSrow41, vec_madd(vAuxLHS39, mRHSrow31, vec_madd(vAuxLHS29, mRHSrow21, vec_mul(vAuxLHS19, mRHSrow11)))))))))))), 0, mResult + 96);
	vec_xst(vec_madd(vAuxLHS129, mRHSrow122, vec_madd(vAuxLHS119, mRHSrow112, vec_madd(vAuxLHS109, mRHSrow102, vec_madd(vAuxLHS99, mRHSrow92, vec_madd(vAuxLHS89, mRHSrow82, vec_madd(vAuxLHS79, mRHSrow72, vec_madd(vAuxLHS69, mRHSrow62, vec_madd(vAuxLHS59, mRHSrow52, vec_madd(vAuxLHS49, mRHSrow42, vec_madd(vAuxLHS39, mRHSrow32, vec_madd(vAuxLHS29, mRHSrow22, vec_mul(vAuxLHS19, mRHSrow12)))))))))))), 0, mResult + 98);
	vec_xst(vec_madd(vAuxLHS129, mRHSrow123, vec_madd(vAuxLHS119, mRHSrow113, vec_madd(vAuxLHS109, mRHSrow103, vec_madd(vAuxLHS99, mRHSrow93, vec_madd(vAuxLHS89, mRHSrow83, vec_madd(vAuxLHS79, mRHSrow73, vec_madd(vAuxLHS69, mRHSrow63, vec_madd(vAuxLHS59, mRHSrow53, vec_madd(vAuxLHS49, mRHSrow43, vec_madd(vAuxLHS39, mRHSrow33, vec_madd(vAuxLHS29, mRHSrow23, vec_mul(vAuxLHS19, mRHSrow13)))))))))))), 0, mResult + 100);
	vec_xst(vec_madd(vAuxLHS129, mRHSrow124, vec_madd(vAuxLHS119, mRHSrow114, vec_madd(vAuxLHS109, mRHSrow104, vec_madd(vAuxLHS99, mRHSrow94, vec_madd(vAuxLHS89, mRHSrow84, vec_madd(vAuxLHS79, mRHSrow74, vec_madd(vAuxLHS69, mRHSrow64, vec_madd(vAuxLHS59, mRHSrow54, vec_madd(vAuxLHS49, mRHSrow44, vec_madd(vAuxLHS39, mRHSrow34, vec_madd(vAuxLHS29, mRHSrow24, vec_mul(vAuxLHS19, mRHSrow14)))))))))))), 0, mResult + 102);
	vec_xst(vec_madd(vAuxLHS129, mRHSrow125, vec_madd(vAuxLHS119, mRHSrow115, vec_madd(vAuxLHS109, mRHSrow105, vec_madd(vAuxLHS99, mRHSrow95, vec_madd(vAuxLHS89, mRHSrow85, vec_madd(vAuxLHS79, mRHSrow75, vec_madd(vAuxLHS69, mRHSrow65, vec_madd(vAuxLHS59, mRHSrow55, vec_madd(vAuxLHS49, mRHSrow45, vec_madd(vAuxLHS39, mRHSrow35, vec_madd(vAuxLHS29, mRHSrow25, vec_mul(vAuxLHS19, mRHSrow15)))))))))))), 0, mResult + 104);
	vec_xst(vec_madd(vAuxLHS129, mRHSrow126, vec_madd(vAuxLHS119, mRHSrow116, vec_madd(vAuxLHS109, mRHSrow106, vec_madd(vAuxLHS99, mRHSrow96, vec_madd(vAuxLHS89, mRHSrow86, vec_madd(vAuxLHS79, mRHSrow76, vec_madd(vAuxLHS69, mRHSrow66, vec_madd(vAuxLHS59, mRHSrow56, vec_madd(vAuxLHS49, mRHSrow46, vec_madd(vAuxLHS39, mRHSrow36, vec_madd(vAuxLHS29, mRHSrow26, vec_mul(vAuxLHS19, mRHSrow16)))))))))))), 0, mResult + 106);

	// row 10 of mResult
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow121, vec_madd(vAuxLHS1110, mRHSrow111, vec_madd(vAuxLHS1010, mRHSrow101, vec_madd(vAuxLHS910, mRHSrow91, vec_madd(vAuxLHS810, mRHSrow81, vec_madd(vAuxLHS710, mRHSrow71, vec_madd(vAuxLHS610, mRHSrow61, vec_madd(vAuxLHS510, mRHSrow51, vec_madd(vAuxLHS410, mRHSrow41, vec_madd(vAuxLHS310, mRHSrow31, vec_madd(vAuxLHS210, mRHSrow21, vec_mul(vAuxLHS110, mRHSrow11)))))))))))), 0, mResult + 108);
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow122, vec_madd(vAuxLHS1110, mRHSrow112, vec_madd(vAuxLHS1010, mRHSrow102, vec_madd(vAuxLHS910, mRHSrow92, vec_madd(vAuxLHS810, mRHSrow82, vec_madd(vAuxLHS710, mRHSrow72, vec_madd(vAuxLHS610, mRHSrow62, vec_madd(vAuxLHS510, mRHSrow52, vec_madd(vAuxLHS410, mRHSrow42, vec_madd(vAuxLHS310, mRHSrow32, vec_madd(vAuxLHS210, mRHSrow22, vec_mul(vAuxLHS110, mRHSrow12)))))))))))), 0, mResult + 110);
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow123, vec_madd(vAuxLHS1110, mRHSrow113, vec_madd(vAuxLHS1010, mRHSrow103, vec_madd(vAuxLHS910, mRHSrow93, vec_madd(vAuxLHS810, mRHSrow83, vec_madd(vAuxLHS710, mRHSrow73, vec_madd(vAuxLHS610, mRHSrow63, vec_madd(vAuxLHS510, mRHSrow53, vec_madd(vAuxLHS410, mRHSrow43, vec_madd(vAuxLHS310, mRHSrow33, vec_madd(vAuxLHS210, mRHSrow23, vec_mul(vAuxLHS110, mRHSrow13)))))))))))), 0, mResult + 112);
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow124, vec_madd(vAuxLHS1110, mRHSrow114, vec_madd(vAuxLHS1010, mRHSrow104, vec_madd(vAuxLHS910, mRHSrow94, vec_madd(vAuxLHS810, mRHSrow84, vec_madd(vAuxLHS710, mRHSrow74, vec_madd(vAuxLHS610, mRHSrow64, vec_madd(vAuxLHS510, mRHSrow54, vec_madd(vAuxLHS410, mRHSrow44, vec_madd(vAuxLHS310, mRHSrow34, vec_madd(vAuxLHS210, mRHSrow24, vec_mul(vAuxLHS110, mRHSrow14)))))))))))), 0, mResult + 114);
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow125, vec_madd(vAuxLHS1110, mRHSrow115, vec_madd(vAuxLHS1010, mRHSrow105, vec_madd(vAuxLHS910, mRHSrow95, vec_madd(vAuxLHS810, mRHSrow85, vec_madd(vAuxLHS710, mRHSrow75, vec_madd(vAuxLHS610, mRHSrow65, vec_madd(vAuxLHS510, mRHSrow55, vec_madd(vAuxLHS410, mRHSrow45, vec_madd(vAuxLHS310, mRHSrow35, vec_madd(vAuxLHS210, mRHSrow25, vec_mul(vAuxLHS110, mRHSrow15)))))))))))), 0, mResult + 116);
	vec_xst(vec_madd(vAuxLHS1210, mRHSrow126, vec_madd(vAuxLHS1110, mRHSrow116, vec_madd(vAuxLHS1010, mRHSrow106, vec_madd(vAuxLHS910, mRHSrow96, vec_madd(vAuxLHS810, mRHSrow86, vec_madd(vAuxLHS710, mRHSrow76, vec_madd(vAuxLHS610, mRHSrow66, vec_madd(vAuxLHS510, mRHSrow56, vec_madd(vAuxLHS410, mRHSrow46, vec_madd(vAuxLHS310, mRHSrow36, vec_madd(vAuxLHS210, mRHSrow26, vec_mul(vAuxLHS110, mRHSrow16)))))))))))), 0, mResult + 118);

	// row 11 of mResult
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow121, vec_madd(vAuxLHS1111, mRHSrow111, vec_madd(vAuxLHS1011, mRHSrow101, vec_madd(vAuxLHS911, mRHSrow91, vec_madd(vAuxLHS811, mRHSrow81, vec_madd(vAuxLHS711, mRHSrow71, vec_madd(vAuxLHS611, mRHSrow61, vec_madd(vAuxLHS511, mRHSrow51, vec_madd(vAuxLHS411, mRHSrow41, vec_madd(vAuxLHS311, mRHSrow31, vec_madd(vAuxLHS211, mRHSrow21, vec_mul(vAuxLHS0111, mRHSrow11)))))))))))), 0, mResult + 120);
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow122, vec_madd(vAuxLHS1111, mRHSrow112, vec_madd(vAuxLHS1011, mRHSrow102, vec_madd(vAuxLHS911, mRHSrow92, vec_madd(vAuxLHS811, mRHSrow82, vec_madd(vAuxLHS711, mRHSrow72, vec_madd(vAuxLHS611, mRHSrow62, vec_madd(vAuxLHS511, mRHSrow52, vec_madd(vAuxLHS411, mRHSrow42, vec_madd(vAuxLHS311, mRHSrow32, vec_madd(vAuxLHS211, mRHSrow22, vec_mul(vAuxLHS0111, mRHSrow12)))))))))))), 0, mResult + 122);
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow123, vec_madd(vAuxLHS1111, mRHSrow113, vec_madd(vAuxLHS1011, mRHSrow103, vec_madd(vAuxLHS911, mRHSrow93, vec_madd(vAuxLHS811, mRHSrow83, vec_madd(vAuxLHS711, mRHSrow73, vec_madd(vAuxLHS611, mRHSrow63, vec_madd(vAuxLHS511, mRHSrow53, vec_madd(vAuxLHS411, mRHSrow43, vec_madd(vAuxLHS311, mRHSrow33, vec_madd(vAuxLHS211, mRHSrow23, vec_mul(vAuxLHS0111, mRHSrow13)))))))))))), 0, mResult + 124);
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow124, vec_madd(vAuxLHS1111, mRHSrow114, vec_madd(vAuxLHS1011, mRHSrow104, vec_madd(vAuxLHS911, mRHSrow94, vec_madd(vAuxLHS811, mRHSrow84, vec_madd(vAuxLHS711, mRHSrow74, vec_madd(vAuxLHS611, mRHSrow64, vec_madd(vAuxLHS511, mRHSrow54, vec_madd(vAuxLHS411, mRHSrow44, vec_madd(vAuxLHS311, mRHSrow34, vec_madd(vAuxLHS211, mRHSrow24, vec_mul(vAuxLHS0111, mRHSrow14)))))))))))), 0, mResult + 126);
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow125, vec_madd(vAuxLHS1111, mRHSrow115, vec_madd(vAuxLHS1011, mRHSrow105, vec_madd(vAuxLHS911, mRHSrow95, vec_madd(vAuxLHS811, mRHSrow85, vec_madd(vAuxLHS711, mRHSrow75, vec_madd(vAuxLHS611, mRHSrow65, vec_madd(vAuxLHS511, mRHSrow55, vec_madd(vAuxLHS411, mRHSrow45, vec_madd(vAuxLHS311, mRHSrow35, vec_madd(vAuxLHS211, mRHSrow25, vec_mul(vAuxLHS0111, mRHSrow15)))))))))))), 0, mResult + 128);
	vec_xst(vec_madd(vAuxLHS1211, mRHSrow126, vec_madd(vAuxLHS1111, mRHSrow116, vec_madd(vAuxLHS1011, mRHSrow106, vec_madd(vAuxLHS911, mRHSrow96, vec_madd(vAuxLHS811, mRHSrow86, vec_madd(vAuxLHS711, mRHSrow76, vec_madd(vAuxLHS611, mRHSrow66, vec_madd(vAuxLHS511, mRHSrow56, vec_madd(vAuxLHS411, mRHSrow46, vec_madd(vAuxLHS311, mRHSrow36, vec_madd(vAuxLHS211, mRHSrow26, vec_mul(vAuxLHS0111, mRHSrow16)))))))))))), 0, mResult + 130);

	// row 12 of mResult
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow121, vec_madd(vAuxLHS1112, mRHSrow111, vec_madd(vAuxLHS1012, mRHSrow101, vec_madd(vAuxLHS912, mRHSrow91, vec_madd(vAuxLHS812, mRHSrow81, vec_madd(vAuxLHS712, mRHSrow71, vec_madd(vAuxLHS612, mRHSrow61, vec_madd(vAuxLHS512, mRHSrow51, vec_madd(vAuxLHS412, mRHSrow41, vec_madd(vAuxLHS312, mRHSrow31, vec_madd(vAuxLHS212, mRHSrow21, vec_mul(vAuxLHS0112, mRHSrow11)))))))))))), 0, mResult + 132);
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow122, vec_madd(vAuxLHS1112, mRHSrow112, vec_madd(vAuxLHS1012, mRHSrow102, vec_madd(vAuxLHS912, mRHSrow92, vec_madd(vAuxLHS812, mRHSrow82, vec_madd(vAuxLHS712, mRHSrow72, vec_madd(vAuxLHS612, mRHSrow62, vec_madd(vAuxLHS512, mRHSrow52, vec_madd(vAuxLHS412, mRHSrow42, vec_madd(vAuxLHS312, mRHSrow32, vec_madd(vAuxLHS212, mRHSrow22, vec_mul(vAuxLHS0112, mRHSrow12)))))))))))), 0, mResult + 134);
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow123, vec_madd(vAuxLHS1112, mRHSrow113, vec_madd(vAuxLHS1012, mRHSrow103, vec_madd(vAuxLHS912, mRHSrow93, vec_madd(vAuxLHS812, mRHSrow83, vec_madd(vAuxLHS712, mRHSrow73, vec_madd(vAuxLHS612, mRHSrow63, vec_madd(vAuxLHS512, mRHSrow53, vec_madd(vAuxLHS412, mRHSrow43, vec_madd(vAuxLHS312, mRHSrow33, vec_madd(vAuxLHS212, mRHSrow23, vec_mul(vAuxLHS0112, mRHSrow13)))))))))))), 0, mResult + 136);
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow124, vec_madd(vAuxLHS1112, mRHSrow114, vec_madd(vAuxLHS1012, mRHSrow104, vec_madd(vAuxLHS912, mRHSrow94, vec_madd(vAuxLHS812, mRHSrow84, vec_madd(vAuxLHS712, mRHSrow74, vec_madd(vAuxLHS612, mRHSrow64, vec_madd(vAuxLHS512, mRHSrow54, vec_madd(vAuxLHS412, mRHSrow44, vec_madd(vAuxLHS312, mRHSrow34, vec_madd(vAuxLHS212, mRHSrow24, vec_mul(vAuxLHS0112, mRHSrow14)))))))))))), 0, mResult + 138);
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow125, vec_madd(vAuxLHS1112, mRHSrow115, vec_madd(vAuxLHS1012, mRHSrow105, vec_madd(vAuxLHS912, mRHSrow95, vec_madd(vAuxLHS812, mRHSrow85, vec_madd(vAuxLHS712, mRHSrow75, vec_madd(vAuxLHS612, mRHSrow65, vec_madd(vAuxLHS512, mRHSrow55, vec_madd(vAuxLHS412, mRHSrow45, vec_madd(vAuxLHS312, mRHSrow35, vec_madd(vAuxLHS212, mRHSrow25, vec_mul(vAuxLHS0112, mRHSrow15)))))))))))), 0, mResult + 140);
	vec_xst(vec_madd(vAuxLHS1212, mRHSrow126, vec_madd(vAuxLHS1112, mRHSrow116, vec_madd(vAuxLHS1012, mRHSrow106, vec_madd(vAuxLHS912, mRHSrow96, vec_madd(vAuxLHS812, mRHSrow86, vec_madd(vAuxLHS712, mRHSrow76, vec_madd(vAuxLHS612, mRHSrow66, vec_madd(vAuxLHS512, mRHSrow56, vec_madd(vAuxLHS412, mRHSrow46, vec_madd(vAuxLHS312, mRHSrow36, vec_madd(vAuxLHS212, mRHSrow26, vec_mul(vAuxLHS0112, mRHSrow16)))))))))))), 0, mResult + 142);

	return mResult;
}

int main () {

	int tam = 12;
	double* ar1 = new double[12*12];
	double*	ar2 = new double[12*12];
	double*	ar3 = new double[12*12];
	double* ar4 = new double[tam*tam];

	for (int i = 0; i < 12*12; i++) {
		ar1[i] = rand() % 100;
		ar2[i] = rand() % 100;
	}

	ar3 = mul(ar1, ar2);

	/*
	ar4 = result(ar1, ar2);
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			cout << (ar3[j + 12*i] == ar4[j + 12*i]) << "\t";
		}
		cout << endl;
	}
	*/

	return 0;
}

