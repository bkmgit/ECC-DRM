
#include "BigNumber.h"


// The strcture of the point in Elliptic Curve (EC)
struct ECpoint 
  { 
      BigNumber x;
      BigNumber y;
  };

// Prototypes of the functions
ECpoint ECDouble(ECpoint Q, int A, BigNumber P); 
ECpoint ECAdd(ECpoint Q,ECpoint G, BigNumber P);
ECpoint ECSub(ECpoint Q,ECpoint G, BigNumber P);
String* Convert_To_DRM(BigNumber num, String bin);
BigNumber inverse(BigNumber a, BigNumber m);
BigNumber modulus(BigNumber xx, BigNumber yy);

void setup()
{
 Serial.begin(9600);



BigNumber x = "11";
BigNumber y = "9";
BigNumber z = "1";
BigNumber w, mod;

z = x/y;
w = z*y;
mod = x-w;
Serial.println(mod);

Serial.println("++++++++++++++++++++++++++++++++++++++++++");
//int q = inverse(b);
BigNumber q = "0";
q = inverse(x,y);
Serial.println(q);
Serial.println("++++++++++++++++++++++++++++++++++++++++++");










 
 // Converting BigNumber to Binary
 Serial.println("Converting BigNumber to Binary .....");
 BigNumber numk = "681123288";
 String INTbin = String(numk, BIN);
 Serial.println(INTbin);
 Serial.println("------------------------------");
 
 //Converting Binary to DRM
 int keysize = 31;
 String* DRMs = new String[keysize];
 DRMs = Convert_To_DRM(numk,INTbin);
 for(int k = 0; k<keysize; k++)
   Serial.print(DRMs[k]);
Serial.println("");
Serial.println("------------------------------");






 String binstr;
 BigNumber P = "1111";
 
 binstr = "111111111111111111111";
 int A=-3;
 int intKLen=25;
 

  BigNumber chGx,chGy;
   chGx    = "2733";
   chGy    = "7034";
    ECpoint Qs,Rs,Q, R;
    Qs.x = chGx; 
    Qs.y = chGy;
// Serial.println((int)(chGx + chGy));
 Serial.println("Start Scalar Multiplications......");

 for (int i=0;i<keysize;i++)
 { 
   Serial.println(DRMs[i]);
   if (DRMs[i] == "1")
    {
           //Rs=ECAdd(Rs,Qs, P); //adds++;
        Serial.println("");
    }
    else if (DRMs[i] == "-1")
    {
         // Rs=ECSub(Rs,Qs,P); //subs++;
         Serial.println("");
    }
     Qs = ECDouble(Qs,A, P);//dubs++;
     

  //Serial.println(Qs.x);
 }

 Serial.println("End Scalar Multiplication...");

}




void loop()
{
}

// The function of finding the doubleing
ECpoint ECDouble(ECpoint Q, int A, BigNumber P)
{
  BigNumber AA = "1";
  BigNumber s1,AC1,AC2,AC3;
  ECpoint R;
  AC1 = Q.x * "3";
  AC2 = Q.y * "2";
  //Serial.println(AC2);

  AC3 = inverse(AC2,P);
  Serial.println(AC3);

 // s1 = ((AC1*Q.x) - (AA)) * AC3;

  BigNumber RR, RX = "0", RY;
  RR = ((s1*s1)-(Q.x)-(Q.x));//% P;
  
  RX = modulus(RR, P);

  Serial.println("");
  Serial.println(RX);

  
  R.y  = (s1*(Q.x-R.x)-Q.y)%P;
  R.x=(R.x <0 ? R.x+P : R.x);
  R.y= (R.y<0 ? R.y+P : R.y);

  return R;
}

