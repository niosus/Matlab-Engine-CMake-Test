#include "engine.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char **argv) {
    // Create arrays of Matlab type
    mxArray *X = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray *Y = mxCreateDoubleMatrix(1, 1, mxREAL);

    // Matlab arrays --> double arrays
    double *ptrToMatX = reinterpret_cast<double *>(mxGetData(X));
    double *ptrToMatY = reinterpret_cast<double *>(mxGetData(Y));

    // Manipulate ordinary c++ arrays
    ptrToMatX[0] = 1;
    ptrToMatY[0] = 2;

    // Start the Matlab Engine
    engine *ep;
    if (!(ep = engOpen("\0"))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        return EXIT_FAILURE;
    }

    // Copy the variables into Matlab prompt
    engPutVariable(ep, "X", X);
    engPutVariable(ep, "Y", Y);

    // Call the function
    engEvalString(ep, "Z = test_function(X, Y)");

    // Copy the variable from Matlab prompt to our code
    mxArray *Z = engGetVariable(ep, "Z");

    // Convert this variable to ordinary c++ array and show it
    double *ptrToMatZ = reinterpret_cast<double *>(mxGetData(Z));
    std::cout << "result is " << *ptrToMatZ << std::endl;

    return EXIT_SUCCESS;
}
