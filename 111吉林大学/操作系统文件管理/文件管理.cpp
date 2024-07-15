#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LEN 100
#define MAX_NAME_LEN 50

// �ļ����ƿ�ṹ��
typedef struct {
    char name[MAX_NAME_LEN];
    char path[MAX_PATH_LEN];  // �ļ�·��
    int is_directory;
    // �������������Ҫ����Ϣ
} FCB;

// ȫ�ֱ���
char current_path[MAX_PATH_LEN];  // ��ǰ����Ŀ¼·����Ĭ��Ϊ��

// ��������
void initialize();
void create_file(char *name, int is_directory);
void delete_file(char *name);
FCB* find_node(char *name);
FCB* find_file(char *name);
void move_file_or_directory(char *source_name, char *dest_name);
void list_directory_contents();
void copy_directory(char *source_name, char *dest_name);
void change_dir(char *path);
void go_back();
void display_current_path();

// ʾ���ļ��ļ�ϵͳ���ݽṹ
#define MAX_FILES 100
FCB filesystem[MAX_FILES];
int file_count = 0;

int main() {
    int choice;
    char name[MAX_NAME_LEN];
    initialize();  // ��ʼ���ļ�ϵͳ

    FCB *file;  // �ڴ˴���������

	char option[5];
    do {
        
        printf("\n�ļ�����ϵͳ�˵�\n");
        printf("cre. �����ļ�/Ŀ¼\n");
        printf("del. ɾ���ļ�/Ŀ¼\n");
        printf("fnd. ���ҽڵ�\n");
        printf("fle. �����ļ�\n");
        printf("mov. �ƶ��ļ�/Ŀ¼\n");
        printf("lst. �г�Ŀ¼����\n");
        printf("cpy. ����Ŀ¼\n");
        printf("cd.  �ı䵱ǰĿ¼\n");
        printf("pwd. ��ʾ��ǰ·��\n");
        printf("exit. �˳�\n");
        printf("\n"); 
        display_current_path();  // ��ʾ��ǰ·��
        printf("����������ѡ��: ");
        
        scanf("%s", option);

        if (strcmp(option, "cre") == 0) {
            printf("������Ҫ�������ļ�/Ŀ¼����: ");
            scanf("%s", name);
            printf("��Ŀ¼�𣿣�1��ʾ�ǣ�0��ʾ��: ");
            int is_directory;
            scanf("%d", &is_directory);
            create_file(name, is_directory);
        } else if (strcmp(option, "del") == 0) {
            printf("������Ҫɾ�����ļ�/Ŀ¼����: ");
            scanf("%s", name);
            delete_file(name);
        } else if (strcmp(option, "fnd") == 0) {
            printf("������Ҫ���ҵĽڵ�����: ");
            scanf("%s", name);
            if (find_node(name) != NULL)
                printf("�ҵ��ڵ㡣\n");
            else
                printf("δ�ҵ��ڵ㡣\n");
        } else if (strcmp(option, "fle") == 0) {
            printf("������Ҫ���ҵ��ļ���: ");
            scanf("%s", name);
            file = find_file(name);
            if (file != NULL) {
                printf("�ҵ��ļ� '%s'��·��Ϊ '%s'��\n", file->name, file->path);
            } else {
                printf("δ�ҵ��ļ���\n");
            }
        } else if (strcmp(option, "mov") == 0) {
            printf("������Դ�ļ�/Ŀ¼����: ");
            scanf("%s", name);
            printf("������Ŀ���ļ�/Ŀ¼����: ");
            char dest_name[MAX_NAME_LEN];
            scanf("%s", dest_name);
            move_file_or_directory(name, dest_name);
        } else if (strcmp(option, "lst") == 0) {
            list_directory_contents();
        } else if (strcmp(option, "cpy") == 0) {
            printf("������Դ�ļ�/Ŀ¼����: ");
            scanf("%s", name);
            printf("������Ŀ���ļ�/Ŀ¼����: ");
            scanf("%s", name);  // ע����������룬Ӧ���� dest_name
            copy_directory(name, name);
        } else if (strcmp(option, "cd") == 0) {
            printf("������Ҫ�л�����Ŀ¼·��������ڵ�ǰ·����: ");
            scanf("%s", name);
            change_dir(name);
        } else if (strcmp(option, "pwd") == 0) {
            display_current_path();
        } else if (strcmp(option, "exit") == 0) {
            printf("�����˳�...\n");
        } else {
            printf("��Чѡ�����������롣\n");
        }
    } while (strcmp(option, "exit") != 0);

    display_current_path();  // �����ʾ��ǰ·��
    return 0;
}

void initialize() {
    // ��ʼ���ļ�ϵͳ�������Ϊ����ļ�ϵͳ��Ϣ
    file_count = 0;
    GetCurrentDirectory(MAX_PATH_LEN, current_path);  // ��ȡ��ǰ����Ŀ¼
}

void create_file(char *name, int is_directory) {
    // �����ļ���Ŀ¼�ĺ���ʵ��
    char full_path[MAX_PATH_LEN];
    sprintf(full_path, "%s\\%s", current_path, name);

    if (is_directory) {
        if (!CreateDirectory(full_path, NULL)) {
            printf("����Ŀ¼ʧ�ܡ�\n");
            return;
        }
    } else {
        HANDLE hFile = CreateFile(full_path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            printf("�����ļ�ʧ�ܡ�\n");
            return;
        }
        CloseHandle(hFile);
    }

    printf("�ļ�/Ŀ¼�����ɹ���\n");
}

