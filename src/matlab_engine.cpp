#include "engine.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char **argv) {
    mxArray *X = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray *Y = mxCreateDoubleMatrix(1, 1, mxREAL);

    double *ptrToMatX = reinterpret_cast<double *>(mxGetData(X));
    double *ptrToMatY = reinterpret_cast<double *>(mxGetData(Y));

    ptrToMatX[0] = 1;
    ptrToMatY[0] = 2;

    engine *ep;
    if (!(ep = engOpen("\0"))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        return EXIT_FAILURE;
    }
    engPutVariable(ep, "X", X);
    engPutVariable(ep, "Y", Y);

    engEvalString(ep, "Z = test_function(X, Y)");

    mxArray *Z = engGetVariable(ep, "Z");
    double *ptrToMatZ = reinterpret_cast<double *>(mxGetData(Z));
    std::cout << "result is " << *ptrToMatZ << std::endl;

    return EXIT_SUCCESS;
}
