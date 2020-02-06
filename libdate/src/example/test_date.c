#include <stdio.h>
#include "date.h"

int main()
{
	T_Date date1 = {dimanche,27,1,2020};
	T_Date date2 = {dimanche,27,1,2020};
	printf("date1 == date2 ? : %d\n",dsame(date1,date2));
	return 0;
}
