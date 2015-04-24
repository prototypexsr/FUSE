#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <locale>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>
#include <ctime>

using namespace std;


//string the_path = "Users\Stefan\Documents\stuff.txt";
//http://runnable.com/UpSpP5ymsslIAAFo/reading-a-file-into-an-array-for-c%2B%2B-and-fstream
struct filename_to_inode_dict{

	int links, indirect;
	long int ctime;
	long int atime;
	long int mtime;
};
//following strip function taken from following website
//http://codereview.stackexchange.com/questions/11203/most-efficient-way-in-c-to-strip-strings

std::string strip(std::string in)
{
	in.erase(std::remove_if(in.begin(), in.end(), [](std::string::value_type ch)
	{ return !isalpha(ch); }
	), in.end());
	return in;
}

//int array_size(char vx[]);

int locate_in_array(vector<char>vec, int size, char* element){
	for (int i = 0; i < sizeof(vec); ++i) {
		if (vec[i] == *element) { return i; }
	}

		 return -1;

}



void csefsck(){
	//Split function into several parts;
	//TODO List: Verify that the following items are correct
	/*1)	The DeviceID is correct
		2)	All times are in the past, nothing in the future
		3)	Validate that the free block list is accurate this includes
		a.Making sure the free block list contains ALL of the free blocks
		b.Make sure than there are no files / directories stored on items listed in the free block list
		4)	Each directory contains.and ..and their block numbers are correct
		5)	Each directory’s link count matches the number of links in the filename_to_inode_dict
		6)	If the data contained in a location pointer is an array, that indirect is one
		7)	That the size is valid for the number of block pointers in the location array.The three possibilities are :
		a.size<blocksize if  indirect = 0 and size>0
		b.size<blocksize*length of location array if indirect != 0
		c.size>blocksize*(length of location array - 1) if indirect != 0*/
	//string number = "0";
	//string full_path = the_path + number;
	
	
}

	

		//while (getline(fp, line)){
		//	peeking = fp.peek();
		//	if (peeking != "d") fp.get();
		//	else {

		//	}
		//	//if ()
		//	//fp.get();
		//	//fp.peek();
		//	//position++;
		//	cout << line << endl;
		//}
		//while (getline(fp, line))
		//{
			//bunch of conditions, look for root block (#26), superblock( #0), generally #0-#26. The rest don't matter, 
			//unless to ensure size is 4096 bytes
			//break;
			//while (!fp.eof() && position < array_size)
			//{
				//fp.get(array[position]); //reading one character from file to array
				//position++;
			//}
			//array[position - 1] = '\0'; //placing character array terminating character

			//cout << "Displaying Array..." << endl << endl;
			//this loop display all the charaters in array till \0 
			//for (int i = 0; array[i] != '\0'; i++)
			//{
				//cout << array[i];
			//}
		
		//}
		
	//}
		/*if (fp.is_open())
		{
			//file opened successfully so we are here
			cout << "File Opened successfully!!!. Reading data from file into array" << endl;
			//this loop run until end of file (eof) does not occur
			while (!fp.eof() && position < array_size)
			{
				fp.get(array[position]); //reading one character from file to array
				position++;
			}
			array[position - 1] = '\0'; //placing character array terminating character

			cout << "Displaying Array..." << endl << endl;
			//this loop display all the charaters in array till \0 
			for (int i = 0; array[i] != '\0'; i++)
			{
				cout << array[i];
			}
		}
		else //file could not be opened
		{
			cout << "File could not be opened." << endl;
			//number += 1;
		}*/
	
