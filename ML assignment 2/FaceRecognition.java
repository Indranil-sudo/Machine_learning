import java.io.*;
import java.util.*;

class FaceRecognition
{
	int nhidden=20,noutput=20,ninput=960; // nhidden stores no of nodes in hidden layer,noutput in output layer and ninput in input layer
	float x[]=new float[ninput+1];  // x stores the inputs
	float h[]=new float[nhidden+1]; // h stores the hidden layer values
	float o[]=new float[noutput]; // o stores the calculated values
	float t[]=new float[noutput]; // t stores the target output values
	float Whx[][]=new float [nhidden+1][ninput+1]; // Whx array stores the weights of all inputs from each hidden layer node
	float Woh[][]=new float[noutput][nhidden+1];
	float learningRate=0.3f;
	float momentum=0.3f;
	float maxIter=1000;//max number of epochs
	float minError=0.05f;
	float errorK[]=new float[noutput];  // errorK stores error in each node of hidden layer with respect to output layer
	float errorH[]=new float[nhidden+1];// errorH stores error in each node of input layer weight with respect to hidden layer
	float w1[][]=new float [noutput][nhidden+1];// w1 stores the previous change in weights of Woh
	float w2[][]=new float [nhidden+1][ninput+1]; // w2 stores the previous change in weights of Whx
	String names[]={"an2i","at33","boland","bpm","ch4f","cheyer","choon","danieln","glickman","karyadi","kawamura","kk49","megak","mitchell","night","phoebe","saavik","steffi","sz24","tammo"};//to store the various UserIDs possible

	void assignrandomweights()
	{
		for(int i=0;i<nhidden+1;i++)
		for(int j=0;j<ninput+1;j++)
			Whx[i][j]=((float)(Math.random()*100)-50)/100f;

		for(int i=0;i<noutput;i++)
		for(int j=0;j<nhidden+1;j++)
			Woh[i][j]=((float)(Math.random()*100)-50)/100f;
	}//function to assign random weights to Whx and Woh

	float sigmoid(float f)
	{
		float p= (float)(1/(1+Math.exp(-f)));
		return p;
	}// function to return sigmoid of the value passed

	String fileget(String s)
	{
		int i1=0;

		for(int i=s.length()-1;i>=0;i--)
			if(s.charAt(i)=='/')
			{
				i1=i+1;
				break;
			}

		String file_name="";

		for(int i=i1;i<s.length();i++)
		file_name=file_name+s.charAt(i);

		return file_name;
	}// function to return the name of the file from its path which is passed as parameter

	void TargetFunction(String s)
	{
		for(int i=0;i<noutput;i++)
			t[i]=0;

		int i1=0,j1=0;
		for(int i=s.length()-1;i>=0;i--)
			if(s.charAt(i)=='/')
			{
				i1=i+1;
				for(int j=i1;j<s.length();j++)
					if(s.charAt(j)=='_')
					{
						j1=j;
						break;
					}
				break;
			}

		String name="";

		for(int i=i1;i<j1;i++)
			name=name+s.charAt(i);

		int flag=0;

		for(int i=0;i<noutput;i++)
		if(name.equals(names[i]))
		{
			t[i]=1;
			flag=1;
			break;
		}

		if(flag==0)
		System.out.println("-------ERROR-------");//displays error if no target value is assigned

	}//function to get the target output value from the file path passed as parameter

	void forward()
	{
		float sum=0;
		h[0]=1f;//threshold
		int i=1;
		while(i<nhidden)
		{
			sum=0;
			for(int j=0;j<ninput+1;j++)
				sum=sum+Whx[i][j]*x[j];

			h[i]=sigmoid(sum);
			i++;
		}//calculates the values at hidden layer nodes

		for(i=0;i<noutput;i++)
		{
			sum=0;

			for(int j=0;j<nhidden+1;j++)
				sum=sum+Woh[i][j]*h[j];

			o[i]=sigmoid(sum);
		}// calculates the values at output layer nodes
	}// function to calculate the values at various nodes

	void calculateError()
	{
		float sum=0;
		int k=0;
		while(k<noutput)
		{
			errorK[k]=o[k]*(1-o[k])*(t[k]-o[k]);
			k++;
		}
		k=0;
		while(k<nhidden)
		{
			sum=0;

			for(int i=0;i<noutput;i++)
				sum+= Woh[i][k]*errorK[i];

			errorH[k]=h[k]*(1-h[k])*sum;
			k++;
		}
	}// function to calculate error

