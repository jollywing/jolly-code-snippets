#include<stdio.h>
void MoveDisks(int , char , char , char );

int main()
{
    MoveDisks(4, '1', '3', '2');
    return 0;
}

void MoveDisks(int nDiskNum, char chSourcePole, char chTargetPole, char chMidPole)
{
	if (nDiskNum == 1)
		printf("%c -> %c\n", chSourcePole, chTargetPole);
	else
	{
	 	MoveDisks(nDiskNum-1, chSourcePole, chMidPole, chTargetPole);
		printf("%c -> %c\n",chSourcePole,chTargetPole);
		MoveDisks(nDiskNum-1, chMidPole,  chTargetPole , chSourcePole);
	}
}


