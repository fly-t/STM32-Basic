#include "soft_iic.h"
#include "sys.h"
/**
 * @brief SDA引脚设置输出模式
 * @param  无
 * @return 无
 */
static void Soft_IIC_Output(void)
{
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_OUTPUT_PP;
    SOFT_IIC_GPIO_STRUCT.Pin = IIC_SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(IIC_SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

/**
 * @brief SDA引脚设置输入模式
 * @param  无
 * @return 无
 */
static void Soft_IIC_Input(void)
{
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_INPUT;
    SOFT_IIC_GPIO_STRUCT.Pin = IIC_SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(IIC_SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	Soft_IIC_Output();     //sda�����
	IIC_SDA_H();	  	  
	IIC_SCL_H();
	delay_us(4);
 	IIC_SDA_L();//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_L();//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	Soft_IIC_Output();//sda�����
	IIC_SCL_L();
	IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H(); 
	IIC_SDA_H();//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	Soft_IIC_Input();      //SDA����Ϊ����  
	IIC_SDA_H();delay_us(1);	   
	IIC_SCL_H();delay_us(1);
    while (HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN))
    {
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L();
	Soft_IIC_Output();
	IIC_SDA_L();
	delay_us(2);
	IIC_SCL_H();
	delay_us(2);
	IIC_SCL_L();
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L();
	Soft_IIC_Output();
	IIC_SDA_H();
	delay_us(2);
	IIC_SCL_H();
	delay_us(2);
	IIC_SCL_L();
}
/**
 * @brief IIC写数据0
 * @param  无
 * @return 无
 */
void Soft_IIC_Write_Low(void)
{
    IIC_SCL_L();
    IIC_SDA_L();
    delay_us(2);
    IIC_SCL_H();
    delay_us(2);
    IIC_SCL_L();
}
/**
 * @brief IIC写数据1
 * @param  无
 * @return 无
 */
void Soft_IIC_Write_High(void)
{
    IIC_SCL_L();
    IIC_SDA_H();
    delay_us(2);
    IIC_SCL_H();
    delay_us(2);
    IIC_SCL_L();
}
/**
 * @brief IIC写入单个数据
 * @param  无
 * @return 应答信号, 0无应答 1有应答
 */
void IIC_Send_Byte(uint8_t Byte)
{
    uint8_t i;
    Soft_IIC_Output();
    IIC_SCL_L();
    for (i = 0x80; i != 0; i >>= 1)
    {
        delay_us(2);
        if (Byte & i)
        {
            Soft_IIC_Write_High();
        }
        else
        {
            Soft_IIC_Write_Low();
        }
    }
}
// void IIC_Send_Byte(uint8_t txd)
// {                        
//     uint8_t t;   
// 	Soft_IIC_Output(); 	    
//     IIC_SCL_L();//����ʱ�ӿ�ʼ���ݴ���
//     for(t=0;t<8;t++)
//     {              
//         IIC_SDA=(txd&0x80)>>7;
//         txd<<=1; 	  
// 		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
// 		IIC_SCL_H();
// 		delay_us(2); 
// 		IIC_SCL_L();	
// 		delay_us(2);
//     }	 
// } 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	Soft_IIC_Input();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L(); 
        delay_us(2);
		IIC_SCL_H();
        receive<<=1;
        if (HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN))
            receive++;
        delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


