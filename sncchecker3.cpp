/*Stefan N. Cherubin
N16336054
File System Checker - CS3224 HW # 3
sncchecker.cpp*/

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
#include <map>

using namespace std;

int array_size = 4096;


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
//Idea for function adapted from following website
//http://runnable.com/UpSpP5ymsslIAAFo/reading-a-file-into-an-array-for-c%2B%2B-and-fstream
vector<char> place_into_stuff(string& file, fstream& fx, vector<char>& vec){
	fx.open(file);
	int position = 0;
	std::cout << "Here is fusedata 26" << endl;
	if (fx){
		while (!fx.eof() && position < array_size - 1)
		{
			fx.get(vec[position]);
			position++;
		}

		fx.close();
	}
	else //file could not be opened
	{
		std::cout << "File could not be opened." << endl;
		exit(1);
	}
	return vec;
}



	
int validate_devID(){
	//This will only associate with the superblock, as devID field can only be found there.
	//There will be 2 Vectors, the first will have the correct information, and the second will be given.
	//Compare the two vectors and make adjustments as necessary. Once there is a mis match between the 2 vectors, record the index of the second one
	//Assumming the user will pass in a file name such as fusedata.[insert number from 0 to 10000] here
	//Requires that the original copy of fusedata.0 be accessible to use as a reference (ignore this)
	vector<char> doom(array_size);
	vector<char> doom2(array_size);
	int position = 0; 
	int secposition = 0;
	fstream fp, fp2;
	string path = "fusedata.0";
	place_into_stuff(path, fp, doom);
	
	for(int pos = 0; pos < doom.size(); ++pos) {

		if (doom[pos] == 'd' && doom[pos + 1] == 'e' && doom[pos + 2] == 'v' &&  doom[pos + 3] == 'I'
			&& doom[pos + 4] == 'd'  && doom[pos + 5] == ':'){
			
			std::cout << "Got it" << endl;
			if (doom[pos + 6] != '2' || doom[pos + 7] != '0' ){
				std::cout << "This is not your file system" << endl;
				return -1;
				
			
			}
	
			std::cout << "This is your file system, you may proceed" << endl;
		}
	
	}
	
	for (int j = 0; j < doom.size(); ++j){
		fp << doom[j];
		std::cout << doom[j];
		fp.close();
	}

	return 0;

}
  

