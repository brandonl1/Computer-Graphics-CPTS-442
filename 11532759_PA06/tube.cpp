#include <iostream>
using namespace std;

#include "curve.h"
#include "geometry.h"
#include "tube.h"
#include "wrap_cmath_inclusion.h"


void Tube::draw(SceneObject *sceneObject)
{
    //
    // ASSIGNMENT (PA06)
    //
    // Add about code that:
    //
    // - checks if `tessellationMesh` is NULL and, if it is,
    //
    //   + calls `tessellate()` to create it
    //
    //   + calls `sceneObject->addHedgehogs(tessellationMesh)`
    //
    // - renders the tessellation
    //
    // Use TrigonometricCurve::draw() as a guideline.
    //
    // Note: This method will go away when it is more generalized in
    // the next assignment.
    //
    // 4 lines in instructor solution (YMMV)
    //
    if(tessellationMesh == NULL){
    
        tessellate();
        sceneObject->addHedgehogs(tessellationMesh);
    }
	
    tessellationMesh->render();
    
}


void Tube::tessellate(void)
{
    //
    // ASSIGNMENT (PA06)
    //
    // Add code to create an `nI` x `nJ` mesh using a trigonometric
    // parameterization. `nI` is along the angular dimension and `nJ`
    // is along the path. Iff `closed` is true, the tube is
    // continuous.
    //
    // Use `curve->coordinateFrame()` to get the position `p` and
    // `vU`, `vV`, and `vW` basis vectors and generate the
    // `vertexPositions[]` Point3's and vertexNormals[] Vector3's from that
    // based on the extrusion formula we derived in class. Remember
    // that the normal to tube with a circular cross section is just
    // the (unit) radial vector.
    //
    // If the tube is closed, use a `u` step size of 1/`nJ`. If is
    // open, use a `u` step size of 1/(`nJ`-1). The former ensures
    // that the triangles defining the last segment of the tube will
    // not be degenerate.
    //
    // Once `vertexPositions[]` are set, return a RegularMesh
    // constructed from them.
    //
    // Note: This method will go away when it is more generalized in
    // the next assignment.
    //
    // 16 lines in instructor solution (YMMV)
    //
   
    //Point3 edge;
    Point3 *vertexPositions = new Point3[nJ * nI];
    Vector3 *vertexNormals = new Vector3[nJ * nI];
    double u;
    for(int i = 0; i < nI; i++){
           u = 0.0;
      for(int j = 0; j < nJ; j++){
       Point3 p;
       Vector3 vU;
       Vector3 vV;
       Vector3 vW;

        curve->coordinateFrame(u, p, vU, vV, vW);

        int pos = (j * nI) + i;
        vertexPositions[pos] = p + vU *radius * cos(2 * M_PI * i / nI) + vV *  radius * sin(2 * M_PI * i / nI);
        vertexNormals[pos] = (p + radius * vU *  cos(2 * M_PI * i / nI) + vV * radius * sin(2 * M_PI * i / nI) ) - p;
        
        if(isClosed == true){
          u += double(1.0 / nJ);
        }
        else if(isClosed == false){
          u += double(1.0 / (nJ - 1.0));
        }
      }
    }

    tessellationMesh = new RegularMesh(vertexPositions, vertexNormals, nI, nJ, true, false);

  delete[] vertexPositions;
   delete[] vertexNormals;
}