int validate_devID(string file = " "){
	//This will only associate with the superblock, as devID field can only be found there.
	//There will be 2 Vectors, the first will have the correct information, and the second will be given.
	//Compare the two vectors and make adjustments as necessary. Once there is a mis match between the 2 vectors, record the index of the second one
	//Assumming the user will pass in a file name such as fusedata.[insert number from 0 to 10000] here
	//Requires that the original copy of fusedata.0 be accessible to use as a reference
	int array_size = 4096; // define the size of character array
	//char* array = new char[array_size]; // allocating an array of 4kb
	vector<char> doom(array_size);
	vector<char> doom2(array_size);
	//char* array2 = new char[array_size];
	int position = 0; //this will be used incremently to fill characters in the array
	int secposition = 0;
	fstream fp, fp2;
	string path = "fusedata.0";
	if (file != " ") {
		string passed_path = file;
		fp.open(passed_path);
		if (fp)
		{ 
			//file opened successfully so we are here
			cout << "Ok, file opened successfully, now to read the file and place into array" << endl;
			//this loop run until end of file (eof) does not occur
			while (!fp.eof() && secposition <= array_size - 1)
			{
				fp.get(doom2[secposition]); //reading one character from file to array
				secposition++;
			}
			doom2[secposition - 1] = '\0'; //placing character array terminating character

			cout << "Displaying Array..." << endl << endl;
			//this loop display all the charaters in array till \0 
			for (int i = 0; doom2[i] != '\0'; i++)
			{
				cout << doom2[i];
			}
			cout << doom2[0];
			cout << doom2[1] << endl;
			fp2.close();
		}
		else //file could not be opened
		{
			cout << "File could not be opened." << endl;
			return -1;
		}
	}

	fp.open(path);
	if (fp)
	{
		//file opened successfully so we are here
		cout << "Ok, Reference file opened successfully, now to read the file and place into vector" << endl;
		//this loop run until end of file (eof) does not occur
		while (!fp.eof() && position < array_size - 1)
		{
			fp.get(doom[position]); //reading one character from file to array
			position++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		fp.close();

		cout << "Displaying Vector..." << endl << endl;
		//this loop display all the charaters in array till \0 
		//for (int i = 0; array[i] != '\0'; i++)
		for (vector<char>::iterator i = doom.begin(); i != doom.end(); ++i)
		{
			cout << *i;
		}
		cout << doom[0];
		cout << doom[1] << endl;
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
		return -1;
	}

	//int pos = 0;
	fp.open(path, ofstream::trunc);
	for(int pos = 0; pos < doom.size(); ++pos) {

		if (doom[pos] == 'd' && doom[pos + 1] == 'e' && doom[pos + 2] == 'v' &&  doom[pos + 3] == 'I'
			&& doom[pos + 4] == 'd'  && doom[pos + 5] == ':'){
			//break;
			cout << "Got it" << endl;
			if (doom[pos + 6] != '2' || doom[pos + 7] != '0' ){
				cout << "This is not your file system" << endl;
				return -1;
				//doom[pos + 6] = '2';
			
			}
	
			cout << "This is your file system, you may proceed" << endl;
		}
	//	if (doom[pos] == 'd'){
	//		if (doom[pos + 1] == 'e'){
	//			//cout << "IN" << endl;
	//			if (doom[pos + 2] == 'v'){
	//				if (doom[pos + 3] == 'I'){
	//					if (doom[pos + 4] == 'd'){
	//						if (doom[pos + 5] == ':'){
	//							//cout << "found devID" << endl;
	//							if (doom[pos + 6] == '2'){
	//								cout << "correct" << endl;
	//								//doom[pos + 6] = '2';
	//								if (doom[pos + 7] == '0'){
	//									cout << "correct" << endl;
	//									//doom[pos + 7] == '0';
	//								}
	//								else { cout << "Incorrect" << endl; doom[pos + 7] = '0'; }
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	}
	
	for (int j = 0; j < doom.size(); ++j){
		fp << doom[j];
		cout << doom[j];
		fp.close();
	}
	if (file != " "){
		for (vector<char>::iterator i = doom.begin(); i != doom.end(); ++i)
		{
			for (vector<char>::iterator j = doom2.begin(); j != doom2.end(); ++j){
				if (*i != *j){
					cout << "Mismatch" << endl;
				}
			}
		}
	}

	return 0;

}
  

bool days_of_future_past(){
	//dealing with superblock, and root directory block
	time_t timer;
	string path1 = "fusedata.26";
	string path2 = "fusedata.0";
	string path3 = "fusedata.27";
	//string path2 = "fusedata.25";
	filename_to_inode_dict fidct;

	(fidct.atime) = time(&timer);
	(fidct.ctime) = time(&timer);
	(fidct.mtime) = time(&timer);
	//gotta look for position where the time fields are stored.
	fstream fr, f2, f3;
	int array_size = 4096; // define the size of character array
	vector<char> exo(array_size);
	vector<char> exo2(array_size);
	vector<char> exo3(array_size);
	//char* exo = new char[array_size]; // allocating an array of 4kb
	//char* exo2 = new char[array_size];
	int position = 0;
	int secposition = 0;
	int tetposition = 0;
	long int time_value, atime_value, ctime_value, mtime_value;
	atime_value = (fidct.atime);
	ctime_value = (fidct.ctime);
	mtime_value = (fidct.mtime);
	cout << fidct.atime << endl;
	fr.open(path1);
	if (fr)
	{
		//file opened successfully so we are here
		cout << "Ok, fusedata26 opened successfully, now to read the file and place into array" << endl;
		//this loop run until end of file (eof) does not occur
		while (!fr.eof() && position < array_size - 1)
		{
			fr.get(exo[position]); //reading one character from file to array
			position++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		fr.close();

		for (int location = 0; location < exo.size(); ++location){
			if (exo[location] == 't' && exo[location + 1] == 'i' && exo[location + 2] == 'm' && exo[location + 3] == 'e'
				&& exo[location + 4] == ':'){
				//cout << "TIME" << endl;
				if (exo[location - 1] == 'a'){
											//cout << "case 2" << endl;
					cout << "ATIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													//concaterizer(buffer, &exo[location + 6]);
												}
											}
											time_value = atol(buffer);
											if (time_value < atime_value) {
												cout << "atime value is in the past. True" << endl;
												//return true;
											}
											else{
												cout << "false" << endl;
												//return false;
											}
											//break;
										}
										if (exo[location - 1] == 'c'){
											cout << "CTIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													//concaterizer(buffer, &exo[location + 6]);
												}
											}
											time_value = atol(buffer);
											if (time_value < ctime_value){ cout << "ctime value is in the past. True" << endl; 
											//return true;
											}

											else {
												cout << "false" << endl;
												//return false;
											}
											//break;
										}
										if (exo[location - 1] == 'm'){
											cout << "MTIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													//concaterizer(buffer, &exo[location + 6]);
												}
											}
											time_value = atol(buffer);
											if (time_value < mtime_value) { 
												cout << "mtime value is in the past. True" << endl;
												//return true;
											}

											else {
												//return false;
												cout << "false" << endl;
											}
											//break;
										}
			}
			//if (exo[location] == 't'){
			//	if (exo[location + 1] == 'i'){
			//		if (exo[location + 2] == 'm'){
			//			if (exo[location + 3] == 'e'){
			//				if (exo[location + 4] == ':'){
			//					cout << "TIME" << endl;
			//					if (exo[location - 1] == 'a'){
			//						//cout << "case 2" << endl;
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < atime_value) cout << "atime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//					if (exo[location - 1] == 'c'){
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//					if (exo[location - 1] == 'm'){
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < mtime_value) cout << "mtime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//				}
			//			}
			//		}
			//	}
			//}
		}

	}

	else{

		cout << "File couldnt be opened" << endl;
		return false;
	}
	//fr.close();

	f2.open(path2);
	if (f2)
	{
		//file opened successfully so we are here
		cout << "Ok, fusedata0 opened successfully, now to read the file and place into array" << endl;
		//this loop run until end of file (eof) does not occur
		while (!f2.eof() && secposition < array_size - 1)
		{
			f2.get(exo2[secposition]); //reading one character from file to array
			secposition++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		f2.close();
		//WARING: LOTS OF IF STATEMENTS INBOUND. GOTTA MAKE SURE ALL BASES ARE COVERED
		//GOOD THING THE TEXT IS IN ENGLISH
		//SIMPLIFIED VERSION
		for (int location2 = 0; location2 < exo2.size(); ++location2){
			if (exo2[location2] == 'c' && exo2[location2 + 1] == 'r' && exo2[location2 + 2] == 'e' && exo2[location2 + 3] == 'a'
				&& exo2[location2 + 4] == 't' && exo2[location2 + 5] == 'i' && exo2[location2 + 6] == 'o' && exo2[location2 + 7] == 'n'){

				if (exo2[location2 + 13] != ' '){
							char buffer[10];
							int counter = 0;
							for (char it = exo2[location2 + 13]; it < exo2[location2 + 24]; ++it){
						    for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							//concaterizer(buffer, &exo[location + 6]);
										}
					           }
							time_value = atol(buffer);
							if (time_value < ctime_value) { cout << "ctime value is in the past. True" << endl;
							//return true;
							}

							else{
								cout << "false" << endl;
								//return false;
							}
						//break;
							}
				else {
					char buffer[10];
					int counter = 0;
					for (char it = exo2[location2 + 14]; it < exo2[location2 + 25]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							//concaterizer(buffer, &exo[location + 6]);
						}
					}
					time_value = atol(buffer);
					if (time_value < ctime_value) { cout << "ctime value is in the past. True" << endl;
					//return true;
					}
					else {
						cout << "false" << endl;
						//return false;
					}
					//break;
				}
			}

			//BELOW IS EXTREME HARDCODING. 
			//if (exo2[location2] == 'c' || exo2[location2] == 'C'){ //c or C
			//	if (exo2[location2 + 1] == 'r' || exo2[location2 + 1] == 'R' || exo2[location2 + 1] == 't' || exo2[location2 + 1] == 'T'
			//		|| exo2[location2 + 1] == '_'){ // cr or ct or c_ (non-case sensitive)  
			//		if (exo2[location2 + 2] == 'e' || exo2[location2 + 2] == 'E' || exo2[location2 + 2] == 'i'
			//			|| exo2[location2 + 2] == 'I' || exo2[location2 + 2] == 'T' || exo2[location2 + 2] == 't'){ //cre or cti or c_t (non-case sensitive)
			//			if (exo2[location2 + 3] == 'a' || exo2[location2 + 3] == 'A' || exo2[location2 + 3] == 'm' || exo2[location2 + 3] == 'M'
			//				|| exo2[location2 + 3] == 'i' || exo2[location2 + 3] == 'I'){ //crea or ctim or c_ti (non-case sensitive)
			//				if (exo2[location2 + 4] == 't' || exo2[location2 + 4] == 'T' || exo2[location2 + 4] == 'e' ||
			//					exo2[location2 + 4] == 'E' || exo2[location2 + 4] == 'm' || exo2[location2 + 4] == 'M'){ //creat or ctime or c_tim (non-case sensitive)
			//					if (exo2[location2 + 5] == 'i' || exo2[location2 + 5] == 'I' || exo2[location2 + 5] == ':'
			//						|| exo2[location2 + 5] == 'e' || exo2[location2 + 5] == 'E'){//creati or ctime: or c_time (non-case sensitive)
			//						if (exo2[location2 + 5] == ':'){ //check if its c_time:
			//							if (exo2[location2 + 6] != ' '){
			//								cout << "case 1" << endl;
			//								char buffer[10];
			//								int counter = 0;
			//								for (char it = exo2[location2 + 6]; it < exo2[location2 + 17]; ++it){
			//									for (int i = 0; i < 10; ++i){
			//										strcat_s(buffer, &exo[it]);
			//										//concaterizer(buffer, &exo[location + 6]);
			//									}
			//								}
			//								time_value = atol(buffer);
			//								if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//								else cout << "false" << endl;
			//								//break;
			//							}

			//							else {
			//								char buffer[10];
			//								int counter = 0;
			//								for (char it = exo2[location2 + 7]; it < exo2[location2 + 17]; ++it){
			//									for (int i = 0; i < 10; ++i){
			//										strcat_s(buffer, &exo[it]);
			//										//concaterizer(buffer, &exo[location + 6]);
			//									}
			//								}
			//								time_value = atol(buffer);
			//								if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//								else cout << "false" << endl;
			//								//break;

			//							}
			//						}
			//						if (exo2[location2 + 6] == 'o' || exo2[location2 + 6] == 'O' || exo2[location2 + 6] == ':'){ //creatio or c_time: (non-case sensitive)
			//							if (exo2[location2 + 6] == ':'){ //check if its c_time:
			//								if (exo2[location2 + 7] != ' '){
			//									cout << "case2" << endl;
			//									char buffer[10];
			//									int counter = 0;
			//									for (char it = exo2[location2 + 7]; it < exo2[location2 + 18]; ++it){
			//										for (int i = 0; i < 10; ++i){
			//											strcat_s(buffer, &exo[it]);
			//											//concaterizer(buffer, &exo[location + 6]);
			//										}
			//									}
			//									time_value = atol(buffer);
			//									if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//									else cout << "false" << endl;
			//									//break;
			//								}

			//								else {
			//									char buffer[10];
			//									int counter = 0;
			//									for (char it = exo2[location2 + 8]; it < exo2[location2 + 19]; ++it){
			//										for (int i = 0; i < 10; ++i){
			//											strcat_s(buffer, &exo[it]);
			//											//concaterizer(buffer, &exo[location + 6]);
			//										}
			//									}
			//									time_value = atol(buffer);
			//									if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//									else cout << "false" << endl;
			//									//break;
			//								}
			//							}
			//							if (exo2[location2 + 7] == 'n' || exo2[location2] == 'N'){ //Next 4 will make creation
			//								if (exo2[location2 + 8] == 'T' || exo2[location2] == 't'){
			//									if (exo2[location2 + 9] == 'i' || exo2[location2] == 'I'){
			//										if (exo2[location2 + 10] == 'm' || exo2[location2] == 'M'){
			//											if (exo2[location2 + 11] == 'e' || exo2[location2] == 'E'){
			//												if (exo2[location2 + 12] == ':'){
			//													cout << "Finally case 3" << endl;
			//													if (exo2[location2 + 13] != ' '){
			//														char buffer[10];
			//														int counter = 0;
			//														for (char it = exo2[location2 + 13]; it < exo2[location2 + 24]; ++it){
			//															for (int i = 0; i < 10; ++i){
			//																strcat_s(buffer, &exo[it]);
			//																//concaterizer(buffer, &exo[location + 6]);
			//															}
			//														}
			//														time_value = atol(buffer);
			//														if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//														else cout << "false" << endl;
			//														//break;
			//													}
			//													else {
			//														char buffer[10];
			//														int counter = 0;
			//														for (char it = exo2[location2 + 14]; it < exo2[location2 + 25]; ++it){
			//															for (int i = 0; i < 10; ++i){
			//																strcat_s(buffer, &exo[it]);
			//																//concaterizer(buffer, &exo[location + 6]);
			//															}
			//														}
			//														time_value = atol(buffer);
			//														if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//														else cout << "false" << endl;
			//														//break;
			//													}
			//												}
			//											}
			//										}
			//									}
			//								}
			//							}
			//						}
			//					}
			//				}
			//			}
			//		}
			//	}
			//}
		}
	}
	else{

		cout << "File couldnt be opened" << endl;
		return false;
	}
	f3.open(path3);
	if (f3)
	{
		//file opened successfully so we are here
		cout << "Ok, fusedata27 opened successfully, now to read the file and place into array" << endl;
		//this loop run until end of file (eof) does not occur
		while (!f3.eof() && tetposition < array_size - 1)
		{
			f3.get(exo3[tetposition]); //reading one character from file to array
			tetposition++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		f3.close();


		for (int location3 = 0; location3 < exo3.size(); ++location3){
			if (exo3[location3] == 't' && exo3[location3 + 1] == 'i' && exo3[location3 + 2] == 'm' && exo3[location3 + 3] == 'e'
				&& exo3[location3 + 4] == ':'){
				//cout << "TIME" << endl;
				if (exo3[location3 - 1] == 'a'){
					//cout << "case 2" << endl;
					cout << "ATIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							//concaterizer(buffer, &exo[location + 6]);
						}
					}
					time_value = atol(buffer);
					if (time_value < atime_value) {
						cout << "atime value is in the past. True" << endl;
						//return true;
					}
					else {
						cout << "false" << endl;
						//return false;
					}
					//break;
				}
				if (exo3[location3 - 1] == 'c'){
					cout << "CTIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							//concaterizer(buffer, &exo[location + 6]);
						}
					}
					time_value = atol(buffer);
					if (time_value < ctime_value){
						cout << "ctime value is in the past. True" << endl;
						//return true;
					}
					else{
						cout << "false" << endl;
						//return false;
					}
					//break;
				}
				if (exo3[location3 - 1] == 'm'){
					cout << "MTIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							//concaterizer(buffer, &exo[location + 6]);
						}
					}
					time_value = atol(buffer);
					if (time_value < mtime_value){
						cout << "mtime value is in the past. True" << endl;
						//return true;
					}
					else {
						cout << "false" << endl;
						//return false;
					}
					//break;
				}
			}
			//if (exo[location3] == 't'){
			//	if (exo[location3 + 1] == 'i'){
			//		if (exo[location3 + 2] == 'm'){
			//			if (exo[location3 + 3] == 'e'){
			//				if (exo[location3 + 4] == ':'){
			//					cout << "TIME" << endl;
			//					if (exo[location3 - 1] == 'a'){
			//						//cout << "case 2" << endl;
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location3 + 5]; it < exo[location3 + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < atime_value) cout << "atime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//					if (exo[location3 - 1] == 'c'){
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location3 + 5]; it < exo[location3 + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < ctime_value) cout << "ctime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//					if (exo[location3 - 1] == 'm'){
			//						char buffer[10];
			//						int counter = 0;
			//						for (char it = exo[location3 + 5]; it < exo[location3 + 16]; ++it){
			//							for (int i = 0; i < 10; ++i){
			//								strcat_s(buffer, &exo[it]);
			//								//concaterizer(buffer, &exo[location + 6]);
			//							}
			//						}
			//						time_value = atol(buffer);
			//						if (time_value < mtime_value) cout << "mtime value is in the past. True" << endl;
			//						else cout << "false" << endl;
			//						//break;
			//					}
			//				}
			//			}
			//		}
			//	}
			//}
		}

	}

	else{

		cout << "File couldnt be opened" << endl;
		return false;
	}
	return true;
	}


	bool link_matcher(){
		//check fusedata 26 and 27
		string path = "fusedata.26";
		string path2 = "fusedata.27";
		fstream fx, fx2;
		int array_size = 4096;
		vector<char> flare(array_size);
		vector<char> flare2(array_size);
		fx.open(path);
		int position = 0;
		int secposition = 0;
		int link_count_f26 = 0;
		int link_count_f27 = 0;
		cout << "Here is fusedata 26. The linkcount listed here is: ";
		if (fx){
			while (!fx.eof() && position < array_size - 1)
			{
				fx.get(flare[position]); //reading one character from file to array
				position++;
			}
			//array[position - 1] = '\0'; //placing character array terminating character
			fx.close();

			for (int loc = 0; loc < flare.size(); ++loc){
				if (flare[loc] == 'l' && flare[loc + 1] == 'i' && flare[loc + 2] == 'n' && flare[loc + 3] == 'k'
					&& flare[loc + 4] == 'c' && flare[loc + 5] == 'o' && flare[loc + 6] == 'u' && flare[loc + 7] == 'n'
					&& flare[loc + 8] == 't' && flare[loc + 9] == ':'){
					//char buffer[2];
					//strcat_s(buffer, &)
					link_count_f26 = atoi(&flare[loc + 10]);

				}
			}

			cout << link_count_f26 << endl;
		}
		fx2.open(path2);
		cout << "Here is fusedata 27. The linkcount listed here is: ";
		if (fx2){
			while (!fx2.eof() && secposition < array_size - 1)
			{
				fx2.get(flare2[secposition]); //reading one character from file to array
				secposition++;
			}
			//array[position - 1] = '\0'; //placing character array terminating character
			fx2.close();

			for (int loc2 = 0; loc2 < flare2.size(); ++loc2){
				if (flare2[loc2] == 'l' && flare2[loc2 + 1] == 'i' && flare2[loc2 + 2] == 'n' && flare2[loc2 + 3] == 'k'
					&& flare2[loc2 + 4] == 'c' && flare2[loc2 + 5] == 'o' && flare2[loc2 + 6] == 'u' && flare2[loc2 + 7] == 'n'
					&& flare2[loc2 + 8] == 't' && flare2[loc2 + 9] == ':'){
					//char buffer[2];
					//strcat_s(buffer, &)
					link_count_f27 = atoi(&flare2[loc2 + 10]);

				}
			}

			cout << link_count_f27 << endl;
		}

		if (link_count_f26 != link_count_f27) { cout << "Linkcount does not match between these files" << endl; return false; }
		else cout << "Link count matches between these files" << endl; return true;
	}

