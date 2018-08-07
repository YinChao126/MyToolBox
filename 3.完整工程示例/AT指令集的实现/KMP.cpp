#include "KMP.h"

#ifdef Cplusplus
int KmpFind(const string& target, const string& pattern)
{
	const int target_length = target.size();
	const int pattern_length = pattern.size();
	int * overlay_value = new int[pattern_length];
	overlay_value[0] = -1;
	int index = 0;
	for (int i = 1; i<pattern_length; ++i)
	{
		index = overlay_value[i - 1];
		while (index >= 0 && pattern[index + 1] != pattern[i])
		{
			index = overlay_value[index];
		}
		if (pattern[index + 1] == pattern[i])
		{
			overlay_value[i] = index + 1;
		}
		else
		{
			overlay_value[i] = -1;
		}
	}
	//match algorithm start
	int pattern_index = 0;
	int target_index = 0;
	while (pattern_index<pattern_length&&target_index<target_length)
	{
		if (target[target_index] == pattern[pattern_index])
		{
			++target_index;
			++pattern_index;
		}
		else if (pattern_index == 0)
		{
			++target_index;
		}
		else
		{
			pattern_index = overlay_value[pattern_index - 1] + 1;
		}
	}
	if (pattern_index == pattern_length)
	{
		return target_index - pattern_index;
	}
	else
	{
		return -1;
	}
	delete[] overlay_value;
}

#else
int KmpFind(const char *target, const char *pattern)
{
	const int target_length = strlen(target);
	const int pattern_length = strlen(pattern);
	int * overlay_value = (int *)malloc(pattern_length * sizeof(int));
	if (overlay_value == NULL)
	{
		return -1;
	}
	overlay_value[0] = -1;
	int index = 0;
	for (int i = 1; i<pattern_length; ++i)
	{
		index = overlay_value[i - 1];
		while (index >= 0 && pattern[index + 1] != pattern[i])
		{
			index = overlay_value[index];
		}
		if (pattern[index + 1] == pattern[i])
		{
			overlay_value[i] = index + 1;
		}
		else
		{
			overlay_value[i] = -1;
		}
	}
	//match algorithm start
	int pattern_index = 0;
	int target_index = 0;
	while (pattern_index<pattern_length&&target_index<target_length)
	{
		if (target[target_index] == pattern[pattern_index])
		{
			++target_index;
			++pattern_index;
		}
		else if (pattern_index == 0)
		{
			++target_index;
		}
		else
		{
			pattern_index = overlay_value[pattern_index - 1] + 1;
		}
	}
	if (pattern_index == pattern_length)
	{
		return target_index - pattern_index;
	}
	else
	{
		return -1;
	}
	free(overlay_value);
}
#endif


