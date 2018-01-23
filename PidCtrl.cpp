#include "PidCtrl.h"

//-----------------------------------------------------------------------------

PidCtrl::PidCtrl(QObject *parent) : QObject(parent)
{
   this->dt = 0.0;
   this->max = 0.0;
   this->min = 0.0;
   this->Kp = 0.0;
   this->Kd = 0.0;
   this->Ki = 0.0;
   this->preError = 0.0;
   this->integral = 0.0;
}

//-----------------------------------------------------------------------------

void PidCtrl::define(double dt, double max, double min, double Kp, double Ki, double Kd)
{
   this->dt = dt;
   this->max = max;
   this->min = min;
   this->Kp = Kp;
   this->Ki = Ki;
   this->Kd = Kd;
   this->preError = 0.0;
   this->integral = 0.0;
}

//-----------------------------------------------------------------------------

double PidCtrl::calculate(double setPoint, double pv)
{
   // Calculate error
   double error = setPoint - pv;

   // Proportional term
   double Pout = Kp * error;

   // Integral term
   integral += error * dt;
   double Iout = Ki * integral;

   // Derivative term
   double derivative = (error - preError) / dt;
   double Dout = Kd * derivative;

   // Calculate total output
   double output = Pout + Iout + Dout;

   // Restrict to max/min
   if( output > max ) {
      output = max;
   } else if ( output < min ) {
      output = min;
   }

   // Save error to previous error
   preError = error;

   return output;
}

//-----------------------------------------------------------------------------
