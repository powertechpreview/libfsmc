#include <iostream>
#include <stdio.h>
#include <altivec.h>

void mul8x8(int boolean_mLHSisRowMajor, double* mLHS, double* mRHS, double* mResult)
{
        __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41, mLHScol51, mLHScol61, mLHScol71, mLHScol81,
                        mLHScol12, mLHScol22, mLHScol32, mLHScol42, mLHScol52, mLHScol62, mLHScol72, mLHScol82,
                        mLHScol13, mLHScol23, mLHScol33, mLHScol43, mLHScol53, mLHScol63, mLHScol73, mLHScol83,
                        mLHScol14, mLHScol24, mLHScol34, mLHScol44, mLHScol54, mLHScol64, mLHScol74, mLHScol84,
                        mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41, mRHSrow51, mRHSrow61, mRHSrow71, mRHSrow81,
                        mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42, mRHSrow52, mRHSrow62, mRHSrow72, mRHSrow82,
                        mRHSrow13, mRHSrow23, mRHSrow33, mRHSrow43, mRHSrow53, mRHSrow63, mRHSrow73, mRHSrow83,
                        mRHSrow14, mRHSrow24, mRHSrow34, mRHSrow44, mRHSrow54, mRHSrow64, mRHSrow74, mRHSrow84;

        if (boolean_mLHSisRowMajor)
        {
                //{ [a11 a12 a13 a14 a15 a16 a17 a18], [a21 a22 a23 a24 a25 a26 a27 a28], [a31 a32 a33 a34 a35 a36 a37 a38], [a41 a42 a43 a44 a45 a46 a47 a48],
                //  [a51 a52 a53 a54 a55 a56 a57 a58], [a61 a62 a63 a64 a65 a66 a67 a68], [a71 a72 a73 a74 a75 a76 a77 a78], [a81 a82 a83 a84 a85 a86 a87 a88]}

                const static __vector unsigned char GETCOL1 = { 0, 1, 2, 3, 4, 5, 6, 7,
                                                                 16, 17, 18, 19, 20, 21, 22, 23};

                const static __vector unsigned char GETCOL2 = { 8, 9, 10, 11, 12, 13, 14, 15,
                                                                 24, 25, 26, 27, 28, 29, 30, 31};
                //==================================================//
                __vector double mLHSaux1 = vec_xl(0, mLHS);
                __vector double mLHSaux2 = vec_xl(0, mLHS + 8);
                mLHScol11 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol21 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 2);
                mLHSaux2 = vec_xl(0, mLHS + 10);
                mLHScol31 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol41 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 4);
                mLHSaux2 = vec_xl(0, mLHS + 12);
                mLHScol51 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol61 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 6);
                mLHSaux2 = vec_xl(0, mLHS + 14);
                mLHScol71 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol81 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                //==================================================//
                mLHSaux1 = vec_xl(0, mLHS + 16);
                mLHSaux2 = vec_xl(0, mLHS + 24);
                mLHScol12 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol22 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 18);
                mLHSaux2 = vec_xl(0, mLHS + 26);
                mLHScol32 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol42 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 20);
                mLHSaux2 = vec_xl(0, mLHS + 28);
                mLHScol52 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol62 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 22);
                mLHSaux2 = vec_xl(0, mLHS + 30);
                mLHScol72 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol82 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                //==================================================//
                mLHSaux1 = vec_xl(0, mLHS + 32);
                mLHSaux2 = vec_xl(0, mLHS + 40);
                mLHScol13 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol23 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 34);
                mLHSaux2 = vec_xl(0, mLHS + 42);
                mLHScol33 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol43 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 36);
                mLHSaux2 = vec_xl(0, mLHS + 44);
                mLHScol53 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol63 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 38);
                mLHSaux2 = vec_xl(0, mLHS + 46);
                mLHScol73 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol83 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                //==================================================//
                mLHSaux1 = vec_xl(0, mLHS + 48);
                mLHSaux2 = vec_xl(0, mLHS + 56);
                mLHScol14 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol24 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 50);
                mLHSaux2 = vec_xl(0, mLHS + 58);
                mLHScol34 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol44 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 52);
                mLHSaux2 = vec_xl(0, mLHS + 60);
                mLHScol54 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol64 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);

                mLHSaux1 = vec_xl(0, mLHS + 54);
                mLHSaux2 = vec_xl(0, mLHS + 62);
                mLHScol74 = vec_perm(mLHSaux1, mLHSaux2, GETCOL1);
                mLHScol84 = vec_perm(mLHSaux1, mLHSaux2, GETCOL2);
        }
        else{
                mLHScol11 = vec_xl(0, mLHS);
                mLHScol12 = vec_xl(0, mLHS + 2);
                mLHScol13 = vec_xl(0, mLHS + 4);
                mLHScol14 = vec_xl(0, mLHS + 6);

                mLHScol21 = vec_xl(0, mLHS + 8);
                mLHScol22 = vec_xl(0, mLHS + 10);
                mLHScol23 = vec_xl(0, mLHS + 12);
                mLHScol24 = vec_xl(0, mLHS + 14);

                mLHScol31 = vec_xl(0, mLHS + 16);
                mLHScol32 = vec_xl(0, mLHS + 18);
                mLHScol33 = vec_xl(0, mLHS + 20);
                mLHScol34 = vec_xl(0, mLHS + 22);

                mLHScol41 = vec_xl(0, mLHS + 24);
                mLHScol42 = vec_xl(0, mLHS + 26);
                mLHScol43 = vec_xl(0, mLHS + 28);
                mLHScol44 = vec_xl(0, mLHS + 30);

                mLHScol51 = vec_xl(0, mLHS + 32);
                mLHScol52 = vec_xl(0, mLHS + 34);
                mLHScol53 = vec_xl(0, mLHS + 36);
                mLHScol54 = vec_xl(0, mLHS + 38);

                mLHScol61 = vec_xl(0, mLHS + 40);
                mLHScol62 = vec_xl(0, mLHS + 42);
                mLHScol63 = vec_xl(0, mLHS + 44);
                mLHScol64 = vec_xl(0, mLHS + 46);

                mLHScol71 = vec_xl(0, mLHS + 48);
                mLHScol72 = vec_xl(0, mLHS + 50);
                mLHScol73 = vec_xl(0, mLHS + 52);
                mLHScol74 = vec_xl(0, mLHS + 54);

                mLHScol81 = vec_xl(0, mLHS + 56);
                mLHScol82 = vec_xl(0, mLHS + 58);
                mLHScol83 = vec_xl(0, mLHS + 60);
                mLHScol84 = vec_xl(0, mLHS + 62);
        }

        mRHSrow11 = vec_xl(0, mRHS);
        mRHSrow12 = vec_xl(0, mRHS + 2);
        mRHSrow13 = vec_xl(0, mRHS + 4);
        mRHSrow14 = vec_xl(0, mRHS + 6);

        mRHSrow21 = vec_xl(0, mRHS + 8);
        mRHSrow22 = vec_xl(0, mRHS + 10);
        mRHSrow23 = vec_xl(0, mRHS + 12);
        mRHSrow24 = vec_xl(0, mRHS + 14);

        mRHSrow31 = vec_xl(0, mRHS + 16);
        mRHSrow32 = vec_xl(0, mRHS + 18);
        mRHSrow33 = vec_xl(0, mRHS + 20);
        mRHSrow34 = vec_xl(0, mRHS + 22);

        mRHSrow41 = vec_xl(0, mRHS + 24);
        mRHSrow42 = vec_xl(0, mRHS + 26);
        mRHSrow43 = vec_xl(0, mRHS + 28);
        mRHSrow44 = vec_xl(0, mRHS + 30);

        mRHSrow51 = vec_xl(0, mRHS + 32);
        mRHSrow52 = vec_xl(0, mRHS + 34);
        mRHSrow53 = vec_xl(0, mRHS + 36);
        mRHSrow54 = vec_xl(0, mRHS + 38);

        mRHSrow61 = vec_xl(0, mRHS + 40);
        mRHSrow62 = vec_xl(0, mRHS + 42);
        mRHSrow63 = vec_xl(0, mRHS + 44);
        mRHSrow64 = vec_xl(0, mRHS + 46);

        mRHSrow71 = vec_xl(0, mRHS + 48);
        mRHSrow72 = vec_xl(0, mRHS + 50);
        mRHSrow73 = vec_xl(0, mRHS + 52);
        mRHSrow74 = vec_xl(0, mRHS + 54);

        mRHSrow81 = vec_xl(0, mRHS + 56);
        mRHSrow82 = vec_xl(0, mRHS + 58);
        mRHSrow83 = vec_xl(0, mRHS + 60);
        mRHSrow84 = vec_xl(0, mRHS + 62);

        __vector double vAuxLHS11 = {mLHScol11[0], mLHScol11[0]};
        __vector double vAuxLHS12 = {mLHScol11[1], mLHScol11[1]};
        __vector double vAuxLHS13 = {mLHScol12[0], mLHScol12[0]};
        __vector double vAuxLHS14 = {mLHScol12[1], mLHScol12[1]};
        __vector double vAuxLHS15 = {mLHScol13[0], mLHScol13[0]};
        __vector double vAuxLHS16 = {mLHScol13[1], mLHScol13[1]};
        __vector double vAuxLHS17 = {mLHScol14[0], mLHScol14[0]};
        __vector double vAuxLHS18 = {mLHScol14[1], mLHScol14[1]};

        __vector double vAuxLHS21 = {mLHScol21[0], mLHScol21[0]};
        __vector double vAuxLHS22 = {mLHScol21[1], mLHScol21[1]};
        __vector double vAuxLHS23 = {mLHScol22[0], mLHScol22[0]};
        __vector double vAuxLHS24 = {mLHScol22[1], mLHScol22[1]};
        __vector double vAuxLHS25 = {mLHScol23[0], mLHScol23[0]};
        __vector double vAuxLHS26 = {mLHScol23[1], mLHScol23[1]};
        __vector double vAuxLHS27 = {mLHScol24[0], mLHScol24[0]};
        __vector double vAuxLHS28 = {mLHScol24[1], mLHScol24[1]};

        __vector double vAuxLHS31 = {mLHScol31[0], mLHScol31[0]};
        __vector double vAuxLHS32 = {mLHScol31[1], mLHScol31[1]};
        __vector double vAuxLHS33 = {mLHScol32[0], mLHScol32[0]};
        __vector double vAuxLHS34 = {mLHScol32[1], mLHScol32[1]};
        __vector double vAuxLHS35 = {mLHScol33[0], mLHScol33[0]};
        __vector double vAuxLHS36 = {mLHScol33[1], mLHScol33[1]};
        __vector double vAuxLHS37 = {mLHScol34[0], mLHScol34[0]};
        __vector double vAuxLHS38 = {mLHScol34[1], mLHScol34[1]};

        __vector double vAuxLHS41 = {mLHScol41[0], mLHScol41[0]};
        __vector double vAuxLHS42 = {mLHScol41[1], mLHScol41[1]};
        __vector double vAuxLHS43 = {mLHScol42[0], mLHScol42[0]};
        __vector double vAuxLHS44 = {mLHScol42[1], mLHScol42[1]};
        __vector double vAuxLHS45 = {mLHScol43[0], mLHScol43[0]};
        __vector double vAuxLHS46 = {mLHScol43[1], mLHScol43[1]};
        __vector double vAuxLHS47 = {mLHScol44[0], mLHScol44[0]};
        __vector double vAuxLHS48 = {mLHScol44[1], mLHScol44[1]};

        __vector double vAuxLHS51 = {mLHScol51[0], mLHScol51[0]};
        __vector double vAuxLHS52 = {mLHScol51[1], mLHScol51[1]};
        __vector double vAuxLHS53 = {mLHScol52[0], mLHScol52[0]};
        __vector double vAuxLHS54 = {mLHScol52[1], mLHScol52[1]};
        __vector double vAuxLHS55 = {mLHScol53[0], mLHScol53[0]};
        __vector double vAuxLHS56 = {mLHScol53[1], mLHScol53[1]};
        __vector double vAuxLHS57 = {mLHScol54[0], mLHScol54[0]};
        __vector double vAuxLHS58 = {mLHScol54[1], mLHScol54[1]};

        __vector double vAuxLHS61 = {mLHScol61[0], mLHScol61[0]};
        __vector double vAuxLHS62 = {mLHScol61[1], mLHScol61[1]};
        __vector double vAuxLHS63 = {mLHScol62[0], mLHScol62[0]};
        __vector double vAuxLHS64 = {mLHScol62[1], mLHScol62[1]};
        __vector double vAuxLHS65 = {mLHScol63[0], mLHScol63[0]};
        __vector double vAuxLHS66 = {mLHScol63[1], mLHScol63[1]};
        __vector double vAuxLHS67 = {mLHScol64[0], mLHScol64[0]};
        __vector double vAuxLHS68 = {mLHScol64[1], mLHScol64[1]};

        __vector double vAuxLHS71 = {mLHScol71[0], mLHScol71[0]};
        __vector double vAuxLHS72 = {mLHScol71[1], mLHScol71[1]};
        __vector double vAuxLHS73 = {mLHScol72[0], mLHScol72[0]};
        __vector double vAuxLHS74 = {mLHScol72[1], mLHScol72[1]};
        __vector double vAuxLHS75 = {mLHScol73[0], mLHScol73[0]};
        __vector double vAuxLHS76 = {mLHScol73[1], mLHScol73[1]};
        __vector double vAuxLHS77 = {mLHScol74[0], mLHScol74[0]};
        __vector double vAuxLHS78 = {mLHScol74[1], mLHScol74[1]};

        __vector double vAuxLHS81 = {mLHScol81[0], mLHScol81[0]};
        __vector double vAuxLHS82 = {mLHScol81[1], mLHScol81[1]};
        __vector double vAuxLHS83 = {mLHScol82[0], mLHScol82[0]};
        __vector double vAuxLHS84 = {mLHScol82[1], mLHScol82[1]};
        __vector double vAuxLHS85 = {mLHScol83[0], mLHScol83[0]};
        __vector double vAuxLHS86 = {mLHScol83[1], mLHScol83[1]};
        __vector double vAuxLHS87 = {mLHScol84[0], mLHScol84[0]};
        __vector double vAuxLHS88 = {mLHScol84[1], mLHScol84[1]};

        //building the first row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS21, vec_mul(mRHSrow11, vAuxLHS11)),
                                vec_madd(mRHSrow41, vAuxLHS41, vec_mul(mRHSrow31, vAuxLHS31)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS61, vec_mul(mRHSrow51, vAuxLHS51)),
                                vec_madd(mRHSrow81, vAuxLHS81, vec_mul(mRHSrow71, vAuxLHS71)) ) ),
                0, mResult);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS21, vec_mul(mRHSrow12, vAuxLHS11)),
                                vec_madd(mRHSrow42, vAuxLHS41, vec_mul(mRHSrow32, vAuxLHS31)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS61, vec_mul(mRHSrow52, vAuxLHS51)),
                                vec_madd(mRHSrow82, vAuxLHS81, vec_mul(mRHSrow72, vAuxLHS71)) ) ),
                0, mResult + 2);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS21, vec_mul(mRHSrow13, vAuxLHS11)),
                                vec_madd(mRHSrow43, vAuxLHS41, vec_mul(mRHSrow33, vAuxLHS31)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS61, vec_mul(mRHSrow53, vAuxLHS51)),
                                vec_madd(mRHSrow83, vAuxLHS81, vec_mul(mRHSrow73, vAuxLHS71)) ) ),
                0, mResult + 4);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS21, vec_mul(mRHSrow14, vAuxLHS11)),
                                vec_madd(mRHSrow44, vAuxLHS41, vec_mul(mRHSrow34, vAuxLHS31)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS61, vec_mul(mRHSrow54, vAuxLHS51)),
                                vec_madd(mRHSrow84, vAuxLHS81, vec_mul(mRHSrow74, vAuxLHS71)) ) ),
                0, mResult + 6);
        //building the second row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS22, vec_mul(mRHSrow11, vAuxLHS12)),
                                vec_madd(mRHSrow41, vAuxLHS42, vec_mul(mRHSrow31, vAuxLHS32)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS62, vec_mul(mRHSrow51, vAuxLHS52)),
                                vec_madd(mRHSrow81, vAuxLHS82, vec_mul(mRHSrow71, vAuxLHS72)) ) ),
                0, mResult + 8);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS22, vec_mul(mRHSrow12, vAuxLHS12)),
                                vec_madd(mRHSrow42, vAuxLHS42, vec_mul(mRHSrow32, vAuxLHS32)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS62, vec_mul(mRHSrow52, vAuxLHS52)),
                                vec_madd(mRHSrow82, vAuxLHS82, vec_mul(mRHSrow72, vAuxLHS72)) ) ),
                0, mResult + 10);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS22, vec_mul(mRHSrow13, vAuxLHS12)),
                                vec_madd(mRHSrow43, vAuxLHS42, vec_mul(mRHSrow33, vAuxLHS32)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS62, vec_mul(mRHSrow53, vAuxLHS52)),
                                vec_madd(mRHSrow83, vAuxLHS82, vec_mul(mRHSrow73, vAuxLHS72)) ) ),
                0, mResult + 12);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS22, vec_mul(mRHSrow14, vAuxLHS12)),
                                vec_madd(mRHSrow44, vAuxLHS42, vec_mul(mRHSrow34, vAuxLHS32)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS62, vec_mul(mRHSrow54, vAuxLHS52)),
                                vec_madd(mRHSrow84, vAuxLHS82, vec_mul(mRHSrow74, vAuxLHS72)) ) ),
                0, mResult + 14);
        //building the third row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS23, vec_mul(mRHSrow11, vAuxLHS13)),
                                vec_madd(mRHSrow41, vAuxLHS43, vec_mul(mRHSrow31, vAuxLHS33)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS63, vec_mul(mRHSrow51, vAuxLHS53)),
                                vec_madd(mRHSrow81, vAuxLHS83, vec_mul(mRHSrow71, vAuxLHS73)) ) ),
                0, mResult + 16);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS23, vec_mul(mRHSrow12, vAuxLHS13)),
                                vec_madd(mRHSrow42, vAuxLHS43, vec_mul(mRHSrow32, vAuxLHS33)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS63, vec_mul(mRHSrow52, vAuxLHS53)),
                                vec_madd(mRHSrow82, vAuxLHS83, vec_mul(mRHSrow72, vAuxLHS73)) ) ),
                0, mResult + 18);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS23, vec_mul(mRHSrow13, vAuxLHS13)),
                                vec_madd(mRHSrow43, vAuxLHS43, vec_mul(mRHSrow33, vAuxLHS33)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS63, vec_mul(mRHSrow53, vAuxLHS53)),
                                vec_madd(mRHSrow83, vAuxLHS83, vec_mul(mRHSrow73, vAuxLHS73)) ) ),
                0, mResult + 20);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS23, vec_mul(mRHSrow14, vAuxLHS13)),
                                vec_madd(mRHSrow44, vAuxLHS43, vec_mul(mRHSrow34, vAuxLHS33)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS63, vec_mul(mRHSrow54, vAuxLHS53)),
                                vec_madd(mRHSrow84, vAuxLHS83, vec_mul(mRHSrow74, vAuxLHS73)) ) ),
                0, mResult + 22);
        //building the fourth row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS24, vec_mul(mRHSrow11, vAuxLHS14)),
                                vec_madd(mRHSrow41, vAuxLHS44, vec_mul(mRHSrow31, vAuxLHS34)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS64, vec_mul(mRHSrow51, vAuxLHS54)),
                                vec_madd(mRHSrow81, vAuxLHS84, vec_mul(mRHSrow71, vAuxLHS74)) ) ),
                0, mResult + 24);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS24, vec_mul(mRHSrow12, vAuxLHS14)),
                                vec_madd(mRHSrow42, vAuxLHS44, vec_mul(mRHSrow32, vAuxLHS34)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS64, vec_mul(mRHSrow52, vAuxLHS54)),
                                vec_madd(mRHSrow82, vAuxLHS84, vec_mul(mRHSrow72, vAuxLHS74)) ) ),
                0, mResult + 26);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS24, vec_mul(mRHSrow13, vAuxLHS14)),
                                vec_madd(mRHSrow43, vAuxLHS44, vec_mul(mRHSrow33, vAuxLHS34)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS64, vec_mul(mRHSrow53, vAuxLHS54)),
                                vec_madd(mRHSrow83, vAuxLHS84, vec_mul(mRHSrow73, vAuxLHS74)) ) ),
                0, mResult + 28);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS24, vec_mul(mRHSrow14, vAuxLHS14)),
                                vec_madd(mRHSrow44, vAuxLHS44, vec_mul(mRHSrow34, vAuxLHS34)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS64, vec_mul(mRHSrow54, vAuxLHS54)),
                                vec_madd(mRHSrow84, vAuxLHS84, vec_mul(mRHSrow74, vAuxLHS74)) ) ),
                0, mResult + 30);
        //building the fifth row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS25, vec_mul(mRHSrow11, vAuxLHS15)),
                                vec_madd(mRHSrow41, vAuxLHS45, vec_mul(mRHSrow31, vAuxLHS35)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS65, vec_mul(mRHSrow51, vAuxLHS55)),
                                vec_madd(mRHSrow81, vAuxLHS85, vec_mul(mRHSrow71, vAuxLHS75)) ) ),
                0, mResult + 32);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS25, vec_mul(mRHSrow12, vAuxLHS15)),
                                vec_madd(mRHSrow42, vAuxLHS45, vec_mul(mRHSrow32, vAuxLHS35)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS65, vec_mul(mRHSrow52, vAuxLHS55)),
                                vec_madd(mRHSrow82, vAuxLHS85, vec_mul(mRHSrow72, vAuxLHS75)) ) ),
                0, mResult + 34);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS25, vec_mul(mRHSrow13, vAuxLHS15)),
                                vec_madd(mRHSrow43, vAuxLHS45, vec_mul(mRHSrow33, vAuxLHS35)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS65, vec_mul(mRHSrow53, vAuxLHS55)),
                                vec_madd(mRHSrow83, vAuxLHS85, vec_mul(mRHSrow73, vAuxLHS75)) ) ),
                0, mResult + 36);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS25, vec_mul(mRHSrow14, vAuxLHS15)),
                                vec_madd(mRHSrow44, vAuxLHS45, vec_mul(mRHSrow34, vAuxLHS35)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS65, vec_mul(mRHSrow54, vAuxLHS55)),
                                vec_madd(mRHSrow84, vAuxLHS85, vec_mul(mRHSrow74, vAuxLHS75)) ) ),
                0, mResult + 38);
        //building the sixth row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS26, vec_mul(mRHSrow11, vAuxLHS16)),
                                vec_madd(mRHSrow41, vAuxLHS46, vec_mul(mRHSrow31, vAuxLHS36)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS66, vec_mul(mRHSrow51, vAuxLHS56)),
                                vec_madd(mRHSrow81, vAuxLHS86, vec_mul(mRHSrow71, vAuxLHS76)) ) ),
                0, mResult + 40);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS26, vec_mul(mRHSrow12, vAuxLHS16)),
                                vec_madd(mRHSrow42, vAuxLHS46, vec_mul(mRHSrow32, vAuxLHS36)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS66, vec_mul(mRHSrow52, vAuxLHS56)),
                                vec_madd(mRHSrow82, vAuxLHS86, vec_mul(mRHSrow72, vAuxLHS76)) ) ),
                0, mResult + 42);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS26, vec_mul(mRHSrow13, vAuxLHS16)),
                                vec_madd(mRHSrow43, vAuxLHS46, vec_mul(mRHSrow33, vAuxLHS36)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS66, vec_mul(mRHSrow53, vAuxLHS56)),
                                vec_madd(mRHSrow83, vAuxLHS86, vec_mul(mRHSrow73, vAuxLHS76)) ) ),
                0, mResult + 44);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS26, vec_mul(mRHSrow14, vAuxLHS16)),
                                vec_madd(mRHSrow44, vAuxLHS46, vec_mul(mRHSrow34, vAuxLHS36)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS66, vec_mul(mRHSrow54, vAuxLHS56)),
                                vec_madd(mRHSrow84, vAuxLHS86, vec_mul(mRHSrow74, vAuxLHS76)) ) ),
                0, mResult + 46);
        //building the seventh row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS27, vec_mul(mRHSrow11, vAuxLHS17)),
                                vec_madd(mRHSrow41, vAuxLHS47, vec_mul(mRHSrow31, vAuxLHS37)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS67, vec_mul(mRHSrow51, vAuxLHS57)),
                                vec_madd(mRHSrow81, vAuxLHS87, vec_mul(mRHSrow71, vAuxLHS77)) ) ),
                0, mResult + 48);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS27, vec_mul(mRHSrow12, vAuxLHS17)),
                                vec_madd(mRHSrow42, vAuxLHS47, vec_mul(mRHSrow32, vAuxLHS37)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS67, vec_mul(mRHSrow52, vAuxLHS57)),
                                vec_madd(mRHSrow82, vAuxLHS87, vec_mul(mRHSrow72, vAuxLHS77)) ) ),
                0, mResult + 50);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS27, vec_mul(mRHSrow13, vAuxLHS17)),
                                vec_madd(mRHSrow43, vAuxLHS47, vec_mul(mRHSrow33, vAuxLHS37)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS67, vec_mul(mRHSrow53, vAuxLHS57)),
                                vec_madd(mRHSrow83, vAuxLHS87, vec_mul(mRHSrow73, vAuxLHS77)) ) ),
                0, mResult + 52);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS27, vec_mul(mRHSrow14, vAuxLHS17)),
                                vec_madd(mRHSrow44, vAuxLHS47, vec_mul(mRHSrow34, vAuxLHS37)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS67, vec_mul(mRHSrow54, vAuxLHS57)),
                                vec_madd(mRHSrow84, vAuxLHS87, vec_mul(mRHSrow74, vAuxLHS77)) ) ),
                0, mResult + 54);
        //building the eigth row of mResult
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow21, vAuxLHS28, vec_mul(mRHSrow11, vAuxLHS18)),
                                vec_madd(mRHSrow41, vAuxLHS48, vec_mul(mRHSrow31, vAuxLHS38)) ),
                        vec_add(
                                vec_madd(mRHSrow61, vAuxLHS68, vec_mul(mRHSrow51, vAuxLHS58)),
                                vec_madd(mRHSrow81, vAuxLHS88, vec_mul(mRHSrow71, vAuxLHS78)) ) ),
                0, mResult + 56);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow22, vAuxLHS28, vec_mul(mRHSrow12, vAuxLHS18)),
                                vec_madd(mRHSrow42, vAuxLHS48, vec_mul(mRHSrow32, vAuxLHS38)) ),
                        vec_add(
                                vec_madd(mRHSrow62, vAuxLHS68, vec_mul(mRHSrow52, vAuxLHS58)),
                                vec_madd(mRHSrow82, vAuxLHS88, vec_mul(mRHSrow72, vAuxLHS78)) ) ),
                0, mResult + 58);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow23, vAuxLHS28, vec_mul(mRHSrow13, vAuxLHS18)),
                                vec_madd(mRHSrow43, vAuxLHS48, vec_mul(mRHSrow33, vAuxLHS38)) ),
                        vec_add(
                                vec_madd(mRHSrow63, vAuxLHS68, vec_mul(mRHSrow53, vAuxLHS58)),
                                vec_madd(mRHSrow83, vAuxLHS88, vec_mul(mRHSrow73, vAuxLHS78)) ) ),
                0, mResult + 60);
        vec_xst(vec_add(
                        vec_add(
                                vec_madd(mRHSrow24, vAuxLHS28, vec_mul(mRHSrow14, vAuxLHS18)),
                                vec_madd(mRHSrow44, vAuxLHS48, vec_mul(mRHSrow34, vAuxLHS38)) ),
                        vec_add(
                                vec_madd(mRHSrow64, vAuxLHS68, vec_mul(mRHSrow54, vAuxLHS58)),
                                vec_madd(mRHSrow84, vAuxLHS88, vec_mul(mRHSrow74, vAuxLHS78)) ) ),
                0, mResult + 62);
}

