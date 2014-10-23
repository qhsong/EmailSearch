short postBits(unsigned int code)//得到低12位，存放在哈希表的节点中
{
	short value = 0;
	value = code & 0x000003FF;
	return value;
}