bool days_of_future_past(){
	//dealing with superblock, and root directory block
	time_t timer;
	string path1 = "fusedata.26";
	string path2 = "fusedata.0";
	string path3 = "fusedata.27";
	filename_to_inode_dict fidct;

	(fidct.atime) = time(&timer);
	(fidct.ctime) = time(&timer);
	(fidct.mtime) = time(&timer);
	//gotta look for position where the time fields are stored.
	fstream fr, f2, f3;
	vector<char> exo(array_size);
	vector<char> exo2(array_size);
	vector<char> exo3(array_size);
	int position = 0;
	int secposition = 0;
	int tetposition = 0;
	long int time_value, atime_value, ctime_value, mtime_value;
	atime_value = (fidct.atime);
	ctime_value = (fidct.ctime);
	mtime_value = (fidct.mtime);
	place_into_stuff(path1, fr, exo);
	place_into_stuff(path2, f2, exo2);
	place_into_stuff(path3, f3, exo3);


		for (int location = 0; location < exo.size(); ++location){
			if (exo[location] == 't' && exo[location + 1] == 'i' && exo[location + 2] == 'm' && exo[location + 3] == 'e'
				&& exo[location + 4] == ':'){
				//cout << "TIME" << endl;
				if (exo[location - 1] == 'a'){
											//cout << "case 2" << endl;
					std::cout << "ATIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													
												}
											}
											time_value = atol(buffer);
											if (time_value < atime_value) {
												std::cout << "atime value is in the past. True" << endl;
												//return true;
											}
											else{
												std::cout << "false" << endl;
												//return false;
											}
											//break;
										}
										if (exo[location - 1] == 'c'){
											std::cout << "CTIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													
												}
											}
											time_value = atol(buffer);
											if (time_value < ctime_value){ std::cout << "ctime value is in the past. True" << endl; 
											//return true;
											}

											else {
												std::cout << "false" << endl;
												//return false;
											}
											//break;
										}
										if (exo[location - 1] == 'm'){
											std::cout << "MTIME" << endl;
											char buffer[10];
											int counter = 0;
											for (char it = exo[location + 5]; it < exo[location + 16]; ++it){
												for (int i = 0; i < 10; ++i){
													strcat_s(buffer, &exo[it]);
													
												}
											}
											time_value = atol(buffer);
											if (time_value < mtime_value) { 
												std::cout << "mtime value is in the past. True" << endl;
												//return true;
											}

											else {
												//return false;
												std::cout << "false" << endl;
											}
											//break;
										}
			}
		
		}

	

		for (int location2 = 0; location2 < exo2.size(); ++location2){
			if (exo2[location2] == 'c' && exo2[location2 + 1] == 'r' && exo2[location2 + 2] == 'e' && exo2[location2 + 3] == 'a'
				&& exo2[location2 + 4] == 't' && exo2[location2 + 5] == 'i' && exo2[location2 + 6] == 'o' && exo2[location2 + 7] == 'n'){

				if (exo2[location2 + 13] != ' '){
							char buffer[10];
							int counter = 0;
							for (char it = exo2[location2 + 13]; it < exo2[location2 + 24]; ++it){
						    for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							
										}
					           }
							time_value = atol(buffer);
							if (time_value < ctime_value) { std::cout << "ctime value is in the past. True" << endl;
							//return true;
							}

							else{
								std::cout << "false" << endl;
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
							
						}
					}
					time_value = atol(buffer);
					if (time_value < ctime_value) { std::cout << "ctime value is in the past. True" << endl;
					//return true;
					}
					else {
						std::cout << "false" << endl;
						//return false;
					}
					//break;
				}
			}
	
		}
	
	


		for (int location3 = 0; location3 < exo3.size(); ++location3){
			if (exo3[location3] == 't' && exo3[location3 + 1] == 'i' && exo3[location3 + 2] == 'm' && exo3[location3 + 3] == 'e'
				&& exo3[location3 + 4] == ':'){
				//cout << "TIME" << endl;
				if (exo3[location3 - 1] == 'a'){
					//cout << "case 2" << endl;
					std::cout << "ATIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							
						}
					}
					time_value = atol(buffer);
					if (time_value < atime_value) {
						std::cout << "atime value is in the past. True" << endl;
						//return true;
					}
					else {
						std::cout << "false" << endl;
						//return false;
					}
					//break;
				}
				if (exo3[location3 - 1] == 'c'){
					std::cout << "CTIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							
						}
					}
					time_value = atol(buffer);
					if (time_value < ctime_value){
						std::cout << "ctime value is in the past. True" << endl;
						//return true;
					}
					else{
						std::cout << "false" << endl;
						//return false;
					}
					//break;
				}
				if (exo3[location3 - 1] == 'm'){
					std::cout << "MTIME" << endl;
					char buffer[10];
					int counter = 0;
					for (char it = exo3[location3 + 5]; it < exo3[location3 + 16]; ++it){
						for (int i = 0; i < 10; ++i){
							strcat_s(buffer, &exo[it]);
							
						}
					}
					time_value = atol(buffer);
					if (time_value < mtime_value){
						std::cout << "mtime value is in the past. True" << endl;
						//return true;
					}
					else {
						std::cout << "false" << endl;
						//return false;
					}
					//break;
				}
			}
			
		}

	

	
	return true;
	}


