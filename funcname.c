#include  <stdio.h>

void myname(void)
{
	
	printf("%s\n",__FUNCTION__);
}

int main()
{
	myname();
	return 0;

}
