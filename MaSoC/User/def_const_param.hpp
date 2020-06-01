#ifndef DEF_CONST_PARAM_HPP_
#define DEF_CONST_PARAM_HPP_


#define MASOC_MICON

/* RTOS関連 */
#define MCTaskStackSize  (512)
#define WSTaskStackSize  (256)
#define MSTaskStackSize  (1024)
#define UICTaskStackSize (128)

#define MCTaskPriority  (3)
#define WSTaskPriority  (2)
#define MSTaskPriority  (1)
#define UICTaskPriority (0)


/* MMT関連 */
#define MMT_MASTER_WHO_AM_I (0x69A9)
#define MMT_SLAVE_WHO_AM_I (0x69BA)

#define MMT_MOC_HEADER (0xEBEBEBEB)
#define MMT_MOC_FOOTER (0xC1C1C1C1)

#define MMT_MASOC_HEADER (0xFAFAFAFA)
#define MMT_MASOC_FOOTER (0xA7A7A7A7)

#endif
