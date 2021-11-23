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

//------< �}�N���֐� >-----------------------------------------------------------
#define SAFE_DELETE(x)  if(x){delete x;x=NULL;}      // ���������������
#define ToRadian(x)     DirectX::XMConvertToRadians(x)  // �p�x�����W�A����

//------< �萔 >----------------------------------------------------------------
#define SCREEN_WIDTH    (1280)                   // ��ʂ̕��i�X�N���[���E�B�b�Y�j
#define SCREEN_HEIGHT   (720)                   // ��ʂ̍����i�X�N���[���n�C�g�j
#define VEC4_WHITE      (VECTOR4(1, 1, 1, 1))   // ��

// �V�[���Ǘ��p�萔
#define SCENE_TITLE     (0)
#define SCENE_GAME      (1)
#define SCENE_RANKING   (2)
#define SCENE_HAIR      (3)
#define SCENE_TUTORIAL  (4)

#endif// ! INCLUDED_COMMON