// The function of finding the addition
ECpoint ECAdd(ECpoint Q,ECpoint G, BigNumber P)
{
  BigNumber s1,AC1; 
  ECpoint R;
  AC1= ((Q.x^-1)%P)%P;
  Q.x = (Q.x-G.x)%P;
  Q.x=(Q.x<0 ? Q.x+P : R.x);
  s1 = (((Q.y-G.y)%P)*AC1)%P;
  R.x = ((s1*s1)%P-G.x-Q.x) % P;
  R.y = ((s1*(G.x-R.x))%P-G.y) % P;
  R.x=(R.x<0 ? R.x+P : R.x);R.y = (R.y<0 ? R.y+P : R.y);
  R.x = R.y = "0" ;
  return R;
}

// The function of finding the subtraction
ECpoint ECSub(ECpoint Q,ECpoint G, BigNumber P)
{
  BigNumber s1,AC1; 
  ECpoint R;
  AC1= ((Q.x^-1)%P)%P;
  G.y = G.y %P;G.y=(G.y<0 ? G.y+P : G.y); 
  Q.x = (Q.x-G.x)%P;
  Q.x=(Q.x<0 ? Q.x+P : R.x);
  s1 = (((Q.y-G.y)%P)*AC1)%P;
  R.x = ((s1*s1)%P-G.x-Q.x) % P;
  R.y = ((s1*(G.x-R.x))%P-G.y) % P;
  R.x=(R.x<0 ? R.x+P : R.x);R.y= (R.y<0 ? R.y+P : R.y);
  return R;
}

// Converting the binary to DRM representation
String* Convert_To_DRM(BigNumber num, String bin)
{
  Serial.print("Key size is : ");
  Serial.println(bin.length());
  BigNumber num1, num2;
  BigNumber temp = "1";
  
  for(int x =0; x<bin.length(); x++)
  temp  = temp * "2";
 
  Serial.println();
  
  num2 = temp-num;
  Serial.print("Num1 :");
  Serial.println(temp);
  Serial.print("Num2 :");
  Serial.println(num2);

  String str1, str2;
  str1 = String(temp, BIN);
  Serial.print("Str1 :");
  Serial.println(str1);

  str2 = String(num2, BIN);
  Serial.print("Str2 :");
  Serial.println(str2);
  
  
  int len_str1 = 0, len_str2 = 0;
 
  len_str1 = str1.length();
  len_str2 = str2.length();
  Serial.print("Str1_length :");
  Serial.println(len_str1);
  Serial.print("Str2_length :");
  Serial.println(len_str2);

  
 
  String* DRM = new String[str1.length()];
 
  byte bit;
  int j ;
  for (j = 0; j < (len_str1 - len_str2); j++)
  {
    bit = str1[j];
      DRM[j] = str1[j];
      Serial.print(str1[j]);
  }
  for(int i = 0; i<len_str2; i++)
  {
      if (str2[i] == '0')
      {
        DRM[j+i] = "0";
        //Serial.print("0");
      }
      else
      {
        DRM[j+i] = "-1";
        //Serial.print("-1");
      }
   }
          
    Serial.println("");
    return DRM;
}






String convertBigNumberToBinary(BigNumber bn)
{
  BigNumber multiplier = BigNumber(16);
  BigNumber remainder;
  BigNumber result ;
  String finalHex;
  while(bn !=0)
  {
    result = bn / multiplier;
    remainder = bn - (result *  multiplier);
    //Serial.println(remainder);
    //Serial.println(String((int)remainder,BIN));
    String newString = padLeft(String((int)remainder,BIN));
    newString.concat(finalHex);
    finalHex = newString;
    bn = result;
  }
  return finalHex;
}



String padLeft(String str)
{
  while(str.length() < 4)
  {
    String zeroString = "0";
    zeroString.concat(str);
    str = zeroString;
  }
    return str;
}



BigNumber inverse(BigNumber a, BigNumber m)
{
  
    a = a%m; 
    for (BigNumber x= 1; x<m; x++) 
    {
        if (modulus((a*x),m) == 1) 
        {        Serial.println(x);
          return x;
        }
    }
}


BigNumber modulus(BigNumber x, BigNumber y)
{
 
 BigNumber z ;
 BigNumber w, mod;

 z = x/y;
 w = z*y;
 mod = x-w;
 return mod;
}







  
