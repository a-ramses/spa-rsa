#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 256
#define M 16
#define F_STR "%04x"

void read(uint32_t *v)
{
  char a;

  for (int i = 0; i < N/M; i++)
  {
    v[N/M - 1 - i] = 0;

    for (int j = 0; j < M/4; j++)
    {
      int ai = 0;

      switch (getchar())
      {
        case '0':           ai = 0x0; break;
        case '1':           ai = 0x1; break;
        case '2':           ai = 0x2; break;
        case '3':           ai = 0x3; break;
        case '4':           ai = 0x4; break;
        case '5':           ai = 0x5; break;
        case '6':           ai = 0x6; break;
        case '7':           ai = 0x7; break;
        case '8':           ai = 0x8; break;
        case '9':           ai = 0x9; break;
        case 'a': case 'A': ai = 0xa; break;
        case 'b': case 'B': ai = 0xb; break;
        case 'c': case 'C': ai = 0xc; break;
        case 'd': case 'D': ai = 0xd; break;
        case 'e': case 'E': ai = 0xe; break;
        case 'f': case 'F': ai = 0xf; break;
        default: printf("exit\n"); exit(0);
      }

      v[N/M - 1 - i] = (v[N/M - 1 - i] << 4) | ai;
    }
  }

  // read next new line
  getchar();
}

void print(uint32_t *v, uint32_t len)
{
  for (int i = 0; i < len; i++)
    printf(F_STR, v[len - 1 - i]);

  printf("\n");
}

void add(uint32_t *a, uint32_t *b, uint32_t *c)
{
  uint32_t carry = 0;

  for (int i = 0; i < N/M; i++)
  {
    uint32_t tmp = a[i] + b[i] + carry;

    carry = tmp >> M;

    c[i] = tmp & ((1 << M) - 1);
  }

  // carry top bit
  carry = (carry << 1) | c[N/M - 1] >> (M - 1);
  c[N/M - 1] = c[N/M - 1] & ((1 << (M - 1)) - 1);


  // this *should* affect only the first niblle
  c[0] += carry * 19;
}

void mul(uint32_t *a, uint32_t *b, uint32_t *c)
{
  // double-lenght temporary result
  uint32_t tmp[2*N/M] = {0};

  uint32_t full = 0;
  uint32_t hi, lo;

  uint32_t carry = 0;


  // compute product
  for (int i = 0; i < N/M; i++)
    for (int j = 0; j < N/M; j++)
    {
      full = a[i] * b[j];

      hi = full >> M;
      lo = full & 0xffff ;

      tmp[i+j] = tmp[i+j] + lo;
      tmp[i+j+1] = tmp[i+j+1] + hi;
    }

  
  // perform all the carries
  carry = 0;

  for (int i = 0; i < 2*N/M; i++)
  {
    tmp[i] += carry;
    carry = tmp[i] >> M;
    tmp[i] = tmp[i] & ((1 << M) - 1);
  }


  // *********** Reduction modulo 2^255 - 19 ************ //

  // reduce top half of double-length result
  // we take only the elements from the  right so all top is reduced reduced   
  for (int i = 0; i < N/M; i++)
    c[i] = tmp[i] + (tmp[i+(N/M)] * 38); // lo + (38 * hi )


  // perform all the carries again
  carry = 0;

  for (int i = 0; i < N/M; i++)
  {
    c[i] += carry;
    carry = c[i] >> M;
    c[i] = c[i] & ((1 << M) - 1);
  }

  // carry new carry and 256th bit
  carry = (carry << 1) | c[N/M - 1] >> (M - 1);
  c[N/M - 1] = c[N/M - 1] & ((1 << (M - 1)) - 1);

  carry = carry * 19;


  // perform all the carries again
  for (int i = 0; i < N/M; i++)
  {
    c[i] += carry;
    carry = c[i] >> M;
    c[i] = c[i] & ((1 << M) - 1);
  }


  // carry 256th bit
  carry = (carry << 1) | c[N/M - 1] >> (M - 1);
  c[N/M - 1] = c[N/M - 1] & ((1 << (M - 1)) - 1);


  // this *should* affect only the first niblle
  c[0] += carry * 19;


  // now, c is almost compeltely reduced by 2^255-19
  // (except if c is between 2^255-19 and 2^255-1)
}

void main()
{
  while (1==1)
  {
    uint32_t a[N/M];
    uint32_t b[N/M];
    uint32_t c[2*N/M] = {0};

    read(a);
    read(b);

    char op = getchar(); getchar(); // read op and following new line

    switch (op)
    {
      case 'a': add(a, b, c);
                break;
      case 'm': mul(a, b, c);
                break;
    }

    print(a, N/M);
    print(b, N/M);
    printf("%c\n", op);
    print(c, N/M);
  }
}