bool link_matcher(){
		//check fusedata 26 and 27
		string path = "fusedata.26";
		string path2 = "fusedata.27";
		fstream fx, fx2;
		vector<char> flare(array_size);
		vector<char> flare2(array_size);
		fx.open(path);
		int position = 0;
		int secposition = 0;
		int link_count_f26 = 0;
		int link_count_f27 = 0;
		std::cout << "Here is fusedata 26. The linkcount listed here is: ";
		place_into_stuff(path, fx, flare);

			for (int loc = 0; loc < flare.size(); ++loc){
				if (flare[loc] == 'l' && flare[loc + 1] == 'i' && flare[loc + 2] == 'n' && flare[loc + 3] == 'k'
					&& flare[loc + 4] == 'c' && flare[loc + 5] == 'o' && flare[loc + 6] == 'u' && flare[loc + 7] == 'n'
					&& flare[loc + 8] == 't' && flare[loc + 9] == ':'){
					link_count_f26 = atoi(&flare[loc + 10]);

				}
			}

			std::cout << link_count_f26 << endl;
		
		std::cout << "Here is fusedata 27. The linkcount listed here is: ";
		place_into_stuff(path2, fx2, flare2);

			for (int loc2 = 0; loc2 < flare2.size(); ++loc2){
				if (flare2[loc2] == 'l' && flare2[loc2 + 1] == 'i' && flare2[loc2 + 2] == 'n' && flare2[loc2 + 3] == 'k'
					&& flare2[loc2 + 4] == 'c' && flare2[loc2 + 5] == 'o' && flare2[loc2 + 6] == 'u' && flare2[loc2 + 7] == 'n'
					&& flare2[loc2 + 8] == 't' && flare2[loc2 + 9] == ':'){
					link_count_f27 = atoi(&flare2[loc2 + 10]);

				}
			}

			std::cout << link_count_f27 << endl;
		

		if (link_count_f26 != link_count_f27) { std::cout << "Linkcount does not match between these files" << endl; return false; }
		else std::cout << "Link count matches between these files" << endl; return true;
	}
	

