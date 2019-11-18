//gcc -o test test.c -lm

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define MAX_SIZE_MESSAGE 1024
long generatePrime(int n);
long gcd(long a, long b);
int coprime(long a);
long isPrime(int num);
void publicKey();
void privKey();


long p=0,q=0,n=0,e=0,phi=0,d=0;
struct private_key
{
	long n1;
	long d1;
};
struct public_key
{
	long n2;
	long e2;
};
struct private_key PRIV_KEY;
struct public_key PUBLIC_KEY;
char * encrypt(char * msg, struct public_key);
char * decrypt(char * msg, struct private_key);
long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX ) * (RAND_MAX ) * (RAND_MAX ) +
                (long long)rand() * (RAND_MAX ) * (RAND_MAX ) +
                (long long)rand() * (RAND_MAX ) +
                rand()) % (h - l + 1);
}



//this function will generate a prime number between 2^n and 2^n-1
long generatePrime(int n)
{
	long long prime = -1;
	int k=1;
	while(k)
	{
		prime = Rand(pow(2,n-1),pow(2,n));
		if (isPrime(prime))
			k=0;
	}
	return prime;
}
//function to find gcd of 2 numbers a, b
long gcd(long a, long b){
    // if a = 0 => gcd(a,b) = b
    // if b = 0 => gcd(a,b) = a
    if (a == 0 || b == 0){
        return a + b;
    }
	// Repeat until a=0 or b=0
    while (a*b != 0){
        if (a > b){
            a %= b; // a = a % b
        }else{
            b %= a;
        }
    }
    return a + b; // return a + b, as at this time, we have a=0 or b=0
}
//function generate a coprime number of a
int coprime(long a)
{
    int co;
    do{
    		co = rand()%phi;
    	}while(gcd(co, a) != 1);
    return co;
}
//function check if a number is prime or not
long isPrime(int num)
{
    if (num < 2)
        return 0;

    for (int i = 2; i <= sqrt((float)num); i ++)
    {
        if (num%i==0)
        {
            return 0;
        }
    }
    return 1;
}

//after this function, we have public key is made of n and e
void publicKey()
{
	p = generatePrime(10);
	int k=1;
	while(k)
	{
		q = generatePrime(10);
		if (q != p)
			k=0;
	}
	n = p * q;
	phi = (p-1)*(q-1);
	e = coprime(phi);
}

void privKey()
{
	d = 1;
	while (((d*e) % (phi)) != 1)
	{
		d++;
	}

}
char* itoa(long long val, int base){

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}

char * encrypt(char * msg, struct public_key Pub)
{	
	unsigned long long buf[MAX_SIZE_MESSAGE];
	memset(buf,0,MAX_SIZE_MESSAGE);
	unsigned long long temp;
	unsigned long long r;
	int i,j, len =strlen(msg);
	for (i = 0; i < len; i++)
	{
		buf[i] = msg[i];
	}	
	i = 0;
	while(buf[i] != 0)
	{
		r = 1;
		for(j=0;j<Pub.e2;j++)
		{
		    temp=0;
            	    temp= r*buf[i];
            	    r =temp% Pub.n2;
		}
		buf[i] = r;
		i++;
	}
	char str[8096];
	char str2[8096];
	int lenS; 
	for(i=0;buf[i]!=0;i++)
	{
		sprintf(str2, "%lli", buf[i]);
		lenS = strlen(str2);
		str2[lenS] = '\0';
		strcat(str,str2);
		strcat(str,".");
	}
	msg = str;
	return msg;
	
	
}

char * decrypt(char * str, struct private_key Priv)
{
	unsigned long long buf[MAX_SIZE_MESSAGE];
	memset(buf,0,MAX_SIZE_MESSAGE);
	int i,j;
	unsigned long long r,temp;
	unsigned long long ret=1;
	char * ptr1, * ptr2;
	ptr1 = str;

	i = 0;
	while(ret != 0)
	{
		ret = strtol(ptr1,&ptr2,10);
		buf[i] = ret;
		ptr1 = ptr2;
		ptr1=ptr1+1;
		i++;
	}
	i = 0;
	while(buf[i] !=0)
	{
		r = 1;
		for(j=0;j<Priv.d1;j++)
		{
		    temp=0;
		    temp= r*buf[i];
            	    r =temp% Priv.n1;
		}
		buf[i] = r;
		i++;
	}

	for(i=0;buf[i]!=0;i++)
	{
		str[i]=buf[i];
	}
	str[i]= '\0';
	return str;
}

int main()
{
    	srand((long long)time(0));
	publicKey();
	privKey();
	PRIV_KEY.n1 = n;
	PRIV_KEY.d1 = d;
	PUBLIC_KEY.n2 = n;
	PUBLIC_KEY.e2 = e;
	
	char *str1,*str2;	
	
	str1 = encrypt("tran triet rat dep trai",PUBLIC_KEY);
	printf("\n_%s_\n",str1);
	str2 = decrypt(str1,PRIV_KEY);
	printf("\n_%s_\n",str2);

  	return 0;
}


















