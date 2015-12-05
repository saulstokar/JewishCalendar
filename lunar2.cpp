#include <stdio.h>
#include <iostream>
//#include <fstream.h>
//#include <iomanip.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include "MoladNumber.h"
#include "rosh_hashana.h"
#include <fstream>
using namespace std;

void RoshHashana::set_molad(int show_reason){

  Number cycle_length = 19;

  // calculate number of months in preceeding years
  Number full_cycles = (its_hebrew_year-1)/cycle_length; // integer division 

  Number remainder = (its_hebrew_year-1) - full_cycles * cycle_length;

  Number extra_months=0;

  int months_in_year[20];  // dummy value in entry 0 - not used
  months_in_year[0] = 0; 
  months_in_year[1] =  12;
  months_in_year[2] = 12;
  months_in_year[3] = 13;
  months_in_year[4] = 12;
  months_in_year[5] = 12;
  months_in_year[6] = 13;
  months_in_year[7] = 12;
  months_in_year[8] = 13;
  months_in_year[9] = 12;
  months_in_year[10] = 12;
  months_in_year[11] = 13;
  months_in_year[12] = 12;
  months_in_year[13] = 12;
  months_in_year[14] = 13;
  months_in_year[15] = 12;
  months_in_year[16] = 12;
  months_in_year[17] = 13;
  months_in_year[18] = 12;
  months_in_year[19] = 13;
  
  for (Number year_in_cycle=1; year_in_cycle <=remainder; year_in_cycle++){
    extra_months=extra_months + months_in_year[year_in_cycle];
  }

  // Number of months in a full cycle of 19 years (should equal 235!)
  Number months_in_cycle = 0;
  for (int i_year=1; i_year <=cycle_length; i_year++)
    months_in_cycle = months_in_cycle + months_in_year[i_year];
					     
  Number months = full_cycles * months_in_cycle + extra_months;

  MoladNumber molad_tohu(2,5,204); 
  MoladNumber lunar_month(29,12,793);
//  MoladNumber lunar_month_fixed(29,12,793);

//  ThisYearsMolad = lunar_month * months;
  ThisYearsMolad = lunar_month;
  ThisYearsMolad = ThisYearsMolad*months;
  ThisYearsMolad = ThisYearsMolad + molad_tohu;

  if(show_reason){
	  char fileName[30];
	sprintf(&fileName[0],"%d",its_hebrew_year);
	strcat(fileName,"Details");
	strcat(fileName,".dat");
	std::ofstream out(fileName);
	out << "Hebrew year " << its_hebrew_year << endl <<
	"Note: "<<its_hebrew_year<<" = "<< its_hebrew_year/19 << " * 19 + "<<its_hebrew_year%19<<endl<<
	"  => No. full cycles: "<< full_cycles << endl <<
	"  => No. remaining years: "<<remainder << endl <<
	"No. months per cycle: " << months_in_cycle  << "  No. extra months: " << extra_months << endl <<
	"  => Total no. of months since ToHu: " << months << " (" << full_cycles << " * " << months_in_cycle << " + " << extra_months << ") "<< endl <<
	"Molad_tohu: " << molad_tohu.Days() <<"." << molad_tohu.Hours() << "." << molad_tohu.Halakim()<< " (days.hours.chalakim)" << endl<<
	"Lunar_month: " << lunar_month.Days() <<"." << lunar_month.Hours() << "." << lunar_month.Halakim()<< endl <<
	"  => Molad for " << its_hebrew_year <<": "<<ThisYearsMolad.Days() << "." << ThisYearsMolad.Hours() << "." << ThisYearsMolad.Halakim() <<
	" ( (2.5.204) + " << months << " * (29.12.793) ) " << endl <<
	"Note: " << ThisYearsMolad.Days() << " = " << ThisYearsMolad.Days()/7 << " * 7 + " 
		<< ThisYearsMolad.Days()%7 << endl; 
  }


}

