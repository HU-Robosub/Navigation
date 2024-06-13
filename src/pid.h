#ifndef PID_H
#define PID_H

#include <Arduino.h>

extern float kP;
extern float kI;
extern float kD;
extern float dT;
extern float setpoint;
extern float process_variable;
extern float pid_error;
extern float previous_pid_error;
extern float proportional;
extern float integral;
extern float derivative;

void set_gains(float kp, float ki, float kd);
void set_setpoint(float sp);
void set_process_variable(float pv);
float calculate_error();
int pid_to_pwm(float pid);
void calculate_proportional();
void calculate_integral();
void calculate_derivative();
float calculate_pid();

#endif // PID_H
