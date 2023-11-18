// #include "../includes/models.hpp"
// #include <map>

// int unplotedPoints(std::map<Vec3 *, bool> &mape, Triangles &it) {
//   int unplotedPoints = 0;
//   for (int i = 0; i < 3; i++) {
//     if (mape[it.points[i]] == true)
//       unplotedPoints++;
//   }
//   return unplotedPoints;
// }

// float calculateDistance(Triangles &it, int p1, int p2) {
//   return (sqrt(pow(it.points[p1]->x - it.points[p2]->x, 2) +
//                pow(it.points[p1]->y - it.points[p2]->y, 2) +
//                pow(it.points[p1]->z - it.points[p2]->z, 2)));
// }

// void Models::plotTriangle(std::map<Vec3 *, bool> &mape, Triangles &it) {
//   it.textures[0] = new Vec3(0, 0, 0);
//   it.textures[1] = new Vec3(0, 0, 0);
//   it.textures[2] = new Vec3(0, 0, 0);
//   it.textures[0]->x = 0;
//   it.textures[0]->y = 0;
//   float deltaDistance = calculateDistance(it, 0, 1);
//   it.textures[1]->x = deltaDistance;
//   it.textures[1]->y = 0;
//   float radiux13 = calculateDistance(it, 0, 2);
//   float radiux23 = calculateDistance(it, 1, 2);
//   it.textures[2]->x =
//       (pow(radiux13, 2) - pow(radiux23, 2) + pow(deltaDistance, 2)) /
//       (2 * deltaDistance);
//   it.textures[2]->y = sqrt(pow(radiux13, 2) - pow(it.textures[2]->x, 2));
//   mape[it.points[0]] = true;
//   mape[it.points[1]] = true;
//   mape[it.points[2]] = true;
// }

// int findPointToPlot(std::map<Vec3 *, bool> mape, Triangles &it) {
//   for (int i = 0; i < 3; i++) {
//     if (mape[it.points[i]] == true)
//       return i;
//   }
//   return 0;
// }

// void Models::plotTriangleFrom2Points(std::map<Vec3 *, bool> mape, Triangles &it,
//                                      int pointToPlot) {
//   (void)mape;
//   int point1 = 0, point2 = 1;
//   if (pointToPlot == 0)
//     point1 = 1, point2 = 2;
//   if (pointToPlot == 1)
//     point1 = 0, point2 = 2;
//   it.textures[pointToPlot] = new Vec3(0, 0, 0);
//   it.textures[point1] = map.find()
//   float radius1Point = calculateDistance(it, point1, pointToPlot);
//   float radius2Point = calculateDistance(it, point2, pointToPlot);
//   float dPoint1Point2 = calculateDistance(it, point2, point1);
  
//   cout << radius1Point << " " << radius2Point << " " << dPoint1Point2 << endl;
// }

// void Models::generateUvMap() {
//   std::map<Vec3 *, bool> mape;
//   int pointsToPlot = 0;
//   for (auto &it : _points) {
//     mape[it] = false;
//     pointsToPlot++;
//   }

//   for (auto &it : _triangles) {
//     if (unplotedPoints(mape, it) == 0) {
//       plotTriangle(mape, it);
//       pointsToPlot -= 3;
//       break;
//     }
//   }

//   for (auto &it : _triangles) {
//     if (unplotedPoints(mape, it) == 0)
//       continue;
//     if (unplotedPoints(mape, it) == 2) {
//       int point = findPointToPlot(mape, it);
//       plotTriangleFrom2Points(mape, it, point);
//     }
//   }
// }