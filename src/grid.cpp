#include "grid.h"
#include "plane.h"

GridPoint::GridPoint() : Point(0, 0, 0), color(SDL_Color{0, 0, 0}), temperatureKelvin(0), slopeDeg(0), height(0) {}
GridPoint::GridPoint(Point p, SDL_Color color_, double temperatureKelvin_, double slopeDeg_, double height_)
    : Point(p), color(color_), temperatureKelvin(temperatureKelvin_), slopeDeg(slopeDeg_), height(height_) {}

Grid::Grid() : lattice((49 + 1) * (49 + 1)),
               system(),
               rows(49),
               columns(49),
               cellSize(1) {
                   setLatticePoints();
}

Grid::Grid(int rows_, int columns_, double cellSize_)
    : lattice((rows_ + 1) * (columns_ + 1)),
      system(),
      rows(rows_),
      columns(columns_),
      cellSize(cellSize_) {
    setLatticePoints();
}

void Grid::setLatticePoints() {
    Point displacedCenter = system.center;
    displacedCenter.x = system.center.x + ((columns + 1) * cellSize);
    displacedCenter.z = system.center.z - ((rows + 1) * cellSize);
    for (int row = 0; row <= rows; row += 1) {
        for (int column = 0; column <= columns; column += 1) {
            int index = (row * columns) + column;
            GridPoint& gridPoint = lattice[index];
            Point actualLocation = displacedCenter + (column * cellSize * system.axisX) + (row * cellSize * system.axisZ) + (gridPoint.height * system.axisY);
            gridPoint.x = actualLocation.x;
            gridPoint.y = actualLocation.y;
            gridPoint.z = actualLocation.z;
        }
    }
}

void Grid::render(SDL_Surface* canvas, SDL_Rect viewPortRect, Basis camera) {
    const Matrix cameraMatrix = cameraTransform(camera.axisX, camera.axisY, camera.axisZ, camera.center);
    const Plane cameraPlane = Plane(camera.center, camera.axisZ);
    const double focalDistance = 24;
    // Screen rect is the rectangle in the camera space that represents what the camera currently sees.
    // Growing this rectangle zooms the camera out.
    const SDL_Rect screenRect = {-100, -100, 200, 200};
<<<<<<< HEAD

    const Matrix projectionMatrix = ::projectionMatrix(focalDistance, screenRect, viewPortRect);
    const Matrix megaMatrix = projectionMatrix * cameraMatrix;

    uint32_t* const pixels = static_cast<uint32_t*>(canvas->pixels);

    for (const GridPoint& currentPoint: lattice) {
        Point p = currentPoint;

        // Is the point behind the camera? If so, get rid of it.
        if (cameraPlane.whichSide(p) < 0) {
            continue;
        }

        // Transfrom p from world space to camera space.
        // Then transform p from camera space to viewport space.
        p = megaMatrix * p;

        // Any point out of bounds of the view rectangle is skipped.
        if (p.x < viewPortRect.x ||
            p.y < viewPortRect.y ||
            p.x >= viewPortRect.x + viewPortRect.w ||
            p.y >= viewPortRect.y + viewPortRect.h) {
                continue;
        }

        // Render points that weren't skipped.
        // Offset formula:
        // width*y+x
        unsigned int offset = canvas->w * static_cast<unsigned int>(p.y) + static_cast<unsigned int>(p.x);
        pixels[offset] = SDL_MapRGBA(canvas->format, currentPoint.color.r, currentPoint.color.g, currentPoint.color.b, currentPoint.color.a);
=======

    const Matrix projectionMatrix = ::projectionMatrix(focalDistance, screenRect, viewPortRect);
    const Matrix megaMatrix = projectionMatrix * cameraMatrix;

    for (const GridPoint& currentPoint: lattice) {
        Point p = currentPoint;

        // Is the point behind the camera? If so, get rid of it.
        if (cameraPlane.whichSide(p) < 0) {
            continue;
        }

        // Transfrom p from world space to camera space.
        // Then transform p from camera space to viewport space.
        p = megaMatrix * p;

        // Any point out of bounds of the view rectangle is skipped.
        if (p.x < viewPortRect.x ||
            p.y < viewPortRect.y ||
            p.x >= viewPortRect.x + viewPortRect.w ||
            p.y >= viewPortRect.y + viewPortRect.h) {
            // TODO: skip this point and render all unskipped points onto the SDL surface.
        }
>>>>>>> 1d0c8e310e124d6c3e3c0504489478d502482f22
    }
}
