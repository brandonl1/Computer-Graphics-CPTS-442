#include <assert.h>

#include "basis.h"

const void BezierBasis::operator()(const double u,
    double bs[4], double (*db_dus)[4]) const
// returns the values of the 4 cubic Bezier basis functions, otherwise
// known as the Bernstein polynomials and (if `db_dus` is not NULL)
// their derivatives.
{
    //
    // ASSIGNMENT (PA07)
    //
    // Add code to evaluate the 4 Bernstein polynomials at `u` and
    // put the results in `bs[]`.
    //
    // If `db_dus` ("[d]erivative of [bs] with respect to u [du]"s) is
    // not NULL, set the 4 elements of the array it points at to the
    // derivatives of the polynomials with respect to `u`. (Remember
    // how to differentiate a polynomial?)
    //
    // You're welcome to look at
    // `UniformCubicBSplineBasis::operator()` as an example of the
    // way to lay out code, but remember that the coefficients are
    // different.
    //
    // 12 lines in instructor solution (YMMV)
    //
     double u2 = u*u;
     double u3 = u2*u;
     //
    // These are the bases ...
    //equations found from slides
    //
    
  bs[0]    = (1-3*u+3*u2-u3);
  bs[1]    = ( 3*u - 6*u2       + 3*u3);
  bs[2]    = (3 * u2 - 3*u3);
  bs[3]    = ( 1*u3                 );
      if (db_dus) {
        //
        // ... and these are their derivatives wrt u. (Notice how the
        // notation lets you confirm this by inspection.)
        //
        (*db_dus)[0] = (-3 +6*u - 3*u2);
        (*db_dus)[1] = ( 9*u2 - 12*u   +3 );
        (*db_dus)[2] = (-9*u2 +  6*u );
        (*db_dus)[3] = ( 3*u2           );
      
        
    }
    
}

const void UniformCubicBSplineBasis::operator()(
    const double u, double bs[4], double (*db_dus)[4]) const
//
// returns the values of the 4 uniform cubic (aka "N_3") B-spline
// basis functions and (if `db_dus` is not NULL) their derivatives.
// For the time being, we're leaving out the knot sequence details.
//
{
    //
    // These polynomials are a little more difficult to find, so I'll
    // just provide the solution. You can use it as a model for
    // BezierBasis.
    //
    double u2 = u*u;
    double u3 = u2*u;

    //
    // These are the bases ...
    //
    bs[0]    = (-1*u3 + 3*u2 - 3*u + 1) / 6.0;
    bs[1]    = ( 3*u3 - 6*u2       + 4) / 6.0;
    bs[2]    = (-3*u3 + 3*u2 + 3*u + 1) / 6.0;
    bs[3]    = ( 1*u3                 ) / 6.0;

    if (db_dus) {
        //
        // ... and these are their derivatives wrt u. (Notice how the
        // notation lets you confirm this by inspection.)
        //
        (*db_dus)[0] = (-3*u2 +  6*u - 3) / 6.0;
        (*db_dus)[1] = ( 9*u2 - 12*u    ) / 6.0;
        (*db_dus)[2] = (-9*u2 +  6*u + 3) / 6.0;
        (*db_dus)[3] = ( 3*u2           ) / 6.0;
    }
}
