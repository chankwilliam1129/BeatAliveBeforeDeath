#include  "DxLib.h"
#include "all.h"

// シーン切り替え用変数の宣言
int curScene;
int nextScene;

//--------------------------------
//  WinMain（エントリポイント）
//--------------------------------
int  WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpComdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);					// ウィンドウモードに設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);				// 画面サイズの設定
	SetOutApplicationLogValidFlag(FALSE);	// Log.txt を生成しないように設定
	SetDrawScreen(DX_SCREEN_BACK);		    // 描画を裏画面に設定
	if (DxLib_Init() == 1) { return -1; }	// DxLib の初期化を実行し失敗したら終了
		
// ゲームシーンの設定										
	curScene = SCENE_TITLE;
	nextScene = SCENE_TITLE;

//画像の読み込み
	image_load(nextScene);                  //画像の読み込み

// タイトルの初期設定を行う
	title_init();
	
	while (ProcessMessage() == 0)			// メインループ
	{
		GetKeyState();
		ClearDrawScreen();					// 画面のクリア

											// ゲームシーン切り替え
		if (nextScene != curScene)			// 次フレームでシーン変更があれば
		{
			switch (curScene)				// 現シーンの終了処理を行う
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

			image_load(nextScene);          //画像の読み込み

			switch (nextScene)				// 次シーンの初期設定を行う
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
			curScene = nextScene;			// 現シーンに次シーンを代入する
		}

		// 現在のシーンに応じた更新処理
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

		// 現在のシーンに応じた描画処理
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
		ScreenFlip();						// 裏画面の表示
	}

	// 現在のシーンに応じた終了処理
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
	DxLib_End();							// DxLib の終了処理
	return 0;
}