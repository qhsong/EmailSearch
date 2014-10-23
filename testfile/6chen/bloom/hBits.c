int preBits(unsigned int code)//得到高28位,用来指示哈希表中的位置
{
	int pos = 0;
	pos = code >> 10;
	return pos;
}
