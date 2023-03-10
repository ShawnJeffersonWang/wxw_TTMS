#include "EntityKey_Persist.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

static const char ENTITY_KEY_FILE[] = "EntityKey.dat";

typedef struct
{
	char entyName[41];
	long key;
} entity_key_t;

long EntKey_Perst_GetNewKeys(const char entName[], int count)
{
	entity_key_t ent;
	FILE *fp;
	int found = 0;
	long newEntKey = 1;

	if (count < 1)
	{
		printf("Entity count must be bigger than 0!\n");
		return 0;
	}

	if (access(ENTITY_KEY_FILE, 0))
	{
		fp = fopen(ENTITY_KEY_FILE, "wb+");
		if (NULL == fp)
		{
			return 0;
		}
	}
	else
	{
		fp = fopen(ENTITY_KEY_FILE, "rb+");
		if (NULL == fp)
		{
			return 0;
		}
	}

	while (!feof(fp))
	{
		if (fread(&ent, sizeof(entity_key_t), 1, fp))
		{
			if (0 == strcmp(ent.entyName, entName))
			{
				fseek(fp, -((int)sizeof(entity_key_t)), SEEK_CUR);
				newEntKey = ent.key + 1;
				ent.key += count;
				fwrite(&ent, sizeof(entity_key_t), 1, fp);
				found = 1;
				break;
			}
		}
	}

	if (!found)
	{
		strcpy(ent.entyName, entName);
		newEntKey = 1;
		ent.key = count;
		fwrite(&ent, sizeof(entity_key_t), 1, fp);
	}

	fclose(fp);

	return newEntKey;
}
