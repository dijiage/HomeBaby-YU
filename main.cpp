#include "magictower.h"
#include "picture.h"

Hero hero = Hero();

int main()
{
	//��ʼ����ͼ
	init_map();
	go();


	// ����Ļ��������ַ���
	/*RECT r = { 0, 0, 200, 100 };
	drawtext(_T("Hello World�ü���������Ӧ���ĹǻҴ�ź�"), &r,   DT_WORDBREAK | DT_LEFT);

	// ��������˳�
	_getch();
	closegraph();
	*/
	return 0;
}