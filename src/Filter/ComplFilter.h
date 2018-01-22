/*
 * ComplFilter.h
 *
 *  Created on: 22 de jan de 2018
 *      Author: caio
 */

#ifndef SRC_FILTER_COMPLFILTER_H_
#define SRC_FILTER_COMPLFILTER_H_

#include <math.h>

#define Axis_X    0
#define Axis_Y    1
#define Axis_Z    2

#define ALPHA_STD   (0.7143)

double getPureAngle(double *acel){
  double angle = 0.0;

  angle = acos( (acel[Axis_Y]) / sqrt(acel[Axis_Y]*acel[Axis_Y] + acel[Axis_Z]*acel[Axis_Z] + acel[Axis_X]*acel[Axis_X] ) ) * (180.0/M_PI);
  if (acel[Axis_X] < 0){
    angle = - angle;
  }

  return angle;
}

class ComplFilter {
protected:
  double _dAlpha;
  double _dAngleFilter;
public:

  ComplFilter(){
    /* Init Alpha Constant for Filter */
    setAlpha(ALPHA_STD);

    /* Initialize Angle */
    double dInitAccel[] = {0,0,0};
    setInitAccel(dInitAccel);
  }

  ComplFilter(double dAlpha, double *pdInitAccel){
    /* Init Alpha Constant for Filter */
    setAlpha(dAlpha);

    /* Initialize Angle */
    setInitAccel(pdInitAccel);
  }

  ~ComplFilter(){}

  void setAlpha(double dAlpha) {

    if (dAlpha >= 0 && dAlpha <= 1) {
      this->_dAlpha = dAlpha;
    } else {
      this->_dAlpha = ALPHA_STD;
    }

  }

  double setInitAccel(double *pdInitAccel) {
    _dAngleFilter = getPureAngle(pdInitAccel);
    return _dAngleFilter;
  }

  double getComplFilterAngle(double *pdAccel, double dZGyro, double dt) {
    double dMeasureAngle = getPureAngle(pdAccel);

    _dAngleFilter =
        (_dAngleFilter + (dZGyro*dt) )*_dAlpha
        + (1-_dAlpha)*(dMeasureAngle);

    return _dAngleFilter;
  }
};


#endif /* SRC_FILTER_COMPLFILTER_H_ */
