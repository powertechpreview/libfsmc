#ifndef IBM_SMUL_H
#define IBM_SMUL_H

#include <iostream>
#include <stdio.h>
#include <altivec.h>

//col x col


inline void mul4x4ColColFloat(const float* mLHS, const float* mRHS, float* const mResult){
	
	vector float mLHScol1,mLHScol2,mLHScol3,mLHScol4;
	vector float mRHScol1,mRHScol2,mRHScol3,mRHScol4;


	//====================================================
	
	mRHScol1 = vec_xl(0,mRHS);
	mRHScol2 = vec_xl(0,mRHS+4);
	mRHScol3 = vec_xl(0,mRHS+4*2);
	mRHScol4 = vec_xl(0,mRHS+4*3);

	mLHScol1 = vec_xl(0,mLHS);
	mLHScol2 = vec_xl(0,mLHS+4);
	mLHScol3 = vec_xl(0,mLHS+4*2);
	mLHScol4 = vec_xl(0,mLHS+4*3);

	//transpose RHS
	vector float mRHSrow1 = {mRHScol1[0],mRHScol2[0],mRHScol3[0],mRHScol4[0]};
	vector float mRHSrow2 = {mRHScol1[1],mRHScol2[1],mRHScol3[1],mRHScol4[1]};
	vector float mRHSrow3 = {mRHScol1[2],mRHScol2[2],mRHScol3[2],mRHScol4[2]};
	vector float mRHSrow4 = {mRHScol1[3],mRHScol2[3],mRHScol3[3],mRHScol4[3]};


	//splat==============================================
	
	vector float auxLHS11 = {mLHScol1[0],mLHScol1[0],mLHScol1[0],mLHScol1[0]};
	vector float auxLHS12 = {mLHScol1[1],mLHScol1[1],mLHScol1[1],mLHScol1[1]};
	vector float auxLHS13 = {mLHScol1[2],mLHScol1[2],mLHScol1[2],mLHScol1[2]};
	vector float auxLHS14 = {mLHScol1[3],mLHScol1[3],mLHScol1[3],mLHScol1[3]};
	
	vector float auxLHS21 = {mLHScol2[0],mLHScol2[0],mLHScol2[0],mLHScol2[0]};
	vector float auxLHS22 = {mLHScol2[1],mLHScol2[1],mLHScol2[1],mLHScol2[1]};
	vector float auxLHS23 = {mLHScol2[2],mLHScol2[2],mLHScol2[2],mLHScol2[2]};
	vector float auxLHS24 = {mLHScol2[3],mLHScol2[3],mLHScol2[3],mLHScol2[3]};

	vector float auxLHS31 = {mLHScol3[0],mLHScol3[0],mLHScol3[0],mLHScol3[0]};
	vector float auxLHS32 = {mLHScol3[1],mLHScol3[1],mLHScol3[1],mLHScol3[1]};
	vector float auxLHS33 = {mLHScol3[2],mLHScol3[2],mLHScol3[2],mLHScol3[2]};
	vector float auxLHS34 = {mLHScol3[3],mLHScol3[3],mLHScol3[3],mLHScol3[3]};
	
	vector float auxLHS41 = {mLHScol4[0],mLHScol4[0],mLHScol4[0],mLHScol4[0]};
	vector float auxLHS42 = {mLHScol4[1],mLHScol4[1],mLHScol4[1],mLHScol4[1]};
	vector float auxLHS43 = {mLHScol4[2],mLHScol4[2],mLHScol4[2],mLHScol4[2]};
	vector float auxLHS44 = {mLHScol4[3],mLHScol4[3],mLHScol4[3],mLHScol4[3]};
	
	
 	//row 1 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS11,mRHSrow1),vec_mul(auxLHS12,mRHSrow2)),
	vec_add(vec_mul(auxLHS13,mRHSrow3),vec_mul(auxLHS14,mRHSrow4))),0,
	mResult
	);

	//row 2 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS21,mRHSrow1),vec_mul(auxLHS22,mRHSrow2)),
	vec_add(vec_mul(auxLHS23,mRHSrow3),vec_mul(auxLHS24,mRHSrow4))),0,mResult+4
	);

	//row 3
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS31,mRHSrow1),vec_mul(auxLHS32,mRHSrow2)),
	vec_add(vec_mul(auxLHS33,mRHSrow3),vec_mul(auxLHS34,mRHSrow4))),0,mResult+8
	);

	//row 4
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS41,mRHSrow1),vec_mul(auxLHS42,mRHSrow2)),
	vec_add(vec_mul(auxLHS43,mRHSrow3),vec_mul(auxLHS44,mRHSrow4))),0,mResult+12
	);

}

inline void mul9x9ColColFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHScol11, mLHScol12, mLHScol13, mLHScol21, mLHScol22, mLHScol23, mLHScol31, mLHScol32, mLHScol33,
	      	     mLHScol41, mLHScol42, mLHScol43, mLHScol51, mLHScol52, mLHScol53, mLHScol61, mLHScol62, mLHScol63,
		     mLHScol71, mLHScol72, mLHScol73, mLHScol81, mLHScol82, mLHScol83, mLHScol91, mLHScol92, mLHScol93;


	vector float mRHScol11, mRHScol12, mRHScol13, mRHScol21, mRHScol22, mRHScol23, mRHScol31, mRHScol32, mRHScol33,
	      	     mRHScol41, mRHScol42, mRHScol43, mRHScol51, mRHScol52, mRHScol53, mRHScol61, mRHScol62, mRHScol63,
		     mRHScol71, mRHScol72, mRHScol73, mRHScol81, mRHScol82, mRHScol83, mRHScol91, mRHScol92, mRHScol93;

//load
// __8__17__26__35__44__53__62__71__80


	mLHScol11 = vec_xl(0,mLHS);
	mLHScol12 = vec_xl(0,mLHS+4);
	mLHScol13 = vec_splats((float)0);
	mLHScol13[0] = mLHS[8];

	mLHScol21 = vec_xl(0,mLHS+4*2+1);
	mLHScol22 = vec_xl(0,mLHS+4*3+1);
	mLHScol23 = vec_splats((float)0);
	mLHScol23[0] = mLHS[17];

	mLHScol31 = vec_xl(0,mLHS+4*4+2);
	mLHScol32 = vec_xl(0,mLHS+4*5+2);
	mLHScol33 = vec_splats((float)0);
	mLHScol33[0] = mLHS[26];

	mLHScol41 = vec_xl(0,mLHS+4*6+3);
	mLHScol42 = vec_xl(0,mLHS+4*7+3);
	mLHScol43 = vec_splats((float)0);
	mLHScol43[0] = mLHS[35];

	mLHScol51 = vec_xl(0,mLHS+4*8+4);
	mLHScol52 = vec_xl(0,mLHS+4*9+4);
	mLHScol53 = vec_splats((float)0);
	mLHScol53[0] = mLHS[44];

	mLHScol61 = vec_xl(0,mLHS+4*10+5);
	mLHScol62 = vec_xl(0,mLHS+4*11+5);
	mLHScol63 = vec_splats((float)0);
	mLHScol63[0] = mLHS[53];
	
	mLHScol71 = vec_xl(0,mLHS+4*12+6);
	mLHScol72 = vec_xl(0,mLHS+4*13+6);
	mLHScol73 = vec_splats((float)0);
	mLHScol73[0] = mLHS[62];

	mLHScol81 = vec_xl(0,mLHS+4*14+7);
	mLHScol82 = vec_xl(0,mLHS+4*15+7);
	mLHScol83 = vec_splats((float)0);
	mLHScol83[0] = mLHS[71];

	mLHScol91 = vec_xl(0,mLHS+4*16+8);
	mLHScol92 = vec_xl(0,mLHS+4*17+8);
	mLHScol93 = vec_splats((float)0);
	mLHScol93[0] = mLHS[80];
//-----------------------------------------------------

	mRHScol11 = vec_xl(0,mRHS);
	mRHScol12 = vec_xl(0,mRHS+4);

	mRHScol21 = vec_xl(0,mRHS+4*2+1);
	mRHScol22 = vec_xl(0,mRHS+4*3+1);

	mRHScol31 = vec_xl(0,mRHS+4*4+2);
	mRHScol32 = vec_xl(0,mRHS+4*5+2);

	mRHScol41 = vec_xl(0,mRHS+4*6+3);
	mRHScol42 = vec_xl(0,mRHS+4*7+3);

	mRHScol51 = vec_xl(0,mRHS+4*8+4);
	mRHScol52 = vec_xl(0,mRHS+4*9+4);

	mRHScol61 = vec_xl(0,mRHS+4*10+5);
	mRHScol62 = vec_xl(0,mRHS+4*11+5);
	
	mRHScol71 = vec_xl(0,mRHS+4*12+6);
	mRHScol72 = vec_xl(0,mRHS+4*13+6);

	mRHScol81 = vec_xl(0,mRHS+4*14+7);
	mRHScol82 = vec_xl(0,mRHS+4*15+7);

	mRHScol91 = vec_xl(0,mRHS+4*16+8);
	mRHScol92 = vec_xl(0,mRHS+4*17+8);


// transpose RHS

	vector float mRHSrow11 = {mRHScol11[0],mRHScol21[0],mRHScol31[0],mRHScol41[0]};
	vector float mRHSrow12 = {mRHScol51[0],mRHScol61[0],mRHScol71[0],mRHScol81[0]};
	vector float mRHSrow13 = {mRHScol91[0],0,0,0};

	vector float mRHSrow21 = {mRHScol11[1],mRHScol21[1],mRHScol31[1],mRHScol41[1]};
	vector float mRHSrow22 = {mRHScol51[1],mRHScol61[1],mRHScol71[1],mRHScol81[1]};
	vector float mRHSrow23 = {mRHScol91[1],0,0,0};

	vector float mRHSrow31 = {mRHScol11[2],mRHScol21[2],mRHScol31[2],mRHScol41[2]};
	vector float mRHSrow32 = {mRHScol51[2],mRHScol61[2],mRHScol71[2],mRHScol81[2]};
	vector float mRHSrow33 = {mRHScol91[2],0,0,0};

	vector float mRHSrow41 = {mRHScol11[3],mRHScol21[3],mRHScol31[3],mRHScol41[3]};
	vector float mRHSrow42 = {mRHScol51[3],mRHScol61[3],mRHScol71[3],mRHScol81[3]};
	vector float mRHSrow43 = {mRHScol91[3],0,0,0};

	vector float mRHSrow51 = {mRHScol12[0],mRHScol22[0],mRHScol32[0],mRHScol42[0]};
	vector float mRHSrow52 = {mRHScol52[0],mRHScol62[0],mRHScol72[0],mRHScol82[0]};
	vector float mRHSrow53 = {mRHScol92[0],0,0,0};

	vector float mRHSrow61 = {mRHScol12[1],mRHScol22[1],mRHScol32[1],mRHScol42[1]};
	vector float mRHSrow62 = {mRHScol12[1],mRHScol62[1],mRHScol72[1],mRHScol82[1]};
	vector float mRHSrow63 = {mRHScol12[1],0,0,0};

	vector float mRHSrow71 = {mRHScol12[2],mRHScol22[2],mRHScol32[2],mRHScol42[2]};
	vector float mRHSrow72 = {mRHScol52[2],mRHScol62[2],mRHScol72[2],mRHScol82[2]};
	vector float mRHSrow73 = {mRHScol92[2],0,0,0};

	vector float mRHSrow81 = {mRHScol12[3],mRHScol22[3],mRHScol32[3],mRHScol42[3]};
	vector float mRHSrow82 = {mRHScol52[3],mRHScol62[3],mRHScol72[3],mRHScol82[3]};
	vector float mRHSrow83 = {mRHScol92[3],0,0,0};

	vector float mRHSrow91 = {mRHS[8],mRHS[17],mRHS[26],mRHS[35]};
	vector float mRHSrow92 = {mRHS[44],mRHS[53],mRHS[62],mRHS[71]};
	vector float mRHSrow93 = {mRHS[80],0,0,0};



//===================================================================================
//Splat
//===================================================================================
	
	vector float aux11={mLHScol11[0],mLHScol11[0],mLHScol11[0],mLHScol11[0]};
	vector float aux12={mLHScol11[1],mLHScol11[1],mLHScol11[1],mLHScol11[1]};
	vector float aux13={mLHScol11[2],mLHScol11[2],mLHScol11[2],mLHScol11[2]};
	vector float aux14={mLHScol11[3],mLHScol11[3],mLHScol11[3],mLHScol11[3]};

	vector float aux15={mLHScol12[0],mLHScol12[0],mLHScol12[0],mLHScol12[0]};
	vector float aux16={mLHScol12[1],mLHScol12[1],mLHScol12[1],mLHScol12[1]};
	vector float aux17={mLHScol12[2],mLHScol12[2],mLHScol12[2],mLHScol12[2]};
	vector float aux18={mLHScol12[3],mLHScol12[3],mLHScol12[3],mLHScol12[3]};

	vector float aux19={mLHScol13[0],mLHScol13[0],mLHScol13[0],mLHScol13[0]};
//----------------------------------------------------------------------------------
	vector float aux21={mLHScol21[0],mLHScol21[0],mLHScol21[0],mLHScol21[0]};
	vector float aux22={mLHScol21[1],mLHScol21[1],mLHScol21[1],mLHScol21[1]};
	vector float aux23={mLHScol21[2],mLHScol21[2],mLHScol21[2],mLHScol21[2]};
	vector float aux24={mLHScol21[3],mLHScol21[3],mLHScol21[3],mLHScol21[3]};

	vector float aux25={mLHScol22[0],mLHScol22[0],mLHScol22[0],mLHScol22[0]};
	vector float aux26={mLHScol22[1],mLHScol22[1],mLHScol22[1],mLHScol22[1]};
	vector float aux27={mLHScol22[2],mLHScol22[2],mLHScol22[2],mLHScol22[2]};
	vector float aux28={mLHScol22[3],mLHScol22[3],mLHScol22[3],mLHScol22[3]};

	vector float aux29={mLHScol23[0],mLHScol23[0],mLHScol23[0],mLHScol23[0]};
//----------------------------------------------------------------------------------
	vector float aux31={mLHScol31[0],mLHScol31[0],mLHScol31[0],mLHScol31[0]};
	vector float aux32={mLHScol31[1],mLHScol31[1],mLHScol31[1],mLHScol31[1]};
	vector float aux33={mLHScol31[2],mLHScol31[2],mLHScol31[2],mLHScol31[2]};
	vector float aux34={mLHScol31[3],mLHScol31[3],mLHScol31[3],mLHScol31[3]};

	vector float aux35={mLHScol32[0],mLHScol32[0],mLHScol32[0],mLHScol32[0]};
	vector float aux36={mLHScol32[1],mLHScol32[1],mLHScol32[1],mLHScol32[1]};
	vector float aux37={mLHScol32[2],mLHScol32[2],mLHScol32[2],mLHScol32[2]};
	vector float aux38={mLHScol32[3],mLHScol32[3],mLHScol32[3],mLHScol32[3]};

	vector float aux39={mLHScol33[0],mLHScol33[0],mLHScol33[0],mLHScol33[0]};
//----------------------------------------------------------------------------------
	vector float aux41={mLHScol41[0],mLHScol41[0],mLHScol41[0],mLHScol41[0]};
	vector float aux42={mLHScol41[1],mLHScol41[1],mLHScol41[1],mLHScol41[1]};
	vector float aux43={mLHScol41[2],mLHScol41[2],mLHScol41[2],mLHScol41[2]};
	vector float aux44={mLHScol41[3],mLHScol41[3],mLHScol41[3],mLHScol41[3]};

	vector float aux45={mLHScol42[0],mLHScol42[0],mLHScol42[0],mLHScol42[0]};
	vector float aux46={mLHScol42[1],mLHScol42[1],mLHScol42[1],mLHScol42[1]};
	vector float aux47={mLHScol42[2],mLHScol42[2],mLHScol42[2],mLHScol42[2]};
	vector float aux48={mLHScol42[3],mLHScol42[3],mLHScol42[3],mLHScol42[3]};

	vector float aux49={mLHScol43[0],mLHScol43[0],mLHScol43[0],mLHScol43[0]};
//----------------------------------------------------------------------------------
	vector float aux51={mLHScol51[0],mLHScol51[0],mLHScol51[0],mLHScol51[0]};
	vector float aux52={mLHScol51[1],mLHScol51[1],mLHScol51[1],mLHScol51[1]};
	vector float aux53={mLHScol51[2],mLHScol51[2],mLHScol51[2],mLHScol51[2]};
	vector float aux54={mLHScol51[3],mLHScol51[3],mLHScol51[3],mLHScol51[3]};

	vector float aux55={mLHScol52[0],mLHScol52[0],mLHScol52[0],mLHScol52[0]};
	vector float aux56={mLHScol52[1],mLHScol52[1],mLHScol52[1],mLHScol52[1]};
	vector float aux57={mLHScol52[2],mLHScol52[2],mLHScol52[2],mLHScol52[2]};
	vector float aux58={mLHScol52[3],mLHScol52[3],mLHScol52[3],mLHScol52[3]};

	vector float aux59={mLHScol53[0],mLHScol53[0],mLHScol53[0],mLHScol53[0]};
//----------------------------------------------------------------------------------
	vector float aux61={mLHScol61[0],mLHScol61[0],mLHScol61[0],mLHScol61[0]};
	vector float aux62={mLHScol61[1],mLHScol61[1],mLHScol61[1],mLHScol61[1]};
	vector float aux63={mLHScol61[2],mLHScol61[2],mLHScol61[2],mLHScol61[2]};
	vector float aux64={mLHScol61[3],mLHScol61[3],mLHScol61[3],mLHScol61[3]};

	vector float aux65={mLHScol62[0],mLHScol62[0],mLHScol62[0],mLHScol62[0]};
	vector float aux66={mLHScol62[1],mLHScol62[1],mLHScol62[1],mLHScol62[1]};
	vector float aux67={mLHScol62[2],mLHScol62[2],mLHScol62[2],mLHScol62[2]};
	vector float aux68={mLHScol62[3],mLHScol62[3],mLHScol62[3],mLHScol62[3]};

	vector float aux69={mLHScol63[0],mLHScol63[0],mLHScol63[0],mLHScol63[0]};
//----------------------------------------------------------------------------------
	vector float aux71={mLHScol71[0],mLHScol71[0],mLHScol71[0],mLHScol71[0]};
	vector float aux72={mLHScol71[1],mLHScol71[1],mLHScol71[1],mLHScol71[1]};
	vector float aux73={mLHScol71[2],mLHScol71[2],mLHScol71[2],mLHScol71[2]};
	vector float aux74={mLHScol71[3],mLHScol71[3],mLHScol71[3],mLHScol71[3]};

	vector float aux75={mLHScol72[0],mLHScol72[0],mLHScol72[0],mLHScol72[0]};
	vector float aux76={mLHScol72[1],mLHScol72[1],mLHScol72[1],mLHScol72[1]};
	vector float aux77={mLHScol72[2],mLHScol72[2],mLHScol72[2],mLHScol72[2]};
	vector float aux78={mLHScol72[3],mLHScol72[3],mLHScol72[3],mLHScol72[3]};

	vector float aux79={mLHScol73[0],mLHScol73[0],mLHScol73[0],mLHScol73[0]};
//----------------------------------------------------------------------------------
	vector float aux81={mLHScol81[0],mLHScol81[0],mLHScol81[0],mLHScol81[0]};
	vector float aux82={mLHScol81[1],mLHScol81[1],mLHScol81[1],mLHScol81[1]};
	vector float aux83={mLHScol81[2],mLHScol81[2],mLHScol81[2],mLHScol81[2]};
	vector float aux84={mLHScol81[3],mLHScol81[3],mLHScol81[3],mLHScol81[3]};

	vector float aux85={mLHScol82[0],mLHScol82[0],mLHScol82[0],mLHScol82[0]};
	vector float aux86={mLHScol82[1],mLHScol82[1],mLHScol82[1],mLHScol82[1]};
	vector float aux87={mLHScol82[2],mLHScol82[2],mLHScol82[2],mLHScol82[2]};
	vector float aux88={mLHScol82[3],mLHScol82[3],mLHScol82[3],mLHScol82[3]};

	vector float aux89={mLHScol83[0],mLHScol83[0],mLHScol83[0],mLHScol83[0]};
//----------------------------------------------------------------------------------
	vector float aux91={mLHScol91[0],mLHScol91[0],mLHScol91[0],mLHScol91[0]};
	vector float aux92={mLHScol91[1],mLHScol91[1],mLHScol91[1],mLHScol91[1]};
	vector float aux93={mLHScol91[2],mLHScol91[2],mLHScol91[2],mLHScol91[2]};
	vector float aux94={mLHScol91[3],mLHScol91[3],mLHScol91[3],mLHScol91[3]};

	vector float aux95={mLHScol92[0],mLHScol92[0],mLHScol92[0],mLHScol92[0]};
	vector float aux96={mLHScol92[1],mLHScol92[1],mLHScol92[1],mLHScol92[1]};
	vector float aux97={mLHScol92[2],mLHScol92[2],mLHScol92[2],mLHScol92[2]};
	vector float aux98={mLHScol92[3],mLHScol92[3],mLHScol92[3],mLHScol92[3]};

	vector float aux99={mLHScol93[0],mLHScol93[0],mLHScol93[0],mLHScol93[0]};
//----------------------------------------------------------------------------------


//row1
	vec_xst(vec_madd( mRHSrow91, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux21, vec_mul(mRHSrow11, aux11)),
					vec_madd(mRHSrow41, aux41, vec_mul(mRHSrow31, aux31)) ),
				vec_add(
					vec_madd(mRHSrow61, aux61, vec_mul(mRHSrow51, aux51)),
					vec_madd(mRHSrow81, aux81, vec_mul(mRHSrow71, aux71)) ) ) ),

				0, mResult);	

	
	vec_xst(vec_madd( mRHSrow92, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux21, vec_mul(mRHSrow12, aux11)),
					vec_madd(mRHSrow42, aux41, vec_mul(mRHSrow32, aux31)) ),
				vec_add(
					vec_madd(mRHSrow62, aux61, vec_mul(mRHSrow52, aux51)),
					vec_madd(mRHSrow82, aux81, vec_mul(mRHSrow72, aux71)) ) ) ),

				0, mResult+4);

	vec_xst(vec_madd( mRHSrow93, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux21, vec_mul(mRHSrow13, aux11)),
					vec_madd(mRHSrow43, aux41, vec_mul(mRHSrow33, aux31)) ),
				vec_add(
					vec_madd(mRHSrow63, aux61, vec_mul(mRHSrow53, aux51)),
					vec_madd(mRHSrow83, aux81, vec_mul(mRHSrow73, aux71)) ) ) ),

				0, mResult+8);	
//row 2


	vec_xst(vec_madd( mRHSrow91, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux22, vec_mul(mRHSrow11, aux12)),
					vec_madd(mRHSrow41, aux42, vec_mul(mRHSrow31, aux32)) ),
				vec_add(
					vec_madd(mRHSrow61, aux62, vec_mul(mRHSrow51, aux52)),
					vec_madd(mRHSrow81, aux82, vec_mul(mRHSrow71, aux72)) ) ) ),

				0, mResult+4*2+1);

	vec_xst(vec_madd( mRHSrow92, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux22, vec_mul(mRHSrow12, aux12)),
					vec_madd(mRHSrow42, aux42, vec_mul(mRHSrow32, aux32)) ),
				vec_add(
					vec_madd(mRHSrow62, aux62, vec_mul(mRHSrow52, aux52)),
					vec_madd(mRHSrow82, aux82, vec_mul(mRHSrow72, aux72)) ) ) ),

				0, mResult+4*3+1);


	vec_xst(vec_madd( mRHSrow93, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux22, vec_mul(mRHSrow13, aux12)),
					vec_madd(mRHSrow43, aux42, vec_mul(mRHSrow33, aux32)) ),
				vec_add(
					vec_madd(mRHSrow63, aux62, vec_mul(mRHSrow53, aux52)),
					vec_madd(mRHSrow83, aux82, vec_mul(mRHSrow73, aux72)) ) ) ),

				0, mResult+17);

//row 3

	vec_xst(vec_madd( mRHSrow91, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux23, vec_mul(mRHSrow11, aux13)),
					vec_madd(mRHSrow41, aux43, vec_mul(mRHSrow31, aux33)) ),
				vec_add(
					vec_madd(mRHSrow61, aux63, vec_mul(mRHSrow51, aux53)),
					vec_madd(mRHSrow81, aux83, vec_mul(mRHSrow71, aux73)) ) ) ),

				0, mResult+4*4+2);

	vec_xst(vec_madd( mRHSrow92, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux23, vec_mul(mRHSrow12, aux13)),
					vec_madd(mRHSrow42, aux43, vec_mul(mRHSrow32, aux33)) ),
				vec_add(
					vec_madd(mRHSrow62, aux63, vec_mul(mRHSrow52, aux53)),
					vec_madd(mRHSrow82, aux83, vec_mul(mRHSrow72, aux73)) ) ) ),

				0, mResult+4*5+2);


	vec_xst(vec_madd( mRHSrow93, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux23, vec_mul(mRHSrow13, aux13)),
					vec_madd(mRHSrow43, aux43, vec_mul(mRHSrow33, aux33)) ),
				vec_add(
					vec_madd(mRHSrow63, aux63, vec_mul(mRHSrow53, aux53)),
					vec_madd(mRHSrow83, aux83, vec_mul(mRHSrow73, aux73)) ) ) ),

				0, mResult+26);
//row 4


	vec_xst(vec_madd( mRHSrow91, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux24, vec_mul(mRHSrow11, aux14)),
					vec_madd(mRHSrow41, aux44, vec_mul(mRHSrow31, aux34)) ),
				vec_add(
					vec_madd(mRHSrow61, aux64, vec_mul(mRHSrow51, aux54)),
					vec_madd(mRHSrow81, aux84, vec_mul(mRHSrow71, aux74)) ) ) ),

				0, mResult+4*6+3);

	vec_xst(vec_madd( mRHSrow92, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux24, vec_mul(mRHSrow12, aux14)),
					vec_madd(mRHSrow42, aux44, vec_mul(mRHSrow32, aux34)) ),
				vec_add(
					vec_madd(mRHSrow62, aux64, vec_mul(mRHSrow52, aux54)),
					vec_madd(mRHSrow82, aux84, vec_mul(mRHSrow72, aux74)) ) ) ),

				0, mResult+4*7+3);

	vec_xst(vec_madd( mRHSrow93, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux24, vec_mul(mRHSrow13, aux14)),
					vec_madd(mRHSrow43, aux44, vec_mul(mRHSrow33, aux34)) ),
				vec_add(
					vec_madd(mRHSrow63, aux64, vec_mul(mRHSrow53, aux54)),
					vec_madd(mRHSrow83, aux84, vec_mul(mRHSrow73, aux74)) ) ) ),

				0, mResult+35);
//row 5


	vec_xst(vec_madd( mRHSrow91, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux25, vec_mul(mRHSrow11, aux15)),
					vec_madd(mRHSrow41, aux45, vec_mul(mRHSrow31, aux35)) ),
				vec_add(
					vec_madd(mRHSrow61, aux65, vec_mul(mRHSrow51, aux55)),
					vec_madd(mRHSrow81, aux85, vec_mul(mRHSrow71, aux75)) ) ) ),

				0, mResult+4*8+4);



	vec_xst(vec_madd( mRHSrow92, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux25, vec_mul(mRHSrow12, aux15)),
					vec_madd(mRHSrow42, aux45, vec_mul(mRHSrow32, aux35)) ),
				vec_add(
					vec_madd(mRHSrow62, aux65, vec_mul(mRHSrow52, aux55)),
					vec_madd(mRHSrow82, aux85, vec_mul(mRHSrow72, aux75)) ) ) ),

				0, mResult+4*9+4);


	vec_xst(vec_madd( mRHSrow93, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux25, vec_mul(mRHSrow13, aux15)),
					vec_madd(mRHSrow43, aux45, vec_mul(mRHSrow33, aux35)) ),
				vec_add(
					vec_madd(mRHSrow63, aux65, vec_mul(mRHSrow53, aux55)),
					vec_madd(mRHSrow83, aux85, vec_mul(mRHSrow73, aux75)) ) ) ),

				0, mResult+44);

//row 6


	vec_xst(vec_madd( mRHSrow91, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux26, vec_mul(mRHSrow11, aux16)),
					vec_madd(mRHSrow41, aux46, vec_mul(mRHSrow31, aux36)) ),
				vec_add(
					vec_madd(mRHSrow61, aux66, vec_mul(mRHSrow51, aux56)),
					vec_madd(mRHSrow81, aux86, vec_mul(mRHSrow71, aux76)) ) ) ),

				0, mResult+4*10+5);


	vec_xst(vec_madd( mRHSrow92, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux26, vec_mul(mRHSrow12, aux16)),
					vec_madd(mRHSrow42, aux46, vec_mul(mRHSrow32, aux36)) ),
				vec_add(
					vec_madd(mRHSrow62, aux66, vec_mul(mRHSrow52, aux56)),
					vec_madd(mRHSrow82, aux86, vec_mul(mRHSrow72, aux76)) ) ) ),

				0, mResult+4*11+5);


	vec_xst(vec_madd( mRHSrow93, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux26, vec_mul(mRHSrow13, aux16)),
					vec_madd(mRHSrow43, aux46, vec_mul(mRHSrow33, aux36)) ),
				vec_add(
					vec_madd(mRHSrow63, aux66, vec_mul(mRHSrow53, aux56)),
					vec_madd(mRHSrow83, aux86, vec_mul(mRHSrow73, aux76)) ) ) ),

				0, mResult+53);

//row 7

	vec_xst(vec_madd( mRHSrow91, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux27, vec_mul(mRHSrow11, aux17)),
					vec_madd(mRHSrow41, aux47, vec_mul(mRHSrow31, aux37)) ),
				vec_add(
					vec_madd(mRHSrow61, aux67, vec_mul(mRHSrow51, aux57)),
					vec_madd(mRHSrow81, aux87, vec_mul(mRHSrow71, aux77)) ) ) ),

				0, mResult+4*12+6);

	vec_xst(vec_madd( mRHSrow92, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux27, vec_mul(mRHSrow12, aux17)),
					vec_madd(mRHSrow42, aux47, vec_mul(mRHSrow32, aux37)) ),
				vec_add(
					vec_madd(mRHSrow62, aux67, vec_mul(mRHSrow52, aux57)),
					vec_madd(mRHSrow82, aux87, vec_mul(mRHSrow72, aux77)) ) ) ),

				0, mResult+4*13+6);


	vec_xst(vec_madd( mRHSrow93, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux27, vec_mul(mRHSrow13, aux17)),
					vec_madd(mRHSrow43, aux47, vec_mul(mRHSrow33, aux37)) ),
				vec_add(
					vec_madd(mRHSrow63, aux67, vec_mul(mRHSrow53, aux57)),
					vec_madd(mRHSrow83, aux87, vec_mul(mRHSrow73, aux77)) ) ) ),

				0, mResult+62);
//row 8



	vec_xst(vec_madd( mRHSrow91, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux28, vec_mul(mRHSrow11, aux18)),
					vec_madd(mRHSrow41, aux48, vec_mul(mRHSrow31, aux38)) ),
				vec_add(
					vec_madd(mRHSrow61, aux68, vec_mul(mRHSrow51, aux58)),
					vec_madd(mRHSrow81, aux88, vec_mul(mRHSrow71, aux78)) ) ) ),

				0, mResult+4*14+7);


	vec_xst(vec_madd( mRHSrow92, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux28, vec_mul(mRHSrow12, aux18)),
					vec_madd(mRHSrow42, aux48, vec_mul(mRHSrow32, aux38)) ),
				vec_add(
					vec_madd(mRHSrow62, aux68, vec_mul(mRHSrow52, aux58)),
					vec_madd(mRHSrow82, aux88, vec_mul(mRHSrow72, aux78)) ) ) ),

				0, mResult+4*15+7);


	vec_xst(vec_madd( mRHSrow93, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux28, vec_mul(mRHSrow13, aux18)),
					vec_madd(mRHSrow43, aux48, vec_mul(mRHSrow33, aux38)) ),
				vec_add(
					vec_madd(mRHSrow63, aux68, vec_mul(mRHSrow53, aux58)),
					vec_madd(mRHSrow83, aux88, vec_mul(mRHSrow73, aux78)) ) ) ),

				0, mResult+71);

//row 9



	vec_xst(vec_madd( mRHSrow91, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux29, vec_mul(mRHSrow11, aux19)),
					vec_madd(mRHSrow41, aux49, vec_mul(mRHSrow31, aux39)) ),
				vec_add(
					vec_madd(mRHSrow61, aux69, vec_mul(mRHSrow51, aux59)),
					vec_madd(mRHSrow81, aux89, vec_mul(mRHSrow71, aux79)) ) ) ),

				0, mResult+4*16+8);

	vec_xst(vec_madd( mRHSrow92, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux29, vec_mul(mRHSrow12, aux19)),
					vec_madd(mRHSrow42, aux49, vec_mul(mRHSrow32, aux39)) ),
				vec_add(
					vec_madd(mRHSrow62, aux69, vec_mul(mRHSrow52, aux59)),
					vec_madd(mRHSrow82, aux89, vec_mul(mRHSrow72, aux79)) ) ) ),

				0, mResult+4*17+8);


	vector float mResultLastElem = 
		
		vec_madd( mRHSrow93, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux29, vec_mul(mRHSrow13, aux19)),
					vec_madd(mRHSrow43, aux49, vec_mul(mRHSrow33, aux39)) ),
				vec_add(
					vec_madd(mRHSrow63, aux69, vec_mul(mRHSrow53, aux59)),
					vec_madd(mRHSrow83, aux89, vec_mul(mRHSrow73, aux79)) ) ) );
	mResult[80] = mResultLastElem[0];
}






inline void mul12x12ColColFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHScol11, mLHScol12, mLHScol13, mLHScol21, mLHScol22, mLHScol23, mLHScol31, mLHScol32, mLHScol33,
	      	     mLHScol41, mLHScol42, mLHScol43, mLHScol51, mLHScol52, mLHScol53, mLHScol61, mLHScol62, mLHScol63,
		     mLHScol71, mLHScol72, mLHScol73, mLHScol81, mLHScol82, mLHScol83, mLHScol91, mLHScol92, mLHScol93, mLHScol101, mLHScol102, mLHScol103, mLHScol111,
		     mLHScol112, mLHScol113,  mLHScol121, mLHScol122, mLHScol123;

	vector float mRHScol11, mRHScol12, mRHScol13, mRHScol21, mRHScol22, mRHScol23, mRHScol31, mRHScol32, mRHScol33,
	      	     mRHScol41, mRHScol42, mRHScol43, mRHScol51, mRHScol52, mRHScol53, mRHScol61, mRHScol62, mRHScol63,
		     mRHScol71, mRHScol72, mRHScol73, mRHScol81, mRHScol82, mRHScol83, mRHScol91, mRHScol92, mRHScol93, mRHScol101, mRHScol102, mRHScol103, mRHScol111,
		     mRHScol112, mRHScol113,  mRHScol121, mRHScol122, mRHScol123;
//load


	mRHScol11 = vec_xl(0,mRHS);
	mRHScol12 = vec_xl(0,mRHS+4);
	mRHScol13 = vec_xl(0,mRHS+4*2);

	mRHScol21 = vec_xl(0,mRHS+4*3);
	mRHScol22 = vec_xl(0,mRHS+4*4);
	mRHScol23 = vec_xl(0,mRHS+4*5);

	mRHScol31 = vec_xl(0,mRHS+4*6);
	mRHScol32 = vec_xl(0,mRHS+4*7);
	mRHScol33 = vec_xl(0,mRHS+4*8);

	mRHScol41 = vec_xl(0,mRHS+4*9);
	mRHScol42 = vec_xl(0,mRHS+4*10);
	mRHScol43 = vec_xl(0,mRHS+4*11);

	mRHScol51 = vec_xl(0,mRHS+4*12);
	mRHScol52 = vec_xl(0,mRHS+4*13);
	mRHScol53 = vec_xl(0,mRHS+4*14);

	mRHScol61 = vec_xl(0,mRHS+4*15);
	mRHScol62 = vec_xl(0,mRHS+4*16);
	mRHScol63 = vec_xl(0,mRHS+4*17);

	mRHScol71 = vec_xl(0,mRHS+4*18);
	mRHScol72 = vec_xl(0,mRHS+4*19);
	mRHScol73 = vec_xl(0,mRHS+4*20);

	mRHScol81 = vec_xl(0,mRHS+4*21);
	mRHScol82 = vec_xl(0,mRHS+4*22);
	mRHScol83 = vec_xl(0,mRHS+4*23);

	mRHScol91 = vec_xl(0,mRHS+4*24);
	mRHScol92 = vec_xl(0,mRHS+4*25);
	mRHScol93 = vec_xl(0,mRHS+4*26);

	mRHScol101 = vec_xl(0,mRHS+4*27);
	mRHScol102 = vec_xl(0,mRHS+4*28);
	mRHScol103 = vec_xl(0,mRHS+4*29);

	mRHScol111 = vec_xl(0,mRHS+4*30);
	mRHScol112 = vec_xl(0,mRHS+4*31);
	mRHScol113 = vec_xl(0,mRHS+4*32);

	mRHScol121 = vec_xl(0,mRHS+4*33);
	mRHScol122 = vec_xl(0,mRHS+4*34);
	mRHScol123 = vec_xl(0,mRHS+4*35);

//transpose RHS
	vector float mRHSrow11 = {mRHScol11[0], mRHScol21[0], mRHScol31[0], mRHScol41[0]};	
	vector float mRHSrow12 = {mRHScol51[0], mRHScol61[0], mRHScol71[0], mRHScol81[0]};	
	vector float mRHSrow13 = {mRHScol91[0],mRHScol101[0],mRHScol111[0],mRHScol121[0]};	

	vector float mRHSrow21 = {mRHScol11[1], mRHScol21[1], mRHScol31[1], mRHScol41[1]};	
	vector float mRHSrow22 = {mRHScol51[1], mRHScol61[1], mRHScol71[1], mRHScol81[1]};	
	vector float mRHSrow23 = {mRHScol91[1],mRHScol101[1],mRHScol111[1],mRHScol121[1]};	

	vector float mRHSrow31 = {mRHScol11[2], mRHScol21[2], mRHScol31[2], mRHScol41[2]};	
	vector float mRHSrow32 = {mRHScol51[2], mRHScol61[2], mRHScol71[2], mRHScol81[2]};	
	vector float mRHSrow33 = {mRHScol91[2],mRHScol101[2],mRHScol111[2],mRHScol121[2]};	

	vector float mRHSrow41 = {mRHScol11[3], mRHScol21[3], mRHScol31[3], mRHScol41[3]};	
	vector float mRHSrow42 = {mRHScol51[3], mRHScol61[3], mRHScol71[3], mRHScol81[3]};	
	vector float mRHSrow43 = {mRHScol91[3],mRHScol101[3],mRHScol111[3],mRHScol121[3]};	

	vector float mRHSrow51 = {mRHScol12[0], mRHScol22[0], mRHScol32[0], mRHScol42[0]};	
	vector float mRHSrow52 = {mRHScol52[0], mRHScol62[0], mRHScol72[0], mRHScol82[0]};	
	vector float mRHSrow53 = {mRHScol92[0],mRHScol102[0],mRHScol112[0],mRHScol122[0]};	

	vector float mRHSrow61 = {mRHScol12[1], mRHScol22[1], mRHScol32[1], mRHScol42[1]};	
	vector float mRHSrow62 = {mRHScol52[1], mRHScol62[1], mRHScol72[1], mRHScol82[1]};	
	vector float mRHSrow63 = {mRHScol92[1],mRHScol102[1],mRHScol112[1],mRHScol122[1]};	

	vector float mRHSrow71 = {mRHScol12[2], mRHScol22[2], mRHScol32[2], mRHScol42[2]};	
	vector float mRHSrow72 = {mRHScol52[2], mRHScol62[2], mRHScol72[2], mRHScol82[2]};	
	vector float mRHSrow73 = {mRHScol92[2],mRHScol102[2],mRHScol112[2],mRHScol122[2]};	

	vector float mRHSrow81 = {mRHScol12[3], mRHScol22[3], mRHScol32[3], mRHScol42[3]};	
	vector float mRHSrow82 = {mRHScol52[3], mRHScol62[3], mRHScol72[3], mRHScol82[3]};	
	vector float mRHSrow83 = {mRHScol92[3],mRHScol102[3],mRHScol112[3],mRHScol122[3]};	

	vector float mRHSrow91 = {mRHScol13[0], mRHScol23[0], mRHScol33[0], mRHScol43[0]};	
	vector float mRHSrow92 = {mRHScol53[0], mRHScol63[0], mRHScol73[0], mRHScol83[0]};	
	vector float mRHSrow93 = {mRHScol93[0],mRHScol103[0],mRHScol113[0],mRHScol123[0]};	

	vector float mRHSrow101 = {mRHScol12[1], mRHScol22[1], mRHScol32[1], mRHScol42[1]};	
	vector float mRHSrow102 = {mRHScol52[1], mRHScol62[1], mRHScol72[1], mRHScol82[1]};	
	vector float mRHSrow103 = {mRHScol92[1],mRHScol102[1],mRHScol112[1],mRHScol122[1]};	

	vector float mRHSrow111 = {mRHScol12[2], mRHScol22[2], mRHScol32[2], mRHScol42[2]};	
	vector float mRHSrow112 = {mRHScol52[2], mRHScol62[2], mRHScol72[2], mRHScol82[2]};	
	vector float mRHSrow113 = {mRHScol92[2],mRHScol102[2],mRHScol112[2],mRHScol122[2]};	

	vector float mRHSrow121 = {mRHScol12[3], mRHScol22[3], mRHScol32[3], mRHScol42[3]};	
	vector float mRHSrow122 = {mRHScol52[3], mRHScol62[3], mRHScol72[3], mRHScol82[3]};	
	vector float mRHSrow123 = {mRHScol92[3],mRHScol102[3],mRHScol112[3],mRHScol122[3]};	




	//--------------------------------------------------
	mLHScol11 = vec_xl(0,mLHS);
	mLHScol12 = vec_xl(0,mLHS+4);
	mLHScol13 = vec_xl(0,mLHS+4*2);

	mLHScol21 = vec_xl(0,mLHS+4*3);
	mLHScol22 = vec_xl(0,mLHS+4*4);
	mLHScol23 = vec_xl(0,mLHS+4*5);

	mLHScol31 = vec_xl(0,mLHS+4*6);
	mLHScol32 = vec_xl(0,mLHS+4*7);
	mLHScol33 = vec_xl(0,mLHS+4*8);

	mLHScol41 = vec_xl(0,mLHS+4*9);
	mLHScol42 = vec_xl(0,mLHS+4*10);
	mLHScol43 = vec_xl(0,mLHS+4*11);

	mLHScol51 = vec_xl(0,mLHS+4*12);
	mLHScol52 = vec_xl(0,mLHS+4*13);
	mLHScol53 = vec_xl(0,mLHS+4*14);

	mLHScol61 = vec_xl(0,mLHS+4*15);
	mLHScol62 = vec_xl(0,mLHS+4*16);
	mLHScol63 = vec_xl(0,mLHS+4*17);

	mLHScol71 = vec_xl(0,mLHS+4*18);
	mLHScol72 = vec_xl(0,mLHS+4*19);
	mLHScol73 = vec_xl(0,mLHS+4*20);

	mLHScol81 = vec_xl(0,mLHS+4*21);
	mLHScol82 = vec_xl(0,mLHS+4*22);
	mLHScol83 = vec_xl(0,mLHS+4*23);

	mLHScol91 = vec_xl(0,mLHS+4*24);
	mLHScol92 = vec_xl(0,mLHS+4*25);
	mLHScol93 = vec_xl(0,mLHS+4*26);

	mLHScol101 = vec_xl(0,mLHS+4*27);
	mLHScol102 = vec_xl(0,mLHS+4*28);
	mLHScol103 = vec_xl(0,mLHS+4*29);

	mLHScol111 = vec_xl(0,mLHS+4*30);
	mLHScol112 = vec_xl(0,mLHS+4*31);
	mLHScol113 = vec_xl(0,mLHS+4*32);

	mLHScol121 = vec_xl(0,mLHS+4*33);
	mLHScol122 = vec_xl(0,mLHS+4*34);
	mLHScol123 = vec_xl(0,mLHS+4*35);

//-------------------------------------------------------------------------

	vector float aux11={mLHScol11[0],mLHScol11[0],mLHScol11[0],mLHScol11[0]};
	vector float aux12={mLHScol11[1],mLHScol11[1],mLHScol11[1],mLHScol11[1]};
	vector float aux13={mLHScol11[2],mLHScol11[2],mLHScol11[2],mLHScol11[2]};
	vector float aux14={mLHScol11[3],mLHScol11[3],mLHScol11[3],mLHScol11[3]};

	vector float aux15={mLHScol12[0],mLHScol12[0],mLHScol12[0],mLHScol12[0]};
	vector float aux16={mLHScol12[1],mLHScol12[1],mLHScol12[1],mLHScol12[1]};
	vector float aux17={mLHScol12[2],mLHScol12[2],mLHScol12[2],mLHScol12[2]};
	vector float aux18={mLHScol12[3],mLHScol12[3],mLHScol12[3],mLHScol12[3]};

	vector float aux19= {mLHScol13[0],mLHScol13[0],mLHScol13[0],mLHScol13[0]};
	vector float aux110={mLHScol13[1],mLHScol13[1],mLHScol13[1],mLHScol13[1]};
	vector float aux0111={mLHScol13[2],mLHScol13[2],mLHScol13[2],mLHScol13[2]};
	vector float aux0112={mLHScol13[3],mLHScol13[3],mLHScol13[3],mLHScol13[3]};

//-------------------------------------------------------------------------
	vector float aux21= {mLHScol21[0],mLHScol21[0],mLHScol21[0],mLHScol21[0]};
	vector float aux22= {mLHScol21[1],mLHScol21[1],mLHScol21[1],mLHScol21[1]};
	vector float aux23= {mLHScol21[2],mLHScol21[2],mLHScol21[2],mLHScol21[2]};
	vector float aux24= {mLHScol21[3],mLHScol21[3],mLHScol21[3],mLHScol21[3]};

	vector float aux25= {mLHScol22[0],mLHScol22[0],mLHScol22[0],mLHScol22[0]};
	vector float aux26= {mLHScol22[1],mLHScol22[1],mLHScol22[1],mLHScol22[1]};
	vector float aux27= {mLHScol22[2],mLHScol22[2],mLHScol22[2],mLHScol22[2]};
	vector float aux28= {mLHScol22[3],mLHScol22[3],mLHScol22[3],mLHScol22[3]};

	vector float aux29= {mLHScol23[0],mLHScol23[0],mLHScol23[0],mLHScol23[0]};
	vector float aux210={mLHScol23[1],mLHScol23[1],mLHScol23[1],mLHScol23[1]};
	vector float aux211={mLHScol23[2],mLHScol23[2],mLHScol23[2],mLHScol23[2]};
	vector float aux212={mLHScol23[3],mLHScol23[3],mLHScol23[3],mLHScol23[3]};

//-------------------------------------------------------------------------
	vector float aux31= {mLHScol31[0],mLHScol31[0],mLHScol31[0],mLHScol31[0]};
	vector float aux32= {mLHScol31[1],mLHScol31[1],mLHScol31[1],mLHScol31[1]};
	vector float aux33= {mLHScol31[2],mLHScol31[2],mLHScol31[2],mLHScol31[2]};
	vector float aux34= {mLHScol31[3],mLHScol31[3],mLHScol31[3],mLHScol31[3]};

	vector float aux35= {mLHScol32[0],mLHScol32[0],mLHScol32[0],mLHScol32[0]};
	vector float aux36= {mLHScol32[1],mLHScol32[1],mLHScol32[1],mLHScol32[1]};
	vector float aux37= {mLHScol32[2],mLHScol32[2],mLHScol32[2],mLHScol32[2]};
	vector float aux38= {mLHScol32[3],mLHScol32[3],mLHScol32[3],mLHScol32[3]};

	vector float aux39= {mLHScol33[0],mLHScol33[0],mLHScol33[0],mLHScol33[0]};
	vector float aux310={mLHScol33[1],mLHScol33[1],mLHScol33[1],mLHScol33[1]};
	vector float aux311={mLHScol33[2],mLHScol33[2],mLHScol33[2],mLHScol33[2]};
	vector float aux312={mLHScol33[3],mLHScol33[3],mLHScol33[3],mLHScol33[3]};

//-------------------------------------------------------------------------
	vector float aux41= {mLHScol41[0],mLHScol41[0],mLHScol41[0],mLHScol41[0]};
	vector float aux42= {mLHScol41[1],mLHScol41[1],mLHScol41[1],mLHScol41[1]};
	vector float aux43= {mLHScol41[2],mLHScol41[2],mLHScol41[2],mLHScol41[2]};
	vector float aux44= {mLHScol41[3],mLHScol41[3],mLHScol41[3],mLHScol41[3]};

	vector float aux45= {mLHScol42[0],mLHScol42[0],mLHScol42[0],mLHScol42[0]};
	vector float aux46= {mLHScol42[1],mLHScol42[1],mLHScol42[1],mLHScol42[1]};
	vector float aux47= {mLHScol42[2],mLHScol42[2],mLHScol42[2],mLHScol42[2]};
	vector float aux48= {mLHScol42[3],mLHScol42[3],mLHScol42[3],mLHScol42[3]};

	vector float aux49= {mLHScol43[0],mLHScol43[0],mLHScol43[0],mLHScol43[0]};
	vector float aux410={mLHScol43[1],mLHScol43[1],mLHScol43[1],mLHScol43[1]};
	vector float aux411={mLHScol43[2],mLHScol43[2],mLHScol43[2],mLHScol43[2]};
	vector float aux412={mLHScol43[3],mLHScol43[3],mLHScol43[3],mLHScol43[3]};

//-------------------------------------------------------------------------
	vector float aux51= {mLHScol51[0],mLHScol51[0],mLHScol51[0],mLHScol51[0]};
	vector float aux52= {mLHScol51[1],mLHScol51[1],mLHScol51[1],mLHScol51[1]};
	vector float aux53= {mLHScol51[2],mLHScol51[2],mLHScol51[2],mLHScol51[2]};
	vector float aux54= {mLHScol51[3],mLHScol51[3],mLHScol51[3],mLHScol51[3]};

	vector float aux55= {mLHScol52[0],mLHScol52[0],mLHScol52[0],mLHScol52[0]};
	vector float aux56= {mLHScol52[1],mLHScol52[1],mLHScol52[1],mLHScol52[1]};
	vector float aux57= {mLHScol52[2],mLHScol52[2],mLHScol52[2],mLHScol52[2]};
	vector float aux58= {mLHScol52[3],mLHScol52[3],mLHScol52[3],mLHScol52[3]};

	vector float aux59= {mLHScol53[0],mLHScol53[0],mLHScol53[0],mLHScol53[0]};
	vector float aux510={mLHScol53[1],mLHScol53[1],mLHScol53[1],mLHScol53[1]};
	vector float aux511={mLHScol53[2],mLHScol53[2],mLHScol53[2],mLHScol53[2]};
	vector float aux512={mLHScol53[3],mLHScol53[3],mLHScol53[3],mLHScol53[3]};
//-------------------------------------------------------------------------
	vector float aux61= {mLHScol61[0],mLHScol61[0],mLHScol61[0],mLHScol61[0]};
	vector float aux62= {mLHScol61[1],mLHScol61[1],mLHScol61[1],mLHScol61[1]};
	vector float aux63= {mLHScol61[2],mLHScol61[2],mLHScol61[2],mLHScol61[2]};
	vector float aux64= {mLHScol61[3],mLHScol61[3],mLHScol61[3],mLHScol61[3]};

	vector float aux65= {mLHScol62[0],mLHScol62[0],mLHScol62[0],mLHScol62[0]};
	vector float aux66= {mLHScol62[1],mLHScol62[1],mLHScol62[1],mLHScol62[1]};
	vector float aux67= {mLHScol62[2],mLHScol62[2],mLHScol62[2],mLHScol62[2]};
	vector float aux68= {mLHScol62[3],mLHScol62[3],mLHScol62[3],mLHScol62[3]};

	vector float aux69= {mLHScol63[0],mLHScol63[0],mLHScol63[0],mLHScol63[0]};
	vector float aux610={mLHScol63[1],mLHScol63[1],mLHScol63[1],mLHScol63[1]};
	vector float aux611={mLHScol63[2],mLHScol63[2],mLHScol63[2],mLHScol63[2]};
	vector float aux612={mLHScol63[3],mLHScol63[3],mLHScol63[3],mLHScol63[3]};
//-------------------------------------------------------------------------
	vector float aux71= {mLHScol71[0],mLHScol71[0],mLHScol71[0],mLHScol71[0]};
	vector float aux72= {mLHScol71[1],mLHScol71[1],mLHScol71[1],mLHScol71[1]};
	vector float aux73= {mLHScol71[2],mLHScol71[2],mLHScol71[2],mLHScol71[2]};
	vector float aux74= {mLHScol71[3],mLHScol71[3],mLHScol71[3],mLHScol71[3]};

	vector float aux75= {mLHScol72[0],mLHScol72[0],mLHScol72[0],mLHScol72[0]};
	vector float aux76= {mLHScol72[1],mLHScol72[1],mLHScol72[1],mLHScol72[1]};
	vector float aux77= {mLHScol72[2],mLHScol72[2],mLHScol72[2],mLHScol72[2]};
	vector float aux78= {mLHScol72[3],mLHScol72[3],mLHScol72[3],mLHScol72[3]};

	vector float aux79= {mLHScol73[0],mLHScol73[0],mLHScol73[0],mLHScol73[0]};
	vector float aux710={mLHScol73[1],mLHScol73[1],mLHScol73[1],mLHScol73[1]};
	vector float aux711={mLHScol73[2],mLHScol73[2],mLHScol73[2],mLHScol73[2]};
	vector float aux712={mLHScol73[3],mLHScol73[3],mLHScol73[3],mLHScol73[3]};
//-------------------------------------------------------------------------
	vector float aux81= {mLHScol81[0],mLHScol81[0],mLHScol81[0],mLHScol81[0]};
	vector float aux82= {mLHScol81[1],mLHScol81[1],mLHScol81[1],mLHScol81[1]};
	vector float aux83= {mLHScol81[2],mLHScol81[2],mLHScol81[2],mLHScol81[2]};
	vector float aux84= {mLHScol81[3],mLHScol81[3],mLHScol81[3],mLHScol81[3]};

	vector float aux85= {mLHScol82[0],mLHScol82[0],mLHScol82[0],mLHScol82[0]};
	vector float aux86= {mLHScol82[1],mLHScol82[1],mLHScol82[1],mLHScol82[1]};
	vector float aux87= {mLHScol82[2],mLHScol82[2],mLHScol82[2],mLHScol82[2]};
	vector float aux88= {mLHScol82[3],mLHScol82[3],mLHScol82[3],mLHScol82[3]};

	vector float aux89= {mLHScol83[0],mLHScol83[0],mLHScol83[0],mLHScol83[0]};
	vector float aux810={mLHScol83[1],mLHScol83[1],mLHScol83[1],mLHScol83[1]};
	vector float aux811={mLHScol83[2],mLHScol83[2],mLHScol83[2],mLHScol83[2]};
	vector float aux812={mLHScol83[3],mLHScol83[3],mLHScol83[3],mLHScol83[3]};
//-------------------------------------------------------------------------
	vector float aux91= {mLHScol91[0],mLHScol91[0],mLHScol91[0],mLHScol91[0]};
	vector float aux92= {mLHScol91[1],mLHScol91[1],mLHScol91[1],mLHScol91[1]};
	vector float aux93= {mLHScol91[2],mLHScol91[2],mLHScol91[2],mLHScol91[2]};
	vector float aux94= {mLHScol91[3],mLHScol91[3],mLHScol91[3],mLHScol91[3]};

	vector float aux95= {mLHScol92[0],mLHScol92[0],mLHScol92[0],mLHScol92[0]};
	vector float aux96= {mLHScol92[1],mLHScol92[1],mLHScol92[1],mLHScol92[1]};
	vector float aux97= {mLHScol92[2],mLHScol92[2],mLHScol92[2],mLHScol92[2]};
	vector float aux98= {mLHScol92[3],mLHScol92[3],mLHScol92[3],mLHScol92[3]};

	vector float aux99= {mLHScol93[0],mLHScol93[0],mLHScol93[0],mLHScol93[0]};
	vector float aux910={mLHScol93[1],mLHScol93[1],mLHScol93[1],mLHScol93[1]};
	vector float aux911={mLHScol93[2],mLHScol93[2],mLHScol93[2],mLHScol93[2]};
	vector float aux912={mLHScol93[3],mLHScol93[3],mLHScol93[3],mLHScol93[3]};
//-------------------------------------------------------------------------
	vector float aux101= {mLHScol101[0],mLHScol101[0],mLHScol101[0],mLHScol101[0]};
	vector float aux102= {mLHScol101[1],mLHScol101[1],mLHScol101[1],mLHScol101[1]};
	vector float aux103= {mLHScol101[2],mLHScol101[2],mLHScol101[2],mLHScol101[2]};
	vector float aux104= {mLHScol101[3],mLHScol101[3],mLHScol101[3],mLHScol101[3]};

	vector float aux105= {mLHScol102[0],mLHScol102[0],mLHScol102[0],mLHScol102[0]};
	vector float aux106= {mLHScol102[1],mLHScol102[1],mLHScol102[1],mLHScol102[1]};
	vector float aux107= {mLHScol102[2],mLHScol102[2],mLHScol102[2],mLHScol102[2]};
	vector float aux108= {mLHScol102[3],mLHScol102[3],mLHScol102[3],mLHScol102[3]};

	vector float aux109= {mLHScol103[0],mLHScol103[0],mLHScol103[0],mLHScol103[0]};
	vector float aux1010={mLHScol103[1],mLHScol103[1],mLHScol103[1],mLHScol103[1]};
	vector float aux1011={mLHScol103[2],mLHScol103[2],mLHScol103[2],mLHScol103[2]};
	vector float aux1012={mLHScol103[3],mLHScol103[3],mLHScol103[3],mLHScol103[3]};
//-------------------------------------------------------------------------
	vector float aux111= {mLHScol111[0],mLHScol111[0],mLHScol111[0],mLHScol111[0]};
	vector float aux112= {mLHScol111[1],mLHScol111[1],mLHScol111[1],mLHScol111[1]};
	vector float aux113= {mLHScol111[2],mLHScol111[2],mLHScol111[2],mLHScol111[2]};
	vector float aux114= {mLHScol111[3],mLHScol111[3],mLHScol111[3],mLHScol111[3]};

	vector float aux115= {mLHScol112[0],mLHScol112[0],mLHScol112[0],mLHScol112[0]};
	vector float aux116= {mLHScol112[1],mLHScol112[1],mLHScol112[1],mLHScol112[1]};
	vector float aux117= {mLHScol112[2],mLHScol112[2],mLHScol112[2],mLHScol112[2]};
	vector float aux118= {mLHScol112[3],mLHScol112[3],mLHScol112[3],mLHScol112[3]};

	vector float aux119= {mLHScol113[0],mLHScol113[0],mLHScol113[0],mLHScol113[0]};
	vector float aux1110={mLHScol113[1],mLHScol113[1],mLHScol113[1],mLHScol113[1]};
	vector float aux1111={mLHScol113[2],mLHScol113[2],mLHScol113[2],mLHScol113[2]};
	vector float aux1112={mLHScol113[3],mLHScol113[3],mLHScol113[3],mLHScol113[3]};
//-------------------------------------------------------------------------
	vector float aux121= {mLHScol121[0],mLHScol121[0],mLHScol121[0],mLHScol121[0]};
	vector float aux122= {mLHScol121[1],mLHScol121[1],mLHScol121[1],mLHScol121[1]};
	vector float aux123= {mLHScol121[2],mLHScol121[2],mLHScol121[2],mLHScol121[2]};
	vector float aux124= {mLHScol121[3],mLHScol121[3],mLHScol121[3],mLHScol121[3]};

	vector float aux125= {mLHScol122[0],mLHScol122[0],mLHScol122[0],mLHScol122[0]};
	vector float aux126= {mLHScol122[1],mLHScol122[1],mLHScol122[1],mLHScol122[1]};
	vector float aux127= {mLHScol122[2],mLHScol122[2],mLHScol122[2],mLHScol122[2]};
	vector float aux128= {mLHScol122[3],mLHScol122[3],mLHScol122[3],mLHScol122[3]};

	vector float aux129= {mLHScol123[0],mLHScol123[0],mLHScol123[0],mLHScol123[0]};
	vector float aux1210={mLHScol123[1],mLHScol123[1],mLHScol123[1],mLHScol123[1]};
	vector float aux1211={mLHScol123[2],mLHScol123[2],mLHScol123[2],mLHScol123[2]};
	vector float aux1212={mLHScol123[3],mLHScol123[3],mLHScol123[3],mLHScol123[3]};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
		//row 1 of result
	vec_xst(vec_madd(aux121, mRHSrow121, vec_madd(aux111, mRHSrow111, vec_madd(aux101, mRHSrow101, vec_madd(aux91, mRHSrow91, vec_madd(aux81, mRHSrow81, vec_madd(aux71, mRHSrow71, vec_madd(aux61, mRHSrow61, vec_madd(aux51, mRHSrow51, vec_madd(aux41, mRHSrow41, vec_madd(aux31, mRHSrow31, vec_madd(aux21, mRHSrow21, vec_mul(aux11, mRHSrow11)))))))))))), 0, mResult);
	vec_xst(vec_madd(aux121, mRHSrow122, vec_madd(aux111, mRHSrow112, vec_madd(aux101, mRHSrow102, vec_madd(aux91, mRHSrow92, vec_madd(aux81, mRHSrow82, vec_madd(aux71, mRHSrow72, vec_madd(aux61, mRHSrow62, vec_madd(aux51, mRHSrow52, vec_madd(aux41, mRHSrow42, vec_madd(aux31, mRHSrow32, vec_madd(aux21, mRHSrow22, vec_mul(aux11, mRHSrow12)))))))))))), 0, mResult + 4);
	vec_xst(vec_madd(aux121, mRHSrow123, vec_madd(aux111, mRHSrow113, vec_madd(aux101, mRHSrow103, vec_madd(aux91, mRHSrow93, vec_madd(aux81, mRHSrow83, vec_madd(aux71, mRHSrow73, vec_madd(aux61, mRHSrow63, vec_madd(aux51, mRHSrow53, vec_madd(aux41, mRHSrow43, vec_madd(aux31, mRHSrow33, vec_madd(aux21, mRHSrow23, vec_mul(aux11, mRHSrow13)))))))))))), 0, mResult + 4*2);

	//row 2 of result
	vec_xst(vec_madd(aux122, mRHSrow121, vec_madd(aux112, mRHSrow111, vec_madd(aux102, mRHSrow101, vec_madd(aux92, mRHSrow91, vec_madd(aux82, mRHSrow81, vec_madd(aux72, mRHSrow71, vec_madd(aux62, mRHSrow61, vec_madd(aux52, mRHSrow51, vec_madd(aux42, mRHSrow41, vec_madd(aux32, mRHSrow31, vec_madd(aux22, mRHSrow21, vec_mul(aux12, mRHSrow11)))))))))))), 0, mResult + 4*3);
	vec_xst(vec_madd(aux122, mRHSrow122, vec_madd(aux112, mRHSrow112, vec_madd(aux102, mRHSrow102, vec_madd(aux92, mRHSrow92, vec_madd(aux82, mRHSrow82, vec_madd(aux72, mRHSrow72, vec_madd(aux62, mRHSrow62, vec_madd(aux52, mRHSrow52, vec_madd(aux42, mRHSrow42, vec_madd(aux32, mRHSrow32, vec_madd(aux22, mRHSrow22, vec_mul(aux12, mRHSrow12)))))))))))), 0, mResult + 4*4);
	vec_xst(vec_madd(aux122, mRHSrow123, vec_madd(aux112, mRHSrow113, vec_madd(aux102, mRHSrow103, vec_madd(aux92, mRHSrow93, vec_madd(aux82, mRHSrow83, vec_madd(aux72, mRHSrow73, vec_madd(aux62, mRHSrow63, vec_madd(aux52, mRHSrow53, vec_madd(aux42, mRHSrow43, vec_madd(aux32, mRHSrow33, vec_madd(aux22, mRHSrow23, vec_mul(aux12, mRHSrow13)))))))))))), 0, mResult + 4*5);

	// row 3 of mResult

	vec_xst(vec_madd(aux123, mRHSrow121, vec_madd(aux113, mRHSrow111, vec_madd(aux103, mRHSrow101, vec_madd(aux93, mRHSrow91, vec_madd(aux83, mRHSrow81, vec_madd(aux73, mRHSrow71, vec_madd(aux63, mRHSrow61, vec_madd(aux53, mRHSrow51, vec_madd(aux43, mRHSrow41, vec_madd(aux33, mRHSrow31, vec_madd(aux23, mRHSrow21, vec_mul(aux13, mRHSrow11)))))))))))), 0, mResult + 4*6);
	vec_xst(vec_madd(aux123, mRHSrow122, vec_madd(aux113, mRHSrow112, vec_madd(aux103, mRHSrow102, vec_madd(aux93, mRHSrow92, vec_madd(aux83, mRHSrow82, vec_madd(aux73, mRHSrow72, vec_madd(aux63, mRHSrow62, vec_madd(aux53, mRHSrow52, vec_madd(aux43, mRHSrow42, vec_madd(aux33, mRHSrow32, vec_madd(aux23, mRHSrow22, vec_mul(aux13, mRHSrow12)))))))))))), 0, mResult + 4*7);
	vec_xst(vec_madd(aux123, mRHSrow123, vec_madd(aux113, mRHSrow113, vec_madd(aux103, mRHSrow103, vec_madd(aux93, mRHSrow93, vec_madd(aux83, mRHSrow83, vec_madd(aux73, mRHSrow73, vec_madd(aux63, mRHSrow63, vec_madd(aux53, mRHSrow53, vec_madd(aux43, mRHSrow43, vec_madd(aux33, mRHSrow33, vec_madd(aux23, mRHSrow23, vec_mul(aux13, mRHSrow13)))))))))))), 0, mResult + 4*8);
	
	// row 4 of mResult
	vec_xst(vec_madd(aux124, mRHSrow121, vec_madd(aux114, mRHSrow111, vec_madd(aux104, mRHSrow101, vec_madd(aux94, mRHSrow91, vec_madd(aux84, mRHSrow81, vec_madd(aux74, mRHSrow71, vec_madd(aux64, mRHSrow61, vec_madd(aux54, mRHSrow51, vec_madd(aux44, mRHSrow41, vec_madd(aux34, mRHSrow31, vec_madd(aux24, mRHSrow21, vec_mul(aux14, mRHSrow11)))))))))))), 0, mResult + 4*9);
	vec_xst(vec_madd(aux124, mRHSrow122, vec_madd(aux114, mRHSrow112, vec_madd(aux104, mRHSrow102, vec_madd(aux94, mRHSrow92, vec_madd(aux84, mRHSrow82, vec_madd(aux74, mRHSrow72, vec_madd(aux64, mRHSrow62, vec_madd(aux54, mRHSrow52, vec_madd(aux44, mRHSrow42, vec_madd(aux34, mRHSrow32, vec_madd(aux24, mRHSrow22, vec_mul(aux14, mRHSrow12)))))))))))), 0, mResult + 4*10);
	vec_xst(vec_madd(aux124, mRHSrow123, vec_madd(aux114, mRHSrow113, vec_madd(aux104, mRHSrow103, vec_madd(aux94, mRHSrow93, vec_madd(aux84, mRHSrow83, vec_madd(aux74, mRHSrow73, vec_madd(aux64, mRHSrow63, vec_madd(aux54, mRHSrow53, vec_madd(aux44, mRHSrow43, vec_madd(aux34, mRHSrow33, vec_madd(aux24, mRHSrow23, vec_mul(aux14, mRHSrow13)))))))))))), 0, mResult + 4*11);
	
	// row 5 of mResult
	vec_xst(vec_madd(aux125, mRHSrow121, vec_madd(aux115, mRHSrow111, vec_madd(aux105, mRHSrow101, vec_madd(aux95, mRHSrow91, vec_madd(aux85, mRHSrow81, vec_madd(aux75, mRHSrow71, vec_madd(aux65, mRHSrow61, vec_madd(aux55, mRHSrow51, vec_madd(aux45, mRHSrow41, vec_madd(aux35, mRHSrow31, vec_madd(aux25, mRHSrow21, vec_mul(aux15, mRHSrow11)))))))))))), 0, mResult + 4*12);
	vec_xst(vec_madd(aux125, mRHSrow122, vec_madd(aux115, mRHSrow112, vec_madd(aux105, mRHSrow102, vec_madd(aux95, mRHSrow92, vec_madd(aux85, mRHSrow82, vec_madd(aux75, mRHSrow72, vec_madd(aux65, mRHSrow62, vec_madd(aux55, mRHSrow52, vec_madd(aux45, mRHSrow42, vec_madd(aux35, mRHSrow32, vec_madd(aux25, mRHSrow22, vec_mul(aux15, mRHSrow12)))))))))))), 0, mResult + 4*13);
	vec_xst(vec_madd(aux125, mRHSrow123, vec_madd(aux115, mRHSrow113, vec_madd(aux105, mRHSrow103, vec_madd(aux95, mRHSrow93, vec_madd(aux85, mRHSrow83, vec_madd(aux75, mRHSrow73, vec_madd(aux65, mRHSrow63, vec_madd(aux55, mRHSrow53, vec_madd(aux45, mRHSrow43, vec_madd(aux35, mRHSrow33, vec_madd(aux25, mRHSrow23, vec_mul(aux15, mRHSrow13)))))))))))), 0, mResult + 4*14);
	
	// row 6 of mResult
	vec_xst(vec_madd(aux126, mRHSrow121, vec_madd(aux116, mRHSrow111, vec_madd(aux106, mRHSrow101, vec_madd(aux96, mRHSrow91, vec_madd(aux86, mRHSrow81, vec_madd(aux76, mRHSrow71, vec_madd(aux66, mRHSrow61, vec_madd(aux56, mRHSrow51, vec_madd(aux46, mRHSrow41, vec_madd(aux36, mRHSrow31, vec_madd(aux26, mRHSrow21, vec_mul(aux16, mRHSrow11)))))))))))), 0, mResult + 4*15);
	vec_xst(vec_madd(aux126, mRHSrow122, vec_madd(aux116, mRHSrow112, vec_madd(aux106, mRHSrow102, vec_madd(aux96, mRHSrow92, vec_madd(aux86, mRHSrow82, vec_madd(aux76, mRHSrow72, vec_madd(aux66, mRHSrow62, vec_madd(aux56, mRHSrow52, vec_madd(aux46, mRHSrow42, vec_madd(aux36, mRHSrow32, vec_madd(aux26, mRHSrow22, vec_mul(aux16, mRHSrow12)))))))))))), 0, mResult + 4*16);
	vec_xst(vec_madd(aux126, mRHSrow123, vec_madd(aux116, mRHSrow113, vec_madd(aux106, mRHSrow103, vec_madd(aux96, mRHSrow93, vec_madd(aux86, mRHSrow83, vec_madd(aux76, mRHSrow73, vec_madd(aux66, mRHSrow63, vec_madd(aux56, mRHSrow53, vec_madd(aux46, mRHSrow43, vec_madd(aux36, mRHSrow33, vec_madd(aux26, mRHSrow23, vec_mul(aux16, mRHSrow13)))))))))))), 0, mResult + 4*17);
	
	// row 7 of mResult
	vec_xst(vec_madd(aux127, mRHSrow121, vec_madd(aux117, mRHSrow111, vec_madd(aux107, mRHSrow101, vec_madd(aux97, mRHSrow91, vec_madd(aux87, mRHSrow81, vec_madd(aux77, mRHSrow71, vec_madd(aux67, mRHSrow61, vec_madd(aux57, mRHSrow51, vec_madd(aux47, mRHSrow41, vec_madd(aux37, mRHSrow31, vec_madd(aux27, mRHSrow21, vec_mul(aux17, mRHSrow11)))))))))))), 0, mResult + 4*18);
	vec_xst(vec_madd(aux127, mRHSrow122, vec_madd(aux117, mRHSrow112, vec_madd(aux107, mRHSrow102, vec_madd(aux97, mRHSrow92, vec_madd(aux87, mRHSrow82, vec_madd(aux77, mRHSrow72, vec_madd(aux67, mRHSrow62, vec_madd(aux57, mRHSrow52, vec_madd(aux47, mRHSrow42, vec_madd(aux37, mRHSrow32, vec_madd(aux27, mRHSrow22, vec_mul(aux17, mRHSrow12)))))))))))), 0, mResult + 4*19);
	vec_xst(vec_madd(aux127, mRHSrow123, vec_madd(aux117, mRHSrow113, vec_madd(aux107, mRHSrow103, vec_madd(aux97, mRHSrow93, vec_madd(aux87, mRHSrow83, vec_madd(aux77, mRHSrow73, vec_madd(aux67, mRHSrow63, vec_madd(aux57, mRHSrow53, vec_madd(aux47, mRHSrow43, vec_madd(aux37, mRHSrow33, vec_madd(aux27, mRHSrow23, vec_mul(aux17, mRHSrow13)))))))))))), 0, mResult + 4*20);
	
	// row 8 of mResult
	vec_xst(vec_madd(aux128, mRHSrow121, vec_madd(aux118, mRHSrow111, vec_madd(aux108, mRHSrow101, vec_madd(aux98, mRHSrow91, vec_madd(aux88, mRHSrow81, vec_madd(aux78, mRHSrow71, vec_madd(aux68, mRHSrow61, vec_madd(aux58, mRHSrow51, vec_madd(aux48, mRHSrow41, vec_madd(aux38, mRHSrow31, vec_madd(aux28, mRHSrow21, vec_mul(aux18, mRHSrow11)))))))))))), 0, mResult + 4*21);
	vec_xst(vec_madd(aux128, mRHSrow122, vec_madd(aux118, mRHSrow112, vec_madd(aux108, mRHSrow102, vec_madd(aux98, mRHSrow92, vec_madd(aux88, mRHSrow82, vec_madd(aux78, mRHSrow72, vec_madd(aux68, mRHSrow62, vec_madd(aux58, mRHSrow52, vec_madd(aux48, mRHSrow42, vec_madd(aux38, mRHSrow32, vec_madd(aux28, mRHSrow22, vec_mul(aux18, mRHSrow12)))))))))))), 0, mResult + 4*22);
	vec_xst(vec_madd(aux128, mRHSrow123, vec_madd(aux118, mRHSrow113, vec_madd(aux108, mRHSrow103, vec_madd(aux98, mRHSrow93, vec_madd(aux88, mRHSrow83, vec_madd(aux78, mRHSrow73, vec_madd(aux68, mRHSrow63, vec_madd(aux58, mRHSrow53, vec_madd(aux48, mRHSrow43, vec_madd(aux38, mRHSrow33, vec_madd(aux28, mRHSrow23, vec_mul(aux18, mRHSrow13)))))))))))), 0, mResult + 4*23);
	
	// row 9 of mResult
	vec_xst(vec_madd(aux129, mRHSrow121, vec_madd(aux119, mRHSrow111, vec_madd(aux109, mRHSrow101, vec_madd(aux99, mRHSrow91, vec_madd(aux89, mRHSrow81, vec_madd(aux79, mRHSrow71, vec_madd(aux69, mRHSrow61, vec_madd(aux59, mRHSrow51, vec_madd(aux49, mRHSrow41, vec_madd(aux39, mRHSrow31, vec_madd(aux29, mRHSrow21, vec_mul(aux19, mRHSrow11)))))))))))), 0, mResult + 4*24);
	vec_xst(vec_madd(aux129, mRHSrow122, vec_madd(aux119, mRHSrow112, vec_madd(aux109, mRHSrow102, vec_madd(aux99, mRHSrow92, vec_madd(aux89, mRHSrow82, vec_madd(aux79, mRHSrow72, vec_madd(aux69, mRHSrow62, vec_madd(aux59, mRHSrow52, vec_madd(aux49, mRHSrow42, vec_madd(aux39, mRHSrow32, vec_madd(aux29, mRHSrow22, vec_mul(aux19, mRHSrow12)))))))))))), 0, mResult + 4*25);
	vec_xst(vec_madd(aux129, mRHSrow123, vec_madd(aux119, mRHSrow113, vec_madd(aux109, mRHSrow103, vec_madd(aux99, mRHSrow93, vec_madd(aux89, mRHSrow83, vec_madd(aux79, mRHSrow73, vec_madd(aux69, mRHSrow63, vec_madd(aux59, mRHSrow53, vec_madd(aux49, mRHSrow43, vec_madd(aux39, mRHSrow33, vec_madd(aux29, mRHSrow23, vec_mul(aux19, mRHSrow13)))))))))))), 0, mResult + 4*26);
	
	// row 10 of mResult
	vec_xst(vec_madd(aux1210, mRHSrow121, vec_madd(aux1110, mRHSrow111, vec_madd(aux1010, mRHSrow101, vec_madd(aux910, mRHSrow91, vec_madd(aux810, mRHSrow81, vec_madd(aux710, mRHSrow71, vec_madd(aux610, mRHSrow61, vec_madd(aux510, mRHSrow51, vec_madd(aux410, mRHSrow41, vec_madd(aux310, mRHSrow31, vec_madd(aux210, mRHSrow21, vec_mul(aux110, mRHSrow11)))))))))))), 0, mResult + 4*27);
	vec_xst(vec_madd(aux1210, mRHSrow122, vec_madd(aux1110, mRHSrow112, vec_madd(aux1010, mRHSrow102, vec_madd(aux910, mRHSrow92, vec_madd(aux810, mRHSrow82, vec_madd(aux710, mRHSrow72, vec_madd(aux610, mRHSrow62, vec_madd(aux510, mRHSrow52, vec_madd(aux410, mRHSrow42, vec_madd(aux310, mRHSrow32, vec_madd(aux210, mRHSrow22, vec_mul(aux110, mRHSrow12)))))))))))), 0, mResult + 4*28);
	vec_xst(vec_madd(aux1210, mRHSrow123, vec_madd(aux1110, mRHSrow113, vec_madd(aux1010, mRHSrow103, vec_madd(aux910, mRHSrow93, vec_madd(aux810, mRHSrow83, vec_madd(aux710, mRHSrow73, vec_madd(aux610, mRHSrow63, vec_madd(aux510, mRHSrow53, vec_madd(aux410, mRHSrow43, vec_madd(aux310, mRHSrow33, vec_madd(aux210, mRHSrow23, vec_mul(aux110, mRHSrow13)))))))))))), 0, mResult + 4*29);
	

	// row 11 of mResult
	vec_xst(vec_madd(aux1211, mRHSrow121, vec_madd(aux1111, mRHSrow111, vec_madd(aux1011, mRHSrow101, vec_madd(aux911, mRHSrow91, vec_madd(aux811, mRHSrow81, vec_madd(aux711, mRHSrow71, vec_madd(aux611, mRHSrow61, vec_madd(aux511, mRHSrow51, vec_madd(aux411, mRHSrow41, vec_madd(aux311, mRHSrow31, vec_madd(aux211, mRHSrow21, vec_mul(aux0111, mRHSrow11)))))))))))), 0, mResult + 4*30);
	vec_xst(vec_madd(aux1211, mRHSrow122, vec_madd(aux1111, mRHSrow112, vec_madd(aux1011, mRHSrow102, vec_madd(aux911, mRHSrow92, vec_madd(aux811, mRHSrow82, vec_madd(aux711, mRHSrow72, vec_madd(aux611, mRHSrow62, vec_madd(aux511, mRHSrow52, vec_madd(aux411, mRHSrow42, vec_madd(aux311, mRHSrow32, vec_madd(aux211, mRHSrow22, vec_mul(aux0111, mRHSrow12)))))))))))), 0, mResult + 4*31);
	vec_xst(vec_madd(aux1211, mRHSrow123, vec_madd(aux1111, mRHSrow113, vec_madd(aux1011, mRHSrow103, vec_madd(aux911, mRHSrow93, vec_madd(aux811, mRHSrow83, vec_madd(aux711, mRHSrow73, vec_madd(aux611, mRHSrow63, vec_madd(aux511, mRHSrow53, vec_madd(aux411, mRHSrow43, vec_madd(aux311, mRHSrow33, vec_madd(aux211, mRHSrow23, vec_mul(aux0111, mRHSrow13)))))))))))), 0, mResult + 4*32);
	
	// row 12 of mResult
	vec_xst(vec_madd(aux1212, mRHSrow121, vec_madd(aux1112, mRHSrow111, vec_madd(aux1012, mRHSrow101, vec_madd(aux912, mRHSrow91, vec_madd(aux812, mRHSrow81, vec_madd(aux712, mRHSrow71, vec_madd(aux612, mRHSrow61, vec_madd(aux512, mRHSrow51, vec_madd(aux412, mRHSrow41, vec_madd(aux312, mRHSrow31, vec_madd(aux212, mRHSrow21, vec_mul(aux0112, mRHSrow11)))))))))))), 0, mResult + 4*33);
	vec_xst(vec_madd(aux1212, mRHSrow122, vec_madd(aux1112, mRHSrow112, vec_madd(aux1012, mRHSrow102, vec_madd(aux912, mRHSrow92, vec_madd(aux812, mRHSrow82, vec_madd(aux712, mRHSrow72, vec_madd(aux612, mRHSrow62, vec_madd(aux512, mRHSrow52, vec_madd(aux412, mRHSrow42, vec_madd(aux312, mRHSrow32, vec_madd(aux212, mRHSrow22, vec_mul(aux0112, mRHSrow12)))))))))))), 0, mResult + 4*34);
	vec_xst(vec_madd(aux1212, mRHSrow123, vec_madd(aux1112, mRHSrow113, vec_madd(aux1012, mRHSrow103, vec_madd(aux912, mRHSrow93, vec_madd(aux812, mRHSrow83, vec_madd(aux712, mRHSrow73, vec_madd(aux612, mRHSrow63, vec_madd(aux512, mRHSrow53, vec_madd(aux412, mRHSrow43, vec_madd(aux312, mRHSrow33, vec_madd(aux212, mRHSrow23, vec_mul(aux0112, mRHSrow13)))))))))))), 0, mResult + 4*35);
	

}
//row x col

inline void mul4x4RowColFloat(const float* mLHS, const float* mRHS, float* const mResult){
	
	vector float mLHSrow1,mLHSrow2,mLHSrow3,mLHSrow4;
	vector float mRHScol1,mRHScol2,mRHScol3,mRHScol4;


	//====================================================
	
	mRHScol1 = vec_xl(0,mRHS);
	mRHScol2 = vec_xl(0,mRHS+4);
	mRHScol3 = vec_xl(0,mRHS+4*2);
	mRHScol4 = vec_xl(0,mRHS+4*3);

	mLHSrow1 = vec_xl(0,mLHS);
	mLHSrow2 = vec_xl(0,mLHS+4);
	mLHSrow3 = vec_xl(0,mLHS+4*2);
	mLHSrow4 = vec_xl(0,mLHS+4*3);

	//transpose RHS
	vector float mRHSrow1 = {mRHScol1[0],mRHScol2[0],mRHScol3[0],mRHScol4[0]};
	vector float mRHSrow2 = {mRHScol1[1],mRHScol2[1],mRHScol3[1],mRHScol4[1]};
	vector float mRHSrow3 = {mRHScol1[2],mRHScol2[2],mRHScol3[2],mRHScol4[2]};
	vector float mRHSrow4 = {mRHScol1[3],mRHScol2[3],mRHScol3[3],mRHScol4[3]};


	//splat==============================================
	
	vector float auxLHS11 = {mLHSrow1[0],mLHSrow1[0],mLHSrow1[0],mLHSrow1[0]};
	vector float auxLHS12 = {mLHSrow2[0],mLHSrow2[0],mLHSrow2[0],mLHSrow2[0]};
	vector float auxLHS13 = {mLHSrow3[0],mLHSrow3[0],mLHSrow3[0],mLHSrow3[0]};
	vector float auxLHS14 = {mLHSrow4[0],mLHSrow4[0],mLHSrow4[0],mLHSrow4[0]};
	
	vector float auxLHS21 = {mLHSrow1[1],mLHSrow1[1],mLHSrow1[1],mLHSrow1[1]};
	vector float auxLHS22 = {mLHSrow2[1],mLHSrow2[1],mLHSrow2[1],mLHSrow2[1]};
	vector float auxLHS23 = {mLHSrow3[1],mLHSrow3[1],mLHSrow3[1],mLHSrow3[1]};
	vector float auxLHS24 = {mLHSrow4[1],mLHSrow4[1],mLHSrow4[1],mLHSrow4[1]};
	
	vector float auxLHS31 = {mLHSrow1[2],mLHSrow1[2],mLHSrow1[2],mLHSrow1[2]};
	vector float auxLHS32 = {mLHSrow2[2],mLHSrow2[2],mLHSrow2[2],mLHSrow2[2]};
	vector float auxLHS33 = {mLHSrow3[2],mLHSrow3[2],mLHSrow3[2],mLHSrow3[2]};
	vector float auxLHS34 = {mLHSrow4[2],mLHSrow4[2],mLHSrow4[2],mLHSrow4[2]};
	
	vector float auxLHS41 = {mLHSrow1[3],mLHSrow1[3],mLHSrow1[3],mLHSrow1[3]};
	vector float auxLHS42 = {mLHSrow2[3],mLHSrow2[3],mLHSrow2[3],mLHSrow2[3]};
	vector float auxLHS43 = {mLHSrow3[3],mLHSrow3[3],mLHSrow3[3],mLHSrow3[3]};
	vector float auxLHS44 = {mLHSrow4[3],mLHSrow4[3],mLHSrow4[3],mLHSrow4[3]};
	

 	//row 1 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS11,mRHSrow1),vec_mul(auxLHS12,mRHSrow2)),
	vec_add(vec_mul(auxLHS13,mRHSrow3),vec_mul(auxLHS14,mRHSrow4))),0,
	mResult
	);

	//row 2 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS21,mRHSrow1),vec_mul(auxLHS22,mRHSrow2)),
	vec_add(vec_mul(auxLHS23,mRHSrow3),vec_mul(auxLHS24,mRHSrow4))),0,mResult+4
	);

	//row 3
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS31,mRHSrow1),vec_mul(auxLHS32,mRHSrow2)),
	vec_add(vec_mul(auxLHS33,mRHSrow3),vec_mul(auxLHS34,mRHSrow4))),0,mResult+8
	);

	//row 4
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS41,mRHSrow1),vec_mul(auxLHS42,mRHSrow2)),
	vec_add(vec_mul(auxLHS43,mRHSrow3),vec_mul(auxLHS44,mRHSrow4))),0,mResult+12
	);



}



inline void mul9x9RowColFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHSrow11, mLHSrow12, mLHSrow13, mLHSrow21, mLHSrow22, mLHSrow23, mLHSrow31, mLHSrow32, mLHSrow33,
	      	     mLHSrow41, mLHSrow42, mLHSrow43, mLHSrow51, mLHSrow52, mLHSrow53, mLHSrow61, mLHSrow62, mLHSrow63,
		     mLHSrow71, mLHSrow72, mLHSrow73, mLHSrow81, mLHSrow82, mLHSrow83, mLHSrow91, mLHSrow92, mLHSrow93;

	vector float mRHScol11, mRHScol12, mRHScol13, mRHScol21, mRHScol22, mRHScol23, mRHScol31, mRHScol32, mRHScol33,
	      	     mRHScol41, mRHScol42, mRHScol43, mRHScol51, mRHScol52, mRHScol53, mRHScol61, mRHScol62, mRHScol63,
		     mRHScol71, mRHScol72, mRHScol73, mRHScol81, mRHScol82, mRHScol83, mRHScol91, mRHScol92, mRHScol93;

//load
// __8__17__26__35__44__53__62__71__80


	mLHSrow11 = vec_xl(0,mLHS);
	mLHSrow12 = vec_xl(0,mLHS+4);
	mLHSrow13 = vec_splats((float)0);
	mLHSrow13[0] = mLHS[8];

	mLHSrow21 = vec_xl(0,mLHS+4*2+1);
	mLHSrow22 = vec_xl(0,mLHS+4*3+1);
	mLHSrow23 = vec_splats((float)0);
	mLHSrow23[0] = mLHS[17];

	mLHSrow31 = vec_xl(0,mLHS+4*4+2);
	mLHSrow32 = vec_xl(0,mLHS+4*5+2);
	mLHSrow33 = vec_splats((float)0);
	mLHSrow33[0] = mLHS[26];

	mLHSrow41 = vec_xl(0,mLHS+4*6+3);
	mLHSrow42 = vec_xl(0,mLHS+4*7+3);
	mLHSrow43 = vec_splats((float)0);
	mLHSrow43[0] = mLHS[35];

	mLHSrow51 = vec_xl(0,mLHS+4*8+4);
	mLHSrow52 = vec_xl(0,mLHS+4*9+4);
	mLHSrow53 = vec_splats((float)0);
	mLHSrow53[0] = mLHS[44];

	mLHSrow61 = vec_xl(0,mLHS+4*10+5);
	mLHSrow62 = vec_xl(0,mLHS+4*11+5);
	mLHSrow63 = vec_splats((float)0);
	mLHSrow63[0] = mLHS[53];
	
	mLHSrow71 = vec_xl(0,mLHS+4*12+6);
	mLHSrow72 = vec_xl(0,mLHS+4*13+6);
	mLHSrow73 = vec_splats((float)0);
	mLHSrow73[0] = mLHS[62];

	mLHSrow81 = vec_xl(0,mLHS+4*14+7);
	mLHSrow82 = vec_xl(0,mLHS+4*15+7);
	mLHSrow83 = vec_splats((float)0);
	mLHSrow83[0] = mLHS[71];

	mLHSrow91 = vec_xl(0,mLHS+4*16+8);
	mLHSrow92 = vec_xl(0,mLHS+4*17+8);
	mLHSrow93 = vec_splats((float)0);
	mLHSrow93[0] = mLHS[80];
//-----------------------------------------------------

	mRHScol11 = vec_xl(0,mRHS);
	mRHScol12 = vec_xl(0,mRHS+4);

	mRHScol21 = vec_xl(0,mRHS+4*2+1);
	mRHScol22 = vec_xl(0,mRHS+4*3+1);

	mRHScol31 = vec_xl(0,mRHS+4*4+2);
	mRHScol32 = vec_xl(0,mRHS+4*5+2);

	mRHScol41 = vec_xl(0,mRHS+4*6+3);
	mRHScol42 = vec_xl(0,mRHS+4*7+3);

	mRHScol51 = vec_xl(0,mRHS+4*8+4);
	mRHScol52 = vec_xl(0,mRHS+4*9+4);

	mRHScol61 = vec_xl(0,mRHS+4*10+5);
	mRHScol62 = vec_xl(0,mRHS+4*11+5);
	
	mRHScol71 = vec_xl(0,mRHS+4*12+6);
	mRHScol72 = vec_xl(0,mRHS+4*13+6);

	mRHScol81 = vec_xl(0,mRHS+4*14+7);
	mRHScol82 = vec_xl(0,mRHS+4*15+7);

	mRHScol91 = vec_xl(0,mRHS+4*16+8);
	mRHScol92 = vec_xl(0,mRHS+4*17+8);


// transpose RHS

	vector float mRHSrow11 = {mRHScol11[0],mRHScol21[0],mRHScol31[0],mRHScol41[0]};
	vector float mRHSrow12 = {mRHScol51[0],mRHScol61[0],mRHScol71[0],mRHScol81[0]};
	vector float mRHSrow13 = {mRHScol91[0],0,0,0};

	vector float mRHSrow21 = {mRHScol11[1],mRHScol21[1],mRHScol31[1],mRHScol41[1]};
	vector float mRHSrow22 = {mRHScol51[1],mRHScol61[1],mRHScol71[1],mRHScol81[1]};
	vector float mRHSrow23 = {mRHScol91[1],0,0,0};

	vector float mRHSrow31 = {mRHScol11[2],mRHScol21[2],mRHScol31[2],mRHScol41[2]};
	vector float mRHSrow32 = {mRHScol51[2],mRHScol61[2],mRHScol71[2],mRHScol81[2]};
	vector float mRHSrow33 = {mRHScol91[2],0,0,0};

	vector float mRHSrow41 = {mRHScol11[3],mRHScol21[3],mRHScol31[3],mRHScol41[3]};
	vector float mRHSrow42 = {mRHScol51[3],mRHScol61[3],mRHScol71[3],mRHScol81[3]};
	vector float mRHSrow43 = {mRHScol91[3],0,0,0};

	vector float mRHSrow51 = {mRHScol12[0],mRHScol22[0],mRHScol32[0],mRHScol42[0]};
	vector float mRHSrow52 = {mRHScol52[0],mRHScol62[0],mRHScol72[0],mRHScol82[0]};
	vector float mRHSrow53 = {mRHScol92[0],0,0,0};

	vector float mRHSrow61 = {mRHScol12[1],mRHScol22[1],mRHScol32[1],mRHScol42[1]};
	vector float mRHSrow62 = {mRHScol12[1],mRHScol62[1],mRHScol72[1],mRHScol82[1]};
	vector float mRHSrow63 = {mRHScol12[1],0,0,0};

	vector float mRHSrow71 = {mRHScol12[2],mRHScol22[2],mRHScol32[2],mRHScol42[2]};
	vector float mRHSrow72 = {mRHScol52[2],mRHScol62[2],mRHScol72[2],mRHScol82[2]};
	vector float mRHSrow73 = {mRHScol92[2],0,0,0};

	vector float mRHSrow81 = {mRHScol12[3],mRHScol22[3],mRHScol32[3],mRHScol42[3]};
	vector float mRHSrow82 = {mRHScol52[3],mRHScol62[3],mRHScol72[3],mRHScol82[3]};
	vector float mRHSrow83 = {mRHScol92[3],0,0,0};

	vector float mRHSrow91 = {mRHS[8],mRHS[17],mRHS[26],mRHS[35]};
	vector float mRHSrow92 = {mRHS[44],mRHS[53],mRHS[62],mRHS[71]};
	vector float mRHSrow93 = {mRHS[80],0,0,0};



//===================================================================================
//Splat
//===================================================================================
	
	vector float aux11={mLHSrow11[0],mLHSrow11[0],mLHSrow11[0],mLHSrow11[0]};
	vector float aux12={mLHSrow21[0],mLHSrow21[0],mLHSrow21[0],mLHSrow21[0]};
	vector float aux13={mLHSrow31[0],mLHSrow31[0],mLHSrow31[0],mLHSrow31[0]};
	vector float aux14={mLHSrow41[0],mLHSrow41[0],mLHSrow41[0],mLHSrow41[0]};

	vector float aux15={mLHSrow51[0],mLHSrow51[0],mLHSrow51[0],mLHSrow51[0]};
	vector float aux16={mLHSrow61[0],mLHSrow61[0],mLHSrow61[0],mLHSrow61[0]};
	vector float aux17={mLHSrow71[0],mLHSrow71[0],mLHSrow71[0],mLHSrow71[0]};
	vector float aux18={mLHSrow81[0],mLHSrow81[0],mLHSrow81[0],mLHSrow81[0]};
	
	vector float aux19={mLHSrow91[0],mLHSrow91[0],mLHSrow91[0],mLHSrow91[0]};
//----------------------------------------------------------------------------------
	vector float aux21={mLHSrow11[1],mLHSrow11[1],mLHSrow11[1],mLHSrow11[1]};
	vector float aux22={mLHSrow21[1],mLHSrow21[1],mLHSrow21[1],mLHSrow21[1]};
	vector float aux23={mLHSrow31[1],mLHSrow31[1],mLHSrow31[1],mLHSrow31[1]};
	vector float aux24={mLHSrow41[1],mLHSrow41[1],mLHSrow41[1],mLHSrow41[1]};

	vector float aux25={mLHSrow51[1],mLHSrow51[1],mLHSrow51[1],mLHSrow51[1]};
	vector float aux26={mLHSrow61[1],mLHSrow61[1],mLHSrow61[1],mLHSrow61[1]};
	vector float aux27={mLHSrow71[1],mLHSrow71[1],mLHSrow71[1],mLHSrow71[1]};
	vector float aux28={mLHSrow81[1],mLHSrow81[1],mLHSrow81[1],mLHSrow81[1]};
	
	vector float aux29={mLHSrow91[1],mLHSrow91[1],mLHSrow91[1],mLHSrow91[1]};
//----------------------------------------------------------------------------------
	vector float aux31={mLHSrow11[2],mLHSrow11[2],mLHSrow11[2],mLHSrow11[2]};
	vector float aux32={mLHSrow21[2],mLHSrow21[2],mLHSrow21[2],mLHSrow21[2]};
	vector float aux33={mLHSrow31[2],mLHSrow31[2],mLHSrow31[2],mLHSrow31[2]};
	vector float aux34={mLHSrow41[2],mLHSrow41[2],mLHSrow41[2],mLHSrow41[2]};

	vector float aux35={mLHSrow51[2],mLHSrow51[2],mLHSrow51[2],mLHSrow51[2]};
	vector float aux36={mLHSrow61[2],mLHSrow61[2],mLHSrow61[2],mLHSrow61[2]};
	vector float aux37={mLHSrow71[2],mLHSrow71[2],mLHSrow71[2],mLHSrow71[2]};
	vector float aux38={mLHSrow81[2],mLHSrow81[2],mLHSrow81[2],mLHSrow81[2]};
	
	vector float aux39={mLHSrow91[2],mLHSrow91[2],mLHSrow91[2],mLHSrow91[2]};
//----------------------------------------------------------------------------------
	vector float aux41={mLHSrow11[3],mLHSrow11[3],mLHSrow11[3],mLHSrow11[3]};
	vector float aux42={mLHSrow21[3],mLHSrow21[3],mLHSrow21[3],mLHSrow21[3]};
	vector float aux43={mLHSrow31[3],mLHSrow31[3],mLHSrow31[3],mLHSrow31[3]};
	vector float aux44={mLHSrow41[3],mLHSrow41[3],mLHSrow41[3],mLHSrow41[3]};

	vector float aux45={mLHSrow51[3],mLHSrow51[3],mLHSrow51[3],mLHSrow51[3]};
	vector float aux46={mLHSrow61[3],mLHSrow61[3],mLHSrow61[3],mLHSrow61[3]};
	vector float aux47={mLHSrow71[3],mLHSrow71[3],mLHSrow71[3],mLHSrow71[3]};
	vector float aux48={mLHSrow81[3],mLHSrow81[3],mLHSrow81[3],mLHSrow81[3]};
	
	vector float aux49={mLHSrow91[3],mLHSrow91[3],mLHSrow91[3],mLHSrow91[3]};
//----------------------------------------------------------------------------------
	vector float aux51={mLHSrow12[0],mLHSrow12[0],mLHSrow12[0],mLHSrow12[0]};
	vector float aux52={mLHSrow22[0],mLHSrow22[0],mLHSrow22[0],mLHSrow22[0]};
	vector float aux53={mLHSrow32[0],mLHSrow32[0],mLHSrow32[0],mLHSrow32[0]};
	vector float aux54={mLHSrow42[0],mLHSrow42[0],mLHSrow42[0],mLHSrow42[0]};

	vector float aux55={mLHSrow52[0],mLHSrow52[0],mLHSrow52[0],mLHSrow52[0]};
	vector float aux56={mLHSrow62[0],mLHSrow62[0],mLHSrow62[0],mLHSrow62[0]};
	vector float aux57={mLHSrow72[0],mLHSrow72[0],mLHSrow72[0],mLHSrow72[0]};
	vector float aux58={mLHSrow82[0],mLHSrow82[0],mLHSrow82[0],mLHSrow82[0]};
	
	vector float aux59={mLHSrow92[0],mLHSrow92[0],mLHSrow92[0],mLHSrow92[0]};
//----------------------------------------------------------------------------------
	vector float aux61={mLHSrow12[1],mLHSrow12[1],mLHSrow12[1],mLHSrow12[1]};
	vector float aux62={mLHSrow22[1],mLHSrow22[1],mLHSrow22[1],mLHSrow22[1]};
	vector float aux63={mLHSrow32[1],mLHSrow32[1],mLHSrow32[1],mLHSrow32[1]};
	vector float aux64={mLHSrow42[1],mLHSrow42[1],mLHSrow42[1],mLHSrow42[1]};

	vector float aux65={mLHSrow52[1],mLHSrow52[1],mLHSrow52[1],mLHSrow52[1]};
	vector float aux66={mLHSrow62[1],mLHSrow62[1],mLHSrow62[1],mLHSrow62[1]};
	vector float aux67={mLHSrow72[1],mLHSrow72[1],mLHSrow72[1],mLHSrow72[1]};
	vector float aux68={mLHSrow82[1],mLHSrow82[1],mLHSrow82[1],mLHSrow82[1]};
	
	vector float aux69={mLHSrow92[1],mLHSrow92[1],mLHSrow92[1],mLHSrow92[1]};
//----------------------------------------------------------------------------------
	vector float aux71={mLHSrow12[2],mLHSrow12[2],mLHSrow12[2],mLHSrow12[2]};
	vector float aux72={mLHSrow22[2],mLHSrow22[2],mLHSrow22[2],mLHSrow22[2]};
	vector float aux73={mLHSrow32[2],mLHSrow32[2],mLHSrow32[2],mLHSrow32[2]};
	vector float aux74={mLHSrow42[2],mLHSrow42[2],mLHSrow42[2],mLHSrow42[2]};

	vector float aux75={mLHSrow52[2],mLHSrow52[2],mLHSrow52[2],mLHSrow52[2]};
	vector float aux76={mLHSrow62[2],mLHSrow62[2],mLHSrow62[2],mLHSrow62[2]};
	vector float aux77={mLHSrow72[2],mLHSrow72[2],mLHSrow72[2],mLHSrow72[2]};
	vector float aux78={mLHSrow82[2],mLHSrow82[2],mLHSrow82[2],mLHSrow82[2]};
	
	vector float aux79={mLHSrow92[2],mLHSrow92[2],mLHSrow92[2],mLHSrow92[2]};
//----------------------------------------------------------------------------------
	vector float aux81={mLHSrow12[3],mLHSrow12[3],mLHSrow12[3],mLHSrow12[3]};
	vector float aux82={mLHSrow22[3],mLHSrow22[3],mLHSrow22[3],mLHSrow22[3]};
	vector float aux83={mLHSrow32[3],mLHSrow32[3],mLHSrow32[3],mLHSrow32[3]};
	vector float aux84={mLHSrow42[3],mLHSrow42[3],mLHSrow42[3],mLHSrow42[3]};

	vector float aux85={mLHSrow52[3],mLHSrow52[3],mLHSrow52[3],mLHSrow52[3]};
	vector float aux86={mLHSrow62[3],mLHSrow62[3],mLHSrow62[3],mLHSrow62[3]};
	vector float aux87={mLHSrow72[3],mLHSrow72[3],mLHSrow72[3],mLHSrow72[3]};
	vector float aux88={mLHSrow82[3],mLHSrow82[3],mLHSrow82[3],mLHSrow82[3]};
	
	vector float aux89={mLHSrow92[3],mLHSrow92[3],mLHSrow92[3],mLHSrow92[3]};
//----------------------------------------------------------------------------------
	vector float aux91={mLHSrow13[0],mLHSrow13[0],mLHSrow13[0],mLHSrow13[0]};
	vector float aux92={mLHSrow23[0],mLHSrow23[0],mLHSrow23[0],mLHSrow23[0]};
	vector float aux93={mLHSrow33[0],mLHSrow33[0],mLHSrow33[0],mLHSrow33[0]};
	vector float aux94={mLHSrow43[0],mLHSrow43[0],mLHSrow43[0],mLHSrow43[0]};

	vector float aux95={mLHSrow53[0],mLHSrow53[0],mLHSrow53[0],mLHSrow53[0]};
	vector float aux96={mLHSrow63[0],mLHSrow63[0],mLHSrow63[0],mLHSrow63[0]};
	vector float aux97={mLHSrow73[0],mLHSrow73[0],mLHSrow73[0],mLHSrow73[0]};
	vector float aux98={mLHSrow83[0],mLHSrow83[0],mLHSrow83[0],mLHSrow83[0]};
	
	vector float aux99={mLHSrow93[0],mLHSrow93[0],mLHSrow93[0],mLHSrow93[0]};
//----------------------------------------------------------------------------------


//row1
	vec_xst(vec_madd( mRHSrow91, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux21, vec_mul(mRHSrow11, aux11)),
					vec_madd(mRHSrow41, aux41, vec_mul(mRHSrow31, aux31)) ),
				vec_add(
					vec_madd(mRHSrow61, aux61, vec_mul(mRHSrow51, aux51)),
					vec_madd(mRHSrow81, aux81, vec_mul(mRHSrow71, aux71)) ) ) ),

				0, mResult);	

	
	vec_xst(vec_madd( mRHSrow92, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux21, vec_mul(mRHSrow12, aux11)),
					vec_madd(mRHSrow42, aux41, vec_mul(mRHSrow32, aux31)) ),
				vec_add(
					vec_madd(mRHSrow62, aux61, vec_mul(mRHSrow52, aux51)),
					vec_madd(mRHSrow82, aux81, vec_mul(mRHSrow72, aux71)) ) ) ),

				0, mResult+4);

	vec_xst(vec_madd( mRHSrow93, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux21, vec_mul(mRHSrow13, aux11)),
					vec_madd(mRHSrow43, aux41, vec_mul(mRHSrow33, aux31)) ),
				vec_add(
					vec_madd(mRHSrow63, aux61, vec_mul(mRHSrow53, aux51)),
					vec_madd(mRHSrow83, aux81, vec_mul(mRHSrow73, aux71)) ) ) ),

				0, mResult+8);	
//row 2


	vec_xst(vec_madd( mRHSrow91, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux22, vec_mul(mRHSrow11, aux12)),
					vec_madd(mRHSrow41, aux42, vec_mul(mRHSrow31, aux32)) ),
				vec_add(
					vec_madd(mRHSrow61, aux62, vec_mul(mRHSrow51, aux52)),
					vec_madd(mRHSrow81, aux82, vec_mul(mRHSrow71, aux72)) ) ) ),

				0, mResult+4*2+1);

	vec_xst(vec_madd( mRHSrow92, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux22, vec_mul(mRHSrow12, aux12)),
					vec_madd(mRHSrow42, aux42, vec_mul(mRHSrow32, aux32)) ),
				vec_add(
					vec_madd(mRHSrow62, aux62, vec_mul(mRHSrow52, aux52)),
					vec_madd(mRHSrow82, aux82, vec_mul(mRHSrow72, aux72)) ) ) ),

				0, mResult+4*3+1);


	vec_xst(vec_madd( mRHSrow93, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux22, vec_mul(mRHSrow13, aux12)),
					vec_madd(mRHSrow43, aux42, vec_mul(mRHSrow33, aux32)) ),
				vec_add(
					vec_madd(mRHSrow63, aux62, vec_mul(mRHSrow53, aux52)),
					vec_madd(mRHSrow83, aux82, vec_mul(mRHSrow73, aux72)) ) ) ),

				0, mResult+17);

//row 3

	vec_xst(vec_madd( mRHSrow91, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux23, vec_mul(mRHSrow11, aux13)),
					vec_madd(mRHSrow41, aux43, vec_mul(mRHSrow31, aux33)) ),
				vec_add(
					vec_madd(mRHSrow61, aux63, vec_mul(mRHSrow51, aux53)),
					vec_madd(mRHSrow81, aux83, vec_mul(mRHSrow71, aux73)) ) ) ),

				0, mResult+4*4+2);

	vec_xst(vec_madd( mRHSrow92, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux23, vec_mul(mRHSrow12, aux13)),
					vec_madd(mRHSrow42, aux43, vec_mul(mRHSrow32, aux33)) ),
				vec_add(
					vec_madd(mRHSrow62, aux63, vec_mul(mRHSrow52, aux53)),
					vec_madd(mRHSrow82, aux83, vec_mul(mRHSrow72, aux73)) ) ) ),

				0, mResult+4*5+2);


	vec_xst(vec_madd( mRHSrow93, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux23, vec_mul(mRHSrow13, aux13)),
					vec_madd(mRHSrow43, aux43, vec_mul(mRHSrow33, aux33)) ),
				vec_add(
					vec_madd(mRHSrow63, aux63, vec_mul(mRHSrow53, aux53)),
					vec_madd(mRHSrow83, aux83, vec_mul(mRHSrow73, aux73)) ) ) ),

				0, mResult+26);
//row 4


	vec_xst(vec_madd( mRHSrow91, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux24, vec_mul(mRHSrow11, aux14)),
					vec_madd(mRHSrow41, aux44, vec_mul(mRHSrow31, aux34)) ),
				vec_add(
					vec_madd(mRHSrow61, aux64, vec_mul(mRHSrow51, aux54)),
					vec_madd(mRHSrow81, aux84, vec_mul(mRHSrow71, aux74)) ) ) ),

				0, mResult+4*6+3);

	vec_xst(vec_madd( mRHSrow92, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux24, vec_mul(mRHSrow12, aux14)),
					vec_madd(mRHSrow42, aux44, vec_mul(mRHSrow32, aux34)) ),
				vec_add(
					vec_madd(mRHSrow62, aux64, vec_mul(mRHSrow52, aux54)),
					vec_madd(mRHSrow82, aux84, vec_mul(mRHSrow72, aux74)) ) ) ),

				0, mResult+4*7+3);

	vec_xst(vec_madd( mRHSrow93, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux24, vec_mul(mRHSrow13, aux14)),
					vec_madd(mRHSrow43, aux44, vec_mul(mRHSrow33, aux34)) ),
				vec_add(
					vec_madd(mRHSrow63, aux64, vec_mul(mRHSrow53, aux54)),
					vec_madd(mRHSrow83, aux84, vec_mul(mRHSrow73, aux74)) ) ) ),

				0, mResult+35);
//row 5


	vec_xst(vec_madd( mRHSrow91, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux25, vec_mul(mRHSrow11, aux15)),
					vec_madd(mRHSrow41, aux45, vec_mul(mRHSrow31, aux35)) ),
				vec_add(
					vec_madd(mRHSrow61, aux65, vec_mul(mRHSrow51, aux55)),
					vec_madd(mRHSrow81, aux85, vec_mul(mRHSrow71, aux75)) ) ) ),

				0, mResult+4*8+4);



	vec_xst(vec_madd( mRHSrow92, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux25, vec_mul(mRHSrow12, aux15)),
					vec_madd(mRHSrow42, aux45, vec_mul(mRHSrow32, aux35)) ),
				vec_add(
					vec_madd(mRHSrow62, aux65, vec_mul(mRHSrow52, aux55)),
					vec_madd(mRHSrow82, aux85, vec_mul(mRHSrow72, aux75)) ) ) ),

				0, mResult+4*9+4);


	vec_xst(vec_madd( mRHSrow93, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux25, vec_mul(mRHSrow13, aux15)),
					vec_madd(mRHSrow43, aux45, vec_mul(mRHSrow33, aux35)) ),
				vec_add(
					vec_madd(mRHSrow63, aux65, vec_mul(mRHSrow53, aux55)),
					vec_madd(mRHSrow83, aux85, vec_mul(mRHSrow73, aux75)) ) ) ),

				0, mResult+44);

//row 6


	vec_xst(vec_madd( mRHSrow91, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux26, vec_mul(mRHSrow11, aux16)),
					vec_madd(mRHSrow41, aux46, vec_mul(mRHSrow31, aux36)) ),
				vec_add(
					vec_madd(mRHSrow61, aux66, vec_mul(mRHSrow51, aux56)),
					vec_madd(mRHSrow81, aux86, vec_mul(mRHSrow71, aux76)) ) ) ),

				0, mResult+4*10+5);


	vec_xst(vec_madd( mRHSrow92, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux26, vec_mul(mRHSrow12, aux16)),
					vec_madd(mRHSrow42, aux46, vec_mul(mRHSrow32, aux36)) ),
				vec_add(
					vec_madd(mRHSrow62, aux66, vec_mul(mRHSrow52, aux56)),
					vec_madd(mRHSrow82, aux86, vec_mul(mRHSrow72, aux76)) ) ) ),

				0, mResult+4*11+5);


	vec_xst(vec_madd( mRHSrow93, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux26, vec_mul(mRHSrow13, aux16)),
					vec_madd(mRHSrow43, aux46, vec_mul(mRHSrow33, aux36)) ),
				vec_add(
					vec_madd(mRHSrow63, aux66, vec_mul(mRHSrow53, aux56)),
					vec_madd(mRHSrow83, aux86, vec_mul(mRHSrow73, aux76)) ) ) ),

				0, mResult+53);

//row 7

	vec_xst(vec_madd( mRHSrow91, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux27, vec_mul(mRHSrow11, aux17)),
					vec_madd(mRHSrow41, aux47, vec_mul(mRHSrow31, aux37)) ),
				vec_add(
					vec_madd(mRHSrow61, aux67, vec_mul(mRHSrow51, aux57)),
					vec_madd(mRHSrow81, aux87, vec_mul(mRHSrow71, aux77)) ) ) ),

				0, mResult+4*12+6);

	vec_xst(vec_madd( mRHSrow92, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux27, vec_mul(mRHSrow12, aux17)),
					vec_madd(mRHSrow42, aux47, vec_mul(mRHSrow32, aux37)) ),
				vec_add(
					vec_madd(mRHSrow62, aux67, vec_mul(mRHSrow52, aux57)),
					vec_madd(mRHSrow82, aux87, vec_mul(mRHSrow72, aux77)) ) ) ),

				0, mResult+4*13+6);


	vec_xst(vec_madd( mRHSrow93, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux27, vec_mul(mRHSrow13, aux17)),
					vec_madd(mRHSrow43, aux47, vec_mul(mRHSrow33, aux37)) ),
				vec_add(
					vec_madd(mRHSrow63, aux67, vec_mul(mRHSrow53, aux57)),
					vec_madd(mRHSrow83, aux87, vec_mul(mRHSrow73, aux77)) ) ) ),

				0, mResult+62);
//row 8



	vec_xst(vec_madd( mRHSrow91, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux28, vec_mul(mRHSrow11, aux18)),
					vec_madd(mRHSrow41, aux48, vec_mul(mRHSrow31, aux38)) ),
				vec_add(
					vec_madd(mRHSrow61, aux68, vec_mul(mRHSrow51, aux58)),
					vec_madd(mRHSrow81, aux88, vec_mul(mRHSrow71, aux78)) ) ) ),

				0, mResult+4*14+7);


	vec_xst(vec_madd( mRHSrow92, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux28, vec_mul(mRHSrow12, aux18)),
					vec_madd(mRHSrow42, aux48, vec_mul(mRHSrow32, aux38)) ),
				vec_add(
					vec_madd(mRHSrow62, aux68, vec_mul(mRHSrow52, aux58)),
					vec_madd(mRHSrow82, aux88, vec_mul(mRHSrow72, aux78)) ) ) ),

				0, mResult+4*15+7);


	vec_xst(vec_madd( mRHSrow93, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux28, vec_mul(mRHSrow13, aux18)),
					vec_madd(mRHSrow43, aux48, vec_mul(mRHSrow33, aux38)) ),
				vec_add(
					vec_madd(mRHSrow63, aux68, vec_mul(mRHSrow53, aux58)),
					vec_madd(mRHSrow83, aux88, vec_mul(mRHSrow73, aux78)) ) ) ),

				0, mResult+71);

//row 9


	vec_xst(vec_madd( mRHSrow91, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux29, vec_mul(mRHSrow11, aux19)),
					vec_madd(mRHSrow41, aux49, vec_mul(mRHSrow31, aux39)) ),
				vec_add(
					vec_madd(mRHSrow61, aux69, vec_mul(mRHSrow51, aux59)),
					vec_madd(mRHSrow81, aux89, vec_mul(mRHSrow71, aux79)) ) ) ),

				0, mResult+4*16+8);

	vec_xst(vec_madd( mRHSrow92, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux29, vec_mul(mRHSrow12, aux19)),
					vec_madd(mRHSrow42, aux49, vec_mul(mRHSrow32, aux39)) ),
				vec_add(
					vec_madd(mRHSrow62, aux69, vec_mul(mRHSrow52, aux59)),
					vec_madd(mRHSrow82, aux89, vec_mul(mRHSrow72, aux79)) ) ) ),

				0, mResult+4*17+8);


	vector float mResultLastElem = 
		
		vec_madd( mRHSrow93, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux29, vec_mul(mRHSrow13, aux19)),
					vec_madd(mRHSrow43, aux49, vec_mul(mRHSrow33, aux39)) ),
				vec_add(
					vec_madd(mRHSrow63, aux69, vec_mul(mRHSrow53, aux59)),
					vec_madd(mRHSrow83, aux89, vec_mul(mRHSrow73, aux79)) ) ) );
	mResult[80] = mResultLastElem[0];



}


inline void mul12x12RowColFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHSrow11, mLHSrow12, mLHSrow13, mLHSrow21, mLHSrow22, mLHSrow23, mLHSrow31, mLHSrow32, mLHSrow33,
	      	     mLHSrow41, mLHSrow42, mLHSrow43, mLHSrow51, mLHSrow52, mLHSrow53, mLHSrow61, mLHSrow62, mLHSrow63,
		     mLHSrow71, mLHSrow72, mLHSrow73, mLHSrow81, mLHSrow82, mLHSrow83, mLHSrow91, mLHSrow92, mLHSrow93, mLHSrow101, mLHSrow102, mLHSrow103, mLHSrow111,
		     mLHSrow112,mLHSrow113,mLHSrow121,mLHSrow122, mLHSrow123;

	vector float mRHScol11, mRHScol12, mRHScol13, mRHScol21, mRHScol22, mRHScol23, mRHScol31, mRHScol32, mRHScol33,
	      	     mRHScol41, mRHScol42, mRHScol43, mRHScol51, mRHScol52, mRHScol53, mRHScol61, mRHScol62, mRHScol63,
		     mRHScol71, mRHScol72, mRHScol73, mRHScol81, mRHScol82, mRHScol83, mRHScol91, mRHScol92, mRHScol93, mRHScol101, mRHScol102, mRHScol103, mRHScol111,
		     mRHScol112, mRHScol113,  mRHScol121, mRHScol122, mRHScol123;
//load


	mRHScol11 = vec_xl(0,mRHS);
	mRHScol12 = vec_xl(0,mRHS+4);
	mRHScol13 = vec_xl(0,mRHS+4*2);

	mRHScol21 = vec_xl(0,mRHS+4*3);
	mRHScol22 = vec_xl(0,mRHS+4*4);
	mRHScol23 = vec_xl(0,mRHS+4*5);

	mRHScol31 = vec_xl(0,mRHS+4*6);
	mRHScol32 = vec_xl(0,mRHS+4*7);
	mRHScol33 = vec_xl(0,mRHS+4*8);

	mRHScol41 = vec_xl(0,mRHS+4*9);
	mRHScol42 = vec_xl(0,mRHS+4*10);
	mRHScol43 = vec_xl(0,mRHS+4*11);

	mRHScol51 = vec_xl(0,mRHS+4*12);
	mRHScol52 = vec_xl(0,mRHS+4*13);
	mRHScol53 = vec_xl(0,mRHS+4*14);

	mRHScol61 = vec_xl(0,mRHS+4*15);
	mRHScol62 = vec_xl(0,mRHS+4*16);
	mRHScol63 = vec_xl(0,mRHS+4*17);

	mRHScol71 = vec_xl(0,mRHS+4*18);
	mRHScol72 = vec_xl(0,mRHS+4*19);
	mRHScol73 = vec_xl(0,mRHS+4*20);

	mRHScol81 = vec_xl(0,mRHS+4*21);
	mRHScol82 = vec_xl(0,mRHS+4*22);
	mRHScol83 = vec_xl(0,mRHS+4*23);

	mRHScol91 = vec_xl(0,mRHS+4*24);
	mRHScol92 = vec_xl(0,mRHS+4*25);
	mRHScol93 = vec_xl(0,mRHS+4*26);

	mRHScol101 = vec_xl(0,mRHS+4*27);
	mRHScol102 = vec_xl(0,mRHS+4*28);
	mRHScol103 = vec_xl(0,mRHS+4*29);

	mRHScol111 = vec_xl(0,mRHS+4*30);
	mRHScol112 = vec_xl(0,mRHS+4*31);
	mRHScol113 = vec_xl(0,mRHS+4*32);

	mRHScol121 = vec_xl(0,mRHS+4*33);
	mRHScol122 = vec_xl(0,mRHS+4*34);
	mRHScol123 = vec_xl(0,mRHS+4*35);

//transpose RHS
	vector float mRHSrow11 = {mRHScol11[0], mRHScol21[0], mRHScol31[0], mRHScol41[0]};	
	vector float mRHSrow12 = {mRHScol51[0], mRHScol61[0], mRHScol71[0], mRHScol81[0]};	
	vector float mRHSrow13 = {mRHScol91[0],mRHScol101[0],mRHScol111[0],mRHScol121[0]};	

	vector float mRHSrow21 = {mRHScol11[1], mRHScol21[1], mRHScol31[1], mRHScol41[1]};	
	vector float mRHSrow22 = {mRHScol51[1], mRHScol61[1], mRHScol71[1], mRHScol81[1]};	
	vector float mRHSrow23 = {mRHScol91[1],mRHScol101[1],mRHScol111[1],mRHScol121[1]};	

	vector float mRHSrow31 = {mRHScol11[2], mRHScol21[2], mRHScol31[2], mRHScol41[2]};	
	vector float mRHSrow32 = {mRHScol51[2], mRHScol61[2], mRHScol71[2], mRHScol81[2]};	
	vector float mRHSrow33 = {mRHScol91[2],mRHScol101[2],mRHScol111[2],mRHScol121[2]};	

	vector float mRHSrow41 = {mRHScol11[3], mRHScol21[3], mRHScol31[3], mRHScol41[3]};	
	vector float mRHSrow42 = {mRHScol51[3], mRHScol61[3], mRHScol71[3], mRHScol81[3]};	
	vector float mRHSrow43 = {mRHScol91[3],mRHScol101[3],mRHScol111[3],mRHScol121[3]};	

	vector float mRHSrow51 = {mRHScol12[0], mRHScol22[0], mRHScol32[0], mRHScol42[0]};	
	vector float mRHSrow52 = {mRHScol52[0], mRHScol62[0], mRHScol72[0], mRHScol82[0]};	
	vector float mRHSrow53 = {mRHScol92[0],mRHScol102[0],mRHScol112[0],mRHScol122[0]};	

	vector float mRHSrow61 = {mRHScol12[1], mRHScol22[1], mRHScol32[1], mRHScol42[1]};	
	vector float mRHSrow62 = {mRHScol52[1], mRHScol62[1], mRHScol72[1], mRHScol82[1]};	
	vector float mRHSrow63 = {mRHScol92[1],mRHScol102[1],mRHScol112[1],mRHScol122[1]};	

	vector float mRHSrow71 = {mRHScol12[2], mRHScol22[2], mRHScol32[2], mRHScol42[2]};	
	vector float mRHSrow72 = {mRHScol52[2], mRHScol62[2], mRHScol72[2], mRHScol82[2]};	
	vector float mRHSrow73 = {mRHScol92[2],mRHScol102[2],mRHScol112[2],mRHScol122[2]};	

	vector float mRHSrow81 = {mRHScol12[3], mRHScol22[3], mRHScol32[3], mRHScol42[3]};	
	vector float mRHSrow82 = {mRHScol52[3], mRHScol62[3], mRHScol72[3], mRHScol82[3]};	
	vector float mRHSrow83 = {mRHScol92[3],mRHScol102[3],mRHScol112[3],mRHScol122[3]};	

	vector float mRHSrow91 = {mRHScol13[0], mRHScol23[0], mRHScol33[0], mRHScol43[0]};	
	vector float mRHSrow92 = {mRHScol53[0], mRHScol63[0], mRHScol73[0], mRHScol83[0]};	
	vector float mRHSrow93 = {mRHScol93[0],mRHScol103[0],mRHScol113[0],mRHScol123[0]};	

	vector float mRHSrow101 = {mRHScol12[1], mRHScol22[1], mRHScol32[1], mRHScol42[1]};	
	vector float mRHSrow102 = {mRHScol52[1], mRHScol62[1], mRHScol72[1], mRHScol82[1]};	
	vector float mRHSrow103 = {mRHScol92[1],mRHScol102[1],mRHScol112[1],mRHScol122[1]};	

	vector float mRHSrow111 = {mRHScol12[2], mRHScol22[2], mRHScol32[2], mRHScol42[2]};	
	vector float mRHSrow112 = {mRHScol52[2], mRHScol62[2], mRHScol72[2], mRHScol82[2]};	
	vector float mRHSrow113 = {mRHScol92[2],mRHScol102[2],mRHScol112[2],mRHScol122[2]};	

	vector float mRHSrow121 = {mRHScol12[3], mRHScol22[3], mRHScol32[3], mRHScol42[3]};	
	vector float mRHSrow122 = {mRHScol52[3], mRHScol62[3], mRHScol72[3], mRHScol82[3]};	
	vector float mRHSrow123 = {mRHScol92[3],mRHScol102[3],mRHScol112[3],mRHScol122[3]};	




	//--------------------------------------------------
	mLHSrow11 = vec_xl(0,mLHS);
	mLHSrow12 = vec_xl(0,mLHS+4);
	mLHSrow13 = vec_xl(0,mLHS+4*2);

	mLHSrow21 = vec_xl(0,mLHS+4*3);
	mLHSrow22 = vec_xl(0,mLHS+4*4);
	mLHSrow23 = vec_xl(0,mLHS+4*5);

	mLHSrow31 = vec_xl(0,mLHS+4*6);
	mLHSrow32 = vec_xl(0,mLHS+4*7);
	mLHSrow33 = vec_xl(0,mLHS+4*8);

	mLHSrow41 = vec_xl(0,mLHS+4*9);
	mLHSrow42 = vec_xl(0,mLHS+4*10);
	mLHSrow43 = vec_xl(0,mLHS+4*11);

	mLHSrow51 = vec_xl(0,mLHS+4*12);
	mLHSrow52 = vec_xl(0,mLHS+4*13);
	mLHSrow53 = vec_xl(0,mLHS+4*14);

	mLHSrow61 = vec_xl(0,mLHS+4*15);
	mLHSrow62 = vec_xl(0,mLHS+4*16);
	mLHSrow63 = vec_xl(0,mLHS+4*17);

	mLHSrow71 = vec_xl(0,mLHS+4*18);
	mLHSrow72 = vec_xl(0,mLHS+4*19);
	mLHSrow73 = vec_xl(0,mLHS+4*20);

	mLHSrow81 = vec_xl(0,mLHS+4*21);
	mLHSrow82 = vec_xl(0,mLHS+4*22);
	mLHSrow83 = vec_xl(0,mLHS+4*23);

	mLHSrow91 = vec_xl(0,mLHS+4*24);
	mLHSrow92 = vec_xl(0,mLHS+4*25);
	mLHSrow93 = vec_xl(0,mLHS+4*26);

	mLHSrow101 = vec_xl(0,mLHS+4*27);
	mLHSrow102 = vec_xl(0,mLHS+4*28);
	mLHSrow103 = vec_xl(0,mLHS+4*29);

	mLHSrow111 = vec_xl(0,mLHS+4*30);
	mLHSrow112 = vec_xl(0,mLHS+4*31);
	mLHSrow113 = vec_xl(0,mLHS+4*32);

	mLHSrow121 = vec_xl(0,mLHS+4*33);
	mLHSrow122 = vec_xl(0,mLHS+4*34);
	mLHSrow123 = vec_xl(0,mLHS+4*35);

//-------------------------------------------------------------------------

	vector float aux11={mLHSrow11[0],mLHSrow11[0],mLHSrow11[0],mLHSrow11[0]};
	vector float aux12={mLHSrow21[0],mLHSrow21[0],mLHSrow21[0],mLHSrow21[0]};
	vector float aux13={mLHSrow31[0],mLHSrow31[0],mLHSrow31[0],mLHSrow31[0]};
	vector float aux14={mLHSrow41[0],mLHSrow41[0],mLHSrow41[0],mLHSrow41[0]};

	vector float aux15={mLHSrow51[0],mLHSrow51[0],mLHSrow51[0],mLHSrow51[0]};
	vector float aux16={mLHSrow61[0],mLHSrow61[0],mLHSrow61[0],mLHSrow61[0]};
	vector float aux17={mLHSrow71[0],mLHSrow71[0],mLHSrow71[0],mLHSrow71[0]};
	vector float aux18={mLHSrow81[0],mLHSrow81[0],mLHSrow81[0],mLHSrow81[0]};

	vector float aux19={mLHSrow91[0],mLHSrow91[0],mLHSrow91[0],mLHSrow91[0]};
	vector float aux110={mLHSrow101[0],mLHSrow101[0],mLHSrow101[0],mLHSrow101[0]};
	vector float aux0111={mLHSrow111[0],mLHSrow111[0],mLHSrow111[0],mLHSrow111[0]};
	vector float aux0112={mLHSrow121[0],mLHSrow121[0],mLHSrow121[0],mLHSrow121[0]};

//-------------------------------------------------------------------------
	vector float aux21={mLHSrow11[1],mLHSrow11[1],mLHSrow11[1],mLHSrow11[1]};
	vector float aux22={mLHSrow21[1],mLHSrow21[1],mLHSrow21[1],mLHSrow21[1]};
	vector float aux23={mLHSrow31[1],mLHSrow31[1],mLHSrow31[1],mLHSrow31[1]};
	vector float aux24={mLHSrow41[1],mLHSrow41[1],mLHSrow41[1],mLHSrow41[1]};

	vector float aux25={mLHSrow51[1],mLHSrow51[1],mLHSrow51[1],mLHSrow51[1]};
	vector float aux26={mLHSrow61[1],mLHSrow61[1],mLHSrow61[1],mLHSrow61[1]};
	vector float aux27={mLHSrow71[1],mLHSrow71[1],mLHSrow71[1],mLHSrow71[1]};
	vector float aux28={mLHSrow81[1],mLHSrow81[1],mLHSrow81[1],mLHSrow81[1]};

	vector float aux29={mLHSrow91[1],mLHSrow91[1],mLHSrow91[1],mLHSrow91[1]};
	vector float aux210={mLHSrow101[1],mLHSrow101[1],mLHSrow101[1],mLHSrow101[1]};
	vector float aux211={mLHSrow111[1],mLHSrow111[1],mLHSrow111[1],mLHSrow111[1]};
	vector float aux212={mLHSrow121[1],mLHSrow121[1],mLHSrow121[1],mLHSrow121[1]};

//-------------------------------------------------------------------------
	vector float aux31={mLHSrow11[2],mLHSrow11[2],mLHSrow11[2],mLHSrow11[2]};
	vector float aux32={mLHSrow21[2],mLHSrow21[2],mLHSrow21[2],mLHSrow21[2]};
	vector float aux33={mLHSrow31[2],mLHSrow31[2],mLHSrow31[2],mLHSrow31[2]};
	vector float aux34={mLHSrow41[2],mLHSrow41[2],mLHSrow41[2],mLHSrow41[2]};

	vector float aux35={mLHSrow51[2],mLHSrow51[2],mLHSrow51[2],mLHSrow51[2]};
	vector float aux36={mLHSrow61[2],mLHSrow61[2],mLHSrow61[2],mLHSrow61[2]};
	vector float aux37={mLHSrow71[2],mLHSrow71[2],mLHSrow71[2],mLHSrow71[2]};
	vector float aux38={mLHSrow81[2],mLHSrow81[2],mLHSrow81[2],mLHSrow81[2]};

	vector float aux39={mLHSrow91[2],mLHSrow91[2],mLHSrow91[2],mLHSrow91[2]};
	vector float aux310={mLHSrow101[2],mLHSrow101[2],mLHSrow101[2],mLHSrow101[2]};
	vector float aux311={mLHSrow111[2],mLHSrow111[2],mLHSrow111[2],mLHSrow111[2]};
	vector float aux312={mLHSrow121[2],mLHSrow121[2],mLHSrow121[2],mLHSrow121[2]};

//-------------------------------------------------------------------------
	vector float aux41={mLHSrow11[3],mLHSrow11[3],mLHSrow11[3],mLHSrow11[3]};
	vector float aux42={mLHSrow21[3],mLHSrow21[3],mLHSrow21[3],mLHSrow21[3]};
	vector float aux43={mLHSrow31[3],mLHSrow31[3],mLHSrow31[3],mLHSrow31[3]};
	vector float aux44={mLHSrow41[3],mLHSrow41[3],mLHSrow41[3],mLHSrow41[3]};

	vector float aux45={mLHSrow51[3],mLHSrow51[3],mLHSrow51[3],mLHSrow51[3]};
	vector float aux46={mLHSrow61[3],mLHSrow61[3],mLHSrow61[3],mLHSrow61[3]};
	vector float aux47={mLHSrow71[3],mLHSrow71[3],mLHSrow71[3],mLHSrow71[3]};
	vector float aux48={mLHSrow81[3],mLHSrow81[3],mLHSrow81[3],mLHSrow81[3]};

	vector float aux49={mLHSrow91[3],mLHSrow91[3],mLHSrow91[3],mLHSrow91[3]};
	vector float aux410={mLHSrow101[3],mLHSrow101[3],mLHSrow101[3],mLHSrow101[3]};
	vector float aux411={mLHSrow111[3],mLHSrow111[3],mLHSrow111[3],mLHSrow111[3]};
	vector float aux412={mLHSrow121[3],mLHSrow121[3],mLHSrow121[3],mLHSrow121[3]};

//-------------------------------------------------------------------------

	vector float aux51={mLHSrow12[0],mLHSrow12[0],mLHSrow12[0],mLHSrow12[0]};
	vector float aux52={mLHSrow22[0],mLHSrow22[0],mLHSrow22[0],mLHSrow22[0]};
	vector float aux53={mLHSrow32[0],mLHSrow32[0],mLHSrow32[0],mLHSrow32[0]};
	vector float aux54={mLHSrow42[0],mLHSrow42[0],mLHSrow42[0],mLHSrow42[0]};

	vector float aux55={mLHSrow52[0],mLHSrow52[0],mLHSrow52[0],mLHSrow52[0]};
	vector float aux56={mLHSrow62[0],mLHSrow62[0],mLHSrow62[0],mLHSrow62[0]};
	vector float aux57={mLHSrow72[0],mLHSrow72[0],mLHSrow72[0],mLHSrow72[0]};
	vector float aux58={mLHSrow82[0],mLHSrow82[0],mLHSrow82[0],mLHSrow82[0]};

	vector float aux59={mLHSrow92[0],mLHSrow92[0],mLHSrow92[0],mLHSrow92[0]};
	vector float aux510={mLHSrow102[0],mLHSrow102[0],mLHSrow102[0],mLHSrow102[0]};
	vector float aux511={mLHSrow112[0],mLHSrow112[0],mLHSrow112[0],mLHSrow112[0]};
	vector float aux512={mLHSrow122[0],mLHSrow122[0],mLHSrow122[0],mLHSrow122[0]};

//-------------------------------------------------------------------------
	vector float aux61={mLHSrow12[1],mLHSrow12[1],mLHSrow12[1],mLHSrow12[1]};
	vector float aux62={mLHSrow22[1],mLHSrow22[1],mLHSrow22[1],mLHSrow22[1]};
	vector float aux63={mLHSrow32[1],mLHSrow32[1],mLHSrow32[1],mLHSrow32[1]};
	vector float aux64={mLHSrow42[1],mLHSrow42[1],mLHSrow42[1],mLHSrow42[1]};

	vector float aux65={mLHSrow52[1],mLHSrow52[1],mLHSrow52[1],mLHSrow52[1]};
	vector float aux66={mLHSrow62[1],mLHSrow62[1],mLHSrow62[1],mLHSrow62[1]};
	vector float aux67={mLHSrow72[1],mLHSrow72[1],mLHSrow72[1],mLHSrow72[1]};
	vector float aux68={mLHSrow82[1],mLHSrow82[1],mLHSrow82[1],mLHSrow82[1]};

	vector float aux69={mLHSrow92[1],mLHSrow92[1],mLHSrow92[1],mLHSrow92[1]};
	vector float aux610={mLHSrow102[1],mLHSrow102[1],mLHSrow102[1],mLHSrow102[1]};
	vector float aux611={mLHSrow112[1],mLHSrow112[1],mLHSrow112[1],mLHSrow112[1]};
	vector float aux612={mLHSrow122[1],mLHSrow122[1],mLHSrow122[1],mLHSrow122[1]};

//-------------------------------------------------------------------------
	vector float aux71={mLHSrow12[2],mLHSrow12[2],mLHSrow12[2],mLHSrow12[2]};
	vector float aux72={mLHSrow22[2],mLHSrow22[2],mLHSrow22[2],mLHSrow22[2]};
	vector float aux73={mLHSrow32[2],mLHSrow32[2],mLHSrow32[2],mLHSrow32[2]};
	vector float aux74={mLHSrow42[2],mLHSrow42[2],mLHSrow42[2],mLHSrow42[2]};

	vector float aux75={mLHSrow52[2],mLHSrow52[2],mLHSrow52[2],mLHSrow52[2]};
	vector float aux76={mLHSrow62[2],mLHSrow62[2],mLHSrow62[2],mLHSrow62[2]};
	vector float aux77={mLHSrow72[2],mLHSrow72[2],mLHSrow72[2],mLHSrow72[2]};
	vector float aux78={mLHSrow82[2],mLHSrow82[2],mLHSrow82[2],mLHSrow82[2]};

	vector float aux79={mLHSrow92[2],mLHSrow92[2],mLHSrow92[2],mLHSrow92[2]};
	vector float aux710={mLHSrow102[2],mLHSrow102[2],mLHSrow102[2],mLHSrow102[2]};
	vector float aux711={mLHSrow112[2],mLHSrow112[2],mLHSrow112[2],mLHSrow112[2]};
	vector float aux712={mLHSrow122[2],mLHSrow122[2],mLHSrow122[2],mLHSrow122[2]};

//-------------------------------------------------------------------------
	vector float aux81={mLHSrow12[3],mLHSrow12[3],mLHSrow12[3],mLHSrow12[3]};
	vector float aux82={mLHSrow22[3],mLHSrow22[3],mLHSrow22[3],mLHSrow22[3]};
	vector float aux83={mLHSrow32[3],mLHSrow32[3],mLHSrow32[3],mLHSrow32[3]};
	vector float aux84={mLHSrow42[3],mLHSrow42[3],mLHSrow42[3],mLHSrow42[3]};

	vector float aux85={mLHSrow52[3],mLHSrow52[3],mLHSrow52[3],mLHSrow52[3]};
	vector float aux86={mLHSrow62[3],mLHSrow62[3],mLHSrow62[3],mLHSrow62[3]};
	vector float aux87={mLHSrow72[3],mLHSrow72[3],mLHSrow72[3],mLHSrow72[3]};
	vector float aux88={mLHSrow82[3],mLHSrow82[3],mLHSrow82[3],mLHSrow82[3]};

	vector float aux89={mLHSrow92[3],mLHSrow92[3],mLHSrow92[3],mLHSrow92[3]};
	vector float aux810={mLHSrow102[3],mLHSrow102[3],mLHSrow102[3],mLHSrow102[3]};
	vector float aux811={mLHSrow112[3],mLHSrow112[3],mLHSrow112[3],mLHSrow112[3]};
	vector float aux812={mLHSrow122[3],mLHSrow122[3],mLHSrow122[3],mLHSrow122[3]};

//-------------------------------------------------------------------------
	vector float aux91={mLHSrow13[0],mLHSrow13[0],mLHSrow13[0],mLHSrow13[0]};
	vector float aux92={mLHSrow23[0],mLHSrow23[0],mLHSrow23[0],mLHSrow23[0]};
	vector float aux93={mLHSrow33[0],mLHSrow33[0],mLHSrow33[0],mLHSrow33[0]};
	vector float aux94={mLHSrow43[0],mLHSrow43[0],mLHSrow43[0],mLHSrow43[0]};

	vector float aux95={mLHSrow53[0],mLHSrow53[0],mLHSrow53[0],mLHSrow53[0]};
	vector float aux96={mLHSrow63[0],mLHSrow63[0],mLHSrow63[0],mLHSrow63[0]};
	vector float aux97={mLHSrow73[0],mLHSrow73[0],mLHSrow73[0],mLHSrow73[0]};
	vector float aux98={mLHSrow83[0],mLHSrow83[0],mLHSrow83[0],mLHSrow83[0]};

	vector float aux99={mLHSrow93[0],mLHSrow93[0],mLHSrow93[0],mLHSrow93[0]};
	vector float aux910={mLHSrow103[0],mLHSrow103[0],mLHSrow103[0],mLHSrow103[0]};
	vector float aux911={mLHSrow113[0],mLHSrow113[0],mLHSrow113[0],mLHSrow113[0]};
	vector float aux912={mLHSrow123[0],mLHSrow123[0],mLHSrow123[0],mLHSrow123[0]};

//-------------------------------------------------------------------------
	vector float aux101={mLHSrow13[1],mLHSrow13[1],mLHSrow13[1],mLHSrow13[1]};
	vector float aux102={mLHSrow23[1],mLHSrow23[1],mLHSrow23[1],mLHSrow23[1]};
	vector float aux103={mLHSrow33[1],mLHSrow33[1],mLHSrow33[1],mLHSrow33[1]};
	vector float aux104={mLHSrow43[1],mLHSrow43[1],mLHSrow43[1],mLHSrow43[1]};

	vector float aux105={mLHSrow53[1],mLHSrow53[1],mLHSrow53[1],mLHSrow53[1]};
	vector float aux106={mLHSrow63[1],mLHSrow63[1],mLHSrow63[1],mLHSrow63[1]};
	vector float aux107={mLHSrow73[1],mLHSrow73[1],mLHSrow73[1],mLHSrow73[1]};
	vector float aux108={mLHSrow83[1],mLHSrow83[1],mLHSrow83[1],mLHSrow83[1]};

	vector float aux109={mLHSrow93[1],mLHSrow93[1],mLHSrow93[1],mLHSrow93[1]};
	vector float aux1010={mLHSrow103[1],mLHSrow103[1],mLHSrow103[1],mLHSrow103[1]};
	vector float aux1011={mLHSrow113[1],mLHSrow113[1],mLHSrow113[1],mLHSrow113[1]};
	vector float aux1012={mLHSrow123[1],mLHSrow123[1],mLHSrow123[1],mLHSrow123[1]};

//-------------------------------------------------------------------------
	vector float aux111={mLHSrow13[2],mLHSrow13[2],mLHSrow13[2],mLHSrow13[2]};
	vector float aux112={mLHSrow23[2],mLHSrow23[2],mLHSrow23[2],mLHSrow23[2]};
	vector float aux113={mLHSrow33[2],mLHSrow33[2],mLHSrow33[2],mLHSrow33[2]};
	vector float aux114={mLHSrow43[2],mLHSrow43[2],mLHSrow43[2],mLHSrow43[2]};

	vector float aux115={mLHSrow53[2],mLHSrow53[2],mLHSrow53[2],mLHSrow53[2]};
	vector float aux116={mLHSrow63[2],mLHSrow63[2],mLHSrow63[2],mLHSrow63[2]};
	vector float aux117={mLHSrow73[2],mLHSrow73[2],mLHSrow73[2],mLHSrow73[2]};
	vector float aux118={mLHSrow83[2],mLHSrow83[2],mLHSrow83[2],mLHSrow83[2]};

	vector float aux119={mLHSrow93[2],mLHSrow93[2],mLHSrow93[2],mLHSrow93[2]};
	vector float aux1110={mLHSrow103[2],mLHSrow103[2],mLHSrow103[2],mLHSrow103[2]};
	vector float aux1111={mLHSrow113[2],mLHSrow113[2],mLHSrow113[2],mLHSrow113[2]};
	vector float aux1112={mLHSrow123[2],mLHSrow123[2],mLHSrow123[2],mLHSrow123[2]};

//-------------------------------------------------------------------------
	vector float aux121={mLHSrow13[3],mLHSrow13[3],mLHSrow13[3],mLHSrow13[3]};
	vector float aux122={mLHSrow23[3],mLHSrow23[3],mLHSrow23[3],mLHSrow23[3]};
	vector float aux123={mLHSrow33[3],mLHSrow33[3],mLHSrow33[3],mLHSrow33[3]};
	vector float aux124={mLHSrow43[3],mLHSrow43[3],mLHSrow43[3],mLHSrow43[3]};

	vector float aux125={mLHSrow53[3],mLHSrow53[3],mLHSrow53[3],mLHSrow53[3]};
	vector float aux126={mLHSrow63[3],mLHSrow63[3],mLHSrow63[3],mLHSrow63[3]};
	vector float aux127={mLHSrow73[3],mLHSrow73[3],mLHSrow73[3],mLHSrow73[3]};
	vector float aux128={mLHSrow83[3],mLHSrow83[3],mLHSrow83[3],mLHSrow83[3]};

	vector float aux129={mLHSrow93[3],mLHSrow93[3],mLHSrow93[3],mLHSrow93[3]};
	vector float aux1210={mLHSrow103[3],mLHSrow103[3],mLHSrow103[3],mLHSrow103[3]};
	vector float aux1211={mLHSrow113[3],mLHSrow113[3],mLHSrow113[3],mLHSrow113[3]};
	vector float aux1212={mLHSrow123[3],mLHSrow123[3],mLHSrow123[3],mLHSrow123[3]};

//-------------------------------------------------------------------------
		//row 1 of result
	vec_xst(vec_madd(aux121, mRHSrow121, vec_madd(aux111, mRHSrow111, vec_madd(aux101, mRHSrow101, vec_madd(aux91, mRHSrow91, vec_madd(aux81, mRHSrow81, vec_madd(aux71, mRHSrow71, vec_madd(aux61, mRHSrow61, vec_madd(aux51, mRHSrow51, vec_madd(aux41, mRHSrow41, vec_madd(aux31, mRHSrow31, vec_madd(aux21, mRHSrow21, vec_mul(aux11, mRHSrow11)))))))))))), 0, mResult);
	vec_xst(vec_madd(aux121, mRHSrow122, vec_madd(aux111, mRHSrow112, vec_madd(aux101, mRHSrow102, vec_madd(aux91, mRHSrow92, vec_madd(aux81, mRHSrow82, vec_madd(aux71, mRHSrow72, vec_madd(aux61, mRHSrow62, vec_madd(aux51, mRHSrow52, vec_madd(aux41, mRHSrow42, vec_madd(aux31, mRHSrow32, vec_madd(aux21, mRHSrow22, vec_mul(aux11, mRHSrow12)))))))))))), 0, mResult + 4);
	vec_xst(vec_madd(aux121, mRHSrow123, vec_madd(aux111, mRHSrow113, vec_madd(aux101, mRHSrow103, vec_madd(aux91, mRHSrow93, vec_madd(aux81, mRHSrow83, vec_madd(aux71, mRHSrow73, vec_madd(aux61, mRHSrow63, vec_madd(aux51, mRHSrow53, vec_madd(aux41, mRHSrow43, vec_madd(aux31, mRHSrow33, vec_madd(aux21, mRHSrow23, vec_mul(aux11, mRHSrow13)))))))))))), 0, mResult + 4*2);

	//row 2 of result
	vec_xst(vec_madd(aux122, mRHSrow121, vec_madd(aux112, mRHSrow111, vec_madd(aux102, mRHSrow101, vec_madd(aux92, mRHSrow91, vec_madd(aux82, mRHSrow81, vec_madd(aux72, mRHSrow71, vec_madd(aux62, mRHSrow61, vec_madd(aux52, mRHSrow51, vec_madd(aux42, mRHSrow41, vec_madd(aux32, mRHSrow31, vec_madd(aux22, mRHSrow21, vec_mul(aux12, mRHSrow11)))))))))))), 0, mResult + 4*3);
	vec_xst(vec_madd(aux122, mRHSrow122, vec_madd(aux112, mRHSrow112, vec_madd(aux102, mRHSrow102, vec_madd(aux92, mRHSrow92, vec_madd(aux82, mRHSrow82, vec_madd(aux72, mRHSrow72, vec_madd(aux62, mRHSrow62, vec_madd(aux52, mRHSrow52, vec_madd(aux42, mRHSrow42, vec_madd(aux32, mRHSrow32, vec_madd(aux22, mRHSrow22, vec_mul(aux12, mRHSrow12)))))))))))), 0, mResult + 4*4);
	vec_xst(vec_madd(aux122, mRHSrow123, vec_madd(aux112, mRHSrow113, vec_madd(aux102, mRHSrow103, vec_madd(aux92, mRHSrow93, vec_madd(aux82, mRHSrow83, vec_madd(aux72, mRHSrow73, vec_madd(aux62, mRHSrow63, vec_madd(aux52, mRHSrow53, vec_madd(aux42, mRHSrow43, vec_madd(aux32, mRHSrow33, vec_madd(aux22, mRHSrow23, vec_mul(aux12, mRHSrow13)))))))))))), 0, mResult + 4*5);

	// row 3 of mResult
	vec_xst(vec_madd(aux123, mRHSrow121, vec_madd(aux113, mRHSrow111, vec_madd(aux103, mRHSrow101, vec_madd(aux93, mRHSrow91, vec_madd(aux83, mRHSrow81, vec_madd(aux73, mRHSrow71, vec_madd(aux63, mRHSrow61, vec_madd(aux53, mRHSrow51, vec_madd(aux43, mRHSrow41, vec_madd(aux33, mRHSrow31, vec_madd(aux23, mRHSrow21, vec_mul(aux13, mRHSrow11)))))))))))), 0, mResult + 4*6);
	vec_xst(vec_madd(aux123, mRHSrow122, vec_madd(aux113, mRHSrow112, vec_madd(aux103, mRHSrow102, vec_madd(aux93, mRHSrow92, vec_madd(aux83, mRHSrow82, vec_madd(aux73, mRHSrow72, vec_madd(aux63, mRHSrow62, vec_madd(aux53, mRHSrow52, vec_madd(aux43, mRHSrow42, vec_madd(aux33, mRHSrow32, vec_madd(aux23, mRHSrow22, vec_mul(aux13, mRHSrow12)))))))))))), 0, mResult + 4*7);
	vec_xst(vec_madd(aux123, mRHSrow123, vec_madd(aux113, mRHSrow113, vec_madd(aux103, mRHSrow103, vec_madd(aux93, mRHSrow93, vec_madd(aux83, mRHSrow83, vec_madd(aux73, mRHSrow73, vec_madd(aux63, mRHSrow63, vec_madd(aux53, mRHSrow53, vec_madd(aux43, mRHSrow43, vec_madd(aux33, mRHSrow33, vec_madd(aux23, mRHSrow23, vec_mul(aux13, mRHSrow13)))))))))))), 0, mResult + 4*8);
	
	// row 4 of mResult
	vec_xst(vec_madd(aux124, mRHSrow121, vec_madd(aux114, mRHSrow111, vec_madd(aux104, mRHSrow101, vec_madd(aux94, mRHSrow91, vec_madd(aux84, mRHSrow81, vec_madd(aux74, mRHSrow71, vec_madd(aux64, mRHSrow61, vec_madd(aux54, mRHSrow51, vec_madd(aux44, mRHSrow41, vec_madd(aux34, mRHSrow31, vec_madd(aux24, mRHSrow21, vec_mul(aux14, mRHSrow11)))))))))))), 0, mResult + 4*9);
	vec_xst(vec_madd(aux124, mRHSrow122, vec_madd(aux114, mRHSrow112, vec_madd(aux104, mRHSrow102, vec_madd(aux94, mRHSrow92, vec_madd(aux84, mRHSrow82, vec_madd(aux74, mRHSrow72, vec_madd(aux64, mRHSrow62, vec_madd(aux54, mRHSrow52, vec_madd(aux44, mRHSrow42, vec_madd(aux34, mRHSrow32, vec_madd(aux24, mRHSrow22, vec_mul(aux14, mRHSrow12)))))))))))), 0, mResult + 4*10);
	vec_xst(vec_madd(aux124, mRHSrow123, vec_madd(aux114, mRHSrow113, vec_madd(aux104, mRHSrow103, vec_madd(aux94, mRHSrow93, vec_madd(aux84, mRHSrow83, vec_madd(aux74, mRHSrow73, vec_madd(aux64, mRHSrow63, vec_madd(aux54, mRHSrow53, vec_madd(aux44, mRHSrow43, vec_madd(aux34, mRHSrow33, vec_madd(aux24, mRHSrow23, vec_mul(aux14, mRHSrow13)))))))))))), 0, mResult + 4*11);
	
	// row 5 of mResult
	vec_xst(vec_madd(aux125, mRHSrow121, vec_madd(aux115, mRHSrow111, vec_madd(aux105, mRHSrow101, vec_madd(aux95, mRHSrow91, vec_madd(aux85, mRHSrow81, vec_madd(aux75, mRHSrow71, vec_madd(aux65, mRHSrow61, vec_madd(aux55, mRHSrow51, vec_madd(aux45, mRHSrow41, vec_madd(aux35, mRHSrow31, vec_madd(aux25, mRHSrow21, vec_mul(aux15, mRHSrow11)))))))))))), 0, mResult + 4*12);
	vec_xst(vec_madd(aux125, mRHSrow122, vec_madd(aux115, mRHSrow112, vec_madd(aux105, mRHSrow102, vec_madd(aux95, mRHSrow92, vec_madd(aux85, mRHSrow82, vec_madd(aux75, mRHSrow72, vec_madd(aux65, mRHSrow62, vec_madd(aux55, mRHSrow52, vec_madd(aux45, mRHSrow42, vec_madd(aux35, mRHSrow32, vec_madd(aux25, mRHSrow22, vec_mul(aux15, mRHSrow12)))))))))))), 0, mResult + 4*13);
	vec_xst(vec_madd(aux125, mRHSrow123, vec_madd(aux115, mRHSrow113, vec_madd(aux105, mRHSrow103, vec_madd(aux95, mRHSrow93, vec_madd(aux85, mRHSrow83, vec_madd(aux75, mRHSrow73, vec_madd(aux65, mRHSrow63, vec_madd(aux55, mRHSrow53, vec_madd(aux45, mRHSrow43, vec_madd(aux35, mRHSrow33, vec_madd(aux25, mRHSrow23, vec_mul(aux15, mRHSrow13)))))))))))), 0, mResult + 4*14);
	
	// row 6 of mResult
	vec_xst(vec_madd(aux126, mRHSrow121, vec_madd(aux116, mRHSrow111, vec_madd(aux106, mRHSrow101, vec_madd(aux96, mRHSrow91, vec_madd(aux86, mRHSrow81, vec_madd(aux76, mRHSrow71, vec_madd(aux66, mRHSrow61, vec_madd(aux56, mRHSrow51, vec_madd(aux46, mRHSrow41, vec_madd(aux36, mRHSrow31, vec_madd(aux26, mRHSrow21, vec_mul(aux16, mRHSrow11)))))))))))), 0, mResult + 4*15);
	vec_xst(vec_madd(aux126, mRHSrow122, vec_madd(aux116, mRHSrow112, vec_madd(aux106, mRHSrow102, vec_madd(aux96, mRHSrow92, vec_madd(aux86, mRHSrow82, vec_madd(aux76, mRHSrow72, vec_madd(aux66, mRHSrow62, vec_madd(aux56, mRHSrow52, vec_madd(aux46, mRHSrow42, vec_madd(aux36, mRHSrow32, vec_madd(aux26, mRHSrow22, vec_mul(aux16, mRHSrow12)))))))))))), 0, mResult + 4*16);
	vec_xst(vec_madd(aux126, mRHSrow123, vec_madd(aux116, mRHSrow113, vec_madd(aux106, mRHSrow103, vec_madd(aux96, mRHSrow93, vec_madd(aux86, mRHSrow83, vec_madd(aux76, mRHSrow73, vec_madd(aux66, mRHSrow63, vec_madd(aux56, mRHSrow53, vec_madd(aux46, mRHSrow43, vec_madd(aux36, mRHSrow33, vec_madd(aux26, mRHSrow23, vec_mul(aux16, mRHSrow13)))))))))))), 0, mResult + 4*17);
	
	// row 7 of mResult
	vec_xst(vec_madd(aux127, mRHSrow121, vec_madd(aux117, mRHSrow111, vec_madd(aux107, mRHSrow101, vec_madd(aux97, mRHSrow91, vec_madd(aux87, mRHSrow81, vec_madd(aux77, mRHSrow71, vec_madd(aux67, mRHSrow61, vec_madd(aux57, mRHSrow51, vec_madd(aux47, mRHSrow41, vec_madd(aux37, mRHSrow31, vec_madd(aux27, mRHSrow21, vec_mul(aux17, mRHSrow11)))))))))))), 0, mResult + 4*18);
	vec_xst(vec_madd(aux127, mRHSrow122, vec_madd(aux117, mRHSrow112, vec_madd(aux107, mRHSrow102, vec_madd(aux97, mRHSrow92, vec_madd(aux87, mRHSrow82, vec_madd(aux77, mRHSrow72, vec_madd(aux67, mRHSrow62, vec_madd(aux57, mRHSrow52, vec_madd(aux47, mRHSrow42, vec_madd(aux37, mRHSrow32, vec_madd(aux27, mRHSrow22, vec_mul(aux17, mRHSrow12)))))))))))), 0, mResult + 4*19);
	vec_xst(vec_madd(aux127, mRHSrow123, vec_madd(aux117, mRHSrow113, vec_madd(aux107, mRHSrow103, vec_madd(aux97, mRHSrow93, vec_madd(aux87, mRHSrow83, vec_madd(aux77, mRHSrow73, vec_madd(aux67, mRHSrow63, vec_madd(aux57, mRHSrow53, vec_madd(aux47, mRHSrow43, vec_madd(aux37, mRHSrow33, vec_madd(aux27, mRHSrow23, vec_mul(aux17, mRHSrow13)))))))))))), 0, mResult + 4*20);
	
	// row 8 of mResult
	vec_xst(vec_madd(aux128, mRHSrow121, vec_madd(aux118, mRHSrow111, vec_madd(aux108, mRHSrow101, vec_madd(aux98, mRHSrow91, vec_madd(aux88, mRHSrow81, vec_madd(aux78, mRHSrow71, vec_madd(aux68, mRHSrow61, vec_madd(aux58, mRHSrow51, vec_madd(aux48, mRHSrow41, vec_madd(aux38, mRHSrow31, vec_madd(aux28, mRHSrow21, vec_mul(aux18, mRHSrow11)))))))))))), 0, mResult + 4*21);
	vec_xst(vec_madd(aux128, mRHSrow122, vec_madd(aux118, mRHSrow112, vec_madd(aux108, mRHSrow102, vec_madd(aux98, mRHSrow92, vec_madd(aux88, mRHSrow82, vec_madd(aux78, mRHSrow72, vec_madd(aux68, mRHSrow62, vec_madd(aux58, mRHSrow52, vec_madd(aux48, mRHSrow42, vec_madd(aux38, mRHSrow32, vec_madd(aux28, mRHSrow22, vec_mul(aux18, mRHSrow12)))))))))))), 0, mResult + 4*22);
	vec_xst(vec_madd(aux128, mRHSrow123, vec_madd(aux118, mRHSrow113, vec_madd(aux108, mRHSrow103, vec_madd(aux98, mRHSrow93, vec_madd(aux88, mRHSrow83, vec_madd(aux78, mRHSrow73, vec_madd(aux68, mRHSrow63, vec_madd(aux58, mRHSrow53, vec_madd(aux48, mRHSrow43, vec_madd(aux38, mRHSrow33, vec_madd(aux28, mRHSrow23, vec_mul(aux18, mRHSrow13)))))))))))), 0, mResult + 4*23);
	
	// row 9 of mResult
	vec_xst(vec_madd(aux129, mRHSrow121, vec_madd(aux119, mRHSrow111, vec_madd(aux109, mRHSrow101, vec_madd(aux99, mRHSrow91, vec_madd(aux89, mRHSrow81, vec_madd(aux79, mRHSrow71, vec_madd(aux69, mRHSrow61, vec_madd(aux59, mRHSrow51, vec_madd(aux49, mRHSrow41, vec_madd(aux39, mRHSrow31, vec_madd(aux29, mRHSrow21, vec_mul(aux19, mRHSrow11)))))))))))), 0, mResult + 4*24);
	vec_xst(vec_madd(aux129, mRHSrow122, vec_madd(aux119, mRHSrow112, vec_madd(aux109, mRHSrow102, vec_madd(aux99, mRHSrow92, vec_madd(aux89, mRHSrow82, vec_madd(aux79, mRHSrow72, vec_madd(aux69, mRHSrow62, vec_madd(aux59, mRHSrow52, vec_madd(aux49, mRHSrow42, vec_madd(aux39, mRHSrow32, vec_madd(aux29, mRHSrow22, vec_mul(aux19, mRHSrow12)))))))))))), 0, mResult + 4*25);
	vec_xst(vec_madd(aux129, mRHSrow123, vec_madd(aux119, mRHSrow113, vec_madd(aux109, mRHSrow103, vec_madd(aux99, mRHSrow93, vec_madd(aux89, mRHSrow83, vec_madd(aux79, mRHSrow73, vec_madd(aux69, mRHSrow63, vec_madd(aux59, mRHSrow53, vec_madd(aux49, mRHSrow43, vec_madd(aux39, mRHSrow33, vec_madd(aux29, mRHSrow23, vec_mul(aux19, mRHSrow13)))))))))))), 0, mResult + 4*26);
	
	// row 10 of mResult
	vec_xst(vec_madd(aux1210, mRHSrow121, vec_madd(aux1110, mRHSrow111, vec_madd(aux1010, mRHSrow101, vec_madd(aux910, mRHSrow91, vec_madd(aux810, mRHSrow81, vec_madd(aux710, mRHSrow71, vec_madd(aux610, mRHSrow61, vec_madd(aux510, mRHSrow51, vec_madd(aux410, mRHSrow41, vec_madd(aux310, mRHSrow31, vec_madd(aux210, mRHSrow21, vec_mul(aux110, mRHSrow11)))))))))))), 0, mResult + 4*27);
	vec_xst(vec_madd(aux1210, mRHSrow122, vec_madd(aux1110, mRHSrow112, vec_madd(aux1010, mRHSrow102, vec_madd(aux910, mRHSrow92, vec_madd(aux810, mRHSrow82, vec_madd(aux710, mRHSrow72, vec_madd(aux610, mRHSrow62, vec_madd(aux510, mRHSrow52, vec_madd(aux410, mRHSrow42, vec_madd(aux310, mRHSrow32, vec_madd(aux210, mRHSrow22, vec_mul(aux110, mRHSrow12)))))))))))), 0, mResult + 4*28);
	vec_xst(vec_madd(aux1210, mRHSrow123, vec_madd(aux1110, mRHSrow113, vec_madd(aux1010, mRHSrow103, vec_madd(aux910, mRHSrow93, vec_madd(aux810, mRHSrow83, vec_madd(aux710, mRHSrow73, vec_madd(aux610, mRHSrow63, vec_madd(aux510, mRHSrow53, vec_madd(aux410, mRHSrow43, vec_madd(aux310, mRHSrow33, vec_madd(aux210, mRHSrow23, vec_mul(aux110, mRHSrow13)))))))))))), 0, mResult + 4*29);
	

	// row 11 of mResult
	vec_xst(vec_madd(aux1211, mRHSrow121, vec_madd(aux1111, mRHSrow111, vec_madd(aux1011, mRHSrow101, vec_madd(aux911, mRHSrow91, vec_madd(aux811, mRHSrow81, vec_madd(aux711, mRHSrow71, vec_madd(aux611, mRHSrow61, vec_madd(aux511, mRHSrow51, vec_madd(aux411, mRHSrow41, vec_madd(aux311, mRHSrow31, vec_madd(aux211, mRHSrow21, vec_mul(aux0111, mRHSrow11)))))))))))), 0, mResult + 4*30);
	vec_xst(vec_madd(aux1211, mRHSrow122, vec_madd(aux1111, mRHSrow112, vec_madd(aux1011, mRHSrow102, vec_madd(aux911, mRHSrow92, vec_madd(aux811, mRHSrow82, vec_madd(aux711, mRHSrow72, vec_madd(aux611, mRHSrow62, vec_madd(aux511, mRHSrow52, vec_madd(aux411, mRHSrow42, vec_madd(aux311, mRHSrow32, vec_madd(aux211, mRHSrow22, vec_mul(aux0111, mRHSrow12)))))))))))), 0, mResult + 4*31);
	vec_xst(vec_madd(aux1211, mRHSrow123, vec_madd(aux1111, mRHSrow113, vec_madd(aux1011, mRHSrow103, vec_madd(aux911, mRHSrow93, vec_madd(aux811, mRHSrow83, vec_madd(aux711, mRHSrow73, vec_madd(aux611, mRHSrow63, vec_madd(aux511, mRHSrow53, vec_madd(aux411, mRHSrow43, vec_madd(aux311, mRHSrow33, vec_madd(aux211, mRHSrow23, vec_mul(aux0111, mRHSrow13)))))))))))), 0, mResult + 4*32);
	
	// row 12 of mResult
	vec_xst(vec_madd(aux1212, mRHSrow121, vec_madd(aux1112, mRHSrow111, vec_madd(aux1012, mRHSrow101, vec_madd(aux912, mRHSrow91, vec_madd(aux812, mRHSrow81, vec_madd(aux712, mRHSrow71, vec_madd(aux612, mRHSrow61, vec_madd(aux512, mRHSrow51, vec_madd(aux412, mRHSrow41, vec_madd(aux312, mRHSrow31, vec_madd(aux212, mRHSrow21, vec_mul(aux0112, mRHSrow11)))))))))))), 0, mResult + 4*33);
	vec_xst(vec_madd(aux1212, mRHSrow122, vec_madd(aux1112, mRHSrow112, vec_madd(aux1012, mRHSrow102, vec_madd(aux912, mRHSrow92, vec_madd(aux812, mRHSrow82, vec_madd(aux712, mRHSrow72, vec_madd(aux612, mRHSrow62, vec_madd(aux512, mRHSrow52, vec_madd(aux412, mRHSrow42, vec_madd(aux312, mRHSrow32, vec_madd(aux212, mRHSrow22, vec_mul(aux0112, mRHSrow12)))))))))))), 0, mResult + 4*34);
	vec_xst(vec_madd(aux1212, mRHSrow123, vec_madd(aux1112, mRHSrow113, vec_madd(aux1012, mRHSrow103, vec_madd(aux912, mRHSrow93, vec_madd(aux812, mRHSrow83, vec_madd(aux712, mRHSrow73, vec_madd(aux612, mRHSrow63, vec_madd(aux512, mRHSrow53, vec_madd(aux412, mRHSrow43, vec_madd(aux312, mRHSrow33, vec_madd(aux212, mRHSrow23, vec_mul(aux0112, mRHSrow13)))))))))))), 0, mResult + 4*35);
	

}



//=========================================================================================================================
//row x row float

inline void mul4x4RowMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){
	
	vector float mLHSrow1,mLHSrow2,mLHSrow3,mLHSrow4;
	vector float mRHSrow1,mRHSrow2,mRHSrow3,mRHSrow4;


	//====================================================
	
	mRHSrow1 = vec_xl(0,mRHS);
	mRHSrow2 = vec_xl(0,mRHS+4);
	mRHSrow3 = vec_xl(0,mRHS+4*2);
	mRHSrow4 = vec_xl(0,mRHS+4*3);

	mLHSrow1 = vec_xl(0,mLHS);
	mLHSrow2 = vec_xl(0,mLHS+4);
	mLHSrow3 = vec_xl(0,mLHS+4*2);
	mLHSrow4 = vec_xl(0,mLHS+4*3);

	//splat==============================================
	
	vector float auxLHS11 = {mLHSrow1[0],mLHSrow1[0],mLHSrow1[0],mLHSrow1[0]};
	vector float auxLHS12 = {mLHSrow2[0],mLHSrow2[0],mLHSrow2[0],mLHSrow2[0]};
	vector float auxLHS13 = {mLHSrow3[0],mLHSrow3[0],mLHSrow3[0],mLHSrow3[0]};
	vector float auxLHS14 = {mLHSrow4[0],mLHSrow4[0],mLHSrow4[0],mLHSrow4[0]};
	
	vector float auxLHS21 = {mLHSrow1[1],mLHSrow1[1],mLHSrow1[1],mLHSrow1[1]};
	vector float auxLHS22 = {mLHSrow2[1],mLHSrow2[1],mLHSrow2[1],mLHSrow2[1]};
	vector float auxLHS23 = {mLHSrow3[1],mLHSrow3[1],mLHSrow3[1],mLHSrow3[1]};
	vector float auxLHS24 = {mLHSrow4[1],mLHSrow4[1],mLHSrow4[1],mLHSrow4[1]};
	
	vector float auxLHS31 = {mLHSrow1[2],mLHSrow1[2],mLHSrow1[2],mLHSrow1[2]};
	vector float auxLHS32 = {mLHSrow2[2],mLHSrow2[2],mLHSrow2[2],mLHSrow2[2]};
	vector float auxLHS33 = {mLHSrow3[2],mLHSrow3[2],mLHSrow3[2],mLHSrow3[2]};
	vector float auxLHS34 = {mLHSrow4[2],mLHSrow4[2],mLHSrow4[2],mLHSrow4[2]};
	
	vector float auxLHS41 = {mLHSrow1[3],mLHSrow1[3],mLHSrow1[3],mLHSrow1[3]};
	vector float auxLHS42 = {mLHSrow2[3],mLHSrow2[3],mLHSrow2[3],mLHSrow2[3]};
	vector float auxLHS43 = {mLHSrow3[3],mLHSrow3[3],mLHSrow3[3],mLHSrow3[3]};
	vector float auxLHS44 = {mLHSrow4[3],mLHSrow4[3],mLHSrow4[3],mLHSrow4[3]};
	

 	//row 1 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS11,mRHSrow1),vec_mul(auxLHS12,mRHSrow2)),
	vec_add(vec_mul(auxLHS13,mRHSrow3),vec_mul(auxLHS14,mRHSrow4))),0,
	mResult
	);

	//row 2 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS21,mRHSrow1),vec_mul(auxLHS22,mRHSrow2)),
	vec_add(vec_mul(auxLHS23,mRHSrow3),vec_mul(auxLHS24,mRHSrow4))),0,mResult+4
	);

	//row 3
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS31,mRHSrow1),vec_mul(auxLHS32,mRHSrow2)),
	vec_add(vec_mul(auxLHS33,mRHSrow3),vec_mul(auxLHS34,mRHSrow4))),0,mResult+8
	);

	//row 4
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS41,mRHSrow1),vec_mul(auxLHS42,mRHSrow2)),
	vec_add(vec_mul(auxLHS43,mRHSrow3),vec_mul(auxLHS44,mRHSrow4))),0,mResult+12
	);

}

inline void mul9x9RowMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHSrow11, mLHSrow12, mLHSrow13, mLHSrow21, mLHSrow22, mLHSrow23, mLHSrow31, mLHSrow32, mLHSrow33,
	      	     mLHSrow41, mLHSrow42, mLHSrow43, mLHSrow51, mLHSrow52, mLHSrow53, mLHSrow61, mLHSrow62, mLHSrow63,
		     mLHSrow71, mLHSrow72, mLHSrow73, mLHSrow81, mLHSrow82, mLHSrow83, mLHSrow91, mLHSrow92, mLHSrow93;

	vector float mRHSrow11, mRHSrow12, mRHSrow13, mRHSrow21, mRHSrow22, mRHSrow23, mRHSrow31, mRHSrow32, mRHSrow33,
	      	     mRHSrow41, mRHSrow42, mRHSrow43, mRHSrow51, mRHSrow52, mRHSrow53, mRHSrow61, mRHSrow62, mRHSrow63,
		     mRHSrow71, mRHSrow72, mRHSrow73, mRHSrow81, mRHSrow82, mRHSrow83, mRHSrow91, mRHSrow92, mRHSrow93;

//load
// __8__17__26__35__44__53__62__71__80


	mLHSrow11 = vec_xl(0,mLHS);
	mLHSrow12 = vec_xl(0,mLHS+4);
	mLHSrow13 = vec_splats((float)0);
	mLHSrow13[0] = mLHS[8];

	mLHSrow21 = vec_xl(0,mLHS+4*2+1);
	mLHSrow22 = vec_xl(0,mLHS+4*3+1);
	mLHSrow23 = vec_splats((float)0);
	mLHSrow23[0] = mLHS[17];

	mLHSrow31 = vec_xl(0,mLHS+4*4+2);
	mLHSrow32 = vec_xl(0,mLHS+4*5+2);
	mLHSrow33 = vec_splats((float)0);
	mLHSrow33[0] = mLHS[26];

	mLHSrow41 = vec_xl(0,mLHS+4*6+3);
	mLHSrow42 = vec_xl(0,mLHS+4*7+3);
	mLHSrow43 = vec_splats((float)0);
	mLHSrow43[0] = mLHS[35];

	mLHSrow51 = vec_xl(0,mLHS+4*8+4);
	mLHSrow52 = vec_xl(0,mLHS+4*9+4);
	mLHSrow53 = vec_splats((float)0);
	mLHSrow53[0] = mLHS[44];

	mLHSrow61 = vec_xl(0,mLHS+4*10+5);
	mLHSrow62 = vec_xl(0,mLHS+4*11+5);
	mLHSrow63 = vec_splats((float)0);
	mLHSrow63[0] = mLHS[53];
	
	mLHSrow71 = vec_xl(0,mLHS+4*12+6);
	mLHSrow72 = vec_xl(0,mLHS+4*13+6);
	mLHSrow73 = vec_splats((float)0);
	mLHSrow73[0] = mLHS[62];

	mLHSrow81 = vec_xl(0,mLHS+4*14+7);
	mLHSrow82 = vec_xl(0,mLHS+4*15+7);
	mLHSrow83 = vec_splats((float)0);
	mLHSrow83[0] = mLHS[71];

	mLHSrow91 = vec_xl(0,mLHS+4*16+8);
	mLHSrow92 = vec_xl(0,mLHS+4*17+8);
	mLHSrow93 = vec_splats((float)0);
	mLHSrow93[0] = mLHS[80];
//-----------------------------------------------------

	mRHSrow11 = vec_xl(0,mRHS);
	mRHSrow12 = vec_xl(0,mRHS+4);
	mRHSrow13 = vec_splats((float)0);
	mRHSrow13[0] = mRHS[8];

	mRHSrow21 = vec_xl(0,mRHS+4*2+1);
	mRHSrow22 = vec_xl(0,mRHS+4*3+1);
	mRHSrow23 = vec_splats((float)0);
	mRHSrow23[0] = mRHS[17];

	mRHSrow31 = vec_xl(0,mRHS+4*4+2);
	mRHSrow32 = vec_xl(0,mRHS+4*5+2);
	mRHSrow33 = vec_splats((float)0);
	mRHSrow33[0] = mRHS[26];

	mRHSrow41 = vec_xl(0,mRHS+4*6+3);
	mRHSrow42 = vec_xl(0,mRHS+4*7+3);
	mRHSrow43 = vec_splats((float)0);
	mRHSrow43[0] = mRHS[35];

	mRHSrow51 = vec_xl(0,mRHS+4*8+4);
	mRHSrow52 = vec_xl(0,mRHS+4*9+4);
	mRHSrow53 = vec_splats((float)0);
	mRHSrow53[0] = mRHS[44];

	mRHSrow61 = vec_xl(0,mRHS+4*10+5);
	mRHSrow62 = vec_xl(0,mRHS+4*11+5);
	mRHSrow63 = vec_splats((float)0);
	mRHSrow63[0] = mRHS[53];
	
	mRHSrow71 = vec_xl(0,mRHS+4*12+6);
	mRHSrow72 = vec_xl(0,mRHS+4*13+6);
	mRHSrow73 = vec_splats((float)0);
	mRHSrow73[0] = mRHS[62];

	mRHSrow81 = vec_xl(0,mRHS+4*14+7);
	mRHSrow82 = vec_xl(0,mRHS+4*15+7);
	mRHSrow83 = vec_splats((float)0);
	mRHSrow83[0] = mRHS[71];

	mRHSrow91 = vec_xl(0,mRHS+4*16+8);
	mRHSrow92 = vec_xl(0,mRHS+4*17+8);
	mRHSrow93 = vec_splats((float)0);
	mRHSrow93[0] = mRHS[80];

//===================================================================================
//Splat
//===================================================================================
	
	vector float aux11={mLHSrow11[0],mLHSrow11[0],mLHSrow11[0],mLHSrow11[0]};
	vector float aux12={mLHSrow21[0],mLHSrow21[0],mLHSrow21[0],mLHSrow21[0]};
	vector float aux13={mLHSrow31[0],mLHSrow31[0],mLHSrow31[0],mLHSrow31[0]};
	vector float aux14={mLHSrow41[0],mLHSrow41[0],mLHSrow41[0],mLHSrow41[0]};

	vector float aux15={mLHSrow51[0],mLHSrow51[0],mLHSrow51[0],mLHSrow51[0]};
	vector float aux16={mLHSrow61[0],mLHSrow61[0],mLHSrow61[0],mLHSrow61[0]};
	vector float aux17={mLHSrow71[0],mLHSrow71[0],mLHSrow71[0],mLHSrow71[0]};
	vector float aux18={mLHSrow81[0],mLHSrow81[0],mLHSrow81[0],mLHSrow81[0]};
	
	vector float aux19={mLHSrow91[0],mLHSrow91[0],mLHSrow91[0],mLHSrow91[0]};
//----------------------------------------------------------------------------------
	vector float aux21={mLHSrow11[1],mLHSrow11[1],mLHSrow11[1],mLHSrow11[1]};
	vector float aux22={mLHSrow21[1],mLHSrow21[1],mLHSrow21[1],mLHSrow21[1]};
	vector float aux23={mLHSrow31[1],mLHSrow31[1],mLHSrow31[1],mLHSrow31[1]};
	vector float aux24={mLHSrow41[1],mLHSrow41[1],mLHSrow41[1],mLHSrow41[1]};

	vector float aux25={mLHSrow51[1],mLHSrow51[1],mLHSrow51[1],mLHSrow51[1]};
	vector float aux26={mLHSrow61[1],mLHSrow61[1],mLHSrow61[1],mLHSrow61[1]};
	vector float aux27={mLHSrow71[1],mLHSrow71[1],mLHSrow71[1],mLHSrow71[1]};
	vector float aux28={mLHSrow81[1],mLHSrow81[1],mLHSrow81[1],mLHSrow81[1]};
	
	vector float aux29={mLHSrow91[1],mLHSrow91[1],mLHSrow91[1],mLHSrow91[1]};
//----------------------------------------------------------------------------------
	vector float aux31={mLHSrow11[2],mLHSrow11[2],mLHSrow11[2],mLHSrow11[2]};
	vector float aux32={mLHSrow21[2],mLHSrow21[2],mLHSrow21[2],mLHSrow21[2]};
	vector float aux33={mLHSrow31[2],mLHSrow31[2],mLHSrow31[2],mLHSrow31[2]};
	vector float aux34={mLHSrow41[2],mLHSrow41[2],mLHSrow41[2],mLHSrow41[2]};

	vector float aux35={mLHSrow51[2],mLHSrow51[2],mLHSrow51[2],mLHSrow51[2]};
	vector float aux36={mLHSrow61[2],mLHSrow61[2],mLHSrow61[2],mLHSrow61[2]};
	vector float aux37={mLHSrow71[2],mLHSrow71[2],mLHSrow71[2],mLHSrow71[2]};
	vector float aux38={mLHSrow81[2],mLHSrow81[2],mLHSrow81[2],mLHSrow81[2]};
	
	vector float aux39={mLHSrow91[2],mLHSrow91[2],mLHSrow91[2],mLHSrow91[2]};
//----------------------------------------------------------------------------------
	vector float aux41={mLHSrow11[3],mLHSrow11[3],mLHSrow11[3],mLHSrow11[3]};
	vector float aux42={mLHSrow21[3],mLHSrow21[3],mLHSrow21[3],mLHSrow21[3]};
	vector float aux43={mLHSrow31[3],mLHSrow31[3],mLHSrow31[3],mLHSrow31[3]};
	vector float aux44={mLHSrow41[3],mLHSrow41[3],mLHSrow41[3],mLHSrow41[3]};

	vector float aux45={mLHSrow51[3],mLHSrow51[3],mLHSrow51[3],mLHSrow51[3]};
	vector float aux46={mLHSrow61[3],mLHSrow61[3],mLHSrow61[3],mLHSrow61[3]};
	vector float aux47={mLHSrow71[3],mLHSrow71[3],mLHSrow71[3],mLHSrow71[3]};
	vector float aux48={mLHSrow81[3],mLHSrow81[3],mLHSrow81[3],mLHSrow81[3]};
	
	vector float aux49={mLHSrow91[3],mLHSrow91[3],mLHSrow91[3],mLHSrow91[3]};
//----------------------------------------------------------------------------------
	vector float aux51={mLHSrow12[0],mLHSrow12[0],mLHSrow12[0],mLHSrow12[0]};
	vector float aux52={mLHSrow22[0],mLHSrow22[0],mLHSrow22[0],mLHSrow22[0]};
	vector float aux53={mLHSrow32[0],mLHSrow32[0],mLHSrow32[0],mLHSrow32[0]};
	vector float aux54={mLHSrow42[0],mLHSrow42[0],mLHSrow42[0],mLHSrow42[0]};

	vector float aux55={mLHSrow52[0],mLHSrow52[0],mLHSrow52[0],mLHSrow52[0]};
	vector float aux56={mLHSrow62[0],mLHSrow62[0],mLHSrow62[0],mLHSrow62[0]};
	vector float aux57={mLHSrow72[0],mLHSrow72[0],mLHSrow72[0],mLHSrow72[0]};
	vector float aux58={mLHSrow82[0],mLHSrow82[0],mLHSrow82[0],mLHSrow82[0]};
	
	vector float aux59={mLHSrow92[0],mLHSrow92[0],mLHSrow92[0],mLHSrow92[0]};
//----------------------------------------------------------------------------------
	vector float aux61={mLHSrow12[1],mLHSrow12[1],mLHSrow12[1],mLHSrow12[1]};
	vector float aux62={mLHSrow22[1],mLHSrow22[1],mLHSrow22[1],mLHSrow22[1]};
	vector float aux63={mLHSrow32[1],mLHSrow32[1],mLHSrow32[1],mLHSrow32[1]};
	vector float aux64={mLHSrow42[1],mLHSrow42[1],mLHSrow42[1],mLHSrow42[1]};

	vector float aux65={mLHSrow52[1],mLHSrow52[1],mLHSrow52[1],mLHSrow52[1]};
	vector float aux66={mLHSrow62[1],mLHSrow62[1],mLHSrow62[1],mLHSrow62[1]};
	vector float aux67={mLHSrow72[1],mLHSrow72[1],mLHSrow72[1],mLHSrow72[1]};
	vector float aux68={mLHSrow82[1],mLHSrow82[1],mLHSrow82[1],mLHSrow82[1]};
	
	vector float aux69={mLHSrow92[1],mLHSrow92[1],mLHSrow92[1],mLHSrow92[1]};
//----------------------------------------------------------------------------------
	vector float aux71={mLHSrow12[2],mLHSrow12[2],mLHSrow12[2],mLHSrow12[2]};
	vector float aux72={mLHSrow22[2],mLHSrow22[2],mLHSrow22[2],mLHSrow22[2]};
	vector float aux73={mLHSrow32[2],mLHSrow32[2],mLHSrow32[2],mLHSrow32[2]};
	vector float aux74={mLHSrow42[2],mLHSrow42[2],mLHSrow42[2],mLHSrow42[2]};

	vector float aux75={mLHSrow52[2],mLHSrow52[2],mLHSrow52[2],mLHSrow52[2]};
	vector float aux76={mLHSrow62[2],mLHSrow62[2],mLHSrow62[2],mLHSrow62[2]};
	vector float aux77={mLHSrow72[2],mLHSrow72[2],mLHSrow72[2],mLHSrow72[2]};
	vector float aux78={mLHSrow82[2],mLHSrow82[2],mLHSrow82[2],mLHSrow82[2]};
	
	vector float aux79={mLHSrow92[2],mLHSrow92[2],mLHSrow92[2],mLHSrow92[2]};
//----------------------------------------------------------------------------------
	vector float aux81={mLHSrow12[3],mLHSrow12[3],mLHSrow12[3],mLHSrow12[3]};
	vector float aux82={mLHSrow22[3],mLHSrow22[3],mLHSrow22[3],mLHSrow22[3]};
	vector float aux83={mLHSrow32[3],mLHSrow32[3],mLHSrow32[3],mLHSrow32[3]};
	vector float aux84={mLHSrow42[3],mLHSrow42[3],mLHSrow42[3],mLHSrow42[3]};

	vector float aux85={mLHSrow52[3],mLHSrow52[3],mLHSrow52[3],mLHSrow52[3]};
	vector float aux86={mLHSrow62[3],mLHSrow62[3],mLHSrow62[3],mLHSrow62[3]};
	vector float aux87={mLHSrow72[3],mLHSrow72[3],mLHSrow72[3],mLHSrow72[3]};
	vector float aux88={mLHSrow82[3],mLHSrow82[3],mLHSrow82[3],mLHSrow82[3]};
	
	vector float aux89={mLHSrow92[3],mLHSrow92[3],mLHSrow92[3],mLHSrow92[3]};
//----------------------------------------------------------------------------------
	vector float aux91={mLHSrow13[0],mLHSrow13[0],mLHSrow13[0],mLHSrow13[0]};
	vector float aux92={mLHSrow23[0],mLHSrow23[0],mLHSrow23[0],mLHSrow23[0]};
	vector float aux93={mLHSrow33[0],mLHSrow33[0],mLHSrow33[0],mLHSrow33[0]};
	vector float aux94={mLHSrow43[0],mLHSrow43[0],mLHSrow43[0],mLHSrow43[0]};

	vector float aux95={mLHSrow53[0],mLHSrow53[0],mLHSrow53[0],mLHSrow53[0]};
	vector float aux96={mLHSrow63[0],mLHSrow63[0],mLHSrow63[0],mLHSrow63[0]};
	vector float aux97={mLHSrow73[0],mLHSrow73[0],mLHSrow73[0],mLHSrow73[0]};
	vector float aux98={mLHSrow83[0],mLHSrow83[0],mLHSrow83[0],mLHSrow83[0]};
	
	vector float aux99={mLHSrow93[0],mLHSrow93[0],mLHSrow93[0],mLHSrow93[0]};
//----------------------------------------------------------------------------------


//row1
	vec_xst(vec_madd( mRHSrow91, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux21, vec_mul(mRHSrow11, aux11)),
					vec_madd(mRHSrow41, aux41, vec_mul(mRHSrow31, aux31)) ),
				vec_add(
					vec_madd(mRHSrow61, aux61, vec_mul(mRHSrow51, aux51)),
					vec_madd(mRHSrow81, aux81, vec_mul(mRHSrow71, aux71)) ) ) ),

				0, mResult);	

	
	vec_xst(vec_madd( mRHSrow92, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux21, vec_mul(mRHSrow12, aux11)),
					vec_madd(mRHSrow42, aux41, vec_mul(mRHSrow32, aux31)) ),
				vec_add(
					vec_madd(mRHSrow62, aux61, vec_mul(mRHSrow52, aux51)),
					vec_madd(mRHSrow82, aux81, vec_mul(mRHSrow72, aux71)) ) ) ),

				0, mResult+4);

	vec_xst(vec_madd( mRHSrow93, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux21, vec_mul(mRHSrow13, aux11)),
					vec_madd(mRHSrow43, aux41, vec_mul(mRHSrow33, aux31)) ),
				vec_add(
					vec_madd(mRHSrow63, aux61, vec_mul(mRHSrow53, aux51)),
					vec_madd(mRHSrow83, aux81, vec_mul(mRHSrow73, aux71)) ) ) ),

				0, mResult+8);	
//row 2


	vec_xst(vec_madd( mRHSrow91, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux22, vec_mul(mRHSrow11, aux12)),
					vec_madd(mRHSrow41, aux42, vec_mul(mRHSrow31, aux32)) ),
				vec_add(
					vec_madd(mRHSrow61, aux62, vec_mul(mRHSrow51, aux52)),
					vec_madd(mRHSrow81, aux82, vec_mul(mRHSrow71, aux72)) ) ) ),

				0, mResult+4*2+1);

	vec_xst(vec_madd( mRHSrow92, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux22, vec_mul(mRHSrow12, aux12)),
					vec_madd(mRHSrow42, aux42, vec_mul(mRHSrow32, aux32)) ),
				vec_add(
					vec_madd(mRHSrow62, aux62, vec_mul(mRHSrow52, aux52)),
					vec_madd(mRHSrow82, aux82, vec_mul(mRHSrow72, aux72)) ) ) ),

				0, mResult+4*3+1);


	vec_xst(vec_madd( mRHSrow93, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux22, vec_mul(mRHSrow13, aux12)),
					vec_madd(mRHSrow43, aux42, vec_mul(mRHSrow33, aux32)) ),
				vec_add(
					vec_madd(mRHSrow63, aux62, vec_mul(mRHSrow53, aux52)),
					vec_madd(mRHSrow83, aux82, vec_mul(mRHSrow73, aux72)) ) ) ),

				0, mResult+17);

//row 3

	vec_xst(vec_madd( mRHSrow91, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux23, vec_mul(mRHSrow11, aux13)),
					vec_madd(mRHSrow41, aux43, vec_mul(mRHSrow31, aux33)) ),
				vec_add(
					vec_madd(mRHSrow61, aux63, vec_mul(mRHSrow51, aux53)),
					vec_madd(mRHSrow81, aux83, vec_mul(mRHSrow71, aux73)) ) ) ),

				0, mResult+4*4+2);

	vec_xst(vec_madd( mRHSrow92, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux23, vec_mul(mRHSrow12, aux13)),
					vec_madd(mRHSrow42, aux43, vec_mul(mRHSrow32, aux33)) ),
				vec_add(
					vec_madd(mRHSrow62, aux63, vec_mul(mRHSrow52, aux53)),
					vec_madd(mRHSrow82, aux83, vec_mul(mRHSrow72, aux73)) ) ) ),

				0, mResult+4*5+2);


	vec_xst(vec_madd( mRHSrow93, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux23, vec_mul(mRHSrow13, aux13)),
					vec_madd(mRHSrow43, aux43, vec_mul(mRHSrow33, aux33)) ),
				vec_add(
					vec_madd(mRHSrow63, aux63, vec_mul(mRHSrow53, aux53)),
					vec_madd(mRHSrow83, aux83, vec_mul(mRHSrow73, aux73)) ) ) ),

				0, mResult+26);
//row 4


	vec_xst(vec_madd( mRHSrow91, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux24, vec_mul(mRHSrow11, aux14)),
					vec_madd(mRHSrow41, aux44, vec_mul(mRHSrow31, aux34)) ),
				vec_add(
					vec_madd(mRHSrow61, aux64, vec_mul(mRHSrow51, aux54)),
					vec_madd(mRHSrow81, aux84, vec_mul(mRHSrow71, aux74)) ) ) ),

				0, mResult+4*6+3);

	vec_xst(vec_madd( mRHSrow92, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux24, vec_mul(mRHSrow12, aux14)),
					vec_madd(mRHSrow42, aux44, vec_mul(mRHSrow32, aux34)) ),
				vec_add(
					vec_madd(mRHSrow62, aux64, vec_mul(mRHSrow52, aux54)),
					vec_madd(mRHSrow82, aux84, vec_mul(mRHSrow72, aux74)) ) ) ),

				0, mResult+4*7+3);

	vec_xst(vec_madd( mRHSrow93, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux24, vec_mul(mRHSrow13, aux14)),
					vec_madd(mRHSrow43, aux44, vec_mul(mRHSrow33, aux34)) ),
				vec_add(
					vec_madd(mRHSrow63, aux64, vec_mul(mRHSrow53, aux54)),
					vec_madd(mRHSrow83, aux84, vec_mul(mRHSrow73, aux74)) ) ) ),

				0, mResult+35);
//row 5


	vec_xst(vec_madd( mRHSrow91, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux25, vec_mul(mRHSrow11, aux15)),
					vec_madd(mRHSrow41, aux45, vec_mul(mRHSrow31, aux35)) ),
				vec_add(
					vec_madd(mRHSrow61, aux65, vec_mul(mRHSrow51, aux55)),
					vec_madd(mRHSrow81, aux85, vec_mul(mRHSrow71, aux75)) ) ) ),

				0, mResult+4*8+4);



	vec_xst(vec_madd( mRHSrow92, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux25, vec_mul(mRHSrow12, aux15)),
					vec_madd(mRHSrow42, aux45, vec_mul(mRHSrow32, aux35)) ),
				vec_add(
					vec_madd(mRHSrow62, aux65, vec_mul(mRHSrow52, aux55)),
					vec_madd(mRHSrow82, aux85, vec_mul(mRHSrow72, aux75)) ) ) ),

				0, mResult+4*9+4);


	vec_xst(vec_madd( mRHSrow93, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux25, vec_mul(mRHSrow13, aux15)),
					vec_madd(mRHSrow43, aux45, vec_mul(mRHSrow33, aux35)) ),
				vec_add(
					vec_madd(mRHSrow63, aux65, vec_mul(mRHSrow53, aux55)),
					vec_madd(mRHSrow83, aux85, vec_mul(mRHSrow73, aux75)) ) ) ),

				0, mResult+44);

//row 6


	vec_xst(vec_madd( mRHSrow91, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux26, vec_mul(mRHSrow11, aux16)),
					vec_madd(mRHSrow41, aux46, vec_mul(mRHSrow31, aux36)) ),
				vec_add(
					vec_madd(mRHSrow61, aux66, vec_mul(mRHSrow51, aux56)),
					vec_madd(mRHSrow81, aux86, vec_mul(mRHSrow71, aux76)) ) ) ),

				0, mResult+4*10+5);


	vec_xst(vec_madd( mRHSrow92, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux26, vec_mul(mRHSrow12, aux16)),
					vec_madd(mRHSrow42, aux46, vec_mul(mRHSrow32, aux36)) ),
				vec_add(
					vec_madd(mRHSrow62, aux66, vec_mul(mRHSrow52, aux56)),
					vec_madd(mRHSrow82, aux86, vec_mul(mRHSrow72, aux76)) ) ) ),

				0, mResult+4*11+5);


	vec_xst(vec_madd( mRHSrow93, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux26, vec_mul(mRHSrow13, aux16)),
					vec_madd(mRHSrow43, aux46, vec_mul(mRHSrow33, aux36)) ),
				vec_add(
					vec_madd(mRHSrow63, aux66, vec_mul(mRHSrow53, aux56)),
					vec_madd(mRHSrow83, aux86, vec_mul(mRHSrow73, aux76)) ) ) ),

				0, mResult+53);

//row 7

	vec_xst(vec_madd( mRHSrow91, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux27, vec_mul(mRHSrow11, aux17)),
					vec_madd(mRHSrow41, aux47, vec_mul(mRHSrow31, aux37)) ),
				vec_add(
					vec_madd(mRHSrow61, aux67, vec_mul(mRHSrow51, aux57)),
					vec_madd(mRHSrow81, aux87, vec_mul(mRHSrow71, aux77)) ) ) ),

				0, mResult+4*12+6);

	vec_xst(vec_madd( mRHSrow92, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux27, vec_mul(mRHSrow12, aux17)),
					vec_madd(mRHSrow42, aux47, vec_mul(mRHSrow32, aux37)) ),
				vec_add(
					vec_madd(mRHSrow62, aux67, vec_mul(mRHSrow52, aux57)),
					vec_madd(mRHSrow82, aux87, vec_mul(mRHSrow72, aux77)) ) ) ),

				0, mResult+4*13+6);


	vec_xst(vec_madd( mRHSrow93, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux27, vec_mul(mRHSrow13, aux17)),
					vec_madd(mRHSrow43, aux47, vec_mul(mRHSrow33, aux37)) ),
				vec_add(
					vec_madd(mRHSrow63, aux67, vec_mul(mRHSrow53, aux57)),
					vec_madd(mRHSrow83, aux87, vec_mul(mRHSrow73, aux77)) ) ) ),

				0, mResult+62);
//row 8



	vec_xst(vec_madd( mRHSrow91, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux28, vec_mul(mRHSrow11, aux18)),
					vec_madd(mRHSrow41, aux48, vec_mul(mRHSrow31, aux38)) ),
				vec_add(
					vec_madd(mRHSrow61, aux68, vec_mul(mRHSrow51, aux58)),
					vec_madd(mRHSrow81, aux88, vec_mul(mRHSrow71, aux78)) ) ) ),

				0, mResult+4*14+7);


	vec_xst(vec_madd( mRHSrow92, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux28, vec_mul(mRHSrow12, aux18)),
					vec_madd(mRHSrow42, aux48, vec_mul(mRHSrow32, aux38)) ),
				vec_add(
					vec_madd(mRHSrow62, aux68, vec_mul(mRHSrow52, aux58)),
					vec_madd(mRHSrow82, aux88, vec_mul(mRHSrow72, aux78)) ) ) ),

				0, mResult+4*15+7);


	vec_xst(vec_madd( mRHSrow93, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux28, vec_mul(mRHSrow13, aux18)),
					vec_madd(mRHSrow43, aux48, vec_mul(mRHSrow33, aux38)) ),
				vec_add(
					vec_madd(mRHSrow63, aux68, vec_mul(mRHSrow53, aux58)),
					vec_madd(mRHSrow83, aux88, vec_mul(mRHSrow73, aux78)) ) ) ),

				0, mResult+71);

//row 9


	vec_xst(vec_madd( mRHSrow91, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux29, vec_mul(mRHSrow11, aux19)),
					vec_madd(mRHSrow41, aux49, vec_mul(mRHSrow31, aux39)) ),
				vec_add(
					vec_madd(mRHSrow61, aux69, vec_mul(mRHSrow51, aux59)),
					vec_madd(mRHSrow81, aux89, vec_mul(mRHSrow71, aux79)) ) ) ),

				0, mResult+4*16+8);

	vec_xst(vec_madd( mRHSrow92, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux29, vec_mul(mRHSrow12, aux19)),
					vec_madd(mRHSrow42, aux49, vec_mul(mRHSrow32, aux39)) ),
				vec_add(
					vec_madd(mRHSrow62, aux69, vec_mul(mRHSrow52, aux59)),
					vec_madd(mRHSrow82, aux89, vec_mul(mRHSrow72, aux79)) ) ) ),

				0, mResult+4*17+8);


	vector float mResultLastElem = 
		
		vec_madd( mRHSrow93, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux29, vec_mul(mRHSrow13, aux19)),
					vec_madd(mRHSrow43, aux49, vec_mul(mRHSrow33, aux39)) ),
				vec_add(
					vec_madd(mRHSrow63, aux69, vec_mul(mRHSrow53, aux59)),
					vec_madd(mRHSrow83, aux89, vec_mul(mRHSrow73, aux79)) ) ) );
	mResult[80] = mResultLastElem[0];



}


inline void mul12x12RowMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHSrow11, mLHSrow12, mLHSrow13, mLHSrow21, mLHSrow22, mLHSrow23, mLHSrow31, mLHSrow32, mLHSrow33,
	      	     mLHSrow41, mLHSrow42, mLHSrow43, mLHSrow51, mLHSrow52, mLHSrow53, mLHSrow61, mLHSrow62, mLHSrow63,
		     mLHSrow71, mLHSrow72, mLHSrow73, mLHSrow81, mLHSrow82, mLHSrow83, mLHSrow91, mLHSrow92, mLHSrow93, mLHSrow101, mLHSrow102, mLHSrow103, mLHSrow111,
		     mLHSrow112,mLHSrow113,mLHSrow121,mLHSrow122, mLHSrow123;

	vector float mRHSrow11, mRHSrow12, mRHSrow13, mRHSrow21, mRHSrow22, mRHSrow23, mRHSrow31, mRHSrow32, mRHSrow33,
	      	     mRHSrow41, mRHSrow42, mRHSrow43, mRHSrow51, mRHSrow52, mRHSrow53, mRHSrow61, mRHSrow62, mRHSrow63,
		     mRHSrow71, mRHSrow72, mRHSrow73, mRHSrow81, mRHSrow82, mRHSrow83, mRHSrow91, mRHSrow92, mRHSrow93, mRHSrow101, mRHSrow102, mRHSrow103, mRHSrow111,
		     mRHSrow112, mRHSrow113,  mRHSrow121, mRHSrow122, mRHSrow123;
//load


	mRHSrow11 = vec_xl(0,mRHS);
	mRHSrow12 = vec_xl(0,mRHS+4);
	mRHSrow13 = vec_xl(0,mRHS+4*2);

	mRHSrow21 = vec_xl(0,mRHS+4*3);
	mRHSrow22 = vec_xl(0,mRHS+4*4);
	mRHSrow23 = vec_xl(0,mRHS+4*5);

	mRHSrow31 = vec_xl(0,mRHS+4*6);
	mRHSrow32 = vec_xl(0,mRHS+4*7);
	mRHSrow33 = vec_xl(0,mRHS+4*8);

	mRHSrow41 = vec_xl(0,mRHS+4*9);
	mRHSrow42 = vec_xl(0,mRHS+4*10);
	mRHSrow43 = vec_xl(0,mRHS+4*11);

	mRHSrow51 = vec_xl(0,mRHS+4*12);
	mRHSrow52 = vec_xl(0,mRHS+4*13);
	mRHSrow53 = vec_xl(0,mRHS+4*14);

	mRHSrow61 = vec_xl(0,mRHS+4*15);
	mRHSrow62 = vec_xl(0,mRHS+4*16);
	mRHSrow63 = vec_xl(0,mRHS+4*17);

	mRHSrow71 = vec_xl(0,mRHS+4*18);
	mRHSrow72 = vec_xl(0,mRHS+4*19);
	mRHSrow73 = vec_xl(0,mRHS+4*20);

	mRHSrow81 = vec_xl(0,mRHS+4*21);
	mRHSrow82 = vec_xl(0,mRHS+4*22);
	mRHSrow83 = vec_xl(0,mRHS+4*23);

	mRHSrow91 = vec_xl(0,mRHS+4*24);
	mRHSrow92 = vec_xl(0,mRHS+4*25);
	mRHSrow93 = vec_xl(0,mRHS+4*26);

	mRHSrow101 = vec_xl(0,mRHS+4*27);
	mRHSrow102 = vec_xl(0,mRHS+4*28);
	mRHSrow103 = vec_xl(0,mRHS+4*29);

	mRHSrow111 = vec_xl(0,mRHS+4*30);
	mRHSrow112 = vec_xl(0,mRHS+4*31);
	mRHSrow113 = vec_xl(0,mRHS+4*32);

	mRHSrow121 = vec_xl(0,mRHS+4*33);
	mRHSrow122 = vec_xl(0,mRHS+4*34);
	mRHSrow123 = vec_xl(0,mRHS+4*35);

	//--------------------------------------------------
	mLHSrow11 = vec_xl(0,mLHS);
	mLHSrow12 = vec_xl(0,mLHS+4);
	mLHSrow13 = vec_xl(0,mLHS+4*2);

	mLHSrow21 = vec_xl(0,mLHS+4*3);
	mLHSrow22 = vec_xl(0,mLHS+4*4);
	mLHSrow23 = vec_xl(0,mLHS+4*5);

	mLHSrow31 = vec_xl(0,mLHS+4*6);
	mLHSrow32 = vec_xl(0,mLHS+4*7);
	mLHSrow33 = vec_xl(0,mLHS+4*8);

	mLHSrow41 = vec_xl(0,mLHS+4*9);
	mLHSrow42 = vec_xl(0,mLHS+4*10);
	mLHSrow43 = vec_xl(0,mLHS+4*11);

	mLHSrow51 = vec_xl(0,mLHS+4*12);
	mLHSrow52 = vec_xl(0,mLHS+4*13);
	mLHSrow53 = vec_xl(0,mLHS+4*14);

	mLHSrow61 = vec_xl(0,mLHS+4*15);
	mLHSrow62 = vec_xl(0,mLHS+4*16);
	mLHSrow63 = vec_xl(0,mLHS+4*17);

	mLHSrow71 = vec_xl(0,mLHS+4*18);
	mLHSrow72 = vec_xl(0,mLHS+4*19);
	mLHSrow73 = vec_xl(0,mLHS+4*20);

	mLHSrow81 = vec_xl(0,mLHS+4*21);
	mLHSrow82 = vec_xl(0,mLHS+4*22);
	mLHSrow83 = vec_xl(0,mLHS+4*23);

	mLHSrow91 = vec_xl(0,mLHS+4*24);
	mLHSrow92 = vec_xl(0,mLHS+4*25);
	mLHSrow93 = vec_xl(0,mLHS+4*26);

	mLHSrow101 = vec_xl(0,mLHS+4*27);
	mLHSrow102 = vec_xl(0,mLHS+4*28);
	mLHSrow103 = vec_xl(0,mLHS+4*29);

	mLHSrow111 = vec_xl(0,mLHS+4*30);
	mLHSrow112 = vec_xl(0,mLHS+4*31);
	mLHSrow113 = vec_xl(0,mLHS+4*32);

	mLHSrow121 = vec_xl(0,mLHS+4*33);
	mLHSrow122 = vec_xl(0,mLHS+4*34);
	mLHSrow123 = vec_xl(0,mLHS+4*35);

//-------------------------------------------------------------------------

	vector float aux11={mLHSrow11[0],mLHSrow11[0],mLHSrow11[0],mLHSrow11[0]};
	vector float aux12={mLHSrow21[0],mLHSrow21[0],mLHSrow21[0],mLHSrow21[0]};
	vector float aux13={mLHSrow31[0],mLHSrow31[0],mLHSrow31[0],mLHSrow31[0]};
	vector float aux14={mLHSrow41[0],mLHSrow41[0],mLHSrow41[0],mLHSrow41[0]};

	vector float aux15={mLHSrow51[0],mLHSrow51[0],mLHSrow51[0],mLHSrow51[0]};
	vector float aux16={mLHSrow61[0],mLHSrow61[0],mLHSrow61[0],mLHSrow61[0]};
	vector float aux17={mLHSrow71[0],mLHSrow71[0],mLHSrow71[0],mLHSrow71[0]};
	vector float aux18={mLHSrow81[0],mLHSrow81[0],mLHSrow81[0],mLHSrow81[0]};

	vector float aux19={mLHSrow91[0],mLHSrow91[0],mLHSrow91[0],mLHSrow91[0]};
	vector float aux110={mLHSrow101[0],mLHSrow101[0],mLHSrow101[0],mLHSrow101[0]};
	vector float aux0111={mLHSrow111[0],mLHSrow111[0],mLHSrow111[0],mLHSrow111[0]};
	vector float aux0112={mLHSrow121[0],mLHSrow121[0],mLHSrow121[0],mLHSrow121[0]};

//-------------------------------------------------------------------------
	vector float aux21={mLHSrow11[1],mLHSrow11[1],mLHSrow11[1],mLHSrow11[1]};
	vector float aux22={mLHSrow21[1],mLHSrow21[1],mLHSrow21[1],mLHSrow21[1]};
	vector float aux23={mLHSrow31[1],mLHSrow31[1],mLHSrow31[1],mLHSrow31[1]};
	vector float aux24={mLHSrow41[1],mLHSrow41[1],mLHSrow41[1],mLHSrow41[1]};

	vector float aux25={mLHSrow51[1],mLHSrow51[1],mLHSrow51[1],mLHSrow51[1]};
	vector float aux26={mLHSrow61[1],mLHSrow61[1],mLHSrow61[1],mLHSrow61[1]};
	vector float aux27={mLHSrow71[1],mLHSrow71[1],mLHSrow71[1],mLHSrow71[1]};
	vector float aux28={mLHSrow81[1],mLHSrow81[1],mLHSrow81[1],mLHSrow81[1]};

	vector float aux29={mLHSrow91[1],mLHSrow91[1],mLHSrow91[1],mLHSrow91[1]};
	vector float aux210={mLHSrow101[1],mLHSrow101[1],mLHSrow101[1],mLHSrow101[1]};
	vector float aux211={mLHSrow111[1],mLHSrow111[1],mLHSrow111[1],mLHSrow111[1]};
	vector float aux212={mLHSrow121[1],mLHSrow121[1],mLHSrow121[1],mLHSrow121[1]};

//-------------------------------------------------------------------------
	vector float aux31={mLHSrow11[2],mLHSrow11[2],mLHSrow11[2],mLHSrow11[2]};
	vector float aux32={mLHSrow21[2],mLHSrow21[2],mLHSrow21[2],mLHSrow21[2]};
	vector float aux33={mLHSrow31[2],mLHSrow31[2],mLHSrow31[2],mLHSrow31[2]};
	vector float aux34={mLHSrow41[2],mLHSrow41[2],mLHSrow41[2],mLHSrow41[2]};

	vector float aux35={mLHSrow51[2],mLHSrow51[2],mLHSrow51[2],mLHSrow51[2]};
	vector float aux36={mLHSrow61[2],mLHSrow61[2],mLHSrow61[2],mLHSrow61[2]};
	vector float aux37={mLHSrow71[2],mLHSrow71[2],mLHSrow71[2],mLHSrow71[2]};
	vector float aux38={mLHSrow81[2],mLHSrow81[2],mLHSrow81[2],mLHSrow81[2]};

	vector float aux39={mLHSrow91[2],mLHSrow91[2],mLHSrow91[2],mLHSrow91[2]};
	vector float aux310={mLHSrow101[2],mLHSrow101[2],mLHSrow101[2],mLHSrow101[2]};
	vector float aux311={mLHSrow111[2],mLHSrow111[2],mLHSrow111[2],mLHSrow111[2]};
	vector float aux312={mLHSrow121[2],mLHSrow121[2],mLHSrow121[2],mLHSrow121[2]};

//-------------------------------------------------------------------------
	vector float aux41={mLHSrow11[3],mLHSrow11[3],mLHSrow11[3],mLHSrow11[3]};
	vector float aux42={mLHSrow21[3],mLHSrow21[3],mLHSrow21[3],mLHSrow21[3]};
	vector float aux43={mLHSrow31[3],mLHSrow31[3],mLHSrow31[3],mLHSrow31[3]};
	vector float aux44={mLHSrow41[3],mLHSrow41[3],mLHSrow41[3],mLHSrow41[3]};

	vector float aux45={mLHSrow51[3],mLHSrow51[3],mLHSrow51[3],mLHSrow51[3]};
	vector float aux46={mLHSrow61[3],mLHSrow61[3],mLHSrow61[3],mLHSrow61[3]};
	vector float aux47={mLHSrow71[3],mLHSrow71[3],mLHSrow71[3],mLHSrow71[3]};
	vector float aux48={mLHSrow81[3],mLHSrow81[3],mLHSrow81[3],mLHSrow81[3]};

	vector float aux49={mLHSrow91[3],mLHSrow91[3],mLHSrow91[3],mLHSrow91[3]};
	vector float aux410={mLHSrow101[3],mLHSrow101[3],mLHSrow101[3],mLHSrow101[3]};
	vector float aux411={mLHSrow111[3],mLHSrow111[3],mLHSrow111[3],mLHSrow111[3]};
	vector float aux412={mLHSrow121[3],mLHSrow121[3],mLHSrow121[3],mLHSrow121[3]};

//-------------------------------------------------------------------------

	vector float aux51={mLHSrow12[0],mLHSrow12[0],mLHSrow12[0],mLHSrow12[0]};
	vector float aux52={mLHSrow22[0],mLHSrow22[0],mLHSrow22[0],mLHSrow22[0]};
	vector float aux53={mLHSrow32[0],mLHSrow32[0],mLHSrow32[0],mLHSrow32[0]};
	vector float aux54={mLHSrow42[0],mLHSrow42[0],mLHSrow42[0],mLHSrow42[0]};

	vector float aux55={mLHSrow52[0],mLHSrow52[0],mLHSrow52[0],mLHSrow52[0]};
	vector float aux56={mLHSrow62[0],mLHSrow62[0],mLHSrow62[0],mLHSrow62[0]};
	vector float aux57={mLHSrow72[0],mLHSrow72[0],mLHSrow72[0],mLHSrow72[0]};
	vector float aux58={mLHSrow82[0],mLHSrow82[0],mLHSrow82[0],mLHSrow82[0]};

	vector float aux59={mLHSrow92[0],mLHSrow92[0],mLHSrow92[0],mLHSrow92[0]};
	vector float aux510={mLHSrow102[0],mLHSrow102[0],mLHSrow102[0],mLHSrow102[0]};
	vector float aux511={mLHSrow112[0],mLHSrow112[0],mLHSrow112[0],mLHSrow112[0]};
	vector float aux512={mLHSrow122[0],mLHSrow122[0],mLHSrow122[0],mLHSrow122[0]};

//-------------------------------------------------------------------------
	vector float aux61={mLHSrow12[1],mLHSrow12[1],mLHSrow12[1],mLHSrow12[1]};
	vector float aux62={mLHSrow22[1],mLHSrow22[1],mLHSrow22[1],mLHSrow22[1]};
	vector float aux63={mLHSrow32[1],mLHSrow32[1],mLHSrow32[1],mLHSrow32[1]};
	vector float aux64={mLHSrow42[1],mLHSrow42[1],mLHSrow42[1],mLHSrow42[1]};

	vector float aux65={mLHSrow52[1],mLHSrow52[1],mLHSrow52[1],mLHSrow52[1]};
	vector float aux66={mLHSrow62[1],mLHSrow62[1],mLHSrow62[1],mLHSrow62[1]};
	vector float aux67={mLHSrow72[1],mLHSrow72[1],mLHSrow72[1],mLHSrow72[1]};
	vector float aux68={mLHSrow82[1],mLHSrow82[1],mLHSrow82[1],mLHSrow82[1]};

	vector float aux69={mLHSrow92[1],mLHSrow92[1],mLHSrow92[1],mLHSrow92[1]};
	vector float aux610={mLHSrow102[1],mLHSrow102[1],mLHSrow102[1],mLHSrow102[1]};
	vector float aux611={mLHSrow112[1],mLHSrow112[1],mLHSrow112[1],mLHSrow112[1]};
	vector float aux612={mLHSrow122[1],mLHSrow122[1],mLHSrow122[1],mLHSrow122[1]};

//-------------------------------------------------------------------------
	vector float aux71={mLHSrow12[2],mLHSrow12[2],mLHSrow12[2],mLHSrow12[2]};
	vector float aux72={mLHSrow22[2],mLHSrow22[2],mLHSrow22[2],mLHSrow22[2]};
	vector float aux73={mLHSrow32[2],mLHSrow32[2],mLHSrow32[2],mLHSrow32[2]};
	vector float aux74={mLHSrow42[2],mLHSrow42[2],mLHSrow42[2],mLHSrow42[2]};

	vector float aux75={mLHSrow52[2],mLHSrow52[2],mLHSrow52[2],mLHSrow52[2]};
	vector float aux76={mLHSrow62[2],mLHSrow62[2],mLHSrow62[2],mLHSrow62[2]};
	vector float aux77={mLHSrow72[2],mLHSrow72[2],mLHSrow72[2],mLHSrow72[2]};
	vector float aux78={mLHSrow82[2],mLHSrow82[2],mLHSrow82[2],mLHSrow82[2]};

	vector float aux79={mLHSrow92[2],mLHSrow92[2],mLHSrow92[2],mLHSrow92[2]};
	vector float aux710={mLHSrow102[2],mLHSrow102[2],mLHSrow102[2],mLHSrow102[2]};
	vector float aux711={mLHSrow112[2],mLHSrow112[2],mLHSrow112[2],mLHSrow112[2]};
	vector float aux712={mLHSrow122[2],mLHSrow122[2],mLHSrow122[2],mLHSrow122[2]};

//-------------------------------------------------------------------------
	vector float aux81={mLHSrow12[3],mLHSrow12[3],mLHSrow12[3],mLHSrow12[3]};
	vector float aux82={mLHSrow22[3],mLHSrow22[3],mLHSrow22[3],mLHSrow22[3]};
	vector float aux83={mLHSrow32[3],mLHSrow32[3],mLHSrow32[3],mLHSrow32[3]};
	vector float aux84={mLHSrow42[3],mLHSrow42[3],mLHSrow42[3],mLHSrow42[3]};

	vector float aux85={mLHSrow52[3],mLHSrow52[3],mLHSrow52[3],mLHSrow52[3]};
	vector float aux86={mLHSrow62[3],mLHSrow62[3],mLHSrow62[3],mLHSrow62[3]};
	vector float aux87={mLHSrow72[3],mLHSrow72[3],mLHSrow72[3],mLHSrow72[3]};
	vector float aux88={mLHSrow82[3],mLHSrow82[3],mLHSrow82[3],mLHSrow82[3]};

	vector float aux89={mLHSrow92[3],mLHSrow92[3],mLHSrow92[3],mLHSrow92[3]};
	vector float aux810={mLHSrow102[3],mLHSrow102[3],mLHSrow102[3],mLHSrow102[3]};
	vector float aux811={mLHSrow112[3],mLHSrow112[3],mLHSrow112[3],mLHSrow112[3]};
	vector float aux812={mLHSrow122[3],mLHSrow122[3],mLHSrow122[3],mLHSrow122[3]};

//-------------------------------------------------------------------------
	vector float aux91={mLHSrow13[0],mLHSrow13[0],mLHSrow13[0],mLHSrow13[0]};
	vector float aux92={mLHSrow23[0],mLHSrow23[0],mLHSrow23[0],mLHSrow23[0]};
	vector float aux93={mLHSrow33[0],mLHSrow33[0],mLHSrow33[0],mLHSrow33[0]};
	vector float aux94={mLHSrow43[0],mLHSrow43[0],mLHSrow43[0],mLHSrow43[0]};

	vector float aux95={mLHSrow53[0],mLHSrow53[0],mLHSrow53[0],mLHSrow53[0]};
	vector float aux96={mLHSrow63[0],mLHSrow63[0],mLHSrow63[0],mLHSrow63[0]};
	vector float aux97={mLHSrow73[0],mLHSrow73[0],mLHSrow73[0],mLHSrow73[0]};
	vector float aux98={mLHSrow83[0],mLHSrow83[0],mLHSrow83[0],mLHSrow83[0]};

	vector float aux99={mLHSrow93[0],mLHSrow93[0],mLHSrow93[0],mLHSrow93[0]};
	vector float aux910={mLHSrow103[0],mLHSrow103[0],mLHSrow103[0],mLHSrow103[0]};
	vector float aux911={mLHSrow113[0],mLHSrow113[0],mLHSrow113[0],mLHSrow113[0]};
	vector float aux912={mLHSrow123[0],mLHSrow123[0],mLHSrow123[0],mLHSrow123[0]};

//-------------------------------------------------------------------------
	vector float aux101={mLHSrow13[1],mLHSrow13[1],mLHSrow13[1],mLHSrow13[1]};
	vector float aux102={mLHSrow23[1],mLHSrow23[1],mLHSrow23[1],mLHSrow23[1]};
	vector float aux103={mLHSrow33[1],mLHSrow33[1],mLHSrow33[1],mLHSrow33[1]};
	vector float aux104={mLHSrow43[1],mLHSrow43[1],mLHSrow43[1],mLHSrow43[1]};

	vector float aux105={mLHSrow53[1],mLHSrow53[1],mLHSrow53[1],mLHSrow53[1]};
	vector float aux106={mLHSrow63[1],mLHSrow63[1],mLHSrow63[1],mLHSrow63[1]};
	vector float aux107={mLHSrow73[1],mLHSrow73[1],mLHSrow73[1],mLHSrow73[1]};
	vector float aux108={mLHSrow83[1],mLHSrow83[1],mLHSrow83[1],mLHSrow83[1]};

	vector float aux109={mLHSrow93[1],mLHSrow93[1],mLHSrow93[1],mLHSrow93[1]};
	vector float aux1010={mLHSrow103[1],mLHSrow103[1],mLHSrow103[1],mLHSrow103[1]};
	vector float aux1011={mLHSrow113[1],mLHSrow113[1],mLHSrow113[1],mLHSrow113[1]};
	vector float aux1012={mLHSrow123[1],mLHSrow123[1],mLHSrow123[1],mLHSrow123[1]};

//-------------------------------------------------------------------------
	vector float aux111={mLHSrow13[2],mLHSrow13[2],mLHSrow13[2],mLHSrow13[2]};
	vector float aux112={mLHSrow23[2],mLHSrow23[2],mLHSrow23[2],mLHSrow23[2]};
	vector float aux113={mLHSrow33[2],mLHSrow33[2],mLHSrow33[2],mLHSrow33[2]};
	vector float aux114={mLHSrow43[2],mLHSrow43[2],mLHSrow43[2],mLHSrow43[2]};

	vector float aux115={mLHSrow53[2],mLHSrow53[2],mLHSrow53[2],mLHSrow53[2]};
	vector float aux116={mLHSrow63[2],mLHSrow63[2],mLHSrow63[2],mLHSrow63[2]};
	vector float aux117={mLHSrow73[2],mLHSrow73[2],mLHSrow73[2],mLHSrow73[2]};
	vector float aux118={mLHSrow83[2],mLHSrow83[2],mLHSrow83[2],mLHSrow83[2]};

	vector float aux119={mLHSrow93[2],mLHSrow93[2],mLHSrow93[2],mLHSrow93[2]};
	vector float aux1110={mLHSrow103[2],mLHSrow103[2],mLHSrow103[2],mLHSrow103[2]};
	vector float aux1111={mLHSrow113[2],mLHSrow113[2],mLHSrow113[2],mLHSrow113[2]};
	vector float aux1112={mLHSrow123[2],mLHSrow123[2],mLHSrow123[2],mLHSrow123[2]};

//-------------------------------------------------------------------------
	vector float aux121={mLHSrow13[3],mLHSrow13[3],mLHSrow13[3],mLHSrow13[3]};
	vector float aux122={mLHSrow23[3],mLHSrow23[3],mLHSrow23[3],mLHSrow23[3]};
	vector float aux123={mLHSrow33[3],mLHSrow33[3],mLHSrow33[3],mLHSrow33[3]};
	vector float aux124={mLHSrow43[3],mLHSrow43[3],mLHSrow43[3],mLHSrow43[3]};

	vector float aux125={mLHSrow53[3],mLHSrow53[3],mLHSrow53[3],mLHSrow53[3]};
	vector float aux126={mLHSrow63[3],mLHSrow63[3],mLHSrow63[3],mLHSrow63[3]};
	vector float aux127={mLHSrow73[3],mLHSrow73[3],mLHSrow73[3],mLHSrow73[3]};
	vector float aux128={mLHSrow83[3],mLHSrow83[3],mLHSrow83[3],mLHSrow83[3]};

	vector float aux129={mLHSrow93[3],mLHSrow93[3],mLHSrow93[3],mLHSrow93[3]};
	vector float aux1210={mLHSrow103[3],mLHSrow103[3],mLHSrow103[3],mLHSrow103[3]};
	vector float aux1211={mLHSrow113[3],mLHSrow113[3],mLHSrow113[3],mLHSrow113[3]};
	vector float aux1212={mLHSrow123[3],mLHSrow123[3],mLHSrow123[3],mLHSrow123[3]};

//-------------------------------------------------------------------------
		//row 1 of result
	vec_xst(vec_madd(aux121, mRHSrow121, vec_madd(aux111, mRHSrow111, vec_madd(aux101, mRHSrow101, vec_madd(aux91, mRHSrow91, vec_madd(aux81, mRHSrow81, vec_madd(aux71, mRHSrow71, vec_madd(aux61, mRHSrow61, vec_madd(aux51, mRHSrow51, vec_madd(aux41, mRHSrow41, vec_madd(aux31, mRHSrow31, vec_madd(aux21, mRHSrow21, vec_mul(aux11, mRHSrow11)))))))))))), 0, mResult);
	vec_xst(vec_madd(aux121, mRHSrow122, vec_madd(aux111, mRHSrow112, vec_madd(aux101, mRHSrow102, vec_madd(aux91, mRHSrow92, vec_madd(aux81, mRHSrow82, vec_madd(aux71, mRHSrow72, vec_madd(aux61, mRHSrow62, vec_madd(aux51, mRHSrow52, vec_madd(aux41, mRHSrow42, vec_madd(aux31, mRHSrow32, vec_madd(aux21, mRHSrow22, vec_mul(aux11, mRHSrow12)))))))))))), 0, mResult + 4);
	vec_xst(vec_madd(aux121, mRHSrow123, vec_madd(aux111, mRHSrow113, vec_madd(aux101, mRHSrow103, vec_madd(aux91, mRHSrow93, vec_madd(aux81, mRHSrow83, vec_madd(aux71, mRHSrow73, vec_madd(aux61, mRHSrow63, vec_madd(aux51, mRHSrow53, vec_madd(aux41, mRHSrow43, vec_madd(aux31, mRHSrow33, vec_madd(aux21, mRHSrow23, vec_mul(aux11, mRHSrow13)))))))))))), 0, mResult + 4*2);

	//row 2 of result
	vec_xst(vec_madd(aux122, mRHSrow121, vec_madd(aux112, mRHSrow111, vec_madd(aux102, mRHSrow101, vec_madd(aux92, mRHSrow91, vec_madd(aux82, mRHSrow81, vec_madd(aux72, mRHSrow71, vec_madd(aux62, mRHSrow61, vec_madd(aux52, mRHSrow51, vec_madd(aux42, mRHSrow41, vec_madd(aux32, mRHSrow31, vec_madd(aux22, mRHSrow21, vec_mul(aux12, mRHSrow11)))))))))))), 0, mResult + 4*3);
	vec_xst(vec_madd(aux122, mRHSrow122, vec_madd(aux112, mRHSrow112, vec_madd(aux102, mRHSrow102, vec_madd(aux92, mRHSrow92, vec_madd(aux82, mRHSrow82, vec_madd(aux72, mRHSrow72, vec_madd(aux62, mRHSrow62, vec_madd(aux52, mRHSrow52, vec_madd(aux42, mRHSrow42, vec_madd(aux32, mRHSrow32, vec_madd(aux22, mRHSrow22, vec_mul(aux12, mRHSrow12)))))))))))), 0, mResult + 4*4);
	vec_xst(vec_madd(aux122, mRHSrow123, vec_madd(aux112, mRHSrow113, vec_madd(aux102, mRHSrow103, vec_madd(aux92, mRHSrow93, vec_madd(aux82, mRHSrow83, vec_madd(aux72, mRHSrow73, vec_madd(aux62, mRHSrow63, vec_madd(aux52, mRHSrow53, vec_madd(aux42, mRHSrow43, vec_madd(aux32, mRHSrow33, vec_madd(aux22, mRHSrow23, vec_mul(aux12, mRHSrow13)))))))))))), 0, mResult + 4*5);

	// row 3 of mResult
	vec_xst(vec_madd(aux123, mRHSrow121, vec_madd(aux113, mRHSrow111, vec_madd(aux103, mRHSrow101, vec_madd(aux93, mRHSrow91, vec_madd(aux83, mRHSrow81, vec_madd(aux73, mRHSrow71, vec_madd(aux63, mRHSrow61, vec_madd(aux53, mRHSrow51, vec_madd(aux43, mRHSrow41, vec_madd(aux33, mRHSrow31, vec_madd(aux23, mRHSrow21, vec_mul(aux13, mRHSrow11)))))))))))), 0, mResult + 4*6);
	vec_xst(vec_madd(aux123, mRHSrow122, vec_madd(aux113, mRHSrow112, vec_madd(aux103, mRHSrow102, vec_madd(aux93, mRHSrow92, vec_madd(aux83, mRHSrow82, vec_madd(aux73, mRHSrow72, vec_madd(aux63, mRHSrow62, vec_madd(aux53, mRHSrow52, vec_madd(aux43, mRHSrow42, vec_madd(aux33, mRHSrow32, vec_madd(aux23, mRHSrow22, vec_mul(aux13, mRHSrow12)))))))))))), 0, mResult + 4*7);
	vec_xst(vec_madd(aux123, mRHSrow123, vec_madd(aux113, mRHSrow113, vec_madd(aux103, mRHSrow103, vec_madd(aux93, mRHSrow93, vec_madd(aux83, mRHSrow83, vec_madd(aux73, mRHSrow73, vec_madd(aux63, mRHSrow63, vec_madd(aux53, mRHSrow53, vec_madd(aux43, mRHSrow43, vec_madd(aux33, mRHSrow33, vec_madd(aux23, mRHSrow23, vec_mul(aux13, mRHSrow13)))))))))))), 0, mResult + 4*8);
	
	// row 4 of mResult
	vec_xst(vec_madd(aux124, mRHSrow121, vec_madd(aux114, mRHSrow111, vec_madd(aux104, mRHSrow101, vec_madd(aux94, mRHSrow91, vec_madd(aux84, mRHSrow81, vec_madd(aux74, mRHSrow71, vec_madd(aux64, mRHSrow61, vec_madd(aux54, mRHSrow51, vec_madd(aux44, mRHSrow41, vec_madd(aux34, mRHSrow31, vec_madd(aux24, mRHSrow21, vec_mul(aux14, mRHSrow11)))))))))))), 0, mResult + 4*9);
	vec_xst(vec_madd(aux124, mRHSrow122, vec_madd(aux114, mRHSrow112, vec_madd(aux104, mRHSrow102, vec_madd(aux94, mRHSrow92, vec_madd(aux84, mRHSrow82, vec_madd(aux74, mRHSrow72, vec_madd(aux64, mRHSrow62, vec_madd(aux54, mRHSrow52, vec_madd(aux44, mRHSrow42, vec_madd(aux34, mRHSrow32, vec_madd(aux24, mRHSrow22, vec_mul(aux14, mRHSrow12)))))))))))), 0, mResult + 4*10);
	vec_xst(vec_madd(aux124, mRHSrow123, vec_madd(aux114, mRHSrow113, vec_madd(aux104, mRHSrow103, vec_madd(aux94, mRHSrow93, vec_madd(aux84, mRHSrow83, vec_madd(aux74, mRHSrow73, vec_madd(aux64, mRHSrow63, vec_madd(aux54, mRHSrow53, vec_madd(aux44, mRHSrow43, vec_madd(aux34, mRHSrow33, vec_madd(aux24, mRHSrow23, vec_mul(aux14, mRHSrow13)))))))))))), 0, mResult + 4*11);
	
	// row 5 of mResult
	vec_xst(vec_madd(aux125, mRHSrow121, vec_madd(aux115, mRHSrow111, vec_madd(aux105, mRHSrow101, vec_madd(aux95, mRHSrow91, vec_madd(aux85, mRHSrow81, vec_madd(aux75, mRHSrow71, vec_madd(aux65, mRHSrow61, vec_madd(aux55, mRHSrow51, vec_madd(aux45, mRHSrow41, vec_madd(aux35, mRHSrow31, vec_madd(aux25, mRHSrow21, vec_mul(aux15, mRHSrow11)))))))))))), 0, mResult + 4*12);
	vec_xst(vec_madd(aux125, mRHSrow122, vec_madd(aux115, mRHSrow112, vec_madd(aux105, mRHSrow102, vec_madd(aux95, mRHSrow92, vec_madd(aux85, mRHSrow82, vec_madd(aux75, mRHSrow72, vec_madd(aux65, mRHSrow62, vec_madd(aux55, mRHSrow52, vec_madd(aux45, mRHSrow42, vec_madd(aux35, mRHSrow32, vec_madd(aux25, mRHSrow22, vec_mul(aux15, mRHSrow12)))))))))))), 0, mResult + 4*13);
	vec_xst(vec_madd(aux125, mRHSrow123, vec_madd(aux115, mRHSrow113, vec_madd(aux105, mRHSrow103, vec_madd(aux95, mRHSrow93, vec_madd(aux85, mRHSrow83, vec_madd(aux75, mRHSrow73, vec_madd(aux65, mRHSrow63, vec_madd(aux55, mRHSrow53, vec_madd(aux45, mRHSrow43, vec_madd(aux35, mRHSrow33, vec_madd(aux25, mRHSrow23, vec_mul(aux15, mRHSrow13)))))))))))), 0, mResult + 4*14);
	
	// row 6 of mResult
	vec_xst(vec_madd(aux126, mRHSrow121, vec_madd(aux116, mRHSrow111, vec_madd(aux106, mRHSrow101, vec_madd(aux96, mRHSrow91, vec_madd(aux86, mRHSrow81, vec_madd(aux76, mRHSrow71, vec_madd(aux66, mRHSrow61, vec_madd(aux56, mRHSrow51, vec_madd(aux46, mRHSrow41, vec_madd(aux36, mRHSrow31, vec_madd(aux26, mRHSrow21, vec_mul(aux16, mRHSrow11)))))))))))), 0, mResult + 4*15);
	vec_xst(vec_madd(aux126, mRHSrow122, vec_madd(aux116, mRHSrow112, vec_madd(aux106, mRHSrow102, vec_madd(aux96, mRHSrow92, vec_madd(aux86, mRHSrow82, vec_madd(aux76, mRHSrow72, vec_madd(aux66, mRHSrow62, vec_madd(aux56, mRHSrow52, vec_madd(aux46, mRHSrow42, vec_madd(aux36, mRHSrow32, vec_madd(aux26, mRHSrow22, vec_mul(aux16, mRHSrow12)))))))))))), 0, mResult + 4*16);
	vec_xst(vec_madd(aux126, mRHSrow123, vec_madd(aux116, mRHSrow113, vec_madd(aux106, mRHSrow103, vec_madd(aux96, mRHSrow93, vec_madd(aux86, mRHSrow83, vec_madd(aux76, mRHSrow73, vec_madd(aux66, mRHSrow63, vec_madd(aux56, mRHSrow53, vec_madd(aux46, mRHSrow43, vec_madd(aux36, mRHSrow33, vec_madd(aux26, mRHSrow23, vec_mul(aux16, mRHSrow13)))))))))))), 0, mResult + 4*17);
	
	// row 7 of mResult
	vec_xst(vec_madd(aux127, mRHSrow121, vec_madd(aux117, mRHSrow111, vec_madd(aux107, mRHSrow101, vec_madd(aux97, mRHSrow91, vec_madd(aux87, mRHSrow81, vec_madd(aux77, mRHSrow71, vec_madd(aux67, mRHSrow61, vec_madd(aux57, mRHSrow51, vec_madd(aux47, mRHSrow41, vec_madd(aux37, mRHSrow31, vec_madd(aux27, mRHSrow21, vec_mul(aux17, mRHSrow11)))))))))))), 0, mResult + 4*18);
	vec_xst(vec_madd(aux127, mRHSrow122, vec_madd(aux117, mRHSrow112, vec_madd(aux107, mRHSrow102, vec_madd(aux97, mRHSrow92, vec_madd(aux87, mRHSrow82, vec_madd(aux77, mRHSrow72, vec_madd(aux67, mRHSrow62, vec_madd(aux57, mRHSrow52, vec_madd(aux47, mRHSrow42, vec_madd(aux37, mRHSrow32, vec_madd(aux27, mRHSrow22, vec_mul(aux17, mRHSrow12)))))))))))), 0, mResult + 4*19);
	vec_xst(vec_madd(aux127, mRHSrow123, vec_madd(aux117, mRHSrow113, vec_madd(aux107, mRHSrow103, vec_madd(aux97, mRHSrow93, vec_madd(aux87, mRHSrow83, vec_madd(aux77, mRHSrow73, vec_madd(aux67, mRHSrow63, vec_madd(aux57, mRHSrow53, vec_madd(aux47, mRHSrow43, vec_madd(aux37, mRHSrow33, vec_madd(aux27, mRHSrow23, vec_mul(aux17, mRHSrow13)))))))))))), 0, mResult + 4*20);
	
	// row 8 of mResult
	vec_xst(vec_madd(aux128, mRHSrow121, vec_madd(aux118, mRHSrow111, vec_madd(aux108, mRHSrow101, vec_madd(aux98, mRHSrow91, vec_madd(aux88, mRHSrow81, vec_madd(aux78, mRHSrow71, vec_madd(aux68, mRHSrow61, vec_madd(aux58, mRHSrow51, vec_madd(aux48, mRHSrow41, vec_madd(aux38, mRHSrow31, vec_madd(aux28, mRHSrow21, vec_mul(aux18, mRHSrow11)))))))))))), 0, mResult + 4*21);
	vec_xst(vec_madd(aux128, mRHSrow122, vec_madd(aux118, mRHSrow112, vec_madd(aux108, mRHSrow102, vec_madd(aux98, mRHSrow92, vec_madd(aux88, mRHSrow82, vec_madd(aux78, mRHSrow72, vec_madd(aux68, mRHSrow62, vec_madd(aux58, mRHSrow52, vec_madd(aux48, mRHSrow42, vec_madd(aux38, mRHSrow32, vec_madd(aux28, mRHSrow22, vec_mul(aux18, mRHSrow12)))))))))))), 0, mResult + 4*22);
	vec_xst(vec_madd(aux128, mRHSrow123, vec_madd(aux118, mRHSrow113, vec_madd(aux108, mRHSrow103, vec_madd(aux98, mRHSrow93, vec_madd(aux88, mRHSrow83, vec_madd(aux78, mRHSrow73, vec_madd(aux68, mRHSrow63, vec_madd(aux58, mRHSrow53, vec_madd(aux48, mRHSrow43, vec_madd(aux38, mRHSrow33, vec_madd(aux28, mRHSrow23, vec_mul(aux18, mRHSrow13)))))))))))), 0, mResult + 4*23);
	
	// row 9 of mResult
	vec_xst(vec_madd(aux129, mRHSrow121, vec_madd(aux119, mRHSrow111, vec_madd(aux109, mRHSrow101, vec_madd(aux99, mRHSrow91, vec_madd(aux89, mRHSrow81, vec_madd(aux79, mRHSrow71, vec_madd(aux69, mRHSrow61, vec_madd(aux59, mRHSrow51, vec_madd(aux49, mRHSrow41, vec_madd(aux39, mRHSrow31, vec_madd(aux29, mRHSrow21, vec_mul(aux19, mRHSrow11)))))))))))), 0, mResult + 4*24);
	vec_xst(vec_madd(aux129, mRHSrow122, vec_madd(aux119, mRHSrow112, vec_madd(aux109, mRHSrow102, vec_madd(aux99, mRHSrow92, vec_madd(aux89, mRHSrow82, vec_madd(aux79, mRHSrow72, vec_madd(aux69, mRHSrow62, vec_madd(aux59, mRHSrow52, vec_madd(aux49, mRHSrow42, vec_madd(aux39, mRHSrow32, vec_madd(aux29, mRHSrow22, vec_mul(aux19, mRHSrow12)))))))))))), 0, mResult + 4*25);
	vec_xst(vec_madd(aux129, mRHSrow123, vec_madd(aux119, mRHSrow113, vec_madd(aux109, mRHSrow103, vec_madd(aux99, mRHSrow93, vec_madd(aux89, mRHSrow83, vec_madd(aux79, mRHSrow73, vec_madd(aux69, mRHSrow63, vec_madd(aux59, mRHSrow53, vec_madd(aux49, mRHSrow43, vec_madd(aux39, mRHSrow33, vec_madd(aux29, mRHSrow23, vec_mul(aux19, mRHSrow13)))))))))))), 0, mResult + 4*26);
	
	// row 10 of mResult
	vec_xst(vec_madd(aux1210, mRHSrow121, vec_madd(aux1110, mRHSrow111, vec_madd(aux1010, mRHSrow101, vec_madd(aux910, mRHSrow91, vec_madd(aux810, mRHSrow81, vec_madd(aux710, mRHSrow71, vec_madd(aux610, mRHSrow61, vec_madd(aux510, mRHSrow51, vec_madd(aux410, mRHSrow41, vec_madd(aux310, mRHSrow31, vec_madd(aux210, mRHSrow21, vec_mul(aux110, mRHSrow11)))))))))))), 0, mResult + 4*27);
	vec_xst(vec_madd(aux1210, mRHSrow122, vec_madd(aux1110, mRHSrow112, vec_madd(aux1010, mRHSrow102, vec_madd(aux910, mRHSrow92, vec_madd(aux810, mRHSrow82, vec_madd(aux710, mRHSrow72, vec_madd(aux610, mRHSrow62, vec_madd(aux510, mRHSrow52, vec_madd(aux410, mRHSrow42, vec_madd(aux310, mRHSrow32, vec_madd(aux210, mRHSrow22, vec_mul(aux110, mRHSrow12)))))))))))), 0, mResult + 4*28);
	vec_xst(vec_madd(aux1210, mRHSrow123, vec_madd(aux1110, mRHSrow113, vec_madd(aux1010, mRHSrow103, vec_madd(aux910, mRHSrow93, vec_madd(aux810, mRHSrow83, vec_madd(aux710, mRHSrow73, vec_madd(aux610, mRHSrow63, vec_madd(aux510, mRHSrow53, vec_madd(aux410, mRHSrow43, vec_madd(aux310, mRHSrow33, vec_madd(aux210, mRHSrow23, vec_mul(aux110, mRHSrow13)))))))))))), 0, mResult + 4*29);
	

	// row 11 of mResult
	vec_xst(vec_madd(aux1211, mRHSrow121, vec_madd(aux1111, mRHSrow111, vec_madd(aux1011, mRHSrow101, vec_madd(aux911, mRHSrow91, vec_madd(aux811, mRHSrow81, vec_madd(aux711, mRHSrow71, vec_madd(aux611, mRHSrow61, vec_madd(aux511, mRHSrow51, vec_madd(aux411, mRHSrow41, vec_madd(aux311, mRHSrow31, vec_madd(aux211, mRHSrow21, vec_mul(aux0111, mRHSrow11)))))))))))), 0, mResult + 4*30);
	vec_xst(vec_madd(aux1211, mRHSrow122, vec_madd(aux1111, mRHSrow112, vec_madd(aux1011, mRHSrow102, vec_madd(aux911, mRHSrow92, vec_madd(aux811, mRHSrow82, vec_madd(aux711, mRHSrow72, vec_madd(aux611, mRHSrow62, vec_madd(aux511, mRHSrow52, vec_madd(aux411, mRHSrow42, vec_madd(aux311, mRHSrow32, vec_madd(aux211, mRHSrow22, vec_mul(aux0111, mRHSrow12)))))))))))), 0, mResult + 4*31);
	vec_xst(vec_madd(aux1211, mRHSrow123, vec_madd(aux1111, mRHSrow113, vec_madd(aux1011, mRHSrow103, vec_madd(aux911, mRHSrow93, vec_madd(aux811, mRHSrow83, vec_madd(aux711, mRHSrow73, vec_madd(aux611, mRHSrow63, vec_madd(aux511, mRHSrow53, vec_madd(aux411, mRHSrow43, vec_madd(aux311, mRHSrow33, vec_madd(aux211, mRHSrow23, vec_mul(aux0111, mRHSrow13)))))))))))), 0, mResult + 4*32);
	
	// row 12 of mResult
	vec_xst(vec_madd(aux1212, mRHSrow121, vec_madd(aux1112, mRHSrow111, vec_madd(aux1012, mRHSrow101, vec_madd(aux912, mRHSrow91, vec_madd(aux812, mRHSrow81, vec_madd(aux712, mRHSrow71, vec_madd(aux612, mRHSrow61, vec_madd(aux512, mRHSrow51, vec_madd(aux412, mRHSrow41, vec_madd(aux312, mRHSrow31, vec_madd(aux212, mRHSrow21, vec_mul(aux0112, mRHSrow11)))))))))))), 0, mResult + 4*33);
	vec_xst(vec_madd(aux1212, mRHSrow122, vec_madd(aux1112, mRHSrow112, vec_madd(aux1012, mRHSrow102, vec_madd(aux912, mRHSrow92, vec_madd(aux812, mRHSrow82, vec_madd(aux712, mRHSrow72, vec_madd(aux612, mRHSrow62, vec_madd(aux512, mRHSrow52, vec_madd(aux412, mRHSrow42, vec_madd(aux312, mRHSrow32, vec_madd(aux212, mRHSrow22, vec_mul(aux0112, mRHSrow12)))))))))))), 0, mResult + 4*34);
	vec_xst(vec_madd(aux1212, mRHSrow123, vec_madd(aux1112, mRHSrow113, vec_madd(aux1012, mRHSrow103, vec_madd(aux912, mRHSrow93, vec_madd(aux812, mRHSrow83, vec_madd(aux712, mRHSrow73, vec_madd(aux612, mRHSrow63, vec_madd(aux512, mRHSrow53, vec_madd(aux412, mRHSrow43, vec_madd(aux312, mRHSrow33, vec_madd(aux212, mRHSrow23, vec_mul(aux0112, mRHSrow13)))))))))))), 0, mResult + 4*35);
	

}
//=========================================================================================================================
//=========================================================================================================================
//col x row
inline void mul12x12ColMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHScol11, mLHScol12, mLHScol13, mLHScol21, mLHScol22, mLHScol23, mLHScol31, mLHScol32, mLHScol33,
	      	     mLHScol41, mLHScol42, mLHScol43, mLHScol51, mLHScol52, mLHScol53, mLHScol61, mLHScol62, mLHScol63,
		     mLHScol71, mLHScol72, mLHScol73, mLHScol81, mLHScol82, mLHScol83, mLHScol91, mLHScol92, mLHScol93, mLHScol101, mLHScol102, mLHScol103, mLHScol111,
		     mLHScol112, mLHScol113, mLHScol121, mLHScol122, mLHScol123;

	vector float mRHSrow11, mRHSrow12, mRHSrow13, mRHSrow21, mRHSrow22, mRHSrow23, mRHSrow31, mRHSrow32, mRHSrow33,
	      	     mRHSrow41, mRHSrow42, mRHSrow43, mRHSrow51, mRHSrow52, mRHSrow53, mRHSrow61, mRHSrow62, mRHSrow63,
		     mRHSrow71, mRHSrow72, mRHSrow73, mRHSrow81, mRHSrow82, mRHSrow83, mRHSrow91, mRHSrow92, mRHSrow93, mRHSrow101, mRHSrow102, mRHSrow103, mRHSrow111,
		     mRHSrow112, mRHSrow113,  mRHSrow121, mRHSrow122, mRHSrow123;
//load
//1 row/column --> 3 vectors.
	
	mLHScol11 = vec_xl(0,mLHS);
	mLHScol12 = vec_xl(0,mLHS+4);
	mLHScol13 = vec_xl(0,mLHS+4*2);

	mLHScol21 = vec_xl(0,mLHS+4*3);
	mLHScol22 = vec_xl(0,mLHS+4*4);
	mLHScol23 = vec_xl(0,mLHS+4*5);

	mLHScol31 = vec_xl(0,mLHS+4*6);
	mLHScol32 = vec_xl(0,mLHS+4*7);
	mLHScol33 = vec_xl(0,mLHS+4*8);

	mLHScol41 = vec_xl(0,mLHS+4*9);
	mLHScol42 = vec_xl(0,mLHS+4*10);
	mLHScol43 = vec_xl(0,mLHS+4*11);

	mLHScol51 = vec_xl(0,mLHS+4*12);
	mLHScol52 = vec_xl(0,mLHS+4*13);
	mLHScol53 = vec_xl(0,mLHS+4*14);

	mLHScol61 = vec_xl(0,mLHS+4*15);
	mLHScol62 = vec_xl(0,mLHS+4*16);
	mLHScol63 = vec_xl(0,mLHS+4*17);

	mLHScol71 = vec_xl(0,mLHS+4*18);
	mLHScol72 = vec_xl(0,mLHS+4*19);
	mLHScol73 = vec_xl(0,mLHS+4*20);

	mLHScol81 = vec_xl(0,mLHS+4*21);
	mLHScol82 = vec_xl(0,mLHS+4*22);
	mLHScol83 = vec_xl(0,mLHS+4*23);

	mLHScol91 = vec_xl(0,mLHS+4*24);
	mLHScol92 = vec_xl(0,mLHS+4*25);
	mLHScol93 = vec_xl(0,mLHS+4*26);

	mLHScol101 = vec_xl(0,mLHS+4*27);
	mLHScol102 = vec_xl(0,mLHS+4*28);
	mLHScol103 = vec_xl(0,mLHS+4*29);

	mLHScol111 = vec_xl(0,mLHS+4*30);
	mLHScol112 = vec_xl(0,mLHS+4*31);
	mLHScol113 = vec_xl(0,mLHS+4*32);

	mLHScol121 = vec_xl(0,mLHS+4*33);
	mLHScol122 = vec_xl(0,mLHS+4*34);
	mLHScol123 = vec_xl(0,mLHS+4*35);
//=====================================================================

	mRHSrow11 = vec_xl(0,mRHS);
	mRHSrow12 = vec_xl(0,mRHS+4);
	mRHSrow13 = vec_xl(0,mRHS+4*2);

	mRHSrow21 = vec_xl(0,mRHS+4*3);
	mRHSrow22 = vec_xl(0,mRHS+4*4);
	mRHSrow23 = vec_xl(0,mRHS+4*5);

	mRHSrow31 = vec_xl(0,mRHS+4*6);
	mRHSrow32 = vec_xl(0,mRHS+4*7);
	mRHSrow33 = vec_xl(0,mRHS+4*8);

	mRHSrow41 = vec_xl(0,mRHS+4*9);
	mRHSrow42 = vec_xl(0,mRHS+4*10);
	mRHSrow43 = vec_xl(0,mRHS+4*11);

	mRHSrow51 = vec_xl(0,mRHS+4*12);
	mRHSrow52 = vec_xl(0,mRHS+4*13);
	mRHSrow53 = vec_xl(0,mRHS+4*14);

	mRHSrow61 = vec_xl(0,mRHS+4*15);
	mRHSrow62 = vec_xl(0,mRHS+4*16);
	mRHSrow63 = vec_xl(0,mRHS+4*17);

	mRHSrow71 = vec_xl(0,mRHS+4*18);
	mRHSrow72 = vec_xl(0,mRHS+4*19);
	mRHSrow73 = vec_xl(0,mRHS+4*20);

	mRHSrow81 = vec_xl(0,mRHS+4*21);
	mRHSrow82 = vec_xl(0,mRHS+4*22);
	mRHSrow83 = vec_xl(0,mRHS+4*23);

	mRHSrow91 = vec_xl(0,mRHS+4*24);
	mRHSrow92 = vec_xl(0,mRHS+4*25);
	mRHSrow93 = vec_xl(0,mRHS+4*26);

	mRHSrow101 = vec_xl(0,mRHS+4*27);
	mRHSrow102 = vec_xl(0,mRHS+4*28);
	mRHSrow103 = vec_xl(0,mRHS+4*29);

	mRHSrow111 = vec_xl(0,mRHS+4*30);
	mRHSrow112 = vec_xl(0,mRHS+4*31);
	mRHSrow113 = vec_xl(0,mRHS+4*32);

	mRHSrow121 = vec_xl(0,mRHS+4*33);
	mRHSrow122 = vec_xl(0,mRHS+4*34);
	mRHSrow123 = vec_xl(0,mRHS+4*35);
//=====================================================================




//===================================================================================
//Splat
//===================================================================================

	vector float aux11={mLHScol11[0],mLHScol11[0],mLHScol11[0],mLHScol11[0]};
	vector float aux12={mLHScol11[1],mLHScol11[1],mLHScol11[1],mLHScol11[1]};
	vector float aux13={mLHScol11[2],mLHScol11[2],mLHScol11[2],mLHScol11[2]};
	vector float aux14={mLHScol11[3],mLHScol11[3],mLHScol11[3],mLHScol11[3]};

	vector float aux15={mLHScol12[0],mLHScol12[0],mLHScol12[0],mLHScol12[0]};
	vector float aux16={mLHScol12[1],mLHScol12[1],mLHScol12[1],mLHScol12[1]};
	vector float aux17={mLHScol12[2],mLHScol12[2],mLHScol12[2],mLHScol12[2]};
	vector float aux18={mLHScol12[3],mLHScol12[3],mLHScol12[3],mLHScol12[3]};

	vector float aux19={mLHScol13[0],mLHScol13[0],mLHScol13[0],mLHScol13[0]};
	vector float aux110={mLHScol13[1],mLHScol13[1],mLHScol13[1],mLHScol13[1]};
	vector float aux0111={mLHScol13[2],mLHScol13[2],mLHScol13[2],mLHScol13[2]};
	vector float aux0112={mLHScol13[3],mLHScol13[3],mLHScol13[3],mLHScol13[3]};

//===================================================================================

	vector float aux21={mLHScol21[0],mLHScol21[0],mLHScol21[0],mLHScol21[0]};
	vector float aux22={mLHScol21[1],mLHScol21[1],mLHScol21[1],mLHScol21[1]};
	vector float aux23={mLHScol21[2],mLHScol21[2],mLHScol21[2],mLHScol21[2]};
	vector float aux24={mLHScol21[3],mLHScol21[3],mLHScol21[3],mLHScol21[3]};

	vector float aux25={mLHScol22[0],mLHScol22[0],mLHScol22[0],mLHScol22[0]};
	vector float aux26={mLHScol22[1],mLHScol22[1],mLHScol22[1],mLHScol22[1]};
	vector float aux27={mLHScol22[2],mLHScol22[2],mLHScol22[2],mLHScol22[2]};
	vector float aux28={mLHScol22[3],mLHScol22[3],mLHScol22[3],mLHScol22[3]};

	vector float aux29={mLHScol23[0],mLHScol23[0],mLHScol23[0],mLHScol23[0]};
	vector float aux210={mLHScol23[1],mLHScol23[1],mLHScol23[1],mLHScol23[1]};
	vector float aux211={mLHScol23[2],mLHScol23[2],mLHScol23[2],mLHScol23[2]};
	vector float aux212={mLHScol23[3],mLHScol23[3],mLHScol23[3],mLHScol23[3]};

//===================================================================================

	vector float aux31={mLHScol31[0],mLHScol31[0],mLHScol31[0],mLHScol31[0]};
	vector float aux32={mLHScol31[1],mLHScol31[1],mLHScol31[1],mLHScol31[1]};
	vector float aux33={mLHScol31[2],mLHScol31[2],mLHScol31[2],mLHScol31[2]};
	vector float aux34={mLHScol31[3],mLHScol31[3],mLHScol31[3],mLHScol31[3]};

	vector float aux35={mLHScol32[0],mLHScol32[0],mLHScol32[0],mLHScol32[0]};
	vector float aux36={mLHScol32[1],mLHScol32[1],mLHScol32[1],mLHScol32[1]};
	vector float aux37={mLHScol32[2],mLHScol32[2],mLHScol32[2],mLHScol32[2]};
	vector float aux38={mLHScol32[3],mLHScol32[3],mLHScol32[3],mLHScol32[3]};

	vector float aux39={mLHScol33[0],mLHScol33[0],mLHScol33[0],mLHScol33[0]};
	vector float aux310={mLHScol33[1],mLHScol33[1],mLHScol33[1],mLHScol33[1]};
	vector float aux311={mLHScol33[2],mLHScol33[2],mLHScol33[2],mLHScol33[2]};
	vector float aux312={mLHScol33[3],mLHScol33[3],mLHScol33[3],mLHScol33[3]};


//===================================================================================

	vector float aux41={mLHScol41[0],mLHScol41[0],mLHScol41[0],mLHScol41[0]};
	vector float aux42={mLHScol41[1],mLHScol41[1],mLHScol41[1],mLHScol41[1]};
	vector float aux43={mLHScol41[2],mLHScol41[2],mLHScol41[2],mLHScol41[2]};
	vector float aux44={mLHScol41[3],mLHScol41[3],mLHScol41[3],mLHScol41[3]};

	vector float aux45={mLHScol42[0],mLHScol22[0],mLHScol22[0],mLHScol22[0]};
	vector float aux46={mLHScol42[1],mLHScol22[1],mLHScol22[1],mLHScol22[1]};
	vector float aux47={mLHScol42[2],mLHScol22[2],mLHScol22[2],mLHScol22[2]};
	vector float aux48={mLHScol42[3],mLHScol22[3],mLHScol22[3],mLHScol22[3]};

	vector float aux49={mLHScol43[0],mLHScol43[0],mLHScol43[0],mLHScol43[0]};
	vector float aux410={mLHScol43[1],mLHScol43[1],mLHScol43[1],mLHScol43[1]};
	vector float aux411={mLHScol43[2],mLHScol43[2],mLHScol43[2],mLHScol43[2]};
	vector float aux412={mLHScol43[3],mLHScol43[3],mLHScol43[3],mLHScol43[3]};


//===================================================================================

	
	vector float aux51={mLHScol51[0],mLHScol51[0],mLHScol51[0],mLHScol51[0]};
	vector float aux52={mLHScol51[1],mLHScol51[1],mLHScol51[1],mLHScol51[1]};
	vector float aux53={mLHScol51[2],mLHScol51[2],mLHScol51[2],mLHScol51[2]};
	vector float aux54={mLHScol51[3],mLHScol51[3],mLHScol51[3],mLHScol51[3]};

	vector float aux55={mLHScol52[0],mLHScol52[0],mLHScol52[0],mLHScol52[0]};
	vector float aux56={mLHScol52[1],mLHScol52[1],mLHScol52[1],mLHScol52[1]};
	vector float aux57={mLHScol52[2],mLHScol52[2],mLHScol52[2],mLHScol52[2]};
	vector float aux58={mLHScol52[3],mLHScol52[3],mLHScol52[3],mLHScol52[3]};

	vector float aux59={mLHScol53[0],mLHScol53[0],mLHScol53[0],mLHScol53[0]};
	vector float aux510={mLHScol53[1],mLHScol53[1],mLHScol53[1],mLHScol53[1]};
	vector float aux511={mLHScol53[2],mLHScol53[2],mLHScol53[2],mLHScol53[2]};
	vector float aux512={mLHScol53[3],mLHScol53[3],mLHScol53[3],mLHScol53[3]};

//===================================================================================

	vector float aux61={mLHScol61[0],mLHScol61[0],mLHScol61[0],mLHScol61[0]};
	vector float aux62={mLHScol61[1],mLHScol61[1],mLHScol61[1],mLHScol61[1]};
	vector float aux63={mLHScol61[2],mLHScol61[2],mLHScol61[2],mLHScol61[2]};
	vector float aux64={mLHScol61[3],mLHScol61[3],mLHScol61[3],mLHScol61[3]};

	vector float aux65={mLHScol62[0],mLHScol62[0],mLHScol62[0],mLHScol62[0]};
	vector float aux66={mLHScol62[1],mLHScol62[1],mLHScol62[1],mLHScol62[1]};
	vector float aux67={mLHScol62[2],mLHScol62[2],mLHScol62[2],mLHScol62[2]};
	vector float aux68={mLHScol62[3],mLHScol62[3],mLHScol62[3],mLHScol62[3]};

	vector float aux69={mLHScol63[0],mLHScol63[0],mLHScol63[0],mLHScol63[0]};
	vector float aux610={mLHScol63[1],mLHScol63[1],mLHScol63[1],mLHScol63[1]};
	vector float aux611={mLHScol63[2],mLHScol63[2],mLHScol63[2],mLHScol63[2]};
	vector float aux612={mLHScol63[3],mLHScol63[3],mLHScol63[3],mLHScol63[3]};

//===================================================================================

	vector float aux71={mLHScol71[0],mLHScol71[0],mLHScol71[0],mLHScol71[0]};
	vector float aux72={mLHScol71[1],mLHScol71[1],mLHScol71[1],mLHScol71[1]};
	vector float aux73={mLHScol71[2],mLHScol71[2],mLHScol71[2],mLHScol71[2]};
	vector float aux74={mLHScol71[3],mLHScol71[3],mLHScol71[3],mLHScol71[3]};

	vector float aux75={mLHScol72[0],mLHScol72[0],mLHScol72[0],mLHScol72[0]};
	vector float aux76={mLHScol72[1],mLHScol72[1],mLHScol72[1],mLHScol72[1]};
	vector float aux77={mLHScol72[2],mLHScol72[2],mLHScol72[2],mLHScol72[2]};
	vector float aux78={mLHScol72[3],mLHScol72[3],mLHScol72[3],mLHScol72[3]};

	vector float aux79={mLHScol73[0],mLHScol73[0],mLHScol73[0],mLHScol73[0]};
	vector float aux710={mLHScol73[1],mLHScol73[1],mLHScol73[1],mLHScol73[1]};
	vector float aux711={mLHScol73[2],mLHScol73[2],mLHScol73[2],mLHScol73[2]};
	vector float aux712={mLHScol73[3],mLHScol73[3],mLHScol73[3],mLHScol73[3]};

//===================================================================================

	vector float aux81={mLHScol81[0],mLHScol81[0],mLHScol81[0],mLHScol81[0]};
	vector float aux82={mLHScol81[1],mLHScol81[1],mLHScol81[1],mLHScol81[1]};
	vector float aux83={mLHScol81[2],mLHScol81[2],mLHScol81[2],mLHScol81[2]};
	vector float aux84={mLHScol81[3],mLHScol81[3],mLHScol81[3],mLHScol81[3]};

	vector float aux85={mLHScol82[0],mLHScol82[0],mLHScol82[0],mLHScol82[0]};
	vector float aux86={mLHScol82[1],mLHScol82[1],mLHScol82[1],mLHScol82[1]};
	vector float aux87={mLHScol82[2],mLHScol82[2],mLHScol82[2],mLHScol82[2]};
	vector float aux88={mLHScol82[3],mLHScol82[3],mLHScol82[3],mLHScol82[3]};

	vector float aux89={mLHScol83[0],mLHScol83[0],mLHScol83[0],mLHScol83[0]};
	vector float aux810={mLHScol83[1],mLHScol83[1],mLHScol83[1],mLHScol83[1]};
	vector float aux811={mLHScol83[2],mLHScol83[2],mLHScol83[2],mLHScol83[2]};
	vector float aux812={mLHScol83[3],mLHScol83[3],mLHScol83[3],mLHScol83[3]};

//===================================================================================

	vector float aux91={mLHScol91[0],mLHScol91[0],mLHScol91[0],mLHScol91[0]};
	vector float aux92={mLHScol91[1],mLHScol91[1],mLHScol91[1],mLHScol91[1]};
	vector float aux93={mLHScol91[2],mLHScol91[2],mLHScol91[2],mLHScol91[2]};
	vector float aux94={mLHScol91[3],mLHScol91[3],mLHScol91[3],mLHScol91[3]};

	vector float aux95={mLHScol92[0],mLHScol92[0],mLHScol92[0],mLHScol92[0]};
	vector float aux96={mLHScol92[1],mLHScol92[1],mLHScol92[1],mLHScol92[1]};
	vector float aux97={mLHScol92[2],mLHScol92[2],mLHScol92[2],mLHScol92[2]};
	vector float aux98={mLHScol92[3],mLHScol92[3],mLHScol92[3],mLHScol92[3]};

	vector float aux99={mLHScol93[0],mLHScol93[0],mLHScol93[0],mLHScol93[0]};
	vector float aux910={mLHScol93[1],mLHScol93[1],mLHScol93[1],mLHScol93[1]};
	vector float aux911={mLHScol93[2],mLHScol93[2],mLHScol93[2],mLHScol93[2]};
	vector float aux912={mLHScol93[3],mLHScol93[3],mLHScol93[3],mLHScol93[3]};

//===================================================================================

	vector float aux101={mLHScol101[0],mLHScol101[0],mLHScol101[0],mLHScol101[0]};
	vector float aux102={mLHScol101[1],mLHScol101[1],mLHScol101[1],mLHScol101[1]};
	vector float aux103={mLHScol101[2],mLHScol101[2],mLHScol101[2],mLHScol101[2]};
	vector float aux104={mLHScol101[3],mLHScol101[3],mLHScol101[3],mLHScol101[3]};

	vector float aux105={mLHScol102[0],mLHScol102[0],mLHScol102[0],mLHScol102[0]};
	vector float aux106={mLHScol102[1],mLHScol102[1],mLHScol102[1],mLHScol102[1]};
	vector float aux107={mLHScol102[2],mLHScol102[2],mLHScol102[2],mLHScol102[2]};
	vector float aux108={mLHScol102[3],mLHScol102[3],mLHScol102[3],mLHScol102[3]};

	vector float aux109={mLHScol103[0],mLHScol103[0],mLHScol103[0],mLHScol103[0]};
	vector float aux1010={mLHScol103[1],mLHScol103[1],mLHScol103[1],mLHScol103[1]};
	vector float aux1011={mLHScol103[2],mLHScol103[2],mLHScol103[2],mLHScol103[2]};
	vector float aux1012={mLHScol103[3],mLHScol103[3],mLHScol103[3],mLHScol103[3]};

//===================================================================================

	vector float aux111={mLHScol111[0],mLHScol111[0],mLHScol111[0],mLHScol111[0]};
	vector float aux112={mLHScol111[1],mLHScol111[1],mLHScol111[1],mLHScol111[1]};
	vector float aux113={mLHScol111[2],mLHScol111[2],mLHScol111[2],mLHScol111[2]};
	vector float aux114={mLHScol111[3],mLHScol111[3],mLHScol111[3],mLHScol111[3]};

	vector float aux115={mLHScol112[0],mLHScol112[0],mLHScol112[0],mLHScol112[0]};
	vector float aux116={mLHScol112[1],mLHScol112[1],mLHScol112[1],mLHScol112[1]};
	vector float aux117={mLHScol112[2],mLHScol112[2],mLHScol112[2],mLHScol112[2]};
	vector float aux118={mLHScol112[3],mLHScol112[3],mLHScol112[3],mLHScol112[3]};

	vector float aux119={mLHScol113[0],mLHScol113[0],mLHScol113[0],mLHScol113[0]};
	vector float aux1110={mLHScol113[1],mLHScol113[1],mLHScol113[1],mLHScol113[1]};
	vector float aux1111={mLHScol113[2],mLHScol113[2],mLHScol113[2],mLHScol113[2]};
	vector float aux1112={mLHScol113[3],mLHScol113[3],mLHScol113[3],mLHScol113[3]};

//===================================================================================

	vector float aux121={mLHScol121[0],mLHScol121[0],mLHScol121[0],mLHScol121[0]};
	vector float aux122={mLHScol121[1],mLHScol121[1],mLHScol121[1],mLHScol121[1]};
	vector float aux123={mLHScol121[2],mLHScol121[2],mLHScol121[2],mLHScol121[2]};
	vector float aux124={mLHScol121[3],mLHScol121[3],mLHScol121[3],mLHScol121[3]};

	vector float aux125={mLHScol122[0],mLHScol122[0],mLHScol122[0],mLHScol122[0]};
	vector float aux126={mLHScol122[1],mLHScol122[1],mLHScol122[1],mLHScol122[1]};
	vector float aux127={mLHScol122[2],mLHScol122[2],mLHScol122[2],mLHScol122[2]};
	vector float aux128={mLHScol122[3],mLHScol122[3],mLHScol122[3],mLHScol122[3]};

	vector float aux129={mLHScol123[0],mLHScol123[0],mLHScol123[0],mLHScol123[0]};
	vector float aux1210={mLHScol123[1],mLHScol123[1],mLHScol123[1],mLHScol123[1]};
	vector float aux1211={mLHScol123[2],mLHScol123[2],mLHScol123[2],mLHScol123[2]};
	vector float aux1212={mLHScol123[3],mLHScol123[3],mLHScol123[3],mLHScol123[3]};

//===================================================================================
//end of splat
//===================================================================================
//store rows
//===================================================================================
		//row 1 of result
	vec_xst(vec_madd(aux121, mRHSrow121, vec_madd(aux111, mRHSrow111, vec_madd(aux101, mRHSrow101, vec_madd(aux91, mRHSrow91, vec_madd(aux81, mRHSrow81, vec_madd(aux71, mRHSrow71, vec_madd(aux61, mRHSrow61, vec_madd(aux51, mRHSrow51, vec_madd(aux41, mRHSrow41, vec_madd(aux31, mRHSrow31, vec_madd(aux21, mRHSrow21, vec_mul(aux11, mRHSrow11)))))))))))), 0, mResult);
	vec_xst(vec_madd(aux121, mRHSrow122, vec_madd(aux111, mRHSrow112, vec_madd(aux101, mRHSrow102, vec_madd(aux91, mRHSrow92, vec_madd(aux81, mRHSrow82, vec_madd(aux71, mRHSrow72, vec_madd(aux61, mRHSrow62, vec_madd(aux51, mRHSrow52, vec_madd(aux41, mRHSrow42, vec_madd(aux31, mRHSrow32, vec_madd(aux21, mRHSrow22, vec_mul(aux11, mRHSrow12)))))))))))), 0, mResult + 4);
	vec_xst(vec_madd(aux121, mRHSrow123, vec_madd(aux111, mRHSrow113, vec_madd(aux101, mRHSrow103, vec_madd(aux91, mRHSrow93, vec_madd(aux81, mRHSrow83, vec_madd(aux71, mRHSrow73, vec_madd(aux61, mRHSrow63, vec_madd(aux51, mRHSrow53, vec_madd(aux41, mRHSrow43, vec_madd(aux31, mRHSrow33, vec_madd(aux21, mRHSrow23, vec_mul(aux11, mRHSrow13)))))))))))), 0, mResult + 4*2);

	//row 2 of result
	vec_xst(vec_madd(aux122, mRHSrow121, vec_madd(aux112, mRHSrow111, vec_madd(aux102, mRHSrow101, vec_madd(aux92, mRHSrow91, vec_madd(aux82, mRHSrow81, vec_madd(aux72, mRHSrow71, vec_madd(aux62, mRHSrow61, vec_madd(aux52, mRHSrow51, vec_madd(aux42, mRHSrow41, vec_madd(aux32, mRHSrow31, vec_madd(aux22, mRHSrow21, vec_mul(aux12, mRHSrow11)))))))))))), 0, mResult + 4*3);
	vec_xst(vec_madd(aux122, mRHSrow122, vec_madd(aux112, mRHSrow112, vec_madd(aux102, mRHSrow102, vec_madd(aux92, mRHSrow92, vec_madd(aux82, mRHSrow82, vec_madd(aux72, mRHSrow72, vec_madd(aux62, mRHSrow62, vec_madd(aux52, mRHSrow52, vec_madd(aux42, mRHSrow42, vec_madd(aux32, mRHSrow32, vec_madd(aux22, mRHSrow22, vec_mul(aux12, mRHSrow12)))))))))))), 0, mResult + 4*4);
	vec_xst(vec_madd(aux122, mRHSrow123, vec_madd(aux112, mRHSrow113, vec_madd(aux102, mRHSrow103, vec_madd(aux92, mRHSrow93, vec_madd(aux82, mRHSrow83, vec_madd(aux72, mRHSrow73, vec_madd(aux62, mRHSrow63, vec_madd(aux52, mRHSrow53, vec_madd(aux42, mRHSrow43, vec_madd(aux32, mRHSrow33, vec_madd(aux22, mRHSrow23, vec_mul(aux12, mRHSrow13)))))))))))), 0, mResult + 4*5);

	// row 3 of mResult
	vec_xst(vec_madd(aux123, mRHSrow121, vec_madd(aux113, mRHSrow111, vec_madd(aux103, mRHSrow101, vec_madd(aux93, mRHSrow91, vec_madd(aux83, mRHSrow81, vec_madd(aux73, mRHSrow71, vec_madd(aux63, mRHSrow61, vec_madd(aux53, mRHSrow51, vec_madd(aux43, mRHSrow41, vec_madd(aux33, mRHSrow31, vec_madd(aux23, mRHSrow21, vec_mul(aux13, mRHSrow11)))))))))))), 0, mResult + 4*6);
	vec_xst(vec_madd(aux123, mRHSrow122, vec_madd(aux113, mRHSrow112, vec_madd(aux103, mRHSrow102, vec_madd(aux93, mRHSrow92, vec_madd(aux83, mRHSrow82, vec_madd(aux73, mRHSrow72, vec_madd(aux63, mRHSrow62, vec_madd(aux53, mRHSrow52, vec_madd(aux43, mRHSrow42, vec_madd(aux33, mRHSrow32, vec_madd(aux23, mRHSrow22, vec_mul(aux13, mRHSrow12)))))))))))), 0, mResult + 4*7);
	vec_xst(vec_madd(aux123, mRHSrow123, vec_madd(aux113, mRHSrow113, vec_madd(aux103, mRHSrow103, vec_madd(aux93, mRHSrow93, vec_madd(aux83, mRHSrow83, vec_madd(aux73, mRHSrow73, vec_madd(aux63, mRHSrow63, vec_madd(aux53, mRHSrow53, vec_madd(aux43, mRHSrow43, vec_madd(aux33, mRHSrow33, vec_madd(aux23, mRHSrow23, vec_mul(aux13, mRHSrow13)))))))))))), 0, mResult + 4*8);
	
	// row 4 of mResult
	vec_xst(vec_madd(aux124, mRHSrow121, vec_madd(aux114, mRHSrow111, vec_madd(aux104, mRHSrow101, vec_madd(aux94, mRHSrow91, vec_madd(aux84, mRHSrow81, vec_madd(aux74, mRHSrow71, vec_madd(aux64, mRHSrow61, vec_madd(aux54, mRHSrow51, vec_madd(aux44, mRHSrow41, vec_madd(aux34, mRHSrow31, vec_madd(aux24, mRHSrow21, vec_mul(aux14, mRHSrow11)))))))))))), 0, mResult + 4*9);
	vec_xst(vec_madd(aux124, mRHSrow122, vec_madd(aux114, mRHSrow112, vec_madd(aux104, mRHSrow102, vec_madd(aux94, mRHSrow92, vec_madd(aux84, mRHSrow82, vec_madd(aux74, mRHSrow72, vec_madd(aux64, mRHSrow62, vec_madd(aux54, mRHSrow52, vec_madd(aux44, mRHSrow42, vec_madd(aux34, mRHSrow32, vec_madd(aux24, mRHSrow22, vec_mul(aux14, mRHSrow12)))))))))))), 0, mResult + 4*10);
	vec_xst(vec_madd(aux124, mRHSrow123, vec_madd(aux114, mRHSrow113, vec_madd(aux104, mRHSrow103, vec_madd(aux94, mRHSrow93, vec_madd(aux84, mRHSrow83, vec_madd(aux74, mRHSrow73, vec_madd(aux64, mRHSrow63, vec_madd(aux54, mRHSrow53, vec_madd(aux44, mRHSrow43, vec_madd(aux34, mRHSrow33, vec_madd(aux24, mRHSrow23, vec_mul(aux14, mRHSrow13)))))))))))), 0, mResult + 4*11);
	
	// row 5 of mResult
	vec_xst(vec_madd(aux125, mRHSrow121, vec_madd(aux115, mRHSrow111, vec_madd(aux105, mRHSrow101, vec_madd(aux95, mRHSrow91, vec_madd(aux85, mRHSrow81, vec_madd(aux75, mRHSrow71, vec_madd(aux65, mRHSrow61, vec_madd(aux55, mRHSrow51, vec_madd(aux45, mRHSrow41, vec_madd(aux35, mRHSrow31, vec_madd(aux25, mRHSrow21, vec_mul(aux15, mRHSrow11)))))))))))), 0, mResult + 4*12);
	vec_xst(vec_madd(aux125, mRHSrow122, vec_madd(aux115, mRHSrow112, vec_madd(aux105, mRHSrow102, vec_madd(aux95, mRHSrow92, vec_madd(aux85, mRHSrow82, vec_madd(aux75, mRHSrow72, vec_madd(aux65, mRHSrow62, vec_madd(aux55, mRHSrow52, vec_madd(aux45, mRHSrow42, vec_madd(aux35, mRHSrow32, vec_madd(aux25, mRHSrow22, vec_mul(aux15, mRHSrow12)))))))))))), 0, mResult + 4*13);
	vec_xst(vec_madd(aux125, mRHSrow123, vec_madd(aux115, mRHSrow113, vec_madd(aux105, mRHSrow103, vec_madd(aux95, mRHSrow93, vec_madd(aux85, mRHSrow83, vec_madd(aux75, mRHSrow73, vec_madd(aux65, mRHSrow63, vec_madd(aux55, mRHSrow53, vec_madd(aux45, mRHSrow43, vec_madd(aux35, mRHSrow33, vec_madd(aux25, mRHSrow23, vec_mul(aux15, mRHSrow13)))))))))))), 0, mResult + 4*14);
	
	// row 6 of mResult
	vec_xst(vec_madd(aux126, mRHSrow121, vec_madd(aux116, mRHSrow111, vec_madd(aux106, mRHSrow101, vec_madd(aux96, mRHSrow91, vec_madd(aux86, mRHSrow81, vec_madd(aux76, mRHSrow71, vec_madd(aux66, mRHSrow61, vec_madd(aux56, mRHSrow51, vec_madd(aux46, mRHSrow41, vec_madd(aux36, mRHSrow31, vec_madd(aux26, mRHSrow21, vec_mul(aux16, mRHSrow11)))))))))))), 0, mResult + 4*15);
	vec_xst(vec_madd(aux126, mRHSrow122, vec_madd(aux116, mRHSrow112, vec_madd(aux106, mRHSrow102, vec_madd(aux96, mRHSrow92, vec_madd(aux86, mRHSrow82, vec_madd(aux76, mRHSrow72, vec_madd(aux66, mRHSrow62, vec_madd(aux56, mRHSrow52, vec_madd(aux46, mRHSrow42, vec_madd(aux36, mRHSrow32, vec_madd(aux26, mRHSrow22, vec_mul(aux16, mRHSrow12)))))))))))), 0, mResult + 4*16);
	vec_xst(vec_madd(aux126, mRHSrow123, vec_madd(aux116, mRHSrow113, vec_madd(aux106, mRHSrow103, vec_madd(aux96, mRHSrow93, vec_madd(aux86, mRHSrow83, vec_madd(aux76, mRHSrow73, vec_madd(aux66, mRHSrow63, vec_madd(aux56, mRHSrow53, vec_madd(aux46, mRHSrow43, vec_madd(aux36, mRHSrow33, vec_madd(aux26, mRHSrow23, vec_mul(aux16, mRHSrow13)))))))))))), 0, mResult + 4*17);
	
	// row 7 of mResult
	vec_xst(vec_madd(aux127, mRHSrow121, vec_madd(aux117, mRHSrow111, vec_madd(aux107, mRHSrow101, vec_madd(aux97, mRHSrow91, vec_madd(aux87, mRHSrow81, vec_madd(aux77, mRHSrow71, vec_madd(aux67, mRHSrow61, vec_madd(aux57, mRHSrow51, vec_madd(aux47, mRHSrow41, vec_madd(aux37, mRHSrow31, vec_madd(aux27, mRHSrow21, vec_mul(aux17, mRHSrow11)))))))))))), 0, mResult + 4*18);
	vec_xst(vec_madd(aux127, mRHSrow122, vec_madd(aux117, mRHSrow112, vec_madd(aux107, mRHSrow102, vec_madd(aux97, mRHSrow92, vec_madd(aux87, mRHSrow82, vec_madd(aux77, mRHSrow72, vec_madd(aux67, mRHSrow62, vec_madd(aux57, mRHSrow52, vec_madd(aux47, mRHSrow42, vec_madd(aux37, mRHSrow32, vec_madd(aux27, mRHSrow22, vec_mul(aux17, mRHSrow12)))))))))))), 0, mResult + 4*19);
	vec_xst(vec_madd(aux127, mRHSrow123, vec_madd(aux117, mRHSrow113, vec_madd(aux107, mRHSrow103, vec_madd(aux97, mRHSrow93, vec_madd(aux87, mRHSrow83, vec_madd(aux77, mRHSrow73, vec_madd(aux67, mRHSrow63, vec_madd(aux57, mRHSrow53, vec_madd(aux47, mRHSrow43, vec_madd(aux37, mRHSrow33, vec_madd(aux27, mRHSrow23, vec_mul(aux17, mRHSrow13)))))))))))), 0, mResult + 4*20);
	
	// row 8 of mResult
	vec_xst(vec_madd(aux128, mRHSrow121, vec_madd(aux118, mRHSrow111, vec_madd(aux108, mRHSrow101, vec_madd(aux98, mRHSrow91, vec_madd(aux88, mRHSrow81, vec_madd(aux78, mRHSrow71, vec_madd(aux68, mRHSrow61, vec_madd(aux58, mRHSrow51, vec_madd(aux48, mRHSrow41, vec_madd(aux38, mRHSrow31, vec_madd(aux28, mRHSrow21, vec_mul(aux18, mRHSrow11)))))))))))), 0, mResult + 4*21);
	vec_xst(vec_madd(aux128, mRHSrow122, vec_madd(aux118, mRHSrow112, vec_madd(aux108, mRHSrow102, vec_madd(aux98, mRHSrow92, vec_madd(aux88, mRHSrow82, vec_madd(aux78, mRHSrow72, vec_madd(aux68, mRHSrow62, vec_madd(aux58, mRHSrow52, vec_madd(aux48, mRHSrow42, vec_madd(aux38, mRHSrow32, vec_madd(aux28, mRHSrow22, vec_mul(aux18, mRHSrow12)))))))))))), 0, mResult + 4*22);
	vec_xst(vec_madd(aux128, mRHSrow123, vec_madd(aux118, mRHSrow113, vec_madd(aux108, mRHSrow103, vec_madd(aux98, mRHSrow93, vec_madd(aux88, mRHSrow83, vec_madd(aux78, mRHSrow73, vec_madd(aux68, mRHSrow63, vec_madd(aux58, mRHSrow53, vec_madd(aux48, mRHSrow43, vec_madd(aux38, mRHSrow33, vec_madd(aux28, mRHSrow23, vec_mul(aux18, mRHSrow13)))))))))))), 0, mResult + 4*23);
	
	// row 9 of mResult
	vec_xst(vec_madd(aux129, mRHSrow121, vec_madd(aux119, mRHSrow111, vec_madd(aux109, mRHSrow101, vec_madd(aux99, mRHSrow91, vec_madd(aux89, mRHSrow81, vec_madd(aux79, mRHSrow71, vec_madd(aux69, mRHSrow61, vec_madd(aux59, mRHSrow51, vec_madd(aux49, mRHSrow41, vec_madd(aux39, mRHSrow31, vec_madd(aux29, mRHSrow21, vec_mul(aux19, mRHSrow11)))))))))))), 0, mResult + 4*24);
	vec_xst(vec_madd(aux129, mRHSrow122, vec_madd(aux119, mRHSrow112, vec_madd(aux109, mRHSrow102, vec_madd(aux99, mRHSrow92, vec_madd(aux89, mRHSrow82, vec_madd(aux79, mRHSrow72, vec_madd(aux69, mRHSrow62, vec_madd(aux59, mRHSrow52, vec_madd(aux49, mRHSrow42, vec_madd(aux39, mRHSrow32, vec_madd(aux29, mRHSrow22, vec_mul(aux19, mRHSrow12)))))))))))), 0, mResult + 4*25);
	vec_xst(vec_madd(aux129, mRHSrow123, vec_madd(aux119, mRHSrow113, vec_madd(aux109, mRHSrow103, vec_madd(aux99, mRHSrow93, vec_madd(aux89, mRHSrow83, vec_madd(aux79, mRHSrow73, vec_madd(aux69, mRHSrow63, vec_madd(aux59, mRHSrow53, vec_madd(aux49, mRHSrow43, vec_madd(aux39, mRHSrow33, vec_madd(aux29, mRHSrow23, vec_mul(aux19, mRHSrow13)))))))))))), 0, mResult + 4*26);
	
	// row 10 of mResult
	vec_xst(vec_madd(aux1210, mRHSrow121, vec_madd(aux1110, mRHSrow111, vec_madd(aux1010, mRHSrow101, vec_madd(aux910, mRHSrow91, vec_madd(aux810, mRHSrow81, vec_madd(aux710, mRHSrow71, vec_madd(aux610, mRHSrow61, vec_madd(aux510, mRHSrow51, vec_madd(aux410, mRHSrow41, vec_madd(aux310, mRHSrow31, vec_madd(aux210, mRHSrow21, vec_mul(aux110, mRHSrow11)))))))))))), 0, mResult + 4*27);
	vec_xst(vec_madd(aux1210, mRHSrow122, vec_madd(aux1110, mRHSrow112, vec_madd(aux1010, mRHSrow102, vec_madd(aux910, mRHSrow92, vec_madd(aux810, mRHSrow82, vec_madd(aux710, mRHSrow72, vec_madd(aux610, mRHSrow62, vec_madd(aux510, mRHSrow52, vec_madd(aux410, mRHSrow42, vec_madd(aux310, mRHSrow32, vec_madd(aux210, mRHSrow22, vec_mul(aux110, mRHSrow12)))))))))))), 0, mResult + 4*28);
	vec_xst(vec_madd(aux1210, mRHSrow123, vec_madd(aux1110, mRHSrow113, vec_madd(aux1010, mRHSrow103, vec_madd(aux910, mRHSrow93, vec_madd(aux810, mRHSrow83, vec_madd(aux710, mRHSrow73, vec_madd(aux610, mRHSrow63, vec_madd(aux510, mRHSrow53, vec_madd(aux410, mRHSrow43, vec_madd(aux310, mRHSrow33, vec_madd(aux210, mRHSrow23, vec_mul(aux110, mRHSrow13)))))))))))), 0, mResult + 4*29);
	
	// row 11 of mResult
	vec_xst(vec_madd(aux1211, mRHSrow121, vec_madd(aux1111, mRHSrow111, vec_madd(aux1011, mRHSrow101, vec_madd(aux911, mRHSrow91, vec_madd(aux811, mRHSrow81, vec_madd(aux711, mRHSrow71, vec_madd(aux611, mRHSrow61, vec_madd(aux511, mRHSrow51, vec_madd(aux411, mRHSrow41, vec_madd(aux311, mRHSrow31, vec_madd(aux211, mRHSrow21, vec_mul(aux0111, mRHSrow11)))))))))))), 0, mResult + 4*30);
	vec_xst(vec_madd(aux1211, mRHSrow122, vec_madd(aux1111, mRHSrow112, vec_madd(aux1011, mRHSrow102, vec_madd(aux911, mRHSrow92, vec_madd(aux811, mRHSrow82, vec_madd(aux711, mRHSrow72, vec_madd(aux611, mRHSrow62, vec_madd(aux511, mRHSrow52, vec_madd(aux411, mRHSrow42, vec_madd(aux311, mRHSrow32, vec_madd(aux211, mRHSrow22, vec_mul(aux0111, mRHSrow12)))))))))))), 0, mResult + 4*31);
	vec_xst(vec_madd(aux1211, mRHSrow123, vec_madd(aux1111, mRHSrow113, vec_madd(aux1011, mRHSrow103, vec_madd(aux911, mRHSrow93, vec_madd(aux811, mRHSrow83, vec_madd(aux711, mRHSrow73, vec_madd(aux611, mRHSrow63, vec_madd(aux511, mRHSrow53, vec_madd(aux411, mRHSrow43, vec_madd(aux311, mRHSrow33, vec_madd(aux211, mRHSrow23, vec_mul(aux0111, mRHSrow13)))))))))))), 0, mResult + 4*32);
	
	// row 12 of mResult
	vec_xst(vec_madd(aux1212, mRHSrow121, vec_madd(aux1112, mRHSrow111, vec_madd(aux1012, mRHSrow101, vec_madd(aux912, mRHSrow91, vec_madd(aux812, mRHSrow81, vec_madd(aux712, mRHSrow71, vec_madd(aux612, mRHSrow61, vec_madd(aux512, mRHSrow51, vec_madd(aux412, mRHSrow41, vec_madd(aux312, mRHSrow31, vec_madd(aux212, mRHSrow21, vec_mul(aux0112, mRHSrow11)))))))))))), 0, mResult + 4*33);
	vec_xst(vec_madd(aux1212, mRHSrow122, vec_madd(aux1112, mRHSrow112, vec_madd(aux1012, mRHSrow102, vec_madd(aux912, mRHSrow92, vec_madd(aux812, mRHSrow82, vec_madd(aux712, mRHSrow72, vec_madd(aux612, mRHSrow62, vec_madd(aux512, mRHSrow52, vec_madd(aux412, mRHSrow42, vec_madd(aux312, mRHSrow32, vec_madd(aux212, mRHSrow22, vec_mul(aux0112, mRHSrow12)))))))))))), 0, mResult + 4*34);
	vec_xst(vec_madd(aux1212, mRHSrow123, vec_madd(aux1112, mRHSrow113, vec_madd(aux1012, mRHSrow103, vec_madd(aux912, mRHSrow93, vec_madd(aux812, mRHSrow83, vec_madd(aux712, mRHSrow73, vec_madd(aux612, mRHSrow63, vec_madd(aux512, mRHSrow53, vec_madd(aux412, mRHSrow43, vec_madd(aux312, mRHSrow33, vec_madd(aux212, mRHSrow23, vec_mul(aux0112, mRHSrow13)))))))))))), 0, mResult + 4*35);
	

}
//float 9x9 matrices
inline void mul9x9ColMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){

	vector float mLHScol11, mLHScol12, mLHScol13, mLHScol21, mLHScol22, mLHScol23, mLHScol31, mLHScol32, mLHScol33,
	      	     mLHScol41, mLHScol42, mLHScol43, mLHScol51, mLHScol52, mLHScol53, mLHScol61, mLHScol62, mLHScol63,
		     mLHScol71, mLHScol72, mLHScol73, mLHScol81, mLHScol82, mLHScol83, mLHScol91, mLHScol92, mLHScol93;

	vector float mRHSrow11, mRHSrow12, mRHSrow13, mRHSrow21, mRHSrow22, mRHSrow23, mRHSrow31, mRHSrow32, mRHSrow33,
	      	     mRHSrow41, mRHSrow42, mRHSrow43, mRHSrow51, mRHSrow52, mRHSrow53, mRHSrow61, mRHSrow62, mRHSrow63,
		     mRHSrow71, mRHSrow72, mRHSrow73, mRHSrow81, mRHSrow82, mRHSrow83, mRHSrow91, mRHSrow92, mRHSrow93;

//load
// __8__17__26__35__44__53__62__71__80
	mLHScol11 = vec_xl(0,mLHS);
	mLHScol12 = vec_xl(0,mLHS+4);
	mLHScol13 = vec_splats((float)0);
	mLHScol13[0] = mLHS[8];

	mLHScol21 = vec_xl(0,mLHS+4*2+1);
	mLHScol22 = vec_xl(0,mLHS+4*3+1);
	mLHScol23 = vec_splats((float)0);
	mLHScol23[0] = mLHS[17];

	mLHScol31 = vec_xl(0,mLHS+4*4+2);
	mLHScol32 = vec_xl(0,mLHS+4*5+2);
	mLHScol33 = vec_splats((float)0);
	mLHScol33[0] = mLHS[26];

	mLHScol41 = vec_xl(0,mLHS+4*6+3);
	mLHScol42 = vec_xl(0,mLHS+4*7+3);
	mLHScol43 = vec_splats((float)0);
	mLHScol43[0] = mLHS[35];

	mLHScol51 = vec_xl(0,mLHS+4*8+4);
	mLHScol52 = vec_xl(0,mLHS+4*9+4);
	mLHScol53 = vec_splats((float)0);
	mLHScol53[0] = mLHS[44];

	mLHScol61 = vec_xl(0,mLHS+4*10+5);
	mLHScol62 = vec_xl(0,mLHS+4*11+5);
	mLHScol63 = vec_splats((float)0);
	mLHScol63[0] = mLHS[53];

	mLHScol71 = vec_xl(0,mLHS+4*12+6);
	mLHScol72 = vec_xl(0,mLHS+4*13+6);
	mLHScol73 = vec_splats((float)0);
	mLHScol73[0] = mLHS[62];

	mLHScol81 = vec_xl(0,mLHS+4*14+7);
	mLHScol82 = vec_xl(0,mLHS+4*15+7);
	mLHScol83 = vec_splats((float)0);
	mLHScol83[0] = mLHS[71];

	mLHScol91 = vec_xl(0,mLHS+4*16+8);
	mLHScol92 = vec_xl(0,mLHS+4*17+8);
	mLHScol93 = vec_splats((float)0);
	mLHScol93[0] = mLHS[80];
//--------------------------------------------------------------------------------

	mRHSrow11 = vec_xl(0,mRHS);
	mRHSrow12 = vec_xl(0,mRHS+4);
	mRHSrow13 = vec_splats((float)0);
	mRHSrow13[0] = mRHS[8];

	mRHSrow21 = vec_xl(0,mRHS+4*2+1);
	mRHSrow22 = vec_xl(0,mRHS+4*3+1);
	mRHSrow23 = vec_splats((float)0);
	mRHSrow23[0] = mRHS[17];

	mRHSrow31 = vec_xl(0,mRHS+4*4+2);
	mRHSrow32 = vec_xl(0,mRHS+4*5+2);
	mRHSrow33 = vec_splats((float)0);
	mRHSrow33[0] = mRHS[26];

	mRHSrow41 = vec_xl(0,mRHS+4*6+3);
	mRHSrow42 = vec_xl(0,mRHS+4*7+3);
	mRHSrow43 = vec_splats((float)0);
	mRHSrow43[0] = mRHS[35];

	mRHSrow51 = vec_xl(0,mRHS+4*8+4);
	mRHSrow52 = vec_xl(0,mRHS+4*9+4);
	mRHSrow53 = vec_splats((float)0);
	mRHSrow53[0] = mRHS[44];

	mRHSrow61 = vec_xl(0,mRHS+4*10+5);
	mRHSrow62 = vec_xl(0,mRHS+4*11+5);
	mRHSrow63 = vec_splats((float)0);
	mRHSrow63[0] = mRHS[53];
	
	mRHSrow71 = vec_xl(0,mRHS+4*12+6);
	mRHSrow72 = vec_xl(0,mRHS+4*13+6);
	mRHSrow73 = vec_splats((float)0);
	mRHSrow73[0] = mRHS[62];

	mRHSrow81 = vec_xl(0,mRHS+4*14+7);
	mRHSrow82 = vec_xl(0,mRHS+4*15+7);
	mRHSrow83 = vec_splats((float)0);
	mRHSrow83[0] = mRHS[71];

	mRHSrow91 = vec_xl(0,mRHS+4*16+8);
	mRHSrow92 = vec_xl(0,mRHS+4*17+8);
	mRHSrow93 = vec_splats((float)0);
	mRHSrow93[0] = mRHS[80];

//===================================================================================
//Splat
//===================================================================================
	vector float aux11={mLHScol11[0],mLHScol11[0],mLHScol11[0],mLHScol11[0]};
	vector float aux12={mLHScol11[1],mLHScol11[1],mLHScol11[1],mLHScol11[1]};
	vector float aux13={mLHScol11[2],mLHScol11[2],mLHScol11[2],mLHScol11[2]};
	vector float aux14={mLHScol11[3],mLHScol11[3],mLHScol11[3],mLHScol11[3]};

	vector float aux15={mLHScol12[0],mLHScol12[0],mLHScol12[0],mLHScol12[0]};
	vector float aux16={mLHScol12[1],mLHScol12[1],mLHScol12[1],mLHScol12[1]};
	vector float aux17={mLHScol12[2],mLHScol12[2],mLHScol12[2],mLHScol12[2]};
	vector float aux18={mLHScol12[3],mLHScol12[3],mLHScol12[3],mLHScol12[3]};
	
	vector float aux19={mLHScol13[0],mLHScol13[0],mLHScol13[0],mLHScol13[0]};
//===================================================================================
	vector float aux21={mLHScol21[0],mLHScol21[0],mLHScol21[0],mLHScol21[0]};
	vector float aux22={mLHScol21[1],mLHScol21[1],mLHScol21[1],mLHScol21[1]};
	vector float aux23={mLHScol21[2],mLHScol21[2],mLHScol21[2],mLHScol21[2]};
	vector float aux24={mLHScol21[3],mLHScol21[3],mLHScol21[3],mLHScol21[3]};

	vector float aux25={mLHScol22[0],mLHScol22[0],mLHScol22[0],mLHScol22[0]};
	vector float aux26={mLHScol22[1],mLHScol22[1],mLHScol22[1],mLHScol22[1]};
	vector float aux27={mLHScol22[2],mLHScol22[2],mLHScol22[2],mLHScol22[2]};
	vector float aux28={mLHScol22[3],mLHScol22[3],mLHScol22[3],mLHScol22[3]};

	vector float aux29={mLHScol23[0],mLHScol23[0],mLHScol23[0],mLHScol23[0]};
//===================================================================================

	vector float aux31={mLHScol31[0],mLHScol31[0],mLHScol31[0],mLHScol31[0]};
	vector float aux32={mLHScol31[1],mLHScol31[1],mLHScol31[1],mLHScol31[1]};
	vector float aux33={mLHScol31[2],mLHScol31[2],mLHScol31[2],mLHScol31[2]};
	vector float aux34={mLHScol31[3],mLHScol31[3],mLHScol31[3],mLHScol31[3]};

	vector float aux35={mLHScol32[0],mLHScol32[0],mLHScol32[0],mLHScol32[0]};
	vector float aux36={mLHScol32[1],mLHScol32[1],mLHScol32[1],mLHScol32[1]};
	vector float aux37={mLHScol32[2],mLHScol32[2],mLHScol32[2],mLHScol32[2]};
	vector float aux38={mLHScol32[3],mLHScol32[3],mLHScol32[3],mLHScol32[3]};

	vector float aux39={mLHScol33[0],mLHScol33[0],mLHScol33[0],mLHScol33[0]};
//===================================================================================

	vector float aux41={mLHScol41[0],mLHScol41[0],mLHScol41[0],mLHScol41[0]};
	vector float aux42={mLHScol41[1],mLHScol41[1],mLHScol41[1],mLHScol41[1]};
	vector float aux43={mLHScol41[2],mLHScol41[2],mLHScol41[2],mLHScol41[2]};
	vector float aux44={mLHScol41[3],mLHScol41[3],mLHScol41[3],mLHScol41[3]};

	vector float aux45={mLHScol42[0],mLHScol42[0],mLHScol42[0],mLHScol42[0]};
	vector float aux46={mLHScol42[1],mLHScol42[1],mLHScol42[1],mLHScol42[1]};
	vector float aux47={mLHScol42[2],mLHScol42[2],mLHScol42[2],mLHScol42[2]};
	vector float aux48={mLHScol42[3],mLHScol42[3],mLHScol42[3],mLHScol42[3]};

	vector float aux49={mLHScol43[0],mLHScol43[0],mLHScol43[0],mLHScol43[0]};
//===================================================================================
	vector float aux51={mLHScol51[0],mLHScol51[0],mLHScol51[0],mLHScol51[0]};
	vector float aux52={mLHScol51[1],mLHScol51[1],mLHScol51[1],mLHScol51[1]};
	vector float aux53={mLHScol51[2],mLHScol51[2],mLHScol51[2],mLHScol51[2]};
	vector float aux54={mLHScol51[3],mLHScol51[3],mLHScol51[3],mLHScol51[3]};

	vector float aux55={mLHScol52[0],mLHScol52[0],mLHScol52[0],mLHScol52[0]};
	vector float aux56={mLHScol52[1],mLHScol52[1],mLHScol52[1],mLHScol52[1]};
	vector float aux57={mLHScol52[2],mLHScol52[2],mLHScol52[2],mLHScol52[2]};
	vector float aux58={mLHScol52[3],mLHScol52[3],mLHScol52[3],mLHScol52[3]};

	vector float aux59={mLHScol53[0],mLHScol53[0],mLHScol53[0],mLHScol53[0]};
//===================================================================================
	vector float aux61={mLHScol61[0],mLHScol61[0],mLHScol61[0],mLHScol61[0]};
	vector float aux62={mLHScol61[1],mLHScol61[1],mLHScol61[1],mLHScol61[1]};
	vector float aux63={mLHScol61[2],mLHScol61[2],mLHScol61[2],mLHScol61[2]};
	vector float aux64={mLHScol61[3],mLHScol61[3],mLHScol61[3],mLHScol61[3]};

	vector float aux65={mLHScol62[0],mLHScol62[0],mLHScol62[0],mLHScol62[0]};
	vector float aux66={mLHScol62[1],mLHScol62[1],mLHScol62[1],mLHScol62[1]};
	vector float aux67={mLHScol62[2],mLHScol62[2],mLHScol62[2],mLHScol62[2]};
	vector float aux68={mLHScol62[3],mLHScol62[3],mLHScol62[3],mLHScol62[3]};

	vector float aux69={mLHScol63[0],mLHScol63[0],mLHScol63[0],mLHScol63[0]};
//===================================================================================
	vector float aux71={mLHScol71[0],mLHScol71[0],mLHScol71[0],mLHScol71[0]};
	vector float aux72={mLHScol71[1],mLHScol71[1],mLHScol71[1],mLHScol71[1]};
	vector float aux73={mLHScol71[2],mLHScol71[2],mLHScol71[2],mLHScol71[2]};
	vector float aux74={mLHScol71[3],mLHScol71[3],mLHScol71[3],mLHScol71[3]};

	vector float aux75={mLHScol72[0],mLHScol72[0],mLHScol72[0],mLHScol72[0]};
	vector float aux76={mLHScol72[1],mLHScol72[1],mLHScol72[1],mLHScol72[1]};
	vector float aux77={mLHScol72[2],mLHScol72[2],mLHScol72[2],mLHScol72[2]};
	vector float aux78={mLHScol72[3],mLHScol72[3],mLHScol72[3],mLHScol72[3]};

	vector float aux79={mLHScol73[0],mLHScol73[0],mLHScol73[0],mLHScol73[0]};
//===================================================================================
	vector float aux81={mLHScol81[0],mLHScol81[0],mLHScol81[0],mLHScol81[0]};
	vector float aux82={mLHScol81[1],mLHScol81[1],mLHScol81[1],mLHScol81[1]};
	vector float aux83={mLHScol81[2],mLHScol81[2],mLHScol81[2],mLHScol81[2]};
	vector float aux84={mLHScol81[3],mLHScol81[3],mLHScol81[3],mLHScol81[3]};

	vector float aux85={mLHScol82[0],mLHScol82[0],mLHScol82[0],mLHScol82[0]};
	vector float aux86={mLHScol82[1],mLHScol82[1],mLHScol82[1],mLHScol82[1]};
	vector float aux87={mLHScol82[2],mLHScol82[2],mLHScol82[2],mLHScol82[2]};
	vector float aux88={mLHScol82[3],mLHScol82[3],mLHScol82[3],mLHScol82[3]};

	vector float aux89={mLHScol83[0],mLHScol83[0],mLHScol83[0],mLHScol83[0]};
//===================================================================================
	vector float aux91={mLHScol91[0],mLHScol91[0],mLHScol91[0],mLHScol91[0]};
	vector float aux92={mLHScol91[1],mLHScol91[1],mLHScol91[1],mLHScol91[1]};
	vector float aux93={mLHScol91[2],mLHScol91[2],mLHScol91[2],mLHScol91[2]};
	vector float aux94={mLHScol91[3],mLHScol91[3],mLHScol91[3],mLHScol91[3]};

	vector float aux95={mLHScol92[0],mLHScol92[0],mLHScol92[0],mLHScol92[0]};
	vector float aux96={mLHScol92[1],mLHScol92[1],mLHScol92[1],mLHScol92[1]};
	vector float aux97={mLHScol92[2],mLHScol92[2],mLHScol92[2],mLHScol92[2]};
	vector float aux98={mLHScol92[3],mLHScol92[3],mLHScol92[3],mLHScol92[3]};

	vector float aux99={mLHScol93[0],mLHScol93[0],mLHScol93[0],mLHScol93[0]};
//===================================================================================
//end of splat
//===================================================================================

//row1
	vec_xst(vec_madd( mRHSrow91, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux21, vec_mul(mRHSrow11, aux11)),
					vec_madd(mRHSrow41, aux41, vec_mul(mRHSrow31, aux31)) ),
				vec_add(
					vec_madd(mRHSrow61, aux61, vec_mul(mRHSrow51, aux51)),
					vec_madd(mRHSrow81, aux81, vec_mul(mRHSrow71, aux71)) ) ) ),

				0, mResult);	

	
	vec_xst(vec_madd( mRHSrow92, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux21, vec_mul(mRHSrow12, aux11)),
					vec_madd(mRHSrow42, aux41, vec_mul(mRHSrow32, aux31)) ),
				vec_add(
					vec_madd(mRHSrow62, aux61, vec_mul(mRHSrow52, aux51)),
					vec_madd(mRHSrow82, aux81, vec_mul(mRHSrow72, aux71)) ) ) ),

				0, mResult+4);

	vec_xst(vec_madd( mRHSrow93, aux91,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux21, vec_mul(mRHSrow13, aux11)),
					vec_madd(mRHSrow43, aux41, vec_mul(mRHSrow33, aux31)) ),
				vec_add(
					vec_madd(mRHSrow63, aux61, vec_mul(mRHSrow53, aux51)),
					vec_madd(mRHSrow83, aux81, vec_mul(mRHSrow73, aux71)) ) ) ),

				0, mResult+8);	
//row 2


	vec_xst(vec_madd( mRHSrow91, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux22, vec_mul(mRHSrow11, aux12)),
					vec_madd(mRHSrow41, aux42, vec_mul(mRHSrow31, aux32)) ),
				vec_add(
					vec_madd(mRHSrow61, aux62, vec_mul(mRHSrow51, aux52)),
					vec_madd(mRHSrow81, aux82, vec_mul(mRHSrow71, aux72)) ) ) ),

				0, mResult+4*2+1);

	vec_xst(vec_madd( mRHSrow92, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux22, vec_mul(mRHSrow12, aux12)),
					vec_madd(mRHSrow42, aux42, vec_mul(mRHSrow32, aux32)) ),
				vec_add(
					vec_madd(mRHSrow62, aux62, vec_mul(mRHSrow52, aux52)),
					vec_madd(mRHSrow82, aux82, vec_mul(mRHSrow72, aux72)) ) ) ),

				0, mResult+4*3+1);


	vec_xst(vec_madd( mRHSrow93, aux92,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux22, vec_mul(mRHSrow13, aux12)),
					vec_madd(mRHSrow43, aux42, vec_mul(mRHSrow33, aux32)) ),
				vec_add(
					vec_madd(mRHSrow63, aux62, vec_mul(mRHSrow53, aux52)),
					vec_madd(mRHSrow83, aux82, vec_mul(mRHSrow73, aux72)) ) ) ),

				0, mResult+17);

//row 3


	vec_xst(vec_madd( mRHSrow91, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux23, vec_mul(mRHSrow11, aux13)),
					vec_madd(mRHSrow41, aux43, vec_mul(mRHSrow31, aux33)) ),
				vec_add(
					vec_madd(mRHSrow61, aux63, vec_mul(mRHSrow51, aux53)),
					vec_madd(mRHSrow81, aux83, vec_mul(mRHSrow71, aux73)) ) ) ),

				0, mResult+4*4+2);

	vec_xst(vec_madd( mRHSrow92, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux23, vec_mul(mRHSrow12, aux13)),
					vec_madd(mRHSrow42, aux43, vec_mul(mRHSrow32, aux33)) ),
				vec_add(
					vec_madd(mRHSrow62, aux63, vec_mul(mRHSrow52, aux53)),
					vec_madd(mRHSrow82, aux83, vec_mul(mRHSrow72, aux73)) ) ) ),

				0, mResult+4*5+2);


	vec_xst(vec_madd( mRHSrow93, aux93,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux23, vec_mul(mRHSrow13, aux13)),
					vec_madd(mRHSrow43, aux43, vec_mul(mRHSrow33, aux33)) ),
				vec_add(
					vec_madd(mRHSrow63, aux63, vec_mul(mRHSrow53, aux53)),
					vec_madd(mRHSrow83, aux83, vec_mul(mRHSrow73, aux73)) ) ) ),

				0, mResult+26);
//row 4


	vec_xst(vec_madd( mRHSrow91, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux24, vec_mul(mRHSrow11, aux14)),
					vec_madd(mRHSrow41, aux44, vec_mul(mRHSrow31, aux34)) ),
				vec_add(
					vec_madd(mRHSrow61, aux64, vec_mul(mRHSrow51, aux54)),
					vec_madd(mRHSrow81, aux84, vec_mul(mRHSrow71, aux74)) ) ) ),

				0, mResult+4*6+3);

	vec_xst(vec_madd( mRHSrow92, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux24, vec_mul(mRHSrow12, aux14)),
					vec_madd(mRHSrow42, aux44, vec_mul(mRHSrow32, aux34)) ),
				vec_add(
					vec_madd(mRHSrow62, aux64, vec_mul(mRHSrow52, aux54)),
					vec_madd(mRHSrow82, aux84, vec_mul(mRHSrow72, aux74)) ) ) ),

				0, mResult+4*7+3);

	vec_xst(vec_madd( mRHSrow93, aux94,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux24, vec_mul(mRHSrow13, aux14)),
					vec_madd(mRHSrow43, aux44, vec_mul(mRHSrow33, aux34)) ),
				vec_add(
					vec_madd(mRHSrow63, aux64, vec_mul(mRHSrow53, aux54)),
					vec_madd(mRHSrow83, aux84, vec_mul(mRHSrow73, aux74)) ) ) ),

				0, mResult+35);
//row 5


	vec_xst(vec_madd( mRHSrow91, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux25, vec_mul(mRHSrow11, aux15)),
					vec_madd(mRHSrow41, aux45, vec_mul(mRHSrow31, aux35)) ),
				vec_add(
					vec_madd(mRHSrow61, aux65, vec_mul(mRHSrow51, aux55)),
					vec_madd(mRHSrow81, aux85, vec_mul(mRHSrow71, aux75)) ) ) ),

				0, mResult+4*8+4);



	vec_xst(vec_madd( mRHSrow92, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux25, vec_mul(mRHSrow12, aux15)),
					vec_madd(mRHSrow42, aux45, vec_mul(mRHSrow32, aux35)) ),
				vec_add(
					vec_madd(mRHSrow62, aux65, vec_mul(mRHSrow52, aux55)),
					vec_madd(mRHSrow82, aux85, vec_mul(mRHSrow72, aux75)) ) ) ),

				0, mResult+4*9+4);


	vec_xst(vec_madd( mRHSrow93, aux95,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux25, vec_mul(mRHSrow13, aux15)),
					vec_madd(mRHSrow43, aux45, vec_mul(mRHSrow33, aux35)) ),
				vec_add(
					vec_madd(mRHSrow63, aux65, vec_mul(mRHSrow53, aux55)),
					vec_madd(mRHSrow83, aux85, vec_mul(mRHSrow73, aux75)) ) ) ),

				0, mResult+44);

//row 6


	vec_xst(vec_madd( mRHSrow91, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux26, vec_mul(mRHSrow11, aux16)),
					vec_madd(mRHSrow41, aux46, vec_mul(mRHSrow31, aux36)) ),
				vec_add(
					vec_madd(mRHSrow61, aux66, vec_mul(mRHSrow51, aux56)),
					vec_madd(mRHSrow81, aux86, vec_mul(mRHSrow71, aux76)) ) ) ),

				0, mResult+4*10+5);


	vec_xst(vec_madd( mRHSrow92, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux26, vec_mul(mRHSrow12, aux16)),
					vec_madd(mRHSrow42, aux46, vec_mul(mRHSrow32, aux36)) ),
				vec_add(
					vec_madd(mRHSrow62, aux66, vec_mul(mRHSrow52, aux56)),
					vec_madd(mRHSrow82, aux86, vec_mul(mRHSrow72, aux76)) ) ) ),

				0, mResult+4*11+5);


	vec_xst(vec_madd( mRHSrow93, aux96,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux26, vec_mul(mRHSrow13, aux16)),
					vec_madd(mRHSrow43, aux46, vec_mul(mRHSrow33, aux36)) ),
				vec_add(
					vec_madd(mRHSrow63, aux66, vec_mul(mRHSrow53, aux56)),
					vec_madd(mRHSrow83, aux86, vec_mul(mRHSrow73, aux76)) ) ) ),

				0, mResult+53);

//row 7


	vec_xst(vec_madd( mRHSrow91, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux27, vec_mul(mRHSrow11, aux17)),
					vec_madd(mRHSrow41, aux47, vec_mul(mRHSrow31, aux37)) ),
				vec_add(
					vec_madd(mRHSrow61, aux67, vec_mul(mRHSrow51, aux57)),
					vec_madd(mRHSrow81, aux87, vec_mul(mRHSrow71, aux77)) ) ) ),

				0, mResult+4*12+6);

	vec_xst(vec_madd( mRHSrow92, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux27, vec_mul(mRHSrow12, aux17)),
					vec_madd(mRHSrow42, aux47, vec_mul(mRHSrow32, aux37)) ),
				vec_add(
					vec_madd(mRHSrow62, aux67, vec_mul(mRHSrow52, aux57)),
					vec_madd(mRHSrow82, aux87, vec_mul(mRHSrow72, aux77)) ) ) ),

				0, mResult+4*13+6);


	vec_xst(vec_madd( mRHSrow93, aux97,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux27, vec_mul(mRHSrow13, aux17)),
					vec_madd(mRHSrow43, aux47, vec_mul(mRHSrow33, aux37)) ),
				vec_add(
					vec_madd(mRHSrow63, aux67, vec_mul(mRHSrow53, aux57)),
					vec_madd(mRHSrow83, aux87, vec_mul(mRHSrow73, aux77)) ) ) ),

				0, mResult+62);
//row 8



	vec_xst(vec_madd( mRHSrow91, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux28, vec_mul(mRHSrow11, aux18)),
					vec_madd(mRHSrow41, aux48, vec_mul(mRHSrow31, aux38)) ),
				vec_add(
					vec_madd(mRHSrow61, aux68, vec_mul(mRHSrow51, aux58)),
					vec_madd(mRHSrow81, aux88, vec_mul(mRHSrow71, aux78)) ) ) ),

				0, mResult+4*14+7);


	vec_xst(vec_madd( mRHSrow92, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux28, vec_mul(mRHSrow12, aux18)),
					vec_madd(mRHSrow42, aux48, vec_mul(mRHSrow32, aux38)) ),
				vec_add(
					vec_madd(mRHSrow62, aux68, vec_mul(mRHSrow52, aux58)),
					vec_madd(mRHSrow82, aux88, vec_mul(mRHSrow72, aux78)) ) ) ),

				0, mResult+4*15+7);


	vec_xst(vec_madd( mRHSrow93, aux98,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux28, vec_mul(mRHSrow13, aux18)),
					vec_madd(mRHSrow43, aux48, vec_mul(mRHSrow33, aux38)) ),
				vec_add(
					vec_madd(mRHSrow63, aux68, vec_mul(mRHSrow53, aux58)),
					vec_madd(mRHSrow83, aux88, vec_mul(mRHSrow73, aux78)) ) ) ),

				0, mResult+71);

//row 9


	vec_xst(vec_madd( mRHSrow91, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow21, aux29, vec_mul(mRHSrow11, aux19)),
					vec_madd(mRHSrow41, aux49, vec_mul(mRHSrow31, aux39)) ),
				vec_add(
					vec_madd(mRHSrow61, aux69, vec_mul(mRHSrow51, aux59)),
					vec_madd(mRHSrow81, aux89, vec_mul(mRHSrow71, aux79)) ) ) ),

				0, mResult+4*16+8);

	vec_xst(vec_madd( mRHSrow92, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow22, aux29, vec_mul(mRHSrow12, aux19)),
					vec_madd(mRHSrow42, aux49, vec_mul(mRHSrow32, aux39)) ),
				vec_add(
					vec_madd(mRHSrow62, aux69, vec_mul(mRHSrow52, aux59)),
					vec_madd(mRHSrow82, aux89, vec_mul(mRHSrow72, aux79)) ) ) ),

				0, mResult+4*17+8);


	vector float mResultLastElem = 
		
		vec_madd( mRHSrow93, aux99,
			vec_add(
				vec_add(
					vec_madd(mRHSrow23, aux29, vec_mul(mRHSrow13, aux19)),
					vec_madd(mRHSrow43, aux49, vec_mul(mRHSrow33, aux39)) ),
				vec_add(
					vec_madd(mRHSrow63, aux69, vec_mul(mRHSrow53, aux59)),
					vec_madd(mRHSrow83, aux89, vec_mul(mRHSrow73, aux79)) ) ) );
	mResult[80] = mResultLastElem[0];


}



//float 4x4 matrices col major

inline void mul4x4ColMajorFloat(const float* mLHS, const float* mRHS, float* const mResult){
	vector float mLHScol1,mLHScol2,mLHScol3,mLHScol4;
	vector float mRHSrow1,mRHSrow2,mRHSrow3,mRHSrow4;
	
	mLHScol1 = vec_xl(0,mLHS);
	mLHScol2 = vec_xl(0,mLHS+4);
	mLHScol3 = vec_xl(0,mLHS+8);
	mLHScol4 = vec_xl(0,mLHS+12);

	mRHSrow1 = vec_xl(0,mRHS);
	mRHSrow2 = vec_xl(0,mRHS+4);
	mRHSrow3 = vec_xl(0,mRHS+8);
	mRHSrow4 = vec_xl(0,mRHS+12);

	vector float auxLHS11 = {mLHScol1[0],mLHScol1[0],mLHScol1[0],mLHScol1[0]};
	vector float auxLHS12 = {mLHScol1[1],mLHScol1[1],mLHScol1[1],mLHScol1[1]};
	vector float auxLHS13 = {mLHScol1[2],mLHScol1[2],mLHScol1[2],mLHScol1[2]};
	vector float auxLHS14 = {mLHScol1[3],mLHScol1[3],mLHScol1[3],mLHScol1[3]};
	
	vector float auxLHS21 = {mLHScol2[0],mLHScol2[0],mLHScol2[0],mLHScol2[0]};
	vector float auxLHS22 = {mLHScol2[1],mLHScol2[1],mLHScol2[1],mLHScol2[1]};
	vector float auxLHS23 = {mLHScol2[2],mLHScol2[2],mLHScol2[2],mLHScol2[2]};
	vector float auxLHS24 = {mLHScol2[3],mLHScol2[3],mLHScol2[3],mLHScol2[3]};
	
	vector float auxLHS31 = {mLHScol3[0],mLHScol3[0],mLHScol3[0],mLHScol3[0]};
	vector float auxLHS32 = {mLHScol3[1],mLHScol3[1],mLHScol3[1],mLHScol3[1]};
	vector float auxLHS33 = {mLHScol3[2],mLHScol3[2],mLHScol3[2],mLHScol3[2]};
	vector float auxLHS34 = {mLHScol3[3],mLHScol3[3],mLHScol3[3],mLHScol3[3]};
	
	vector float auxLHS41 = {mLHScol4[0],mLHScol4[0],mLHScol4[0],mLHScol4[0]};
	vector float auxLHS42 = {mLHScol4[1],mLHScol4[1],mLHScol4[1],mLHScol4[1]};
	vector float auxLHS43 = {mLHScol4[2],mLHScol4[2],mLHScol4[2],mLHScol4[2]};
	vector float auxLHS44 = {mLHScol4[3],mLHScol4[3],mLHScol4[3],mLHScol4[3]};

 	//row 1 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS11,mRHSrow1),vec_mul(auxLHS12,mRHSrow2)),
	vec_add(vec_mul(auxLHS13,mRHSrow3),vec_mul(auxLHS14,mRHSrow4))),0,
	mResult
	);

	//row 2 
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS21,mRHSrow1),vec_mul(auxLHS22,mRHSrow2)),
	vec_add(vec_mul(auxLHS23,mRHSrow3),vec_mul(auxLHS24,mRHSrow4))),0,mResult+4
	);

	//row 3
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS31,mRHSrow1),vec_mul(auxLHS32,mRHSrow2)),
	vec_add(vec_mul(auxLHS33,mRHSrow3),vec_mul(auxLHS34,mRHSrow4))),0,mResult+8
	);

	//row 4
	vec_xst(
	vec_add(vec_add(vec_mul(auxLHS41,mRHSrow1),vec_mul(auxLHS42,mRHSrow2)),
	vec_add(vec_mul(auxLHS43,mRHSrow3),vec_mul(auxLHS44,mRHSrow4))),0,mResult+12
	);

}


//====================================================================================================
inline void mul4x4RowMajor(const double* mLHS, const double* mRHS, double* const mResult)
{
    __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41,
                    mLHScol12, mLHScol22, mLHScol32, mLHScol42,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42;

    //{ [a11 a12 a13 a14], [a21 a22 a23 a24], [a31 a32 a33 a34], [a41 a42 a43 a44]}

    const static __vector unsigned char GETCOL1 = { 0, 1, 2, 3, 4, 5, 6, 7,
                                                     16, 17, 18, 19, 20, 21, 22, 23};

    const static __vector unsigned char GETCOL2 = { 8, 9, 10, 11, 12, 13, 14, 15,
                                                     24, 25, 26, 27, 28, 29, 30, 31};

    __vector double mLHSaux1 = vec_xl(0, mLHS);
    __vector double mLHSaux2 = vec_xl(0, mLHS + 4);
    mLHScol11 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol21 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 2);
    mLHSaux2 = vec_xl(0, mLHS + 6);
    mLHScol31 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol41 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 8);
    mLHSaux2 = vec_xl(0, mLHS + 12);
    mLHScol12 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol22 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 10);
    mLHSaux2 = vec_xl(0, mLHS + 14);
    mLHScol32 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol42 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);
    //==================================================

    mRHSrow11 = vec_xl(0, mRHS);
    mRHSrow12 = vec_xl(0, mRHS + 2);

    mRHSrow21 = vec_xl(0, mRHS + 4);
    mRHSrow22 = vec_xl(0, mRHS + 6);

    mRHSrow31 = vec_xl(0, mRHS + 8);
    mRHSrow32 = vec_xl(0, mRHS + 10);

    mRHSrow41 = vec_xl(0, mRHS + 12);
    mRHSrow42 = vec_xl(0, mRHS + 14);
    //==================================================

    __vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
    __vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
    __vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
    __vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};

    __vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
    __vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
    __vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
    __vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};

    __vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
    __vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
    __vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
    __vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};

    __vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
    __vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
    __vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
    __vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
    //==================================================

    //building the first row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS21, vec_mul(mRHSrow11, vAuxLHS11)),
                    vec_madd(mRHSrow41, vAuxLHS41, vec_mul(mRHSrow31, vAuxLHS31)) ),
            0, mResult);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS21, vec_mul(mRHSrow12, vAuxLHS11)),
                    vec_madd(mRHSrow42, vAuxLHS41, vec_mul(mRHSrow32, vAuxLHS31)) ),
            0, mResult + 2);

    //building the second row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS22, vec_mul(mRHSrow11, vAuxLHS12)),
                    vec_madd(mRHSrow41, vAuxLHS42, vec_mul(mRHSrow31, vAuxLHS32)) ),
            0, mResult + 4);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS22, vec_mul(mRHSrow12, vAuxLHS12)),
                    vec_madd(mRHSrow42, vAuxLHS42, vec_mul(mRHSrow32, vAuxLHS32)) ),
            0, mResult + 6);

    //building the third row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS23, vec_mul(mRHSrow11, vAuxLHS13)),
                    vec_madd(mRHSrow41, vAuxLHS43, vec_mul(mRHSrow31, vAuxLHS33)) ),
            0, mResult + 8);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS23, vec_mul(mRHSrow12, vAuxLHS13)),
                    vec_madd(mRHSrow42, vAuxLHS43, vec_mul(mRHSrow32, vAuxLHS33)) ),
            0, mResult + 10);

    //building the fourth row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS24, vec_mul(mRHSrow11, vAuxLHS14)),
                    vec_madd(mRHSrow41, vAuxLHS44, vec_mul(mRHSrow31, vAuxLHS34)) ),
            0, mResult + 12);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS24, vec_mul(mRHSrow12, vAuxLHS14)),
                    vec_madd(mRHSrow42, vAuxLHS44, vec_mul(mRHSrow32, vAuxLHS34)) ),
            0, mResult + 14);
}
//====================================================================================================

inline void mul4x4ColMajor(const double* mLHS, const double* mRHS, double* const mResult)
{
    __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41,
                    mLHScol12, mLHScol22, mLHScol32, mLHScol42,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42;

    mLHScol11 = vec_xl(0, mLHS);
    mLHScol12 = vec_xl(0, mLHS + 2);

    mLHScol21 = vec_xl(0, mLHS + 4);
    mLHScol22 = vec_xl(0, mLHS + 6);

    mLHScol31 = vec_xl(0, mLHS + 8);
    mLHScol32 = vec_xl(0, mLHS + 10);

    mLHScol41 = vec_xl(0, mLHS + 12);
    mLHScol42 = vec_xl(0, mLHS + 14);
    //==================================================

    mRHSrow11 = vec_xl(0, mRHS);
    mRHSrow12 = vec_xl(0, mRHS + 2);

    mRHSrow21 = vec_xl(0, mRHS + 4);
    mRHSrow22 = vec_xl(0, mRHS + 6);

    mRHSrow31 = vec_xl(0, mRHS + 8);
    mRHSrow32 = vec_xl(0, mRHS + 10);

    mRHSrow41 = vec_xl(0, mRHS + 12);
    mRHSrow42 = vec_xl(0, mRHS + 14);
    //==================================================

    __vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
    __vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
    __vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
    __vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};

    __vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
    __vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
    __vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
    __vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};

    __vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
    __vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
    __vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
    __vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};

    __vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
    __vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
    __vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
    __vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
    //==================================================

    //building the first row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS21, vec_mul(mRHSrow11, vAuxLHS11)),
                    vec_madd(mRHSrow41, vAuxLHS41, vec_mul(mRHSrow31, vAuxLHS31)) ),
            0, mResult);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS21, vec_mul(mRHSrow12, vAuxLHS11)),
                    vec_madd(mRHSrow42, vAuxLHS41, vec_mul(mRHSrow32, vAuxLHS31)) ),
            0, mResult + 2);

    //building the second row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS22, vec_mul(mRHSrow11, vAuxLHS12)),
                    vec_madd(mRHSrow41, vAuxLHS42, vec_mul(mRHSrow31, vAuxLHS32)) ),
            0, mResult + 4);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS22, vec_mul(mRHSrow12, vAuxLHS12)),
                    vec_madd(mRHSrow42, vAuxLHS42, vec_mul(mRHSrow32, vAuxLHS32)) ),
            0, mResult + 6);

    //building the third row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS23, vec_mul(mRHSrow11, vAuxLHS13)),
                    vec_madd(mRHSrow41, vAuxLHS43, vec_mul(mRHSrow31, vAuxLHS33)) ),
            0, mResult + 8);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS23, vec_mul(mRHSrow12, vAuxLHS13)),
                    vec_madd(mRHSrow42, vAuxLHS43, vec_mul(mRHSrow32, vAuxLHS33)) ),
            0, mResult + 10);

    //building the fourth row of mResult
    vec_xst(vec_add(
                    vec_madd(mRHSrow21, vAuxLHS24, vec_mul(mRHSrow11, vAuxLHS14)),
                    vec_madd(mRHSrow41, vAuxLHS44, vec_mul(mRHSrow31, vAuxLHS34)) ),
            0, mResult + 12);
    vec_xst(vec_add(
                    vec_madd(mRHSrow22, vAuxLHS24, vec_mul(mRHSrow12, vAuxLHS14)),
                    vec_madd(mRHSrow42, vAuxLHS44, vec_mul(mRHSrow32, vAuxLHS34)) ),
            0, mResult + 14);
}
//====================================================================================================//


//====================================================================================================
inline void mul9x9RowMajor(const double* mLHS, const double* mRHS, double* const mResult)
{
    __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41, mLHScol51, mLHScol61, mLHScol71, mLHScol81, mLHScol91,
                    mLHScol12, mLHScol22, mLHScol32, mLHScol42, mLHScol52, mLHScol62, mLHScol72, mLHScol82, mLHScol92,
                    mLHScol13, mLHScol23, mLHScol33, mLHScol43, mLHScol53, mLHScol63, mLHScol73, mLHScol83, mLHScol93,
                    mLHScol14, mLHScol24, mLHScol34, mLHScol44, mLHScol54, mLHScol64, mLHScol74, mLHScol84, mLHScol94,
                    mLHScol15, mLHScol25, mLHScol35, mLHScol45, mLHScol55, mLHScol65, mLHScol75, mLHScol85, mLHScol95,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81, mRHSrow91,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82, mRHSrow92,
                    mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83, mRHSrow93,
                    mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84, mRHSrow94,
                    mRHSrow15, mRHSrow25, mRHSrow35, mRHSrow45, mRHSrow55, mRHSrow65, mRHSrow75, mRHSrow85, mRHSrow95;

    //{ [a11 a12 a13 a14 a15 a16 a17 a18 a19], [a21 a22 a23 a24 a25 a26 a27 a28 a29], [a31 a32 a33 a34 a35 a36 a37 a38 a39], [a41 a42 a43 a44 a45 a46 a47 a48 a49],
    //  [a51 a52 a53 a54 a55 a56 a57 a58 a59], [a61 a62 a63 a64 a65 a66 a67 a68 a69], [a71 a72 a73 a74 a75 a76 a77 a78 a79], [a81 a82 a83 a84 a85 a86 a87 a88 a89]}

    const static __vector unsigned char GETCOL1 = { 0, 1, 2, 3, 4, 5, 6, 7,
                                                     16, 17, 18, 19, 20, 21, 22, 23};

    const static __vector unsigned char GETCOL2 = { 8, 9, 10, 11, 12, 13, 14, 15,
                                                     24, 25, 26, 27, 28, 29, 30, 31};
    //==================================================//
    __vector double mLHSaux1 = vec_xl(0, mLHS);
    __vector double mLHSaux2 = vec_xl(0, mLHS + 9);
    mLHScol11 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol21 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 2);
    mLHSaux2 = vec_xl(0, mLHS + 11);
    mLHScol31 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol41 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 4);
    mLHSaux2 = vec_xl(0, mLHS + 13);
    mLHScol51 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol61 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 6);
    mLHSaux2 = vec_xl(0, mLHS + 15);
    mLHScol71 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol81 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHScol91[0] = mLHS[8];
    mLHScol91[1] = mLHS[17];

    //==================================================//
    mLHSaux1 = vec_xl(0, mLHS + 18);
    mLHSaux2 = vec_xl(0, mLHS + 27);
    mLHScol12 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol22 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 20);
    mLHSaux2 = vec_xl(0, mLHS + 29);
    mLHScol32 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol42 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 22);
    mLHSaux2 = vec_xl(0, mLHS + 31);
    mLHScol52 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol62 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 24);
    mLHSaux2 = vec_xl(0, mLHS + 33);
    mLHScol72 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol82 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHScol92[0] = mLHS[26];
    mLHScol92[1] = mLHS[35];

    //==================================================//
    mLHSaux1 = vec_xl(0, mLHS + 36);
    mLHSaux2 = vec_xl(0, mLHS + 45);
    mLHScol13 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol23 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 38);
    mLHSaux2 = vec_xl(0, mLHS + 47);
    mLHScol33 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol43 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 40);
    mLHSaux2 = vec_xl(0, mLHS + 49);
    mLHScol53 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol63 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 42);
    mLHSaux2 = vec_xl(0, mLHS + 51);
    mLHScol73 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol83 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHScol93[0] = mLHS[44];
    mLHScol93[1] = mLHS[53];

    //==================================================//
    mLHSaux1 = vec_xl(0, mLHS + 54);
    mLHSaux2 = vec_xl(0, mLHS + 63);
    mLHScol14 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol24 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 56);
    mLHSaux2 = vec_xl(0, mLHS + 65);
    mLHScol34 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol44 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 58);
    mLHSaux2 = vec_xl(0, mLHS + 67);
    mLHScol54 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol64 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHSaux1 = vec_xl(0, mLHS + 60);
    mLHSaux2 = vec_xl(0, mLHS + 69);
    mLHScol74 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
    mLHScol84 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

    mLHScol94[0] = mLHS[62];
    mLHScol94[1] = mLHS[71];

    //==================================================//
    mLHScol15[0] = mLHS[72];
    mLHScol15[1] = 0;

    mLHScol25[0] = mLHS[73];
    mLHScol25[1] = 0;

    mLHScol35[0] = mLHS[74];
    mLHScol35[1] = 0;

    mLHScol45[0] = mLHS[75];
    mLHScol45[1] = 0;

    mLHScol55[0] = mLHS[76];
    mLHScol55[1] = 0;

    mLHScol65[0] = mLHS[77];
    mLHScol65[1] = 0;

    mLHScol75[0] = mLHS[78];
    mLHScol75[1] = 0;

    mLHScol85[0] = mLHS[79];
    mLHScol85[1] = 0;

    mLHScol95[0] = mLHS[80];
    mLHScol95[1] = 0;

    mRHSrow11 = vec_xl(0, mRHS);
    mRHSrow12 = vec_xl(0, mRHS + 2);
    mRHSrow13 = vec_xl(0, mRHS + 4);
    mRHSrow14 = vec_xl(0, mRHS + 6);
    mRHSrow15[0] = mRHS[8];
    mRHSrow15[1] = 0;

    mRHSrow21 = vec_xl(0, mRHS + 9);
    mRHSrow22 = vec_xl(0, mRHS + 11);
    mRHSrow23 = vec_xl(0, mRHS + 13);
    mRHSrow24 = vec_xl(0, mRHS + 15);
    mRHSrow25[0] = mRHS[17];
    mRHSrow25[1] = 0;

    mRHSrow31 = vec_xl(0, mRHS + 18);
    mRHSrow32 = vec_xl(0, mRHS + 20);
    mRHSrow33 = vec_xl(0, mRHS + 22);
    mRHSrow34 = vec_xl(0, mRHS + 24);
    mRHSrow35[0] = mRHS[26];
    mRHSrow35[1] = 0;

    mRHSrow41 = vec_xl(0, mRHS + 27);
    mRHSrow42 = vec_xl(0, mRHS + 29);
    mRHSrow43 = vec_xl(0, mRHS + 31);
    mRHSrow44 = vec_xl(0, mRHS + 33);
    mRHSrow45[0] = mRHS[35];
    mRHSrow45[1] = 0;

    mRHSrow51 = vec_xl(0, mRHS + 36);
    mRHSrow52 = vec_xl(0, mRHS + 38);
    mRHSrow53 = vec_xl(0, mRHS + 40);
    mRHSrow54 = vec_xl(0, mRHS + 42);
    mRHSrow55[0] = mRHS[44];
    mRHSrow55[1] = 0;

    mRHSrow61 = vec_xl(0, mRHS + 45);
    mRHSrow62 = vec_xl(0, mRHS + 47);
    mRHSrow63 = vec_xl(0, mRHS + 49);
    mRHSrow64 = vec_xl(0, mRHS + 51);
    mRHSrow65[0] = mRHS[53];
    mRHSrow65[1] = 0;

    mRHSrow71 = vec_xl(0, mRHS + 54);
    mRHSrow72 = vec_xl(0, mRHS + 56);
    mRHSrow73 = vec_xl(0, mRHS + 58);
    mRHSrow74 = vec_xl(0, mRHS + 60);
    mRHSrow75[0] = mRHS[62];
    mRHSrow75[1] = 0;

    mRHSrow81 = vec_xl(0, mRHS + 63);
    mRHSrow82 = vec_xl(0, mRHS + 65);
    mRHSrow83 = vec_xl(0, mRHS + 67);
    mRHSrow84 = vec_xl(0, mRHS + 69);
    mRHSrow85[0] = mRHS[71];
    mRHSrow85[1] = 0;

    mRHSrow91 = vec_xl(0, mRHS + 72);
    mRHSrow92 = vec_xl(0, mRHS + 74);
    mRHSrow93 = vec_xl(0, mRHS + 76);
    mRHSrow94 = vec_xl(0, mRHS + 78);
    mRHSrow95[0] = mRHS[80];
    mRHSrow95[1] = 0;

    __vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
    __vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
    __vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
    __vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};
    __vector double vAuxLHS15 = {mLHScol13[0], mLHScol13[0]};
    __vector double vAuxLHS16 = {mLHScol13[1], mLHScol13[1]};
    __vector double vAuxLHS17 = {mLHScol14[0], mLHScol14[0]};
    __vector double vAuxLHS18 = {mLHScol14[1], mLHScol14[1]};
    __vector double vAuxLHS19 = {mLHScol15[0], mLHScol15[0]};

    __vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
    __vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
    __vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
    __vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};
    __vector double vAuxLHS25 = {mLHScol23[0], mLHScol23[0]};
    __vector double vAuxLHS26 = {mLHScol23[1], mLHScol23[1]};
    __vector double vAuxLHS27 = {mLHScol24[0], mLHScol24[0]};
    __vector double vAuxLHS28 = {mLHScol24[1], mLHScol24[1]};
    __vector double vAuxLHS29 = {mLHScol25[0], mLHScol25[0]};

    __vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
    __vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
    __vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
    __vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};
    __vector double vAuxLHS35 = {mLHScol33[0], mLHScol33[0]};
    __vector double vAuxLHS36 = {mLHScol33[1], mLHScol33[1]};
    __vector double vAuxLHS37 = {mLHScol34[0], mLHScol34[0]};
    __vector double vAuxLHS38 = {mLHScol34[1], mLHScol34[1]};
    __vector double vAuxLHS39 = {mLHScol35[0], mLHScol35[0]};

    __vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
    __vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
    __vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
    __vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
    __vector double vAuxLHS45 = {mLHScol43[0], mLHScol43[0]};
    __vector double vAuxLHS46 = {mLHScol43[1], mLHScol43[1]};
    __vector double vAuxLHS47 = {mLHScol44[0], mLHScol44[0]};
    __vector double vAuxLHS48 = {mLHScol44[1], mLHScol44[1]};
    __vector double vAuxLHS49 = {mLHScol45[0], mLHScol45[0]};

    __vector double vAuxLHS51 = {mLHScol51[0], mLHScol51[0]};
    __vector double vAuxLHS52 = {mLHScol51[1], mLHScol51[1]};
    __vector double vAuxLHS53 = {mLHScol52[0], mLHScol52[0]};
    __vector double vAuxLHS54 = {mLHScol52[1], mLHScol52[1]};
    __vector double vAuxLHS55 = {mLHScol53[0], mLHScol53[0]};
    __vector double vAuxLHS56 = {mLHScol53[1], mLHScol53[1]};
    __vector double vAuxLHS57 = {mLHScol54[0], mLHScol54[0]};
    __vector double vAuxLHS58 = {mLHScol54[1], mLHScol54[1]};
    __vector double vAuxLHS59 = {mLHScol55[0], mLHScol55[0]};

    __vector double vAuxLHS61 = {mLHScol61[0], mLHScol61[0]};
    __vector double vAuxLHS62 = {mLHScol61[1], mLHScol61[1]};
    __vector double vAuxLHS63 = {mLHScol62[0], mLHScol62[0]};
    __vector double vAuxLHS64 = {mLHScol62[1], mLHScol62[1]};
    __vector double vAuxLHS65 = {mLHScol63[0], mLHScol63[0]};
    __vector double vAuxLHS66 = {mLHScol63[1], mLHScol63[1]};
    __vector double vAuxLHS67 = {mLHScol64[0], mLHScol64[0]};
    __vector double vAuxLHS68 = {mLHScol64[1], mLHScol64[1]};
    __vector double vAuxLHS69 = {mLHScol65[0], mLHScol65[0]};

    __vector double vAuxLHS71 = {mLHScol71[0], mLHScol71[0]};
    __vector double vAuxLHS72 = {mLHScol71[1], mLHScol71[1]};
    __vector double vAuxLHS73 = {mLHScol72[0], mLHScol72[0]};
    __vector double vAuxLHS74 = {mLHScol72[1], mLHScol72[1]};
    __vector double vAuxLHS75 = {mLHScol73[0], mLHScol73[0]};
    __vector double vAuxLHS76 = {mLHScol73[1], mLHScol73[1]};
    __vector double vAuxLHS77 = {mLHScol74[0], mLHScol74[0]};
    __vector double vAuxLHS78 = {mLHScol74[1], mLHScol74[1]};
    __vector double vAuxLHS79 = {mLHScol75[0], mLHScol75[0]};

    __vector double vAuxLHS81 = {mLHScol81[0], mLHScol81[0]};
    __vector double vAuxLHS82 = {mLHScol81[1], mLHScol81[1]};
    __vector double vAuxLHS83 = {mLHScol82[0], mLHScol82[0]};
    __vector double vAuxLHS84 = {mLHScol82[1], mLHScol82[1]};
    __vector double vAuxLHS85 = {mLHScol83[0], mLHScol83[0]};
    __vector double vAuxLHS86 = {mLHScol83[1], mLHScol83[1]};
    __vector double vAuxLHS87 = {mLHScol84[0], mLHScol84[0]};
    __vector double vAuxLHS88 = {mLHScol84[1], mLHScol84[1]};
    __vector double vAuxLHS89 = {mLHScol85[0], mLHScol85[0]};

    __vector double vAuxLHS91 = {mLHScol91[0], mLHScol91[0]};
    __vector double vAuxLHS92 = {mLHScol91[1], mLHScol91[1]};
    __vector double vAuxLHS93 = {mLHScol92[0], mLHScol92[0]};
    __vector double vAuxLHS94 = {mLHScol92[1], mLHScol92[1]};
    __vector double vAuxLHS95 = {mLHScol93[0], mLHScol93[0]};
    __vector double vAuxLHS96 = {mLHScol93[1], mLHScol93[1]};
    __vector double vAuxLHS97 = {mLHScol94[0], mLHScol94[0]};
    __vector double vAuxLHS98 = {mLHScol94[1], mLHScol94[1]};
    __vector double vAuxLHS99 = {mLHScol95[0], mLHScol95[0]};

    //building the first row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS21, vec_mul(mRHSrow11, vAuxLHS11)),
                                    vec_madd(mRHSrow41, vAuxLHS41, vec_mul(mRHSrow31, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS61, vec_mul(mRHSrow51, vAuxLHS51)),
                                    vec_madd(mRHSrow81, vAuxLHS81, vec_mul(mRHSrow71, vAuxLHS71)) ) ) ),
            0, mResult);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS21, vec_mul(mRHSrow12, vAuxLHS11)),
                                    vec_madd(mRHSrow42, vAuxLHS41, vec_mul(mRHSrow32, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS61, vec_mul(mRHSrow52, vAuxLHS51)),
                                    vec_madd(mRHSrow82, vAuxLHS81, vec_mul(mRHSrow72, vAuxLHS71)) ) ) ),
            0, mResult + 2);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS21, vec_mul(mRHSrow13, vAuxLHS11)),
                                    vec_madd(mRHSrow43, vAuxLHS41, vec_mul(mRHSrow33, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS61, vec_mul(mRHSrow53, vAuxLHS51)),
                                    vec_madd(mRHSrow83, vAuxLHS81, vec_mul(mRHSrow73, vAuxLHS71)) ) ) ),
            0, mResult + 4);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS21, vec_mul(mRHSrow14, vAuxLHS11)),
                                    vec_madd(mRHSrow44, vAuxLHS41, vec_mul(mRHSrow34, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS61, vec_mul(mRHSrow54, vAuxLHS51)),
                                    vec_madd(mRHSrow84, vAuxLHS81, vec_mul(mRHSrow74, vAuxLHS71)) ) ) ),
            0, mResult + 6);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS21, vec_mul(mRHSrow15, vAuxLHS11)),
                                    vec_madd(mRHSrow45, vAuxLHS41, vec_mul(mRHSrow35, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS61, vec_mul(mRHSrow55, vAuxLHS51)),
                                    vec_madd(mRHSrow85, vAuxLHS81, vec_mul(mRHSrow75, vAuxLHS71)) ) ) ),
            0, mResult + 8);
    //building the second row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS22, vec_mul(mRHSrow11, vAuxLHS12)),
                                    vec_madd(mRHSrow41, vAuxLHS42, vec_mul(mRHSrow31, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS62, vec_mul(mRHSrow51, vAuxLHS52)),
                                    vec_madd(mRHSrow81, vAuxLHS82, vec_mul(mRHSrow71, vAuxLHS72)) ) ) ),
            0, mResult + 9);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS22, vec_mul(mRHSrow12, vAuxLHS12)),
                                    vec_madd(mRHSrow42, vAuxLHS42, vec_mul(mRHSrow32, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS62, vec_mul(mRHSrow52, vAuxLHS52)),
                                    vec_madd(mRHSrow82, vAuxLHS82, vec_mul(mRHSrow72, vAuxLHS72)) ) ) ),
            0, mResult + 11);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS22, vec_mul(mRHSrow13, vAuxLHS12)),
                                    vec_madd(mRHSrow43, vAuxLHS42, vec_mul(mRHSrow33, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS62, vec_mul(mRHSrow53, vAuxLHS52)),
                                    vec_madd(mRHSrow83, vAuxLHS82, vec_mul(mRHSrow73, vAuxLHS72)) ) ) ),
            0, mResult + 13);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS22, vec_mul(mRHSrow14, vAuxLHS12)),
                                    vec_madd(mRHSrow44, vAuxLHS42, vec_mul(mRHSrow34, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS62, vec_mul(mRHSrow54, vAuxLHS52)),
                                    vec_madd(mRHSrow84, vAuxLHS82, vec_mul(mRHSrow74, vAuxLHS72)) ) ) ),
            0, mResult + 15);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS22, vec_mul(mRHSrow15, vAuxLHS12)),
                                    vec_madd(mRHSrow45, vAuxLHS42, vec_mul(mRHSrow35, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS62, vec_mul(mRHSrow55, vAuxLHS52)),
                                    vec_madd(mRHSrow85, vAuxLHS82, vec_mul(mRHSrow75, vAuxLHS72)) ) ) ),
            0, mResult + 17);
    //building the third row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS23, vec_mul(mRHSrow11, vAuxLHS13)),
                                    vec_madd(mRHSrow41, vAuxLHS43, vec_mul(mRHSrow31, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS63, vec_mul(mRHSrow51, vAuxLHS53)),
                                    vec_madd(mRHSrow81, vAuxLHS83, vec_mul(mRHSrow71, vAuxLHS73)) ) ) ),
            0, mResult + 18);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS23, vec_mul(mRHSrow12, vAuxLHS13)),
                                    vec_madd(mRHSrow42, vAuxLHS43, vec_mul(mRHSrow32, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS63, vec_mul(mRHSrow52, vAuxLHS53)),
                                    vec_madd(mRHSrow82, vAuxLHS83, vec_mul(mRHSrow72, vAuxLHS73)) ) ) ),
            0, mResult + 20);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS23, vec_mul(mRHSrow13, vAuxLHS13)),
                                    vec_madd(mRHSrow43, vAuxLHS43, vec_mul(mRHSrow33, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS63, vec_mul(mRHSrow53, vAuxLHS53)),
                                    vec_madd(mRHSrow83, vAuxLHS83, vec_mul(mRHSrow73, vAuxLHS73)) ) ) ),
            0, mResult + 22);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS23, vec_mul(mRHSrow14, vAuxLHS13)),
                                    vec_madd(mRHSrow44, vAuxLHS43, vec_mul(mRHSrow34, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS63, vec_mul(mRHSrow54, vAuxLHS53)),
                                    vec_madd(mRHSrow84, vAuxLHS83, vec_mul(mRHSrow74, vAuxLHS73)) ) ) ),
            0, mResult + 24);
    vec_xst(vec_madd(mRHSrow95, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS23, vec_mul(mRHSrow15, vAuxLHS13)),
                                    vec_madd(mRHSrow45, vAuxLHS43, vec_mul(mRHSrow35, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS63, vec_mul(mRHSrow55, vAuxLHS53)),
                                    vec_madd(mRHSrow85, vAuxLHS83, vec_mul(mRHSrow75, vAuxLHS73)) ) ) ),
            0, mResult + 26);
    //building the fourth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS24, vec_mul(mRHSrow11, vAuxLHS14)),
                                    vec_madd(mRHSrow41, vAuxLHS44, vec_mul(mRHSrow31, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS64, vec_mul(mRHSrow51, vAuxLHS54)),
                                    vec_madd(mRHSrow81, vAuxLHS84, vec_mul(mRHSrow71, vAuxLHS74)) ) ) ),
            0, mResult + 27);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS24, vec_mul(mRHSrow12, vAuxLHS14)),
                                    vec_madd(mRHSrow42, vAuxLHS44, vec_mul(mRHSrow32, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS64, vec_mul(mRHSrow52, vAuxLHS54)),
                                    vec_madd(mRHSrow82, vAuxLHS84, vec_mul(mRHSrow72, vAuxLHS74)) ) ) ),
            0, mResult + 29);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS24, vec_mul(mRHSrow13, vAuxLHS14)),
                                    vec_madd(mRHSrow43, vAuxLHS44, vec_mul(mRHSrow33, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS64, vec_mul(mRHSrow53, vAuxLHS54)),
                                    vec_madd(mRHSrow83, vAuxLHS84, vec_mul(mRHSrow73, vAuxLHS74)) ) ) ),
            0, mResult + 31);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS24, vec_mul(mRHSrow14, vAuxLHS14)),
                                    vec_madd(mRHSrow44, vAuxLHS44, vec_mul(mRHSrow34, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS64, vec_mul(mRHSrow54, vAuxLHS54)),
                                    vec_madd(mRHSrow84, vAuxLHS84, vec_mul(mRHSrow74, vAuxLHS74)) ) ) ),
            0, mResult + 33);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS24, vec_mul(mRHSrow15, vAuxLHS14)),
                                    vec_madd(mRHSrow45, vAuxLHS44, vec_mul(mRHSrow35, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS64, vec_mul(mRHSrow55, vAuxLHS54)),
                                    vec_madd(mRHSrow85, vAuxLHS84, vec_mul(mRHSrow75, vAuxLHS74)) ) ) ),
            0, mResult + 35);
    //building the fifth row of mResult
    vec_xst(vec_madd(mRHSrow91, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS25, vec_mul(mRHSrow11, vAuxLHS15)),
                                    vec_madd(mRHSrow41, vAuxLHS45, vec_mul(mRHSrow31, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS65, vec_mul(mRHSrow51, vAuxLHS55)),
                                    vec_madd(mRHSrow81, vAuxLHS85, vec_mul(mRHSrow71, vAuxLHS75)) ) ) ),
            0, mResult + 36);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS25, vec_mul(mRHSrow12, vAuxLHS15)),
                                    vec_madd(mRHSrow42, vAuxLHS45, vec_mul(mRHSrow32, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS65, vec_mul(mRHSrow52, vAuxLHS55)),
                                    vec_madd(mRHSrow82, vAuxLHS85, vec_mul(mRHSrow72, vAuxLHS75)) ) ) ),
            0, mResult + 38);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS25, vec_mul(mRHSrow13, vAuxLHS15)),
                                    vec_madd(mRHSrow43, vAuxLHS45, vec_mul(mRHSrow33, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS65, vec_mul(mRHSrow53, vAuxLHS55)),
                                    vec_madd(mRHSrow83, vAuxLHS85, vec_mul(mRHSrow73, vAuxLHS75)) ) ) ),
            0, mResult + 40);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS25, vec_mul(mRHSrow14, vAuxLHS15)),
                                    vec_madd(mRHSrow44, vAuxLHS45, vec_mul(mRHSrow34, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS65, vec_mul(mRHSrow54, vAuxLHS55)),
                                    vec_madd(mRHSrow84, vAuxLHS85, vec_mul(mRHSrow74, vAuxLHS75)) ) ) ),
            0, mResult + 42);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS25, vec_mul(mRHSrow15, vAuxLHS15)),
                                    vec_madd(mRHSrow45, vAuxLHS45, vec_mul(mRHSrow35, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS65, vec_mul(mRHSrow55, vAuxLHS55)),
                                    vec_madd(mRHSrow85, vAuxLHS85, vec_mul(mRHSrow75, vAuxLHS75)) ) ) ),
            0, mResult + 44);
    //building the sixth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS26, vec_mul(mRHSrow11, vAuxLHS16)),
                                    vec_madd(mRHSrow41, vAuxLHS46, vec_mul(mRHSrow31, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS66, vec_mul(mRHSrow51, vAuxLHS56)),
                                    vec_madd(mRHSrow81, vAuxLHS86, vec_mul(mRHSrow71, vAuxLHS76)) ) ) ),
            0, mResult + 45);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS26, vec_mul(mRHSrow12, vAuxLHS16)),
                                    vec_madd(mRHSrow42, vAuxLHS46, vec_mul(mRHSrow32, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS66, vec_mul(mRHSrow52, vAuxLHS56)),
                                    vec_madd(mRHSrow82, vAuxLHS86, vec_mul(mRHSrow72, vAuxLHS76)) ) ) ),
            0, mResult + 47);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS26, vec_mul(mRHSrow13, vAuxLHS16)),
                                    vec_madd(mRHSrow43, vAuxLHS46, vec_mul(mRHSrow33, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS66, vec_mul(mRHSrow53, vAuxLHS56)),
                                    vec_madd(mRHSrow83, vAuxLHS86, vec_mul(mRHSrow73, vAuxLHS76)) ) ) ),
            0, mResult + 49);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS26, vec_mul(mRHSrow14, vAuxLHS16)),
                                    vec_madd(mRHSrow44, vAuxLHS46, vec_mul(mRHSrow34, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS66, vec_mul(mRHSrow54, vAuxLHS56)),
                                    vec_madd(mRHSrow84, vAuxLHS86, vec_mul(mRHSrow74, vAuxLHS76)) ) ) ),
            0, mResult + 51);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS26, vec_mul(mRHSrow15, vAuxLHS16)),
                                    vec_madd(mRHSrow45, vAuxLHS46, vec_mul(mRHSrow35, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS66, vec_mul(mRHSrow55, vAuxLHS56)),
                                    vec_madd(mRHSrow85, vAuxLHS86, vec_mul(mRHSrow75, vAuxLHS76)) ) ) ),
            0, mResult + 53);
    //building the seventh row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS27, vec_mul(mRHSrow11, vAuxLHS17)),
                                    vec_madd(mRHSrow41, vAuxLHS47, vec_mul(mRHSrow31, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS67, vec_mul(mRHSrow51, vAuxLHS57)),
                                    vec_madd(mRHSrow81, vAuxLHS87, vec_mul(mRHSrow71, vAuxLHS77)) ) ) ),
            0, mResult + 54);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS27, vec_mul(mRHSrow12, vAuxLHS17)),
                                    vec_madd(mRHSrow42, vAuxLHS47, vec_mul(mRHSrow32, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS67, vec_mul(mRHSrow52, vAuxLHS57)),
                                    vec_madd(mRHSrow82, vAuxLHS87, vec_mul(mRHSrow72, vAuxLHS77)) ) ) ),
            0, mResult + 56);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS27, vec_mul(mRHSrow13, vAuxLHS17)),
                                    vec_madd(mRHSrow43, vAuxLHS47, vec_mul(mRHSrow33, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS67, vec_mul(mRHSrow53, vAuxLHS57)),
                                    vec_madd(mRHSrow83, vAuxLHS87, vec_mul(mRHSrow73, vAuxLHS77)) ) ) ),
            0, mResult + 58);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS27, vec_mul(mRHSrow14, vAuxLHS17)),
                                    vec_madd(mRHSrow44, vAuxLHS47, vec_mul(mRHSrow34, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS67, vec_mul(mRHSrow54, vAuxLHS57)),
                                    vec_madd(mRHSrow84, vAuxLHS87, vec_mul(mRHSrow74, vAuxLHS77)) ) ) ),
            0, mResult + 60);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS27, vec_mul(mRHSrow15, vAuxLHS17)),
                                    vec_madd(mRHSrow45, vAuxLHS47, vec_mul(mRHSrow35, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS67, vec_mul(mRHSrow55, vAuxLHS57)),
                                    vec_madd(mRHSrow85, vAuxLHS87, vec_mul(mRHSrow75, vAuxLHS77)) ) ) ),
            0, mResult + 62);
    //building the eighth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS28, vec_mul(mRHSrow11, vAuxLHS18)),
                                    vec_madd(mRHSrow41, vAuxLHS48, vec_mul(mRHSrow31, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS68, vec_mul(mRHSrow51, vAuxLHS58)),
                                    vec_madd(mRHSrow81, vAuxLHS88, vec_mul(mRHSrow71, vAuxLHS78)) ) ) ),
            0, mResult + 63);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS28, vec_mul(mRHSrow12, vAuxLHS18)),
                                    vec_madd(mRHSrow42, vAuxLHS48, vec_mul(mRHSrow32, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS68, vec_mul(mRHSrow52, vAuxLHS58)),
                                    vec_madd(mRHSrow82, vAuxLHS88, vec_mul(mRHSrow72, vAuxLHS78)) ) ) ),
            0, mResult + 65);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS28, vec_mul(mRHSrow13, vAuxLHS18)),
                                    vec_madd(mRHSrow43, vAuxLHS48, vec_mul(mRHSrow33, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS68, vec_mul(mRHSrow53, vAuxLHS58)),
                                    vec_madd(mRHSrow83, vAuxLHS88, vec_mul(mRHSrow73, vAuxLHS78)) ) ) ),
            0, mResult + 67);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS28, vec_mul(mRHSrow14, vAuxLHS18)),
                                    vec_madd(mRHSrow44, vAuxLHS48, vec_mul(mRHSrow34, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS68, vec_mul(mRHSrow54, vAuxLHS58)),
                                    vec_madd(mRHSrow84, vAuxLHS88, vec_mul(mRHSrow74, vAuxLHS78)) ) ) ),
            0, mResult + 69);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS28, vec_mul(mRHSrow15, vAuxLHS18)),
                                    vec_madd(mRHSrow45, vAuxLHS48, vec_mul(mRHSrow35, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS68, vec_mul(mRHSrow55, vAuxLHS58)),
                                    vec_madd(mRHSrow85, vAuxLHS88, vec_mul(mRHSrow75, vAuxLHS78)) ) ) ),
            0, mResult + 71);
    //building the ninth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS29, vec_mul(mRHSrow11, vAuxLHS19)),
                                    vec_madd(mRHSrow41, vAuxLHS49, vec_mul(mRHSrow31, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS69, vec_mul(mRHSrow51, vAuxLHS59)),
                                    vec_madd(mRHSrow81, vAuxLHS89, vec_mul(mRHSrow71, vAuxLHS79)) ) ) ),
            0, mResult + 72);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS29, vec_mul(mRHSrow12, vAuxLHS19)),
                                    vec_madd(mRHSrow42, vAuxLHS49, vec_mul(mRHSrow32, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS69, vec_mul(mRHSrow52, vAuxLHS59)),
                                    vec_madd(mRHSrow82, vAuxLHS89, vec_mul(mRHSrow72, vAuxLHS79)) ) ) ),
            0, mResult + 74);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS29, vec_mul(mRHSrow13, vAuxLHS19)),
                                    vec_madd(mRHSrow43, vAuxLHS49, vec_mul(mRHSrow33, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS69, vec_mul(mRHSrow53, vAuxLHS59)),
                                    vec_madd(mRHSrow83, vAuxLHS89, vec_mul(mRHSrow73, vAuxLHS79)) ) ) ),
            0, mResult + 76);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS29, vec_mul(mRHSrow14, vAuxLHS19)),
                                    vec_madd(mRHSrow44, vAuxLHS49, vec_mul(mRHSrow34, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS69, vec_mul(mRHSrow54, vAuxLHS59)),
                                    vec_madd(mRHSrow84, vAuxLHS89, vec_mul(mRHSrow74, vAuxLHS79)) ) ) ),
            0, mResult + 78);
    __vector double mResultLastElem =
          vec_madd( mRHSrow95, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS29, vec_mul(mRHSrow15, vAuxLHS19)),
                                    vec_madd(mRHSrow45, vAuxLHS49, vec_mul(mRHSrow35, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS69, vec_mul(mRHSrow55, vAuxLHS59)),
                                    vec_madd(mRHSrow85, vAuxLHS89, vec_mul(mRHSrow75, vAuxLHS79)) ) ) );
      mResult[80] = mResultLastElem[0];

}
//====================================================================================================

inline void mul9x9ColMajor(const double* mLHS, const double* mRHS, double* const mResult)
{
    __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41, mLHScol51, mLHScol61, mLHScol71, mLHScol81, mLHScol91,
                    mLHScol12, mLHScol22, mLHScol32, mLHScol42, mLHScol52, mLHScol62, mLHScol72, mLHScol82, mLHScol92,
                    mLHScol13, mLHScol23, mLHScol33, mLHScol43, mLHScol53, mLHScol63, mLHScol73, mLHScol83, mLHScol93,
                    mLHScol14, mLHScol24, mLHScol34, mLHScol44, mLHScol54, mLHScol64, mLHScol74, mLHScol84, mLHScol94,
                    mLHScol15, mLHScol25, mLHScol35, mLHScol45, mLHScol55, mLHScol65, mLHScol75, mLHScol85, mLHScol95,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81, mRHSrow91,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82, mRHSrow92,
                    mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83, mRHSrow93,
                    mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84, mRHSrow94,
                    mRHSrow15, mRHSrow25, mRHSrow35, mRHSrow45, mRHSrow55, mRHSrow65, mRHSrow75, mRHSrow85, mRHSrow95;

    mLHScol11 = vec_xl(0, mLHS);
    mLHScol12 = vec_xl(0, mLHS + 2);
    mLHScol13 = vec_xl(0, mLHS + 4);
    mLHScol14 = vec_xl(0, mLHS + 6);
    mLHScol15[0] = mLHS[8];
    mLHScol15[1] = 0;

    mLHScol21 = vec_xl(0, mLHS + 9);
    mLHScol22 = vec_xl(0, mLHS + 11);
    mLHScol23 = vec_xl(0, mLHS + 13);
    mLHScol24 = vec_xl(0, mLHS + 15);
    mLHScol25[0] = mLHS[17];
    mLHScol25[1] = 0;

    mLHScol31 = vec_xl(0, mLHS + 18);
    mLHScol32 = vec_xl(0, mLHS + 20);
    mLHScol33 = vec_xl(0, mLHS + 22);
    mLHScol34 = vec_xl(0, mLHS + 24);
    mLHScol35[0] = mLHS[26];
    mLHScol35[1] = 0;

    mLHScol41 = vec_xl(0, mLHS + 27);
    mLHScol42 = vec_xl(0, mLHS + 29);
    mLHScol43 = vec_xl(0, mLHS + 31);
    mLHScol44 = vec_xl(0, mLHS + 33);
    mLHScol45[0] = mLHS[35];
    mLHScol45[1] = 0;

    mLHScol51 = vec_xl(0, mLHS + 36);
    mLHScol52 = vec_xl(0, mLHS + 38);
    mLHScol53 = vec_xl(0, mLHS + 40);
    mLHScol54 = vec_xl(0, mLHS + 42);
    mLHScol55[0] = mLHS[44];
    mLHScol55[1] = 0;

    mLHScol61 = vec_xl(0, mLHS + 45);
    mLHScol62 = vec_xl(0, mLHS + 47);
    mLHScol63 = vec_xl(0, mLHS + 49);
    mLHScol64 = vec_xl(0, mLHS + 51);
    mLHScol65[0] = mLHS[53];
    mLHScol65[1] = 0;

    mLHScol71 = vec_xl(0, mLHS + 54);
    mLHScol72 = vec_xl(0, mLHS + 56);
    mLHScol73 = vec_xl(0, mLHS + 58);
    mLHScol74 = vec_xl(0, mLHS + 60);
    mLHScol75[0] = mLHS[62];
    mLHScol75[1] = 0;

    mLHScol81 = vec_xl(0, mLHS + 63);
    mLHScol82 = vec_xl(0, mLHS + 65);
    mLHScol83 = vec_xl(0, mLHS + 67);
    mLHScol84 = vec_xl(0, mLHS + 69);
    mLHScol85[0] = mLHS[71];
    mLHScol85[1] = 0;

    mLHScol91 = vec_xl(0, mLHS + 72);
    mLHScol92 = vec_xl(0, mLHS + 74);
    mLHScol93 = vec_xl(0, mLHS + 76);
    mLHScol94 = vec_xl(0, mLHS + 78);
    mLHScol95[0] = mLHS[80];
    mLHScol95[1] = 0;

    mRHSrow11 = vec_xl(0, mRHS);
    mRHSrow12 = vec_xl(0, mRHS + 2);
    mRHSrow13 = vec_xl(0, mRHS + 4);
    mRHSrow14 = vec_xl(0, mRHS + 6);
    mRHSrow15[0] = mRHS[8];
    mRHSrow15[1] = 0;

    mRHSrow21 = vec_xl(0, mRHS + 9);
    mRHSrow22 = vec_xl(0, mRHS + 11);
    mRHSrow23 = vec_xl(0, mRHS + 13);
    mRHSrow24 = vec_xl(0, mRHS + 15);
    mRHSrow25[0] = mRHS[17];
    mRHSrow25[1] = 0;

    mRHSrow31 = vec_xl(0, mRHS + 18);
    mRHSrow32 = vec_xl(0, mRHS + 20);
    mRHSrow33 = vec_xl(0, mRHS + 22);
    mRHSrow34 = vec_xl(0, mRHS + 24);
    mRHSrow35[0] = mRHS[26];
    mRHSrow35[1] = 0;

    mRHSrow41 = vec_xl(0, mRHS + 27);
    mRHSrow42 = vec_xl(0, mRHS + 29);
    mRHSrow43 = vec_xl(0, mRHS + 31);
    mRHSrow44 = vec_xl(0, mRHS + 33);
    mRHSrow45[0] = mRHS[35];
    mRHSrow45[1] = 0;

    mRHSrow51 = vec_xl(0, mRHS + 36);
    mRHSrow52 = vec_xl(0, mRHS + 38);
    mRHSrow53 = vec_xl(0, mRHS + 40);
    mRHSrow54 = vec_xl(0, mRHS + 42);
    mRHSrow55[0] = mRHS[44];
    mRHSrow55[1] = 0;

    mRHSrow61 = vec_xl(0, mRHS + 45);
    mRHSrow62 = vec_xl(0, mRHS + 47);
    mRHSrow63 = vec_xl(0, mRHS + 49);
    mRHSrow64 = vec_xl(0, mRHS + 51);
    mRHSrow65[0] = mRHS[53];
    mRHSrow65[1] = 0;

    mRHSrow71 = vec_xl(0, mRHS + 54);
    mRHSrow72 = vec_xl(0, mRHS + 56);
    mRHSrow73 = vec_xl(0, mRHS + 58);
    mRHSrow74 = vec_xl(0, mRHS + 60);
    mRHSrow75[0] = mRHS[62];
    mRHSrow75[1] = 0;

    mRHSrow81 = vec_xl(0, mRHS + 63);
    mRHSrow82 = vec_xl(0, mRHS + 65);
    mRHSrow83 = vec_xl(0, mRHS + 67);
    mRHSrow84 = vec_xl(0, mRHS + 69);
    mRHSrow85[0] = mRHS[71];
    mRHSrow85[1] = 0;

    mRHSrow91 = vec_xl(0, mRHS + 72);
    mRHSrow92 = vec_xl(0, mRHS + 74);
    mRHSrow93 = vec_xl(0, mRHS + 76);
    mRHSrow94 = vec_xl(0, mRHS + 78);
    mRHSrow95[0] = mRHS[80];
    mRHSrow95[1] = 0;

    __vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
    __vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
    __vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
    __vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};
    __vector double vAuxLHS15 = {mLHScol13[0], mLHScol13[0]};
    __vector double vAuxLHS16 = {mLHScol13[1], mLHScol13[1]};
    __vector double vAuxLHS17 = {mLHScol14[0], mLHScol14[0]};
    __vector double vAuxLHS18 = {mLHScol14[1], mLHScol14[1]};
    __vector double vAuxLHS19 = {mLHScol15[0], mLHScol15[0]};

    __vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
    __vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
    __vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
    __vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};
    __vector double vAuxLHS25 = {mLHScol23[0], mLHScol23[0]};
    __vector double vAuxLHS26 = {mLHScol23[1], mLHScol23[1]};
    __vector double vAuxLHS27 = {mLHScol24[0], mLHScol24[0]};
    __vector double vAuxLHS28 = {mLHScol24[1], mLHScol24[1]};
    __vector double vAuxLHS29 = {mLHScol25[0], mLHScol25[0]};

    __vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
    __vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
    __vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
    __vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};
    __vector double vAuxLHS35 = {mLHScol33[0], mLHScol33[0]};
    __vector double vAuxLHS36 = {mLHScol33[1], mLHScol33[1]};
    __vector double vAuxLHS37 = {mLHScol34[0], mLHScol34[0]};
    __vector double vAuxLHS38 = {mLHScol34[1], mLHScol34[1]};
    __vector double vAuxLHS39 = {mLHScol35[0], mLHScol35[0]};

    __vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
    __vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
    __vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
    __vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
    __vector double vAuxLHS45 = {mLHScol43[0], mLHScol43[0]};
    __vector double vAuxLHS46 = {mLHScol43[1], mLHScol43[1]};
    __vector double vAuxLHS47 = {mLHScol44[0], mLHScol44[0]};
    __vector double vAuxLHS48 = {mLHScol44[1], mLHScol44[1]};
    __vector double vAuxLHS49 = {mLHScol45[0], mLHScol45[0]};

    __vector double vAuxLHS51 = {mLHScol51[0], mLHScol51[0]};
    __vector double vAuxLHS52 = {mLHScol51[1], mLHScol51[1]};
    __vector double vAuxLHS53 = {mLHScol52[0], mLHScol52[0]};
    __vector double vAuxLHS54 = {mLHScol52[1], mLHScol52[1]};
    __vector double vAuxLHS55 = {mLHScol53[0], mLHScol53[0]};
    __vector double vAuxLHS56 = {mLHScol53[1], mLHScol53[1]};
    __vector double vAuxLHS57 = {mLHScol54[0], mLHScol54[0]};
    __vector double vAuxLHS58 = {mLHScol54[1], mLHScol54[1]};
    __vector double vAuxLHS59 = {mLHScol55[0], mLHScol55[0]};

    __vector double vAuxLHS61 = {mLHScol61[0], mLHScol61[0]};
    __vector double vAuxLHS62 = {mLHScol61[1], mLHScol61[1]};
    __vector double vAuxLHS63 = {mLHScol62[0], mLHScol62[0]};
    __vector double vAuxLHS64 = {mLHScol62[1], mLHScol62[1]};
    __vector double vAuxLHS65 = {mLHScol63[0], mLHScol63[0]};
    __vector double vAuxLHS66 = {mLHScol63[1], mLHScol63[1]};
    __vector double vAuxLHS67 = {mLHScol64[0], mLHScol64[0]};
    __vector double vAuxLHS68 = {mLHScol64[1], mLHScol64[1]};
    __vector double vAuxLHS69 = {mLHScol65[0], mLHScol65[0]};

    __vector double vAuxLHS71 = {mLHScol71[0], mLHScol71[0]};
    __vector double vAuxLHS72 = {mLHScol71[1], mLHScol71[1]};
    __vector double vAuxLHS73 = {mLHScol72[0], mLHScol72[0]};
    __vector double vAuxLHS74 = {mLHScol72[1], mLHScol72[1]};
    __vector double vAuxLHS75 = {mLHScol73[0], mLHScol73[0]};
    __vector double vAuxLHS76 = {mLHScol73[1], mLHScol73[1]};
    __vector double vAuxLHS77 = {mLHScol74[0], mLHScol74[0]};
    __vector double vAuxLHS78 = {mLHScol74[1], mLHScol74[1]};
    __vector double vAuxLHS79 = {mLHScol75[0], mLHScol75[0]};

    __vector double vAuxLHS81 = {mLHScol81[0], mLHScol81[0]};
    __vector double vAuxLHS82 = {mLHScol81[1], mLHScol81[1]};
    __vector double vAuxLHS83 = {mLHScol82[0], mLHScol82[0]};
    __vector double vAuxLHS84 = {mLHScol82[1], mLHScol82[1]};
    __vector double vAuxLHS85 = {mLHScol83[0], mLHScol83[0]};
    __vector double vAuxLHS86 = {mLHScol83[1], mLHScol83[1]};
    __vector double vAuxLHS87 = {mLHScol84[0], mLHScol84[0]};
    __vector double vAuxLHS88 = {mLHScol84[1], mLHScol84[1]};
    __vector double vAuxLHS89 = {mLHScol85[0], mLHScol85[0]};

    __vector double vAuxLHS91 = {mLHScol91[0], mLHScol91[0]};
    __vector double vAuxLHS92 = {mLHScol91[1], mLHScol91[1]};
    __vector double vAuxLHS93 = {mLHScol92[0], mLHScol92[0]};
    __vector double vAuxLHS94 = {mLHScol92[1], mLHScol92[1]};
    __vector double vAuxLHS95 = {mLHScol93[0], mLHScol93[0]};
    __vector double vAuxLHS96 = {mLHScol93[1], mLHScol93[1]};
    __vector double vAuxLHS97 = {mLHScol94[0], mLHScol94[0]};
    __vector double vAuxLHS98 = {mLHScol94[1], mLHScol94[1]};
    __vector double vAuxLHS99 = {mLHScol95[0], mLHScol95[0]};

    //building the first row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS21, vec_mul(mRHSrow11, vAuxLHS11)),
                                    vec_madd(mRHSrow41, vAuxLHS41, vec_mul(mRHSrow31, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS61, vec_mul(mRHSrow51, vAuxLHS51)),
                                    vec_madd(mRHSrow81, vAuxLHS81, vec_mul(mRHSrow71, vAuxLHS71)) ) ) ),
            0, mResult);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS21, vec_mul(mRHSrow12, vAuxLHS11)),
                                    vec_madd(mRHSrow42, vAuxLHS41, vec_mul(mRHSrow32, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS61, vec_mul(mRHSrow52, vAuxLHS51)),
                                    vec_madd(mRHSrow82, vAuxLHS81, vec_mul(mRHSrow72, vAuxLHS71)) ) ) ),
            0, mResult + 2);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS21, vec_mul(mRHSrow13, vAuxLHS11)),
                                    vec_madd(mRHSrow43, vAuxLHS41, vec_mul(mRHSrow33, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS61, vec_mul(mRHSrow53, vAuxLHS51)),
                                    vec_madd(mRHSrow83, vAuxLHS81, vec_mul(mRHSrow73, vAuxLHS71)) ) ) ),
            0, mResult + 4);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS21, vec_mul(mRHSrow14, vAuxLHS11)),
                                    vec_madd(mRHSrow44, vAuxLHS41, vec_mul(mRHSrow34, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS61, vec_mul(mRHSrow54, vAuxLHS51)),
                                    vec_madd(mRHSrow84, vAuxLHS81, vec_mul(mRHSrow74, vAuxLHS71)) ) ) ),
            0, mResult + 6);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS91,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS21, vec_mul(mRHSrow15, vAuxLHS11)),
                                    vec_madd(mRHSrow45, vAuxLHS41, vec_mul(mRHSrow35, vAuxLHS31)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS61, vec_mul(mRHSrow55, vAuxLHS51)),
                                    vec_madd(mRHSrow85, vAuxLHS81, vec_mul(mRHSrow75, vAuxLHS71)) ) ) ),
            0, mResult + 8);
    //building the second row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS22, vec_mul(mRHSrow11, vAuxLHS12)),
                                    vec_madd(mRHSrow41, vAuxLHS42, vec_mul(mRHSrow31, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS62, vec_mul(mRHSrow51, vAuxLHS52)),
                                    vec_madd(mRHSrow81, vAuxLHS82, vec_mul(mRHSrow71, vAuxLHS72)) ) ) ),
            0, mResult + 9);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS22, vec_mul(mRHSrow12, vAuxLHS12)),
                                    vec_madd(mRHSrow42, vAuxLHS42, vec_mul(mRHSrow32, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS62, vec_mul(mRHSrow52, vAuxLHS52)),
                                    vec_madd(mRHSrow82, vAuxLHS82, vec_mul(mRHSrow72, vAuxLHS72)) ) ) ),
            0, mResult + 11);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS22, vec_mul(mRHSrow13, vAuxLHS12)),
                                    vec_madd(mRHSrow43, vAuxLHS42, vec_mul(mRHSrow33, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS62, vec_mul(mRHSrow53, vAuxLHS52)),
                                    vec_madd(mRHSrow83, vAuxLHS82, vec_mul(mRHSrow73, vAuxLHS72)) ) ) ),
            0, mResult + 13);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS22, vec_mul(mRHSrow14, vAuxLHS12)),
                                    vec_madd(mRHSrow44, vAuxLHS42, vec_mul(mRHSrow34, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS62, vec_mul(mRHSrow54, vAuxLHS52)),
                                    vec_madd(mRHSrow84, vAuxLHS82, vec_mul(mRHSrow74, vAuxLHS72)) ) ) ),
            0, mResult + 15);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS92,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS22, vec_mul(mRHSrow15, vAuxLHS12)),
                                    vec_madd(mRHSrow45, vAuxLHS42, vec_mul(mRHSrow35, vAuxLHS32)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS62, vec_mul(mRHSrow55, vAuxLHS52)),
                                    vec_madd(mRHSrow85, vAuxLHS82, vec_mul(mRHSrow75, vAuxLHS72)) ) ) ),
            0, mResult + 17);
    //building the third row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS23, vec_mul(mRHSrow11, vAuxLHS13)),
                                    vec_madd(mRHSrow41, vAuxLHS43, vec_mul(mRHSrow31, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS63, vec_mul(mRHSrow51, vAuxLHS53)),
                                    vec_madd(mRHSrow81, vAuxLHS83, vec_mul(mRHSrow71, vAuxLHS73)) ) ) ),
            0, mResult + 18);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS23, vec_mul(mRHSrow12, vAuxLHS13)),
                                    vec_madd(mRHSrow42, vAuxLHS43, vec_mul(mRHSrow32, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS63, vec_mul(mRHSrow52, vAuxLHS53)),
                                    vec_madd(mRHSrow82, vAuxLHS83, vec_mul(mRHSrow72, vAuxLHS73)) ) ) ),
            0, mResult + 20);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS23, vec_mul(mRHSrow13, vAuxLHS13)),
                                    vec_madd(mRHSrow43, vAuxLHS43, vec_mul(mRHSrow33, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS63, vec_mul(mRHSrow53, vAuxLHS53)),
                                    vec_madd(mRHSrow83, vAuxLHS83, vec_mul(mRHSrow73, vAuxLHS73)) ) ) ),
            0, mResult + 22);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS23, vec_mul(mRHSrow14, vAuxLHS13)),
                                    vec_madd(mRHSrow44, vAuxLHS43, vec_mul(mRHSrow34, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS63, vec_mul(mRHSrow54, vAuxLHS53)),
                                    vec_madd(mRHSrow84, vAuxLHS83, vec_mul(mRHSrow74, vAuxLHS73)) ) ) ),
            0, mResult + 24);
    vec_xst(vec_madd(mRHSrow95, vAuxLHS93,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS23, vec_mul(mRHSrow15, vAuxLHS13)),
                                    vec_madd(mRHSrow45, vAuxLHS43, vec_mul(mRHSrow35, vAuxLHS33)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS63, vec_mul(mRHSrow55, vAuxLHS53)),
                                    vec_madd(mRHSrow85, vAuxLHS83, vec_mul(mRHSrow75, vAuxLHS73)) ) ) ),
            0, mResult + 26);
    //building the fourth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS24, vec_mul(mRHSrow11, vAuxLHS14)),
                                    vec_madd(mRHSrow41, vAuxLHS44, vec_mul(mRHSrow31, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS64, vec_mul(mRHSrow51, vAuxLHS54)),
                                    vec_madd(mRHSrow81, vAuxLHS84, vec_mul(mRHSrow71, vAuxLHS74)) ) ) ),
            0, mResult + 27);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS24, vec_mul(mRHSrow12, vAuxLHS14)),
                                    vec_madd(mRHSrow42, vAuxLHS44, vec_mul(mRHSrow32, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS64, vec_mul(mRHSrow52, vAuxLHS54)),
                                    vec_madd(mRHSrow82, vAuxLHS84, vec_mul(mRHSrow72, vAuxLHS74)) ) ) ),
            0, mResult + 29);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS24, vec_mul(mRHSrow13, vAuxLHS14)),
                                    vec_madd(mRHSrow43, vAuxLHS44, vec_mul(mRHSrow33, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS64, vec_mul(mRHSrow53, vAuxLHS54)),
                                    vec_madd(mRHSrow83, vAuxLHS84, vec_mul(mRHSrow73, vAuxLHS74)) ) ) ),
            0, mResult + 31);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS24, vec_mul(mRHSrow14, vAuxLHS14)),
                                    vec_madd(mRHSrow44, vAuxLHS44, vec_mul(mRHSrow34, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS64, vec_mul(mRHSrow54, vAuxLHS54)),
                                    vec_madd(mRHSrow84, vAuxLHS84, vec_mul(mRHSrow74, vAuxLHS74)) ) ) ),
            0, mResult + 33);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS94,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS24, vec_mul(mRHSrow15, vAuxLHS14)),
                                    vec_madd(mRHSrow45, vAuxLHS44, vec_mul(mRHSrow35, vAuxLHS34)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS64, vec_mul(mRHSrow55, vAuxLHS54)),
                                    vec_madd(mRHSrow85, vAuxLHS84, vec_mul(mRHSrow75, vAuxLHS74)) ) ) ),
            0, mResult + 35);
    //building the fifth row of mResult
    vec_xst(vec_madd(mRHSrow91, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS25, vec_mul(mRHSrow11, vAuxLHS15)),
                                    vec_madd(mRHSrow41, vAuxLHS45, vec_mul(mRHSrow31, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS65, vec_mul(mRHSrow51, vAuxLHS55)),
                                    vec_madd(mRHSrow81, vAuxLHS85, vec_mul(mRHSrow71, vAuxLHS75)) ) ) ),
            0, mResult + 36);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS25, vec_mul(mRHSrow12, vAuxLHS15)),
                                    vec_madd(mRHSrow42, vAuxLHS45, vec_mul(mRHSrow32, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS65, vec_mul(mRHSrow52, vAuxLHS55)),
                                    vec_madd(mRHSrow82, vAuxLHS85, vec_mul(mRHSrow72, vAuxLHS75)) ) ) ),
            0, mResult + 38);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS25, vec_mul(mRHSrow13, vAuxLHS15)),
                                    vec_madd(mRHSrow43, vAuxLHS45, vec_mul(mRHSrow33, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS65, vec_mul(mRHSrow53, vAuxLHS55)),
                                    vec_madd(mRHSrow83, vAuxLHS85, vec_mul(mRHSrow73, vAuxLHS75)) ) ) ),
            0, mResult + 40);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS25, vec_mul(mRHSrow14, vAuxLHS15)),
                                    vec_madd(mRHSrow44, vAuxLHS45, vec_mul(mRHSrow34, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS65, vec_mul(mRHSrow54, vAuxLHS55)),
                                    vec_madd(mRHSrow84, vAuxLHS85, vec_mul(mRHSrow74, vAuxLHS75)) ) ) ),
            0, mResult + 42);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS95,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS25, vec_mul(mRHSrow15, vAuxLHS15)),
                                    vec_madd(mRHSrow45, vAuxLHS45, vec_mul(mRHSrow35, vAuxLHS35)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS65, vec_mul(mRHSrow55, vAuxLHS55)),
                                    vec_madd(mRHSrow85, vAuxLHS85, vec_mul(mRHSrow75, vAuxLHS75)) ) ) ),
            0, mResult + 44);
    //building the sixth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS26, vec_mul(mRHSrow11, vAuxLHS16)),
                                    vec_madd(mRHSrow41, vAuxLHS46, vec_mul(mRHSrow31, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS66, vec_mul(mRHSrow51, vAuxLHS56)),
                                    vec_madd(mRHSrow81, vAuxLHS86, vec_mul(mRHSrow71, vAuxLHS76)) ) ) ),
            0, mResult + 45);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS26, vec_mul(mRHSrow12, vAuxLHS16)),
                                    vec_madd(mRHSrow42, vAuxLHS46, vec_mul(mRHSrow32, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS66, vec_mul(mRHSrow52, vAuxLHS56)),
                                    vec_madd(mRHSrow82, vAuxLHS86, vec_mul(mRHSrow72, vAuxLHS76)) ) ) ),
            0, mResult + 47);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS26, vec_mul(mRHSrow13, vAuxLHS16)),
                                    vec_madd(mRHSrow43, vAuxLHS46, vec_mul(mRHSrow33, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS66, vec_mul(mRHSrow53, vAuxLHS56)),
                                    vec_madd(mRHSrow83, vAuxLHS86, vec_mul(mRHSrow73, vAuxLHS76)) ) ) ),
            0, mResult + 49);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS26, vec_mul(mRHSrow14, vAuxLHS16)),
                                    vec_madd(mRHSrow44, vAuxLHS46, vec_mul(mRHSrow34, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS66, vec_mul(mRHSrow54, vAuxLHS56)),
                                    vec_madd(mRHSrow84, vAuxLHS86, vec_mul(mRHSrow74, vAuxLHS76)) ) ) ),
            0, mResult + 51);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS96,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS26, vec_mul(mRHSrow15, vAuxLHS16)),
                                    vec_madd(mRHSrow45, vAuxLHS46, vec_mul(mRHSrow35, vAuxLHS36)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS66, vec_mul(mRHSrow55, vAuxLHS56)),
                                    vec_madd(mRHSrow85, vAuxLHS86, vec_mul(mRHSrow75, vAuxLHS76)) ) ) ),
            0, mResult + 53);
    //building the seventh row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS27, vec_mul(mRHSrow11, vAuxLHS17)),
                                    vec_madd(mRHSrow41, vAuxLHS47, vec_mul(mRHSrow31, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS67, vec_mul(mRHSrow51, vAuxLHS57)),
                                    vec_madd(mRHSrow81, vAuxLHS87, vec_mul(mRHSrow71, vAuxLHS77)) ) ) ),
            0, mResult + 54);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS27, vec_mul(mRHSrow12, vAuxLHS17)),
                                    vec_madd(mRHSrow42, vAuxLHS47, vec_mul(mRHSrow32, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS67, vec_mul(mRHSrow52, vAuxLHS57)),
                                    vec_madd(mRHSrow82, vAuxLHS87, vec_mul(mRHSrow72, vAuxLHS77)) ) ) ),
            0, mResult + 56);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS27, vec_mul(mRHSrow13, vAuxLHS17)),
                                    vec_madd(mRHSrow43, vAuxLHS47, vec_mul(mRHSrow33, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS67, vec_mul(mRHSrow53, vAuxLHS57)),
                                    vec_madd(mRHSrow83, vAuxLHS87, vec_mul(mRHSrow73, vAuxLHS77)) ) ) ),
            0, mResult + 58);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS27, vec_mul(mRHSrow14, vAuxLHS17)),
                                    vec_madd(mRHSrow44, vAuxLHS47, vec_mul(mRHSrow34, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS67, vec_mul(mRHSrow54, vAuxLHS57)),
                                    vec_madd(mRHSrow84, vAuxLHS87, vec_mul(mRHSrow74, vAuxLHS77)) ) ) ),
            0, mResult + 60);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS97,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS27, vec_mul(mRHSrow15, vAuxLHS17)),
                                    vec_madd(mRHSrow45, vAuxLHS47, vec_mul(mRHSrow35, vAuxLHS37)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS67, vec_mul(mRHSrow55, vAuxLHS57)),
                                    vec_madd(mRHSrow85, vAuxLHS87, vec_mul(mRHSrow75, vAuxLHS77)) ) ) ),
            0, mResult + 62);
    //building the eighth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS28, vec_mul(mRHSrow11, vAuxLHS18)),
                                    vec_madd(mRHSrow41, vAuxLHS48, vec_mul(mRHSrow31, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS68, vec_mul(mRHSrow51, vAuxLHS58)),
                                    vec_madd(mRHSrow81, vAuxLHS88, vec_mul(mRHSrow71, vAuxLHS78)) ) ) ),
            0, mResult + 63);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS28, vec_mul(mRHSrow12, vAuxLHS18)),
                                    vec_madd(mRHSrow42, vAuxLHS48, vec_mul(mRHSrow32, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS68, vec_mul(mRHSrow52, vAuxLHS58)),
                                    vec_madd(mRHSrow82, vAuxLHS88, vec_mul(mRHSrow72, vAuxLHS78)) ) ) ),
            0, mResult + 65);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS28, vec_mul(mRHSrow13, vAuxLHS18)),
                                    vec_madd(mRHSrow43, vAuxLHS48, vec_mul(mRHSrow33, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS68, vec_mul(mRHSrow53, vAuxLHS58)),
                                    vec_madd(mRHSrow83, vAuxLHS88, vec_mul(mRHSrow73, vAuxLHS78)) ) ) ),
            0, mResult + 67);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS28, vec_mul(mRHSrow14, vAuxLHS18)),
                                    vec_madd(mRHSrow44, vAuxLHS48, vec_mul(mRHSrow34, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS68, vec_mul(mRHSrow54, vAuxLHS58)),
                                    vec_madd(mRHSrow84, vAuxLHS88, vec_mul(mRHSrow74, vAuxLHS78)) ) ) ),
            0, mResult + 69);
    vec_xst(vec_madd( mRHSrow95, vAuxLHS98,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS28, vec_mul(mRHSrow15, vAuxLHS18)),
                                    vec_madd(mRHSrow45, vAuxLHS48, vec_mul(mRHSrow35, vAuxLHS38)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS68, vec_mul(mRHSrow55, vAuxLHS58)),
                                    vec_madd(mRHSrow85, vAuxLHS88, vec_mul(mRHSrow75, vAuxLHS78)) ) ) ),
            0, mResult + 71);
    //building the ninth row of mResult
    vec_xst(vec_madd( mRHSrow91, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow21, vAuxLHS29, vec_mul(mRHSrow11, vAuxLHS19)),
                                    vec_madd(mRHSrow41, vAuxLHS49, vec_mul(mRHSrow31, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow61, vAuxLHS69, vec_mul(mRHSrow51, vAuxLHS59)),
                                    vec_madd(mRHSrow81, vAuxLHS89, vec_mul(mRHSrow71, vAuxLHS79)) ) ) ),
            0, mResult + 72);
    vec_xst(vec_madd( mRHSrow92, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow22, vAuxLHS29, vec_mul(mRHSrow12, vAuxLHS19)),
                                    vec_madd(mRHSrow42, vAuxLHS49, vec_mul(mRHSrow32, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow62, vAuxLHS69, vec_mul(mRHSrow52, vAuxLHS59)),
                                    vec_madd(mRHSrow82, vAuxLHS89, vec_mul(mRHSrow72, vAuxLHS79)) ) ) ),
            0, mResult + 74);
    vec_xst(vec_madd( mRHSrow93, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow23, vAuxLHS29, vec_mul(mRHSrow13, vAuxLHS19)),
                                    vec_madd(mRHSrow43, vAuxLHS49, vec_mul(mRHSrow33, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow63, vAuxLHS69, vec_mul(mRHSrow53, vAuxLHS59)),
                                    vec_madd(mRHSrow83, vAuxLHS89, vec_mul(mRHSrow73, vAuxLHS79)) ) ) ),
            0, mResult + 76);
    vec_xst(vec_madd( mRHSrow94, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow24, vAuxLHS29, vec_mul(mRHSrow14, vAuxLHS19)),
                                    vec_madd(mRHSrow44, vAuxLHS49, vec_mul(mRHSrow34, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow64, vAuxLHS69, vec_mul(mRHSrow54, vAuxLHS59)),
                                    vec_madd(mRHSrow84, vAuxLHS89, vec_mul(mRHSrow74, vAuxLHS79)) ) ) ),
            0, mResult + 78);
    __vector double mResultLastElem =
          vec_madd( mRHSrow95, vAuxLHS99,
                    vec_add(
                            vec_add(
                                    vec_madd(mRHSrow25, vAuxLHS29, vec_mul(mRHSrow15, vAuxLHS19)),
                                    vec_madd(mRHSrow45, vAuxLHS49, vec_mul(mRHSrow35, vAuxLHS39)) ),
                            vec_add(
                                    vec_madd(mRHSrow65, vAuxLHS69, vec_mul(mRHSrow55, vAuxLHS59)),
                                    vec_madd(mRHSrow85, vAuxLHS89, vec_mul(mRHSrow75, vAuxLHS79)) ) ) );
      mResult[80] = mResultLastElem[0];

}
//====================================================================================================//
inline void mul12x12RowMajor(double* mLHS, double* mRHS, double* mResult) {

	__vector double mLHSrow11, mLHSrow21, mLHSrow31, mLHSrow41, mLHSrow51, mLHSrow61, mLHSrow71, mLHSrow81, mLHSrow91, mLHSrow101, mLHSrow111, mLHSrow121,
			mLHSrow12, mLHSrow22, mLHSrow32, mLHSrow42, mLHSrow52, mLHSrow62, mLHSrow72, mLHSrow82, mLHSrow92, mLHSrow102, mLHSrow112, mLHSrow122,
			mLHSrow13, mLHSrow23, mLHSrow33, mLHSrow43, mLHSrow53, mLHSrow63, mLHSrow73, mLHSrow83, mLHSrow93, mLHSrow103, mLHSrow113, mLHSrow123,
			mLHSrow14, mLHSrow24, mLHSrow34, mLHSrow44, mLHSrow54, mLHSrow64, mLHSrow74, mLHSrow84, mLHSrow94, mLHSrow104, mLHSrow114, mLHSrow124,
			mLHSrow15, mLHSrow25, mLHSrow35, mLHSrow45, mLHSrow55, mLHSrow65, mLHSrow75, mLHSrow85, mLHSrow95, mLHSrow105, mLHSrow115, mLHSrow125,
			mLHSrow16, mLHSrow26, mLHSrow36, mLHSrow46, mLHSrow56, mLHSrow66, mLHSrow76, mLHSrow86, mLHSrow96, mLHSrow106, mLHSrow116, mLHSrow126,
			mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81, mRHSrow91, mRHSrow101, mRHSrow111, mRHSrow121,
			mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82, mRHSrow92, mRHSrow102, mRHSrow112, mRHSrow122,
			mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83, mRHSrow93, mRHSrow103, mRHSrow113, mRHSrow123,
			mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84, mRHSrow94, mRHSrow104, mRHSrow114, mRHSrow124,
			mRHSrow15, mRHSrow25, mRHSrow35, mRHSrow45, mRHSrow55, mRHSrow65, mRHSrow75, mRHSrow85, mRHSrow95, mRHSrow105, mRHSrow115, mRHSrow125,
			mRHSrow16, mRHSrow26, mRHSrow36, mRHSrow46, mRHSrow56, mRHSrow66, mRHSrow76, mRHSrow86, mRHSrow96, mRHSrow106, mRHSrow116, mRHSrow126;

	// row 1
	mLHSrow11 = vec_xl(0, mLHS);
	mLHSrow12 = vec_xl(0, mLHS + 2);
	mLHSrow13 = vec_xl(0, mLHS + 4);
	mLHSrow14 = vec_xl(0, mLHS + 6);
	mLHSrow15 = vec_xl(0, mLHS + 8);
	mLHSrow16 = vec_xl(0, mLHS + 10);

	// row 2
	mLHSrow21 = vec_xl(0, mLHS + 12);
	mLHSrow22 = vec_xl(0, mLHS + 14);
	mLHSrow23 = vec_xl(0, mLHS + 16);
	mLHSrow24 = vec_xl(0, mLHS + 18);
	mLHSrow25 = vec_xl(0, mLHS + 20);
	mLHSrow26 = vec_xl(0, mLHS + 22);

	// row 3
	mLHSrow31 = vec_xl(0, mLHS + 24);
	mLHSrow32 = vec_xl(0, mLHS + 26);
	mLHSrow33 = vec_xl(0, mLHS + 28);
	mLHSrow34 = vec_xl(0, mLHS + 30);
	mLHSrow35 = vec_xl(0, mLHS + 32);
	mLHSrow36 = vec_xl(0, mLHS + 34);

	// row 4
	mLHSrow41 = vec_xl(0, mLHS + 36);
	mLHSrow42 = vec_xl(0, mLHS + 38);
	mLHSrow43 = vec_xl(0, mLHS + 40);
	mLHSrow44 = vec_xl(0, mLHS + 42);
	mLHSrow45 = vec_xl(0, mLHS + 44);
	mLHSrow46 = vec_xl(0, mLHS + 46);

	// row 5
	mLHSrow51 = vec_xl(0, mLHS + 48);
	mLHSrow52 = vec_xl(0, mLHS + 50);
	mLHSrow53 = vec_xl(0, mLHS + 52);
	mLHSrow54 = vec_xl(0, mLHS + 54);
	mLHSrow55 = vec_xl(0, mLHS + 56);
	mLHSrow56 = vec_xl(0, mLHS + 58);

	// row 6
	mLHSrow61 = vec_xl(0, mLHS + 60);
	mLHSrow62 = vec_xl(0, mLHS + 62);
	mLHSrow63 = vec_xl(0, mLHS + 64);
	mLHSrow64 = vec_xl(0, mLHS + 66);
	mLHSrow65 = vec_xl(0, mLHS + 68);
	mLHSrow66 = vec_xl(0, mLHS + 70);

	// row 7
	mLHSrow71 = vec_xl(0, mLHS + 72);
	mLHSrow72 = vec_xl(0, mLHS + 74);
	mLHSrow73 = vec_xl(0, mLHS + 76);
	mLHSrow74 = vec_xl(0, mLHS + 78);
	mLHSrow75 = vec_xl(0, mLHS + 80);
	mLHSrow76 = vec_xl(0, mLHS + 82);

	// row 8
	mLHSrow81 = vec_xl(0, mLHS + 84);
	mLHSrow82 = vec_xl(0, mLHS + 86);
	mLHSrow83 = vec_xl(0, mLHS + 88);
	mLHSrow84 = vec_xl(0, mLHS + 90);
	mLHSrow85 = vec_xl(0, mLHS + 92);
	mLHSrow86 = vec_xl(0, mLHS + 94);

	// row 9
	mLHSrow91 = vec_xl(0, mLHS + 96);
	mLHSrow92 = vec_xl(0, mLHS + 98);
	mLHSrow93 = vec_xl(0, mLHS + 100);
	mLHSrow94 = vec_xl(0, mLHS + 102);
	mLHSrow95 = vec_xl(0, mLHS + 104);
	mLHSrow96 = vec_xl(0, mLHS + 106);

	// row 10
	mLHSrow101 = vec_xl(0, mLHS + 108);
	mLHSrow102 = vec_xl(0, mLHS + 110);
	mLHSrow103 = vec_xl(0, mLHS + 112);
	mLHSrow104 = vec_xl(0, mLHS + 114);
	mLHSrow105 = vec_xl(0, mLHS + 116);
	mLHSrow106 = vec_xl(0, mLHS + 118);

	// row 11
	mLHSrow111 = vec_xl(0, mLHS + 120);
	mLHSrow112 = vec_xl(0, mLHS + 122);
	mLHSrow113 = vec_xl(0, mLHS + 124);
	mLHSrow114 = vec_xl(0, mLHS + 126);
	mLHSrow115 = vec_xl(0, mLHS + 128);
	mLHSrow116 = vec_xl(0, mLHS + 130);

	// row 12
	mLHSrow121 = vec_xl(0, mLHS + 132);
	mLHSrow122 = vec_xl(0, mLHS + 134);
	mLHSrow123 = vec_xl(0, mLHS + 136);
	mLHSrow124 = vec_xl(0, mLHS + 138);
	mLHSrow125 = vec_xl(0, mLHS + 140);
	mLHSrow126 = vec_xl(0, mLHS + 142);

	// column 1
	__vector double vAuxLHS11 = {mLHSrow11[0], mLHSrow11[0]};
	__vector double vAuxLHS12 = {mLHSrow21[0], mLHSrow21[0]};
	__vector double vAuxLHS13 = {mLHSrow31[0], mLHSrow31[0]};
	__vector double vAuxLHS14 = {mLHSrow41[0], mLHSrow41[0]};
	__vector double vAuxLHS15 = {mLHSrow51[0], mLHSrow51[0]};
	__vector double vAuxLHS16 = {mLHSrow61[0], mLHSrow61[0]};
	__vector double vAuxLHS17 = {mLHSrow71[0], mLHSrow71[0]};
	__vector double vAuxLHS18 = {mLHSrow81[0], mLHSrow81[0]};
	__vector double vAuxLHS19 = {mLHSrow91[0], mLHSrow91[0]};
	__vector double vAuxLHS110 = {mLHSrow101[0], mLHSrow101[0]};
	__vector double vAuxLHS0111 = {mLHSrow111[0], mLHSrow111[0]};
	__vector double vAuxLHS0112 = {mLHSrow121[0], mLHSrow121[0]};

	// column 2
	__vector double vAuxLHS21 = {mLHSrow11[1], mLHSrow11[1]};
	__vector double vAuxLHS22 = {mLHSrow21[1], mLHSrow21[1]};
	__vector double vAuxLHS23 = {mLHSrow31[1], mLHSrow31[1]};
	__vector double vAuxLHS24 = {mLHSrow41[1], mLHSrow41[1]};
	__vector double vAuxLHS25 = {mLHSrow51[1], mLHSrow51[1]};
	__vector double vAuxLHS26 = {mLHSrow61[1], mLHSrow61[1]};
	__vector double vAuxLHS27 = {mLHSrow71[1], mLHSrow71[1]};
	__vector double vAuxLHS28 = {mLHSrow81[1], mLHSrow81[1]};
	__vector double vAuxLHS29 = {mLHSrow91[1], mLHSrow91[1]};
	__vector double vAuxLHS210 = {mLHSrow101[1], mLHSrow101[1]};
	__vector double vAuxLHS211 = {mLHSrow111[1], mLHSrow111[1]};
	__vector double vAuxLHS212 = {mLHSrow121[1], mLHSrow121[1]};

	// column 3
	__vector double vAuxLHS31 = {mLHSrow12[0], mLHSrow12[0]};
	__vector double vAuxLHS32 = {mLHSrow22[0], mLHSrow22[0]};
	__vector double vAuxLHS33 = {mLHSrow32[0], mLHSrow32[0]};
	__vector double vAuxLHS34 = {mLHSrow42[0], mLHSrow42[0]};
	__vector double vAuxLHS35 = {mLHSrow52[0], mLHSrow52[0]};
	__vector double vAuxLHS36 = {mLHSrow62[0], mLHSrow62[0]};
	__vector double vAuxLHS37 = {mLHSrow72[0], mLHSrow72[0]};
	__vector double vAuxLHS38 = {mLHSrow82[0], mLHSrow82[0]};
	__vector double vAuxLHS39 = {mLHSrow92[0], mLHSrow92[0]};
	__vector double vAuxLHS310 = {mLHSrow102[0], mLHSrow102[0]};
	__vector double vAuxLHS311 = {mLHSrow112[0], mLHSrow112[0]};
	__vector double vAuxLHS312 = {mLHSrow122[0], mLHSrow122[0]};

	// column 4
	__vector double vAuxLHS41 = {mLHSrow12[1], mLHSrow12[1]};
	__vector double vAuxLHS42 = {mLHSrow22[1], mLHSrow22[1]};
	__vector double vAuxLHS43 = {mLHSrow32[1], mLHSrow32[1]};
	__vector double vAuxLHS44 = {mLHSrow42[1], mLHSrow42[1]};
	__vector double vAuxLHS45 = {mLHSrow52[1], mLHSrow52[1]};
	__vector double vAuxLHS46 = {mLHSrow62[1], mLHSrow62[1]};
	__vector double vAuxLHS47 = {mLHSrow72[1], mLHSrow72[1]};
	__vector double vAuxLHS48 = {mLHSrow82[1], mLHSrow82[1]};
	__vector double vAuxLHS49 = {mLHSrow92[1], mLHSrow92[1]};
	__vector double vAuxLHS410 = {mLHSrow102[1], mLHSrow102[1]};
	__vector double vAuxLHS411 = {mLHSrow112[1], mLHSrow112[1]};
	__vector double vAuxLHS412 = {mLHSrow122[1], mLHSrow122[1]};

	// column 5
	__vector double vAuxLHS51 = {mLHSrow13[0], mLHSrow13[0]};
	__vector double vAuxLHS52 = {mLHSrow23[0], mLHSrow23[0]};
	__vector double vAuxLHS53 = {mLHSrow33[0], mLHSrow33[0]};
	__vector double vAuxLHS54 = {mLHSrow43[0], mLHSrow43[0]};
	__vector double vAuxLHS55 = {mLHSrow53[0], mLHSrow53[0]};
	__vector double vAuxLHS56 = {mLHSrow63[0], mLHSrow63[0]};
	__vector double vAuxLHS57 = {mLHSrow73[0], mLHSrow73[0]};
	__vector double vAuxLHS58 = {mLHSrow83[0], mLHSrow83[0]};
	__vector double vAuxLHS59 = {mLHSrow93[0], mLHSrow93[0]};
	__vector double vAuxLHS510 = {mLHSrow103[0], mLHSrow103[0]};
	__vector double vAuxLHS511 = {mLHSrow113[0], mLHSrow113[0]};
	__vector double vAuxLHS512 = {mLHSrow123[0], mLHSrow123[0]};

	// column 6
	__vector double vAuxLHS61 = {mLHSrow13[1], mLHSrow13[1]};
	__vector double vAuxLHS62 = {mLHSrow23[1], mLHSrow23[1]};
	__vector double vAuxLHS63 = {mLHSrow33[1], mLHSrow33[1]};
	__vector double vAuxLHS64 = {mLHSrow43[1], mLHSrow43[1]};
	__vector double vAuxLHS65 = {mLHSrow53[1], mLHSrow53[1]};
	__vector double vAuxLHS66 = {mLHSrow63[1], mLHSrow63[1]};
	__vector double vAuxLHS67 = {mLHSrow73[1], mLHSrow73[1]};
	__vector double vAuxLHS68 = {mLHSrow83[1], mLHSrow83[1]};
	__vector double vAuxLHS69 = {mLHSrow93[1], mLHSrow93[1]};
	__vector double vAuxLHS610 = {mLHSrow103[1], mLHSrow103[1]};
	__vector double vAuxLHS611 = {mLHSrow113[1], mLHSrow113[1]};
	__vector double vAuxLHS612 = {mLHSrow123[1], mLHSrow123[1]};

	// column 7
	__vector double vAuxLHS71 = {mLHSrow14[0], mLHSrow14[0]};
	__vector double vAuxLHS72 = {mLHSrow24[0], mLHSrow24[0]};
	__vector double vAuxLHS73 = {mLHSrow34[0], mLHSrow34[0]};
	__vector double vAuxLHS74 = {mLHSrow44[0], mLHSrow44[0]};
	__vector double vAuxLHS75 = {mLHSrow54[0], mLHSrow54[0]};
	__vector double vAuxLHS76 = {mLHSrow64[0], mLHSrow64[0]};
	__vector double vAuxLHS77 = {mLHSrow74[0], mLHSrow74[0]};
	__vector double vAuxLHS78 = {mLHSrow84[0], mLHSrow84[0]};
	__vector double vAuxLHS79 = {mLHSrow94[0], mLHSrow94[0]};
	__vector double vAuxLHS710 = {mLHSrow104[0], mLHSrow104[0]};
	__vector double vAuxLHS711 = {mLHSrow114[0], mLHSrow114[0]};
	__vector double vAuxLHS712 = {mLHSrow124[0], mLHSrow124[0]};

	// column 8
	__vector double vAuxLHS81 = {mLHSrow14[1], mLHSrow14[1]};
	__vector double vAuxLHS82 = {mLHSrow24[1], mLHSrow24[1]};
	__vector double vAuxLHS83 = {mLHSrow34[1], mLHSrow34[1]};
	__vector double vAuxLHS84 = {mLHSrow44[1], mLHSrow44[1]};
	__vector double vAuxLHS85 = {mLHSrow54[1], mLHSrow54[1]};
	__vector double vAuxLHS86 = {mLHSrow64[1], mLHSrow64[1]};
	__vector double vAuxLHS87 = {mLHSrow74[1], mLHSrow74[1]};
	__vector double vAuxLHS88 = {mLHSrow84[1], mLHSrow84[1]};
	__vector double vAuxLHS89 = {mLHSrow94[1], mLHSrow94[1]};
	__vector double vAuxLHS810 = {mLHSrow104[1], mLHSrow104[1]};
	__vector double vAuxLHS811 = {mLHSrow114[1], mLHSrow114[1]};
	__vector double vAuxLHS812 = {mLHSrow124[1], mLHSrow124[1]};

	// column 9
	__vector double vAuxLHS91 = {mLHSrow15[0], mLHSrow15[0]};
	__vector double vAuxLHS92 = {mLHSrow25[0], mLHSrow25[0]};
	__vector double vAuxLHS93 = {mLHSrow35[0], mLHSrow35[0]};
	__vector double vAuxLHS94 = {mLHSrow45[0], mLHSrow45[0]};
	__vector double vAuxLHS95 = {mLHSrow55[0], mLHSrow55[0]};
	__vector double vAuxLHS96 = {mLHSrow65[0], mLHSrow65[0]};
	__vector double vAuxLHS97 = {mLHSrow75[0], mLHSrow75[0]};
	__vector double vAuxLHS98 = {mLHSrow85[0], mLHSrow85[0]};
	__vector double vAuxLHS99 = {mLHSrow95[0], mLHSrow95[0]};
	__vector double vAuxLHS910 = {mLHSrow105[0], mLHSrow105[0]};
	__vector double vAuxLHS911 = {mLHSrow115[0], mLHSrow115[0]};
	__vector double vAuxLHS912 = {mLHSrow125[0], mLHSrow125[0]};

	// column 10
	__vector double vAuxLHS101 = {mLHSrow15[1], mLHSrow15[1]};
	__vector double vAuxLHS102 = {mLHSrow25[1], mLHSrow25[1]};
	__vector double vAuxLHS103 = {mLHSrow35[1], mLHSrow35[1]};
	__vector double vAuxLHS104 = {mLHSrow45[1], mLHSrow45[1]};
	__vector double vAuxLHS105 = {mLHSrow55[1], mLHSrow55[1]};
	__vector double vAuxLHS106 = {mLHSrow65[1], mLHSrow65[1]};
	__vector double vAuxLHS107 = {mLHSrow75[1], mLHSrow75[1]};
	__vector double vAuxLHS108 = {mLHSrow85[1], mLHSrow85[1]};
	__vector double vAuxLHS109 = {mLHSrow95[1], mLHSrow95[1]};
	__vector double vAuxLHS1010 = {mLHSrow105[1], mLHSrow105[1]};
	__vector double vAuxLHS1011 = {mLHSrow115[1], mLHSrow115[1]};
	__vector double vAuxLHS1012 = {mLHSrow125[1], mLHSrow125[1]};

	// column 11
	__vector double vAuxLHS111 = {mLHSrow16[0], mLHSrow16[0]};
	__vector double vAuxLHS112 = {mLHSrow26[0], mLHSrow26[0]};
	__vector double vAuxLHS113 = {mLHSrow36[0], mLHSrow36[0]};
	__vector double vAuxLHS114 = {mLHSrow46[0], mLHSrow46[0]};
	__vector double vAuxLHS115 = {mLHSrow56[0], mLHSrow56[0]};
	__vector double vAuxLHS116 = {mLHSrow66[0], mLHSrow66[0]};
	__vector double vAuxLHS117 = {mLHSrow76[0], mLHSrow76[0]};
	__vector double vAuxLHS118 = {mLHSrow86[0], mLHSrow86[0]};
	__vector double vAuxLHS119 = {mLHSrow96[0], mLHSrow96[0]};
	__vector double vAuxLHS1110 = {mLHSrow106[0], mLHSrow106[0]};
	__vector double vAuxLHS1111 = {mLHSrow116[0], mLHSrow116[0]};
	__vector double vAuxLHS1112 = {mLHSrow126[0], mLHSrow126[0]};

	// column 12
	__vector double vAuxLHS121 = {mLHSrow16[1], mLHSrow16[1]};
	__vector double vAuxLHS122 = {mLHSrow26[1], mLHSrow26[1]};
	__vector double vAuxLHS123 = {mLHSrow36[1], mLHSrow36[1]};
	__vector double vAuxLHS124 = {mLHSrow46[1], mLHSrow46[1]};
	__vector double vAuxLHS125 = {mLHSrow56[1], mLHSrow56[1]};
	__vector double vAuxLHS126 = {mLHSrow66[1], mLHSrow66[1]};
	__vector double vAuxLHS127 = {mLHSrow76[1], mLHSrow76[1]};
	__vector double vAuxLHS128 = {mLHSrow86[1], mLHSrow86[1]};
	__vector double vAuxLHS129 = {mLHSrow96[1], mLHSrow96[1]};
	__vector double vAuxLHS1210 = {mLHSrow106[1], mLHSrow106[1]};
	__vector double vAuxLHS1211 = {mLHSrow116[1], mLHSrow116[1]};
	__vector double vAuxLHS1212 = {mLHSrow126[1], mLHSrow126[1]};

	// row 1
	mRHSrow11 = vec_xl(0, mRHS);
	mRHSrow12 = vec_xl(0, mRHS + 2);
	mRHSrow13 = vec_xl(0, mRHS + 4);
	mRHSrow14 = vec_xl(0, mRHS + 6);
	mRHSrow15 = vec_xl(0, mRHS + 8);
	mRHSrow16 = vec_xl(0, mRHS + 10);

	// row 2
	mRHSrow21 = vec_xl(0, mRHS + 12);
	mRHSrow22 = vec_xl(0, mRHS + 14);
	mRHSrow23 = vec_xl(0, mRHS + 16);
	mRHSrow24 = vec_xl(0, mRHS + 18);
	mRHSrow25 = vec_xl(0, mRHS + 20);
	mRHSrow26 = vec_xl(0, mRHS + 22);

	// row 3
	mRHSrow31 = vec_xl(0, mRHS + 24);
	mRHSrow32 = vec_xl(0, mRHS + 26);
	mRHSrow33 = vec_xl(0, mRHS + 28);
	mRHSrow34 = vec_xl(0, mRHS + 30);
	mRHSrow35 = vec_xl(0, mRHS + 32);
	mRHSrow36 = vec_xl(0, mRHS + 34);

	// row 4
	mRHSrow41 = vec_xl(0, mRHS + 36);
	mRHSrow42 = vec_xl(0, mRHS + 38);
	mRHSrow43 = vec_xl(0, mRHS + 40);
	mRHSrow44 = vec_xl(0, mRHS + 42);
	mRHSrow45 = vec_xl(0, mRHS + 44);
	mRHSrow46 = vec_xl(0, mRHS + 46);

	// row 5
	mRHSrow51 = vec_xl(0, mRHS + 48);
	mRHSrow52 = vec_xl(0, mRHS + 50);
	mRHSrow53 = vec_xl(0, mRHS + 52);
	mRHSrow54 = vec_xl(0, mRHS + 54);
	mRHSrow55 = vec_xl(0, mRHS + 56);
	mRHSrow56 = vec_xl(0, mRHS + 58);

	// row 6
	mRHSrow61 = vec_xl(0, mRHS + 60);
	mRHSrow62 = vec_xl(0, mRHS + 62);
	mRHSrow63 = vec_xl(0, mRHS + 64);
	mRHSrow64 = vec_xl(0, mRHS + 66);
	mRHSrow65 = vec_xl(0, mRHS + 68);
	mRHSrow66 = vec_xl(0, mRHS + 70);

	// row 7
	mRHSrow71 = vec_xl(0, mRHS + 72);
	mRHSrow72 = vec_xl(0, mRHS + 74);
	mRHSrow73 = vec_xl(0, mRHS + 76);
	mRHSrow74 = vec_xl(0, mRHS + 78);
	mRHSrow75 = vec_xl(0, mRHS + 80);
	mRHSrow76 = vec_xl(0, mRHS + 82);

	// row 8
	mRHSrow81 = vec_xl(0, mRHS + 84);
	mRHSrow82 = vec_xl(0, mRHS + 86);
	mRHSrow83 = vec_xl(0, mRHS + 88);
	mRHSrow84 = vec_xl(0, mRHS + 90);
	mRHSrow85 = vec_xl(0, mRHS + 92);
	mRHSrow86 = vec_xl(0, mRHS + 94);

	// row 9
	mRHSrow91 = vec_xl(0, mRHS + 96);
	mRHSrow92 = vec_xl(0, mRHS + 98);
	mRHSrow93 = vec_xl(0, mRHS + 100);
	mRHSrow94 = vec_xl(0, mRHS + 102);
	mRHSrow95 = vec_xl(0, mRHS + 104);
	mRHSrow96 = vec_xl(0, mRHS + 106);

	// row 10
	mRHSrow101 = vec_xl(0, mRHS + 108);
	mRHSrow102 = vec_xl(0, mRHS + 110);
	mRHSrow103 = vec_xl(0, mRHS + 112);
	mRHSrow104 = vec_xl(0, mRHS + 114);
	mRHSrow105 = vec_xl(0, mRHS + 116);
	mRHSrow106 = vec_xl(0, mRHS + 118);

	// row 11
	mRHSrow111 = vec_xl(0, mRHS + 120);
	mRHSrow112 = vec_xl(0, mRHS + 122);
	mRHSrow113 = vec_xl(0, mRHS + 124);
	mRHSrow114 = vec_xl(0, mRHS + 126);
	mRHSrow115 = vec_xl(0, mRHS + 128);
	mRHSrow116 = vec_xl(0, mRHS + 130);

	// row 12
	mRHSrow121 = vec_xl(0, mRHS + 132);
	mRHSrow122 = vec_xl(0, mRHS + 134);
	mRHSrow123 = vec_xl(0, mRHS + 136);
	mRHSrow124 = vec_xl(0, mRHS + 138);
	mRHSrow125 = vec_xl(0, mRHS + 140);
	mRHSrow126 = vec_xl(0, mRHS + 142);

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
}

inline void mul12x12ColMajor(double* mLHS, double* mRHS, double* mResult) {

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

	// column 1
	mLHScol11 = vec_xl(0, mLHS);
	mLHScol12 = vec_xl(0, mLHS + 2);
	mLHScol13 = vec_xl(0, mLHS + 4);
	mLHScol14 = vec_xl(0, mLHS + 6);
	mLHScol15 = vec_xl(0, mLHS + 8);
	mLHScol16 = vec_xl(0, mLHS + 10);

	// column 2
	mLHScol21 = vec_xl(0, mLHS + 12);
	mLHScol22 = vec_xl(0, mLHS + 14);
	mLHScol23 = vec_xl(0, mLHS + 16);
	mLHScol24 = vec_xl(0, mLHS + 18);
	mLHScol25 = vec_xl(0, mLHS + 20);
	mLHScol26 = vec_xl(0, mLHS + 22);

	// column 3
	mLHScol31 = vec_xl(0, mLHS + 24);
	mLHScol32 = vec_xl(0, mLHS + 26);
	mLHScol33 = vec_xl(0, mLHS + 28);
	mLHScol34 = vec_xl(0, mLHS + 30);
	mLHScol35 = vec_xl(0, mLHS + 32);
	mLHScol36 = vec_xl(0, mLHS + 34);

	// column 4
	mLHScol41 = vec_xl(0, mLHS + 36);
	mLHScol42 = vec_xl(0, mLHS + 38);
	mLHScol43 = vec_xl(0, mLHS + 40);
	mLHScol44 = vec_xl(0, mLHS + 42);
	mLHScol45 = vec_xl(0, mLHS + 44);
	mLHScol46 = vec_xl(0, mLHS + 46);

	// column 5
	mLHScol51 = vec_xl(0, mLHS + 48);
	mLHScol52 = vec_xl(0, mLHS + 50);
	mLHScol53 = vec_xl(0, mLHS + 52);
	mLHScol54 = vec_xl(0, mLHS + 54);
	mLHScol55 = vec_xl(0, mLHS + 56);
	mLHScol56 = vec_xl(0, mLHS + 58);

	// column 6
	mLHScol61 = vec_xl(0, mLHS + 60);
	mLHScol62 = vec_xl(0, mLHS + 62);
	mLHScol63 = vec_xl(0, mLHS + 64);
	mLHScol64 = vec_xl(0, mLHS + 66);
	mLHScol65 = vec_xl(0, mLHS + 68);
	mLHScol66 = vec_xl(0, mLHS + 70);

	// column 7
	mLHScol71 = vec_xl(0, mLHS + 72);
	mLHScol72 = vec_xl(0, mLHS + 74);
	mLHScol73 = vec_xl(0, mLHS + 76);
	mLHScol74 = vec_xl(0, mLHS + 78);
	mLHScol75 = vec_xl(0, mLHS + 80);
	mLHScol76 = vec_xl(0, mLHS + 82);

	// column 8
	mLHScol81 = vec_xl(0, mLHS + 84);
	mLHScol82 = vec_xl(0, mLHS + 86);
	mLHScol83 = vec_xl(0, mLHS + 88);
	mLHScol84 = vec_xl(0, mLHS + 90);
	mLHScol85 = vec_xl(0, mLHS + 92);
	mLHScol86 = vec_xl(0, mLHS + 94);

	// column 9
	mLHScol91 = vec_xl(0, mLHS + 96);
	mLHScol92 = vec_xl(0, mLHS + 98);
	mLHScol93 = vec_xl(0, mLHS + 100);
	mLHScol94 = vec_xl(0, mLHS + 102);
	mLHScol95 = vec_xl(0, mLHS + 104);
	mLHScol96 = vec_xl(0, mLHS + 106);

	// column 10
	mLHScol101 = vec_xl(0, mLHS + 108);
	mLHScol102 = vec_xl(0, mLHS + 110);
	mLHScol103 = vec_xl(0, mLHS + 112);
	mLHScol104 = vec_xl(0, mLHS + 114);
	mLHScol105 = vec_xl(0, mLHS + 116);
	mLHScol106 = vec_xl(0, mLHS + 118);

	// column 11
	mLHScol111 = vec_xl(0, mLHS + 120);
	mLHScol112 = vec_xl(0, mLHS + 122);
	mLHScol113 = vec_xl(0, mLHS + 124);
	mLHScol114 = vec_xl(0, mLHS + 126);
	mLHScol115 = vec_xl(0, mLHS + 128);
	mLHScol116 = vec_xl(0, mLHS + 130);

	// column 12
	mLHScol121 = vec_xl(0, mLHS + 132);
	mLHScol122 = vec_xl(0, mLHS + 134);
	mLHScol123 = vec_xl(0, mLHS + 136);
	mLHScol124 = vec_xl(0, mLHS + 138);
	mLHScol125 = vec_xl(0, mLHS + 140);
	mLHScol126 = vec_xl(0, mLHS + 142);

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

	// column 1
	mRHSrow11 = vec_xl(0, mRHS);
	mRHSrow12 = vec_xl(0, mRHS + 2);
	mRHSrow13 = vec_xl(0, mRHS + 4);
	mRHSrow14 = vec_xl(0, mRHS + 6);
	mRHSrow15 = vec_xl(0, mRHS + 8);
	mRHSrow16 = vec_xl(0, mRHS + 10);

	// column 2
	mRHSrow21 = vec_xl(0, mRHS + 12);
	mRHSrow22 = vec_xl(0, mRHS + 14);
	mRHSrow23 = vec_xl(0, mRHS + 16);
	mRHSrow24 = vec_xl(0, mRHS + 18);
	mRHSrow25 = vec_xl(0, mRHS + 20);
	mRHSrow26 = vec_xl(0, mRHS + 22);

	// column 3
	mRHSrow31 = vec_xl(0, mRHS + 24);
	mRHSrow32 = vec_xl(0, mRHS + 26);
	mRHSrow33 = vec_xl(0, mRHS + 28);
	mRHSrow34 = vec_xl(0, mRHS + 30);
	mRHSrow35 = vec_xl(0, mRHS + 32);
	mRHSrow36 = vec_xl(0, mRHS + 34);

	// column 4
	mRHSrow41 = vec_xl(0, mRHS + 36);
	mRHSrow42 = vec_xl(0, mRHS + 38);
	mRHSrow43 = vec_xl(0, mRHS + 40);
	mRHSrow44 = vec_xl(0, mRHS + 42);
	mRHSrow45 = vec_xl(0, mRHS + 44);
	mRHSrow46 = vec_xl(0, mRHS + 46);

	// column 5
	mRHSrow51 = vec_xl(0, mRHS + 48);
	mRHSrow52 = vec_xl(0, mRHS + 50);
	mRHSrow53 = vec_xl(0, mRHS + 52);
	mRHSrow54 = vec_xl(0, mRHS + 54);
	mRHSrow55 = vec_xl(0, mRHS + 56);
	mRHSrow56 = vec_xl(0, mRHS + 58);

	// column 6
	mRHSrow61 = vec_xl(0, mRHS + 60);
	mRHSrow62 = vec_xl(0, mRHS + 62);
	mRHSrow63 = vec_xl(0, mRHS + 64);
	mRHSrow64 = vec_xl(0, mRHS + 66);
	mRHSrow65 = vec_xl(0, mRHS + 68);
	mRHSrow66 = vec_xl(0, mRHS + 70);

	// column 7
	mRHSrow71 = vec_xl(0, mRHS + 72);
	mRHSrow72 = vec_xl(0, mRHS + 74);
	mRHSrow73 = vec_xl(0, mRHS + 76);
	mRHSrow74 = vec_xl(0, mRHS + 78);
	mRHSrow75 = vec_xl(0, mRHS + 80);
	mRHSrow76 = vec_xl(0, mRHS + 82);

	// column 8
	mRHSrow81 = vec_xl(0, mRHS + 84);
	mRHSrow82 = vec_xl(0, mRHS + 86);
	mRHSrow83 = vec_xl(0, mRHS + 88);
	mRHSrow84 = vec_xl(0, mRHS + 90);
	mRHSrow85 = vec_xl(0, mRHS + 92);
	mRHSrow86 = vec_xl(0, mRHS + 94);

	// column 9
	mRHSrow91 = vec_xl(0, mRHS + 96);
	mRHSrow92 = vec_xl(0, mRHS + 98);
	mRHSrow93 = vec_xl(0, mRHS + 100);
	mRHSrow94 = vec_xl(0, mRHS + 102);
	mRHSrow95 = vec_xl(0, mRHS + 104);
	mRHSrow96 = vec_xl(0, mRHS + 106);

	// column 10
	mRHSrow101 = vec_xl(0, mRHS + 108);
	mRHSrow102 = vec_xl(0, mRHS + 110);
	mRHSrow103 = vec_xl(0, mRHS + 112);
	mRHSrow104 = vec_xl(0, mRHS + 114);
	mRHSrow105 = vec_xl(0, mRHS + 116);
	mRHSrow106 = vec_xl(0, mRHS + 118);

	// column 11
	mRHSrow111 = vec_xl(0, mRHS + 120);
	mRHSrow112 = vec_xl(0, mRHS + 122);
	mRHSrow113 = vec_xl(0, mRHS + 124);
	mRHSrow114 = vec_xl(0, mRHS + 126);
	mRHSrow115 = vec_xl(0, mRHS + 128);
	mRHSrow116 = vec_xl(0, mRHS + 130);

	// column 12
	mRHSrow121 = vec_xl(0, mRHS + 132);
	mRHSrow122 = vec_xl(0, mRHS + 134);
	mRHSrow123 = vec_xl(0, mRHS + 136);
	mRHSrow124 = vec_xl(0, mRHS + 138);
	mRHSrow125 = vec_xl(0, mRHS + 140);
	mRHSrow126 = vec_xl(0, mRHS + 142);

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
}

//====================================================================================================//
//Divide And Conquer - Matrix Size 2^n by 2^n, where n>=1 .
//====================================================================================================//

template <typename T>
inline void Mul2x2(T* lhs, T* rhs, T* res, int SIZE){
	
	res[0] += lhs[0]*rhs[0] + lhs[1]*rhs[SIZE];

	res[1] += lhs[0]*rhs[1] + lhs[1]*rhs[SIZE+1];

	res[SIZE] += lhs[SIZE]*rhs[0] + lhs[SIZE+1]*rhs[SIZE];

	res[SIZE+1] += lhs[SIZE]*rhs[1] + lhs[SIZE+1]*rhs[SIZE+1];


}


template <typename t>
inline void conquer(t* lhs, t* rhs, t* res, int n, int N){

	if(n==2){
		
		Mul2x2(lhs, rhs, res, N);
	
	}

	else{
	
		int k=n/2;

		conquer(lhs, rhs, res,k ,N);
		conquer(lhs+k, rhs+N*k, res, k, N);


		conquer(lhs, rhs+k, res+k, k, N);
		conquer(lhs+k, rhs+k*N+k, res+k, k, N);


		conquer(lhs+N*k, rhs, res+k*N, k, N);
		conquer(lhs+k*N+k, rhs+k*N, res+k*N, k, N);
		

		conquer(lhs+N*k, rhs+k, res+k*N+k, k, N);
		conquer(lhs+k*N+k, rhs+k*N+k, res+k*N+k, k, N);
	}

}


#endif //IBM_SMUL_H
