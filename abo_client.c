/**
 * Test client for the abo_lib library.
 */

#include "abo_lib.h"
#include <stdio.h>

int main() {
  TAngle angle = AngleBetweenTwoObjects(5, 13, 31.7, -8, 13, 30, 6, 44, 13.4,
                                        -16, 41, 11, 'H');

  printf("The result is %f degrees %f minutes %f seconds.\n",
         angle.angleDegrees, angle.angleMinutes, angle.angleSeconds);

  return (0);
}