#include <assert.h>

#include "geometry.h"
#include "mesh.h"
#include "scene_object.h"
#include "surface.h"


void Surface::draw(SceneObject *sceneObject)
{
    if (!tessellationMesh) {
        tessellate();
        sceneObject->addHedgehogs(tessellationMesh);
    }

    tessellationMesh->render();
}

void Surface::tessellate(void)
{
    //
    // ASSIGNMENT (PA07)
    //
    // Construct the `nI` x `nJ` grid of `vertexPositions` (Point3s)
    // and their `vertexNormals` (Vector3s) on the surface and set
    // `tessellationMesh` to a new RegularMesh using them. Remember
    // that the surface itself can be invoked parametrically (as
    // "(*this)(...)").
    //
    // To construct `vertexNormals`, note that "(*this)(...)" now
    // returns partial derivative Vector3's `dp_du` and `dp_dv` and
    // that the surface normal can be constructed from these. Also
    // remember that surface normals must be of unit length.
    //
    // Use the same criteria for `u` step size (depending on closed
    // vs. non-closed) that you used for Tube::tessellate() in PA06
    // (using `wrapJ` here, of course). Also use it for the `v` step
    // size.
    //
    // For consistency with the solution (although it's really
    // arbitrary), make `i` the most rapidly-varying index.
    //
    // 17 lines in instructor solution (YMMV)
    //
    Point3 *vertexPositions = new Point3[nJ * nI];
    Vector3 *vertexNormals = new Vector3[nJ * nI];
    double u;
    double v = 0.0;
    Point3 bernstein;
    Vector3 normal;
    for(int j = 0; j < nJ; j++){
           u = 0.0;
      for(int i = 0; i < nI; i++){
       Vector3 vU;
       Vector3 vV;
         int pos = (j * nI) + i;
         bernstein = (*this)(u,v,vU,vV);
          //curve->coordinateFrame(u, p, vU, vV, vW);
	vertexPositions[pos] = bernstein;
	vertexNormals[pos] =  (vV.cross(vU)).normalized();

         
        if(wrapI == true){
          u += double(1.0 / nI);
        }
        else if(wrapI == false){
          u += double(1.0 / (nI - 1.0));
        }
      }
       
	 if(wrapJ == true){
          v += double(1.0 / nJ);
        }
        else if(wrapJ == false){
          v += double(1.0 / (nJ - 1.0));
        }
    }

    tessellationMesh = new RegularMesh(vertexPositions, vertexNormals, nI, nJ, wrapI, wrapJ);

  delete[] vertexPositions;
   delete[] vertexNormals;


}
