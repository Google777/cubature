# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

doHCubature <- function(fDim, f, xLL, xUL, maxEval, absErr, tol, vectorInterface, norm) {
    .Call('_cubature_doHCubature', PACKAGE = 'cubature', fDim, f, xLL, xUL, maxEval, absErr, tol, vectorInterface, norm)
}

doPCubature <- function(fDim, f, xLL, xUL, maxEval, absErr, tol, vectorInterface, norm) {
    .Call('_cubature_doPCubature', PACKAGE = 'cubature', fDim, f, xLL, xUL, maxEval, absErr, tol, vectorInterface, norm)
}

