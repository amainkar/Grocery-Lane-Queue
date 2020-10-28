#include <stdio.h>
#include <stdlib.h>

struct Grocery_item
{
	char grocery_product[40];
	float grocery_cost;
	char grocery_amount[5];
	struct Grocery_item *next;
};
struct Customer
{
	char name[40];
	float balance;
	struct Customer *next_cust;
	struct Grocery_item *list;
} *head = NULL, *tail;

void addCustomer(struct Customer *current)
{
	if (head == NULL)
	{
		head = current;
		tail = head;
		head->next_cust = NULL;
	}
	else
	{
		tail->next_cust = current;
		tail = tail->next_cust;
		tail->next_cust = NULL;
	}
}

int callCustomer(FILE *fp)
{

	struct Customer *front;
	if (head == NULL)
	{
		//printf("\nSorry, queue is empty\n\n");
		return 0;
	}

	else
	{
		//Gets the Customer at the front of the line
		front = head;
		head = head->next_cust;
		front->next_cust = NULL;

		//Get the total_items and total_cost from the items
		struct Grocery_item *begin = front->list;
		int total_items = 0;
		float total_cost = 0;
		while (begin != NULL)
		{
			total_items += atoi(begin->grocery_amount);
			total_cost += (begin->grocery_cost) * atof(begin->grocery_amount);
			begin = begin->next;
		}

		//Finally, create the log for the current customer
		//First determine which line the customer goes into
		char lane[8] = "normal";
		if (total_items < 10)
		{
			lane[0] = 'e';
			lane[1] = 'x';
			lane[2] = 'p';
			lane[3] = 'r';
			lane[4] = 'e';
			lane[5] = 's';
			lane[6] = 's';
			lane[7] = '\0';
		}

		//Next determine if the customer got money
		if (total_cost > front->balance)
		{
			fprintf(fp, "%s was rejected at the %s register\n", front->name, lane);
		}
		else
		{
			struct Grocery_item *bruh = front->list;
			struct Grocery_item *temp = front->list;
			char string[100];
			int index = 0;
			//Create the part of the log that specifies the groceries bought and the amount
			//Loop through all the groceries and keep adding to a character array
			while (bruh != NULL)
			{
				for (int i = 0; i < sizeof(bruh->grocery_amount) / sizeof(char); i++)
				{
					if (bruh->grocery_amount[i] == '\0')
					{
						break;
					}
					string[index] = bruh->grocery_amount[i];
					index++;
				}
				string[index] = ' ';
				index++;
				for (int sis = 0; sis < (sizeof(bruh->grocery_product) / sizeof(char)) - 1; sis++)
				{
					if (bruh->grocery_product[sis] == '\0')
					{
						break;
					}
					string[index] = bruh->grocery_product[sis];
					index++;
				}
				if (bruh->next != NULL)
				{
					string[index] = ',';
					index++;
					string[index] = ' ';
					index++;
				}

				bruh = bruh->next;
				free(temp);
				temp=bruh;
			}
			string[index++] = '\0';

			//Now enter in the generate string into the printf
			fprintf(fp, "%s paid $%.2f for %s at the %s register\n", front->name, total_cost, string, lane);
			//printf("%s paid $%.2f for %s at the %s register\n", front->name, total_cost, string, lane);
			free(front);
		}
		return 1;
	}
}

