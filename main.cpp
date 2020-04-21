#include "magictower.h"
#include "picture.h"

Hero hero = Hero();

int main()
{
	//初始化地图
	init_map();
	go();


	// 在屏幕中央输出字符串
	/*RECT r = { 0, 0, 200, 100 };
	drawtext(_T("Hello World好几个交换反应他的骨灰存放和"), &r,   DT_WORDBREAK | DT_LEFT);

	// 按任意键退出
	_getch();
	closegraph();
	*/
	return 0;
}