RoshHashana::RoshHashana(Number hebrew_year, int show_reason=0){
  
 its_hebrew_year = hebrew_year;

 set_molad(show_reason);

 rosh_hashana = ThisYearsMolad.WeekDays() ;
 rosh_hashana_date = ThisYearsMolad.Days();

 if(show_reason) cout << " Initial setting: Rosh Hashana is on: " << rosh_hashana << endl;

 // for convenience, define four local variables that describe molad
 its_molad_full_day = ThisYearsMolad.Days();
 its_molad_day = ThisYearsMolad.WeekDays();
 its_molad_hour = ThisYearsMolad.Hours();
 its_molad_helek = ThisYearsMolad.Halakim();

  // check dehiyot, one at a time
 strcpy (its_reason, "None");  

 adu = (its_molad_day == 1 || its_molad_day == 4 || its_molad_day == 6);

 year_in_cycle = its_hebrew_year % 19;

 leap_year = year_in_cycle == 3 || year_in_cycle == 6 || year_in_cycle == 8 || 
   year_in_cycle == 11 || year_in_cycle == 14 || year_in_cycle == 17 
   || year_in_cycle == 0;

 post_leap_year=year_in_cycle == 1 || year_in_cycle == 4 || year_in_cycle == 7 || 
   year_in_cycle == 9 || year_in_cycle == 12 || year_in_cycle == 15 || year_in_cycle == 18;

 Rc = Dehiyat_MoladZakein(show_reason);

 if(!Rc) Rc = Dehiyat_GaTaRad(show_reason);

 if(!Rc) Rc = Dehiyat_BeTuTeKaPot(show_reason);

 if(!Rc) Rc = Dehiyat_Adu(show_reason);

}

int RoshHashana::Dehiyat_MoladZakein(int show_reason){
 
  int done=0;

  int MoladZakein = (its_molad_hour >= 18 && !adu);
 
  if( MoladZakein){
    rosh_hashana = rosh_hashana  + 1;
    rosh_hashana = rosh_hashana  % 7;
    rosh_hashana_date = rosh_hashana_date + 1;

    adu = rosh_hashana == 1 || rosh_hashana == 4 || rosh_hashana == 6;
    if (adu){
      rosh_hashana = rosh_hashana  + 1;
      rosh_hashana = rosh_hashana  % 7;
      rosh_hashana_date = rosh_hashana_date + 1;
      if(show_reason) cout <<  "Using Molad Zakein & ADU dehiyya" << endl;     
      strcpy (its_reason,"Molad Zakein & ADU"); 
    } else{
      if(show_reason) cout <<  "Using Molad Zakein dehiyya" << endl;
      strcpy (its_reason,"Molad Zakein"); 
    }

    done = 1;
  }

  return done;

}

int RoshHashana::Dehiyat_GaTaRad(int show_reason){
  int done=0;


  int GaTaRad = its_molad_day == 3 && !leap_year && 
    ( (its_molad_hour == 9 && its_molad_helek >= 204) || (its_molad_hour > 9));

  if(GaTaRad){
    if(show_reason) cout << "Using GaTaRad dehiyya" << endl;
    strcpy(its_reason,"GaTaRad");
    rosh_hashana = 5; 
    rosh_hashana_date = rosh_hashana_date + 2;
    done = 1;
  }

  return done;
}

int RoshHashana::Dehiyat_BeTuTeKaPot(int show_reason){
  int done=0;
 
  int BeTuTeKaPot = post_leap_year && its_molad_day == 2 && 
    ( (its_molad_hour == 15 && its_molad_helek >= 589) || (its_molad_hour > 15));
 
  if(BeTuTeKaPot){
    if(show_reason) cout << "Using BeTuTeKaPot dehiyya" << endl;
    strcpy(its_reason,"BeTuTeKaPot");
    rosh_hashana = 3;
//    rosh_hashana_date = rosh_hashana_date + 2;
    rosh_hashana_date = rosh_hashana_date + 1;
    done = 1;
  }
  return done;
}

