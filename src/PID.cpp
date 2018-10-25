#include <iostream>
#include "PID.h"


using namespace std;





PID::PID() {
	//init: Kp,   Ki,    Kd	
	Init(0.03, 0.01, 1.5);
}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;

}

void PID::UpdateError(double cte) {
	static double prev_error = 0.0;
	
	// update proportional error term
	p_error = cte; 

	// update integral error term
	i_error += cte;

	// update derivative error term
	d_error = cte - prev_error; 	

	prev_error = cte;
}

double PID::TotalError() {
	return p_error + i_error + d_error;
}


double PID::pid_cntl(){

	double steer = - Kp * p_error - Ki * i_error - Kd * d_error;
	return steer; 
}



