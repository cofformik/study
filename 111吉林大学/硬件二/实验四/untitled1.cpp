#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// ����״̬
const string Status[3] = {"Invalid", "Modified", "Shared"};

// ��������� 
struct Block {
	string str; 
	string state;
};

// ���建���
struct cacheBlock {
	string state;
	int tag;
	Block data;
};

// ���建�棬ÿ����������ĸ������
struct Cache {
	cacheBlock cacheblock[4];
};

// ��������ͻ���
Block block[32];
Cache cache[4];

// ��ʼ��
void initial() {
	srand(time(0)); 
	for (int i = 0; i < 32; ++i) {
		block[i].str = ""; 
		for (int j = 0; j < 10; ++j) { 
			if (rand() % 2 == 0) {
				block[i].str += 'A' + rand() % 26; 
			} else {
				block[i].str += 'a' + rand() % 26; 
			}
		}
		block[i].state = "Invalid";
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cache[i].cacheblock[j].state = "Invalid"; 
			cache[i].cacheblock[j].tag = -1; 
		}
	}
}

// ��ʾ��������ݺ�״̬
void show_block() {
	for (int i = 0; i < 32; ++i) {
		cout << "memory block " << i << ": ";
		cout << "data = " << block[i].str;
		cout << ", status = " << block[i].state << endl;
	}
}

// ��ʾ��������
void show_cache() {
	for (int i = 0; i < 4; ++i) {
		cout << "Cache " << i << ":\n\n";
		for (int j = 0; j < 4; ++j) {
			cout << "  block " << j << ": "
			<< "status = " << cache[i].cacheblock[j].state
			<< ", tag = " << cache[i].cacheblock[j].tag
			<< ", data = " << cache[i].cacheblock[j].data.str;
			cout << endl;
		}
	}
}

// ��д�����������������д������
void write_back(int i, int j) {
	int tag = cache[i].cacheblock[j].tag;
	block[tag] = cache[i].cacheblock[j].data;
	cache[i].cacheblock[j].state = "Shared";
	block[tag].state = "Shared"; 
}

// ����cache�еı�ǩ��
int search(int icpu, int tag) {
	for (int i = 0; i < 4; ++i) {
		if (cache[icpu].cacheblock[i].tag == tag) {
			return i;
		}
	}
	return -1;
}

// ��Ч��������������ͬ��ǩ�Ŀ�
void invalidate_others(int tag, int icpu) {
	for (int i = 0; i < 4; ++i) {
		if (i == icpu) continue;
		for (int j = 0; j < 4; ++j) {
			if (cache[i].cacheblock[j].tag == tag) {
				cache[i].cacheblock[j].state = "Invalid";
			}
		}
	}
}

// д���������
void cpuwrite(int icpu, int tag, const char str[]) {
	int block_index = search(icpu, tag);
	
	if (block_index != -1) {  // ��ǰ�����д�����ͬ��ǩ�Ŀ�
		invalidate_others(tag, icpu);  // ��Ч�����������е���ͬ��ǩ��
		cache[icpu].cacheblock[block_index].state = "Modified";  
		cache[icpu].cacheblock[block_index].data.str = str;  
	} else {  // ��ǰ�����в�������ͬ��ǩ�Ŀ�
		bool replaced = false;
		
		for (int i = 0; i < 4; ++i) {
			if (cache[icpu].cacheblock[i].state == "Invalid") {  // �ҵ�һ����Ч�Ļ����
				cache[icpu].cacheblock[i].state = "Modified";  
				cache[icpu].cacheblock[i].tag = tag;  
				cache[icpu].cacheblock[i].data.str = str;  
				invalidate_others(tag, icpu); 
				replaced = true;
				break;
			}
		}
		
		if (!replaced) {
			// ������л���鶼����Ч�ģ������滻shared��
			for (int i = 0; i < 4; ++i) {
				if (cache[icpu].cacheblock[i].state == "Shared") {  // �ҵ�һ������Ļ����
					cache[icpu].cacheblock[i].state = "Modified";  
					cache[icpu].cacheblock[i].tag = tag;  
					cache[icpu].cacheblock[i].data.str = str;  
					invalidate_others(tag, icpu);  
					replaced = true;
					break;
				}
			}
		}
		
		if (!replaced) {
			// ���û�й���飬ѡ��һ���޸ĵĻ��������滻
			for (int i = 0; i < 4; ++i) {
				if (cache[icpu].cacheblock[i].state == "Modified") {  // �ҵ�һ���޸ĵĻ����
					write_back(icpu, i);  // �Ƚ��޸ĵĻ����д������
					cache[icpu].cacheblock[i].state = "Modified";  
					cache[icpu].cacheblock[i].tag = tag;  
					cache[icpu].cacheblock[i].data.str = str;  
					invalidate_others(tag, icpu);  
					break;
				}
			}
		}
	}
}

