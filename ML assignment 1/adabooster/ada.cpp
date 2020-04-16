#include <vector>
#include <cmath>
#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <time.h>
#include <iostream>

using namespace std;
double wt[32561];
const int NUM_FIN=5;
double wt_tre[NUM_FIN];
int NUMATTR = 14;
int DATASIZE = 32561;
int TDATASIZE = 16281;
const int NUMTREES = 50;
int picked[NUMTREES]={0};
int id3_fin[NUM_FIN];
int RDATASIZE = 10000;
int RNUMATTR = 5;

int (*dat)[15];
int ranges[15]={1,7,1,15,1,6,13,5,4,1,1,1,1,40,1};

const int numattr = NUMATTR;
int sc;

bool comp(int a,int b)
{
	return dat[a][sc]<dat[b][sc];
}

class Node
{
public:
	int attr;
	bool value;
	vector<Node*> childs;
	Node(int a,bool v,int r)
	{
		attr = a;
		value = v;
		childs.insert(childs.begin(),r,0);
	}
};

class ID3
{
private:
	vector<int> data;
	vector<bool> vis;
	int dataSize, mismatches, numattr,tdataSize;
	Node *root;

	double entLoss(int s, int e,int c)
	{
		int j,numvalues,k;
		double ent,prob,loss;

		numvalues = ranges[c]+1;
		int t[numvalues] ={}, f[numvalues]={};
		for(j=s;j<=e;j++)
		{
			k = data[j];
			t[dat[k][c]] += dat[k][numattr];
			f[dat[k][c]] += !dat[k][numattr];
		}

		for(loss=0,j=0;j<numvalues;j++)
		{
			if(t[j]!=0 && f[j] !=0)
			{
				prob = (t[j]*1.0)/(t[j]+f[j]);
				ent = -(prob*log(prob)+(1-prob)*log(1-prob));
				loss += (ent*((t[j]+f[j]))/(e-s+1));
			}
		}

		return loss;
	}

	Node* train(int s, int e)
	{
		int minc, i, j, k, p, c, cnt, numvalues,ju;
		double min, loss;

		min = 9999;

		for(i=s, cnt=0; i<=e; i++)
		{
			k = data[i];
			cnt = cnt+dat[k][numattr];
		}

		if(cnt==0)
		{
			return new Node(-1,false,0);
		}
		else if(cnt==e-s+1)
		{
			return new Node(-1,true,0);
		}

		for(i=0,j=0;i<numattr;i++)
		{
			if(vis[i])
				continue;
			j=1;
			loss = entLoss(s,e,i);
			if(loss<min)
			{
				min = loss;
				minc = i;
			}
		}

		if(j==0)
		{

			if(cnt>((e-s+1)/2))
				return new Node(-1,true,0);
			else
				return new Node(-1,false,0);
		}

		Node &n = *(new Node(minc,true,ranges[minc]+1));

		sc = minc;
		sort(data.begin()+s,data.begin()+e+1,comp);

		vis[minc]  = true;
		numvalues = ranges[minc]+1;
		k = s;
		p = dat[data[s]][minc];

		for(j=s+1;j<=e;j++)
		{
			i = data[j];
			c = dat[i][minc];
			if(p != c)
			{
				n.childs[p]=train(k,j-1);
				k = j;
			}
			p = c;
		}

		n.childs[p]=train(k,j-1);

		for(j=0;j<numvalues;j++)
		{
			if(n.childs[j]==0)
			{
				if(cnt>((e-s+1)/2))
					n.childs[j] = new Node(-1,true,0);
				else
					n.childs[j] = new Node(-1,false,0);
			}
		}
		vis[minc] = false;

		return &n;
	}

	void print_tree(Node *c)
	{
		int i=0;
		Node *n;
		for(Node*n:c->childs)
		{
			if(n->attr ==-1)
			{
				if((n->value)==true)
					printf("attribute-%d value-%d child-true\n",c->attr,i);
				else
					printf("attribute-%d value-%d child-false\n",c->attr,i);
			}
			else
			{
				printf("attribute-%d value-%d child-%d\n",c->attr,i,n->attr);
				print_tree(n);
			}
			i++;
		}
	}

public:
	ID3(int d,int a,int t,int rd,int rn)
	{
		numattr = a;
		tdataSize = t;

		srand(clock());
		set<int> st;

		while(st.size()<rd)
		{
			st.insert(rand()%d);
		}
		for(int i: st)
			data.push_back(i);
		dataSize = data.size();

		srand(clock());
		st.clear();
		for(int i=0;i<a;i++)
			vis.push_back(true);
		while(st.size()<rn)
		{
			st.insert(rand()%a);
		}
		for(int i: st)
			vis[i] = false;
	}

	ID3(int d,int a,int t)
	{
		int i;
		for(i=0;i<d;i++)
			data.push_back(i);
		for(i=0;i<a;i++)
			vis.push_back(false);
		dataSize = d;
		numattr = a;
		tdataSize = t;
	}

