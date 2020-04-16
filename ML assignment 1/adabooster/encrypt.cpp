#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
using namespace std;

int enc1(string a){
    if(a==" ?")
    {
        return 100;
    }
                int x;
                stringstream convert(a);
                convert>>x;
                // x= x/10;
                return x;
}
int enc3(string a){
    if(a==" ?")
    {
        return 101;
    }
                int x;
                // a.erase(remove(a.begin(), a.end(), ' '), a.end());
                stringstream convert(a);
                convert>>x;
                // x= x/1000;
                // stringstream s;
                // s<<x;
                // string b=s.str();
                return x;
}
int enc5(string a){
    if(a==" ?")
        return 102;
                int x;
                stringstream convert(a);
                convert>>x;
                return x;
}
int enc11(string a){
    if(a==" ?")
    {
        return 103;
    }
    int x;
    stringstream convert(a);
    convert>>x;
    return x;
}
int enc12(string a){
    if(a==" ?")
    {
        return 104;
    }
    int x;
    stringstream convert(a);
    convert>>x;
    return x;
}
int enc13(string a){
    if(a==" ?")
    {
        return 107;
    }
                int x;
                stringstream convert(a);
                convert>>x;
                return x;
}

int recode(string a, int y){
    int b=99999;
    if(a==" ?")
    {
        switch(y)
        {
            case 2:
                return 1;
            case 4:
                return 4;
            case 6:
                return 1;
            case 7:
                return 5;
            case 8:
                return 3;
            case 9:
                return 1;
            case 10:
                return 2;
            case 14:
                return 1;
            default:
                return 1111111;
        }
    }
if(a==" Private")
    b=1;
if(a==" Self-emp-not-inc")
    b=2;
if(a==" Self-emp-inc")
    b=3;
if(a==" Federal-gov")
    b=4;
if(a==" Local-gov")
    b=5;
if(a==" State-gov")
    b=6;
if(a==" Without-pay")
    b=7;
if(a==" Never-worked")
    b=8;

if(a==" Bachelors")
    b=1;
if(a==" Some-college")
    b=2;
if(a==" 11th")
    b=3;
if(a==" HS-grad")
    b=4;
if(a==" Prof-school")
    b=5;
if(a==" Assoc-acdm")
    b=6;
if(a==" Assoc-voc")
    b=7;
if(a==" 9th")
    b=8;
if(a==" 7th-8th")
    b=9;
if(a==" 12th")
    b=10;
if(a==" Masters")
    b=11;
if(a==" 1st-4th")
    b=12;
if(a==" 10th")
    b=13;
if(a==" Doctorate")
    b=14;
if(a==" 5th-6th")
    b=15;
if(a==" Preschool")
    b=16;

if(a==" Married-civ-spouse")
    b=1;
if(a==" Divorced")
    b=2;
if(a==" Never-married")
    b=3;
if(a==" Separated")
    b=4;
if(a==" Widowed")
    b=5;
if(a==" Married-spouse-absent")
    b=6;
if(a==" Married-AF-spouse")
    b=7;

if(a==" Tech-support")
    b=1;
if(a==" Craft-repair")
    b=2;
if(a==" Other-service")
    b=3;
if(a==" Sales")
    b=4;
if(a==" Exec-managerial")
    b=5;
if(a==" Prof-specialty")
    b=6;
if(a==" Handlers-cleaners")
    b=7;
if(a==" Machine-op-inspct")
    b=8;
if(a==" Adm-clerical")
    b=9;
if(a==" Farming-fishing")
    b=10;
if(a==" Transport-moving")
    b=11;
if(a==" Priv-house-serv")
    b=12;
if(a==" Protective-serv")
    b=13;
if(a==" Armed-Forces")
    b=14;

if(a==" Wife")
    b=1;
if(a==" Own-child")
    b=2;
if(a==" Husband")
    b=3;
if(a==" Not-in-family")
    b=4;
if(a==" Other-relative")
    b=5;
if(a==" Unmarried")
    b=6;

if(a==" White")
    b=1;
if(a==" Asian-Pac-Islander")
    b=2;
if(a==" Amer-Indian-Eskimo")
    b=3;
if(a==" Other")
    b=4;
if(a==" Black")
    b=5;

if(a==" Female")
    b=1;
if(a==" Male")
    b=2;

if(a==" United-States")
    b=1;
if(a==" Cambodia")
    b=2;
if(a==" England")
    b=3;
if(a==" Puerto-Rico")
    b=4;
if(a==" Canada")
    b=5;
if(a==" Germany")
    b=6;
if(a==" Outlying-US(Guam-USVI-etc)")
    b=7;
if(a==" India")
    b=8;
if(a==" Japan")
    b=9;
if(a==" Greece")
    b=1;
if(a==" South")
    b=11;
if(a==" China")
    b=12;
if(a==" Cuba")
    b=13;
if(a==" Iran")
    b=14;
if(a==" Honduras")
    b=15;
if(a==" Philippines")
    b=16;
if(a==" Italy")
    b=17;
if(a==" Poland")
    b=18;
if(a==" Jamaica")
    b=19;
if(a==" Vietnam")
    b=20;
if(a== " Mexico")
    b=21;
if(a==" Portugal")
    b=22;
if(a==" Ireland")
    b=23;
if(a==" France")
    b=24;
if(a==" Dominican-Republic")
    b=25;
if(a==" Laos")
    b=26;
if(a==" Ecuador")
    b=27;
if(a==" Taiwan")
    b=28;
if(a==" Haiti")
    b=29;
if(a==" Columbia")
    b=30;
if(a==" Hungary")
    b=31;
if(a==" Guatemala")
    b=32;
if(a==" Nicaragua")
    b=33;
if(a==" Scotland")
    b=34;
if(a==" Thailand")
    b=35;
if(a==" Yugoslavia")
    b=36;
if(a==" El-Salvador")
    b=37;
if(a==" Trinadad&Tobago")
    b=38;
if(a==" Peru")
    b=39;
if(a==" Hong")
    b=40;
if(a==" Holand-Netherlands")
    b=41;

if(a==" <=50K")
    b=1;
if(a==" >50K")
    b=2;

return b;
}
void readCSV(istream &input, vector< vector<string> > &output)
{
   string csvLine;
    while( getline(input, csvLine) )
    {
            istringstream csvStream(csvLine);
           vector<string> csvColumn;
            string csvElement;

            while( getline(csvStream, csvElement, ',') )
            {
                    csvColumn.push_back(csvElement);
            }
            output.push_back(csvColumn);
    }
}

int main()
{
    ofstream myfile;
    string a,s;
    int b;
    int y;
    char str[100];
    printf("Enter input file name : ");
    cin>>s;
    fstream file(s, ios::in);
    printf("Enter output file name : ");
    cin>>s;
    myfile.open (s);

    if(!file.is_open())
    {
           cout << "File not found!\n";
            return 1;
    }

    typedef vector< vector<string> > csvVector;//array of arrays
    csvVector csvData;
    readCSV(file, csvData);
    int k=0,l;
     for(csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i,k++)
    {
        y=0;
        l=0;
        for(vector<string>::iterator j = i->begin(); j != i->end(); ++j,l++)
        {
            a= *j;
            y++;
            if(y==1)
            {
                b=enc1(a);
            }else if(y==3)
            {
                b=enc3(a);
            }else if(y==5)
            {
                b=enc5(a);
            }
            else if(y==11)
            {
                b=enc11(a);
            }
            else if(y==12)
            {
                b=enc12(a);
            }
            else if(y==13)
            {
                b=enc13(a);
            }
            else
                b=recode(a,y)-1;

                myfile <<b<<" ";
        }

        myfile <<"\n";
    }
    myfile.close();
}

