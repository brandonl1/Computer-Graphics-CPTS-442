//
// This file will deal with all single-parametric curves.
//

#include "curve.h"
#include "geometry.h"
#include "poly_line.h"
#include "wrap_cmath_inclusion.h"


const void Curve::coordinateFrame(const double u,
                            Point3 &p, Vector3 &vU, Vector3 &vV, Vector3 &vW)
    const
{
    //
    // ASSIGNMENT (PA06)
    //
    // Set up a right-handed local coordinate system along the tube at
    // parameter value `u`. The origin of the coordinate system is `p`
    // and its three axes are `vU`, `vV`, and `vW`, all of unit length
    // and perpendicular to each other. `vW` will define the car's
    // direction of travel axis ("z"-like). `vV` is the "up" vector
    // that points above the rider's head ("y"-like). `vU` is the
    // remaining rider's left hand ("x"-like) vector.
    //
    // Make them in this order: Build `vW` from the tangent to the
    // curve. Make `vU` from `vW` and the given `vNeverParallel`. Make
    // `vV` from `vU` and `vW`.
    //
    // 8 lines in instructor solution (YMMV)
    //

    Vector3 tangent;
    p = (*this)(u, &tangent);
    vW = tangent.normalized();


    //make vU from vW and the given vNeverParallel
    Vector3 vuAns = tangent.cross(vNeverParallel);    

    vU = vuAns.normalized();


    // Make vV from vU and vW
    vV = vU.cross(vW);
    vV = vV.normalized();
}


const Point3 LineSegment::operator()(const double u, Vector3 *dp_du) const
{
    if (dp_du)
        (*dp_du) = p1 - p0;
    // simple linear interpolation of the endpoints
    return p0 + u * (p1 - p0);
}


const Point3 OffsetCurve::operator()(const double u, Vector3 *dp_du) const
{
    Point3 p;
    Vector3 v[3];
    (*frameCurve)(u, dp_du);
   
    frameCurve->coordinateFrame(u, p, v[0], v[1], v[2]);

    // This is actually a matrix operation
    return p
        + offset.a[0] * v[0]
        + offset.a[1] * v[1]
        + offset.a[2] * v[2];
}


const Point3 TrigonometricCurve::operator()(const double u,
                                            Vector3 *dp_du) const
//
// returns ths position of the curve at the parameter `u`
// (0 <= `u` <= 1).  If `dp_du` is not NULL, it will be set to the
// path derivative vector at `u`.
//
// Note: the path derivative is *not* normalized. If the components
// of the path had dimensions of length (i.e. the path was a
// position) and `u` had dimensions of time, the path derivative
// would be a velocity. If the caller wants a unit-length
// (dimensionless) tangent vector, it is up to them to normalize
// `dp_du` upon its return.
//
{
    //
    // ASSIGNMENT (PA06)
    //
    // Enhance your previous (PA02) solution to set `*dp_du` to the
    // path derivative as per the function header. Use your knowledge
    // of calculus to compute it.
    //
    // 10 lines in instructor solution (YMMV)
    //
   
    
    Vec3 angle = 2*M_PI *(freq * u + phase);
     double a = cos(angle.a[0])*mag.a[0];
     double b = cos(angle.a[1])*mag.a[1];
     double c = cos(angle.a[2])*mag.a[2];
    Point3 point(a,b,c);

    if(dp_du != NULL){
    	 double x =  2 * M_PI * -sin(angle.a[0]) * freq.a[0] * mag.a[0];
       	 double y =  2 * M_PI * -sin(angle.a[1]) * freq.a[1] * mag.a[1] ;
         double z =  2 * M_PI * -sin(angle.a[2]) * freq.a[2] * mag.a[2];
         dp_du->a[0] = x;
         dp_du->a[1] = y;
         dp_du->a[2] = z;
        }

    return point + offset; // replace (permits template to compile cleanly)
}