int RoshHashana::Dehiyat_Adu(int show_reason){
  int done=0;
  if(adu){
    if(show_reason) cout << " Using ADU dehiyya" << endl;
    strcpy(its_reason,"ADU");
    rosh_hashana = rosh_hashana  + 1;
    rosh_hashana = rosh_hashana  % 7;
    rosh_hashana_date = rosh_hashana_date + 1;
    done = 1;
  }
  return done;
}


Number RoshHashana:: full_day(){
  return rosh_hashana_date;
}
Number RoshHashana:: week_day(){
  return rosh_hashana;
}

Number RoshHashana::molad_full_day(){
  return ThisYearsMolad.Days();
}

Number RoshHashana::molad_day(){
return ThisYearsMolad.WeekDays();
}

Number RoshHashana::molad_hour(){
return ThisYearsMolad.Hours();
}

Number RoshHashana::molad_helek(){
return ThisYearsMolad.Halakim();
}

void RoshHashana::PrintSummary(){


  cout << "Data for hebrew year " << its_hebrew_year << endl;
  cout << " Molad: " <<
    "   day: " << its_molad_day << 
    "   hour:     " << its_molad_hour <<
    "   helek:    " << its_molad_helek << endl;
  //  cout << "   full day: " << its_molad_full_day << endl;

  cout << " Reason for dehiyya: "  << its_reason << endl;
  char day_name[10];
    switch (rosh_hashana){
    case 0: 
      strcpy(day_name,"Saturday");
      break;
    case 1: 
      strcpy(day_name,"Sunday");
      break;
    case 2: 
      strcpy(day_name,"Monday");
      break;
    case 3: 
      strcpy(day_name,"Tuesday");
      break;
    case 4: 
      strcpy(day_name,"Wednesday");
      break;
    case 5: 
      strcpy(day_name,"Thursday");
      break;
    case 6: 
      strcpy(day_name,"Friday");
      break;
    default:
      strcpy(day_name,"NoName");
      break;
    }
    cout << " Rosh Hashana day: " << rosh_hashana << "  (" << day_name << ", " <<rosh_hashana_date 
	 << ")" << endl << endl;
}
void RoshHashana::PrintSummaryToFile(Number its_hebrew_year){

	char fileName[30];
	sprintf(&fileName[0],"%d",its_hebrew_year);
	strcat(fileName,".dat");
	ofstream out(fileName);

  out << "Data for hebrew year " << its_hebrew_year << endl;
  out << " Molad: " <<
    "   day: " << its_molad_day << 
    "   hour:     " << its_molad_hour <<
    "   helek:    " << its_molad_helek << endl;
  //  cout << "   full day: " << its_molad_full_day << endl;

  out << " Reason for dehiyya: "  << its_reason << endl;
  char day_name[10];
    switch (rosh_hashana){
    case 0: 
      strcpy(day_name,"Saturday");
      break;
    case 1: 
      strcpy(day_name,"Sunday");
      break;
    case 2: 
      strcpy(day_name,"Monday");
      break;
    case 3: 
      strcpy(day_name,"Tuesday");
      break;
    case 4: 
      strcpy(day_name,"Wednesday");
      break;
    case 5: 
      strcpy(day_name,"Thursday");
      break;
    case 6: 
      strcpy(day_name,"Friday");
      break;
    default:
      strcpy(day_name,"NoName");
      break;
    }
    out << " Rosh Hashana day: " << rosh_hashana << "  (" << day_name << ", " <<rosh_hashana_date 
	 << ")" << endl << endl;

	cout << " Data stored in file " << fileName << endl << endl; 

}
MoladNumber::MoladNumber(){
  ptr_to_data = new long int[3];
  *ptr_to_data = 0;
  *(ptr_to_data + 1) = 0;
  *(ptr_to_data + 2) = 0;

}

