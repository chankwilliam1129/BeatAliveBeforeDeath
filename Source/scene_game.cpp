#include "all.h"
//�ς��� UI.cpp scenegame.cpp scene tutorial.cpp image.cpp 

//------< �ϐ� >----------------------------------------------------------------
int game_state;     // ���
int game_timer;     // �^�C�}�[
int step_count;     // �X�R�A
int judge_timer;
int ground_timer;
int bg_sound;
extern int nextScene;
extern char KeyBuf[256];
extern int GrHandle[24];
//player
extern int PlHandle[8];
extern int PlHandle2[8];
extern int PlHandle3[8];
extern int PlHandle4[8];
extern int PlHandle5[8];
extern int Dash_Handle[10];
extern int bgImage; //BG
extern int bgImage2;
extern int UiImage1;
extern int UiImage2;
extern int UiHandle3[8];
extern int effectHandle[16];//sound
extern int decision;
extern int score_board;
extern int score_num[10];
extern int dead[4];
extern int BgHandle[8];
extern int point[8];
extern int GoalHandle[8];
extern int rocketHandle[8];
extern int J_PlHandle[8];
extern int die;
//--------------------------------
// �����ݒ�
//--------------------------------
void game_init()
{
	sound_load(nextScene);
	game_state = 0;
	game_timer = 0;
	step_count = 0;
	judge_timer = 0;
	ground_timer = 0;
}
//--------------------------------
// �Q�[����
//--------------------------------
void game_common()
{
	// �v���C���[�̍X�V
	player_update();

	// BG�̍X�V
	bg_update();
	// �G�̍X�V
	//�T�E���h
	sound_update();

	// �G�t�F�N�g�̍X�V
	effect_update();
	//UI�̏����ݒ�
	ui_update();
	// �����蔻��֐����Ă�
	
}

//--------------------------------
// �X�V����
//--------------------------------
void game_update()
{
	switch (game_state)
	{
	case 0:
		TimingInit(); 
		//////// �����ݒ� ////////
	// �v���C���[�i���@�j�̏����ݒ�
		player_init();
		// �G�̏����ݒ�		

		// �G�t�F�N�g�̏����ݒ�
		effect_init();
		//UI�̏����ݒ�
		ui_init();
		// ground�̏����ݒ�
		ground_init();
		// BG�̏����ݒ�
		bg_init();
		// TODO:09 �Q�[�����̉��y���Đ�������
		
		game_state++;
		break;

	case 1:
		//////// �ʏ펞 ////////
		game_common();
		break;

	case 2:
		//////// �����L���O ////////
		if (KeyBuf[KEY_INPUT_SPACE] == 1)
		{
			sound_play_back(decision);
			//�����L���O��\��
			//hiscore_load();
			nextScene = SCENE_RANKING;
		}
		game_common();
		break;
	}
	game_timer++;
	judge_timer++;
	ground_timer++;
}
//--------------------------------
// �`�揈��
//--------------------------------
void game_draw()
{	
	// BG�̕`��i�n�㕨�j
	bg_draw();
	// �G�̕`��i�n�㕨�j
	ground_draw();
	// BG�̕`��i�󒆕��j

	// �G�̕`��i�󒆕��j
	
	// �v���C���[�̕`��
	player_draw();
	// UI�̕`��
	ui_draw();
	// �G�t�F�N�g�̕`��
	effect_draw();
}

//--------------------------------
// �I������
//--------------------------------
void game_end(){
	DeleteDraw(bgImage);
	DeleteDraw(bgImage2);
	DeleteDraw(GrHandle[24]);
	DeleteDraw(PlHandle[8]);
	DeleteDraw(PlHandle2[8]);
	DeleteDraw(PlHandle3[8]);
	DeleteDraw(PlHandle4[8]);
	DeleteDraw(PlHandle5[8]);
	DeleteDraw(UiImage1);
	DeleteDraw(UiImage2);
	DeleteDraw(UiHandle3[8]);
	DeleteDraw(effectHandle[6]);
	DeleteDraw(Dash_Handle[10]);
	DeleteDraw(score_board);
	DeleteDraw(score_num[10]);
	DeleteDraw(dead[4]);
	DeleteDraw(point[8]);
	DeleteDraw(rocketHandle[8]);
	DeleteDraw(BgHandle[8]);
	DeleteDraw(GoalHandle[8]);
	DeleteDraw(J_PlHandle[8]);	
	DeleteDraw(die);

}
