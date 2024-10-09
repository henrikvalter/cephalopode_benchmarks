#include <string.h>
#include "types.h"

typedef int	arbi_T;

/* ----- Function prototypes for public functions ----- */
void		Init_arbi();

/* Conversion routines */
arbi_T		Arbi_FromString(char *s, int base);
arbi_T		Arbi_FromInt(int i);

/* Arithmetic operations */
#define Arbi_add(a,b) ((a)+(b))
#define Arbi_sub(a,b) ((a)-(b))
#define Arbi_mlt(a,b) ((a)*(b))

/* Comparisons */
#define Arbi_cmp(a,b) (((a)>(b))? 1 : ((a)<(b))? -1 : 0)
#define arbi_LESS  -1
#define arbi_EQ     0
#define arbi_GREAT  1
