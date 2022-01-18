#include "abo_lib.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Round input to specified number of decimal places.
 */
double Round(double input, int places) {
  bool isNegative = (input < 0) ? true : false;

  long double multiplier = pow(10, places);

  if (isNegative) {
    input = fabs(input);
  };

  long double a = input * multiplier;
  a = (a >= 0) ? a + 0.5 : a - 0.5;

  double returnValue =
      floor(a) / multiplier; // floor() gives good results for more places (7+)
                             // than the original (int) cast.

  return (isNegative) ? -(returnValue) : returnValue;
}

/**
 * Convert Civil Time (hours,minutes,seconds) to Decimal Hours
 */
double HmsToDh(double hours, double minutes, double seconds) {
  double fHours = hours;
  double fMinutes = minutes;
  double fSeconds = seconds;

  double a = fabs(fSeconds) / 60;
  double b = (fabs(fMinutes) + a) / 60;
  double c = fabs(fHours) + b;

  return (fHours < 0 || fMinutes < 0 || fSeconds < 0) ? -c : c;
}

/**
 * Convert Degrees Minutes Seconds to Decimal Degrees
 */
double DegreesMinutesSecondsToDecimalDegrees(double degrees, double minutes,
                                             double seconds) {
  double a = fabs(seconds) / 60;
  double b = (fabs(minutes) + a) / 60;
  double c = fabs(degrees) + b;

  return (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;
}

/**
 * Convert Degree-Hours to Decimal Degrees
 */
double DegreeHoursToDecimalDegrees(double degreeHours) {
  return degreeHours * 15;
}

/**
 * Convert Degrees to Radians
 */
double DegreesToRadians(double degrees) { return (degrees * M_PI) / 180; }

/**
 * Convert W value to Degrees
 */
double WToDegrees(double w) { return w * 57.29577951; }

/**
 * Extract Degrees part of Decimal Degrees
 */
double DecimalDegreesDegrees(double decimalDegrees) {
  double a = fabs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? 60 : b;

  return (decimalDegrees < 0) ? -(floor(e / 3600)) : floor(e / 3600);
}

/**
 * Extract Minutes part of Decimal Degrees
 */
double DecimalDegreesMinutes(double decimalDegrees) {
  double a = fabs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

/**
 * Extract Seconds part of Decimal Degrees
 */
double DecimalDegreesSeconds(double decimalDegrees) {
  double a = fabs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}

/**
 * Calculate the angle between two celestial objects, in
 * degrees,minutes,seconds.
 */
TAngle AngleBetweenTwoObjects(double raLong1HourDeg, double raLong1Min,
                              double raLong1Sec, double decLat1Deg,
                              double decLat1Min, double decLat1Sec,
                              double raLong2HourDeg, double raLong2Min,
                              double raLong2Sec, double decLat2Deg,
                              double decLat2Min, double decLat2Sec,
                              char hourOrDegree) {

  TAngle returnValue;

  double raLong1Decimal = (hourOrDegree == 'H')
                              ? HmsToDh(raLong1HourDeg, raLong1Min, raLong1Sec)
                              : DegreesMinutesSecondsToDecimalDegrees(
                                    raLong1HourDeg, raLong1Min, raLong1Sec);

  double raLong1Deg = (hourOrDegree == 'H')
                          ? DegreeHoursToDecimalDegrees(raLong1Decimal)
                          : raLong1Decimal;

  double raLong1Rad = DegreesToRadians(raLong1Deg);
  double decLat1Deg1 =
      DegreesMinutesSecondsToDecimalDegrees(decLat1Deg, decLat1Min, decLat1Sec);
  double decLat1Rad = DegreesToRadians(decLat1Deg1);

  double raLong2Decimal = (hourOrDegree == 'H')
                              ? HmsToDh(raLong2HourDeg, raLong2Min, raLong2Sec)
                              : DegreesMinutesSecondsToDecimalDegrees(
                                    raLong2HourDeg, raLong2Min, raLong2Sec);
  double raLong2Deg = (hourOrDegree == 'H')
                          ? DegreeHoursToDecimalDegrees(raLong2Decimal)
                          : raLong2Decimal;
  double raLong2Rad = DegreesToRadians(raLong2Deg);
  double decLat2Deg1 =
      DegreesMinutesSecondsToDecimalDegrees(decLat2Deg, decLat2Min, decLat2Sec);
  double decLat2Rad = DegreesToRadians(decLat2Deg1);

  double cosD =
      sin(decLat1Rad) * sin(decLat2Rad) +
      cos(decLat1Rad) * cos(decLat2Rad) * cos(raLong1Rad - raLong2Rad);
  double dRad = acos(cosD);
  double dDeg = WToDegrees(dRad);

  double angleDeg = DecimalDegreesDegrees(dDeg);
  double angleMin = DecimalDegreesMinutes(dDeg);
  double angleSec = DecimalDegreesSeconds(dDeg);

  returnValue.angleDegrees = angleDeg;
  returnValue.angleMinutes = angleMin;
  returnValue.angleSeconds = angleSec;

  return returnValue;
}