void cpuread(int icpu, int tag, string& str) {
    int block_index = search(icpu, tag);

    // �ڱ�cache�����ҵ��Ҳ�ΪInvalid
    if (block_index != -1 && cache[icpu].cacheblock[block_index].state != "Invalid") {
        str = cache[icpu].cacheblock[block_index].data.str;
        return;
    }

    // �ڱ�cache�����ҵ���ΪInvalid
    if (block_index != -1 && cache[icpu].cacheblock[block_index].state == "Invalid") {
        for (int i = 0; i < 4; ++i) {
            if (i == icpu) continue;
            int other_block_index = search(i, tag);
            if (other_block_index != -1 && cache[i].cacheblock[other_block_index].state != "Invalid") {
                if (cache[i].cacheblock[other_block_index].state == "Modified") {
                    write_back(i, other_block_index);
                }
                cache[icpu].cacheblock[block_index].state = "Shared";
                cache[icpu].cacheblock[block_index].tag = tag;
                cache[icpu].cacheblock[block_index].data = cache[i].cacheblock[other_block_index].data;
                str = cache[icpu].cacheblock[block_index].data.str;
                return;
            }
        }
        cache[icpu].cacheblock[block_index].state = "Shared";
        cache[icpu].cacheblock[block_index].tag = tag;
        cache[icpu].cacheblock[block_index].data = block[tag];
        str = cache[icpu].cacheblock[block_index].data.str;
        block[tag].state = "Shared";
        return;
    }

    // �ڱ�cache����δ�ҵ�����������cache���ҵ��Ҳ���Invalid
    for (int i = 0; i < 4; ++i) {
        if (i == icpu) continue;
        int other_block_index = search(i, tag);
        if (other_block_index != -1 && cache[i].cacheblock[other_block_index].state != "Invalid") {
            if (cache[i].cacheblock[other_block_index].state == "Modified") {
                write_back(i, other_block_index);
            }

            for (int j = 0; j < 4; ++j) {
                if (cache[icpu].cacheblock[j].state == "Invalid") {
                    cache[icpu].cacheblock[j].state = "Shared";
                    cache[icpu].cacheblock[j].tag = tag;
                    cache[icpu].cacheblock[j].data = cache[i].cacheblock[other_block_index].data;
                    str = cache[icpu].cacheblock[j].data.str;
                    return;
                }
            }

            // ����ѡ��Shared״̬�Ļ��������滻
            for (int j = 0; j < 4; ++j) {
                if (cache[icpu].cacheblock[j].state == "Shared") {
                    cache[icpu].cacheblock[j].state = "Shared";
                    cache[icpu].cacheblock[j].tag = tag;
                    cache[icpu].cacheblock[j].data = cache[i].cacheblock[other_block_index].data;
                    str = cache[icpu].cacheblock[j].data.str;
                    return;
                }
            }

            // ���û��Shared״̬�Ŀ飬������滻һ�������
            int replace_index = rand() % 4;
            if (cache[icpu].cacheblock[replace_index].state == "Modified") {
                write_back(icpu, replace_index);
            }
            cache[icpu].cacheblock[replace_index].state = "Shared";
            cache[icpu].cacheblock[replace_index].tag = tag;
            cache[icpu].cacheblock[replace_index].data = cache[i].cacheblock[other_block_index].data;
            str = cache[icpu].cacheblock[replace_index].data.str;
            return;
        }
    }

    // ���������cache��Ҳδ�ҵ�����������ȡ
    for (int i = 0; i < 4; ++i) {
        if (cache[icpu].cacheblock[i].state == "Invalid") {
            cache[icpu].cacheblock[i].state = "Shared";
            cache[icpu].cacheblock[i].tag = tag;
            cache[icpu].cacheblock[i].data = block[tag];
            str = cache[icpu].cacheblock[i].data.str;
            block[tag].state = "Shared";
            return;
        }
    }

    // ������л���鶼����Ч�ģ������滻Shared״̬�Ŀ�
    for (int i = 0; i < 4; ++i) {
        if (cache[icpu].cacheblock[i].state == "Shared") {
            cache[icpu].cacheblock[i].state = "Shared";
            cache[icpu].cacheblock[i].tag = tag;
            cache[icpu].cacheblock[i].data = block[tag];
            str = cache[icpu].cacheblock[i].data.str;
            block[tag].state = "Shared";
            return;
        }
    }

    // ���û��Shared״̬�Ŀ飬������滻һ�������
    int replace_index = rand() % 4;
    if (cache[icpu].cacheblock[replace_index].state == "Modified") {
        write_back(icpu, replace_index);
    }
    cache[icpu].cacheblock[replace_index].state = "Shared";
    cache[icpu].cacheblock[replace_index].tag = tag;
    cache[icpu].cacheblock[replace_index].data = block[tag];
    str = cache[icpu].cacheblock[replace_index].data.str;
    block[tag].state = "Shared";
}