void getCustomer(char name[])
{
	char tempvar[100], tempname[100], tempamount[100], tempGroceriesName[10][50], tempGroceriesAmount[10][50], tempGroceriesPrice[10][50];
	int x = 0, y = 0, z = 0, a = 0, b = 0, grosCounter = 0, arrayLineAmt = 0, lineIndex[15];

	//printf("%s\n%s\n%s\n",name[0],name[1],name[2]);

	while (name[y + 1] != '\0')
	{
		if (name[y] != '{' && name[y] != '}' && name[y] != '[' && name[y] != ']' && name[y] != '\"' && name[y] != ' ')
		{ //printf("%c",name[b][y]);
			tempvar[z] = name[y];
			z++;
		}
		y++;
	}
	tempvar[z] = ',', z++;
	tempvar[z] = '\0';

	z = 0, y = 0;
	while (tempvar[z] != '\0')
	{
		if (a == 0 && tempvar[z] == ',')
		{
			tempname[y] = '\0';
			y++;
			//printf("%c",tempname[b][y]);
		}
		if (a == 1 && tempvar[z] == ',')
		{
			tempamount[y] = '\0';
			y++;
			//printf("%c",tempamount[b][y]);
		}
		if (tempvar[z] == ',')
		{
			a++, y = 0;
		}
		if (a == 0 && tempvar[z] != ',')
		{
			tempname[y] = tempvar[z];
			y++;
			//printf("%c",tempname[b][y]);
		}
		if (a == 1 && tempvar[z] != ',')
		{
			tempamount[y] = tempvar[z];
			y++;
			//printf("%c",tempamount[b][y]);
		}
		if (a == 2)
		{
			break;
		}
		z++;
	}

	y = 0, a = 0, z++;

	//printf("%c",tempvar[z]);
	while (tempvar[z] != '\0')
	{
		if (a % 3 == 0 && tempvar[z] != ',')
		{
			tempGroceriesName[grosCounter][y] = tempvar[z];
			//printf("%c",tempGroceriesName[grosCounter][y]);
			y++;
			//printf("%c",tempvar[z]);
		}
		if (a % 3 == 1 && tempvar[z] != ',')
		{
			tempGroceriesPrice[grosCounter][y] = tempvar[z];
			y++;
		}
		if (a % 3 == 2 && tempvar[z] != ',')
		{
			tempGroceriesAmount[grosCounter][y] = tempvar[z];
			//printf("%c",tempGroceriesAmount[grosCounter][y]);
			y++;
		}
		if (a % 3 == 0 && tempvar[z] == ',')
		{
			tempGroceriesName[grosCounter][y] = '\0';
		}
		if (a % 3 == 1 && tempvar[z] == ',')
		{
			tempGroceriesPrice[grosCounter][y] = '\0';
		}
		if (a % 3 == 2 && tempvar[z] == ',')
		{
			tempGroceriesAmount[grosCounter][y] = '\0';
			grosCounter++;
		}
		if (tempvar[z] == ',')
		{
			a++, y = 0;
		}
		z++;
		//printf("%s",tempGroceriesAmount[grosCounter]);
	}

	struct Customer *current = (struct Customer *)malloc(sizeof(struct Customer));

	struct Grocery_item *start = NULL;
	struct Grocery_item *fin;

	int index = 0;
	while (index < grosCounter)
	{
		if (start == NULL)
		{
			start = (struct Grocery_item *)malloc(sizeof(struct Grocery_item));
			start->next = NULL;
			fin = start;
		}
		else
		{
			fin->next = (struct Grocery_item *)malloc(sizeof(struct Grocery_item));
			fin = fin->next;
			fin->next = NULL;
		}

		//Enter in the grocery's name
		for (int i = 0; i < sizeof(tempGroceriesName[index]) / sizeof(char); i++)
		{
			fin->grocery_product[i] = tempGroceriesName[index][i];
			if (tempGroceriesName[index][i] == '\0')
			{
				break;
			}
		}

		//Enter in the Grocery's price
		fin->grocery_cost = atof(tempGroceriesPrice[index]);

		//Enter in the Grocery amount
		for (int i = 0; i < sizeof(tempGroceriesAmount[index]) / sizeof(char); i++)
		{
			fin->grocery_amount[i] = tempGroceriesAmount[index][i];
			if (tempGroceriesAmount[index][i] == '\0')
			{
				break;
			}
		}

		index++;
	}

	current->list = start;
	current->balance = atof(tempamount);
	for (int i = 0; i < sizeof(tempname) / sizeof(char); i++)
	{
		current->name[i] = tempname[i];
		if (tempname[i] == '\0')
		{
			break;
		}
	}

	addCustomer(current);
}

int main()
{
	FILE *fp;
	char line[100];
	fp = fopen("input.txt", "r");
	while (!feof(fp))
	{
		fgets(line, 100, fp);
		getCustomer(line);
	}
	FILE *sp;
	sp = fopen("output.txt", "w+");
	while (callCustomer(sp))
	{
		continue;
	}
	fclose(sp);
}
