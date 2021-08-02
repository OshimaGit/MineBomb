#include <stdio.h>
#include <time.h>
#define VERTICAL 10
#define SIDE 10

struct Zahyo {
	int x, y;
};


int main(void) {
	//パネルの情報を格納
	int field[SIDE][VERTICAL];
	//プレイヤーの座標を格納
	struct Zahyo player;
	//キーボードからの入力を格納
	char input;
	//周りの爆弾の数を格納
	int bomb_num[SIDE][VERTICAL];
	//開けたパネルの情報を格納
	int isOpen[SIDE][VERTICAL];
	//時間計測
	float clear_time;

	srand((unsigned int)time(NULL));
	//時間の計測開始
	clear_time = (float)clock()/CLOCKS_PER_SEC;

	//プレイヤーの位置の初期化
	player.x = 0;
	player.y = 0;

	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < SIDE; j++) {
			//bomb_numの初期化
			bomb_num[j][i] = 0;
			//isOpenの初期化
			isOpen[j][i] = 0;
			//fieldの初期化
			field[j][i] = 0;
		}
	}
	//爆弾の位置を決定
	for (int i = 0; i < 6; i++) {
		field[rand() % SIDE][rand() % VERTICAL] = 1;
	}

	while (1) {
		system("cls");
		for (int i = 0; i < VERTICAL; i++) {
			for (int j = 0; j < SIDE; j++) {
				//プレイヤーの位置には□を表示
				if (player.x == j && player.y == i)printf("□");
				//すでに開いたパネルなら数値を表示
				else if (isOpen[j][i]) printf("%2d", bomb_num[j][i]);
				//それ以外は■を表示
				else printf("■");
			}
			puts("");
		}
		//操作入力
		printf("↑:W, ↓:S, →:D, ←:A, E:パネルをめくる\n");
		//scanfが使用できないのでscanf_sを使用している
		scanf_s("%c", &input);
		switch (input) {
		case 'w':if (player.y > 0)player.y--; break;
		case 's':if (player.y < VERTICAL - 1)player.y++; break;
		case 'd':if (player.x < SIDE - 1)player.x++; break;
		case 'a':if (player.x > 0)player.x--; break;
		case 'e':if (!isOpen[player.x][player.y]) {
			isOpen[player.x][player.y] = 1;
			//プレイヤーのマスが爆弾でない場合、周りの爆弾の数を計算
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
			//プレイヤーのマスが爆弾の場合、ゲームオーバー
			else if (field[player.x][player.y] == 1) {
				printf("ゲームオーバー");
				return(0);
			}
			//爆弾のパネル以外をすべて開けるとクリア
			int isClear = 1;
			for (int i = 0; i < SIDE; i++) {
				for (int j = 0; j < VERTICAL; j++) {
					if (!isOpen[j][i] && field[j][i] == 0) isClear = 0;
				}
			}
			
			if (isClear) {
				clear_time = (float)clock() / CLOCKS_PER_SEC - clear_time;
				puts("クリア");
				printf("クリアタイム：%.1f秒\n", clear_time);
				return(0);
			}
		}break;
		}
	}
	return(0);
}