void delete_file(char *name) {
    // ɾ���ļ���Ŀ¼�ĺ���ʵ��
    char full_path[MAX_PATH_LEN];
    sprintf(full_path, "%s\\%s", current_path, name);

    if (RemoveDirectory(full_path) || DeleteFile(full_path)) {
        printf("�ļ�/Ŀ¼ɾ���ɹ���\n");
    } else {
        printf("ɾ��ʧ�ܻ��ļ�/Ŀ¼�����ڡ�\n");
    }
}

FCB* find_node(char *name) {
    // ���ļ�ϵͳ�в����ض����ƵĽڵ㣨�ļ���Ŀ¼��
    char full_path[MAX_PATH_LEN];
    sprintf(full_path, "%s\\%s", current_path, name);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(full_path, &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
        return &filesystem[0];  // ����һ������� FCB ָ�룬��Ϊʾ��
    }
    return NULL;
}

FCB* find_file(char *name) {
    // ���ļ�ϵͳ�в����ض����Ƶ��ļ����������·��
    char search_path[MAX_PATH_LEN];
    sprintf(search_path, "%s\\*", current_path);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("�޷������ļ���\n");
        return NULL;
    }

    static FCB found_file;  // ��̬�����洢�ҵ����ļ���Ϣ
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            strcmp(findData.cFileName, name) == 0) {
            // �ҵ��ļ������·��
            strcpy(found_file.name, findData.cFileName);
            sprintf(found_file.path, "%s\\%s", current_path, findData.cFileName);
            found_file.is_directory = 0;  // ����Ŀ¼
            FindClose(hFind);
            return &found_file;
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
    return NULL;
}

void move_file_or_directory(char *source_name, char *dest_name) {
    // �ƶ��ļ���Ŀ¼�ĺ���ʵ��
    char source_path[MAX_PATH_LEN], dest_path[MAX_PATH_LEN];
    sprintf(source_path, "%s\\%s", current_path, source_name);
    sprintf(dest_path, "%s\\%s\\%s", current_path, dest_name, source_name);  // Ŀ��·������Դ�ļ���

    if (MoveFile(source_path, dest_path)) {
        printf("�ļ�/Ŀ¼�ƶ��ɹ���\n");
    } else {
        printf("�ƶ�ʧ�ܻ��ļ�/Ŀ¼�����ڡ�\n");
    }
}

void list_directory_contents() {
    // �г�Ŀ¼���ݵĺ���ʵ��
    char search_path[MAX_PATH_LEN];
    sprintf(search_path, "%s\\*", current_path);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("�޷��г�Ŀ¼���ݡ�\n");
        return;
    }

    printf("Ŀ¼ '%s' ������:\n", current_path);
    do {
        printf("%s\n", findData.cFileName);
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}


   

void copy_directory(char *source_name, char *dest_name) {
    // ����Ŀ¼�ĺ���ʵ��
    char source_path[MAX_PATH_LEN], dest_path[MAX_PATH_LEN];
    sprintf(source_path, "%s\\%s", current_path, source_name);
    sprintf(dest_path, "%s\\%s", current_path, dest_name);

    if (!CreateDirectory(dest_path, NULL)) {
        printf("����Ŀ��Ŀ¼ʧ�ܡ�\n");
        return;
    }

    char search_path[MAX_PATH_LEN];
    sprintf(search_path, "%s\\*", source_path);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("�޷�����Ŀ¼���ݡ�\n");
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
            char source_file[MAX_PATH_LEN], dest_file[MAX_PATH_LEN];
            sprintf(source_file, "%s\\%s", source_path, findData.cFileName);
            sprintf(dest_file, "%s\\%s", dest_path, findData.cFileName);

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                copy_directory(source_file, dest_file);
            } else {
                CopyFile(source_file, dest_file, FALSE);
            }
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
    printf("Ŀ¼���Ƴɹ���\n");
}

void change_dir(char *path) {
    // �ı䵱ǰ����Ŀ¼�ĺ���ʵ��
    char new_path[MAX_PATH_LEN];
    sprintf(new_path, "%s\\%s", current_path, path);

    if (SetCurrentDirectory(new_path)) {
        GetCurrentDirectory(MAX_PATH_LEN, current_path);  // ���µ�ǰ·��
        printf("��ǰĿ¼�л��� '%s'��\n", current_path);
    } else {
        printf("�л�Ŀ¼ʧ�ܻ�Ŀ¼�����ڡ�\n");
    }
}

void go_back() {
    // ������һ��Ŀ¼�ĺ���ʵ��
    if (!SetCurrentDirectory("..")) {
        printf("�����ϼ�Ŀ¼ʧ�ܡ�\n");
        return;
    }
    GetCurrentDirectory(MAX_PATH_LEN, current_path);  // ���µ�ǰ·��
    printf("��ǰĿ¼�л��� '%s'��\n", current_path);
}

void display_current_path() {
    // ��ʾ��ǰ����Ŀ¼·���ĺ���ʵ��
    GetCurrentDirectory(MAX_PATH_LEN, current_path);
    printf("��ǰ·��: %s\n", current_path);
}

