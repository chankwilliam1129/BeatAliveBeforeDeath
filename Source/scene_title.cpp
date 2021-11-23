//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"
#include<math.h>
//------< �ϐ� >----------------------------------------------------------------
int title_state;    // ���
int title_timer;    // �^�C�}�[
//float fadeOut; // �t�F�[�h�A�E�g�p�ϐ��̐錾

// �ʂ̃t�@�C���̕ϐ����g�p����錾
extern int nextScene;
extern int TitleBgImage1;
extern int TitleBgImage2;
extern int TitleBgImage3;
extern int TitleBgImage4;
extern int TitleBgImage5;
extern int TitleBgImage6;
extern int TitleBgImage7;
extern int TitleBgImage8;
extern int TitleBgImage9;

extern int Titlesound;
extern int hairSelect;
extern int tutorialSelect;
extern char KeyBuf[256];

extern int decision;
extern int cursor;
extern int tutorial_;
extern int game_;
extern int bgImage2;
int bgImage2_x;
int bgImage2_x2;
float light;
float x;
//--------------------------------
// �����ݒ�
//--------------------------------
void title_init()
{
	sound_load(nextScene);
	title_state = 0;
	title_timer = 0;
	TimingInit();
	bgImage2_x = 0;
	bgImage2_x2 = BG2_SIZE_X;
	// �t�F�[�h�A�E�g�p�ϐ��̏����ݒ�
	//fadeOut = 0.0f;
    light = 0;
    light = sin(x);
}

//--------------------------------
// �X�V����
//--------------------------------
void title_update()
{
	switch (title_state)
	{
	case 0:
		//////// �����ݒ� ////////
		// TODO:07 �^�C�g���̉��y���Đ�������	
		sound_play_loop(Titlesound);
		//////// ���Z�b�g ////////
		title_state++;
		break;

	case 1:
		//////// �ʏ펞 ////////
		// �L�[���͂ŃV�[���؂�ւ�
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			title_state++;		
		}
		/*if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			hair_Select_x += 100;
			title_state = 4;
		}*/
		break;
	case 2:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			title_state++;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			sound_play_back(cursor);
			title_state = 5;			
		}
		break;
	case 3:
		StopSoundMem(Titlesound);
		nextScene = SCENE_TUTORIAL;
		break;
	/*case 4:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_HAIR;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			hair_Select_x -= 100;
			title_state = 1;
		}*/
		break;
	case 5:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			StopSoundMem(Titlesound);
			nextScene = SCENE_GAME;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			sound_play_back(cursor);
			title_state = 2;
		}
		break;
	}	
	bgImage2_x -= BG_SPEED;
	bgImage2_x2 -= BG_SPEED;
	if (bgImage2_x < -BG2_SIZE_X) {
		bgImage2_x += BG2_SIZE_X * 2;
	}
	if (bgImage2_x2 < -BG2_SIZE_X) {
		bgImage2_x2 += BG2_SIZE_X * 2;
	}
	title_timer++;
	// �f�o�b�O�p������̐ݒ�
	//debug::setString("title_state:%d", title_state);
	//debug::setString("title_timer:%d", title_timer);

    light = sin(x)*255.0;
    if (sin(x) < 0) {
        x += 0.06;
    }
    else {
        x += 0.03;
    }
}

//--------------------------------
// �`�揈��
//--------------------------------
void title_draw()
{
	DrawGraph(bgImage2_x, 0, TitleBgImage1, 1);  //�w�i
	DrawGraph(bgImage2_x2, 0, TitleBgImage1, 1);  //�w�i	
	DrawGraph(0, 0, TitleBgImage2, 1);//�w�i

	DrawGraph(25, SCREEN_HEIGHT / 2 - 30, TitleBgImage3, 1);  //�w�i
	//DrawGraph(SCREEN_WIDTH / 2 - 25 , SCREEN_HEIGHT / 2 + 20, TitleBgImage4, 1);//�����G�t�F�N�g
	//DrawGraph(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 20, TitleBgImage5, 1);//gamestart
	DrawGraph(0, SCREEN_HEIGHT - 400, TitleBgImage6, 1);      //��
	DrawGraph(180, SCREEN_HEIGHT / 2 - 90, TitleBgImage7, 1); //�v���C���[
	DrawGraph(SCREEN_WIDTH / 2 - 420, 0, TitleBgImage8, 1);   //�^�C�g��
	//DrawGraph(0, 0, TitleBgImage9, 1);   //push space

	
	/*if (title_state == 1 || title_state == 4) {
		DrawGraph(hair_Select_x, 0, hairSelect, 1);
	}*/
	if (title_state == 2) {
		DrawGraph(SCREEN_WIDTH / 2 - 463, 145, tutorial_, 1);
	}
	if (title_state == 5) {
		DrawGraph(SCREEN_WIDTH / 2 - 463, 145, game_, 1);
	}

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, light);
    DrawGraph(0, 0, TitleBgImage9, 1);   //push space
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//--------------------------------
// �I������
//--------------------------------
void title_end()
{
	DeleteDraw(hairSelect);
	DeleteDraw(tutorialSelect);
	DeleteDraw(TitleBgImage1);
	DeleteDraw(TitleBgImage2);
	DeleteDraw(TitleBgImage3);
	DeleteDraw(TitleBgImage4);
	DeleteDraw(TitleBgImage5);
	DeleteDraw(TitleBgImage6);
	DeleteDraw(TitleBgImage7);
	DeleteDraw(TitleBgImage8);
	DeleteDraw(TitleBgImage9);
	DeleteDraw(game_);
	DeleteDraw(tutorial_);
	DeleteDraw(bgImage2);
}
