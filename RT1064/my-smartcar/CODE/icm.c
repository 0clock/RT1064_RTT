//
// Created by Jay on 2022/4/5.
//

#include "icm.h"

//-----------------------��-----------------------//
//--------------------ȫ�ֱ���---------------------//
vectorxyz gyro_vector;
vectorxyz acc_vector;
vectorxyz gyro_RCFilter;
vectorxyz gyro_MovAverFilter;

float MovAverbuf_gyrox[11] = {0};
float MovAverbuf_gyroy[11] = {0};
float MovAverbuf_gyroz[11] = {0};

//---------------------�ṹ��---------------------//

struct RC_Para gyrox_Para = {0,0,0.6};
struct RC_Para gyroy_Para = {0,0,0.6};
struct RC_Para gyroz_Para = {0,0,0.6};

RC_Filter_pt RC_gyrox = &gyrox_Para;
RC_Filter_pt RC_gyroy = &gyroy_Para;
RC_Filter_pt RC_gyroz = &gyroz_Para;

struct IMU_param_t icmOffset={0,0,0,0,0,0};               // ������У׼ֵ
struct IMU_param_t icm_data={0,0,0,0,0,0};                 // ICM����ֵ
//-------------------��������---------------------//

/*
***************************************************************
*�� �� ��:  �����ʼ��
*����˵��:  ͨ���ɼ�һ���������ֵ�������������ƫ��ֵ
*��    ��:  ��
*�� �� ֵ:  ��
***************************************************************
*/
void icmOffsetInit(void)
{
    icmOffset.acc_x = 0;
    icmOffset.acc_y = 0;
    icmOffset.acc_z = 0;

    icmOffset.gyro_x = 0;
    icmOffset.gyro_y = 0;
    icmOffset.gyro_z = 0;
    for (uint8_t i = 0; i < 100; ++i)
    {
        get_icm20602_gyro();    // ��ȡ�����ǽ��ٶ�
        get_icm20602_accdata();	// ��ȡ���ٶȼƼ��ٶ�
        icmOffset.acc_x += icm_acc_x;
        icmOffset.acc_y += icm_acc_y;
        icmOffset.acc_z += icm_acc_z;
        icmOffset.gyro_x += icm_gyro_x;
        icmOffset.gyro_y += icm_gyro_y;
        icmOffset.gyro_z += icm_gyro_z;
        systick_delay_ms(5);    // ��� 1Khz
    }

    icmOffset.acc_x  /= 100;
    icmOffset.acc_y  /= 100;
    icmOffset.acc_z  /= 100;

    icmOffset.gyro_x /= 100;
    icmOffset.gyro_y /= 100;
    icmOffset.gyro_z /= 100;
}

/*
******************************************************************************************
*�� �� ��:  ���������ݴ���
*����˵��:  ���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����@�����Դ�Ϊ�������Ͽ������˲�
*���ٶȼƳ�ʼ������ -> ������Χ: ��8g        ��Ӧ������: 4096 LSB/g
*�����ǳ�ʼ������   -> ������Χ: ��2000 dps  ��Ӧ������: 16.4 LSB/dps
*gyro = (gyro_val / 16.4) ��/s = ((gyro_val / 16.4) * PI / 180) rad/s
*��    ��:  ��
*�� �� ֵ:  ��
*******************************************************************************************
*/
void icmGetValues(void)
{
    //��ȡ˲ʱ����
    get_icm20602_gyro();
    get_icm20602_accdata();
    //���ٶȼ�
    icm_data.acc_x = (float) icm_acc_x - icmOffset.acc_x;
    icm_data.acc_y = (float) icm_acc_y - icmOffset.acc_y;
    icm_data.acc_z = (float) icm_acc_z - icmOffset.acc_z;
    //! �����ǽ��ٶȱ���ת��Ϊ�����ƽ��ٶ�: deg/s -> rad/s
    icm_data.gyro_x = ((float) icm_gyro_x - icmOffset.gyro_x) * PI / 180 / 16.4f;
    icm_data.gyro_y = ((float) icm_gyro_y - icmOffset.gyro_y) * PI / 180 / 16.4f;
    icm_data.gyro_z = ((float) icm_gyro_z - icmOffset.gyro_z) * PI / 180 / 16.4f;
    //��icm��ֵ��ֵ����Ȼ����ϵ�������Խ���AHRS��̬����
    acc_vector.x = icm_data.acc_x;
    acc_vector.y = icm_data.acc_y;
    acc_vector.z = icm_data.acc_z;

    gyro_vector.x = icm_data.gyro_x;
    gyro_vector.y = icm_data.gyro_y;
    gyro_vector.z = icm_data.gyro_z;
    //��ͨ�˲�
    gyro_RCFilter.x = RCFilter(icm_data.gyro_x,RC_gyrox);
    gyro_RCFilter.y = RCFilter(icm_data.gyro_y,RC_gyroy);
    gyro_RCFilter.z = RCFilter(icm_data.gyro_z,RC_gyroz);

    gyro_MovAverFilter.x = Movingaverage_filter(gyro_RCFilter.x,MovAverbuf_gyrox);
    gyro_MovAverFilter.y = Movingaverage_filter(gyro_RCFilter.y,MovAverbuf_gyroy);
    gyro_MovAverFilter.z = Movingaverage_filter(gyro_RCFilter.z,MovAverbuf_gyroz);
}