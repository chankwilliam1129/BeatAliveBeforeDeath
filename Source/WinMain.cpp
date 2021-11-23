#include  "DxLib.h"
#include "all.h"

// �V�[���؂�ւ��p�ϐ��̐錾
int curScene;
int nextScene;

//--------------------------------
//  WinMain�i�G���g���|�C���g�j
//--------------------------------
int  WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpComdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);					// �E�B���h�E���[�h�ɐݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);				// ��ʃT�C�Y�̐ݒ�
	SetOutApplicationLogValidFlag(FALSE);	// Log.txt �𐶐����Ȃ��悤�ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);		    // �`��𗠉�ʂɐݒ�
	if (DxLib_Init() == 1) { return -1; }	// DxLib �̏����������s�����s������I��
		
// �Q�[���V�[���̐ݒ�										
	curScene = SCENE_TITLE;
	nextScene = SCENE_TITLE;

//�摜�̓ǂݍ���
	image_load(nextScene);                  //�摜�̓ǂݍ���

// �^�C�g���̏����ݒ���s��
	title_init();
	
	while (ProcessMessage() == 0)			// ���C�����[�v
	{
		GetKeyState();
		ClearDrawScreen();					// ��ʂ̃N���A

											// �Q�[���V�[���؂�ւ�
		if (nextScene != curScene)			// ���t���[���ŃV�[���ύX�������
		{
			switch (curScene)				// ���V�[���̏I���������s��
			{
			case SCENE_TITLE:
				title_end();
				break;
			case SCENE_GAME:
				game_end();
				break;
			case SCENE_RANKING:
				ranking_end();
				break;
			case SCENE_HAIR:
				hair_end();
				break;
			case SCENE_TUTORIAL:
				tutorial_end();
				break;
			}

			image_load(nextScene);          //�摜�̓ǂݍ���

			switch (nextScene)				// ���V�[���̏����ݒ���s��
			{
			case SCENE_TITLE:
				title_init();
				break;
			case SCENE_GAME:
				game_init();
				break;
			case SCENE_RANKING:
				ranking_init();
				break;
			case SCENE_HAIR:
				hair_init();
				break;
			case SCENE_TUTORIAL:
				tutorial_init();
				break;
			}
			curScene = nextScene;			// ���V�[���Ɏ��V�[����������
		}

		// ���݂̃V�[���ɉ������X�V����
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			break;
		case SCENE_GAME:
			game_update();
			break;
		case SCENE_RANKING:
			ranking_update();
			break;
		case SCENE_HAIR:
			hair_update();
			break;
		case SCENE_TUTORIAL:
			tutorial_update();
			break;
		}

		// ���݂̃V�[���ɉ������`�揈��
		switch (curScene)
		{
		case SCENE_TITLE:
			title_draw();			
			break;
		case SCENE_GAME:
			game_draw();
			break;
		case SCENE_RANKING:
			ranking_draw();
			break;
		case SCENE_HAIR:
			hair_draw();
			break;
		case SCENE_TUTORIAL:
			tutorial_draw();
			break;
		}
		ScreenFlip();						// ����ʂ̕\��
	}

	// ���݂̃V�[���ɉ������I������
	switch (curScene)
	{
	case SCENE_TITLE:
		title_end();
		break;
	case SCENE_GAME:
		game_end();
		break;
	case SCENE_RANKING:
		ranking_end();
		break;
	case SCENE_HAIR:
		hair_end();
		break;
	case SCENE_TUTORIAL:
		tutorial_end();
		break;
	}
	DxLib_End();							// DxLib �̏I������
	return 0;
}