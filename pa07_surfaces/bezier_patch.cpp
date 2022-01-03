#include "bezier_patch.h"

const Point3 BezierPatch::operator()(const double u, const double v,
                                     Vector3 &dp_du, Vector3 &dp_dv) const
{
    //
    // ASSIGNMENT (PA07)
    //
    // Make this function return a Point3 lying on patch at the
    // parametric coordinates (`u`, `v`). Call `basis()` for both `u`
    // and `v`.
    //
    // 15 lines in instructor solution (YMMV)
    //
    
    Point3 point;
    //Point3 cvs_;
    double bs[4];
    double bsv[4];
     double db_bs[4];
      double db_bsv[4];
      dp_du = Vector3();
      dp_dv= Vector3();
    basis(u, bs, &db_bs);
    basis(v, bsv, &db_bsv);
    for(int i = 0; i< 4; i++){
    	for(int j = 0; j<4; j++){
    	    point+= cvs[i][j] * bsv[j] * bs[i];
    		 Point3 offset;
    		 offset.a[0] = cvs[i][j].a[0] *db_bs[i] * bsv[j];
    		  offset.a[1] = cvs[i][j].a[1] *db_bs[i] * bsv[j];
    		 offset.a[2] = cvs[i][j].a[2] *db_bs[i] * bsv[j];
    		Point3 offsetV;
    		offsetV.a[0] = cvs[i][j].a[0] * db_bsv[j]* bs[i];
    		offsetV.a[1] = cvs[i][j].a[1] * db_bsv[j]* bs[i];
    		offsetV.a[2] = cvs[i][j].a[2] * db_bsv[j]* bs[i];
    		dp_du += Vector3(offset.a);
    		dp_dv += Vector3(offsetV.a);
    	}
    }
    
    return point; // replace (permits template to compile cleanly)
}
