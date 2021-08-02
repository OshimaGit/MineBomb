#include <stdio.h>
#include <time.h>
#define VERTICAL 10
#define SIDE 10

struct Zahyo {
	int x, y;
};


int main(void) {
	//�p�l���̏����i�[
	int field[SIDE][VERTICAL];
	//�v���C���[�̍��W���i�[
	struct Zahyo player;
	//�L�[�{�[�h����̓��͂��i�[
	char input;
	//����̔��e�̐����i�[
	int bomb_num[SIDE][VERTICAL];
	//�J�����p�l���̏����i�[
	int isOpen[SIDE][VERTICAL];
	//���Ԍv��
	float clear_time;

	srand((unsigned int)time(NULL));
	//���Ԃ̌v���J�n
	clear_time = (float)clock()/CLOCKS_PER_SEC;

	//�v���C���[�̈ʒu�̏�����
	player.x = 0;
	player.y = 0;

	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < SIDE; j++) {
			//bomb_num�̏�����
			bomb_num[j][i] = 0;
			//isOpen�̏�����
			isOpen[j][i] = 0;
			//field�̏�����
			field[j][i] = 0;
		}
	}
	//���e�̈ʒu������
	for (int i = 0; i < 6; i++) {
		field[rand() % SIDE][rand() % VERTICAL] = 1;
	}

	while (1) {
		system("cls");
		for (int i = 0; i < VERTICAL; i++) {
			for (int j = 0; j < SIDE; j++) {
				//�v���C���[�̈ʒu�ɂ́���\��
				if (player.x == j && player.y == i)printf("��");
				//���łɊJ�����p�l���Ȃ琔�l��\��
				else if (isOpen[j][i]) printf("%2d", bomb_num[j][i]);
				//����ȊO�́���\��
				else printf("��");
			}
			puts("");
		}
		//�������
		printf("��:W, ��:S, ��:D, ��:A, E:�p�l�����߂���\n");
		//scanf���g�p�ł��Ȃ��̂�scanf_s���g�p���Ă���
		scanf_s("%c", &input);
		switch (input) {
		case 'w':if (player.y > 0)player.y--; break;
		case 's':if (player.y < VERTICAL - 1)player.y++; break;
		case 'd':if (player.x < SIDE - 1)player.x++; break;
		case 'a':if (player.x > 0)player.x--; break;
		case 'e':if (!isOpen[player.x][player.y]) {
			isOpen[player.x][player.y] = 1;
			//�v���C���[�̃}�X�����e�łȂ��ꍇ�A����̔��e�̐����v�Z
			if (field[player.x][player.y] == 0) {
				if (player.x != SIDE - 1 && player.y != VERTICAL - 1 && field[player.x + 1][player.y + 1])bomb_num[player.x][player.y]++;
				if (player.x != SIDE - 1 && field[player.x + 1][player.y])bomb_num[player.x][player.y]++;
				if (player.x != SIDE - 1 && player.y != 0 && field[player.x + 1][player.y - 1])bomb_num[player.x][player.y]++;
				if (player.y != VERTICAL - 1 && field[player.x][player.y + 1])bomb_num[player.x][player.y]++;
				if (player.y != 0 && field[player.x][player.y - 1])bomb_num[player.x][player.y]++;
				if (player.x != 0 && player.y != VERTICAL - 1 && field[player.x - 1][player.y + 1])bomb_num[player.x][player.y]++;
				if (player.x != 0 && field[player.x - 1][player.y])bomb_num[player.x][player.y]++;
				if (player.x != 0 && player.y != 0 && field[player.x - 1][player.y - 1])bomb_num[player.x][player.y]++;
			}
			//�v���C���[�̃}�X�����e�̏ꍇ�A�Q�[���I�[�o�[
			else if (field[player.x][player.y] == 1) {
				printf("�Q�[���I�[�o�[");
				return(0);
			}
			//���e�̃p�l���ȊO�����ׂĊJ����ƃN���A
			int isClear = 1;
			for (int i = 0; i < SIDE; i++) {
				for (int j = 0; j < VERTICAL; j++) {
					if (!isOpen[j][i] && field[j][i] == 0) isClear = 0;
				}
			}
			
			if (isClear) {
				clear_time = (float)clock() / CLOCKS_PER_SEC - clear_time;
				puts("�N���A");
				printf("�N���A�^�C���F%.1f�b\n", clear_time);
				return(0);
			}
		}break;
		}
	}
	return(0);
}
