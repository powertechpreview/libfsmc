#include <iostream>
#include <stdio.h>
#include <altivec.h>

void mul4x4(int boolean_mLHSisRowMajor, double* mLHS, double* mRHS, double* mResult)
{
        __vector double mLHScol11, mLHScol21, mLHScol31, mLHScol41,
                        mLHScol12, mLHScol22, mLHScol32, mLHScol42,
                        mRHSrow11, mRHSrow21, mRHSrow31, mRHSrow41,
                        mRHSrow12, mRHSrow22, mRHSrow32, mRHSrow42;

        if (boolean_mLHSisRowMajor)
        {
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
        }
        else{
                mLHScol11 = vec_xl(0, mLHS);
                mLHScol12 = vec_xl(0, mLHS + 2);

                mLHScol21 = vec_xl(0, mLHS + 4);
                mLHScol22 = vec_xl(0, mLHS + 6);

                mLHScol31 = vec_xl(0, mLHS + 8);
                mLHScol32 = vec_xl(0, mLHS + 10);

                mLHScol41 = vec_xl(0, mLHS + 12);
                mLHScol42 = vec_xl(0, mLHS + 14);
        }

        mRHSrow11 = vec_xl(0, mRHS);
        mRHSrow12 = vec_xl(0, mRHS + 2);

        mRHSrow21 = vec_xl(0, mRHS + 4);
        mRHSrow22 = vec_xl(0, mRHS + 6);

        mRHSrow31 = vec_xl(0, mRHS + 8);
        mRHSrow32 = vec_xl(0, mRHS + 10);

        mRHSrow41 = vec_xl(0, mRHS + 12);
        mRHSrow42 = vec_xl(0, mRHS + 14);

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

int main()
{
        double *mLHS {new double[16]}, *mRHS {new double[16]}, *mResult {new double[16]};
        int boolean_mLHSisRowMajor {1};

        //==========//
        //initialization test
        for (auto i = 0; i < 16; ++i)
        {
                mLHS[i] = i + 1;
                mRHS[i] = i + 1;
        }
        //==========//

        //basic test
        mul4x4(boolean_mLHSisRowMajor, mLHS, mRHS, mResult);

        printf("\n%.2f %.2f %.2f %.2f\n", mLHS[0], mLHS[1], mLHS[2], mLHS[3]);
        printf("%.2f %.2f %.2f %.2f\n", mLHS[4], mLHS[5], mLHS[6], mLHS[7]);
        printf("%.2f %.2f %.2f %.2f\n", mLHS[8], mLHS[9], mLHS[10], mLHS[11]);
        printf("%.2f %.2f %.2f %.2f\n", mLHS[12], mLHS[13], mLHS[14], mLHS[15]);

        printf("\n%.2f %.2f %.2f %.2f\n", mRHS[0], mRHS[1], mRHS[2], mRHS[3]);
        printf("%.2f %.2f %.2f %.2f\n", mRHS[4], mRHS[5], mRHS[6], mRHS[7]);
        printf("%.2f %.2f %.2f %.2f\n", mRHS[8], mRHS[9], mRHS[10], mRHS[11]);
        printf("%.2f %.2f %.2f %.2f\n", mRHS[12], mRHS[13], mRHS[14], mRHS[15]);

        printf("\n%.2f %.2f %.2f %.2f\n", mResult[0], mResult[1], mResult[2], mResult[3]);
        printf("%.2f %.2f %.2f %.2f\n", mResult[4], mResult[5], mResult[6], mResult[7]);
        printf("%.2f %.2f %.2f %.2f\n", mResult[8], mResult[9], mResult[10], mResult[11]);
        printf("%.2f %.2f %.2f %.2f\n", mResult[12], mResult[13], mResult[14], mResult[15]);

        return 0;
}
