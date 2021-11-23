#ifndef INCLUDED_COMMON
#define INCLUDED_COMMON

//******************************************************************************
//
//
//      common.h
//
//
//******************************************************************************

//------< typedef >-------------------------------------------------------------

//------< マクロ関数 >-----------------------------------------------------------
#define SAFE_DELETE(x)  if(x){delete x;x=NULL;}      // メモリを解放する
#define ToRadian(x)     DirectX::XMConvertToRadians(x)  // 角度をラジアンに

//------< 定数 >----------------------------------------------------------------
#define SCREEN_WIDTH    (1280)                   // 画面の幅（スクリーンウィッズ）
#define SCREEN_HEIGHT   (720)                   // 画面の高さ（スクリーンハイト）
#define VEC4_WHITE      (VECTOR4(1, 1, 1, 1))   // 白

// シーン管理用定数
#define SCENE_TITLE     (0)
#define SCENE_GAME      (1)
#define SCENE_RANKING   (2)
#define SCENE_HAIR      (3)
#define SCENE_TUTORIAL  (4)

#endif// ! INCLUDED_COMMON

