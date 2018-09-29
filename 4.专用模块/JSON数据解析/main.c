#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main()
{
	FILE *f;
	int len;
	char *data;
	f = fopen("test.txt", "rb");
	if(f == NULL)
	{
		printf("cannot open this files\n");
		return -1;
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	data = (char *)malloc(len+1);
	int ret = fread(data, 1, len, f);
	if(ret != len)
	{
		printf("read error\n");
		return -1;
	}
	cJSON *json;//解析元素
    json=cJSON_Parse(data);
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
	cJSON *mode = cJSON_GetObjectItem(json, "mode");
	printf("name = %s\n", mode->valuestring);
	
	cJSON *sub_json;//解析数组
	sub_json = cJSON_GetObjectItem(json,"service");
	int serv_len = cJSON_GetArraySize(sub_json);
	cJSON* arr_item = sub_json->child;
	cJSON *id;
	for (int i = 0; i < serv_len; i++)
	{
		id = cJSON_GetObjectItem(arr_item, "ServiceId");
		printf("ServiceId = %s\t", id->valuestring);
		id = cJSON_GetObjectItem(arr_item, "FormCode");
		printf("FormCode = %s\t", id->valuestring);
		id = cJSON_GetObjectItem(arr_item, "LdpcNum");
		printf("LdpcNum = %s\t", id->valuestring);
		id = cJSON_GetObjectItem(arr_item, "LdpcRate");
		printf("LdpcRate = %s\t", id->valuestring);
		id = cJSON_GetObjectItem(arr_item, "IntvSize");
		printf("IntvSize = %s\t", id->valuestring);
		id = cJSON_GetObjectItem(arr_item, "QamType");
		printf("QamType = %s\n", id->valuestring);
		arr_item = arr_item->next;
	}

	cJSON *test; //解析json嵌套对象
	test = cJSON_GetObjectItem(json, "test");
	cJSON *sub_test;
	sub_test = cJSON_GetObjectItem(test, "para1");
	printf("para1 = %s\n", sub_test->valuestring);
	sub_test = cJSON_GetObjectItem(test, "para2");
	printf("para2 = %s\n", sub_test->valuestring);

	free(data);
	printf("len = %d\n", len);
	cJSON_Delete(json); 
	return 0;
}
