#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// 定义状态
const string Status[3] = {"Invalid", "Modified", "Shared"};

// 定义主存块 
struct Block {
	string str; 
	string state;
};

// 定义缓存块
struct cacheBlock {
	string state;
	int tag;
	Block data;
};

// 定义缓存，每个缓存包含四个缓存块
struct Cache {
	cacheBlock cacheblock[4];
};

// 定义主存和缓存
Block block[32];
Cache cache[4];

// 初始化
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

// 显示主存块内容和状态
void show_block() {
	for (int i = 0; i < 32; ++i) {
		cout << "memory block " << i << ": ";
		cout << "data = " << block[i].str;
		cout << ", status = " << block[i].state << endl;
	}
}

// 显示缓存内容
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

// 回写函数，将缓存块数据写回主存
void write_back(int i, int j) {
	int tag = cache[i].cacheblock[j].tag;
	block[tag] = cache[i].cacheblock[j].data;
	cache[i].cacheblock[j].state = "Shared";
	block[tag].state = "Shared"; 
}

// 查找cache中的标签块
int search(int icpu, int tag) {
	for (int i = 0; i < 4; ++i) {
		if (cache[icpu].cacheblock[i].tag == tag) {
			return i;
		}
	}
	return -1;
}

// 无效化其他缓存中相同标签的块
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

// 写入操作函数
void cpuwrite(int icpu, int tag, const char str[]) {
	int block_index = search(icpu, tag);
	
	if (block_index != -1) {  // 当前缓存中存在相同标签的块
		invalidate_others(tag, icpu);  // 无效化其他缓存中的相同标签块
		cache[icpu].cacheblock[block_index].state = "Modified";  
		cache[icpu].cacheblock[block_index].data.str = str;  
	} else {  // 当前缓存中不存在相同标签的块
		bool replaced = false;
		
		for (int i = 0; i < 4; ++i) {
			if (cache[icpu].cacheblock[i].state == "Invalid") {  // 找到一个无效的缓存块
				cache[icpu].cacheblock[i].state = "Modified";  
				cache[icpu].cacheblock[i].tag = tag;  
				cache[icpu].cacheblock[i].data.str = str;  
				invalidate_others(tag, icpu); 
				replaced = true;
				break;
			}
		}
		
		if (!replaced) {
			// 如果所有缓存块都是有效的，优先替换shared块
			for (int i = 0; i < 4; ++i) {
				if (cache[icpu].cacheblock[i].state == "Shared") {  // 找到一个共享的缓存块
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
			// 如果没有共享块，选择一个修改的缓存块进行替换
			for (int i = 0; i < 4; ++i) {
				if (cache[icpu].cacheblock[i].state == "Modified") {  // 找到一个修改的缓存块
					write_back(icpu, i);  // 先将修改的缓存块写回主存
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

    // 在本cache块中找到且不为Invalid
    if (block_index != -1 && cache[icpu].cacheblock[block_index].state != "Invalid") {
        str = cache[icpu].cacheblock[block_index].data.str;
        return;
    }

    // 在本cache块中找到且为Invalid
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

    // 在本cache块中未找到，但在其他cache中找到且不是Invalid
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

            // 优先选择Shared状态的缓存块进行替换
            for (int j = 0; j < 4; ++j) {
                if (cache[icpu].cacheblock[j].state == "Shared") {
                    cache[icpu].cacheblock[j].state = "Shared";
                    cache[icpu].cacheblock[j].tag = tag;
                    cache[icpu].cacheblock[j].data = cache[i].cacheblock[other_block_index].data;
                    str = cache[icpu].cacheblock[j].data.str;
                    return;
                }
            }

            // 如果没有Shared状态的块，则随机替换一个缓存块
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

    // 如果在其他cache中也未找到，则从主存读取
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

    // 如果所有缓存块都是有效的，优先替换Shared状态的块
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

    // 如果没有Shared状态的块，则随机替换一个缓存块
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
		cout << "1. 读取\n2. 写入\n3. 显示主存\n4. 显示缓存\n5. 退出\n请输入选项: ";
		
		// 检查输入合法性
		if (!(cin >> choice)) {
			// 清除错误状态并忽略当前行的剩余输入
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid! 请重新输入。\n";
			continue;
		}
		
		switch (choice) {
		case 1:
			cout << "请输入CPU编号 (0-3): ";
			if (!(cin >> icpu) || icpu < 0 || icpu > 3) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid CPU编号! 请重新输入。\n";
				break;
			}
			cout << "请输入标签 (0-31): ";
			if (!(cin >> tag) || tag < 0 || tag > 31) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid 标签! 请重新输入。\n";
				break;
			}
			cout<<"ipcu:"<<icpu<<endl; 
			cpuread(icpu, tag, read_str);
			cout << "读取的数据: " << read_str << endl;
			break;
		case 2:
			cout << "请输入CPU编号 (0-3): ";
			if (!(cin >> icpu) || icpu < 0 || icpu > 3) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid CPU编号! 请重新输入。\n";
				break;
			}
			cout << "请输入标签 (0-31): ";
			if (!(cin >> tag) || tag < 0 || tag > 31) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid 标签! 请重新输入。\n";
				break;
			}
			cout << "请输入写入的字符串: ";
			if (!(cin >> str)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid! 请重新输入。\n";
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
			cout << "Invalid! 请重试。\n";
			break;
		}
		
		// 清除输入流的错误状态和剩余的输入内容
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return 0;
}

