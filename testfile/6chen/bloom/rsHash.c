unsigned int getCode(char *email)
{
	char *str = email;
        unsigned int b = 378551;
        unsigned int a = 63689;
        unsigned int hash = 0;

         while(*str != '\0')
         {
                hash = hash * a + (*str++);
                a *= b;
         }
	return hash;
}
