#ifndef IBM_SMUL_H
#define IBM_SMUL_H

#include <iostream>
#include <stdio.h>
#include <altivec.h>


//====================================================================================================
inline void mul4x4RowMajor(const double* mLHS, const double* mRHS, double* const mResult)
{
    __vector double mLHSrow11, mLHSrow21, mLHSrow31, mLHSrow41,
                    mLHSrow12, mLHSrow22, mLHSrow32, mLHSrow42,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42;

    // row 1
    mLHSrow11 = vec_xl(0, mLHS);
    mLHSrow12 = vec_xl(0, mLHS + 2);

    // row 2
    mLHSrow21 = vec_xl(0, mLHS + 4);
    mLHSrow22 = vec_xl(0, mLHS + 6);

    // row 3
    mLHSrow31 = vec_xl(0, mLHS + 8);
    mLHSrow32 = vec_xl(0, mLHS + 10);

    // row 4
    mLHSrow41 = vec_xl(0, mLHS + 12);
    mLHSrow42 = vec_xl(0, mLHS + 14);

    // column 1
    __vector double vAuxLHS11 = {mLHSrow11[0], mLHSrow11[0]};
    __vector double vAuxLHS12 = {mLHSrow21[0], mLHSrow21[0]};
    __vector double vAuxLHS13 = {mLHSrow31[0], mLHSrow31[0]};
    __vector double vAuxLHS14 = {mLHSrow41[0], mLHSrow41[0]};

    // column 2
    __vector double vAuxLHS21 = {mLHSrow11[1], mLHSrow11[1]};
    __vector double vAuxLHS22 = {mLHSrow21[1], mLHSrow21[1]};
    __vector double vAuxLHS23 = {mLHSrow31[1], mLHSrow31[1]};
    __vector double vAuxLHS24 = {mLHSrow41[1], mLHSrow41[1]};

    // column 3
    __vector double vAuxLHS31 = {mLHSrow12[0], mLHSrow12[0]};
    __vector double vAuxLHS32 = {mLHSrow22[0], mLHSrow22[0]};
    __vector double vAuxLHS33 = {mLHSrow32[0], mLHSrow32[0]};
    __vector double vAuxLHS34 = {mLHSrow42[0], mLHSrow42[0]};

    // column 4
    __vector double vAuxLHS41 = {mLHSrow12[1], mLHSrow12[1]};
    __vector double vAuxLHS42 = {mLHSrow22[1], mLHSrow22[1]};
    __vector double vAuxLHS43 = {mLHSrow32[1], mLHSrow32[1]};
    __vector double vAuxLHS44 = {mLHSrow42[1], mLHSrow42[1]};

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
    __vector double mLHSrow11, mLHSrow21, mLHSrow31, mLHSrow41, mLHSrow51, mLHSrow61, mLHSrow71, mLHSrow81, mLHSrow91,
                    mLHSrow12, mLHSrow22, mLHSrow32, mLHSrow42, mLHSrow52, mLHSrow62, mLHSrow72, mLHSrow82, mLHSrow92,
                    mLHSrow13, mLHSrow23, mLHSrow33, mLHSrow43, mLHSrow53, mLHSrow63, mLHSrow73, mLHSrow83, mLHSrow93,
                    mLHSrow14, mLHSrow24, mLHSrow34, mLHSrow44, mLHSrow54, mLHSrow64, mLHSrow74, mLHSrow84, mLHSrow94,
                    mLHSrow15, mLHSrow25, mLHSrow35, mLHSrow45, mLHSrow55, mLHSrow65, mLHSrow75, mLHSrow85, mLHSrow95,
                    mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81, mRHSrow91,
                    mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82, mRHSrow92,
                    mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83, mRHSrow93,
                    mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84, mRHSrow94,
                    mRHSrow15, mRHSrow25, mRHSrow35, mRHSrow45, mRHSrow55, mRHSrow65, mRHSrow75, mRHSrow85, mRHSrow95;

    //{ [a11 a12 a13 a14 a15 a16 a17 a18 a19], [a21 a22 a23 a24 a25 a26 a27 a28 a29], [a31 a32 a33 a34 a35 a36 a37 a38 a39], [a41 a42 a43 a44 a45 a46 a47 a48 a49],
    //  [a51 a52 a53 a54 a55 a56 a57 a58 a59], [a61 a62 a63 a64 a65 a66 a67 a68 a69], [a71 a72 a73 a74 a75 a76 a77 a78 a79], [a81 a82 a83 a84 a85 a86 a87 a88 a89]}

    // row 1
    mLHSrow11 = vec_xl(0, mLHS);
    mLHSrow12 = vec_xl(0, mLHS + 2);
    mLHSrow13 = vec_xl(0, mLHS + 4);
    mLHSrow14 = vec_xl(0, mLHS + 6);
    mLHSrow15[0] = mLHS[8];
    // mLHSrow15[1] = 0

    // row 2
    mLHSrow21 = vec_xl(0, mLHS + 9);
    mLHSrow22 = vec_xl(0, mLHS + 11);
    mLHSrow23 = vec_xl(0, mLHS + 13);
    mLHSrow24 = vec_xl(0, mLHS + 15);
    mLHSrow25[0] = mLHS[17];
    // mLHSrow25[1] = 0

    // row 3
    mLHSrow31 = vec_xl(0, mLHS + 18);
    mLHSrow32 = vec_xl(0, mLHS + 20);
    mLHSrow33 = vec_xl(0, mLHS + 22);
    mLHSrow34 = vec_xl(0, mLHS + 24);
    mLHSrow35[0] = mLHS[26];
    // mLHSrow35[1] = 0

    // row 4
    mLHSrow41 = vec_xl(0, mLHS + 27);
    mLHSrow42 = vec_xl(0, mLHS + 29);
    mLHSrow43 = vec_xl(0, mLHS + 31);
    mLHSrow44 = vec_xl(0, mLHS + 33);
    mLHSrow45[0] = mLHS[35];
    // mLHSrow45[1] = 0

    // row 5
    mLHSrow51 = vec_xl(0, mLHS + 36);
    mLHSrow52 = vec_xl(0, mLHS + 38);
    mLHSrow53 = vec_xl(0, mLHS + 40);
    mLHSrow54 = vec_xl(0, mLHS + 42);
    mLHSrow55[0] = mLHS[44];
    // mLHSrow55[1] = 0

    // row 6
    mLHSrow61 = vec_xl(0, mLHS + 45);
    mLHSrow62 = vec_xl(0, mLHS + 47);
    mLHSrow63 = vec_xl(0, mLHS + 49);
    mLHSrow64 = vec_xl(0, mLHS + 51);
    mLHSrow65[0] = mLHS[53];
    // mLHSrow65[1] = 0

    // row 7
    mLHSrow71 = vec_xl(0, mLHS + 54);
    mLHSrow72 = vec_xl(0, mLHS + 56);
    mLHSrow73 = vec_xl(0, mLHS + 58);
    mLHSrow74 = vec_xl(0, mLHS + 60);
    mLHSrow75[0] = mLHS[62];
    // mLHSrow75[1] = 0

    // row 8
    mLHSrow81 = vec_xl(0, mLHS + 63);
    mLHSrow82 = vec_xl(0, mLHS + 65);
    mLHSrow83 = vec_xl(0, mLHS + 67);
    mLHSrow84 = vec_xl(0, mLHS + 69);
    mLHSrow85[0] = mLHS[71];
    // mLHSrow85[1] = 0

    // row 9
    mLHSrow91 = vec_xl(0, mLHS + 72);
    mLHSrow92 = vec_xl(0, mLHS + 74);
    mLHSrow93 = vec_xl(0, mLHS + 76);
    mLHSrow94 = vec_xl(0, mLHS + 78);
    mLHSrow95[0] = mLHS[80];
    // mLHSrow95[1] = 0

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

#endif //IBM_SMUL_H