	void print_data()
	{
		int i,j,k;
		printf("Input - Ouptut\n");
		for(i=0;i<dataSize;i++)
		{
			k = data[i];
			for(j=0;j<=numattr;j++)
				printf("%d ",dat[k][j]);
			printf("\n");
		}
	}

	void train()
	{
		root = train(0,dataSize-1);
	}

	void print_tree()
	{
		print_tree(root);
	}

	bool evaluate(int q)
	{
		Node *n = root;
		while(n->attr!=-1)
			n = n->childs[dat[q][n->attr]];
		return n->value;
	}
	double treErr()// weighted error of tree
	{
		int i, k;
		double cnt=0.0;
		mismatches = 0;
		for(i=0;i<DATASIZE;i++)
		{
			if(dat[i][numattr] != evaluate(i))
				cnt+=wt[i];
		}
		return cnt;
	}
	void update(double alpha)
	{
		int i, k;
		for(i=0;i<DATASIZE;i++)
		{
			if(dat[i][numattr] != evaluate(i))
			{
				wt[i]=wt[i]*exp(alpha);// weight of misclassfied instances are increased
			}
			else
			{
				wt[i]=wt[i]*exp(-alpha);// weight of correctly classfied instances are decreased
			}
		}
	}
	void validate()
	{
		int i, cnt=0;
		mismatches = 0;
		for(i=0;i<tdataSize;i++)
		{
			if(dat[i][numattr] != evaluate(i))
				cnt++;
		}
		mismatches = cnt;
		printf("Mismatched %d, Test Data size %d, Attributes %d, Accuracy %f%%\n",mismatches,tdataSize,numattr, (1-((double)mismatches/tdataSize))*100);
	}

};
void norm()
{int i,sum=0;
	for(i=0;i<NUM_FIN;i++)
	{
		sum+=wt_tre[i];
	}
	for(i=0;i<NUM_FIN;i++)
	{
		wt_tre[i]/=sum;
	}
}
int loadAllData(int src)
{
	int i,j;
	FILE *f ;
	if(src==1)
		f = fopen("adultdisc.data","r");
	else if(src==2)
		f = fopen("adultdisc.test","r");
	else
		return 0;
	for(i=0;i<DATASIZE;i++)
	{
		for(j=0;j<15;j++)
		{
			fscanf(f,"%d",&dat[i][j]);
		}
	}
	fclose(f);
}
int main()
{
	bool o,t;
	int mismatches,i,j,k,best_k;
	double sum,cur_min,min,cnt;
	dat = (int (*)[15]) malloc(sizeof(int)*(15)*DATASIZE);
	loadAllData(1);

	clock_t start = clock();

	ID3 *id3[NUMTREES];

	for(i=0;i<NUMTREES;i++)
	{
		id3[i] = new ID3(DATASIZE,NUMATTR,TDATASIZE,RDATASIZE,RNUMATTR);
		id3[i]->train();
	}
	
	//adaboosting
	for(k=0;k<32561;k++)
	{
		wt[k]=1.0/32561;// weights of instance initialized to 1/N ,N=no of instances
	}
	for(k=0;k<NUM_FIN;k++)          // pick a set of classifiers from the random forest
	{
		min=32561.0;
		cur_min=0.0;
		sum=0.0;
		for(i=0;i<DATASIZE;i++)
		{
			sum+=wt[i];             //sum of weights of all instances
		}
		for(i=0;i<NUMTREES;i++)              // pick tree that minimizes sum of weighted missclassification
		{
			if(picked[i]==0)
			{
				cur_min=id3[i]->treErr();
				if(cur_min<min)
				{
					best_k=i;
					min=cur_min;
				}
			}
		}
		picked[best_k]=1;
		id3_fin[k]=best_k;
		wt_tre[k]=0.5*log((sum-min)/min);// weight of picked tree
		id3[best_k]->update(wt_tre[k]);// update instace weights
	}
	norm();
	clock_t end = clock();
	printf("Learning time - %f seconds\n",((double)(end - start))/CLOCKS_PER_SEC);
	loadAllData(2);
	mismatches = 0;
	for(i=0;i<TDATASIZE;i++)
	{
		for(j=0, cnt=0;j<NUM_FIN;j++)
		{
			k=id3_fin[j];
			if(id3[k]->evaluate(i))
			{
				cnt+=wt_tre[j];
			}
			else
			{
				cnt-=wt_tre[j];
			}
		}
		// printf("ones %d zeros %d\n",cnt,NUMTREES-cnt);
		o = (cnt>0)?true:false;
		t = dat[i][NUMATTR]?true:false;
		if(o^t)
		{
			mismatches++;
		}
	}
	double err = (double)(mismatches)/TDATASIZE;
	printf("Trees %d, Attributes %d, Datasize %d, Accuracy %f%%\n",NUMTREES,RNUMATTR,RDATASIZE,(1-err)*100);
}
