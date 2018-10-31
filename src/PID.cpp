#include <iostream>
#include "PID.h"


using namespace std;





PID::PID() {
	//init: Kp,   Ki,    Kd	
	//Init(0.03, 0.01, 1.5);
//	Init(0.15, 0.02, 4.2);
	Init(0.15, 0.0, 4.2);
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


double PID::pid_cntl(double speed){
	static const int max_arr = 3;
	static double speed_array[3] = {0.0,0.0,0.0}; 
	static int index = 0; 
	double speed_avg = 0.0;

//filtering speed values
	speed_array[index++] = speed; 
	if( index >max_arr) index = 0;

	for (int i = 0; i < max_arr; i++){
		speed_avg += speed_array[i];
	}
	speed_avg = speed_avg/max_arr;	
//set gains based of avg speed threshold
	if (speed_avg < 25.0){
		Kp = 0.15;
		Ki = 0.0;
		Kd = 4.2;
	}else{

		Kp = 0.25;
		Ki = 0.0225;
		Kd = 4.15;
	}
	double steer = - Kp * p_error - Ki * i_error - Kd * d_error;
	return steer; 
}


