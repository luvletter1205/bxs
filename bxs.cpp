//code by sherrlock
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<cmath>
#include<algorithm>
#include<fstream>
#include "windows.h"
#include "shlobj.h" 

#define max_num_of_variables 10000
#define max_num_of_code_lines 10000

using namespace std;


double X[max_num_of_variables];int v_id=0; 	 //variable and its id
map <string,int> var;						 //RB-tree conect variable and its id
char str[max_num_of_code_lines][120];		 //Save the code
int line;									 //line of code

int vdef (string variable_name)      		 //define a new variable
{
	var[variable_name]=++v_id;
	return v_id;
}

int vcal (string variable_name)
{
	if(var.find(variable_name) == var.end() )
		return -1;
	else
		return X[var[variable_name]];
}

void assignment (string variable_name,double num)	//assignment a variable
{
	
	if(var.find(variable_name) == var.end() )
		X[vdef(variable_name)]=num;
	else
		X[var[variable_name]]=num;
}

void INPUT_ (string variable_name)
{
	
}

void PRINT_ (string variable_name)
{
	
}


string  getDesktopPath()
{
    LPITEMIDLIST pidl;
    LPMALLOC pShellMalloc;
    char szDir[200];
    if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
    {
        if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
            SHGetPathFromIDListA(pidl, szDir);
            pShellMalloc->Free(pidl);
        }
        pShellMalloc->Release();
    }

    return string(szDir);
}


void solve_sentence(int line_id)
{
	string strs;
	char ch;
	for(int i=0;i++;str[line_id][strs])
	{
		ch=getchar();
		strs[i]=ch;
	}
	if(strs=="PRINT")
		PRINT_();
	else if 
}

void read()
{
	string name;
	cin>>name;
	name+=".bxs";
	string path = getDesktopPath();
	path += "\\" ;
	path+=name;
    char *p = const_cast<char*>(path.data());
	ifstream in(p); 
	while(in.getline(str[++line],100));
}

int main()
{
	
	read();
	for(int i=1;i<=line;i++)
		cout<<str[i]<<endl;
}
