#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int len = strlen(s);
    if (len == 0)
    	return 0;
    
    int charbucket[300] = {0};
    int startidx, i;
    int maxlen = 1, substrlen = 0;
    for (startidx = 0; startidx < len; startidx++) {
    	memset(charbucket, 0, sizeof(charbucket));
    	for (i = startidx; i < len; i++) {
    		if (charbucket[s[i]] == 0) {
    			charbucket[s[i]] = 1;
    		} else {
    			break;
    		}
    	}
    	substrlen = 0;
    	for (i = 0; i < 300; i++) {
    		if (charbucket[i] == 1)
    			substrlen++;
    	}
    	if (substrlen > maxlen)
    		maxlen = substrlen;
    }
    return maxlen;
}

int main(int argc, char const *argv[])
{
	char s[1000] = {0};
	for ( ; ; ) {
		scanf("%s", s);
		printf("result = %d\n", lengthOfLongestSubstring(s));
	}
	return 0;
}