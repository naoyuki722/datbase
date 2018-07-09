#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 文字列の大きさ */
#define STRING_LENGTH (79)
/* personalData配列の大きさ */
#define ARRAY_LENGTH (50)

/**
 * PersonalData 構造体
 * 	name        名前
 * 	postCode    郵便番号
 * 	address     住所
 * 	phoneNumber 電話番号
 */
typedef struct {
	char name[STRING_LENGTH];
	char postCode[STRING_LENGTH];
	char address[STRING_LENGTH];
	char phoneNumber[STRING_LENGTH];
} PersonalData;

/**
 * 一括データ挿入関数(PersonalData)
 * @param  name        名前
 * @param  postCode    郵便番号
 * @param  address     住所
 * @param  phoneNumber 電話番号
 */
PersonalData Init(char name[], char postCode[],
		char address[], char phoneNumber[]) {
	PersonalData tmp;
	strcpy(tmp.name, name);
	strcpy(tmp.postCode, postCode);
	strcpy(tmp.address, address);
	strcpy(tmp.phoneNumber, phoneNumber);
	return tmp;
}

/**
 * 関数1
 * 機能選択
 * @param data PersonalData配列
 */
void ChooseFuction(PersonalData *data);

/**
 * 関数2
 * 新規データ入力
 * @param  data PersonalData配列
 */
void InputData(PersonalData *data);

/**
 * 関数3
 * データ保存
 * @param data PersonalData配列
 */
void OutputData(PersonalData *data);

/**
 * 関数4
 * データ読み込み
 * @param  data PersonalData配列
 */
void ReadData(PersonalData *data);

/** カウンタ */
int count = 0;

/**
 * main関数
 * @return  0
 */
int main(void) {
	PersonalData data[ARRAY_LENGTH];
	ChooseFuction(data);
	return 0;
}

/* 関数1 */
void ChooseFuction(PersonalData *data) {
	/* 無限ループ */
	while(1) {
		/* メニュー表示 */
		printf("処理を選んでください\n");
		printf(" - 1.新規データ入力\n");
		printf(" - 2.ファイルを保存\n");
		printf(" - 3.ファイルを読み込む\n");
		printf(" - 4.プログラムを終了\n > ");

		/* 選択番号の読み込み */
		int functionNumber;
		scanf("%d", &functionNumber);

		/* 選択処理 */
		switch(functionNumber) {
			case 1:
				InputData(data);
				break;
			case 2:
				OutputData(data);
				break;
			case 3:
				ReadData(data);
				break;
			case 4:
				printf("プログラムを終了します\n");
				exit(0);
			default:
				printf("正しい番号を入力してください\n");
		}
	}
}

/* 関数2 */
void InputData(PersonalData *data) {
	/* カウンタがARRAY_LENGTHあるいは、名前入力時に'\n'が入力されると終了 */
	count = 0;
	while(count <= ARRAY_LENGTH) {
		/* gets関数の警告回避 */
		char tmp[2];
		gets(tmp);
		/********************/

		/* 各項目の入力 */
		printf("name > ");
		char name[STRING_LENGTH];
		gets(name);
		if(!strcmp(name, "\0")) {
			break;
		}
		printf("post code > ");
		char postCode[STRING_LENGTH];
		gets(postCode);
		printf("address > ");
		char address[STRING_LENGTH];
		gets(address);
		printf("phone number > ");
		char phoneNumber[STRING_LENGTH];
		gets(phoneNumber);

		/* データの一括挿入 */
		data[count] = Init(name, postCode, address, phoneNumber);

		/* データの表示 */
		printf("%s %s %s %s\n",
			data[count].name, data[count].postCode,
			data[count].address, data[count].phoneNumber);

		count++;
	}
}

/* 関数3 */
void OutputData(PersonalData *data) {
	/* ファイル操作 */
	printf("保存するファイル名を入力 > ");
	char fileName[STRING_LENGTH];
	scanf("%s", fileName);
	FILE *out;
	out = fopen(fileName, "w");
	if(out == NULL) {
		printf("ファイルを開くことができません\n");
		exit(1);
	}

	/* データ書き込み */
	int i = 0;
	for(i = 0; i < count; i++) {
		fprintf(out, "%s %s %s %s\n",
			data[i].name, data[i].postCode,
			data[i].address, data[i].phoneNumber);
	}
	printf("書き込みが完了しました\n\n");
	fclose(out);
}

/* 関数4 */
void ReadData(PersonalData *data) {
	/* ファイル操作 */
	printf("ファイル名を入力 > ");
	char fileName[STRING_LENGTH];
	scanf("%s", fileName);
	printf("\n");
	FILE *in;
	in = fopen(fileName, "r");
	if(in == NULL) {
		printf("ファイルを開くことができません\n");
	}

	/* 行読み込み用 */
	char str[400];

	/* データを読み込み、構造体変数に格納 */
	int i = 0;
	while((fgets(str, 400, in)) != NULL) {
		printf("%s", str);
		char *tmp;
		tmp = strtok(str, " \n");
		strcpy(data[i].name, tmp);
		tmp = strtok(NULL, " \n");
		strcpy(data[i].postCode, tmp);
		tmp = strtok(NULL, " \n");
		strcpy(data[i].address, tmp);
		tmp = strtok(NULL, " \n");
		strcpy(data[i].phoneNumber, tmp);
		i++;
	}
	count = i;
	printf("\n");
	printf("ファイルを読み込みました\n");
	fclose(in);
}
