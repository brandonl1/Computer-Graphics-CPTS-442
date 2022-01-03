#include "circle.h"
#include "n_elem.h"
#include "poly_line.h"
#include "wrap_cmath_inclusion.h"


void Circle::draw(void)
{
    // If the circle has not been tessellated, tessellate it.
    if (!tessellationPolyLine)
        tessellate();

    // Now draw it.
    tessellationPolyLine->render();
}


void Circle::tessellate(void)
//
// tessellates the circle
//
{
    //
    // ASSIGNMENT (PA01)
    //
    // Replace the square PolyLine code below with code that uses the
    // formula you derived to set `tessellationPolyLine` to a PolyLine
    // representing a polygon with the minimum number of sides to be
    // within a half-pixel of a circle of the given `radius`.
    //
    // PolyLine() copies `vertexPosition`, so if you use dynamic
    // storage (and you should), remember to clean up after yourself.
    //
    // 19 lines in instructor solution (YMMV)
    //
    Point2 vertexPositions[4] = {
        Point2(-0.5, -0.5),
        Point2( 0.5, -0.5),
        Point2( 0.5,  0.5),
        Point2(-0.5,  0.5),
    };
    tessellationPolyLine = new PolyLine(vertexPositions,
                                        N_ELEM(vertexPositions), true);
}