MoladNumber::MoladNumber(const MoladNumber& molad){
  ptr_to_data = new long int[3];
  copy(molad);
}

void MoladNumber:: copy(const MoladNumber& molad){
  long int* p = ptr_to_data + 3;
  long int* q = molad.ptr_to_data + 3;
  while(p > ptr_to_data)*--p = *--q;
}

void MoladNumber:: modulo(const MoladNumber& molad){
  long int* p  = molad.ptr_to_data + 2;
  long int remainder = *p % 1080;
  long int whole  = *p/1080;
  *p = remainder;

  p = molad.ptr_to_data + 1;
  *p = *p + whole;
  remainder = *p % 24;
  whole = *p/24;
  *p = remainder;

  p = molad.ptr_to_data;
  *p = *p + whole;


}

MoladNumber& MoladNumber::operator=(const MoladNumber& rhs){
  copy(rhs);
  return *this;
}


MoladNumber::MoladNumber(const long int days, const long int hours, const long int halakim){
  ptr_to_data = new long int[3];
  ptr_to_data[0] = days;
  ptr_to_data[1] = hours;
  ptr_to_data[2] = halakim;
  modulo(*this);
}


MoladNumber::~MoladNumber(){
  delete [] ptr_to_data;
}

long int& MoladNumber::operator[](int i){
  return ptr_to_data[i];
}

MoladNumber& MoladNumber::operator+(const MoladNumber& rhs){
  long int* p = ptr_to_data;
  long int* q = rhs.ptr_to_data;
  for (int i =0; i<=2; i++){
    *p = *p + *q;
    p++;
    q++;
  }

  modulo(*this);


  return *this;
}

MoladNumber& MoladNumber::operator*(const long int& multiplier){
  for (int i =0; i<=2; i++){
  ptr_to_data[i] = (ptr_to_data[i]) * multiplier;
  }

  modulo(*this);
  return *this;
}

long int MoladNumber::Days(){
return ptr_to_data[0];
}
long int MoladNumber::WeekDays(){
return ptr_to_data[0] % 7;
}
long int MoladNumber::Hours(){
return ptr_to_data[1];
}
long int MoladNumber::Halakim(){
return ptr_to_data[2];
}

int main(){
  Number hebrew_year;

  cout << "Hebrew year: " << endl;
  cin >> hebrew_year;
  
  Number this_hebrew_year, next_hebrew_year;
  this_hebrew_year = hebrew_year;
  next_hebrew_year = hebrew_year+1;

  RoshHashana ThisYearsRoshHashana(this_hebrew_year,1);
  ThisYearsRoshHashana.PrintSummary();
  ThisYearsRoshHashana.PrintSummaryToFile(this_hebrew_year);

  RoshHashana NextYearsRoshHashana(next_hebrew_year,1);
  NextYearsRoshHashana.PrintSummary();
  NextYearsRoshHashana.PrintSummaryToFile(next_hebrew_year);

  Number year_length = NextYearsRoshHashana.full_day() - ThisYearsRoshHashana.full_day();
    cout << "Length of year " << this_hebrew_year << " : " << year_length << " days" << endl;

    cout << endl << "Enter first year last year" << endl;
    long int first_year,last_year;
    cin >> first_year >> last_year;
 for (int i_year=first_year ;i_year<=last_year;i_year++){
   RoshHashana RoshHashana1(i_year,0);
   RoshHashana RoshHashana2(i_year+1,0);
   int length = RoshHashana2.full_day()-RoshHashana1.full_day();
   cout << "Length of year " << i_year << " : " << length << endl;
   if( length < 353 || length > 385 ||  (length > 355 && length < 383)){
     cout << "Illegal year length ! " << endl;
     char anykey;
     cout << "Press <return> to continue" << endl;
     cin >> anykey;
   }
 }


  return 0;
}

