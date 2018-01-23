#ifndef PIDCTRL_H
#define PIDCTRL_H

#include <QObject>

//-----------------------------------------------------------------------------

class PidCtrl : public QObject
{
   Q_OBJECT

public:
   explicit PidCtrl(QObject *parent = 0);

   // dt  - Loop interval time
   // max - Maximum value of manipulated variable
   // min - Minimum value of manipulated variable
   // Kp  - Proportional gain
   // Ki  - Integral gain
   // Kd  - Derivative gain
   void define(double dt, double max, double min, double Kp, double Ki, double Kd);

   // Returns the manipulated variable given a setpoint and current process value
   double calculate(double setPoint, double pv);

private:
   double dt;
   double max;
   double min;
   double Kp;
   double Kd;
   double Ki;
   double preError;
   double integral;


};

//-----------------------------------------------------------------------------

#endif // PIDCTRL_H
