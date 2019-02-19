
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
 BigNumber::begin ();  // initialize library


BigNumber x = "963458368592368563485634895834573465346572371";
BigNumber y = "165843658364586345834659384653459345834653831";
BigNumber z = "1";
BigNumber w, mod;

z = x/y;
w = z*y;
mod = x-w;
//Serial.println(mod);
w = modulus(x,y);
//Serial.println(w);
//Serial.println("++++++++++++++++++++++++++++++++++++++++++");
//int q = inverse(b);
BigNumber q = "0";
q = inverse(x,y);
//Serial.println(q);
//Serial.println("++++++++++++++++++++++++++++++++++++++++++");


 // Converting BigNumber to Binary
 Serial.println("Converting BigNumber to Binary.....");
 BigNumber numk = "587235983553484388378941111888568654865834846841";
 String INTbin = convertBigNumberToBinary(numk);


 Serial.println(INTbin);
 Serial.println("------------------------------");

 
 //Converting Binary to DRM
 int keysize = 100;
 String* DRMs = new String[keysize];

 DRMs = Convert_To_DRM(numk,INTbin);

 for(int k = 0; k<keysize; k++)
   Serial.print(DRMs[k]);
Serial.println("");
Serial.println("--------------------------------");


 String binstr;
 BigNumber P = "11111111111111111111111111111111111111111";
 
 BigNumber A="-3";
 BigNumber chGx,chGy;
 chGx    = "7343434387493593453497594594359749579475495775984234";
 chGy    = "3343249834834843883789465648885686548658348468486485";
 ECpoint Qs,Rs,Q, R;
 Qs.x = chGx; 
 Qs.y = chGy;
 //Serial.println("Multiply = ");
 //Serial.println((chGx * chGy));
 Serial.println("Start Scalar Multiplications......");

 for (int i=0;i<keysize;i++)
 { 
  /*
   //Serial.println(DRMs[i]);
   
   if (DRMs[i] == "1")
    {
           Rs=ECAdd(Rs,Qs,P); 
    }
    else if (DRMs[i] == "-1")
    {
           Rs=ECSub(Rs,Qs,P); 
    }
  */  
           Qs = ECDouble(Qs,A,P);     
  
  Serial.println(Qs.x);
 
 }
 
 Serial.println("------------------------------------------------------");
 
 Serial.println("The Result......");
 Serial.print("Q.x = ");
 Serial.println(Qs.x);
 Serial.print("Q.y = ");
 Serial.println(Qs.y);
 Serial.println("End Scalar Multiplication...");

}




void loop()
{
}

// The function of finding the doubleing
ECpoint ECDouble(ECpoint Q, BigNumber A, BigNumber P)
{
  BigNumber s1,AC1,AC2,AC3;
  ECpoint R;
  AC1 = Q.x * "3";
  AC2 = Q.y * "2";
  //Serial.print("Q.x = ");
  //Serial.println(Q.x);

  AC3 = inverse(AC2,P);
  AC3 = AC3%P;
  //Serial.print("AC3 = ");
  //Serial.println(AC3);
  //Serial.print("checking = ");
  //Serial.println(modulus((AC2 * AC3),P));
  s1 = ((AC1*Q.x) + (A)) * AC3;
  //Serial.print("s1 = ");
  //Serial.println(s1);
  BigNumber RR, RX = "0", RY;
  R.x = ((s1*s1)-(Q.x)-(Q.x))% P;
  R.y  = (s1*(Q.x-R.x)-Q.y)%P;
  R.x=(R.x <0 ? R.x+P : R.x);R.y= (R.y<0 ? R.y+P : R.y);
  //Serial.print("R.x = ");
  //Serial.println(R.x);

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
  //Serial.print("R.x = ");
  //Serial.println(R.x);
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
    
  num2 = temp-num;
  
  Serial.print("Num1 :");
  Serial.println(temp);
  Serial.print("Num2 :");
  Serial.println(num2);
  
  String str1, str2;
  str1 = String(temp, BIN);
  str1 = convertBigNumberToBinary(temp);
  Serial.print("Str1 :");
  Serial.println(str1);

  str2 = String(num2, BIN);
  str2 = convertBigNumberToBinary(num2);
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
  //Serial.println(len_str1 - len_str2);
  for (j = 0; j < (len_str1 - len_str2); j++)
  {
    bit = str1[j];
      DRM[j] = str1[j];
      //Serial.print(str1[j]);
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
          
    //Serial.println("");
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
    //Serial.println("inverse function......");
    BigNumber m0 = m; 
    BigNumber y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        BigNumber q = a / m; 
        BigNumber t = m; 
  
        m = modulus(a,m), a = t; //m = a % m
        t = y; 
        
        y = x - q * y; 
        x = t; 
    } 
     
    if (x < 0) 
       x += m0; 
  
    return x; 
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







  
