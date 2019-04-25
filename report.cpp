//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<iomanip.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
{
    int rollno;
    char name[50];
    int p_marks,c_marks,m_marks,e_marks,cs_marks;
    float per;
    char grade;
    int std;
    void calculate()
    {
        per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
        if(per>=60)
            grade='A';
        else if(per>=50 && per<60)
            grade='B';
        else if(per>=33 && per<50)
            grade='C';
        else
            grade='F';
    }
public:
    void getdata()
    {
        cout<<"\nEnter The roll number of student ";
        cin>>rollno;
        cout<<"\n\nEnter The Name of student ";
        gets(name);
        cout<<"\nEnter The marks in physics out of 100 : ";
        cin>>p_marks;
        cout<<"\nEnter The marks in chemistry out of 100 : ";
        cin>>c_marks;
        cout<<"\nEnter The marks in maths out of 100 : ";
        cin>>m_marks;
        cout<<"\nEnter The marks in english out of 100 : ";
        cin>>e_marks;
        cout<<"\nEnter The marks in computer science out of 100 : ";
        cin>>cs_marks;
        calculate();
    }

    void showdata()
    {
        cout<<"\nRoll number of student : "<<rollno;
        cout<<"\nName of student : "<<name;
        cout<<"\nMarks in Physics : "<<p_marks;
        cout<<"\nMarks in Chemistry : "<<c_marks;
        cout<<"\nMarks in Maths : "<<m_marks;
        cout<<"\nMarks in English : "<<e_marks;
        cout<<"\nMarks in Computer Science :"<<cs_marks;
        cout<<"\nPercentage of student is  :"<<setprecision(2)<<per;
        cout<<"\nGrade of student is :"<<grade;
    }

    void show_tabular()
    {
        cout<<rollno<<setw(12)<<name<<setw(10)<<p_marks<<setw(3)<<c_marks<<setw(3)<<m_marks<<setw(3)<<e_marks<<setw(3)<<cs_marks<<setw(6)<<setprecision(3)<<per<<"   "<<grade<<endl;
    }

    int  retrollno()
    {
        return rollno;
    }

};         //class ends here



//***************************************************************
//      global declaration for stream object, object
//****************************************************************

fstream fp;
student st;

//***************************************************************
//      function to write in file
//****************************************************************

void write_student()
{
    fp.open("student.dat",ios::out|ios::app);
    st.getdata();
    fp.write((char*)&st,sizeof(student));
    fp.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}


//***************************************************************
//      function to read all records from file
//****************************************************************


void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}


//***************************************************************
//      function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            clrscr();
            st.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nrecord not exist";
    getch();
}


//***************************************************************
//      function to modify record of file
//****************************************************************

void modify_student()

{

    int no,found=0;

    clrscr();

    cout<<"\n\n\tTo Modify ";

    cout<<"\n\n\tPlease Enter The roll number of student";

    cin>>no;

    fp.open("student.dat",ios::in|ios::out);

    while(fp.read((char*)&st,sizeof(student)) && found==0)

    {

       if(st.retrollno()==no)

        {

            st.showdata();

            cout<<"\nPlease Enter The New Details of student"<<endl;

            st.getdata();

            int pos=-1*sizeof(st);

            fp.seekp(pos,ios::cur);

            fp.write((char*)&st,sizeof(student));

            cout<<"\n\n\t Record Updated";

            found=1;

        }
    }

    
      fp.close();

    if(found==0)

        cout<<"\n\n Record Not Found ";

    getch();
}

 

 

//***************************************************************

//      function to delete record of file

//****************************************************************

 

 

void delete_student()

{

    int no;

    clrscr();

    cout<<"\n\n\n\tDelete Record";

    cout<<"\n\nPlease Enter The roll number of student You Want To Delete";

    cin>>no;

    fp.open("student.dat",ios::in|ios::out);

    fstream fp2;

    fp2.open("Temp.dat",ios::out);

    fp.seekg(0,ios::beg);

    while(fp.read((char*)&st,sizeof(student)))

    {

        if(st.retrollno()!=no)

        {

            fp2.write((char*)&st,sizeof(student));

       }

    }

    fp2.close();

    fp.close();

    remove("student.dat");

    rename("Temp.dat","student.dat");

    cout<<"\n\n\tRecord Deleted ..";

    getch();

}
