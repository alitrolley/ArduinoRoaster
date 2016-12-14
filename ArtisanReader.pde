import processing.serial.*;
import java.io.BufferedReader;
import java.io.*;
int mySwitch=0;
int counter=0;
String [] subtext =  {"0"};
Serial myPort;

void setup(){
 
 //Open the serial port for communication with the Arduino
 //Make sure the COM port is correct
 myPort = new Serial(this, "/dev/tty.usbmodem1411", 115200);
 myPort.bufferUntil('\n');
 readData("/Users/maxhoward/Desktop/coffeeroaster/log1.alog");
 /* Only send new data. This if statement will allow new data to be sent to
 the arduino. */
 if(counter<subtext.length){
 /* Write the next number to the Serial port and send it to the Arduino 
 There will be a delay of half a second before the command is
 sent to turn the LED off : myPort.write('0'); */
 myPort.write(subtext[counter]);
 println(subtext[counter]);
 myPort.write(',');
 delay(500);
 myPort.write('0');
 delay(50000);
 //Increment the counter so that the next number is sent to the arduino.
 counter++;
 } else{
 //If the text file has run out of numbers, then read the text file again in 5 seconds.
 delay(5000);
 mySwitch=1;
 }
}

void draw()
{
  
} 

/* The following function will read from a CSV or TXT file */
void readData(String myFileName){
 
 File file=new File(myFileName);
 BufferedReader br = null;
 try{
  FileReader f = new FileReader(file);
  br =new BufferedReader(f);
  String text=br.readLine();
  
  String startOfTemperaturesString = "'temp2': [";
  String endOfTemperaturesString = "], 'temp1': [";
  
  String temperatures = text.substring(text.indexOf(startOfTemperaturesString)+startOfTemperaturesString.length(), text.indexOf(endOfTemperaturesString));
  myPort.write(temperatures);
  
 }catch(FileNotFoundException e){
 e.printStackTrace();
 }catch(IOException e){
 e.printStackTrace();
 }finally{
 try {
 if (br != null){
 br.close();
 }
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
}