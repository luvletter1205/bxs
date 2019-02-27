#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <shlobj.h>
#include <vector>
#include "TLargeFloat.h"

const int max_num_of_variables=10000;
const int max_num_of_code_lines=10000;

using namespace std;


TLargeFloat X[max_num_of_variables];int v_id=0; 	 //variable and its id
map <string,int> var;						 //RB-tree conect variable and its id
char str[max_num_of_code_lines][120];		 //Save the code
int line;									 //line of code

bool isBlack(const char& ch)
{
	if(ch==' '||ch=='\n'||ch=='\t')return true;
	return false;
}

int vdef (string variable_name)      		 //define a new variable
{
	var[variable_name]=++v_id;
	return v_id;
}

TLargeFloat vcal (string variable_name)
{
	if(var.find(variable_name) == var.end() )
		throw;
	else
		return X[var[variable_name]];
}

void assignment (string variable_name,TLargeFloat num)	//assignment a variable
{
	
	if(var.find(variable_name) == var.end() )
		X[vdef(variable_name)]=num;
	else
		X[var[variable_name]]=num;
}

//获取文件拓展名
//filename:文件名 
//返回：
//含有. 
//不含大写字母 
//eg.
//FileType("example.eG")=".eg"
string FileType(const string &filename)
{
	int p=filename.length()-1;
	while(filename[p]!='.'&&p>=0)p--;
	if(p<0)return "";
	string tmp=filename.substr(p,filename.length()-p+1);
	for(auto &i:tmp)
	{
		if(i>='A'&&i<='Z')i+=32;
	}
	return tmp;
}
//apart sentences
//char b[10][101];
/*void apart(int line_id)
{
	int len=strlen(str[line_id]);
	cout<<"apart note: "<<len<<endl;
	int top=1,size=0;
	bool bl;
	for(int i=0;i<len;i++)
	{
		cout<<"for note: "<<str[line_id][i]<<endl;
		if(str[line_id][i]==' ')
		{
			if(bl==0)
				continue;
			if(bl==1)
			{
				top++;
				size=0;
				bl=0;
			}
		}
		else 
		{
			bl=1;
			b[top][size]=str[line_id][i];
			size++;
			cout<<b[top]<<endl;
		}
	}
//	cout<<"apart note: "<<b[1]<<" "<<b[2]<<endl;
}*/

vector <string> apart(const int &line_id)
{
	vector<string> words;
	string tmp="";
	for(auto i:str[line_id])
	{
		if(isBlack(i)&&tmp!="")
		{
			words.push_back(tmp);
			tmp="";
		}
		else tmp+=i;
	}
	if(tmp!="")
		words.push_back(tmp);
	return words;
}

void INPUT_ (vector<string>tmp)
{
	if(tmp[1][0]=='\"')
	{
		int len=tmp[1].length();
		for(int i=1;i<len-2;i++)
			cout<<tmp[1][i];
		cout<<endl;
		string x0;
		cin>>x0;
		TLargeFloat x(x0);
		x.SetDigitsLength(DEFAULT_DigitsArraySize);
		assignment(tmp[2],x);
	}
	else
	{
	string x0;
		cin>>x0;
		TLargeFloat x(x0);
		x.SetDigitsLength(DEFAULT_DigitsArraySize);
		assignment(tmp[1],x);
	}
}

void PRINT_ (vector<string>tmp)
{
	if(tmp[1][0]=='\"')
	{
		int len=tmp[1].length();
		for(int i=1;i<len-2;i++)
			cout<<tmp[1][i];
		cout<<endl;
		cout<<vcal(tmp[2]);
	}
	else
		cout<<vcal(tmp[1]);
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


void solve_sentence(const int &line_id)
{
	
	/*if(strs=="PRINT")
		PRINT_(line_id);
	else if (strs=="INPUT")
		INPUT_(line_id);*/
	auto tmp=apart(line_id);
	if(tmp[0]=="PRINT")
		PRINT_(tmp);
	if(tmp[0]=="INPUT")
		INPUT_(tmp);
	
}

void read(string name)
{
	//cout<<name<<endl;
	if(FileType(name)!=".bxs")
		name+=".bxs";
	string path = getDesktopPath();
	path += "\\" ;
	path+=name;
    char *p = const_cast<char*>(path.data());
	ifstream in(p); 
	if(!in)
	{
		cerr<<"No such file!";
		exit(2);
	}
	while(in.getline(str[++line],100));
}

int main(int argc,char **argv)
{
	
//	TLargeFloat a,b,c[3];
//	string a1,b1;
//	cin>>a1>>b1;
//	a=TLargeFloat(a1);
//	b=TLargeFloat(b1);
//	a.SetDigitsLength(DEFAULT_DigitsArraySize);
//	b.SetDigitsLength(DEFAULT_DigitsArraySize);
//	cout<<a<<endl;
//	cin>>a>>b;
//	c[0]=a*b;
//	c[1]=a/b;
//	c[2]=a+b;
//	for(int i=0;i<3;i++)
//	{
//		cout<<c[i]<<endl;
//	}
	cout<<fixed;
	if(argc!=2)
	{
		cerr<<"No such file!";
		return 2;
	}
	read(string(argv[1]));
	solve_sentence(1);
	solve_sentence(2);
}
