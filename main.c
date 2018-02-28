#include "sxmlc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display_recursive_children_content(XMLNode* source, int children_count, char* names) {

	for (int i = 0; i < children_count; i++) {
		XMLNode *child = source->children[i];

		int new_children = child->n_children;

		if (new_children > 0) {
			char s[100];
			if (child->n_attributes == 0)
			{
				strcat(names, " ");
				strcat(names, child->tag);
			}
			else
				for (int j = 0; j < child->n_attributes; j++)
				{
					strcpy(s, names);
					strcat(s, " ");
					strcat(s, child->attributes[j].name);
					strcat(s, ": ");
					strcat(s, child->attributes[j].value);
				}

			display_recursive_children_content(child, new_children, s);
		}
		else {
			printf("\n%s", names);
			printf(" %s", child->tag);
			printf(": %s", child->text);
		}
	}
}


int main()
{
	XMLDoc doc;
	XMLDoc_init(&doc);
	XMLDoc_parse_file_DOM("./catalog.xml", &doc);
	XMLNode *root;
	root = doc.nodes[doc.i_root];

	char* root_name = (char*)malloc(strlen(root->tag));
	strcpy(root_name, root->tag);
	root_name[0] -= 'a' - 'A';
	//	for (int i = 0; i < root->n_children; i++)
	//	printf("%s\n", root->children[i]->father->tag);

	display_recursive_children_content(root, root->n_children, root_name);
	free(root_name);
	int a;
	return 0;
}