


#define TOGGLE_BIT(reg,bit) reg^=1<<bit
#define CLR_BIT(reg,bit) reg&=(~(1 << bit))
#define GET_BIT(reg,bit) (reg>>bit)&1
#define SET_BIT(reg,bit) reg|=1<<bit
#define SHIFT_ROTATE(reg,bit) reg^=1<<bit