void dot_block_checker(){

	string path = "fusedata.26";
	string path2 = "fusedata.27";
	fstream fx, fx2;
	int array_size = 4096;
	vector<char> axel(array_size);
	vector<char> axel2(array_size);
	fx.open(path);
	int position = 0;
	int secposition = 0;
	cout << "Here is fusedata 26" << endl;
	if (fx){
		while (!fx.eof() && position < array_size - 1)
		{
			fx.get(axel[position]); //reading one character from file to array
			position++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		fx.close();
		for (int location3 = 0; location3 < axel.size(); ++location3){
			if (axel[location3] == 'd'){
				if (axel[location3 + 1] == ':'){
					if (axel[location3 + 2] == '.'){
						if (axel[location3 + 3] == ':' || axel[location3 + 3] == '.'){
							if (axel[location3 + 3] == ':'){
								cout << "d:.: is here " << endl;
							}
								
							if (axel[location3 + 4] == ':'){
								cout << "d:..: is here" << endl;
							}
						
						}
						
					}
				}
			}
		}

	}
	else {
		cout << "file could not be opened" << endl;
	}
	fx2.open(path2);
	cout << "Here is fusedata 27" << endl;
	if (fx2){
		while (!fx2.eof() && position < array_size - 1)
		{
			fx2.get(axel2[position]); //reading one character from file to array
			position++;
		}
		//array[position - 1] = '\0'; //placing character array terminating character
		fx2.close();
		for (int location4= 0; location4 < axel.size(); ++location4){
			if (axel2[location4] == 'd'){
				if (axel2[location4 + 1] == ':'){
					if (axel2[location4 + 2] == '.'){
						if (axel2[location4 + 3] == ':' || axel2[location4 + 3] == '.'){
							if (axel2[location4 + 3] == ':'){
								cout << "d:.: is here " << endl;
							}

							if (axel2[location4 + 4] == ':'){
								cout << "d:..: is here" << endl;
							}

						}

					}
				}
			}
		}

	}
	else {
		cout << "file could not be opened" << endl;
	}
}









int main(){
	//csefsck();

	//cout << "hi" << endl;
	//validate_devID(); 
	//days_of_future_past();
	//dot_block_checker();
	//link_matcher();
	system("pause");
}
