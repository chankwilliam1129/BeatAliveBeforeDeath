// ------< �C���N���[�h >-------------------------------------------------------- -
#include "all.h"

//------< �ϐ� >----------------------------------------------------------------
int tutorial_state;
extern int judge_timer;
extern int ground_timer;
extern int nextScene;
extern char KeyBuf[256];
extern int GrHandle[24];
//player
extern int PlHandle[8];
extern int PlHandle2[8];
extern int PlHandle3[8];
extern int PlHandle4[8];
extern int PlHandle5[8];
extern int UiImage1;
extern int UiImage2;
extern int UiHandle3[8];
extern int effectHandle[6];
extern int Dash_Handle[10];
extern int Tutorial_1_explain[5];
extern int Tutorial_2_explain[5];
extern int Tutorial_3_explain[7];
extern int Tutorial_retry;
extern int enterskip;

int explain_state;
extern int bgImage; //BG					//sound
bool tutorial_check = false;
bool tutorial_explain_check;
extern int tutorial_restart;
extern OBJ2D player;
extern bool tutorial3_end;
extern int decision;
extern int dead[4];
extern int point[8];

int tutorial_timer;
extern int judge_loop;
//--------------------------------
// �����ݒ�
//--------------------------------
void tutorial_init() {
	sound_load(nextScene);
	tutorial_state = 0;
	judge_timer = 0;
	tutorial_timer = 0;
	ground_timer = 0;
	explain_state = -1;
	judge_loop = JUDGE_LOOP;
	tutorial_check = true;
	tutorial_explain_check = false;
}

//--------------------------------
// �Q�[����
//--------------------------------
void tutorial_common()
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
	//UI�̍X�V
	ui_update();
	// �����蔻��֐����Ă�
}
//--------------------------------
// �X�V����
//--------------------------------
void tutorial_update() 
{
	switch(tutorial_state)
	{
	case 0:
		//////// �����ݒ� ////////
		TimingInit();            
		tutorial_explain_check = false;
		// �v���C���[�i���@�j�̏����ݒ�
		player_init();
		// ground�̏����ݒ�
		
		// �X�e�[�W�̏����ݒ�

		effect_init();
		//UI�̏����ݒ�
		ui_init();
		// BG�̏����ݒ�
		bg_init();
		// TODO:09 �Q�[�����̉��y���Đ�������
		if (tutorial_restart > 0) 
		{
			tutorial_state = tutorial_restart;
		}
		else 
		{
			tutorial_state++;
		}
		break;
	case 1://jump
		//////// �ʏ펞 ////////
		if (KeyBuf[KEY_INPUT_RETURN] == 1) 
		{
			tutorial_state = 5;
		}
		Tutorial_1_init();
		if (tutorial_explain_check == false)
		{
			tutorial_explain();
		}
		else 
		{
			tutorial_common();
		}
		break;

	case 2://skip
		if (KeyBuf[KEY_INPUT_RETURN] == 1) 
		{
			tutorial_state = 5;
		}
		Tutorial_2_init();
		if (tutorial_explain_check == false) 
		{
			tutorial_explain();
		}
		else 
		{
			tutorial_common();
		}
		break;

	case 3://mix
		if (KeyBuf[KEY_INPUT_RETURN] == 1) 
		{
			tutorial_state = 5;
		}
		Tutorial_3_init();
		if (tutorial_explain_check == false) 
		{
			tutorial_explain();
		}
		else 
		{
			tutorial_common();
		}
		break;

	case 4://���S	
		if (KeyBuf[KEY_INPUT_RETURN] == 1)
		{
			tutorial_state = 5;
		}

		if (KeyBuf[KEY_INPUT_SPACE] == 1) 
		{
			sound_play_back(decision);
			tutorial_state = 0;
		}
		break;

	case 5://�V�[���؂�ւ�
			tutorial_check = false;
			tutorial_restart = 0;
			nextScene = SCENE_GAME;
		break;
	}
	judge_timer++;
	tutorial_timer++;
	ground_timer++;
}
//--------------------------------
// �`�揈��
//--------------------------------
void tutorial_draw() {
	//if (tutorial_explain_check == true) {
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

		tutorial_explain_draw();
		if (goal_check(player) == 1) { clear_draw(); }
	//}
}
//--------------------------------
// �I������
//--------------------------------
void tutorial_end() {
	DeleteDraw(bgImage);
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
	DeleteDraw(Tutorial_1_explain[7]);
	DeleteDraw(Tutorial_2_explain[5]);
	DeleteDraw(Tutorial_3_explain[4]);
	DeleteDraw(enterskip);
	DeleteDraw(dead[4]);
	DeleteDraw(point[8]);
	DeleteDraw(Tutorial_retry);
	
}

//--------------------------------
// �`���[�g���A������
//--------------------------------
void tutorial_explain() {
	switch (explain_state) {
	case -1:
		explain_state++;
		break;

	case 0:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			explain_state++;
		}
		break;
	case 1:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			explain_state++;
		}
		break;
	case 2:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			if (tutorial_restart == 3) {
				tutorial_explain_check = true;
				explain_state = -1;
			}
			else explain_state++;
		}
		break;

	case 3:			
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);			
			if (tutorial_restart == 2) {
				tutorial_explain_check = true;
				explain_state = -1;
			}
			else explain_state++;
		}
		break;	
	case 4:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			explain_state++;
		}
		break;
	case 5:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			if (tutorial_restart == 1) {
				tutorial_explain_check = true;
				explain_state = -1;
			}
			else explain_state++;
		}
		break;
	case 6:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			explain_state++;
		}
		break;

	
	//case 4:
	//	if (KeyBuf[KEY_INPUT_SPACE] == 1) {
	//		sound_play_back(decision);
	//		if (tutorial_restart == 1){
	//			tutorial_explain_check = true;
	//			explain_state = -1;
	//		}
	//	}
	//	break;
	}		
}

void tutorial_explain_draw() {
	switch (tutorial_restart) {
	case 1:
		if (explain_state >= 0) {
			DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_1_explain[explain_state], TRUE);
		}
		break;
	case 2:
		if (explain_state >= 0) {
			DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_2_explain[explain_state], TRUE);
		}
		break;
	case 3:
		if (explain_state >= 0) {
			DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_3_explain[explain_state], TRUE);
		}
		break;
	}
}
void clear_draw() {
	if (tutorial_state == 1) {
		DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_1_explain[6], TRUE);
	}
	if (tutorial_state == 2) {
		DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_2_explain[4], TRUE); 
	}
	if (tutorial_state == 3) {
		DrawGraphF(0, SCREEN_HEIGHT / 2 - 100, Tutorial_3_explain[3], TRUE); 
	}
}