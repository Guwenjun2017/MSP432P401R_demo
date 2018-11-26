/*
 * base_move.h
 *
 *  Created on: 2018Äê11ÔÂ26ÈÕ
 *      Author: Jack
 */

#ifndef BASE_MOVE_H_
#define BASE_MOVE_H_

extern Timer_A_PWMConfig pwmConfig_Left_Go;
extern Timer_A_PWMConfig pwmConfig_Left_Back;
extern Timer_A_PWMConfig pwmConfig_Right_Go;
extern Timer_A_PWMConfig pwmConfig_Right_Back;

extern void Go_Forward();
extern void Go_Back();
extern void Turn_Left();
extern void Turn_Right();


#endif /* BASE_MOVE_H_ */
