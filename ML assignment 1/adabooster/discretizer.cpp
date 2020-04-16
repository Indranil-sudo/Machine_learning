#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

int DATASIZE;

int (*dat)[15];
vector<int> data;
int sc,ones;

bool comp(int a,int b)
{
	return dat[a][sc]<dat[b][sc];
}

void disc(int c)
{
	int i,o[2]={},mini,j,out;
	double minent=9999,ent,p,q;

	sc = c;
	sort(data.begin(),data.end(),comp);

	if(dat[data[0]][14])
		o[1]++;

	for(i=1;i<DATASIZE;i++)
	{
		if(dat[data[i]][c] != dat[data[i-1]][c])
		{
			o[0]=o[1];
			j=i-1;
		}
		if(dat[data[i]][14])
			o[1]++;

		if(dat[data[i]][14] != dat[data[i-1]][14])
		{
			p = (o[0]*1.0)/(j+1);
			q = ((ones-o[0])*1.0)/(j+1);
			p = p*log(p)+(1-p)*log(p);
			q = q*log(q)+(1-q)*log(q);
			ent =  (((j+1)*1.0)/DATASIZE)*p + (((DATASIZE-j-1)*1.0)/DATASIZE)*q;
			if(ent<minent)
			{
				minent = ent;
				out = dat[data[i]][c];
			}
		}
	}
	printf("threshold for %d column - %d\n",c,out);

	for(i=0;i<DATASIZE;i++)
	{
		if(dat[data[i]][c] >=out)
			dat[data[i]][c]=1;
		else
			dat[data[i]][c]=0;
	}
}

int main()
{
	FILE *f;
	int i,j;
	char str[100];

	printf("Enter Input size : ");
	scanf("%d",&DATASIZE);
	dat = (int (*)[15]) malloc(sizeof(int)*(15)*DATASIZE);
	
	printf("Enter Input File to disctretize : ");
	scanf("%s",str);
	f = fopen(str,"r");
	for(i=0;i<DATASIZE;i++)
	{
		for(j=0;j<15;j++)
		{
			fscanf(f,"%d",&dat[i][j]);
		}
		data.push_back(i);
	}
	fclose(f);

	for(i=0,ones=0;i<DATASIZE;i++)
	{
		ones += dat[i][14];
	}

	disc(0);
	disc(2);
	disc(4);
	disc(10);
	disc(11);
	disc(12);

	printf("Enter Output File name : ");
	scanf("%s",str);
	f = fopen(str,"w");
	for(i=0;i<DATASIZE;i++)
	{
		for(j=0;j<15;j++)
		{
			fprintf(f,"%d ",dat[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}