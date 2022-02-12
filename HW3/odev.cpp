#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
void read_file();//read data from file
void free_string(string readed[],int number);//make free the array
int check_ref(string readed[],int number,string line);//checking reflexive
int check_smy(string readed[],int number,string line);//checking Symmetric
int check_antsmy(string readed[],int number,string line);//checking antisymmetric
int check_tra(string readed[],int number,string line);//checking transitive
void delete_ref_tran(string readed[],int number);
int main(){
    read_file();
    return 0;
}
void free_string(string readed[],int number){
    for (int i = 0; i < 20; i++)
    {
        readed[i]=" ";//free array
    }
}
void read_file(){
    char char1;
    string line,line1,line2,freeline;
    string readed[30];
    int number,check1,check2,check3,check4;
    int control5=0,control6=0;
    int length;
    bool control2=false;
    bool control3=false,control7=false;
    ifstream myreadfile;
    ofstream mywritefile;
    myreadfile.open("input.txt");//input file
    mywritefile.open("output.txt");//output file
    while(!myreadfile.eof()){//to reach end of file
        myreadfile>>number;//read the number of element
        getline(myreadfile,freeline);//read freeline to pass the other line
        getline(myreadfile,line1);//read the elements
        mywritefile<<number<<endl;//write the number of elements to the output file
        length=line1.length();
        for (int i = 0; i < number; i++)
        {
            getline(myreadfile,line2);//read double element
            readed[i]=line2;//record the array
        }
        for (int j = 0; j < number; ++j)
        {
        	control2=false;
        	control3=false;
        	control7=false;
        	for (int k = 0; k < length; k=k+2)
        	{
        		if (readed[j][0]==line1[k])//to find the first element in set elements
        		{
        			control2=true;
        		}
        		if (readed[j][2]==line1[k])
        		{
        			control3=true;
        		}
        	}
        	if(control2!=true || control3!=true){//if there is incompatible elements i did not check it.
        		control7=true;
        		break;
        	}
        }
        if (control7==true)
        {
        	mywritefile<<endl<<"There is a wrong element here .it doesnt match the set elements so i did not check it"<<endl;
        	continue;
        }
        mywritefile<<"POSET:";//to pass the other line
        check1=check_ref(readed,number,line1);//checking the reflexive
        number=check1;
        check2=check_smy(readed,number,line1);
        check3=check_antsmy(readed,number,line1);
        check4=check_tra(readed,number,line1);
        number=check4;
        for (int i = 0; i < number; i++)
        {
            if(readed[i]!="")
                mywritefile<<"("<<readed[i]<<")";//write the double element
        }
        mywritefile<<endl;
        delete_ref_tran(readed,number);
        mywritefile<<"HESSE:";
        for (int i = 0; i < number; i++)
        {
            if(readed[i]!="")
                mywritefile<<"("<<readed[i]<<")";//write the double element
        }
        mywritefile<<endl;
        free_string(readed,number);//when we reach the end of a one set we pass another because of this we have to free the array
    }
    mywritefile.close();//close output file
    myreadfile.close();//close input file
}
int check_ref(string readed[],int number,string line){
	int number1=0,f=0,t=0;
	char array[20];
    string str="";
	for(int j = 0; j < 20; j++)
	{
		if(line[j]!=',' && line[j]!='\0'){//to avoid the take ',' or '\0' to the array
			array[t]=line[j];//to reach each element 'a' 'b' or '1' 
			t++;
      		number1++;//to control the each element is avaible
		}
	    else if(line[j]=='\0'){//to reach the end of the elements
	      break;
	    }
	}
    for (int i = 0; i < number; ++i)
    {
    	for (int k = 0; k < number; ++k)
    	{
    	    if(array[f]==readed[k][0] && array[f]==readed[k][2]){//check the reflexive
    	   		f++;
    	   	}
    	   	if(f==number1){
    	   		break;
    	   	}
    	}
        if(f==number1){
            break;
        }
        else{
            str=str+array[f]+','+array[f];//Add reflexive if not poset
            readed[number]=str;
            str="";
            f++;
            number++;
        }
    }
	return number;
}
int check_smy(string readed[],int number,string line){
	int number1=0,number2=0,control1=0;
    string str="";
    int array[20];
    int k=0,l=0,m=0;
    for (int i = 0; i < number; ++i)
    {
    	if (readed[i][0]!=readed[i][2])//to avoid to take examples like that(a,a)
    	{
    		control1=0;
    		number1=i;
    		number2=i;
    		for (int j=0; j < number; j++)
    		{
    			if(readed[number2][0]==readed[j][2] && readed[number2][2]==readed[j][0]){//check syymetric
    				control1=1;
                    array[l]=number2;
                    l++;
    			}
    		}
    	}
    }
    for (int i = 0; i < l; ++i)
    {
        for (int j = 0; j < l; ++j)
        {
            if (readed[i][0]!=readed[i][2]){
                if (readed[array[i]][0]==readed[array[j]][2] && readed[array[i]][2]==readed[array[j]][0])
                {
                    array[j]=i;
                }
            }
        }
    }
    for (int i = 0; i < l; i+=2)
    {
        str="";
        readed[array[i]]=str;//to make antisyymetric
    }
    return -1;
}
int check_antsmy(string readed[],int number,string line){
    int number1=0,number2=0,control1=0,control=0;
    //-----------------------------------------------
    for (int i = 0; i < number; ++i)
    {
	    if (readed[i][0]!=readed[i][2])
	    {
	        control1=0;
	        number1=i;
	        number2=i;
	        for (int j=0; j < number; j++)
	        {
	          if(readed[number2][0]==readed[j][2] && readed[number2][2]==readed[j][0]){
	            control1=1; 
	          }
	        }
	        if(control1==1){
	          return number2;
	        }
	    }
	    else{
	    	control=1;
	    }
    }
    if(control==1){
    	return -1;
    }
    //-------------------------until here we check syymetric
    number1=0,number2=0,control1=0;
    for (int k = 0; k < number; ++k)
    {
	    if (readed[k][0]!=readed[k][2])
	    {
	        control1=0;
	        number1=k;
	        number2=k;
	        for (int j=0; j < number; j++)
	        {
	          if(readed[number2][0]==readed[j][2] && readed[number2][2]==readed[j][0]){
	            control1=1; 
	          }
	        }
	        if(control1==0){//check the antisyymetric
	          return -1;
	        }
	    }
    }
}
int check_tra(string readed[],int number,string line){
    int number4=0,number2=0,number3=0,control1=0;
    string str="";
    string array[20];
    int l=0;
    for (int i = 0; i < number; ++i){
        if(readed[i][0]!=readed[i][2]&&readed[i]!=""){
            number2=i;
            for (int j=0; j< number; j++){
                if(readed[i][2]==readed[j][0]){//compare the other elements in array
                    number3=j;
                    for (int k=0; k < number; k++){
                   	    control1=0;
                        if(readed[number2][0]==readed[k][0] && readed[number3][2]==readed[k][2]){
                            number4=k;
                            control1=1;
                            break;
                        }
                    }
                    if(control1==0){
                        str=str+readed[number2][0]+','+readed[number3][2];
                        array[l]=str;
                        str="";
                        l++;
                    }
                }
            }  
        }
    }
    for (int i = 0; i < l; ++i)
    {
        readed[number]=array[i];//if no poset we add transitive element to make poset
        number++;
    }
    return number;
}
void delete_ref_tran(string readed[],int number){
    int number2,number3;
    int control1=0;
    string str="";
    for (int i = 0; i < number; ++i)
    {
        if (readed[i][0]==readed[i][2])
        {
            readed[i]=str;//delete reflexive
        }
    }
    for (int i = 0; i < number; ++i){
        if(readed[i][0]!=readed[i][2]&&readed[i]!=""){
            number2=i;
            for (int j=0; j< number; j++){
                if(readed[i][2]==readed[j][0]){//compare the other elements in array
                    number3=j;
                    for (int k=0; k < number; k++){
                        control1=0;
                        if(readed[number2][0]==readed[k][0] && readed[number3][2]==readed[k][2]){
                            control1=1;
                            readed[k]=str;//delete transtive 
                            break;
                        }
                    }
                }
            }  
        }
    }
}
