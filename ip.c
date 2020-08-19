//DRAGAN SILVIA 311CB

#include <stdio.h>

void baza2(int n, unsigned int v[], int ct)
{
	int k=0;
	for(k=0; k<ct; k++) v[k]=0;
	k=0;
	while(n)
	{
		v[k++]=n%2;
		n/=2;
	}
}

void task1(unsigned int mascazec[], int masca)
{
	int c, r; // catul si restul impartirii la 8 lui msk_2
	int i, j;

	for(i=0; i<4; i++) mascazec[i]=0;

	c=masca/8; 
	r=masca-c*8;

	for(i=0; i<c; i++) 
		mascazec[i]=(1<<8)-1;
	for(i=7; i>=8-r; i--) 
		mascazec[c]=mascazec[c]|(1<<i);
	for(j=c+1; j<4; j++) 
		mascazec[j]=0;
}

int task5(unsigned int v1[],unsigned int m1[],unsigned int v2[],unsigned int m2[])
{

	if ( (v1[0]&m1[0]) == (v2[0]&m2[0]) && 
		 (v1[1]&m1[1]) == (v2[1]&m2[1]) &&
		 (v1[2]&m1[2]) == (v2[2]&m2[2]) &&
		 (v1[3]&m1[3]) == (v2[3]&m2[3]) )
	{
		return 1; //pentru cazul adevarat
	}
	return 0; // daca nu a iesit pe primul retun, e clar fals

}

int main()
{
	unsigned int MSK_1[4], MSK_2, IP_1[4], IP_2[4];

	//TASK0 

	int setdate=0, setcurent=0;
	scanf("%d", &setdate);

	for(setcurent=1;setcurent<=setdate;setcurent++)
	{
		int reint;
		for(reint=0; reint<4; reint++)
		{
			MSK_1[reint]=IP_1[reint]=IP_2[reint]=0;
		}
		MSK_2=0;

		printf("%d\n", setcurent);

		scanf("%u.%u.%u.%u", &MSK_1[0], &MSK_1[1], &MSK_1[2], &MSK_1[3]);
		scanf("%u", &MSK_2);
		scanf("%u.%u.%u.%u", &IP_1[0], &IP_1[1], &IP_1[2], &IP_1[3]);
		scanf("%u.%u.%u.%u", &IP_2[0], &IP_2[1], &IP_2[2], &IP_2[3]);

		printf("-0 %u.%u.%u.%u/%u\n",IP_1[0], IP_1[1], IP_1[2], IP_1[3], MSK_2);

		//TASK1

		unsigned int masca2[4];

		task1(masca2, MSK_2);
		printf("-1 %u.%u.%u.%u\n", masca2[0], masca2[1], masca2[2], masca2[3]);
		
		//TASK2
		
		// in baza 8
		printf("-2 %o.%o.%o.%o ", MSK_1[0], MSK_1[1], MSK_1[2], MSK_1[3]);

		//in baza 16
		printf("%X.%X.%X.%X\n", MSK_1[0], MSK_1[1], MSK_1[2], MSK_1[3]);

		//TASK3

		printf("-3 %u.%u.%u.%u\n", IP_1[0]&masca2[0], IP_1[1]&masca2[1], 
			IP_1[2]&masca2[2], IP_1[3]&masca2[3]);

		//TASK4
		unsigned char masca2_char[4]; 
		unsigned char ip1_char[4];
		int i;
		for(i=0; i<4; i++)
			masca2_char[i]=ip1_char[i]=0;
		for(i=0; i<4; i++)
			{
				masca2_char[i]=(unsigned char)masca2[i];
				ip1_char[i]=(unsigned char)IP_1[i];
			}

		printf("-4 %hhu.%hhu.%hhu.%hhu\n", ip1_char[0]|(~masca2_char[0]), 
			ip1_char[1]|(~masca2_char[1]), ip1_char[2]|(~masca2_char[2]), 
			ip1_char[3]|(~masca2_char[3]));


		//TASK5

		if (task5(IP_1, masca2, IP_2, masca2))
			{
				printf("-5 DA\n");
			}
		else 
		{
			printf("-5 NU\n");
		}

		//TASK6

		unsigned int masca1; //construiesc masca 1 fara .
		unsigned int msb; //pozitia pentru most significant bit

		masca1=( (unsigned int)(MSK_1[0]<<24) | (unsigned int)(MSK_1[1]<<16) 
			| (unsigned int)(MSK_1[2]<<8) | (unsigned int)MSK_1[3] );
		int k, ok=1, s;
		//verificam daca bitii alterneaza
		for(k=31; k>=0; k--)
			{	
				//parcurgem masca pana cand gasim un 0
				if((masca1 & (1<<k))==(unsigned int)(1<<k));
				/*la gasirea primului 0, ii retinem pozitia si verificam daca 
				urmeaza doar 0 uri*/ 
				else 
					for(s=k; s>=0; s--)
						if((masca1 & (1<<s))==(unsigned int)(1<<s))
						{
							msb=s+1; //pozitia ultimului bit de 1
							ok=0;
							break;
						}
				if(!ok) break;
			}

		if(ok) 
		{
			printf("-6 DA\n");
			printf("-7 %u.%u.%u.%u\n", MSK_1[0], MSK_1[1], MSK_1[2], MSK_1[3]);
		}
		else 
		{
			//TASK7
			printf("-6 NU\n");
			printf("-7 ");

			msb=32-msb; //cati biti de 1 are masca1
			unsigned int msc=0;
			int c=0,r=0;
			c= msb/8; r = msb-8*c; //catul si restul impartirii la 8 al lui msb		

			//construiesc masca inapoi in vector
			for(i=0;i<c;i++) 
				MSK_1[i]=(1<<8)-1;
			for(i=7;i>=8-r;i--) 
				msc = msc | (1<<i);

			MSK_1[c]=MSK_1[c]&msc;

			for(i=c+1;i<4;i++) 
				MSK_1[i]=MSK_1[i]&0; 
			
		printf("%u.%u.%u.%u\n", MSK_1[0], MSK_1[1], MSK_1[2], MSK_1[3]);

		}
		
	 	//TASK8

		printf("-8 ");

		unsigned int ipb2[8]; //ip1 in binar

		//initializez ipb2 cu 0
		for(i=0; i<8; i++) 
			ipb2[i]=0;

		/*transform fiecare element al vectorului ip1 in binar folosind functia
		baza2*/ 
		for(i=0; i<4; i++)
		{
			baza2(IP_1[i], ipb2, 8);
			//daca suntem pe ultimul element, nu afisam un punct final
			if(i!=3)
			{
				for(k=7; k>=0; k--)
				{
					printf("%u", ipb2[k]);
				}
				printf(".");
			}
			else 
			{
				for(k=7; k>=0; k--)
				{
					printf("%u", ipb2[k]);
				}
			}
		}
		printf("\n");


	 	//TASK9
	 	printf("-9 ");
	 	int N;
	 	scanf("%u\n", &N);
	 	unsigned int adresa[4], mascanou[4], mascaadr;
	 	for(i=0; i<N; i++)
	 	{
	 		scanf("%u.%u.%u.%u/%u",&adresa[0], &adresa[1], &adresa[2], 
	 			&adresa[3], &mascaadr);

	 		//trasformam masca adresei in zecimal cu ajutorul funtiei task1
			task1(mascanou, mascaadr);

	 		if(task5(IP_2,mascanou, adresa, mascanou))
	 		{
	 			printf("%u ", i);
	 		}

	 	}
	 	printf("\n");
	 }
 	return 0;
}