int main() {
	initial();
	int choice, icpu, tag;
	char str[16];
	string read_str;
	
	while (true) {
		cout << "1. ��ȡ\n2. д��\n3. ��ʾ����\n4. ��ʾ����\n5. �˳�\n������ѡ��: ";
		
		// �������Ϸ���
		if (!(cin >> choice)) {
			// �������״̬�����Ե�ǰ�е�ʣ������
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid! ���������롣\n";
			continue;
		}
		
		switch (choice) {
		case 1:
			cout << "������CPU��� (0-3): ";
			if (!(cin >> icpu) || icpu < 0 || icpu > 3) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid CPU���! ���������롣\n";
				break;
			}
			cout << "�������ǩ (0-31): ";
			if (!(cin >> tag) || tag < 0 || tag > 31) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid ��ǩ! ���������롣\n";
				break;
			}
			cout<<"ipcu:"<<icpu<<endl; 
			cpuread(icpu, tag, read_str);
			cout << "��ȡ������: " << read_str << endl;
			break;
		case 2:
			cout << "������CPU��� (0-3): ";
			if (!(cin >> icpu) || icpu < 0 || icpu > 3) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid CPU���! ���������롣\n";
				break;
			}
			cout << "�������ǩ (0-31): ";
			if (!(cin >> tag) || tag < 0 || tag > 31) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid ��ǩ! ���������롣\n";
				break;
			}
			cout << "������д����ַ���: ";
			if (!(cin >> str)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid! ���������롣\n";
				break;
			}
			cpuwrite(icpu, tag, str);
			break;
		case 3:
			show_block();
			break;
		case 4:
			show_cache();
			break;
		case 5:
			exit(0);
		default:
			cout << "Invalid! �����ԡ�\n";
			break;
		}
		
		// ����������Ĵ���״̬��ʣ�����������
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return 0;
}

