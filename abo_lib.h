#ifndef abo_lib
#define abo_lib
#define M_PI 3.14159265358979323846264338327

struct angle {
  double angleDegrees, angleMinutes, angleSeconds;
};

typedef struct angle TAngle;

TAngle AngleBetweenTwoObjects(double raLong1HourDeg, double raLong1Min,
                              double raLong1Sec, double decLat1Deg,
                              double decLat1Min, double decLat1Sec,
                              double raLong2HourDeg, double raLong2Min,
                              double raLong2Sec, double decLat2Deg,
                              double decLat2Min, double decLat2Sec,
                              char hourOrDegree);
#endif