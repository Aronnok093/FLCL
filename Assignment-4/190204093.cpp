#include<bits/stdc++.h>
using namespace std;

int main()
{
    FILE *p2,*p4;
    p2 = fopen("input.txt","r");
    p4 = fopen("output.txt","w");

    if(!p2) cout << "Error\n";
    else{
        char cur, check;
        string str;
        int line=1,cnt=0;
        vector<string> kw{"int","float","double","if","else","for","return","void"};
        vector<char> sc{'(',')','{','}',';',',','=','<','>'};
        map<int,vector<string>> M;

        while(true){
            cout << line++ << ": ";
            str = "";
            while((cur = fgetc(p2)) != EOF&&cur != '\n') str.push_back(cur);
            if(str.size()>1&&str[0]=='/'&&(str[1]=='*'||str[1]=='/')) cout << endl;
            else{
                cout << str << endl;
                string temp, checkstr;
                bool forchk = false, flag = false;
                int cnt1 = 0, ifchk = 0,cnt2 = 0;
                for(int i=0; i<str.size(); i++){
                    temp.push_back(str[i]);
                    if(temp=="for") forchk = true;
                    if(temp=="if"){
                        cnt2 = 0;
                        ifchk = 1;
                    }
                    else if(temp=="else"&&ifchk!=2) M[line-1].push_back("Unmatched 'else' at ");
                    if(str[i]==')'){
                        cnt1 = 0;
                        forchk=false;
                    }
                    if(find(kw.begin(),kw.end(),temp)!=kw.end()&&find(kw.begin(),kw.end(),checkstr)!=kw.end()&&!(checkstr=="if"||checkstr=="else")){
                        M[line-1].push_back("Back to back keyword at ");
                        checkstr = temp;
                        temp = "";
                    }
                    if(find(sc.begin(),sc.end(),str[i])!=sc.end()) checkstr = temp = "";
                    if(str[i]==' '){
                        check = '.';
                        temp.pop_back();
                        checkstr = temp;
                        temp = "";
                        continue;
                    }
                    else if(str[i]==';'&&forchk==true){
                        cnt1++;
                        if(cnt1>2)M[line-1].push_back("Duplicate token at ");
                    }
                    else if(str[i]==';'){
                        if(ifchk!=1) ifchk = 0;
                        if(ifchk==1&&cnt2==0) ifchk = 2;
                        if(check==';')M[line-1].push_back("Duplicate token at ");
                        check = ';';
                    }
                    else if(str[i]=='{'){
                        if(ifchk==1) cnt2++;
                        cnt++;
                        check = '.';
                    }
                    else if(str[i]=='}'){
                        if(ifchk!=1) ifchk = 0;
                        if(ifchk==1)cnt2--;
                        if(ifchk==1&&cnt2==0) ifchk = 2;
                        check = '.';
                        cnt--;
                        if(cnt<0){
                            M[line-1].push_back("Misplaced '}' at ");
                            cnt = 0;
                        }
                    }
                    else check = '.';
                }
            }
            if(cur==EOF) break;
        }

        cout << endl;
        for(auto it:M){
            for(int i=0; i<it.second.size(); i++){
                cout << it.second[i] << it.first << endl;
                fprintf(p4,"%s%d\n",it.second[i].c_str(),it.first);
            }
        }
    }

    return 0;
}
