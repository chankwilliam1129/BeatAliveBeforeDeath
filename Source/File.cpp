//------< インクルード >---------------------------------------------------------
#include "all.h"
#include <iostream>
#include <fstream>
//------< 変数 >----------------------------------------------------------------
extern int ranking[RANKING_MAX];
extern int step_count;
int  buf[RANKING_MAX] = { 0 };

//--------------------------------
// スコア
//--------------------------------
void hiscore_load()
{
	FILE* fp = NULL;
	fp = fopen("HiScore.dat", "rb");
	fread(&buf, sizeof(int), RANKING_MAX, fp);

	for (int i = 0; i < RANKING_MAX; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ranking[i] = buf[i];
		}
	}
	fclose(fp);	
}

void hiscore_new() {
	//ファイルを仮で作成する
	//{
	//	FILE* fp = NULL;
	//	fp = fopen("HiScore.txt", "w");

	//	for (int i = 0; i < RANKING_MAX; i++)
	//	{
	//		char c = '0' + ranking[i];
	//		fputc(c, fp);
	//	}
	//	fclose(fp);
	//}

		if (step_count > ranking[RANKING_MAX])
		{
			//記録更新
			ranking_check(step_count); //順位並び替え

			FILE* fp = NULL;
			fp = fopen("HiScore.dat", "wb");

			fwrite(&ranking, sizeof(int), RANKING_MAX, fp);
			fclose(fp);
		}
}