#ifndef MOTOR_H 
#define MOTOR_H 

#include "stm32g4xx.h"
#include "motor_math.h"



// typedef enum
// {
//     FOC_MODE_OPEN_LOOP = 0,
//     FOC_MODE_CLOSED_LOOP = 1
// } FOCMode_TypeDef;

typedef struct 
{
	float Uabc_V[3];
	float UalphaBeta_V[2];
	float Udq_V[2];
	
	float Uabc_pu[3];
	float UalphaBeta_pu[2];
	float Udq_pu[2];


	float Iabc_A[3];
	float IalphaBeta_A[2];
	float Idq_A[2];

	float theta_Rad;
	float theta_RadPerLoop;

	struct{
		float setSpeed_RPM;
		float setIdq_A[2];

	}set;



}motor_t ;

static inline void motor_setABCcurrentsFB (motor_t* motor, float iA, float iB, float iC)
{
	motor->Iabc_A[0] = iA;
	motor->Iabc_A[1] = iB;
	motor->Iabc_A[2] = iC;
}
static inline void motor_clark (motor_t* motor)
{
	motor->IalphaBeta_A[0] = motor->Iabc_A[0];
	motor->IalphaBeta_A[1] = (M_1_SQRT3 * motor->IalphaBeta_A[0]) + (M_2_SQRT3 * motor->Iabc_A[1]);
}
static inline void motor_ParkTransform (motor_t* motor)
{
	motor->Idq_A[0] = motor->IalphaBeta_A[0] * cos(motor->theta_Rad) + motor->IalphaBeta_A[1] * sin(motor->theta_Rad);
	motor->Idq_A[1] = -motor->IalphaBeta_A[0] * sin(motor->theta_Rad) + motor->IalphaBeta_A[1] * cos(motor->theta_Rad);

	// iD = iAlpha*cos(theta)+iBeta*sin(theta);
	// iQ = -iAlpha*sin(theta)+iBeta*cos(theta);
}
static inline void motor_invParkTransform (motor_t* motor)
{
	motor->UalphaBeta_pu[0] = cos(motor->theta_Rad) * motor->Udq_pu[0] - sin(motor->theta_Rad) * motor->Udq_pu[1];  // -sin(angle) * Uq;
	motor->UalphaBeta_pu[1] = sin(motor->theta_Rad) * motor->Udq_pu[0] + cos(motor->theta_Rad) * motor->Udq_pu[1];    //  cos(angle) * Uq;

	// Ualpha = cos(angle_el) * Ud -sin(angle_el) * Uq;  // -sin(angle) * Uq;
	// Ubeta = sin(angle_el) * Ud + cos(angle_el) * Uq;    //  cos(angle) * Uq;
}
static inline void motor_invClarkTransform (motor_t* motor)
{
	motor->Uabc_pu[0] = motor->UalphaBeta_pu[0];
	motor->Uabc_pu[1] = -0.5f * motor->UalphaBeta_pu[0] + M_SQRT3_2 * motor->UalphaBeta_pu[1];
	motor->Uabc_pu[2] = -0.5f * motor->UalphaBeta_pu[0] - M_SQRT3_2 * motor->UalphaBeta_pu[1];
	// uint32_t Ua = Ualpha + 500;
	// uint32_t Ub = -0.5f * Ualpha  + M_SQRT3_2 * Ubeta + 500;
	// uint32_t Uc = -0.5f * Ualpha - M_SQRT3_2 * Ubeta + 500;
}
static inline float* motor_getUabc_pu(motor_t* motor)
{
	return motor->Uabc_pu;
}
void motor_dutyProc(motor_t* motor);



#endif  // MOTOR_H