	void updateWeights()
	{

		float errorOH=0f,errorHX=0f;
		int i=0;
		while(i<noutput)
		{
			for(int j=0;j<nhidden+1;j++)
			{
				errorOH=learningRate*errorK[i]*h[j] - momentum*w1[i][j];
				Woh[i][j]=Woh[i][j]+errorOH;
				w1[i][j]=errorOH;// storing the value of change in weights for next iteration
			}
			i++;
		}
		i=1;
		while(i<nhidden+1)
		{
			for(int j=0;j<ninput+1;j++)
			{
				errorHX=learningRate*errorH[i]*x[j]-momentum*w2[i][j];
				Whx[i][j]=Whx[i][j]+errorHX;
				w2[i][j]=errorHX;// storing the value of change in weights for next iteration
			}
			i++;

		}
	}// function to update weights according to error in output

	float totalerror()
	{
		float overallError=0.0f;

		for(int i=0;i<noutput;i++)
		overallError=0.5f*(float)(Math.pow((t[i]-o[i]),2));


		return overallError;
	}//calculates RMS error for each input file

	void backprop()
	{
		forward();
		calculateError();
		updateWeights();

	}//method to calculate the error and backpropogate it to update weights

	public static void main(String [] args)throws IOException//main function
	{
		BufferedReader k=new BufferedReader(new InputStreamReader(System.in));

		FaceRecognition obj=new FaceRecognition();

		//Training the network starts

		obj.assignrandomweights();
		float er=100f;//to store the RMS error for one epoch
		int iter=1;// to store number of epocs performed
		while(er>obj.minError && iter<obj.maxIter)
		{
			er=0;

			FileReader fr = new FileReader("list/straighteven_train.list");//opening the training set
			BufferedReader br=new BufferedReader(fr);
			String s;


			while((s=br.readLine())!=null)//reading each instance of data set
			{
				obj.x[0]=1;// threshold

				FileInputStream fileInputStream = new FileInputStream(s.substring(1,s.length()));
			   	DataInputStream dis = new DataInputStream(fileInputStream);//reading the image file

			  	for (int c=1;c<961; c++ )
					obj.x[c] = dis.readUnsignedByte()/255.0f;//storing the pixel grayscale values

				obj.TargetFunction(s);//to obtain the target output value for the data instance
				obj.backprop();//calls the method which runs the backpropogation algorithm
				er=er+obj.totalerror();// total RMS error is updated
			}

			//System.out.println(iter+" "+er);// Uncomment this to veiw progress of gradient descent

			iter++;
		}

		//Training Network ends

		System.out.println("UserID\t\tFile Name");

		// -------TESTING begins here
		FileReader fr=new FileReader("list/straighteven_test1.list");//opening the testing set file
		BufferedReader br=new BufferedReader(fr);
		String s;
		float acc=0.0f;// stores the accuracy
		int size=0;// stores size of testing set to calculate accuracy

		while((s=br.readLine())!=null)//reads each input image of testing set
		{
			obj.x[0]=1;//threshold
			String file_name=obj.fileget(s);//stores name of the image

			FileInputStream fileInputStream = new FileInputStream(s.substring(1,s.length()));//reading the image file
		   	DataInputStream dis = new DataInputStream(fileInputStream);

		  	for (int c=1;c<961; c++ )
				obj.x[c] = dis.readUnsignedByte()/255.0f;

			obj.forward();// feed forward to get the generated output
			obj.TargetFunction(s);// to get target output

			float max=0f;
			int indexOfOutput=-1;
			int indexOfTarget=-1;

			for(int i=0;i<obj.noutput;i++)
				if(max<obj.o[i])
				{
					indexOfOutput=i;
					max=obj.o[i];

				}

			for(int i=0;i<obj.noutput;i++)
				if(obj.t[i]==1)
				indexOfTarget=i;//stores the address at which the user id of the person in image is stored in names[] array

			System.out.println(file_name+"\t\t"+obj.names[indexOfOutput]);// outputs the file name which has been classified along with the user id

			if(indexOfOutput==indexOfTarget)
			acc++;

			size++;
		}

		System.out.println("Accuracy="+((acc/size)*100)+"%");
	}
}
