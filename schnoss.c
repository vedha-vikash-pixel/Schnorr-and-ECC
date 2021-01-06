#include<stdio.h>        //header files
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

long int p, q, a, s, v, r, x, y, j, flag, e;     //variables
char msg[1000],conmsg[1000];          
int len,i;      

int prime(long int);                  
int prime(long int pr)   //function to determine if the given number is prime or not
{
	int i;
	j=sqrt(pr);
	for (i=2;i<=j;i++) 
	{
		if(pr%i==0)
		    return 0;
	}
	return 1;
}

char *concat(long int x, char *msg,int len)  //function to concatinate the message with X to be fed into Hash function
{

        sprintf(msg+len, "%d", x);            
}

long hash(char *str)      //function to return the hash value of the concatinated message
{
	int hash = 0;
	int c;

	while (c = *str++)
	    hash += c;

	return hash;                    //hash value is returned
}

int verification(char *conmsg,long int e,long int y)      //function to verify and satisfy the property of Schnorr
{
    long int x2,e2;
    x2=((long int)(pow(a,y)) * (long int)(pow(v,e)) % p);  //X2 computed at receiver
    concat(x2 ,conmsg,len);                                //X2 concatinated with message
    e2 = hash(conmsg);                                     //E2 gets hash value of concatinated message
    if (e==e2)                                             //if E equals E2 then X == X2
        return 1;
    else
        return 0;
}
 
int main()                          //main function
{
	printf("ENTER FIRST PRIME NUMBER (P) \n");       
	scanf("%d",&p);                 //Get the first prime number (P)   //public variable
	while(1)
	{
	flag=prime(p);
	if(flag==0) 
	{
		printf("WRONG INPUT,ENTER PRIME NUMBER\n");
		scanf("%d",&p);
	}
	else
	     break;
	}
	
	printf("ENTER ANOTHER PRIME NUMBER (Q) (MUST BE A FACTOR OF P-1) \n");
	scanf("%d",&q);                //get the second prime number (Q) which should also be a factor of P-1   //public variable
	while(1)
	{
	flag=prime(q);
	if((flag==0||p==q)&&((p-1)%q!=0))
	{
     	printf("WRONG INPUT,ENTER ANOTHER PRIME NUMBER\n");
    	scanf("%d",&q);
	}
    else
        break;
	}
	
	printf("ENTER MESSAGE\n");     
	fflush(stdin);
	scanf("%s",msg);                //Get the message (MSG)
	len = strlen(msg);              //calculate the length of the message for concatinating later 
	for(i=0 ;msg[i]!='\0';i++)
	{
	    conmsg[i] = msg[i];
	}
	
	a = (((pow(a,q)) * (1/q)) * pow((1 % p),(1/q)));       //public variable A is calculated
    
    printf("ENTER PRIVATE KEY (S),(0 < S < Q)\n");  //private key S is chosen which should be greater than zero and less than Q   //private variable
    scanf("%d",&s);
    while(1)
    {
    if(s<0||s>q)
    {
         printf("PRIVTE KEY SHOULD BE LESS THAN Q AND GREATER THAN ZERO\n");
         scanf("%d",&s);
    }
    else
         break;
    }     
    
    v=((int)pow(a,-s)) % q;                         //public key is calculated  
    
    printf("KEY GENERATION IS COMPLETE\n\n");
    
    
    printf("CHOOSE A RANDOM NUMBER (R),(0 < R <Q):\n");     //random number R is chosen which should be greater than zero and less than Q
    scanf("%d",&r);
    while(1)
    {
    if(r<0||r>q)
    {
         printf("(R) SHOULD BE LESS THAN Q AND GREATER THAN ZERO\n");
         scanf("%d",&r);
    }
    else
         break;
    }     
    
    x=((long int)(pow(a,r)) % p);             //X is computed
    
    concat(x ,msg,len);                       //X is concatinated to message (MSG) to be fed into a hash function
    
    e = hash(msg);                            //E gets the returnrd value of hash function
    
    y = (r + (s*e)) % q;                      //Y is computed
    
    printf("SIGNING IS COMPLETE\n\nVERIFING...\n");
    
    if(verification(conmsg,e,y))                //verification function is called with parameters non concatinated message, E, Y
        printf("VERIFICATION IS CORRECT\n");
    else
        printf("VERIFICATION IS INCORRECT\n");
}	
