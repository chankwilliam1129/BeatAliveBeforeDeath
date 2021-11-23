//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"
#include <iostream>
#include <fstream>
//------< �ϐ� >----------------------------------------------------------------
extern int ranking[RANKING_MAX];
extern int step_count;
int  buf[RANKING_MAX] = { 0 };

//--------------------------------
// �X�R�A
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
	//�t�@�C�������ō쐬����
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
			//�L�^�X�V
			ranking_check(step_count); //���ʕ��ёւ�

			FILE* fp = NULL;
			fp = fopen("HiScore.dat", "wb");

			fwrite(&ranking, sizeof(int), RANKING_MAX, fp);
			fclose(fp);
		}
}