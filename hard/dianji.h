#include "mysys.h"

void dianji_init(void);
#define STBY(x) PBout(12)=x
#define AIN1(x) PCout(4)=x
#define AIN2(x) PAout(7)=x
#define BIN1(x) PCout(5)=x
#define BIN2(x) PBout(0)=x


