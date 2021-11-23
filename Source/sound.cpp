//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< 変数 >----------------------------------------------------------------
int Titlesound;
int firstSound;
int secondSound;
int jump;
int skip;
bool jump_SoundCheck = false;
bool skip_SoundCheck = false;
int decision;
int cursor;
int rankingBG;
int impact;
int dead_sound;

extern int judge_loop;
extern int judge_timer;
extern OBJ2D player;
extern int tutorial_restart;
//--------------------------------
// 初期設定
//--------------------------------
void sound_load(int nextScene)
{
	switch (nextScene) {
	case SCENE_TITLE:
		Titlesound = LoadSoundMem(L".\\Data\\sound\\title.mp3");
		decision = LoadSoundMem(L".\\Data\\sound\\decision.mp3");
		cursor = LoadSoundMem(L".\\Data\\sound\\cursor.mp3");
		break;
	case SCENE_GAME:
		firstSound = LoadSoundMem(L".\\Data\\sound\\first.mp3");
		secondSound = LoadSoundMem(L".\\Data\\sound\\second.mp3");
		jump = LoadSoundMem(L".\\Data\\sound\\suzu.mp3");
		skip = LoadSoundMem(L".\\Data\\sound\\skip.mp3");
		dead_sound = LoadSoundMem(L".\\Data\\sound\\miss.wav");
		break;
	case SCENE_RANKING:
		rankingBG = LoadSoundMem(L".\\Data\\sound\\ranking.mp3");
		decision = LoadSoundMem(L".\\Data\\sound\\decision.mp3");
		cursor = LoadSoundMem(L".\\Data\\sound\\cursor.mp3");
		impact = LoadSoundMem(L".\\Data\\sound\\impact.mp3");
		break;
	case SCENE_HAIR:
		break;
	case SCENE_TUTORIAL:
		firstSound = LoadSoundMem(L".\\Data\\sound\\first.mp3");
		secondSound = LoadSoundMem(L".\\Data\\sound\\second.mp3");
		jump = LoadSoundMem(L".\\Data\\sound\\suzu.mp3");
		skip = LoadSoundMem(L".\\Data\\sound\\skip.mp3");
		dead_sound = LoadSoundMem(L".\\Data\\sound\\miss.wav");
	}

}

//--------------------------------
// 更新処理
//--------------------------------
void sound_update()
{
	if (judge_timer == 1) { jump_SoundCheck = false; }
	if (judge_timer == 1) { skip_SoundCheck = false; }
	
	if (player.exist == TRUE && judge_timer == 0 + 4)
	{
		sound_play_back(firstSound);
	}
	if (player.exist == TRUE && judge_timer == judge_loop / 2 + 4) 
	{
		sound_play_back(secondSound);
	}
	if (player.exist == TRUE && player_state_check() == JUMP && jump_SoundCheck == false) {
		sound_play_back(jump);
		jump_SoundCheck = true;
	}
	if (tutorial_restart != 1) {
		if (player.exist == TRUE && player_state_check() == SKIP && skip_SoundCheck == false || player_state_check() == JUMPSKIP && skip_SoundCheck == false) {
			sound_play_back(skip);
			skip_SoundCheck = true;
		}
	}
	
}
//--------------------------------
// サウンドプレイ
//--------------------------------
void sound_play_loop(int loop) {
	PlaySoundMem(loop, DX_PLAYTYPE_LOOP, 1);
}
void sound_play_normal(int normal) {
	PlaySoundMem(normal, DX_PLAYTYPE_NORMAL, 1);
}
void sound_play_back(int back) {
	PlaySoundMem(back, DX_PLAYTYPE_BACK, 1);
}
//--------------------------------
// 終了処理
//--------------------------------
void sound_end()
{
}
