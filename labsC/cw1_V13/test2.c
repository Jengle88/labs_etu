//#include <stdlib.h>
//#include <stdio.h>
//
//struct hoba
//{
//	char *str;
//};
//
//struct hoba2
//{
//	struct hoba *h;
//};
//
//void f(struct hoba2 *hbv2)
//{
//	free(hbv2->h->str);
//	hbv2->h->str = malloc(5*sizeof(char));
//	for (int i = 0; i < 5; ++i)
//	{
//		hbv2->h->str[i] = '0' + i + 1;
//	}
//}
//
//int main()
//{
//	struct hoba hb;
//	int n = 3;
//	hb.str = malloc(n * sizeof(char));
//	struct hoba2 hb2;
//	hb2.h = &hb;
//	for (int i = 0; i < n; ++i)
//	{
//		hb2.h->str[i] = '0' + i;
//	}
//	f(&hb2);
//	n = 5;
//	for (int i = 0; i < n; ++i)
//	{
//		printf("%c ", hb2.h->str[i]);
//	}
//}
