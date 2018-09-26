

#include<bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
string config = "/config";
typedef pair<string,string> P;
void dfs(char *path,vector<P> &vec){
    DIR              *pDir ;
    struct dirent    *ent  ;
    char              childpath[1000];

    pDir=opendir(path);
     if(pDir == NULL) {
       // cout<<path<<"3 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));
    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        if(ent->d_type == DT_DIR)
        {
            //sprintf(childpath,"%s/%s",path,ent->d_name);
          //  printf("path:%s\n",childpath);
            sprintf(childpath,"%s/%s",path,ent->d_name);
            dfs(childpath,vec);

        }
        else if(ent->d_type)
        {
            string s = ent->d_name;
            if(s.find(".cpp") != string::npos)
            vec.push_back(P(string(path)+"/"+ent->d_name,ent->d_name));
        }
    }
}
void print(char * path){
    vector<P> vec;
    DIR              *pDir ;
    struct dirent    *ent  ;
    char              childpath[1000];

     pDir=opendir(path);
     if(pDir == NULL) {
       // cout<<path<<"2 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));
    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        if(ent->d_type == DT_DIR)
        {
            sprintf(childpath,"%s/%s",path,ent->d_name);
            //printf("path:%s\n",childpath);

           dfs(childpath,vec);

        }
        else if(ent->d_type==DT_REG)
        {

            string s = ent->d_name;
            if(s.find(".cpp") != string::npos)
            vec.push_back(P(string(path)+"/"+ent->d_name,ent->d_name));
            //cout<<ent->d_name<<endl;
        }
    }
   /// ofstream out;
    if(vec.empty()) return;
    const string s = string(path)+"/config";
    FILE *file = fopen(s.c_str(),"w+");
   // out.open(s.c_str(),ofstream:out);

    sort(vec.begin(),vec.end());
    for(int i = 0;i < vec.size(); ++i){
        //out<<vec[i].second<<" "<<vec[i].first<<endl;
        fprintf(file,"<%s>\t\t<%s>\n",vec[i].second.c_str(),vec[i].first.c_str());
        printf("<%s>\t\t<%s>\n",vec[i].second.c_str(),vec[i].first.c_str());
    }
    fclose(file);
}
void listDir(char *path)
{
    DIR              *pDir ;
    struct dirent    *ent  ;
//    int               i=0  ;
    char              childpath[1000];

    pDir=opendir(path);
    if(pDir == NULL) {
       // cout<<path<<"1 wrong"<<endl;
        return ;
    }
    memset(childpath,0,sizeof(childpath));


    while((ent=readdir(pDir))!=NULL)
    {
        if(strcmp(ent->d_name,"latex")==0) continue;
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        if(ent->d_type == DT_DIR)
        {
            sprintf(childpath,"%s/%s",path,ent->d_name);
            printf("path:%s\n",childpath);

            print(childpath);

        }
    }

}

int main(int argc,char *argv[])
{
     char link[100];
    char path[100];

    sprintf( link, "/proc/%d/exe", getpid() );

    int i = readlink( link, path, sizeof( path ) );
    path[i] = '\0';
    string s = path;
    //for(int i = 0; path[i]; ++i)
    s = s.substr(0,s.find_last_of('/'));
    s = s.substr(0,s.find_last_of('/'));
    path[s.size()] = 0;
    cout<<path<<endl;
    listDir(path);
    return 0;
}

///home/zzuzxy/test/a

/*
/home/zzuzxy/t2/ACM-template
/home/zzuzxy/下载/a
/home/zzuzxy/下载/a/a/bin
/home/zzuzxy/下载/a/a
/home/zzuzxy/下载/a/a/bin
*/
