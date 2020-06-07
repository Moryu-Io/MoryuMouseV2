#ifndef DEF_CONST_PARAM_HPP_
#define DEF_CONST_PARAM_HPP_


#define MOC_MICON

/* 車体のパラメータ */
#define RIGHT_WHEEL_DIAMETER_mm (13.8f)
#define LEFT_WHEEL_DIAMETER_mm  (13.8f)

#define MACHINE_TREAD_mm        (18.0f)
#define MOTOR_REDUCTION_RATIO   (40.0f/13.0f)

#define CONTROLL_FREQ   (2500.0f)
#define CONTROLL_TIME   (0.0004f)




/* MMT関連 */
#define MMT_MASTER_WHO_AM_I (0x69A9)
#define MMT_SLAVE_WHO_AM_I (0x69BA)

#define MMT_MOC_HEADER (0xEBEBEBEB)
#define MMT_MOC_FOOTER (0xC1C1C1C1)

#define MMT_MASOC_HEADER (0xFAFAFAFA)
#define MMT_MASOC_FOOTER (0xA7A7A7A7)


#endif
