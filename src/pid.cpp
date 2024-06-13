#include "pid.h"

#define PWM_PIN 18

#define MIN_PID -30
#define MAX_PID 30

#define MIN_PWM 255
#define MAX_PWM -255

float kP = 0;
float kI = 0;
float kD = 0;
float dT = 0.1;
float setpoint = 0;
float process_variable = 0;
float pid_error = 0;
float previous_pid_error = 0;
float proportional = 0;
float integral = 0;
float derivative = 0;

void set_gains(float kp, float ki, float kd)
{
    kP = kp;
    kI = ki;
    kD = kd;
}

void set_setpoint(float sp)
{
    setpoint = sp;
}

void set_process_variable(float pv)
{
    process_variable = pv;
}

float calculate_error()
{
    return setpoint - process_variable;
}

int pid_to_pwm(float pid)
{
    int pwm_value = map(pid, MIN_PID, MAX_PID, MIN_PWM, MAX_PWM);
    return pwm_value;
}

void calculate_proportional()
{
    proportional = kP * pid_error;
}

void calculate_integral()
{
    integral += kI * pid_error * dT;
}

void calculate_derivative()
{
    derivative = kD * (pid_error - previous_pid_error) / dT;
    previous_pid_error = pid_error;
}

float calculate_pid()
{
    pid_error = calculate_error();
    calculate_proportional();
    calculate_integral();
    calculate_derivative();
    return proportional + integral + derivative;
}
