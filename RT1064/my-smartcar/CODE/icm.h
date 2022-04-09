//
// Created by Jay on 2022/4/5.
//

#ifndef _ICM_H
#define _ICM_H

//#include "headfile.h"
#include "SEEKFREE_ICM20602.h"
#include "ahrs.h"



//-----------------------��-----------------------//
//--------------------ȫ�ֱ���---------------------//
//---------------------�ṹ��---------------------//
//-------------------��������---------------------//

void Charge_Locate(void);            //���괦����

extern int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
extern int16 icm_acc_x,icm_acc_y,icm_acc_z;
extern struct vectorxyz gyro_RCFilter;
extern struct vectorxyz gyro_MovAverFilter;

typedef struct IMU_param_t//�Ǽ��ٶ����ֵ
{
    float acc_x;
    float acc_y;
    float acc_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;
}IMU_param_t;

extern struct IMU_param_t icmOffset;               // ������У׼ֵ
extern struct IMU_param_t icm_data;                 // ICM����ֵ



//----------���ݴ���------------
void icmOffsetInit(void);     //��Ư����
void icmGetValues(void);       //��ͨ+���ݵ�λ����


#endif
