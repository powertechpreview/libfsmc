#ifndef IBM_SMUL_H
#define IBM_SMUL_H

#include <iostream>
#include <stdio.h>
#include <altivec.h>


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


#endif //IBM_SMUL_H