void dot_block_checker(){

	string path = "fusedata.26";
	string path2 = "fusedata.27";
	fstream fx, fx2;
	vector<char> axel(array_size);
	vector<char> axel2(array_size);
	fx.open(path);
	int position = 0;
	int secposition = 0;
	std::cout << "Here is fusedata 26" << endl;
	place_into_stuff(path, fx, axel);
		for (int location3 = 0; location3 < axel.size(); ++location3){
			if (axel[location3] == 'd'){
				if (axel[location3 + 1] == ':'){
					if (axel[location3 + 2] == '.'){
						if (axel[location3 + 3] == ':' || axel[location3 + 3] == '.'){
							if (axel[location3 + 3] == ':'){
								std::cout << "d:.: is here " << endl;
							}
								
							if (axel[location3 + 4] == ':'){
								std::cout << "d:..: is here" << endl;
							}
						
						}
						
					}
				}
			}
		}

	std::cout << "Here is fusedata 27" << endl;
	place_into_stuff(path2, fx2, axel2);
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
	



bool direct_check_indirect(string pathname, int& notdirect, vector<char>& location){
	// should look at location and open the block listed.
	string pather = pathname;
	int position = 0;
	vector<char> invective(array_size);
	fstream directive;
	place_into_stuff(pather, directive, invective);
		for (int i = 0; i < invective.size(); ++i){
			if (invective[i] == 'i' && invective[i + 1] == 'n' && invective[i + 2] == 'd' && invective[i + 3] == 'i'
				&& invective[i + 4] == 'r' && invective[i + 5] == 'e' && invective[i + 6] == 'c' && invective[i + 7] == 't'){
				if (invective[i + 8] == ':'){
					notdirect = atoi(&invective[i + 9]);
					
				}
				if (notdirect != 0 && !invective.empty() || notdirect == 0 && invective.empty()){
					location.push_back(invective[i + 9]);
					return true;
				}
				else {
					cout << "Incorrect data" << endl;
					return false;
				}
				return false;
			}

		}
	
	
	return false;
}


bool sizecheck(string pathname, int& indirection, vector<char>& current_spot){
	string file = pathname;
	fstream plug, outlet;
	vector<char> pocket(array_size);
	int position = 0;
	int length_of_location_array;
	vector<char> locations(array_size);
	char* spot;
	int size = 0;
	place_into_stuff(file, plug, pocket);
		for (int i = 0; i < pocket.size(); ++i){
			if (pocket[i] == 'l' && pocket[i + 1] == 'o' && pocket[i + 2] == 'c' && pocket[i + 3] == 'a' && pocket[i + 4] == 't'
				&& pocket[i + 5] == 'i' && pocket[i + 6] == 'o' && pocket[i + 7] == 'n' && pocket[i + 8] == ':'){
				if (pocket[i + 10] != ','){
					char buffer[10];
					int counter = 0;
					strcat_s(buffer, &pocket[i + 9]);
					strcat_s(buffer, &pocket[i + 10]);
					spot = buffer;
				}
				else {
					char buffer[10];
					int counter = 0;
					strcat_s(buffer, &pocket[i + 9]);
					spot = buffer;

				}
	
			}

		}
		for (int k = 0; k < pocket.size(); ++k){
			if (pocket[k] == 's' && pocket[k + 1] == 'i' && pocket[k + 2] == 'z' && pocket[k + 3] == 'e' && pocket[k + 4] == ':'){
				size = atoi(&pocket[k + 5]);
			}
		}


	
	int secposition = 0;
	place_into_stuff(file, outlet, locations);

		if (locations[0] == ' '){
			length_of_location_array = 0;
		}
		length_of_location_array = 1;
		for (int j = 0; j < locations.size(); ++j){
			if (locations[j] == ','){
				length_of_location_array++;
			}
		}

	

	if (indirection == 0 && size <= 4096){
		cout << "Indirect is zero and size is at most 4096" << endl;
		return true;
	}
	else if (array_size * (length_of_location_array - 1) < size && size < array_size * length_of_location_array){
		cout << "The inequality array_size * (length_of_location_array - 1) < size < array_size * length_of_location_array is true " << endl;
		return true;
	}
	else {
		return false;
	}

	return false;
}


bool free_blockparty(string filez, int& block_number, vector<int> &fblock_list, map<string, string> &freeblocks){
	
	fstream filer;
	int position = 0;
	vector<char> block_party(array_size);
	if (filer){
		fblock_list.push_back(block_number);
		for (int i = 1; i < 26; ++i){
			fstream file("fusedata." + i);
			if (file){
				continue;
			}
			place_into_stuff(filez, filer, block_party);

			
			char* current_fblock = " ";
			current_fblock = _itoa(block_number, current_fblock, 10);
			
			for (int sx = 0; sx < block_party.size(); ++sx){
				if (atoi(&block_party[sx]) || atoi(&block_party[sx + 1]) || atoi(&block_party[sx + 2]) || atoi(&block_party[sx + 3])
					|| atoi(&block_party[sx + 4]) || atoi(&block_party[sx + 5])){
					if (atoi(&block_party[sx]) && atoi(&block_party[sx + 1])){
						char buffer[10];
						strcat_s(buffer, &block_party[sx]);
						strcat_s(buffer, &block_party[sx + 1]);
						if (buffer != current_fblock){ continue; }
						return true;
					}
					else if (atoi(&block_party[sx]) && atoi(&block_party[sx + 1]) && atoi(&block_party[sx + 2])){
						char buffer[10];
						strcat_s(buffer, &block_party[sx]);
						strcat_s(buffer, &block_party[sx + 1]);
						strcat_s(buffer, &block_party[sx + 2]);
						if (buffer != current_fblock){ continue; }
						return true;
					}
					else if (atoi(&block_party[sx]) && atoi(&block_party[sx + 1]) && atoi(&block_party[sx + 2]) && atoi(&block_party[sx + 3])){
						char buffer[10];
						strcat_s(buffer, &block_party[sx]);
						strcat_s(buffer, &block_party[sx + 1]);
						strcat_s(buffer, &block_party[sx + 2]);
						strcat_s(buffer, &block_party[sx + 3]);
						if (buffer != current_fblock){ continue; }
						return true;
					}
					else if (atoi(&block_party[sx]) && atoi(&block_party[sx + 1]) && atoi(&block_party[sx + 2]) && atoi(&block_party[sx + 3])
						&& atoi(&block_party[sx + 4])){
						char buffer[10];
						strcat_s(buffer, &block_party[sx]);
						strcat_s(buffer, &block_party[sx + 1]);
						strcat_s(buffer, &block_party[sx + 2]);
						strcat_s(buffer, &block_party[sx + 3]);
						strcat_s(buffer, &block_party[sx + 4]);
						if (buffer != current_fblock){ continue; }
						return true;
					}
					else if (atoi(&block_party[sx]) && atoi(&block_party[sx + 1]) && atoi(&block_party[sx + 2]) && atoi(&block_party[sx + 3])
						&& atoi(&block_party[sx + 4]) && atoi(&block_party[sx + 5])){
						char buffer[10];
						strcat_s(buffer, &block_party[sx]);
						strcat_s(buffer, &block_party[sx + 1]);
						strcat_s(buffer, &block_party[sx + 2]);
						strcat_s(buffer, &block_party[sx + 3]);
						strcat_s(buffer, &block_party[sx + 4]);
						strcat_s(buffer, &block_party[sx + 5]);
						if (buffer != current_fblock){ continue; }
						return true;
					}

				}
				else {
					return false;
				}

			}

			
		}
		cout << "fusedata." + block_number << "is a free block however is not in the Free Block List.";
		return false;
	}
	else {
		cout << "File could not be opened " << endl;
		return false;
	}
	filer.close();
	
		
	return false;
}

bool free_block_list_check(map<string, string> &FreeBlocks){
	for each(pair<string, string> blocks in FreeBlocks){
		fstream path("fusedata." + blocks.first);
		if (!path){
			return false;
		}
		stringstream streamer;
		streamer << path.rdbuf();
		string file_read = streamer.str();
		path.close();

		if (!file_read.empty()){
			cerr << "There exists a file (fusedata." + blocks.first + ") belonging to the free block list that is currently not empty" << endl;
			return false;
		}
	}
	return true;
}
bool csefsck(){
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
	c.size>blocksize*(length of location array - 1) if indirect != 0
	b and c equates to: blocksize * (length of location array -1) < size < blocksize * length of location array if indirect != 0 */
	vector<char> locations;
	int indirect;
	map<string, string> freeblocks;
	vector<int> block_list;
	int result_dev = validate_devID();
	for (int i = 0; i < 10000; ++i){
		ifstream file("fusedata." + i);
		if (!file.is_open()){
			return false;
		}
		stringstream stream;
		stream << file.rdbuf();
		string readFile = stream.str();
		file.close();

		if (result_dev != 0) {
			cout << "Dev ID has reported that this is not your filesystem. I cannot allow you to go any further" << endl;
			//exit(1);
		}
		bool time_stone = days_of_future_past();
		if (!time_stone){
			cout << "Looks like one of the times listed in a block is not in the past" << endl;
			//exit(1);
		}
		bool link_test = link_matcher();
		if (!link_test){
			cout << "Number of links is inconsistent with multiple blocks" << endl;
			//exit(1);
			return false;
		}
		dot_block_checker();
		bool indirect_check = direct_check_indirect(readFile, indirect, locations);
		if (!indirect_check){
			cout << "Indirect has not been correctly set" << endl;
			//exit(1);
			return false;
		}

		bool size = sizecheck(readFile, indirect, locations);
		if (!size){
			cout << "It was reported that the size for specificed parameters is invalid" << endl;
			//exit(1);
			return false;
		}

		bool blockade = free_blockparty(readFile, i, block_list, freeblocks);
		if (!blockade){
			cout << "There is something not contained in the free block list that should be" << endl;
			//exit(1);
			return false;
		}

	}
	bool blockparty = free_block_list_check(freeblocks);
	if (!blockparty){
		cout << "There is something in the free block list that shouldn't be there" << endl;
		return false;
	}
	return true;
}

int main(){
	csefsck();

	//cout << "hi" << endl;
	//validate_devID(); 
	//days_of_future_past();
	//dot_block_checker();
	//link_matcher();
	//sizecheck();
	//direct_check_indirect();
	//free_blockparty();
	//free_block_list_check(freeblocks);
	
	system("pause");
}
