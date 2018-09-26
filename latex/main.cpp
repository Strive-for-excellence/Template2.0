#include<bits/stdc++.h>
using namespace std;
const int MAXL = 200;
const char* cf = "/config";
const char* tf = "template.tex";
const char* head = "head";
const char* tail = "tail";
int secn;
char sec[20][MAXL];
FILE* tex = NULL;
char temp[MAXL];
struct LineBreaker {
  char name[MAXL], file[MAXL];
  int nl, fl;
  void solve(const char s[]) {
    nl = fl = 0;
    int i = 0;
    while (s[i] && s[i] != '<') i ++;
    if (s[i]) i ++;
    while (s[i] && s[i] != '>') name[nl++] = s[i++];
    while (s[i] && s[i] != '<') i ++;
    if (s[i]) i ++;
    while (s[i] && s[i] != '>') file[fl++] = s[i++];
    name[nl] = file[fl] = 0;
  }
}lb;
void read_dir() {
  FILE* dir = fopen(cf+1, "r");
  secn = 0;
  while (fgets(sec[secn++], MAXL, dir) != NULL) {}
  fclose(dir);
  while (sec[secn-1][0] == 0 && secn > 0) secn --;
  for (int i = 0; i < secn; ++ i) {
    if (sec[i][strlen(sec[i])-1] != 0) {
      sec[i][strlen(sec[i])-1] = 0;
    }
  }
}
void file(const char* filename) {
  FILE* fp = fopen(filename, "r");
  while (fgets(temp, MAXL, fp) != NULL) fprintf(tex, temp);
  fclose(fp);
}
int main() {
  tex = fopen(tf, "w");
  file(head);
  read_dir();

  for (int i = 0; i < secn; ++ i) {
    fprintf(tex, "\\section{%s}\n", sec[i]+3);
    memcpy(temp, sec[i], sizeof temp);
    strcat(temp, cf);
    printf("section: %s\n", sec[i]);
    FILE* fp = fopen(temp, "r");

    string s;
    typedef pair<string,string> P;
    vector<P> vec;
    while(fgets(temp, MAXL, fp) != NULL) {
     string s = temp;
     if(s.find("<")==string::npos) continue;
      string s1,s2;
      for(int i = 0;i < s.size(); ++i){
         while(i < s.size()&&s[i] != '<') ++i;
         ++i;
         while(i < s.size()&&s[i] != '>') s1 += s[i++];
         ++i;
         while(i < s.size()&&s[i] != '<') ++i;
         ++i;
         while(i < s.size()&&s[i] != '>') s2 += s[i++];
         ++i;
      }
     if(s1.empty() ||s2.empty()) continue;
     vec.push_back(P(s1,s2));
     // if (temp[0] != '<') continue;
      //lb.solve(temp);
      //printf("subsection %s with %s\n", lb.name, lb.file);
      //printf("subsection %s with %s\n", s1.c_str(), lb.file);
    //  fprintf(tex, "\\subsection{%s}\n", lb.name);
    // fprintf(tex, "\\subsection{%s}\n", s1.c_str());
     // memcpy(temp, sec[i], sizeof temp);
     // temp[strlen(temp)+1] = 0;
     // temp[strlen(temp)] = '/';
     // strcat(temp, lb.file);
     // fprintf(tex, "\\inputminted{c++}{%s}\n", lb.file);
      //fprintf(tex, "\\inputminted{c++}{%s}\n",s2.c_str());
      //\inputminted[breaklines]{c++}{string/suffix-automaton.cc}
     // fprintf(tex, "\\lstinputlisting[breaklines]{%s}\n", temp);
     // fprintf(tex, "\\lstinputlisting{%s}\n", temp);
    }
    //sort(vec.begin(),vec.end());
    for(int i = 0;i < vec.size(); ++i){
    P p = vec[i];
    string s1,s2;
    s1 = p.first;
    s2 = p.second;

    fprintf(tex, "\\subsection{%s}\n", s1.c_str());
    fprintf(tex, "\\inputminted{c++}{%s}\n",s2.c_str());
    }
    fclose(fp);
  }
  file(tail);
  fclose(tex);
  return 0;
}