int main()
{
        double *mLHS {new double[64]}, *mRHS {new double[64]}, *mResult {new double[64]};
        int boolean_mLHSisRowMajor {1};

        //==========//
        //initialization test
        for (auto i = 0; i < 64; ++i)
        {
                mLHS[i] = (double)(i + 1);
                mRHS[i] = (double)(i + 1)/10;
        }
        //==========//

        //basic test
        mul8x8(boolean_mLHSisRowMajor, mLHS, mRHS, mResult);

        printf("\n%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[0], mLHS[1], mLHS[2], mLHS[3], mLHS[4], mLHS[5], mLHS[6], mLHS[7]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[8], mLHS[9], mLHS[10], mLHS[11], mLHS[12], mLHS[13], mLHS[14], mLHS[15]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[16], mLHS[17], mLHS[18], mLHS[19], mLHS[20], mLHS[21], mLHS[22], mLHS[23]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[24], mLHS[25], mLHS[26], mLHS[27], mLHS[28], mLHS[29], mLHS[30], mLHS[31]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[32], mLHS[33], mLHS[34], mLHS[35], mLHS[36], mLHS[37], mLHS[38], mLHS[39]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[40], mLHS[41], mLHS[42], mLHS[43], mLHS[44], mLHS[45], mLHS[46], mLHS[47]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[48], mLHS[49], mLHS[50], mLHS[51], mLHS[52], mLHS[53], mLHS[54], mLHS[55]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mLHS[56], mLHS[57], mLHS[58], mLHS[59], mLHS[60], mLHS[61], mLHS[62], mLHS[63]);

        printf("\n%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[0], mRHS[1], mRHS[2], mRHS[3], mRHS[4], mRHS[5], mRHS[6], mRHS[7]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[8], mRHS[9], mRHS[10], mRHS[11], mRHS[12], mRHS[13], mRHS[14], mRHS[15]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[16], mRHS[17], mRHS[18], mRHS[19], mRHS[20], mRHS[21], mRHS[22], mRHS[23]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[24], mRHS[25], mRHS[26], mRHS[27], mRHS[28], mRHS[29], mRHS[30], mRHS[31]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[32], mRHS[33], mRHS[34], mRHS[35], mRHS[36], mRHS[37], mRHS[38], mRHS[39]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[40], mRHS[41], mRHS[42], mRHS[43], mRHS[44], mRHS[45], mRHS[46], mRHS[47]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[48], mRHS[49], mRHS[50], mRHS[51], mRHS[52], mRHS[53], mRHS[54], mRHS[55]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mRHS[56], mRHS[57], mRHS[58], mRHS[59], mRHS[60], mRHS[61], mRHS[62], mRHS[63]);

        printf("\n%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[0], mResult[1], mResult[2], mResult[3], mResult[4], mResult[5], mResult[6], mResult[7]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[8], mResult[9], mResult[10], mResult[11], mResult[12], mResult[13], mResult[14], mResult[15]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[16], mResult[17], mResult[18], mResult[19], mResult[20], mResult[21], mResult[22], mResult[23]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[24], mResult[25], mResult[26], mResult[27], mResult[28], mResult[29], mResult[30], mResult[31]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[32], mResult[33], mResult[34], mResult[35], mResult[36], mResult[37], mResult[38], mResult[39]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[40], mResult[41], mResult[42], mResult[43], mResult[44], mResult[45], mResult[46], mResult[47]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[48], mResult[49], mResult[50], mResult[51], mResult[52], mResult[53], mResult[54], mResult[55]);
        printf("%.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f    %.2f\n", mResult[56], mResult[57], mResult[58], mResult[59], mResult[60], mResult[61], mResult[62], mResult[63]);

        return 0;
}
