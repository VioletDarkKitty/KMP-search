#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

/**
 * Performs a substring search using the KMP algorithm
 * Allocates an array which is the same size as the pattern
 * 
 * @param char* subject - The subject of the search
 * @param char* pattern - The pattern to search for
 * @param (optional) unsigned int begin - The position to begin searching at
 * 
 * @returns The first position of the pattern in the subject or -1 if not found
 * May return -2 if the internal array cannot be allocated
 */
int KMP_search(char* subject, char* pattern, unsigned int begin = 0) {
	unsigned int pattern_length = strlen(pattern);
	unsigned int* kmp_arr = (unsigned int*) calloc(pattern_length, sizeof(unsigned int));
	if (kmp_arr == NULL) {
		return -2;
	}
	
	kmp_arr[0] = 0;
	unsigned int i, j;
	for(i = 1, j = 0; i < pattern_length; i++) {
		if (pattern[j] == pattern[i]) {
			j++;
		} else {
			j = 0;
		}
		
		kmp_arr[i] = j;
	}
	
	for(i = 0; i < pattern_length; i++) {
		std::cout << pattern[i] << ":" << kmp_arr[i] << std::endl;
	}
	
	unsigned int subject_length = strlen(subject);
	for(i = begin; i < subject_length; i++) {
		unsigned int match_pos = i;
		if (subject[i] == pattern[0]) {
			i++;
			j = 1;
			while(subject[i] == pattern[j] && i < subject_length) {
				i++;
				j++;
			}
			
			if (j == pattern_length) {
				free(kmp_arr);
				return match_pos;
			}
			
			if (subject[i] != pattern[j]) {
                i += j - kmp_arr[j - 1] - 1; // j can never be 0
				if (i >= subject_length) {
					break;
				}
            }
		}
	}
	
	free(kmp_arr);
	return -1;
}

int naive_search(char* subject, char* pattern, unsigned int begin = 0) {
	unsigned int subject_len = strlen(subject);
	unsigned int pattern_len = strlen(pattern);
	
	unsigned int i, j;
	for(i = 0, j = 0; i < subject_len; i++) {
		if (subject[i] == pattern[j]) {
			unsigned int begin_pos = i;
			while (subject[i] == pattern[j]) {
                if (j == pattern_len - 1) {
					return begin_pos;
				}
				
				i++;
				j++;
			}
			
			if (pattern[i] != subject[j]) {
				j = 0;
			}
		}
	}
	
	return -1;
}

int main(int argc, char** argv) {
	char search[] = "ATCGTGCCCCGTCCCCGGGGGTTTTCCCAAAAAAAATTTCCCAAATTCCCCCCCTTTTTTTTCCCCATACTTCTCTCACTCTCTCACAGGGGGGGGGAAATTTCCCGGGAAATTTCCCTTTCCCAAATTTCCCGGGAAACCCTTTAAACCCGGGTTTCCCAAA";
    char pattern[] = "TCCCTTT";
	int match_pos = KMP_search(search, pattern);
	int match_pos2 = naive_search(search, pattern);
	
	printf("match_pos = %d\n%s\n%s\n", match_pos, search, pattern);
	printf("match_pos = %d\n%s\n%s\n", match_pos2, search, pattern);
	
	return 0;
}
