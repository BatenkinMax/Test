#include "stdio.h"

int test(unsigned char* data, int length);
//прототип функции, 
//принимать должен массив однобайтовых элементов, лучше если это будет uint8_t,  
//в реализации длина массива не использеется, но по хорошему если передаем указатель на первый элемет, ножно передавать и длину массива

int main()
{
	int i;
	unsigned char message[15];
	unsigned char crc = 0;

	for (i = 0; i < sizeof(message)-1; i++)
	{
		if(i != 4)
			message[i] = (unsigned char)i;
		else
			message[i] = sizeof(message) - 8;
		crc ^= message[i];
	}
//	crc++;
	message[sizeof(message) - 1] = crc;

	return test(message, sizeof(message));
}

//реализация функции
int test(unsigned char* data, int length)
{
	int i;
	unsigned char N, XOR;

//все выводы здесь не нужны, представлены просто для наглядности
	
	printf("Preamble: ");
	for (i = 0; i < 4; i++)
		printf("%d", (int)data[i]);
	printf("\n");

	N = data[4];
	printf("N: %d\nSource: %d\nReceiver: %d\nCRC: %d\n", (int)data[4], (int)data[5], (int)data[6], (int)data[N + 7]);

	XOR = data[0];
	for (i = 1; i < N + 7; i++)
		XOR ^= data[i];

	if (data[N + 7] == XOR)
	{
		printf("Ok\n");
		//обработка сообщения
		//так же тут нужно продумать кто будет выделять память под собщение, и кто потом будет её освобождать
		//я бы продублировал сообщение, и не преживать что его кто-то перезапишет
	}
	else
	{
		printf("Error\n");
		//обработка ошибки
		return 1;
	}

	return 0;
}
//про время работы фкнкции мне сложно сказать, про какую-либо оптимизацию этого кода слёту затрудняюсь ответить
