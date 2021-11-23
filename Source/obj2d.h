#ifndef INCLUDED_OBJ2D
#define INCLUDED_OBJ2D

struct OBJ2D {
	
	VECTOR texPos;         // �摜�ʒu
	VECTOR texSize;        // �摜�T�C�Y
	VECTOR texPivot;       // �摜�̊�_
	int     anime;          // �A�j���[�V�����p�i���j
	int anime2;
	int jump_anime;
	int     type;           // �^�C�v
	int       hp;
	BOOL    exist;          // ���݃t���O

	// �ėp�I�Ȃ���
	VECTOR pos;            // �ʒu
	VECTOR scale;          // �X�P�[��
	float   angle;          // �p�x
	VECTOR color;          // �F�ixyzw���ꂼ��rgba�j
	float   radius;         // ���a
	int     state;          // ��ԑJ�ڗp
	int     timer;          // �^�C�}�[
    int jump_timer;
    int skip_timer;
	VECTOR speed;          // ���x
	int     cnt;            // �ėp�J�E���^�i�g�����͎��R�j
	BOOL    hostilityFg;    // �G�t���O�i���񂩂�ǉ��j

    int pos_number;
	VECTOR draw_pos;
	int pos_before;
	int pos_after;
	float distance;
	int dash_anime;
	VECTOR spos;
	int skip_anime;
	int GRAVITY;
	float FRICTION;
	bool dead_flg;
	int state2;
	VECTOR dead_pos;
};
struct Box {
	int number;
	int type;
	int height;
	bool ground_flg; //�n��
	bool ground_flg2;
	bool goal_flg; //clear
	bool next_light;
	bool next_Red_light;
};

#endif // !INCLUDED_SCENE_GAME