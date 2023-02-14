#include"AVL tree.h"
#include"B tree.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include "data read.h"


void write_to_file(fstream& file, vector<node> arr)
{
	file << "ID" << ',' << "Year" << "," << "\n";
	int count = 0;
	for (int i = 0; i < arr.size();i++) {
		file << arr[i].id << "," << arr[i].year << "," << arr[i].cause << "," << arr[i].cause << "," << arr[i].state << "," << arr[i].deaths << "," << arr[i].DR << "\n";
	}
}

int main() {

	fstream file1("C:\\Users\\maraf\\source\\repos\\Project\\Project\\FilesANS.csv");
	int count1 = size_of_file(file1);
	file1.close();

	fstream file2("C:\\Users\\maraf\\source\\repos\\Project\\Project\\FilesANS.csv");
	node* F1 = insert(file2, count1);
	count1--;
	file2.close();



	BTree* BT= NULL;
	AVL* AT = NULL;

	vector<node> Nodes;
	fstream file33("C:\\Users\\maraf\\source\\repos\\Project\\Project\\FilesANS.csv", 'w');


	int choice,choice2,choice3,choice4,choice5,choice6;
	string temp1, temp2, temp3, temp4, temp5, temp6;
	float float1, float2, float3, float4, float5, float6;
	cout << "Select the Type of Tree you would Like to use!\n\t1.B-Tree\n\t2-AVL Tree\n Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		int Order;
		cout << "Enter Order of B-Tree : ";
		cin >> Order;
		BT = new BTree(Order);
		cout << "Press Enter to Read B-TREE from CSV File!\n";
		cin.get();

		for (int i = 0; i < count1 ; i++)
		{
			BT->insertion(F1[i]);
		}
		
		cout << "Your Tree Has Been Loaded!\n";
		MainMenuBTREE:
		cout << "Select Query!\n\t1.Point Search\n\t2-Range Search\n\t3-Update Value\n\t4-Delete Element\n\t5-Multi Parameter Search (Where Clause)\n\t6-Exit Program\n Enter Your Choice : ";
		cin >> choice2;
		switch (choice2) {
			case 1:
				cout << "Please Select Point Search Basis : \n\t1-ID\n\t2-Year Of Death\n\t3-Cause of Death\n\t4-State\n\t5-No of Deaths\n\t6-Death Rate\n\t7-Go Back\nEnter Your Choice : ";
				cin >> choice3;
				switch (choice3) {
					case 1:
						cout << "Please Enter ID for Point Search : ";
						cin >> choice4;
						BT->root->BTreePointSearchID(choice4);
					
						break;
					case 2:
						cout << "Please Enter Year for Point Search : ";
						cin >> choice4;
						BT->root->BTreePointSearchYear(choice4);
						break;
					case 3:
						cout << "Please Enter Cause for Point Search : ";
						cin >> temp1;
						BT->root->BTreePointSearchCause(temp1);
						break;
					case 4:
						cout << "Please Enter State for Point Search : ";
						cin >> temp1;
						BT->root->BTreePointSearchState(temp1);
						break;
					case 5:
						cout << "Please Enter No Of Deaths for Point Search : ";
						cin >> choice4;
						BT->root->BTreePointSearchD(choice4);
						break;
					case 6:
						cout << "Please Enter Death Rate for Point Search : ";
						cin >> float1;
						BT->root->BTreePointSearchDR(float1);
						break;
					case 7:
						goto MainMenuBTREE;
						break;
				}
				goto MainMenuBTREE;
				break;
			case 2:
				cout << "Please Select Range Search Basis : \n\t1-ID\n\t2-Year Of Death\n\t3-No of Deaths\n\t4-Death Rate\n\t5-Go Back\nEnter Your Choice : ";
				cin >> choice3;
				switch (choice3) {
				case 1:
					cout << "Please Enter Lower ID for Range Search : ";
					cin >> choice4;

					cout << "Please Enter Upper ID for Range Search : ";
					cin >> choice5;
					BT->root->BTreeRangeSearchID(choice5,choice4);
					break;
				case 2:
					cout << "Please Enter Lower Year for Range Search : ";
					cin >> choice4;

					cout << "Please Enter Upper Year for Range Search : ";
					cin >> choice5;
					BT->root->BTreeRangeSearchYear(choice5,choice4);
					break;
				case 3:
					cout << "Please Enter Lower No Of Deaths for Range Search : ";
					cin >> choice4;

					cout << "Please Enter Upper No Of Deaths for Range Search : ";
					cin >> choice5;
					BT->root->BTreeRangeSearchD(choice5,choice4);
					break;
				case 4:
					cout << "Please Enter Lower Death Rate for Range Search : ";
					cin >> float1;

					cout << "Please Enter Upper Death Rate for Range Search : ";
					cin >> float2;
					BT->root->BTreeRangeSearchDR(float2,float1);
					break;
				case 7:
					goto MainMenuBTREE;
					break;
				}
				goto MainMenuBTREE;
				break;
			case 3:
				cout << "Please Enter the ID of the Element you would like to update : ";
				cin >> choice3;
				BT->root->BTreeUpdateQuery(choice3);
				goto MainMenuBTREE;
				break;
			case 4:
				cout << "Please Enter the ID of the Element you would like to Delete : ";
				cin >> choice3;
				BT->root->BTreePointSearchID(choice3);
				cout << "Are you sure you would like to delete the above element (1 | 0): ";
				cin >> choice4;
				if (choice4) {
					BT->deletion(choice3);
					goto MainMenuBTREE;
				}
				cout << "Aborted!\n";
				goto MainMenuBTREE;
				break;
			case 5:			
				cout << "Please Select A choice : \n\t1-Year and State\n\t2-Year and Cause\n\t3-Go back\nEnter Your Choice : ";
				cin >> choice3;
				switch (choice3) {
				case 1:
					cout << "Please Enter The Year of the element being searched : ";
					cin >> choice3;
					cout << "Please Enter The State of the element being searched : ";
					cin >> temp1;
					BT->root->BTreePointSearchwhereYS(choice3, temp1);
					break;
				case 2:
					cout << "Please Enter The Year of the element being searched : ";
					cin >> choice3;
					cout << "Please Enter The State of the element being searched : ";
					cin >> temp1;
					BT->root->BTreePointSearchwhereYC(choice3, temp1);
					break;
				}
				goto MainMenuBTREE;
				break;
			case 6:
				BT->root->BTreeGetNodes(Nodes);
				write_to_file(file33, Nodes);
				return 0;
				goto MainMenuBTREE;
				break;
		}

		break;
	case 2:
		cout << "Press Enter to Read AVL-TREE from CSV File!\n";
		cin.get();

		for (int i = 0; i < count1; i++)
		{
			AT = insert(F1[i], AT);
		}
		cout << "Your Tree Has Been Loaded!\n";
		MainMenuAVLTREE:
		cout << "Select Query!\n\t1.Point Search\n\t2-Range Search\n\t3-Update Value\n\t4-Delete Element\n\t5-Multi Parameter Search (Where Clause)\n\t6-Exit Program\n Enter Your Choice : ";
		cin >> choice2;
		switch (choice2) {
		case 1:
			cout << "Please Select Point Search Basis : \n\t1-ID\n\t2-Year Of Death\n\t3-Cause of Death\n\t4-State\n\t5-No of Deaths\n\t6-Death Rate\n\t7-Go Back\nEnter Your Choice : ";
			cin >> choice3;
			switch (choice3) {
			case 1:
				cout << "Please Enter ID for Point Search : ";
				cin >> choice4;
				AVLPointSearchID(AT,choice4);

				break;
			case 2:
				cout << "Please Enter Year for Point Search : ";
				cin >> choice4;
				AVLPointSearchYear(AT, choice4);
				break;
			case 3:
				cout << "Please Enter Cause for Point Search : ";
				cin >> temp1;
				AVLPointSearchCause(AT, temp1);
				break;
			case 4:
				cout << "Please Enter State for Point Search : ";
				cin >> temp1;
				AVLPointSearchState(AT, temp1);
				break;
			case 5:
				cout << "Please Enter No Of Deaths for Point Search : ";
				cin >> choice4;
				AVLPointSearchD(AT, choice4);
				break;
			case 6:
				cout << "Please Enter Death Rate for Point Search : ";
				cin >> float1;
				AVLPointSearchD(AT, float1);
				break;
			case 7:
				goto MainMenuAVLTREE;
				break;
			}
			goto MainMenuAVLTREE;
			break;
		case 2:
			cout << "Please Select Range Search Basis : \n\t1-ID\n\t2-Year Of Death\n\t3-No of Deaths\n\t4-Death Rate\n\t5-Go Back\nEnter Your Choice : ";
			cin >> choice3;
			switch (choice3) {
			case 1:
				cout << "Please Enter Lower ID for Range Search : ";
				cin >> choice4;

				cout << "Please Enter Upper ID for Range Search : ";
				cin >> choice5;
				AVLRangeSearchID(AT, choice4, choice5);
				break;
			case 2:
				cout << "Please Enter Lower Year for Range Search : ";
				cin >> choice4;

				cout << "Please Enter Upper Year for Range Search : ";
				cin >> choice5;
				AVLRangeSearchYear(AT, choice4, choice5);
				break;
			case 3:
				cout << "Please Enter Lower No Of Deaths for Range Search : ";
				cin >> choice4;

				cout << "Please Enter Upper No Of Deaths for Range Search : ";
				cin >> choice5;
				AVLRangeSearchD(AT, choice4, choice5);
				break;
			case 4:
				cout << "Please Enter Lower Death Rate for Range Search : ";
				cin >> float1;

				cout << "Please Enter Upper Death Rate for Range Search : ";
				cin >> float2;
				AVLRangeSearchDR(AT, float1, float2);
				break;
			case 7:
				goto MainMenuAVLTREE;
				break;
			}
			goto MainMenuAVLTREE;
			break;
		case 3:
			cout << "Please Enter the ID of the Element you would like to update : ";
			cin >> choice3;
			AVLUpdateQuery(AT, choice3);

			goto MainMenuAVLTREE;
			break;
		case 4:
			cout << "Please Enter the ID of the Element you would like to Delete : ";
			cin >> choice3;
			AVLPointSearchID(AT, choice3);
			cout << "Are you sure you would like to delete the above element (1 | 0): ";
			cin >> choice4;
			if (choice4) {
				delete_node(choice3, AT);
				goto MainMenuAVLTREE;
			}
			cout << "Aborted!\n";
			goto MainMenuAVLTREE;
			break;
		case 5:
			cout << "Please Select A choice : \n\t1-Year and State\n\t2-Year and Cause\n\t3-Go back\nEnter Your Choice : ";
			cin >> choice3;
			switch (choice3) {
			case 1:
				cout << "Please Enter The Year of the element being searched : ";
				cin >> choice4;
				cout << "Please Enter The State of the element being searched : ";
				cin >> temp1;
				AVLPointSearchhwhereYS(AT, choice4, temp1);
				break;
			case 2:
				cout << "Please Enter The Year of the element being searched : ";
				cin >> choice4;
				cout << "Please Enter The Cause of the element being searched : ";
				cin >> temp1;
				AVLPointSearchhwhereYC(AT, choice4, temp1);
				break;
			}
			goto MainMenuAVLTREE;
			break;
		case 6:
			AVLGetNodes(AT, Nodes);
			write_to_file(file33, Nodes);
			return 0;
			goto MainMenuAVLTREE;
			break;
		}

		break;
	}


}