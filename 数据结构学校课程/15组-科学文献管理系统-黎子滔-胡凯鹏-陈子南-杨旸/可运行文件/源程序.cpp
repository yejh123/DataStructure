#include<fstream>
#include<algorithm>
#include<iostream>
#include<string>    
#include<set>
#include<io.h>
using namespace std;

struct Info
{
	int size;
	string name;
	Info *next;
	Info ( string n, int s )
	{
		size = s;
		name = n;
		next = NULL;
	}
};

string titledir = "D://Czz/huge/title/";
string authordir = "D://Czz/huge/authors/author/";
string authorcountdir = "D://Czz/huge/authors/author_count/";
string keyworddir = "D://Czz/huge/keywords/keyword/";
string keywordcountdir = "D://Czz/huge/keywords/keyword_count/";
string datafile = "D://huge/dblp.xml";
string dataindex = "D://huge/dblpindex_otherone.dat";

void qSQ(Info *pBegin, Info *pEnd)                          //链表快排
{
	if ( pBegin==pEnd ) return;
	Info *key = new Info( pBegin->name,  pBegin->size);
	Info *p = pBegin;
	Info *q = p->next;
	while(q != pEnd)
    {
        if(q->size > key->size)  
        {  
            p = p->next;  
            swap(p->size,q->size);
			swap(p->name,q->name);
        }  
        q = q->next;  
    }  
    swap(p->size,pBegin->size);
	swap(p->name,pBegin->name);
	qSQ(pBegin,p);  
    qSQ(p->next,pEnd);  
}                           
int  getKeyword( string &line, string &keyword )
{
	if (line.compare("") == 0) return 0;
	int i=0;
	for (; i<=line.size(); i++)
		if (line[i]==' ' || line[i]=='.') break;
	keyword = line.substr(0, i);
	line = line.substr(i+1);
	return 1;
}
void createKeywordFile(const string &title)
{
	string line = title;
	if (line[line.size()-1]!='.') line.append(".");
	//char* c = (char*) line.c_str();
	//cout << c << endl;
	string keyword;
	while (  getKeyword( line, keyword ) )
	{
		//cout << keyword << ' ';
		for ( int i = 0; i < keyword.size() ; i ++ )                                                   //关键字小写化
			if ( keyword[i] >= 'A' && keyword[i] <= 'Z' ) keyword[i] += 32; 
		if ( keyword.compare("a") == 0 || keyword.compare("of") == 0 || keyword.compare("for") == 0 
			|| keyword.compare("and") == 0 || keyword.compare("the") == 0 || keyword.compare("in") == 0 
			|| keyword.compare("on") == 0 || keyword.compare("to") == 0 || keyword.compare("and") == 0 
			|| keyword.compare("with") == 0 || keyword.compare("an") == 0 ) continue;
		string keywordfile = keyworddir;
		keywordfile.append(keyword).append(".txt");
		string keywordcountfile = keywordcountdir;
		keywordcountfile.append(keyword).append(".txt");
		ofstream writekeywordfile(keywordfile, ios::app), writekeywordcountfile(keywordcountfile, ios::app);
		writekeywordfile << title << endl;
		writekeywordcountfile << 1;
		writekeywordcountfile.close();
		writekeywordfile.close();
		//cout << authorfile << endl;
	}	
}
void collectInf(ifstream &data)
{
	string content = "", line, title;
	set<string> authorset;
	authorset.clear();
	int i=0;
	while (getline(data, line) && (i++)<20000)
	{
		if (line.find("</article>")!=string::npos || line.find("</inproceedings>")!=string::npos)
		{
			string titlefile = titledir;
			titlefile.append(title);
			titlefile.append(".txt");     //内容写入titlefile.txt
			if (titlefile.find(':',3)!=string::npos) titlefile[titlefile.find(':',3)]='_';
			ofstream writetitle(titlefile, ios::out);
			writetitle << content;
			content = "";
			writetitle.close();
			set<string>::iterator ii;                                                                   //往authorfile中写入title
			for( ii=authorset.begin(); ii!=authorset.end(); ii++ ) 
			{
				string author = *ii, authorfile=authordir, authorcountfile=authorcountdir;
				authorfile.append(author).append(".txt");
				authorcountfile.append(author).append(".txt");
				ofstream writeauthor(authorfile, ios::app);
				ofstream writeauthorcountfile(authorcountfile, ios::app);
				writeauthor << title << endl;
				writeauthorcountfile << 1;
				writeauthor.close();
				writeauthorcountfile.close();
			}
			authorset.clear();
			createKeywordFile(title);
			continue;
		}
		string tag, content2;
		int i1=line.find_first_of('>'), i2=line.find_last_of('<');
		tag = line.substr(1, i1-1);
		content2 = line.substr( i1+1, i2-i1-1 );
		if (tag.compare("title")==0) title = content2;
		else if (tag.compare("author")==0) 
		{
			authorset.insert(content2);
		}  
		content.append(tag).append(":").append(content2).append("\n");
	}
}
void searchMate()
{
	string targetauthor, authorfile = authordir, title, line;
	set<string> authorset;
	authorset.clear();
	getline(cin, targetauthor);
	authorfile.append(targetauthor).append(".txt");
	ifstream readauthorfile(authorfile, ios::in);
	if (readauthorfile == NULL)
	{
		cout << "Author not Finded!" << endl;
		return;
	}
	cout << "Articles :\n" << endl;                                     //...
	while (getline(readauthorfile, title))
	{
		cout << title << endl;                                          //...
		string titlefile = titledir;
		titlefile.append(title).append(".txt");
		ifstream readtitlefile(titlefile);
		while (getline(readtitlefile, line))
		{
			if (line.find("author") == string::npos) continue;
			int i = line.find_first_of(':');
			authorset.insert(line.substr(i+1));
		}
		readtitlefile.close();
	}
	cout << "\nMate:" <<endl;                                           //...
	readauthorfile.close();
	authorset.erase(targetauthor);
	set<string>::iterator ii;                                                                   //往authorfile中写入title
	for( ii=authorset.begin(); ii!=authorset.end(); ii++ ) 
	{
		cout << *ii << endl;
	}
	authorset.clear();
}
void displayTitleFile(ifstream &readtitlefile)
{
	string line, oldtag="";
	while (getline(readtitlefile, line))
	{
		string tag, content;
		int i = line.find(':');
		tag = line.substr(0, i);
		if (tag.compare("title")==0) continue;
		content = line.substr(i+1);
		if (tag.compare(oldtag) == 0) 
		{
			for (int i=0; i<11; i++) cout << ' ';
			cout << content << endl;
		} else {
			cout << tag;
			if (tag.size()<9)
			for (int i=0; i<9-tag.size(); i++) cout << ' ';
			cout <<": " << content << endl;
			oldtag = tag;
		}
	}
}
void searchTitle()
{
	cout << "Please Enter Title: ";
	string targettitle, titlefile;
	getline(cin, targettitle);
	if (targettitle[targettitle.size()-1]!='.') targettitle.append(".");
	titlefile=titledir;
	titlefile.append(targettitle).append(".txt");
	ifstream readtitlefile(titlefile, ios::in);
	if (readtitlefile==NULL)
	{
		cout << "Title Not Found!" << endl;
		return;
	}
	cout << "\nTitle    : " << targettitle << endl;
	displayTitleFile(readtitlefile);
}
void searchKeyword()
{
	cout << "Please Enter Keywords: ";
	string keyword_list, keyword;
	getline( cin, keyword_list ); 
	if (keyword_list[keyword_list.size()-1] != '.') keyword_list.append(".");
	set<string> Set1;
	Set1.clear();
	while (getKeyword(keyword_list, keyword))
	{
		for (int i=0; i<keyword.size(); i++) 
			if (keyword[i]>='A' && keyword[i]<='Z') keyword[i]+=32;
		if ( keyword.compare("a") == 0 || keyword.compare("of") == 0 || keyword.compare("for") == 0 
			|| keyword.compare("and") == 0 || keyword.compare("the") == 0 || keyword.compare("in") == 0 
			|| keyword.compare("on") == 0 || keyword.compare("to") == 0 || keyword.compare("and") == 0 
			|| keyword.compare("with") == 0 || keyword.compare("an") == 0 ) continue;
		if (keyword[keyword.size()-1] == '.') keyword = keyword.substr(0, keyword.size()-1);
		string keywordfile = keyworddir;
		keywordfile.append(keyword).append(".txt");
		ifstream readkeywordfile(keywordfile, ios::in);
		if (readkeywordfile==NULL)
		{
			cout << " Keyword \"" << keyword << "\" Not Found!" << endl;
			readkeywordfile.close();
			return;
		}
		string title;
		set<string>  Set2;
		Set2.clear();
		while ( getline(readkeywordfile, title) )
		{

			Set2.insert( title );
		}
		if ( Set1.empty() == true )
		{
			Set1.insert(Set2.begin(), Set2.end());
		} else {
			set<string> Set3; 
			set_intersection(Set1.begin(), Set1.end(), Set2.begin(), Set2.end(), inserter(Set3, Set3.begin()));
			Set1.clear();
			Set1.insert(Set3.begin(), Set3.end());
			Set3.clear();
		}
		Set2.clear();
		readkeywordfile.close();
	}
	cout << "\n Articles :" << endl;
	if (Set1.empty() == true)
	{
		cout << "sorry"<<endl;
	return;
	}
	set<string>::iterator ii;
	for( ii=Set1.begin(); ii!=Set1.end(); ii++ ) 
	{
		string title = *ii, titlefile = titledir;
		titlefile.append(title).append(".txt");
		if (titlefile.find(':',3)!=string::npos) titlefile[titlefile.find(':',3)]='_';
		ifstream readtitlefile(titlefile, ios::in);
		cout << "\nTitle    : " << title << endl;
		displayTitleFile(readtitlefile);
		cout << endl;
	}
}
void showList(Info* h)
{
	Info *p = h;
	for (; p; p=p->next)
		cout << p->name.substr(0, p->name.size()-4)  <<"  "<< p->size << endl;
}
void listFiles(int _size, string dirc)
{
    char *dir=(char*)dirc.c_str();
	strcat(dir, "*.*");        // 在要遍历的目录后加上通配符
    intptr_t handle;
    _finddata_t findData;
	Info *head = NULL, *p; 
	handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
    if (handle == -1)
    {
        cout << "Failed to find first file!\n";
        return;
    }
	
    do
    {
        if (!(findData.attrib & _A_SUBDIR
            || strcmp(findData.name, ".") == 0
            || strcmp(findData.name, "..") == 0
            ))    // 是否是子目录并且不为"."或".."
		{
			if ( findData.size > _size )
			{
				if (!(head)) 
				{
					char *c = findData.name;
					head = new Info(c, findData.size);
					p = head;
				}
					else {
					char *c = findData.name;
					p->next = new Info(c, findData.size);
					p = p->next;
				}
			}
		}
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
	p = p->next;
	cout << "Done!\n";
    _findclose(handle);    // 关闭搜索句柄
	qSQ(head, p);
	cout << endl;
	showList(head);
}
void list100()
{
	int n;
	cout << "Please choose: 1. Author  2. Keyword  3. Exit" << endl;
	cin >> n;
	if (n==1) listFiles(120, authordir);
	else if (n==2) listFiles(800, keyworddir);
	else return;
}

int main()
{
	ifstream in(datafile);
	in.seekg(0, ios::beg);
	//collectInf(in);
	//searchMate();
	searchTitle();
//	searchKeyword();
	//list100();

	
}